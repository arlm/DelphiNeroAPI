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
|* PROGRAM: BurnContext.cpp
|*
|* PURPOSE: Central class for CD operations; implementation file
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"

CBurnContextProgress::CBurnContextProgress ()
{
	if (m_pNeroProgress != NULL)
	{
		m_pNeroProgress->npAbortedCallback = CBurnContext::AbortedCallback;
		m_pNeroProgress->npAddLogLineCallback = CBurnContext::AddLogLine;
		m_pNeroProgress->npDisableAbortCallback = CBurnContext::DisableAbortCallback;
		m_pNeroProgress->npProgressCallback = CBurnContext::ProgressCallback;
		m_pNeroProgress->npSetMajorPhaseCallback = CBurnContext::SetMajorPhaseCallback;
		m_pNeroProgress->npSetPhaseCallback = CBurnContext::SetPhaseCallback;
		m_pNeroProgress->npSubTaskProgressCallback = NULL;	// Write buffer fill level callback (we don't use this as it is complicated to visualize)
		m_pNeroProgress->npUserData = &CBurnContext::s_NeroSettings;
	}
}


// NERO_SETTINGS is needed when calling NeroInit()

NERO_SETTINGS CBurnContext::s_NeroSettings =
{
	NULL,
	"ahead", "Nero - Burning Rom",
	"Nero.txt",
	{IdleCallback, &s_NeroSettings},
	{UserDialog, &s_NeroSettings}
};

CBurnContext::~CBurnContext ()
{
	// Let the NeroAPI perform the required cleanup

	if (m_bNeroInitialized)
	{
		NeroCloseDevice (m_NeroDeviceHandle);
		NeroFreeMem (m_NeroDeviceInfos);
		NeroFreeMem (m_NeroCDInfo);
		NeroFreeCDStamp (m_pCDStamp);
		NeroClearErrors ();
	}

	// NeroDone needs to be called before closing the DLL.
	// This is necessary because some clean-up actions like
	// stopping threads cannot be done in the close function of the DLL

	if (NeroDone ())
	{
		// If return value is TRUE, some memory leaks were detected.
		// 
	}

	NeroAPIGlueDone();
}


CExitCode CBurnContext::GetAvailableDrives (const PARAMETERS & params)
{
	// Make sure that NeroGetAvailableDrives has not been called before to prevent multiple 
	// allocation of memory for NERO_SCSI_DEVICE_INFOS.

	_ASSERTE (NULL == m_NeroDeviceInfos);

	// NeroGetAvailableDrives returns a list of available WORM and CDROM devices.
	// The memory allocated for NERO_SCSI_DEVICE_INFOS must be freed with NeroFreeMem().
	// This function returns NULL for errors 

	m_NeroDeviceInfos = NeroGetAvailableDrivesEx ((NERO_MEDIA_TYPE) params.GetMediaType (), NULL);

	return (NULL == m_NeroDeviceInfos)? EXITCODE_ERROR_OBTAINING_AVAILABLE_DRIVES: EXITCODE_OK;
}

// Opens the NeroCMD error log

bool CBurnContext::OpenLogFile (LPCSTR psLogFilename)
{
	// We use the CErrorLog class.
	// Open returns true if the error log could be opened.

	return m_ErrorLog.Open (psLogFilename);
}


CExitCode CBurnContext::NeroLoad (void)
{
	// Initialize NeroAPI.

	if (! NeroAPIGlueConnect (NULL))
	{
		return EXITCODE_NEROAPI_DLL_NOT_FOUND;
	}

	// Set the flag.

	m_bNeroInitialized = true;

	return EXITCODE_OK;
}


// This function queries the registry for serial number and initializes
// the NeroAPI.

