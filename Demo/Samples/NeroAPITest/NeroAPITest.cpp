/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / Samples
|*
|* PROGRAM: NeroAPITest.cpp
|*
|* PURPOSE: This command line program demonstrates everything that Nero API can do:
|*			- read information about a CD
|*			- burn audio CD
|*			- burn ISO CD
|*			- burn mixed mode CD
|*			- burn Video and Super Video CD
|*			- burn Nero CD image
|*			- extract CDA tracks
******************************************************************************/

#include "NeroAPIGlue.h"

#include <winbase.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <signal.h>

#include "NeroISODemo.h"


// import the implementation of NeroWaitCDTexts()
#define NERO_WAITCD_TEXTS
#include "NeroUserDialog.h"
#undef NERO_WAITCD_TEXTS

/*
** function declarations
*/
static void NeroError (char *action); /* display Nero error and exit */

/* for the settings */
static BOOL NERO_CALLBACK_ATTR IdleCallback (void *pUserData);
static NeroUserDlgInOut NERO_CALLBACK_ATTR UserDialog (void *pUserData, NeroUserDlgInOut type, void *data);

/* for the progress display */
static BOOL NERO_CALLBACK_ATTR ProgressCallback (void *pUserData, DWORD dwProgressInPercent);
static BOOL NERO_CALLBACK_ATTR AbortedCallback (void *pUserData);
static void NERO_CALLBACK_ATTR AddLogLine (void *pUserData, NERO_TEXT_TYPE type, const char *text);
static void NERO_CALLBACK_ATTR SetPhaseCallback (void *pUserData, const char *text);
static void NERO_CALLBACK_ATTR DisableAbortCallback (void *pUserData,BOOL abortEnabled);
static void NERO_CALLBACK_ATTR SetMajorPhaseCallback(void *pUserData,NERO_MAJOR_PHASE phase,void *reserved);

/* IO callbacks - both take a FILE * as user data */
static DWORD NERO_CALLBACK_ATTR WriteIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen);
static DWORD NERO_CALLBACK_ATTR ReadIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen);
static BOOL NERO_CALLBACK_ATTR EOFCallback (void *pUserData);
static BOOL NERO_CALLBACK_ATTR ErrorCallback (void *pUserData);

/* parameter parsing */
typedef enum {
	WAV,
	MP3,
	WMA,
	PCM,
	MPEG,
	JPEG,
	AVI,
	IMAGE,
	UNKNOWN
} FileType_t;

/*
** global resources
*/

NERO_DEVICEHANDLE NeroDeviceHandle;
NERO_SCSI_DEVICE_INFOS *NeroDeviceInfos;
NERO_CD_INFO *NeroCDInfo;
#define DUMMY_USER_DATA &NeroSettings 	/* &NeroSettings as user data is only used as illustration */
NERO_SETTINGS NeroSettings =
{
	"NeroFiles",                    /* look for DLLs in sub directory */
	NULL,NULL,
	"Nero.txt",
	{ IdleCallback, DUMMY_USER_DATA },
	{ UserDialog, DUMMY_USER_DATA }
};

NERO_PROGRESS NeroProgress =
{
	ProgressCallback,
	AbortedCallback,
	AddLogLine,
	SetPhaseCallback,
	DUMMY_USER_DATA,
	DisableAbortCallback,
	SetMajorPhaseCallback
};

/*
** CTRL-C handling => remember and return TRUE in IdleCallback to make API abort
*/

BOOL Aborted = FALSE;
static void __cdecl SigCtrlC (int sig)
{
	Aborted = TRUE;
}

/* free resources and exit */
static void Exit (int ret)
{
	/* all of these functions may be called even if NeroAPIGlueInit() failed. */
	NeroCloseDevice (NeroDeviceHandle);
	NeroFreeMem (NeroDeviceInfos);
	NeroFreeMem (NeroCDInfo);
	NeroClearErrors ();
	NeroDone ();

	NeroAPIGlueDone();

	puts ("\npress RETURN to exit");
	getchar ();
	exit (ret);
}



static void Usage (char *descr, void *descr_param)
{
	if (descr) {
		printf (descr, descr_param);
		puts ("");
	}
	puts ("Usage: --listdrives\n"
		  "       --cdinfo --drivename 'xxx'\n"
	      "       --write --drivename 'xxx' [--real] [--TAO] [--bup] [--artist 'artist'] [--title 'title'] [--speed x] [--pause x] [--audioinindex0] 'audio file1' 'audio file2' ... [--cdextra] [--iso 'volume name'] [--iso-no-joliet] [--iso-mode2] 'file/dir1' 'file/dir2' ...\n"
		  "		  --write --drivename 'xxx' --videocd [--real] [--TAO] [--bup] [--speed x] 'mpeg/jpeg file1' ...\n"
		  "		  --write --drivename 'xxx' --svideocd [--real] [--TAO] [--bup] [--speed x] 'mpeg/jpeg file1' ...\n"
		  "		  --write --drivename 'xxx' --image [--real] [--TAO] [--bup] [--speed x] 'nrg file'\n"
		  "       --read --drivename 'xxx' --'xy' 'file1' --'xy' 'file2' ...\n"
		  "		  --erase [--entire] --drivename 'xxx'\n"
		  "		  --eject --drivename 'xxx'\n"
		  "		  --load --drivename 'xxx'\n"
		  "\n"
		  "'xy'       = track number\n"
		  "'file'     = file name including suffix; only .wav and .pcm are supported for audio\n"
		  "'dir/file' = after --iso: file or or directory tree to be added in the root directory\n"
		  );
	Exit (10);
}


