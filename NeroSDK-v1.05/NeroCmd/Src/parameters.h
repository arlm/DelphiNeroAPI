/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: parameters.h
|*
|* PURPOSE: PARAMETERS class declaration, COMMAND_LINE_ERRORS enumeration
|*          enumerations for available burn types and commands; structure
|*          for storing a track list.
******************************************************************************/


#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_


#include "SimpleStringArray.h"
#include "NeroAPIGlue.h"


// These are errors that happen when command line arguments are parsed.

enum COMMAND_LINE_ERRORS {
	CLE_NO_ERROR = 0,
	CLE_MULTIPLE_COMMANDS_SPECIFIED,
	CLE_MISSING_DRIVE_NAME_PARAMETER,
	CLE_MISSING_ARTIST_PARAMETER,
	CLE_MISSING_TITLE_PARAMETER,
	CLE_MISSING_SPEED_PARAMETER,
	CLE_INVALID_SPEED_PARAMETER,
	CLE_MISSING_ISO_PARAMETER,
	CLE_INVALID_PARAMETER,
	CLE_BURN_TYPE_ALREADY_SPECIFIED,
	CLE_MISSING_TRACK_PARAMETER,
	CLE_MAXIMUM_NUMBER_OF_TRACKS_REACHED,
	CLE_PARAMETER_FILE_ALREADY_PROCESSED,
	CLE_MISSING_IMAGE_PARAMETER,
	CLE_MISSING_ERROR_LOG_PARAMETER,
	CLE_MISSING_IMPORT_PARAMETER,
	CLE_INVALID_IMPORT_PARAMETER,
	CLE_NEED_TRACKS,
	CLE_BURN_TYPE_NOT_SPECIFIED,
	CLE_NO_COMMAND_SPECIFIED,
	CLE_MISSING_TEMP_PATH_PARAMETER,
	CLE_MISSING_MEDIA_TYPE_PARAMETER,
	CLE_MISSING_OUTPUT_IMAGE_FILENAME_PARAMETER,
	CLE_MISSING_IMAGE_INFO_FILENAME_PARAMETER,
	CLE_MISSING_SYSTEM_IDENTIFIER_PARAMETER,
	CLE_MISSING_VOLUME_SET_PARAMETER,
	CLE_MISSING_PUBLISHER_PARAMETER,
	CLE_MISSING_DATA_PREPARER_PARAMETER,
	CLE_MISSING_APPLICATION_PARAMETER,
	CLE_MISSING_COPYRIGHT_PARAMETER,
	CLE_MISSING_ABSTRACT_PARAMETER,
	CLE_MISSING_BIBLIOGRAPHIC_PARAMETER,
	CLE_MISSING_VIDEO_RESOLUTION_PARAMETER,
	CLE_BAD_VIDEO_RESOLUTION_PARAMETER,
	CLE_MAX
};


// Enumeration of available commands

enum COMMAND {
	COMMAND_UNKNOWN = 0,
	COMMAND_LISTDRIVES,
	COMMAND_READ,
	COMMAND_WRITE,
	COMMAND_CDINFO,
	COMMAND_ERASE,
	COMMAND_EJECT,
	COMMAND_LOAD,
	COMMAND_VERSION,
	COMMAND_DRIVE_INFO,
	COMMAND_INTERNAL,
	COMMAND_LISTFORMATS,
	COMMAND_GET_SPEEDS,
	COMMAND_IMAGE_INFO,
	COMMAND_ESTIMATE,
};


// Enumeration of available CD formats

enum BURNTYPE {
	BURNTYPE_UNKNOWN = 0,
	BURNTYPE_ISOAUDIO,
	BURNTYPE_VIDEOCD,
	BURNTYPE_SVIDEOCD,
	BURNTYPE_IMAGE,
	BURNTYPE_FREESTYLE,
};


// Track structure

struct TRACK {
	int m_iTrack;
	LPCSTR m_psFilename;
	NERO_TRACKMODE_TYPE m_Mode;
};