CExitCode CBurnContext::InitNeroAPI (void)
{
	// Provide the this-pointer for the UserDialog callback

	s_NeroSettings.nstUserDialog.ncCallbackFunction = UserDialog;
	s_NeroSettings.nstUserDialog.ncUserData = this;

	// Do the actual initialization and map the return value
	// into our EXITCODE.

	switch (NeroInit (&s_NeroSettings, NULL))
	{
		case NEROAPI_INIT_OK:
			return EXITCODE_OK;
		
		case NEROAPI_INIT_INVALID_SERIAL_NUM:
			return EXITCODE_BAD_SERIAL_NUMBER;

		case NEROAPI_INIT_DEMOVERSION_EXPIRED:
			return EXITCODE_DEMOVERSION_EXPIRED;
		
		case NEROAPI_INIT_ALREADY_INITIALISED:
		case NEROAPI_INIT_CANNOT_LOCK:
		case NEROAPI_INIT_UNSPECIFIED_ERROR:
		case NEROAPI_INIT_INVALID_ARGS:
		default:
			return EXITCODE_INTERNAL_ERROR;
	}
}


// OpenDevice checks if params.m_psDriveName has a matching
// drive in the list of availabe drives and opens it.

CExitCode CBurnContext::OpenDevice (const PARAMETERS & params)
{
	if (NULL == params.GetDriveName())
	{
		// To open a device we must have its name or drive letter.

		return EXITCODE_MISSING_DRIVENAME;
	}

	// Call the support function that enumerates the drives and finds
	// the requested drive according to the supplied command line
	// parameters.
	//
	int iDriveIndex = LookForADrive (params);

	// If the drive is found (a positive response), try and open it.
	//
	if (iDriveIndex >= 0)
	{
		m_NeroDeviceHandle = NeroOpenDevice (&m_NeroDeviceInfos->nsdisDevInfos[iDriveIndex]);
		if (NULL == m_NeroDeviceHandle) 
		{
			return EXITCODE_ERROR_OPENNING_DRIVE;
		}
	}
	
	// Output a list of available drives and return
	// an error if the requested device could not be found

	if (NULL == m_NeroDeviceHandle)
	{
		printf ("Drive '%s' not found, available are:\n", params.GetDriveName());
		CommandListDrives (params);
		
		return EXITCODE_DRIVE_NOT_FOUND;
	}
	
	return EXITCODE_OK;
}


// This function sets the appropriate burn flags according to the user
// supplied parameters.

DWORD CBurnContext::GetBurnFlags (const PARAMETERS & params)
{
	DWORD dwFlags;

	// Simulation or real mode

	dwFlags = (params.GetUseReal ())? NBF_WRITE : NBF_SIMULATE;

	// DAO (Disc At Once) or TAO (Track At Once)
	// TAO is default

	dwFlags |= (params.GetUseTAO ())? 0 : NBF_DAO;

	// Disable Abort
	// The disable abort callback will be called.

	dwFlags |= (params.GetEnableAbort ())? 0: NBF_DISABLE_ABORT;

	// Perform source speed test first

	dwFlags |= (params.GetUseSpeedTest ())? NBF_SPEED_TEST : 0;

	// Close session after write, not the whole disc

	dwFlags |= (params.GetCloseSession ())? NBF_CLOSE_SESSION: 0;

	// Buffer underrun protection for safer burning

	dwFlags |= (params.GetUseUnderRunProt ()) ? NBF_BUF_UNDERRUN_PROT: 0;

	// Detect non-empty CDRW
	// The DLG_NON_EMPTY_CDRW user callback will be called when trying
	// to burn onto a non empty CDRW

	dwFlags |= (params.GetDetectNonEmptyCDRW ())? NBF_DETECT_NON_EMPTY_CDRW: 0;

	// Enable CD text writing.
	// Will be ignored if the drive does not support this feature

	dwFlags |= (params.GetUseCDText ())? NBF_CD_TEXT: 0;

	// Do not eject CD at the end of the burn process

	dwFlags |= (params.GetDisableEject ())? NBF_DISABLE_EJECT: 0;

	// Verify Filesystem after writing. Works for ISO only
	
	dwFlags |= (params.GetVerify ())? NBF_VERIFY: 0;

	// The speed passed to NeroBurn() is specified in kb/s instead of
	// the usual X.

	dwFlags |= (params.GetSpeedInKbps () >= 0)? NBF_SPEED_IN_KBS: 0;

	// If dvd is burned and a high compatibility mode is specified, this
	// flag is used.

	dwFlags |= (params.GetUseDVDHighCompatibility ())? NBF_DVDP_BURN_30MM_AT_LEAST: 0;

	dwFlags |= (params.GetJapaneseCDText ())? NBF_CD_TEXT_IS_JAPANESE: 0;
	dwFlags |= (params.GetBooktypeDVDROM ())? NBF_BOOKTYPE_DVDROM: 0;

	return dwFlags;
}