int __cdecl main(int argc, char* argv[])
{
	/* parse args */
	BOOL listdrives = FALSE,
		cdinfo = FALSE,
		write = FALSE,
		read = FALSE,
		real = FALSE,
		CDExtra = FALSE,
		TAO = FALSE,
		data = FALSE,
		videocd = FALSE,
		svideocd = FALSE,
		image = FALSE,
		speedtest = FALSE,
		eject = FALSE,
		no_eject = FALSE,
		load = FALSE,
		erase = FALSE,
		entire = FALSE,
		bup = FALSE,
		dvd = FALSE,
		verify = FALSE,
		listspeed = FALSE,
		bAudioInIndex0 = FALSE;
	int writebuffersize=0,iPauseLength=-1;
	float speed = 0;  /* maximum */
	char *drivename = NULL;
	char *artist = NULL, *title = NULL, *pPauseLenStr = NULL;
	char *files[99]; /* maximum number of tracks per CD */
	char *tempdir=NULL;
	unsigned int tracks[99];
	FileType_t type[99];
	unsigned int num_files = 0;
	unsigned int i;
	CDemoIsoTrack IsoTrack;

	/* skip program name */
	argc--;
	argv++;
	while (argc > 0) {
		BOOL had_parameter = FALSE; /* this argument had a parameter */
		if (!strncmp(*argv, "--", 2)) {
			/* option */
			if (!stricmp(*argv, "--listdrives")) {
				listdrives = TRUE;
			} else if (!stricmp(*argv, "--cdinfo")) {
				cdinfo = TRUE;
			} else if (!stricmp(*argv, "--drivename")) {
				if (argc <= 1) {
					Usage ("no drive name specified", 0);
				}
				drivename = argv[1];
				had_parameter = TRUE;
			} else if (!stricmp(*argv, "--write")) {
				write = TRUE;	
			} else if (!stricmp(*argv, "--real")) {
				real = TRUE;
			} else if (!stricmp(*argv, "--speedtest")) 
			{
				speedtest = TRUE;
			} else if (!stricmp(*argv, "--TAO")) {
				TAO = TRUE;
			} else if (!stricmp(*argv, "--bup")) 
			{
				bup = TRUE;
			} else if (!stricmp(*argv, "--read")) 
			{
				read = TRUE;
			} else if (!stricmp(*argv, "--speed")) {
				if (argc <= 1) {
					Usage ("missing argument for --speed", 0);
				}
				speed = atof (argv[1]);
				had_parameter = TRUE;
			} else if (!stricmp(*argv, "--artist"))
			{
				if (argc<=1)
					Usage("Missing argument for --artist", 0);
				artist=argv[1];
				had_parameter=TRUE;
			} else if (!stricmp(*argv, "--title"))
			{
				if (argc<=1)
					Usage("Missing argument for --title", 0);
				title=argv[1];
				had_parameter=TRUE;
			} else if (!stricmp(*argv, "--audioinindex0"))
			{
				bAudioInIndex0 = TRUE;
			} else if (!stricmp(*argv, "--pause"))
			{
				if(argc<=1)
					Usage("Missing argument for --pause", 0);
				pPauseLenStr=argv[1];
				had_parameter=TRUE;
			}
			else if (!stricmp(*argv, "--iso") || !stricmp(*argv, "--udf") || !stricmp(*argv, "--isoudf")) 
			{
				data = TRUE;
				if (argc > 1) {
					IsoTrack.SetVolumeName (argv[1]);
					had_parameter = TRUE;
				}
				IsoTrack.SetISO(!stricmp(*argv, "--iso") || !stricmp(*argv, "--isoudf"));
				IsoTrack.SetUDF(!stricmp(*argv, "--udf") || !stricmp(*argv, "--isoudf"));
			} 
			else if (!stricmp(*argv, "--dvd"))
			{
				dvd=TRUE;
			} 
			else if (!stricmp(*argv, "--dvdvideo"))
			{
				dvd=TRUE;
				IsoTrack.SetReallocDVDVideoFiles(TRUE);
			}
			else if (!stricmp (*argv, "--iso-no-joliet")) {
				IsoTrack.SetJoliet (FALSE);
			} else if (!stricmp (*argv, "--iso-mode2")) {
				IsoTrack.SetMode2 (TRUE);
			} else if (!stricmp (*argv, "--cdextra")) {
				CDExtra = TRUE;
			} else if (!stricmp (*argv, "--videocd"))
			{
				videocd = TRUE;
			} else if (!stricmp (*argv, "--svideocd"))
			{
				svideocd = TRUE;
			} else if (!stricmp (*argv, "--image"))
			{
				image = TRUE;
			} else if (!stricmp (*argv, "--eject"))
			{
				eject = TRUE;
			} else if (!stricmp (*argv, "--no_eject"))
			{
				no_eject = TRUE;
			} else if (!stricmp (*argv, "--load"))
			{
				load = TRUE;
			} else if (!stricmp (*argv, "--erase"))
			{
				erase = TRUE;
			} else if (!stricmp (*argv, "--entire"))
			{
				entire = TRUE;
			} else if (!stricmp( *argv, "--writebuffersize"))
			{
				if (argc<=1)
					Usage("Missing buffer size",0);
				else
				{
					writebuffersize=atoi(argv[1])*1024;
					had_parameter = TRUE;
				}
			} else if (!stricmp( *argv, "--tempdir"))
			{
				if (argc<=1)
					Usage("Missing temp directory",0);
				else
				{
					tempdir=argv[1];
					had_parameter = TRUE;
				}
			} else if (!stricmp( *argv, "--verify"))
			{
				verify = TRUE;
			} else if (!stricmp( *argv, "--listspeed"))
			{
				listspeed = TRUE;
			}
			else if (atoi(&argv[0][2])) {
				/* file with track number */
				int track_number = atoi(&argv[0][2]);
				if (argc <= 1) {
					Usage ("no file specified after track number %ld", (void *)track_number);
				}
				if (num_files < sizeof(files) / sizeof(files[0])) {
					tracks[num_files] = track_number;
					files[num_files++] = argv[1];
				} else {
					Usage ("Number of files limited to 99.", 0);
				}
				had_parameter = TRUE;
			} else {
				Usage ("Unknown parameter %s", argv[0]);
			}
		} else {
			/* file - either ISO or audio */
			if (data) {
				IsoTrack.AddEntry (*argv);
			} 
			else if (write)
			{
				if (num_files < sizeof(files) / sizeof(files[0])) {
					tracks[num_files] = 0;
					files[num_files++] = argv[0];
				} else {
					Usage ("Number of files limited to 99.", 0);
				}
			} else
			{
				Usage("",0);
				Exit(0);
			}
		}
		argc--;
		argv++;
		if (had_parameter) {
			argc--;
			argv++;
		}
	}

	/* verify args */
	if(TAO && bAudioInIndex0)
		Usage ("--TAO and --audioinindex0 are mutually exclusive", 0);
	if(pPauseLenStr != NULL)
	{
		iPauseLength = atoi(pPauseLenStr);
		if((iPauseLength<0) || (iPauseLength>7500))
			Usage ("invalid pause length specified (valid: 0-7500)", 0);
	}
	if(iPauseLength < 0)				/* Pause length unspecified -> set it to the default pause length of 2 seconds */
		iPauseLength = 2 * 75;
	if(TAO && (iPauseLength!=2*75))		/* In TAO only default pause length is supported */
	{
		Usage ("a pause length other than 150 blocks is not supported in TAO mode", 0);
	}
	if (read && write) {
		Usage ("--read and --write are mutually exclusive", 0);
	}
	if (read || write) {
		if (!drivename) {
			Usage ("required drive name not specified", 0);
		}
		if (!num_files && !data) {
			Usage ("no files specified", 0);
		}
		unsigned int i;
		for (i = 0; i < num_files; i++) {
			char *ext = strrchr (files[i], '.');

			if (ext && !stricmp (ext, ".wav") && !videocd && !svideocd) 
			{
				type[i] = WAV;
			} else if (ext && !stricmp (ext, ".mp3") && !videocd && !svideocd) 
			{
				type[i] = MP3;
			} else if (ext && !stricmp (ext, ".wma") && !videocd && !svideocd) 
			{
				type[i] = WMA;
			} else if (ext && !stricmp (ext, ".pcm") && !videocd && !svideocd)
			{
				type[i] = PCM;
			} else if (ext && (!stricmp (ext, ".mpg") || !stricmp (ext, ".mpeg")) && (videocd || svideocd))
			{
				type[i] = MPEG;
			} else if (ext && !stricmp (ext, ".avi") && (videocd || svideocd))
			{
				type[i] = AVI;
			} else if (ext && (!stricmp (ext, ".jpg") || !stricmp (ext, ".jpeg")) && (videocd || svideocd))
			{
				type[i] = JPEG;
			} else if (ext && (!stricmp (ext, ".nrg") || !stricmp (ext, ".iso") || !stricmp (ext, ".cue"))  && image)
			{
				type[i] = IMAGE;
			}
			else {
				type[i] = UNKNOWN;
				Usage ("unknown file type %s", files[i]);
			}
	
			/* read needs track number */
			if (read && !tracks[i]) {
				Usage ("no track number specified for file %s", files[i]);
			}
		}

	}

	/* initialize */
	signal (SIGINT, SigCtrlC);

	if (!NeroAPIGlueConnect(NULL)) 
	{
		puts ("Cannot connect to NeroAPI");
		Exit (10);
	}
	
	WORD ver1, ver2, ver3, ver4;
	if (!NeroGetAPIVersionEx(&ver1,&ver2,&ver3,&ver4,NULL))
	{
		puts("Could not get NeroAPI version number");
		Exit(10);
	}
	printf ("Nero API version %d.%d.%d.%d\n\n",ver1,ver2,ver3,ver4);

	NEROAPI_INIT_ERROR initErr=NeroInit (&NeroSettings,NULL);
	switch (initErr) 
	{
	case NEROAPI_INIT_OK:
		break;
	case NEROAPI_INIT_INVALID_ARGS:
		NeroError ("NeroInit() : invalid args");
		break;
	case NEROAPI_INIT_INVALID_SERIAL_NUM:
		NeroError ("NeroInit() : invalid serial number");
		break;
	case NEROAPI_INIT_DEMOVERSION_EXPIRED:
		NeroError ("NeroInit() : demo version has expired");
		break;
	case NEROAPI_INIT_CANNOT_LOCK:
		NeroError ("NeroInit() : cannot lock");
		break;
	default:
	case NEROAPI_INIT_UNSPECIFIED_ERROR:
		NeroError ("NeroInit() : unspecified error");
	}

	if (writebuffersize!=0)
	{
		NeroSetOption(NEROAPI_OPTION_WRITE_BUFFER_SIZE,&writebuffersize);
	}

	NeroDeviceInfos = NeroGetAvailableDrivesEx (dvd ? MEDIA_DVD_ANY : MEDIA_CD,NULL);
	if (!NeroDeviceInfos) {
		NeroError ("NeroGetAvailableDrives()");
	}

	NERO_SCSI_DEVICE_INFO *pSelectedDeviceInfo;

	if (drivename) {
		for (i = 0; i < NeroDeviceInfos->nsdisNumDevInfos; i++) 
		{
			char driveLetter=NeroDeviceInfos->nsdisDevInfos[i].nsdiDriveLetter ? NeroDeviceInfos->nsdisDevInfos[i].nsdiDriveLetter : '?';

			if (!stricmp(drivename, NeroDeviceInfos->nsdisDevInfos[i].nsdiDeviceName)
				|| (strlen(drivename)==1 && toupper(drivename[0])==toupper(driveLetter)))
			{
				NeroDeviceHandle = NeroOpenDevice (&NeroDeviceInfos->nsdisDevInfos[i]);
				pSelectedDeviceInfo=&NeroDeviceInfos->nsdisDevInfos[i];
				if (!NeroDeviceHandle) 
				{
					NeroError (drivename);
				}
				break;
			}
		}
		if (!NeroDeviceHandle) {
			printf ("Drive %s not found, available are:\n", drivename);
			listdrives = TRUE;
		}
	}

	if (listdrives) 
	{
		printf ("Drive: adapter # (type), ID\n"
			    "-------------------------\n");
		for (i = 0; i < NeroDeviceInfos->nsdisNumDevInfos; i++) 
		{
			char bufUnderrunProtName[128]="";
			char *str;
			if (NeroDeviceInfos->nsdisDevInfos[i].nsdiCapabilities&NSDI_BUF_UNDERRUN_PROT)
			{
				sprintf(bufUnderrunProtName," (%s)",NeroDeviceInfos->nsdisDevInfos[i].nsdiBufUnderrunProtName);
				if (NeroDeviceInfos->nsdisDevInfos[i].nsdiMandatoryBUPSpeed)
					sprintf(bufUnderrunProtName+strlen(bufUnderrunProtName)," (recommanded when burning at %dX or faster)",NeroDeviceInfos->nsdisDevInfos[i].nsdiMandatoryBUPSpeed);
			}

			printf ("%c. %s: %d (%s), %d, %s%s (%s) (%d KB buffer)\n",
				NeroDeviceInfos->nsdisDevInfos[i].nsdiDriveLetter ? NeroDeviceInfos->nsdisDevInfos[i].nsdiDriveLetter : '?',
				NeroDeviceInfos->nsdisDevInfos[i].nsdiDeviceName,
				NeroDeviceInfos->nsdisDevInfos[i].nsdiHostAdapterNo,
				NeroDeviceInfos->nsdisDevInfos[i].nsdiHostAdapterName,
				NeroDeviceInfos->nsdisDevInfos[i].nsdiDeviceID,
				NeroDeviceInfos->nsdisDevInfos[i].nsdiCapabilities&NSDI_ALLOWED ? "" : "(Not allowed) ",
				bufUnderrunProtName,
				str=NeroGetTypeNameOfMedia(NeroDeviceInfos->nsdisDevInfos[i].nsdiMediaSupport,","),
				NeroDeviceInfos->nsdisDevInfos[i].nsdiDriveBufferSize);
			NeroFreeMem(str);
		}
		puts ("");
		Exit(0);
	}

	if (!NeroDeviceHandle)
	{
		Usage ("drive name required", 0);
		Exit (0);
	}
	if (listspeed)
	{
		printf("List of possible speed:\n");
		for(int i=0;i<pSelectedDeviceInfo->nsdiWriteSpeeds.nsiNumSupportedSpeeds;i++)
			printf("%.1fX (%d KB/s)\n",(float)pSelectedDeviceInfo->nsdiWriteSpeeds.nsiSupportedSpeedsKBs[i]/pSelectedDeviceInfo->nsdiWriteSpeeds.nsiBaseSpeedKBs
					,pSelectedDeviceInfo->nsdiWriteSpeeds.nsiSupportedSpeedsKBs[i]);
		
	}
	if (load)
	{
		NeroEjectLoadCD(NeroDeviceHandle,FALSE);
	}
	if (erase)
	{	// Erase CDRW
		NEROAPI_CDRW_ERASE_MODE mode=NEROAPI_ERASE_QUICK;	// Default is quickly
		int time;
		
		if (entire)	mode=NEROAPI_ERASE_ENTIRE;
		time=NeroGetCDRWErasingTime(NeroDeviceHandle,mode);
		if (time==-1)
			NeroError("No CD inserted");
		else if (time==-2)
			NeroError("This CD recorder doesn't support CDRW");
		else if (time==-3)
			NeroError("This media is not rewritable");
		printf("Erasing CDRW. This will take %d seconds.\n",time);
		int err=NeroEraseCDRW(NeroDeviceHandle,mode);
		if (err)
			NeroError("Error erasing the CDRW");
	}
	if (eject)
	{
		NeroEjectLoadCD(NeroDeviceHandle,TRUE);
	}
	if (cdinfo || read) {
		NeroCDInfo = NeroGetCDInfo (NeroDeviceHandle, NGCDI_READ_CD_TEXT|NGCDI_READ_ISRC);
		if (!NeroCDInfo) {
			NeroError ("NeroGetCDInfo()");
		}

		if (cdinfo) {
			switch (NeroCDInfo->ncdiMediumType) {
			case NMT_CD_ROM:
				printf ("Read-only media, ");
				break;
			case NMT_CD_RECORDABLE:
				printf ("Recordable media, ");
				break;
			case NMT_CD_REWRITEABLE:
				printf ("Rewriteable media, ");
				break;
			default:
				printf ("unknown media, ");
				break;
			}
			
			char *mediatypename=NeroGetTypeNameOfMedia(NeroCDInfo->ncdiMediaType,NULL);
			printf("%s ",mediatypename);
			NeroFreeMem(mediatypename);

			printf ("%s, %d blocks free\n",
				NeroCDInfo->ncdiIsWriteable ? "writeable" : "not writable",
				NeroCDInfo->ncdiFreeCapacityInBlocks);
			printf ("Artist %s, Title %s\n",
				NeroCDInfo->ncdiArtist[0] ? NeroCDInfo->ncdiArtist : "unknown",
				NeroCDInfo->ncdiTitle[0] ? NeroCDInfo->ncdiTitle : "unknown");

			for (i = 0; i < NeroCDInfo->ncdiNumTracks; i++) {
				NERO_TRACK_INFO *pTrackInfo = &NeroCDInfo->ncdiTrackInfos[i];
				printf ("%02d. %6s %6d - %6d = %6d blocks, session %d",
					pTrackInfo->ntiTrackNumber,
					pTrackInfo->ntiTrackType == NTT_AUDIO ? "audio" :
					pTrackInfo->ntiTrackType == NTT_DATA ? "data" :
					"unknown",
					pTrackInfo->ntiTrackStartBlk,
					pTrackInfo->ntiTrackStartBlk + pTrackInfo->ntiTrackLengthInBlks,
					pTrackInfo->ntiTrackLengthInBlks,
					pTrackInfo->ntiSessionNumber);
				if (pTrackInfo->ntiArtist[0] || pTrackInfo->ntiTitle[0])
					printf (" (%s %s)\n", pTrackInfo->ntiArtist, pTrackInfo->ntiTitle);
				else
					puts("");

				if (pTrackInfo->ntiISRC[0])
					printf("\tISRC: %s\n",pTrackInfo->ntiISRC);
			}
		}

		if (read) {
			for (i = 0; (int)i < num_files; i++) {
				NERO_TRACK_INFO *pTrackInfo = NULL;
				unsigned int e;
				NERO_CALLBACK callback;
				NERO_DATA_EXCHANGE exchange;
				
				/* tracks may start with a number higher than 1, so search for track */
				for (e = 0; e < NeroCDInfo->ncdiNumTracks; e++) {
					if (NeroCDInfo->ncdiTrackInfos[e].ntiTrackNumber == tracks[i]) {
						pTrackInfo = &NeroCDInfo->ncdiTrackInfos[e];
						break;
					}
				}
				if (!pTrackInfo) {
					printf ("track %d for file '%s' not found on CD\n", tracks[i], files[i]);
					Exit (10);
				}

				/* extract audio */
				callback.ncCallbackFunction = ProgressCallback;
				callback.ncUserData = DUMMY_USER_DATA;
				switch (type[i]) {
				case WAV:
					exchange.ndeType = NERO_ET_FILE;
					strncpy(exchange.ndeData.ndeFileName, files[i], sizeof(exchange.ndeData.ndeFileName));
					exchange.ndeData.ndeFileName[sizeof(exchange.ndeData.ndeFileName) - 1] = 0;
					break;
				case PCM:
					exchange.ndeType = NERO_ET_IO_CALLBACK;
					exchange.ndeData.ndeIO.nioIOCallback = WriteIOCallback;
					exchange.ndeData.ndeIO.nioEOFCallback = EOFCallback;
					exchange.ndeData.ndeIO.nioErrorCallback = ErrorCallback;
					exchange.ndeData.ndeIO.nioUserData = fopen (files[i], "wb");
					if (!exchange.ndeData.ndeIO.nioUserData) {
						printf ("Cannot open target file %s\n", files[i]);
						Exit (10);
					/* We are lazy - closing the file will be done by resource tracking. */
					}
					break;
				
				default:
					/* unknown */
					printf ("unknown file type for writing of %s\n", files[i]);
					Exit (10);
					break;
				}
				printf ("%02d. '%s':\n", tracks[i], files[i]);
				if (NeroDAE (NeroDeviceHandle, pTrackInfo->ntiTrackStartBlk, pTrackInfo->ntiTrackLengthInBlks,
					&exchange, 0, &callback)) {
					NeroError ("NeroDAE()");
				}
				puts ("");
			}
		}
	}

	if (write) 
	{
		int res=0;

		if (!videocd && !svideocd && !image)
		{
			// Burn ISO/Audio CD

			int size = sizeof (NERO_WRITE_CD) + (num_files - 1) * sizeof (NERO_AUDIO_TRACK);
			NERO_WRITE_CD *pWriteCD = (NERO_WRITE_CD *)malloc (size);

			if (!pWriteCD) {
				puts ("no mem");
				Exit (10);
			}
			memset (pWriteCD, 0, size);
			pWriteCD->nwcdMediaType = dvd ? MEDIA_DVD_ANY : MEDIA_CD;
			pWriteCD->nwcdNumTracks = num_files;
			pWriteCD->nwcdArtist = artist;
			pWriteCD->nwcdTitle = title;
			if (data) 
			{
				pWriteCD->nwcdIsoTrack = &IsoTrack;
				pWriteCD->nwcdCDExtra = CDExtra;
			}

			for (i = 0; i < num_files; i++)
			{
				pWriteCD->nwcdTracks [i].natPauseInBlksBeforeThisTrack = ((i==0) ? 2*75 : iPauseLength);	/* Write continously; first track requires minimal pause of 2 seconds (2*75)	*/
				pWriteCD->nwcdTracks [i].natIndex0ContainsData = ((i==0) ? FALSE : bAudioInIndex0);			/* The first track may never contain data in index 0							*/
				/* no indices, artist or title: these values are already NULL */
				switch (type [i]) {
				case WAV:
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeType = NERO_ET_FILE;
					strncpy (pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName, files[i], sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName));
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName[sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName) - 1] = 0;
					break;
				case MP3:
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeType = NERO_ET_FILE_MP3;
					strncpy (pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName, files[i], sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName));
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName[sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName) - 1] = 0;
					break;
				case WMA:
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeType = NERO_ET_FILE_WMA;
					strncpy (pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName, files[i], sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName));
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName[sizeof(pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeFileName) - 1] = 0;
					break;
				case PCM: {
					struct _stat buf;

					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeType = NERO_ET_IO_CALLBACK;
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioIOCallback = ReadIOCallback;
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioEOFCallback = EOFCallback;
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioErrorCallback = ErrorCallback;
					if (_stat (files[i], &buf)) {
						printf ("Cannot determine length of file %s\n", files[i]);
						Exit (10);
					}
					pWriteCD->nwcdTracks [i].natLengthInBlocks = buf.st_size / 2352;
					pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioUserData = fopen (files[i], "rb");
					if (!pWriteCD->nwcdTracks [i].natSourceDataExchg.ndeData.ndeIO.nioUserData) {
						printf ("Cannot open source file %s\n", files[i]);
						Exit (10);
					}
					/* We are lazy - closing the file will be done by resource tracking. */
					break;
				}
				default:
					/* unknown */
					printf ("unknown file type for writing of %s\n", files[i]);
					Exit (10);
					break;
				}
			}
			
			/* burn, baby, burn... */
			res = NeroBurn (NeroDeviceHandle,NERO_ISO_AUDIO_CD ,pWriteCD,
				(real ? NBF_WRITE : NBF_SIMULATE) // Write and simulate are not mutually exclusive, we just use either one or the other here.
				| (TAO ? 0 : NBF_DAO) | NBF_DISABLE_ABORT | NBF_DETECT_NON_EMPTY_CDRW | NBF_SPEED_IN_KBS
				| (speedtest ? NBF_SPEED_TEST : 0)
				| NBF_CLOSE_SESSION
				| NBF_CD_TEXT
				| (bup ? NBF_BUF_UNDERRUN_PROT : 0)
				| (verify ? NBF_VERIFY : 0)
				| (no_eject ? NBF_DISABLE_EJECT : 0),
				speed*pSelectedDeviceInfo->nsdiWriteSpeeds.nsiBaseSpeedKBs
				, &NeroProgress);

			free (pWriteCD);
			pWriteCD = NULL;
		} else if (videocd || svideocd)
		{
			// Burn Video CD or Super Video CD

			int size = sizeof (NERO_WRITE_VIDEO_CD) + (num_files - 1) * sizeof (NERO_VIDEO_ITEM);
			NERO_WRITE_VIDEO_CD *pWriteCD = (NERO_WRITE_VIDEO_CD *)malloc (size);

			if (!pWriteCD) {
				puts ("no mem");
				Exit (10);
			}
			memset (pWriteCD, 0, size);
		
			pWriteCD->nwvcdSVCD=svideocd;
			pWriteCD->nwvcdNumItems=num_files;
			pWriteCD->nwvcdIsoTrack=&IsoTrack;

			if (tempdir)
			{
				strncpy(pWriteCD->nwvcdTempPath,tempdir,sizeof(pWriteCD->nwvcdTempPath));
				pWriteCD->nwvcdTempPath[sizeof(pWriteCD->nwvcdTempPath)-1]=0;
			}

			for (i=0;i<num_files;i++)
			{
				NERO_VIDEO_ITEM *item=&pWriteCD->nwvcdItems[i];
				strncpy (item->nviSourceFileName, files[i], sizeof(pWriteCD->nwvcdItems[i].nviSourceFileName));
				pWriteCD->nwvcdItems[i].nviSourceFileName[sizeof(pWriteCD->nwvcdItems[i].nviSourceFileName)-1]=0;

				if (type[i]==JPEG)
				{
					item->nviItemType=NERO_JPEG_ITEM;
					item->nviPauseAfterItem=-1;
				} else 
				if (type[i]==AVI)
				{
					item->nviItemType=NERO_NONENCODED_VIDEO_ITEM;
					item->nviPauseAfterItem=0;
				} else
				{
					item->nviItemType=NERO_MPEG_ITEM;
					item->nviPauseAfterItem=0;
				}
			}

			/* burn, baby, burn... */
			res = NeroBurn (NeroDeviceHandle,NERO_VIDEO_CD ,pWriteCD,
				(real ? NBF_WRITE : NBF_SIMULATE) 
				| (TAO ? 0 : NBF_DAO) 
				| NBF_DETECT_NON_EMPTY_CDRW 
				| NBF_DISABLE_ABORT 
				| (speedtest ? NBF_SPEED_TEST : 0)/*| NBF_CLOSE_SESSION*/ /* Write and simulate are not mutually exclusive, we just use either one or the other here. */
				| (no_eject ? NBF_DISABLE_EJECT : 0), 
				speed, &NeroProgress);

			free (pWriteCD);
		} else if (image)
		{
			// Burn image
			NERO_WRITE_IMAGE pWriteCD;

			if (num_files<1)
			{
				puts("Image file not specified");
				Exit(10);
			}
			
			strncpy(pWriteCD.nwiImageFileName,files[0],sizeof(pWriteCD.nwiImageFileName));
			pWriteCD.nwiImageFileName[sizeof(pWriteCD.nwiImageFileName)-1]=0;

			/* burn, baby, burn... */
			res = NeroBurn (NeroDeviceHandle,NERO_BURN_IMAGE_CD ,&pWriteCD,
				(real ? NBF_WRITE : NBF_SIMULATE) 
				| (TAO ? 0 : NBF_DAO) 
				| NBF_DISABLE_ABORT 
				| (speedtest ? NBF_SPEED_TEST : 0)/*| NBF_CLOSE_SESSION*/  /* Write and simulate are not mutually exclusive, we just use either one or the other here. */
				| (no_eject ? NBF_DISABLE_EJECT : 0),
				speed, &NeroProgress);
		}

		/* automatically save a log file */
		FILE *fp = fopen ("neroerr.txt", "w");
		if (fp) {
			char *log = NeroGetErrorLog ();
			fputs (log, fp);
			fclose (fp);
			NeroFreeMem (log);
		}

		switch(res)
		{
		case NEROAPI_BURN_OK:
			break;
		case NEROAPI_BURN_UNKNOWN_CD_FORMAT:
			NeroError ("BurnCD() : unknown CD format");
			break;
		case NEROAPI_BURN_INVALID_DRIVE:
			NeroError ("BurnCD() : invalid drive");
			break;
		case NEROAPI_BURN_FAILED:
			NeroError ("BurnCD() : burn failed");
			break;
		case NEROAPI_BURN_FUNCTION_NOT_ALLOWED:
			NeroError ("BurnCD() : function not allowed");
			break;
		case NEROAPI_BURN_DRIVE_NOT_ALLOWED:
			NeroError ("BurnCD() : drive not allowed");
			break;
		case NEROAPI_BURN_USER_ABORT:
			NeroError ("BurnCD() : aborted by the user");
			break;
		default:
			NeroError ("BurnCD() : unknown error");
		}
	}

	/* done */
	Exit (0);
	return 0;
}