class PARAMETERS {

public:
	PARAMETERS ();
	~PARAMETERS () {}

private:
	bool m_bForceEraseCDRW;
	bool m_bNeroLogTimestamp;
	COMMAND m_Command;
	LPCSTR m_psDriveName;
	bool m_bReal;
	bool m_bTAO;
	bool m_bUnderRunProt;
	LPCSTR m_psArtist;
	LPCSTR m_psTitle;
	int m_iReadSpeed;
	int m_iSpeed;
	int m_iSpeedInKbps;
	bool m_bCDExtra;
	bool m_bEnableAbort;
	bool m_bSpeedTest;
	bool m_bCloseSession;
	int m_iSessionToImport;
	bool m_bImportSession;
	bool m_bDetectNonEmptyCDRW;
	bool m_bCDText;
	bool m_bUseRockridge;
	bool m_bCreateIsoFS;
	bool m_bCreateUdfFS;
	bool m_bDVDVideoRealloc;
	bool m_bDVDVideoCmpt;
//	bool m_bImportRockridge;		// Not used any more.
	bool m_bImportIsoOnly;
	bool m_bImportUDF;
	bool m_bImportVMSSession;
	bool m_bPreferRockridge;
	bool m_bDisableEject;
	bool m_bVerify;
	bool m_bAudioSelected;
	bool m_bISOSelected;
	LPCSTR m_psVolumeName;
	bool m_bDontUseJoliet;
	bool m_bMode2;
	bool m_bVolumeNameSupplied;
	bool m_bDVD;
	bool m_bDVDHighCompatibility;
	BURNTYPE m_BurnType;
	LPCSTR m_psImageFilename;
	NEROAPI_CDRW_ERASE_MODE m_eEraseMode;
	int m_iNumTracks;
	TRACK m_Tracks[99];
	bool m_bWriteNeroErrorLog;
	LPCSTR m_psErrorLogFilename;
	CSimpleStringArray m_FileList;
	bool m_bProcessedParameterFile;
	LPCSTR m_psTempPath;
	bool m_bRecursiveSearch;
	NERO_MEDIA_SET m_MediaSet;
	bool m_bUserInteraction;
	LPCSTR m_psOutputImageFilename;
	bool m_bUseAllSpace;
	bool m_bRelaxJoliet;
	bool m_bJapaneseCDText;
	bool m_bBooktypeDVDROM;
	bool m_bNoBooktypeChange;
	bool m_bDisableEjectAfterErase;
	bool m_bForceEjectAfterErase;
	LPCSTR m_psImageInfoFilename;

	// cite-args
	LPCSTR m_psSystemIdentifier;
	LPCSTR m_psVolumeSet;
	LPCSTR m_psPublisher;
	LPCSTR m_psDataPreparer;
	LPCSTR m_psApplication;
	LPCSTR m_psCopyright;
	LPCSTR m_psAbstract;
	LPCSTR m_psBibliographic;
	
	bool m_bBackup;

	NERO_VIDEO_RESOLUTION m_VideoResolution;

	bool m_bEstimateFSOverhead;
	bool m_bEstimateData;
	bool m_bEstimateExactSize;

	const TRACK GetTrack (int iTrack) const;
	TRACK& GetTrack (int iTrack);

public:
	const bool GetForceEraseCDRW() const;
	COMMAND_LINE_ERRORS SetForceEraseCDRW();
	COMMAND_LINE_ERRORS SetNeroLogTimestamp();
	const bool GetNeroLogTimestamp() const;
	COMMAND_LINE_ERRORS AddAudioIsoFreestyleWriteTrack(int& argc, char**& argv);
	COMMAND_LINE_ERRORS AddAudioReadTrack(int& argc, char**& argv);
	COMMAND_LINE_ERRORS SetFreestyleBurnType(int& argc, char**& argv);

	COMMAND_LINE_ERRORS SetImageBurnType(int& argc, char**& argv);

	// Access functions

	const COMMAND GetCommand() const;
	COMMAND_LINE_ERRORS SetCommand (COMMAND Command);

	const LPCSTR GetDriveName() const;
	COMMAND_LINE_ERRORS SetDriveName (int& argc, char**& argv);	

	const bool GetUserInteraction () const;
	COMMAND_LINE_ERRORS SetNoUserInteraction ();

	const bool GetUseReal() const;
	COMMAND_LINE_ERRORS SetUseReal ();	

	const bool GetUseTAO() const;
	COMMAND_LINE_ERRORS SetUseTAO ();	

	const bool GetUseUnderRunProt() const;
	COMMAND_LINE_ERRORS SetUseUnderRunProt ();	

	const LPCSTR GetArtist() const;
	COMMAND_LINE_ERRORS SetArtist (int& argc, char**& argv);	

	const LPCSTR GetTitle() const;
	COMMAND_LINE_ERRORS SetTitle (int& argc, char**& argv);	