// This function is called to exit with a specific error code.

EXITCODE CBurnContext::Exit(CExitCode code)
{
	if (code != EXITCODE_OK)
	{
		printf ("\n%s\n", code.GetTextualExitCode ());

		LPCSTR psNeroAPIError = code.GetLastError ();

		// If the first char is non-null, the string is non-empty
		// and we should print it. Otherwise, it looks silly.
		// 
		if (psNeroAPIError[0] != 0)
		{
			printf("NeroAPI reports: %s.\n", psNeroAPIError);
		}
	}

	return code;
}

CBurnContext::CBurnContext(PARAMETERS* params)
{
	// A PARAMETERS reference is required for 
	// the UserDialog callback.

	m_params = params;

	m_NeroDeviceHandle = NULL;
	m_NeroDeviceInfos = NULL;
	m_pCDStamp = NULL;
	m_NeroCDInfo = NULL;
	m_bNeroInitialized = false;
	m_bPrintUserInteractionErrorMessage = false;
	
	// Set Ctrl+C handler.
	
	SetConsoleCtrlHandler (CtrlHandler, TRUE);
}

// This function prints error log lines
// that are passed from outside the CBurnContext class

void CBurnContext::PrintLogLine(LPCSTR s)
{
	
	m_ErrorLog.printf ("%s\n", s);
}

// This function rids the string from spaces from the right.
// 
void CBurnContext::TrimStringRight (LPSTR psString)
{
	// Loop from the last string character to the first until the first
	// non-space character is encountered.
	// 
	for (LPSTR p = psString + strlen (psString) - 1;
		psString <= p && *p == ' ';
		p --)
	{
		*p = '\0';
	}
}

// This is a support function that enumerates drives and finds the one
// according to the specified command line parameters.
// 
int CBurnContext::LookForADrive (const PARAMETERS & params)
{
	int i;
	LPSTR psTrimmedDriveName = (LPSTR) _alloca (strlen (params.GetDriveName ()) + 1);
	
	strcpy (psTrimmedDriveName, params.GetDriveName ());
	TrimStringRight (psTrimmedDriveName);

	for (i = 0; i < (int)(m_NeroDeviceInfos->nsdisNumDevInfos); i++) 
	{
		NERO_SCSI_DEVICE_INFO nsdiShort = m_NeroDeviceInfos->nsdisDevInfos[i];
		
		// Check if the full device name has been supplied.
        // stricmp performs a lowercase comparison and returns 0 if the strings are identical.
		
		LPSTR psTrimmedDeviceName = (LPSTR) _alloca (strlen (nsdiShort.nsdiDeviceName) + 1);
		strcpy (psTrimmedDeviceName, nsdiShort.nsdiDeviceName);
		TrimStringRight(psTrimmedDeviceName);

		bool bFoundDeviceName = false;
		if (0 == stricmp (psTrimmedDriveName, psTrimmedDeviceName))
		{
			bFoundDeviceName = true;
		}
		
		// Check if the user supplied drive name is only one character long
		// and see if it matches the drive letter
		
		bool bFoundDriveName = false;
		if (1 == strlen(params.GetDriveName()))
		{
			if (toupper(params.GetDriveName()[0]) == toupper(nsdiShort.nsdiDriveLetter))
			{
				bFoundDriveName = true;
			}
		}
		
		// If either a device name or drive name was found try to open the device
		
		if (bFoundDeviceName || bFoundDriveName)
		{
			// We successfully found the wanted drive. Return the index.

			return i;
		}
	}

	return -1;
}

void CBurnContext::PrintUserInteractionMessage (void)
{
	if (m_bPrintUserInteractionErrorMessage)
	{
		m_bPrintUserInteractionErrorMessage = false;
		printf ("\nERROR: The operation cannot be performed without user interaction!\n");
	}
}