/*
** functions using/implementing the API
*/

static BOOL NERO_CALLBACK_ATTR IdleCallback (void *pUserData)
{
	assert (pUserData == DUMMY_USER_DATA);

	/*
	** Nothing to be done in a Shell application.
	** A GUI might react to messages here:
		static MSG msg;
		while ("not canceled" && ::PeekMessage(&msg,NULL,NULL,NULL,PM_NOREMOVE))
			if (!AfxGetThread()->PumpMessage())
				break;	// All messages "pumped"
	*/

	return Aborted;
}

typedef struct {
	char input;
	NeroUserDlgInOut result;
} Input2DlgOut;
	
static NeroUserDlgInOut CharIO (const Input2DlgOut *CharMapping, const char *prompt) /* array is terminated with input == 0 */
{
	NeroUserDlgInOut res = DLG_RETURN_EXIT;
	BOOL cont = TRUE;
	char buffer[80];
	do {
		puts (prompt);
		fgets (buffer, sizeof(buffer), stdin);
		for (int i = 0; CharMapping[i].input != 0; i++) {
			if (toupper(CharMapping[i].input) == toupper(buffer[0])) {
				res = CharMapping[i].result;
				cont = FALSE;
				break;
			}
		}
	} while (!Aborted && cont);

	return res;
}



