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
|* PROGRAM: parameters.cpp
|*
|* PURPOSE: Constructor for PARAMETERS class,
|*          setters and getters for data members
******************************************************************************/



#include "parameters.h"


// This is a constructor for our PARAMETERS struct which holds
// our command line arguments. All values are here set to some
// reasonable defaults.

PARAMETERS::PARAMETERS ()
{
	// Set this flag to prevent destruction of strings because we
	// don't own them.

	m_FileList.m_bOwnData = false;

	m_Command = COMMAND_UNKNOWN;
	m_psDriveName = NULL;
	m_bReal = false;
	m_bTAO = false;
	m_bUnderRunProt = false;
	m_psArtist = NULL;
	m_psTitle = NULL;
	m_iReadSpeed = 0;		// 0 is maximum DAE speed.
	m_iSpeed = -1;			// m_iSpeed is speed in X and m_iSpeedInKbps is
	m_iSpeedInKbps = -1;	// speed in kb/s. -1 means "not set".
	m_bCDExtra = false;
	m_eEraseMode = NEROAPI_ERASE_QUICK;
	m_bEnableAbort = false;
	m_bSpeedTest = false;
	m_bCloseSession = false;
	m_iSessionToImport = -1;
	m_bDetectNonEmptyCDRW = false;
	m_bCDText = false;
	m_bUseRockridge = false;
	m_bCreateIsoFS = false;
	m_bCreateUdfFS = false;
	m_bDVDVideoRealloc = false;
//	m_bImportRockridge = false;			// Not used anymore.
	m_bImportIsoOnly = false;
	m_bImportUDF = false;
	m_bPreferRockridge = false;
	m_bDisableEject = false;
	m_bVerify = false;
	m_bDVD = false;
	m_bDVDHighCompatibility = false;
	m_bAudioSelected = false;
	m_bISOSelected = false;
	
	m_psVolumeName = NULL;
	m_bDontUseJoliet = false;
	m_bMode2 = false;
	m_bVolumeNameSupplied = false;

	m_BurnType = BURNTYPE_UNKNOWN;

	m_psImageFilename = NULL;

	m_iNumTracks = 0;

	m_bProcessedParameterFile = false;

	m_bWriteNeroErrorLog = true;
	m_psErrorLogFilename = NULL;
	m_bNeroLogTimestamp = false;
	m_bForceEraseCDRW = false;

	m_psTempPath = "";

	m_bRecursiveSearch = false;
	m_MediaSet = MEDIA_NONE;
}


int PARAMETERS::GetFileListSize() const
{
	return m_FileList.GetSize();
}

const CSimpleStringArray& PARAMETERS::GetFileList() const
{
	return m_FileList;
}

CSimpleStringArray& PARAMETERS::GetFileList()
{
	return m_FileList;
}

LPCSTR PARAMETERS::GetErrorLogName() const
{
	return m_psErrorLogFilename;
}

