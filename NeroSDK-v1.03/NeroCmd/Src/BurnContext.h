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
|* PROGRAM: BurnContext.h
|*
|* PURPOSE: Central class for CD operations
******************************************************************************/


#ifndef _BURN_CONTEXT_H_
#define _BURN_CONTEXT_H_


#include "ExitCode.h"
#include "getopt.h"
#include "ErrorLog.h"
#include "parameters.h"	// Added by ClassView
#include "NeroProgress.h"

class CBurnContextProgress : public CNeroProgress
{
public:
	CBurnContextProgress ();
};


class CBurnContext
{
	friend CBurnContextProgress;

protected:
	static bool s_bAborted;
	NERO_DEVICEHANDLE m_NeroDeviceHandle;
	NERO_SCSI_DEVICE_INFOS * m_NeroDeviceInfos;
	NERO_CD_INFO * m_NeroCDInfo;
	void * m_pCDStamp;
	bool m_bNeroInitialized;
	CErrorLog m_ErrorLog;
	bool m_bPrintUserInteractionErrorMessage;
	
	static NERO_SETTINGS s_NeroSettings;

public:
	void PrintUserInteractionMessage (void);
	void PrintLogLine(LPCSTR s);
	EXITCODE Exit (CExitCode code);
	CBurnContext(PARAMETERS* params);
	~CBurnContext ();

	CExitCode WriteImage (const PARAMETERS & params);
	CExitCode OpenDevice (const PARAMETERS & params);
	CExitCode NeroLoad (void);
	CExitCode InitNeroAPI (void);
	CExitCode GetAvailableDrives (const PARAMETERS & params);
	void WriteNeroErrorLog (const PARAMETERS & params);
	bool OpenLogFile (LPCSTR psLogFilename);

	CExitCode WriteIsoAudio (const PARAMETERS & params);
	CExitCode WriteVideoCD (const PARAMETERS & params);
	CExitCode WriteFreestyle (const PARAMETERS & params);
	CExitCode CommandErase (const PARAMETERS & params);
	CExitCode CommandListDrives (const PARAMETERS & params);
	CExitCode CommandCDInfo (const PARAMETERS & params);
	CExitCode CommandImageInfo (const PARAMETERS & params);
	CExitCode CommandRead (const PARAMETERS & params);
	CExitCode CommandWrite (const PARAMETERS & params);
	CExitCode CommandEject (const PARAMETERS & params);
	CExitCode CommandDriveInfo (const PARAMETERS & params);
	CExitCode CommandInternal (const PARAMETERS & params);
	CExitCode CommandListFormats (const PARAMETERS & params);
	CExitCode CommandGetSpeeds (const PARAMETERS & params);
	void CommandVersion (void);

protected:
	void DebugPrintIsoTrack (const NERO_ISO_ITEM * pItem, int iLevel = 0);
	void TrimStringRight (LPSTR psString);
	void DecodeSpeeds (const NERO_SPEED_INFOS & nsi);
	void DecodeDeviceType (const NERO_SCSI_DEVICE_INFO * pNSDI) const;
	void DecodeCapabilities (const NERO_SCSI_DEVICE_INFO * pNSDI) const;
	int LookForADrive (const PARAMETERS & params);
	CExitCode TranslateNeroToExitCode (NEROAPI_BURN_ERROR err);
	DWORD GetBurnFlags (const PARAMETERS & params);
	CExitCode GetIsoTrack (const PARAMETERS & params, CNeroIsoTrack ** ppIsoTrack, NERO_ISO_ITEM ** ppItem);
	void DeleteIsoItemTree (NERO_ISO_ITEM * pItem);
	void FreeOurOwnResources (NERO_ISO_ITEM * pItem);
	CExitCode CreateIsoTree (const PARAMETERS & params, LPCSTR psFilename, NERO_ISO_ITEM ** ppItem, int iLevel = 0);
	void StoreFileName (char (& shortFilename) [252], char * psLongFilename, LPCSTR psFilename);
	CExitCode DisplayCDInfo (void);

	static BOOL WINAPI CtrlHandler (DWORD dwCtrlType);
	static BOOL NERO_CALLBACK_ATTR IdleCallback (void *pUserData);
	static NeroUserDlgInOut NERO_CALLBACK_ATTR UserDialog (void * pUserData, NeroUserDlgInOut type, void *data);
	static BOOL NERO_CALLBACK_ATTR ProgressCallback (void *pUserData, DWORD dwProgressInPercent);
	static BOOL NERO_CALLBACK_ATTR AbortedCallback (void *pUserData);
	static void NERO_CALLBACK_ATTR AddLogLine (void *pUserData, NERO_TEXT_TYPE type, const char *text);
	static void NERO_CALLBACK_ATTR SetPhaseCallback (void *pUserData, const char *text);
	static void NERO_CALLBACK_ATTR SetMajorPhaseCallback (void *pUserData, NERO_MAJOR_PHASE phase, void * reserved);
	static void NERO_CALLBACK_ATTR DisableAbortCallback (void *pUserData, BOOL enableAbort);
	static DWORD NERO_CALLBACK_ATTR WriteIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen);
	static BOOL NERO_CALLBACK_ATTR EOFCallback (void *pUserData);
	static BOOL NERO_CALLBACK_ATTR ErrorCallback (void *pUserData);
	static DWORD NERO_CALLBACK_ATTR ReadIOCallback (void *pUserData, BYTE *pBuffer, DWORD dwLen);
private:
	const PARAMETERS* m_params;
};


#endif