static NeroUserDlgInOut NERO_CALLBACK_ATTR UserDialog (void *pUserData, NeroUserDlgInOut type, void *data)
{
	static const Input2DlgOut okay_mapping[] = 
	{
		'O', DLG_RETURN_EXIT,
		0
	};
	static const Input2DlgOut yes_no_mapping[] = 
	{
		'Y', DLG_RETURN_TRUE,
		'N', DLG_RETURN_FALSE,
		0
	};

	assert (pUserData == DUMMY_USER_DATA);

	switch (type) {
	case DLG_AUTO_INSERT:
	{
		static const Input2DlgOut mapping[] = 
		{ 
		  'I', DLG_RETURN_INSTALL_DRIVER,
		  'T', DLG_RETURN_OFF_RESTART,
		  'E', DLG_RETURN_EXIT,
		  'C', DLG_RETURN_CONTINUE,
		  0
		};
		puts ("Auto Insert Notification is turned on in the system configuration.\n"
		      "This may cause serious problems while burning: your CD might be damaged,\n"
		      "or the system might hang up.\n\n"

		      "Nero is able to burn CDs with Auto Insert Notification turned on if all\n"
			  "necessary drivers are installed.\n");

		return CharIO (mapping,
			"[I]nstall drivers and restart Windows\n"
			"[T]urn off Auto Insert Notification and restart Windows\n"
			"[E]xit Nero\n"
			"[C]ontinue at your own risk\n");
		break;
	}
	case DLG_DISCONNECT_RESTART:
	case DLG_DISCONNECT:
	{
		puts ("Disconnect is turned off in the system configuration.\n"
			  "This may cause serious problems while burning: your CD\n"
			  "might be damaged, or the system might hang up.\n");

		if (DLG_DISCONNECT_RESTART == type) {
			static const Input2DlgOut mapping[] = 
			{ 
			  'T', DLG_RETURN_ON_RESTART,
			  'D', DLG_RETURN_RESTART,
			  0
			};

			return CharIO (mapping,
				"[T]urn on Disconnect and restart\n"
				"[D]on't change Disconnect option and restart\n");
		} else {
			static const Input2DlgOut mapping[] = 
			{ 
			  'T', DLG_RETURN_ON_RESTART,
			  'D', DLG_RETURN_RESTART,
			  'C', DLG_RETURN_CONTINUE,
			  0
			};

			return CharIO (mapping,
				"[T]urn on Disconnect and restart\n"
				"[D]on't change Disconnect option and restart\n"
				"[C]ontinue at your own risk\n");
		}
		break;
	}
	case DLG_AUTO_INSERT_RESTART:
		puts ("Auto Insert Notification is now OFF. You should restart Windows.\n");
		return CharIO (okay_mapping, "[O]kay\n");
		break;
	case DLG_RESTART:
		puts ("Please restart Windows now.\n");
		return CharIO (okay_mapping, "[O]kay\n");
		break;
	case DLG_SETTINGS_RESTART: {
		static const Input2DlgOut mapping[] = 
		{ 
		  'R', DLG_RETURN_RESTART,
		  'C', DLG_RETURN_CONTINUE,
		  0
		};

		puts ("Nero detected some modifications of your PC system configuration\n"
		      "and needs to modify some settings. Please restart your PC to make\n"
		      "the changes become effective.\n");
		return CharIO (mapping,
			"[R]estart\n"
			"[C]ontinue at your own risk\n");
		break;
	}
	case DLG_OVERBURN:
		puts ("Sorry, this compilation contains too much data to fit on the CD\n"
		      "with respect to the normal CD capacity. Do you want to try\n"
		      "overburn writing at your own risk (this might cause read\n"
		      "errors at the end of the CD or might even damage your recorder)?\n\n"
		      "Note: It is also possible, that SCSI/Atapi errors occur at the end\n"
		      "of the simulation or burning. Even in this case there is a certain\n"
		      "chance, that the CD is readable.\n");

		return CharIO (yes_no_mapping, "[Y]es\n[N]o\n");
		break;
	case DLG_COPY_QUALITY_LOSS:
		puts( "Disc must be written as 'track at once' ('disc at once' not\n"
			  "supported or not able to write such a disc). This means\n"
			  "there might be some minor quality loss (e.g. lost audio index\n"
			  "or different pause between audio tracks). Do you want to\n"
			  "proceed anyway?\n");
		return CharIO (yes_no_mapping, "[Y]es\n[N]o\n");
		break;
	case DLG_COPY_FULLRISK: 
		puts( "Disc must be written as 'track at once' ('disc at once' not\n"
			  "supported or not able to write such a disc).  Unfortunately\n"
			  "your image has a special format which can most likely only\n"
			  "be written correctly with 'disc at once'. But you may\n"
			  "PROCEED AT YOUR OWN RISK. Do you want to continue\n"
			  "burning?\n");
		return CharIO (yes_no_mapping, "[Y]es\n[N]o\n");
		break;
	case DLG_AUDIO_PROBLEMS:
		if ((INT_PTR)data & AUP_NOTRACK_FOUND) {
			puts ("No tracks given.");
			return DLG_RETURN_EXIT;
		}
		if ((INT_PTR)data == AUP_MEGA_FATAL) {
			puts ("fatal internal problem");
			return DLG_RETURN_EXIT;
		}

		puts ("Nero has detected that the following audio properties are not\n"
		      "supported by your recorder in the current write mode and need\n"
		      "to be modified:");
		if ((INT_PTR)data & AUP_FIRST_TR_PAUSE)    puts ("- CD specification allows only 2-3 Seconds pause for the first track");
		if ((INT_PTR)data & AUP_PAUSE_SETTINGS)    puts ("- Pause length between the tracks not supported");
		if ((INT_PTR)data & AUP_INDEX_SETTINGS)    puts ("- Additional index positions not supported");
		if ((INT_PTR)data & AUP_ISRC_SETTINGS)     puts ("- ISRC codes not supported");
		if ((INT_PTR)data & AUP_COPYPROT_SETTINGS) puts ("- Copy protection bit not supported");

		puts ("Nero can change the audio track settings for you to fit the\n"
		      "capabilities of your recorder. This might cause some audio\n"
			  "properties to be lost. Do you want Nero to change the track\n"
			  "settings for you?\n");
		return CharIO (yes_no_mapping, "[Y]es\n[N]o\n");
		break;
	case DLG_WAITCD:
		{
			char *msg=NeroGetLocalizedWaitCDTexts ((NERO_WAITCD_TYPE) (int)data);
			printf("\n%s\n", msg);
			NeroFreeMem(msg);
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
		printf("\nSave image file : ");
		fgets((char *)data,255,stdin);
		// Remove the carriage return
		((char *)data)[strlen((char *)data)-1]=0; 
		return DLG_RETURN_TRUE;
		break;
	case DLG_BURNIMAGE_CANCEL:
		printf("There is not enough space available to burn the image.\n");
		break;
	case DLG_NON_EMPTY_CDRW:
	{
		puts("This CDRW is not empty.");
		static const Input2DlgOut mapping[] = 
		{ 
		  'C', DLG_RETURN_EXIT,
		  'E', DLG_RETURN_CONTINUE,
		  'O', DLG_RETURN_RESTART,
		  0
		};

		NeroUserDlgInOut res=CharIO(mapping,"[E]rase CD\n[O]pen tray\n[C]ancel");
		if (res==DLG_RETURN_CONTINUE)
		{
			// Erase the CDRW
			NEROAPI_CDRW_ERASE_MODE mode=NEROAPI_ERASE_QUICK;
			int time=NeroGetCDRWErasingTime(NeroDeviceHandle,mode);
			if (time==-1)
				NeroError("No CD inserted");
			else if (time==-2)
				NeroError("This CD recorder doesn't support CDRW");
			printf("Erasing CDRW. This will take %d seconds.\n",time);
			int err=NeroEraseCDRW(NeroDeviceHandle,mode);
			if (err)
				NeroError("Error erasing the CDRW");
		}
		return res;
	}
	case DLG_WAITCD_MEDIA_INFO:
		{
			NERO_DLG_WAITCD_MEDIA_INFO *pInfos=(NERO_DLG_WAITCD_MEDIA_INFO *)data;
			printf("Requested media: %s\n",pInfos->ndwmiRequestedMediaName);
			printf("Last detected media: %s\n",pInfos->ndwmiLastDetectedMediaName);
		}
		break;
	default:
		assert (FALSE); // we don't know this type of requester!
		break;
	}
	
	return DLG_RETURN_EXIT;
}

static BOOL NERO_CALLBACK_ATTR ProgressCallback (void *pUserData, DWORD dwProgressInPercent)
{
	printf ("%03d%%\r", dwProgressInPercent);

	return IdleCallback (pUserData);
}

static BOOL NERO_CALLBACK_ATTR AbortedCallback (void *pUserData)
{
//	printf("Abort ?\n");

	return Aborted;
}

static void NERO_CALLBACK_ATTR AddLogLine (void *pUserData, NERO_TEXT_TYPE type, const char *text)
{
	char *header = "  ";
	const char *start;

	switch (type) {
	case NERO_TEXT_INFO:        /* informative text                     */
		header = "i ";
		break;
	case NERO_TEXT_STOP:        /* some operation stopped prematurely   */
		header = "# ";
		break;
	case NERO_TEXT_EXCLAMATION: /* important information                */
		header = "! ";
		break;
	case NERO_TEXT_QUESTION:    /* a question which requires an answer  */
		header = "? ";
		break;
	case NERO_TEXT_DRIVE:		/* a message concerning a CD-ROM drive or recorder */
		header = "- ";
		break;
	default:
		break;
	}

	start = text;
	while (start) {
		char *end = strchr (start, '\n');
		int len = end ? (int)(end - start) : strlen (start);

		fputs (header, stdout);
		fwrite (start, 1, len, stdout);
		// clear rest of line
		len = 79 - strlen (header) - len;
		while (--len >= 0) {
			putchar (' ');
		}

		puts ("");

		start = end ? end + 1 : NULL;
	}
}

static void NERO_CALLBACK_ATTR SetPhaseCallback (void *pUserData, const char *text)
{
	int len;

	printf ("     %s", text);
	// clear rest of line
	len = 79 - strlen (text) - 5;
	while (--len >= 0) {
		putchar (' ');
	}
	putchar ('\r');
}

static void NERO_CALLBACK_ATTR DisableAbortCallback (void *pUserData, BOOL enableAbort)
{
	if (!enableAbort)
		puts("The current process cannot be interrupted");
	else puts("The process can be interrupted again");
}

static void NERO_CALLBACK_ATTR SetMajorPhaseCallback(void *pUserData,NERO_MAJOR_PHASE phase,void *reserved)
{
}

static DWORD NERO_CALLBACK_ATTR WriteIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen)
{
	return fwrite (pBuffer, 1, dwLen, (FILE *)pUserData);
}
static BOOL NERO_CALLBACK_ATTR EOFCallback (void *pUserData)
{
	return feof ((FILE *)pUserData);
}
static BOOL NERO_CALLBACK_ATTR ErrorCallback (void *pUserData)
{
	return ferror ((FILE *)pUserData);
}
static DWORD NERO_CALLBACK_ATTR ReadIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen)
{
	return fread (pBuffer, 1, dwLen, (FILE *)pUserData);
}

static void NeroError (char *action) /* display Nero error and exit */
{
	char *error = NeroGetLastError ();

	puts (action);
	puts (error ? error : "failed");

	NeroFreeMem (error);
	Exit (10);
}