COMMAND_LINE_ERRORS PARAMETERS::SetErrorLogName(int& argc, char**& argv)
{
	argc--;
	argv++;

	if (argc <= 0)
	{
		return CLE_MISSING_ERROR_LOG_PARAMETER;
	}

	m_psErrorLogFilename = *argv;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::SetWriteErrorLog()
{
	m_bWriteNeroErrorLog = false;
	return CLE_NO_ERROR;
}

bool PARAMETERS::GetWriteErrorLog() const
{
	return m_bWriteNeroErrorLog;
}

COMMAND_LINE_ERRORS PARAMETERS::SetProcessedParameterFile()
{
	if (COMMAND_UNKNOWN != m_Command)
	{
		return CLE_MULTIPLE_COMMANDS_SPECIFIED;
	}

	m_bProcessedParameterFile = true;
	return CLE_NO_ERROR;
}

bool PARAMETERS::GetProcessedParameterFile()
{
	return m_bProcessedParameterFile;
}

const TRACK PARAMETERS::GetTrack(int iTrack) const
{
  return m_Tracks[iTrack];
}

const bool PARAMETERS::StillTrackSpaceLeft() const
{
	return m_iNumTracks < sizeof (m_Tracks)/sizeof (m_Tracks[0]);
}

TRACK& PARAMETERS::GetTrack (int iTrack)
{
	return m_Tracks[iTrack];
}

const int PARAMETERS::GetTrackNumber(int iTrack) const
{
	return m_Tracks[iTrack].m_iTrack;
}

const LPCSTR PARAMETERS::GetTrackFileName (int iTrack) const
{
	return m_Tracks[iTrack].m_psFilename;
}

const NERO_TRACKMODE_TYPE PARAMETERS::GetTrackMode(int iTrack) const
{
	return m_Tracks[iTrack].m_Mode;
}

COMMAND_LINE_ERRORS PARAMETERS::SetTrackFileName(int iTrack, const char *psName)
{
	m_Tracks[iTrack].m_psFilename = psName;
	return CLE_NO_ERROR;
}

const int PARAMETERS::GetNumberOfTracks() const
{
	return m_iNumTracks;
}

COMMAND_LINE_ERRORS PARAMETERS::SetTrackMode(int iTrack, NERO_TRACKMODE_TYPE eType)
{
	m_Tracks[iTrack].m_Mode = eType;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::IncrementNumberOfTracks()
{
	m_iNumTracks++;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::SetTrackNumber(int iTrack, int iNumber)
{
	m_Tracks[iTrack].m_iTrack = iNumber;
	return CLE_NO_ERROR;
}

const NEROAPI_CDRW_ERASE_MODE PARAMETERS::GetEraseMode() const
{
	return m_eEraseMode;
}

COMMAND_LINE_ERRORS PARAMETERS::SetEraseMode(NEROAPI_CDRW_ERASE_MODE eMode)
{
	if (GetEraseMode() == eMode)
	{
		return CLE_MULTIPLE_COMMANDS_SPECIFIED;
	}

	m_eEraseMode = eMode;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::SetImageFileName(const char *psName)
{
	m_psImageFilename = psName;
	return CLE_NO_ERROR;
}

const LPCSTR PARAMETERS::GetImageFileName() const
{
	return m_psImageFilename;
}

COMMAND_LINE_ERRORS PARAMETERS::SetBurnType(BURNTYPE Type)
{
	// The Burn type cannot be set twice
	// BURNTYPE_ISOAUDIO is an exception to this rule.
	// However, settings for ISO/Audio and mixed more are handled
	// in SetAudioSelected and SetISOSelected directly.
	// So we do not have to worry about that here.
	// Another exception is BURNTYPE_FREESTYLE, where every
	// track can be written in a different mode.
	// So it is legal to provide that type more than once.

	if (BURNTYPE_UNKNOWN != GetBurnType())
	{
		if (BURNTYPE_FREESTYLE != GetBurnType())
		{
			// A burn type other than freestyle has been set already. 

			return CLE_BURN_TYPE_ALREADY_SPECIFIED;
		}
		else
		{
			// The burn type set before is freestyle.
			// If the new type is not BURNTYPE_FREESTYLE
			// we need to return an error.

			if (BURNTYPE_FREESTYLE != Type)
			{
				// Illegal combination of types

				return CLE_BURN_TYPE_ALREADY_SPECIFIED;
			}
		}
	}

	// Burn type has not been specified yet, so just set it

	m_BurnType = Type;
	return CLE_NO_ERROR;
}

const BURNTYPE PARAMETERS::GetBurnType() const
{
	return m_BurnType;
}

const COMMAND PARAMETERS::GetCommand() const
{
	return m_Command;
}

COMMAND_LINE_ERRORS PARAMETERS::SetCommand (COMMAND Command)
{
	if (GetCommand() == COMMAND_UNKNOWN)
	{
		m_Command = Command;
	}
	else
	{
		return CLE_MULTIPLE_COMMANDS_SPECIFIED;
	}

	return CLE_NO_ERROR;
}

const LPCSTR PARAMETERS::GetDriveName() const
{
	return m_psDriveName;
}

COMMAND_LINE_ERRORS PARAMETERS::SetDriveName (int& argc, char**& argv)
{
	argc--;
	argv++;

	if (argc <= 0)
	{
		return CLE_MISSING_DRIVE_NAME_PARAMETER;
	}

	m_psDriveName = *argv;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetUseReal() const
{
	return m_bReal;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseReal ()
{
	m_bReal = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetUseTAO() const
{
	return m_bTAO;
}

COMMAND_LINE_ERRORS PARAMETERS::SetUseTAO ()
{
	m_bTAO = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetUseUnderRunProt() const
{
	return m_bUnderRunProt;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseUnderRunProt ()
{
	m_bUnderRunProt = true;
	return CLE_NO_ERROR;
}	
	

const LPCSTR PARAMETERS::GetArtist() const
{
	return m_psArtist;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetArtist (int& argc, char**& argv)
{
	argc--;
	argv++;
	
	if (argc <= 0)
	{
		return CLE_MISSING_ARTIST_PARAMETER;
	}

	m_psArtist = *argv;
	return CLE_NO_ERROR;
}	
	

const LPCSTR PARAMETERS::GetTitle() const
{
	return m_psTitle;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetTitle (int& argc, char**& argv)
{
	argc--;
	argv++;
	
	if (argc <= 0)
	{
		return CLE_MISSING_TITLE_PARAMETER;
	}

	m_psTitle = *argv;
	return CLE_NO_ERROR;
}	
	

const bool PARAMETERS::GetAudioSelected() const
{
	return m_bAudioSelected;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetAudioSelected ()
{
	// Audio can only be used in combination with ISO

	if (BURNTYPE_UNKNOWN != GetBurnType())
	{
		if (!GetISOSelected())
		{
			return CLE_BURN_TYPE_ALREADY_SPECIFIED;
		}
	}

	m_bAudioSelected = true;
	m_BurnType = BURNTYPE_ISOAUDIO;

	return CLE_NO_ERROR;
}	

const int PARAMETERS::GetReadSpeed() const
{
	return m_iReadSpeed;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetReadSpeed (int& argc, char**& argv)
{
	argc--;
	argv++;
	
	if (argc <= 0)
	{
		return CLE_MISSING_SPEED_PARAMETER;
	}
	
	// check if conversion went right
	
	if (!ATOI (*argv, m_iReadSpeed))
	{
		return CLE_INVALID_SPEED_PARAMETER;
	}
	
	return CLE_NO_ERROR;
}	

const int PARAMETERS::GetSpeed() const
{
	return m_iSpeed;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetSpeed (int& argc, char**& argv)
{
	argc--;
	argv++;
	
	if (argc <= 0)
	{
		return CLE_MISSING_SPEED_PARAMETER;
	}

	if (GetSpeedInKbps () >= 0)
	{
		// If the speed in kbps is already specified, it is an error to
		// set the speed in X.
		// 
		return CLE_INVALID_SPEED_PARAMETER;
	}

	// check if conversion went right

	if (!ATOI (*argv, m_iSpeed))
	{
		return CLE_INVALID_SPEED_PARAMETER;
	}

	return CLE_NO_ERROR;
}	
	
const int PARAMETERS::GetSpeedInKbps() const
{
	return m_iSpeedInKbps;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetSpeedInKbps (int& argc, char**& argv)
{
	argc--;
	argv++;
	
	if (argc <= 0)
	{
		return CLE_MISSING_SPEED_PARAMETER;
	}
	
	if (GetSpeed () >= 0)
	{
		// If the speed in X is already specified, it is an error to
		// set the speed in kb/s.
		// 
		return CLE_INVALID_SPEED_PARAMETER;
	}
	
	// check if conversion went right
	
	if (!ATOI (*argv, m_iSpeedInKbps))
	{
		return CLE_INVALID_SPEED_PARAMETER;
	}
	
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetUseCDExtra() const
{
	return m_bCDExtra;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetCDExtra ()
{
	m_bCDExtra = true;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetEnableAbort() const
{
	return m_bEnableAbort;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetEnableAbort ()
{
	m_bEnableAbort = true;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetUseSpeedTest() const
{
	return m_bSpeedTest;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetSpeedTest ()
{
	m_bSpeedTest = true;
	return CLE_NO_ERROR;
}	
	

const bool PARAMETERS::GetCloseSession() const
{
	return m_bCloseSession;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetCloseSession ()
{
	m_bCloseSession = true;
	return CLE_NO_ERROR;
}	
	
const int PARAMETERS::GetSessionToImport() const
{
	return m_iSessionToImport;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetSessionToImport (int& argc, char**& argv)
{
	argc--;
	argv++;

	if (argc <= 0)
	{
		// If there are no more command line arguments, this switch was
		// supplied without a session number.
		// 
		m_iSessionToImport = -1;
	}
	else
	{
		// Check whether the argument is a number. If it is, take it as
		// a part of this switch. If not, backtrack a single position
		// in an argument list and let the parser reuse this argument.
		// 
		if (!ATOI (*argv, m_iSessionToImport))
		{
			argc++;
			argv--;
		}
	}

	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetDetectNonEmptyCDRW() const
{
	return m_bDetectNonEmptyCDRW;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetDetectNonEmptyCDRW ()
{
	m_bDetectNonEmptyCDRW = true;
	return CLE_NO_ERROR;
}	


const bool PARAMETERS::GetUseCDText() const
{
	return m_bCDText;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseCDText ()
{
	m_bCDText = true;
	return CLE_NO_ERROR;
}	
	

const bool PARAMETERS::GetUseRockridge() const
{
	return m_bUseRockridge;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseRockridge ()
{
	m_bUseRockridge = true;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetCreateIsoFs() const
{
	return m_bCreateIsoFS;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetCreateIsoFs ()
{
	m_bCreateIsoFS = true;
	return CLE_NO_ERROR;
}	


const bool PARAMETERS::GetCreateUdfFS() const
{
	return m_bCreateUdfFS;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetCreateUdfFs ()
{
	m_bCreateUdfFS = true;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetDVDVideoRealloc() const
{
	return m_bDVDVideoRealloc;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetDVDVideoRealloc ()
{
	m_bDVDVideoRealloc = true;
	return CLE_NO_ERROR;
}	

// NIITEF_IMPORT_ROCKRIDGE flag is obsolete so we commented the
// code below.
//
/*const bool PARAMETERS::GetImportRockridge() const
{
	return m_bImportRockridge;

}

COMMAND_LINE_ERRORS PARAMETERS::SetImportRockridge ()
{
	m_bImportRockridge = true;
	return CLE_NO_ERROR;
}*/

const bool PARAMETERS::GetImportUDF() const
{
	return m_bImportUDF;

}

COMMAND_LINE_ERRORS PARAMETERS::SetImportUDF ()
{
	m_bImportUDF = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetImportIsoOnly() const
{
	return m_bImportIsoOnly;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetImportIsoOnly ()
{
	m_bImportIsoOnly = true;
	return CLE_NO_ERROR;
}	
	

const bool PARAMETERS::GetPreferRockRidge() const
{
	return m_bPreferRockridge;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetPreferRockridge ()
{
	m_bPreferRockridge = true;
	return CLE_NO_ERROR;
}	


const bool PARAMETERS::GetDisableEject() const
{
	return m_bDisableEject;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetDisableEject ()
{
	m_bDisableEject = true;
	return CLE_NO_ERROR;
}	
	

const bool PARAMETERS::GetVerify() const
{
	return m_bVerify;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetVerify ()
{
	m_bVerify = true;
	return CLE_NO_ERROR;
}	
	
const bool PARAMETERS::GetISOSelected() const
{
	return m_bISOSelected;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetISOSelected (int& argc, char**& argv)
{
	// ISO can be used in combination with 
	// any other burn type except BURNTYPE_IMAGE.

	if (BURNTYPE_UNKNOWN != GetBurnType())
	{
		// If ISO has been set already return an error

		if (GetISOSelected())
		{
			return CLE_BURN_TYPE_ALREADY_SPECIFIED;
		}
		else
		{
			// The other illegal type in this case
			// is BURNTYPE_IMAGE.
			if (BURNTYPE_IMAGE == GetBurnType())
			{
				return CLE_BURN_TYPE_ALREADY_SPECIFIED;
			}
		}
	}
	else
	{
		// No burn type set before

		m_BurnType = BURNTYPE_ISOAUDIO;
	}
	
	if (argc <= 0)
	{
		return CLE_MISSING_ISO_PARAMETER;
	}

	argc--;
	argv++;
	
	COMMAND_LINE_ERRORS ecl = SetVolumeName(*argv);
	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}
	
	ecl = SetVolumeNameSupplied();
	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}

	m_bISOSelected = true;
	return CLE_NO_ERROR;
}	

const LPCSTR PARAMETERS::GetVolumeName() const
{
	return m_psVolumeName;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetVolumeName (char* psName)
{
	m_psVolumeName = psName;
	return CLE_NO_ERROR;
}	
	
const bool PARAMETERS::GetDontUseJoliet() const
{
	return m_bDontUseJoliet;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetDontUseJoliet ()
{
	m_bDontUseJoliet = true;
	return CLE_NO_ERROR;
}	
	
const bool PARAMETERS::GetUseMode2() const
{
	return m_bMode2;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseMode2 ()
{
	m_bMode2 = true;
	return CLE_NO_ERROR;
}	
	
const bool PARAMETERS::GetVolumeNameSupplied() const
{
	return m_bVolumeNameSupplied;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetVolumeNameSupplied ()
{
	m_bVolumeNameSupplied = true;
	return CLE_NO_ERROR;
}	

const bool PARAMETERS::GetUseDVD() const
{
	return m_bDVD;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseDVD ()
{
	m_bDVD = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetUseDVDHighCompatibility() const
{
	return m_bDVDHighCompatibility;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetUseDVDHighCompatibility ()
{
	m_bDVDHighCompatibility = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetRecursive() const
{
	return m_bRecursiveSearch;
}	

COMMAND_LINE_ERRORS PARAMETERS::SetRecursive()
{
	m_bRecursiveSearch = true;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::SetImageBurnType(int &argc, char **&argv)
{
	COMMAND_LINE_ERRORS ecl = SetBurnType(BURNTYPE_IMAGE);
	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}

	if (argc <= 0)
	{
		return CLE_MISSING_IMAGE_PARAMETER;
	}
	
	argc--;
	argv++;

	return SetImageFileName(*argv);
}

COMMAND_LINE_ERRORS PARAMETERS::SetFreestyleBurnType(int &argc, char **&argv)
{
	// make sure that the burn type has not been
	// specified already

	if (GetBurnType() != BURNTYPE_UNKNOWN && GetBurnType() != BURNTYPE_FREESTYLE)
	{
		return CLE_BURN_TYPE_ALREADY_SPECIFIED;
	}

	// set the track mode

	COMMAND_LINE_ERRORS ecl;

	if (!stricmp (*argv, "--freestyle_mode1"))
	{
		ecl = SetTrackMode(GetNumberOfTracks(), NERO_TRACKMODE_MODE1);
	}
	else if (!stricmp (*argv, "--freestyle_mode2"))
	{
		ecl = SetTrackMode(GetNumberOfTracks(), NERO_TRACKMODE_MODE2_FORM1);
	}
	else if (!stricmp (*argv, "--freestyle_audio"))
	{
		ecl = SetTrackMode(GetNumberOfTracks(), NERO_TRACKMODE_AUDIO);
	}

	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}

	// the file name must be specified after the track mode

	if (argc <= 0)
	{
		return CLE_MISSING_IMAGE_PARAMETER;
	}

	// make sure that we can add another track

	if (!StillTrackSpaceLeft())
	{
		return CLE_MAXIMUM_NUMBER_OF_TRACKS_REACHED;
	}

	// Get the track filename
	
	argc--;
	argv++;

	ecl = SetTrackFileName(GetNumberOfTracks(), *argv);
	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}

	ecl = IncrementNumberOfTracks();
	if (CLE_NO_ERROR != ecl)
	{
		return ecl;
	}

	// finally, set the burn type

	return SetBurnType(BURNTYPE_FREESTYLE);
}

COMMAND_LINE_ERRORS PARAMETERS::AddAudioReadTrack(int &argc, char **&argv)
{
	bool bOK = false;

	if (strlen (*argv) <= 4 &&
		'0' <= (*argv)[2] && (*argv)[2] <= '9' &&
		'0' <= (*argv)[3] && (*argv)[3] <= '9')
	{
		if (!StillTrackSpaceLeft())
		{
			return CLE_MAXIMUM_NUMBER_OF_TRACKS_REACHED;
		}

		int iTrackNumber;

		if (!ATOI (&(*argv)[2], iTrackNumber))
		{
			return CLE_INVALID_PARAMETER;
		}

		COMMAND_LINE_ERRORS ecl = SetTrackNumber(GetNumberOfTracks(), iTrackNumber);
		
		if (GetTrackNumber(GetNumberOfTracks()) > 0)
		{
			if (argc <= 0)
			{
				return CLE_MISSING_TRACK_PARAMETER;
			}

			argc--;
			argv++;

			ecl = SetTrackFileName(GetNumberOfTracks(), *argv);
			if (CLE_NO_ERROR != ecl)
			{
				return ecl;
			}
			ecl = IncrementNumberOfTracks();
			if (CLE_NO_ERROR != ecl)
			{
				return ecl;
			}
			bOK = true;
		}
	}

	if (!bOK)
	{
		return CLE_INVALID_PARAMETER;
	}

	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::AddAudioIsoFreestyleWriteTrack(int &argc, char **&argv)
{
	if (!GetVolumeNameSupplied() && GetBurnType() != BURNTYPE_FREESTYLE)
	{
		// If volume name was not yet supplied, the parameter is an audio file.

		if (!StillTrackSpaceLeft())
		{
			return CLE_MAXIMUM_NUMBER_OF_TRACKS_REACHED;
		}

		COMMAND_LINE_ERRORS ecl = SetTrackFileName(GetNumberOfTracks(), *argv);
		if (CLE_NO_ERROR != ecl)
		{
			return ecl;
		}

		ecl = IncrementNumberOfTracks();
		if (CLE_NO_ERROR != ecl)
		{
			return ecl;
		}
	}
	else
	{
		// This is a data file so simply add it to the back of the array.

		GetFileList().Add (*argv);
	}

	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetNeroLogTimestamp() const
{
	return m_bNeroLogTimestamp;
}

COMMAND_LINE_ERRORS PARAMETERS::SetNeroLogTimestamp()
{
	m_bNeroLogTimestamp = true;
	return CLE_NO_ERROR;
}

COMMAND_LINE_ERRORS PARAMETERS::SetForceEraseCDRW()
{
	m_bForceEraseCDRW = true;
	return CLE_NO_ERROR;
}

const bool PARAMETERS::GetForceEraseCDRW() const
{
	return m_bForceEraseCDRW;
}

COMMAND_LINE_ERRORS PARAMETERS::SetTempPath (int& argc, char**& argv)
{
	if (argc <= 0)
	{
		return CLE_MISSING_TEMP_PATH_PARAMETER;
	}

	argc--;
	argv++;

	m_psTempPath = *argv;
	return CLE_NO_ERROR;
}

const LPCSTR PARAMETERS::GetTempPath () const
{
	return m_psTempPath;
}

const NERO_MEDIA_SET PARAMETERS::GetMediaType() const
{
	return m_MediaSet;
}

void ParseMediaTypeArgument (CSimpleStringArray & ssa, LPCSTR psArg)
{
	// A plus sign is a separator between media constants.
	// 
	for (;;)
	{
		LPCSTR psPlus = strchr (psArg, '+');
		if (psPlus == NULL)
		{
			// No more plus signs found. This is the last media constant.
			// 
			LPSTR psMediaType = new char [strlen (psArg) + 1];
			strcpy (psMediaType, psArg);
			ssa.Add (psMediaType);

			// We have reached the end. Break the endless for loop.
			// 
			break;
		}
		else
		{
			// We found a plus sign so there are more constants.
			// 
			LPSTR psMediaType = new char [psPlus - psArg + 1];
			strncpy (psMediaType, psArg, psPlus - psArg);
			psMediaType[psPlus - psArg] = 0;
			ssa.Add (psMediaType);

			// Advance the pointer to the position beyond a plus sign.
			// 
			psArg = psPlus + 1;
		}
	}
}

COMMAND_LINE_ERRORS PARAMETERS::SetMediaType(int& argc, char**& argv)
{
	if (argc <= 0)
	{
		return CLE_MISSING_MEDIA_TYPE_PARAMETER;
	}
	
	argc--;
	argv++;

	CSimpleStringArray ssa;
	ParseMediaTypeArgument (ssa, *argv);

	m_MediaSet = 0;

	for (int i = 0; i < ssa.vect.size (); i ++)
	{
		LPCSTR psMediaType = ssa.vect[i];

		if (0 == stricmp (psMediaType, "media_cd"))
		{
			m_MediaSet |= MEDIA_CD;
		}
		else if (0 == stricmp (psMediaType, "media_ddcd"))
		{
			m_MediaSet |= MEDIA_DDCD;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_m"))
		{
			m_MediaSet |= MEDIA_DVD_M;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_p"))
		{
			m_MediaSet |= MEDIA_DVD_P;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_any"))
		{
			m_MediaSet |= MEDIA_DVD_ANY;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_ram"))
		{
			m_MediaSet |= MEDIA_DVD_RAM;
		}
		else if (0 == stricmp (psMediaType, "media_ml"))
		{
			m_MediaSet |= MEDIA_ML;
		}
		else if (0 == stricmp (psMediaType, "media_mrw"))
		{
			m_MediaSet |= MEDIA_MRW;
		}
		else if (0 == stricmp (psMediaType, "media_no_cdr"))
		{
			m_MediaSet |= MEDIA_NO_CDR;
		}
		else if (0 == stricmp (psMediaType, "media_no_cdrw"))
		{
			m_MediaSet |= MEDIA_NO_CDRW;
		}
		else if (0 == stricmp (psMediaType, "media_cdrw"))
		{
			m_MediaSet |= MEDIA_CDRW;
		}
		else if (0 == stricmp (psMediaType, "media_cdr"))
		{
			m_MediaSet |= MEDIA_CDR;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_rom"))
		{
			m_MediaSet |= MEDIA_DVD_ROM;
		}
		else if (0 == stricmp (psMediaType, "media_cdrom"))
		{
			m_MediaSet |= MEDIA_CDROM;
		}
		else if (0 == stricmp (psMediaType, "media_no_dvd_m_rw"))
		{
			m_MediaSet |= MEDIA_NO_DVD_M_RW;
		}
		else if (0 == stricmp (psMediaType, "media_no_dvd_m_r"))
		{
			m_MediaSet |= MEDIA_NO_DVD_M_R;
		}
		else if (0 == stricmp (psMediaType, "media_no_dvd_p_rw"))
		{
			m_MediaSet |= MEDIA_NO_DVD_P_RW;
		}
		else if (0 == stricmp (psMediaType, "media_no_dvd_p_r"))
		{
			m_MediaSet |= MEDIA_NO_DVD_P_R;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_m_r"))
		{
			m_MediaSet |= MEDIA_DVD_M_R;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_m_rw"))
		{
			m_MediaSet |= MEDIA_DVD_M_RW;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_p_r"))
		{
			m_MediaSet |= MEDIA_DVD_P_R;
		}
		else if (0 == stricmp (psMediaType, "media_dvd_p_rw"))
		{
			m_MediaSet |= MEDIA_DVD_P_RW;
		}
		else if (0 == stricmp (psMediaType, "media_fpacket"))
		{
			m_MediaSet |= MEDIA_FPACKET;
		}
		else if (0 == stricmp (psMediaType, "media_vpacket"))
		{
			m_MediaSet |= MEDIA_VPACKET;
		}
		else if (0 == stricmp (psMediaType, "media_packetw"))
		{
			m_MediaSet |= MEDIA_PACKETW;
		}
	}
	
	return CLE_NO_ERROR;
}

bool PARAMETERS::ATOI (LPCSTR psString, int & iVal)
{
	char * pchStopChar;
	
	iVal = strtol (psString, &pchStopChar, 10);
	
	// C run-time function "strtol" sets internal error to non-null
	// if error occurs on conversion. This error value is retrieved by
	// accessing errno global variable. We will also consider it an error
	// if the stop char is not the actual end of string.
	// 
	return errno == 0 && *pchStopChar == '\0';
}

int PARAMETERS::GetSpeedToNeroBurn (void) const
{
	int iSpeed;
	
	// There are two variants of specifying the burning speed. One is
	// to specify it in X and the other in kb/s. If speed in kb/s is
	// used, a flag NBF_SPEED_IN_KBS must be used to NeroBurn().
	// GetBurnFlags() function will take care of that.
	// 
	if (GetSpeedInKbps () >= 0)
	{
		// If speed is specified as kb/s, the use this setting.
		// 
		iSpeed = GetSpeedInKbps ();
	}
	else if (GetSpeed () >= 0)
	{
		// If the speed is specified in X, the use this setting.
		//
		iSpeed = GetSpeed ();
	}
	else
	{
		// If none is specified, use the default speed of 0. NeroAPI
		// will choose the appropriate speed.
		// 
		iSpeed = 0;
	}

	return iSpeed;
}