	const bool GetAudioSelected() const;
	COMMAND_LINE_ERRORS SetAudioSelected ();	

	const int GetReadSpeed() const;
	COMMAND_LINE_ERRORS SetReadSpeed (int& argc, char**& argv);	

	const int GetSpeed() const;
	COMMAND_LINE_ERRORS SetSpeed (int& argc, char**& argv);	

	const int GetSpeedInKbps() const;
	COMMAND_LINE_ERRORS SetSpeedInKbps (int& argc, char**& argv);	

	const bool GetUseCDExtra() const;
	COMMAND_LINE_ERRORS SetCDExtra ();	

	const bool GetEnableAbort() const;
	COMMAND_LINE_ERRORS SetEnableAbort ();	

	const bool GetUseSpeedTest() const;
	COMMAND_LINE_ERRORS SetSpeedTest ();	

	const bool GetCloseSession() const;
	COMMAND_LINE_ERRORS SetCloseSession ();	

	const int GetSessionToImport() const;
	COMMAND_LINE_ERRORS SetSessionToImport (int& argc, char**& argv);	
	const int GetDoImportSession() const;

	const bool GetDetectNonEmptyCDRW() const;
	COMMAND_LINE_ERRORS SetDetectNonEmptyCDRW ();	

	const bool GetUseCDText() const;
	COMMAND_LINE_ERRORS SetUseCDText ();	

	const bool GetUseRockridge() const;
	COMMAND_LINE_ERRORS SetUseRockridge ();	

	const bool GetCreateIsoFs() const;
	COMMAND_LINE_ERRORS SetCreateIsoFs ();	

	const bool GetCreateUdfFS() const;
	COMMAND_LINE_ERRORS SetCreateUdfFs ();	

	const bool GetDVDVideoRealloc() const;
	COMMAND_LINE_ERRORS SetDVDVideoRealloc ();	

	const bool GetDVDVideoCmpt() const;
	COMMAND_LINE_ERRORS SetDVDVideoCmpt ();	

	
	// NIITEF_IMPORT_ROCKRIDGE flag is obsolete so we commented the
	// code below.
	//
/*	const bool GetImportRockridge() const;
	COMMAND_LINE_ERRORS SetImportRockridge ();*/

	const bool GetImportUDF() const;
	COMMAND_LINE_ERRORS SetImportUDF ();

	const bool GetImportVMSSession() const;
	COMMAND_LINE_ERRORS SetImportVMSSession ();
		
/*	const bool GetImportIsoOnly() const;
	COMMAND_LINE_ERRORS SetImportIsoOnly ();	*/

/*	const bool GetPreferRockRidge() const;
	COMMAND_LINE_ERRORS SetPreferRockridge ();	*/

	const bool GetDisableEject() const;
	COMMAND_LINE_ERRORS SetDisableEject ();	

	const bool GetVerify() const;
	COMMAND_LINE_ERRORS SetVerify ();	

	const bool GetISOSelected() const;
	COMMAND_LINE_ERRORS SetISOSelected (int& argc, char**& argv);	

	const LPCSTR GetVolumeName() const;
	COMMAND_LINE_ERRORS SetVolumeName (char* psName);	

	const bool GetDontUseJoliet() const;
	COMMAND_LINE_ERRORS SetDontUseJoliet ();	

	const bool GetUseMode2() const;
	COMMAND_LINE_ERRORS SetUseMode2 ();	

	const bool GetVolumeNameSupplied() const;
	COMMAND_LINE_ERRORS SetVolumeNameSupplied ();

	const bool GetUseDVD() const;
	COMMAND_LINE_ERRORS SetUseDVD ();

	const bool GetUseDVDHighCompatibility() const;
	COMMAND_LINE_ERRORS SetUseDVDHighCompatibility ();

	const bool GetRecursive() const;
	COMMAND_LINE_ERRORS SetRecursive();

	const BURNTYPE GetBurnType () const;
	COMMAND_LINE_ERRORS SetBurnType (BURNTYPE Type);

	const LPCSTR GetImageFileName () const;
	COMMAND_LINE_ERRORS SetImageFileName (const char* psName);

	const LPCSTR GetOutputImageFileName () const;
	COMMAND_LINE_ERRORS SetOutputImageFileName (int& argc, char**& argv);
	
	COMMAND_LINE_ERRORS SetEraseMode (NEROAPI_CDRW_ERASE_MODE);
	const NEROAPI_CDRW_ERASE_MODE GetEraseMode () const;

