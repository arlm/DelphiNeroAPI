/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: UserDialog.cpp
|*
|* PURPOSE: Interaction with the user
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"


// IMPORTANT: Unimplemented DLG_ROBO_xxx messages !!!
// 

// This simple structure holds a pair of response text and
// the corresponding return value that should be returned
// if that particular text was selected.

struct CResponse {
	LPCSTR m_psButtonText;
	NeroUserDlgInOut m_RetVal;
};

// This is a helper function that displays a set of choices and allows
// the user to move from one choice to another by pressing the arrow
// keys.

static NeroUserDlgInOut SelectResponse (const CResponse response[], int iSelection = 0)
{
	while (1)
	{
		printf ("\r");
		for (int i = 0; response[i].m_psButtonText != NULL; i ++)
		{
			printf ((i == iSelection)? ">": " ");
			printf ("%s", response[i].m_psButtonText);
			printf ((i == iSelection)? "< ": "  ");
		}
		fflush (stdout);

		while (1)
		{
			unsigned char ch = getch ();
			if (ch == '\r')
			{
				printf ("\r                                                                               ");
				fflush (stdout);
				return response[iSelection].m_RetVal;
			}
			else if (ch == 0xe0)
			{
				ch = getch ();

				if (ch == 75)
				{
					if (iSelection > 0)
					{
						iSelection--;
						break;
					}
				}
				else if (ch == 77)
				{
					if (response[iSelection + 1].m_psButtonText != NULL)
					{
						iSelection ++;
						break;
					}
				}
			}
		}
	}
}