	COMMAND_LINE_ERRORS SetTrackNumber(int iTrack, int iNumber);
	COMMAND_LINE_ERRORS IncrementNumberOfTracks();

	COMMAND_LINE_ERRORS SetTempPath (int& argc, char**& argv);
	const LPCSTR GetTempPath () const;

	const NERO_MEDIA_SET GetMediaType() const;
	COMMAND_LINE_ERRORS SetMediaType(int& argc, char**& argv);	
	
	COMMAND_LINE_ERRORS SetTrackMode(int iTrack, NERO_TRACKMODE_TYPE eType);
	const int GetNumberOfTracks () const;

	COMMAND_LINE_ERRORS SetTrackFileName (int iTrack, const char* psName);
	const int GetTrackNumber(int iTrack) const;
	const LPCSTR GetTrackFileName (int iTrack) const;
	const NERO_TRACKMODE_TYPE GetTrackMode(int iTrack) const;
	const bool StillTrackSpaceLeft() const;

	bool GetProcessedParameterFile ();
    COMMAND_LINE_ERRORS SetProcessedParameterFile ();

	bool GetWriteErrorLog () const;
	COMMAND_LINE_ERRORS SetWriteErrorLog ();
	COMMAND_LINE_ERRORS SetErrorLogName (int& argc, char**& argv);
	LPCSTR GetErrorLogName() const;
	
	const CSimpleStringArray& GetFileList() const;
	CSimpleStringArray& GetFileList();
	int GetFileListSize() const;

	int GetSpeedToNeroBurn (void) const;

	const bool GetUseAllSpace() const;
	COMMAND_LINE_ERRORS SetUseAllSpace();

	const bool GetRelaxJoliet() const;
	COMMAND_LINE_ERRORS SetRelaxJoliet();

	const bool GetJapaneseCDText() const;
	COMMAND_LINE_ERRORS SetJapaneseCDText();

	const bool GetBooktypeDVDROM() const;
	COMMAND_LINE_ERRORS SetBooktypeDVDROM();
	
	const bool GetNoBooktypeChange() const;
	COMMAND_LINE_ERRORS SetNoBooktypeChange();
	
	const bool GetDisableEjectAfterErase() const;
	COMMAND_LINE_ERRORS SetDisableEjectAfterErase();

	const bool GetForceEjectAfterErase() const;
	COMMAND_LINE_ERRORS SetForceEjectAfterErase();

	const LPCSTR GetImageInfoFileName () const;
	COMMAND_LINE_ERRORS SetImageInfoFileName(int& argc, char**& argv);

	const LPCSTR GetSystemIdentifier () const;
	COMMAND_LINE_ERRORS SetSystemIdentifier(int& argc, char**& argv);
	
	const LPCSTR GetVolumeSet () const;
	COMMAND_LINE_ERRORS SetVolumeSet(int& argc, char**& argv);

	const LPCSTR GetPublisher () const;
	COMMAND_LINE_ERRORS SetPublisher(int& argc, char**& argv);

	const LPCSTR GetDataPreparer () const;
	COMMAND_LINE_ERRORS SetDataPreparer(int& argc, char**& argv);

	const LPCSTR GetApplication () const;
	COMMAND_LINE_ERRORS SetApplication(int& argc, char**& argv);

	const LPCSTR GetCopyright () const;
	COMMAND_LINE_ERRORS SetCopyright(int& argc, char**& argv);

	const LPCSTR GetAbstract () const;
	COMMAND_LINE_ERRORS SetAbstract(int& argc, char**& argv);

	const LPCSTR GetBibliographic () const;
	COMMAND_LINE_ERRORS SetBibliographic(int& argc, char**& argv);
	
	bool GetBackup () const;
	COMMAND_LINE_ERRORS SetBackup (void);

	NERO_VIDEO_RESOLUTION GetVideoResolution (void) const;
	COMMAND_LINE_ERRORS SetVideoResolution (int & argc, char **& argv);

	bool GetEstimateNoFSOverhead () const;
	COMMAND_LINE_ERRORS SetEstimateNoFSOverhead (void);

	bool GetEstimateNoData () const;
	COMMAND_LINE_ERRORS SetEstimateNoData (void);
	
	bool GetEstimateNoExactSize () const;
	COMMAND_LINE_ERRORS SetEstimateNoExactSize (void);
	
protected:
	bool ATOI (LPCSTR psString, int & iVal);

};

#endif