NeroUserDlgInOut NERO_CALLBACK_ATTR CBurnContext::UserDialog (void* pUserData, NeroUserDlgInOut type, void *data)
{
	static const CResponse
		okay_mapping[] = { "OK", DLG_RETURN_EXIT, NULL},
		yes_no_mapping[] = { "Yes", DLG_RETURN_TRUE, "No", DLG_RETURN_FALSE, NULL};

	printf ("\r                                                                                \r");

	switch (type)
	{
		case DLG_AUTO_INSERT:
			{
				static const CResponse mapping[] = 
				{ 
					"Install drivers & restart", DLG_RETURN_INSTALL_DRIVER,
					"Turn off & restart", DLG_RETURN_OFF_RESTART,
					"Exit", DLG_RETURN_EXIT,
					"Continue at own risk", DLG_RETURN_CONTINUE,
					NULL
				};

				puts ("Auto Insert Notification is turned on in the system configuration.\n"
					"This may cause serious problems while burning: your CD might be damaged,\n"
					"or the system might hang up.\n"
					"\n"
					"Nero is able to burn CDs with Auto Insert Notification turned on if all\n"
					"necessary drivers are installed.\n"
					"\n"
					"You can do the following:\n"
					"Install drivers and restart Windows\n"
					"Turn off Auto Insert Notification and restart Windows\n"
					"Exit Nero\n"
					"Continue at your own risk\n");

				return SelectResponse (mapping);
			}
		case DLG_DISCONNECT_RESTART:
		case DLG_DISCONNECT:
			{
				puts ("Disconnect is turned off in the system configuration.\n"
					"This may cause serious problems while burning: your CD\n"
					"might be damaged, or the system might hang up.\n");
				
				if (DLG_DISCONNECT_RESTART == type)
				{
					static const CResponse mapping[] = 
					{ 
						"Turn on & restart", DLG_RETURN_ON_RESTART,
						"Don't turn on & restart\n", DLG_RETURN_RESTART,
						NULL
					};

					return SelectResponse (mapping);
				}
				else
				{
					static const CResponse mapping[] = 
					{ 
						"Turn on & restart", DLG_RETURN_ON_RESTART,
						"Don't turn on & restart", DLG_RETURN_RESTART,
						"Continue at own risk", DLG_RETURN_CONTINUE,
						NULL
					};

					return SelectResponse (mapping);
				}
			}

		case DLG_AUTO_INSERT_RESTART:
			puts ("Auto Insert Notification is now OFF. You should restart Windows.\n");

			return SelectResponse (okay_mapping);

		case DLG_RESTART:
			puts ("Please restart Windows now.\n");

			return SelectResponse (okay_mapping);

		case DLG_SETTINGS_RESTART:
			{
				static const CResponse mapping[] = 
				{ 
					"Restart", DLG_RETURN_RESTART,
					"Continue at own risk", DLG_RETURN_CONTINUE,
					NULL
				};
				
				puts ("Nero detected some modifications of your PC system configuration\n"
					"and needs to modify some settings. Please restart your PC to make\n"
					"the changes become effective.\n");

				return SelectResponse (mapping);
			}

		case DLG_OVERBURN:
			puts ("Sorry, this compilation contains too much data to fit on the CD\n"
				"with respect to the normal CD capacity. Do you want to try\n"
				"overburn writing at your own risk (this might cause read\n"
				"errors at the end of the CD or might even damage your recorder)?\n\n"
				"Note: It is also possible, that SCSI/Atapi errors occur at the end\n"
				"of the simulation or burning. Even in this case there is a certain\n"
				"chance, that the CD is readable.\n");
			
			return SelectResponse (yes_no_mapping);

		case DLG_COPY_QUALITY_LOSS:
			puts( "Disc must be written as 'track at once' ('disc at once' not\n"
				"supported or not able to write such a disc). This means\n"
				"there might be some minor quality loss (e.g. lost audio index\n"
				"or different pause between audio tracks). Do you want to\n"
				"proceed anyway?\n");

			return SelectResponse (yes_no_mapping);

		case DLG_COPY_FULLRISK: 
			puts( "Disc must be written as 'track at once' ('disc at once' not\n"
				"supported or not able to write such a disc).  Unfortunately\n"
				"your image has a special format which can most likely only\n"
				"be written correctly with 'disc at once'. But you may\n"
				"PROCEED AT YOUR OWN RISK. Do you want to continue\n"
				"burning?\n");

			return SelectResponse (yes_no_mapping);

		case DLG_AUDIO_PROBLEMS:
			if (((DWORD)data) & AUP_NOTRACK_FOUND)
			{
				puts ("No tracks given.");
			return DLG_RETURN_EXIT;
			}
			if (((DWORD)data) == AUP_MEGA_FATAL)
			{
				puts ("fatal internal problem");
				return DLG_RETURN_EXIT;
			}
			
			puts ("Nero has detected that the following audio properties are not\n"
				"supported by your recorder in the current write mode and need\n"
				"to be modified:");

			if (((DWORD)data) & AUP_FIRST_TR_PAUSE) puts ("- CD specification allows only 2-3 Seconds pause for the first track");
			if (((DWORD)data) & AUP_PAUSE_SETTINGS) puts ("- Pause length between the tracks not supported");
			if (((DWORD)data) & AUP_INDEX_SETTINGS) puts ("- Additional index positions not supported");
			if (((DWORD)data) & AUP_ISRC_SETTINGS) puts ("- ISRC codes not supported");
			if (((DWORD)data) & AUP_COPYPROT_SETTINGS) puts ("- Copy protection bit not supported");
			
			puts ("Nero can change the audio track settings for you to fit the\n"
				"capabilities of your recorder. This might cause some audio\n"
				"properties to be lost. Do you want Nero to change the track\n"
				"settings for you?\n");

			return SelectResponse (yes_no_mapping);

		case DLG_WAITCD:
			{
				LPCSTR psText = NeroGetLocalizedWaitCDTexts ((NERO_WAITCD_TYPE) (int)data);
				if (psText != NULL)
				{
					printf("\n%s\n", psText);
					NeroFreeMem ((void *) psText);
				}
			}
			break;

		case DLG_WAITCD_REMINDER:
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\b");
			break;

		case DLG_WAITCD_DONE:
			// nothing to be done in the text interface,
			// should close dialog box in a GUI
			break;

		case DLG_FILESEL_IMAGE:
			printf ("Enter file name to save image to: ");
			fgets ((char *) data, 255, stdin);
			// Remove the carriage return
			((char *)data)[strlen((char *)data)-1]=0; 
			return DLG_RETURN_TRUE;

		case DLG_BURNIMAGE_CANCEL:
			printf("There is not enough space available to burn the image.\n");
			break;

		case DLG_NON_EMPTY_CDRW:
		{
			static const CResponse mapping[] = 
			{ 
				"Erase CD", DLG_RETURN_CONTINUE,
				"Eject CD", DLG_RETURN_RESTART,
				"Cancel", DLG_RETURN_EXIT,
				NULL
			};

			NeroUserDlgInOut res;

			puts ("This CDRW is not empty.");

			// Do not ask the user if the --force_erase_cdrw
			// command line parameter has been provided

			// pUserData holds a pointer to CBurnContext which we set 
			// when initializing NeroAPI.
			// We need this pointer to obtain settings and handles
			// from the CBurnContext class.

			if (((CBurnContext*)pUserData)->m_params->GetForceEraseCDRW())
			{
				res = DLG_RETURN_CONTINUE;
			}
			else
			{
				res = SelectResponse (mapping);
			}

			if (DLG_RETURN_CONTINUE == res)
			{
				// Erase the CDRW

				NEROAPI_CDRW_ERASE_MODE mode = NEROAPI_ERASE_QUICK;

				int time = NeroGetCDRWErasingTime(((CBurnContext*)pUserData)->m_NeroDeviceHandle,mode);

				// If time is negative, it means error.
				//
				switch (time)
				{
				case -1:
					puts("No CD inserted!");
					break;

				case -2:
					puts("This CD recorder does not support CDRW!");
					break;

				case -3:
					puts ("The inserted media is NOT rewritable!");
					break;

				default:
					if (time < 0)
					{
						// If this is some unknown error (negative value)
						// we should print generic error message and not
						// even attepmt erasing.
						// 
						puts ("Unknown error while trying to erase CDRW!");
					}
					else
					{
						// If the value is positive, it is the approximate
						// second count the process will take.
						// 
						printf("Erasing CDRW. This will take %d seconds.\n",time);
						
						int err = NeroEraseCDRW(((CBurnContext*)pUserData)->m_NeroDeviceHandle,mode);
						if (err)
						{
							puts("Error erasing the CDRW");
						}
					}
				}
			}
			return res;
		}

		case DLG_WAITCD_MEDIA_INFO:
			{
				const NERO_DLG_WAITCD_MEDIA_INFO * pMediaInfo = (const NERO_DLG_WAITCD_MEDIA_INFO *) data;

				printf ("Last detected media: %s\n", pMediaInfo->ndwmiLastDetectedMediaName);
				printf ("Requested media: %s\n", pMediaInfo->ndwmiRequestedMediaName);

				// The return value is ignored.
				// 
			}
			break;

		case DLG_COMP_REC_CONFLICT:
			puts ("The compilation cannot be written on this recorder! "
					"You should modify your compilation settings or burn "
					"the disc on another recorder, that supports the required medium type.");
			break;

		case DLG_WRONG_MEDIUM:
			puts ("Another type of medium must be used to burn this compilation!");
			break;
	}

	return DLG_RETURN_EXIT;
}
