{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroAPI.h/NeroAPIGlue.h, released March 2003. The      }
{ original Pascal code is: NeroAPI.pas, released June 2003. The initial        }
{ developer of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).  }
{                                                                              }
{ Portions created by Andreas Hausladen are Copyright (C) 2003                 }
{ Andreas Hausladen. All Rights Reserved.                                      }
{                                                                              }
{ Obtained through: Project Nero API for Delphi                                }
{                                                                              }
{ You may retrieve the latest version of this file at the Nero API for Delphi  }
{ home page, located at http://www.sourceforge.net/projects/delphineroapi      }
{                                                                              }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{******************************************************************************}

{******************************************************************************
|* History
|*
|* CREATOR: Andreas Hausladen
|*
|* 16/06/2003: Modifyied
|*    Alexandre Rocha Lima e Marcondes
|*    Identation
|* 26/06/2003: Modified
|*    Andreas Hausladen
|*    translation error corrected, added default-value for "reserved: PVoid"
|* 27/06/2003: Modifyied
|*    Alexandre Rocha Lima e Marcondes
|*    Identation
|*
******************************************************************************}

{******************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroAPI.h
|*
|* PURPOSE: Main interface for Nero API DLL
******************************************************************************}
unit NeroAPI;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  Windows, Types, SysUtils,
  NeroUserDialog, NeroIsoTrack, NeroFileSystemContent;

type
  _NERO_DEVICEHANDLE = record end;
  NERO_DEVICEHANDLE = ^_NERO_DEVICEHANDLE;

  PVoid = Pointer; // for reserved pointer arguments
  size_t = Integer;

{
// The NeroAPI never uses static memory. Instead, memory is allocated
// dynamically on behalf of the application, e.g. for strings. This
// memory has to be freed with this function.
//
// Passing a NULL is allowed.
}
var
  NeroFreeMem: procedure(pMem: Pointer); cdecl;


{
// All functions returning an DWORD will return 0 for success and a
// error number otherwise. This error numbers are opaque and neither
// can nor should be interpreted by the application. Instead, localized
// strings are provided for errors and informative displays.
//
// The NeroAPI keeps a log of such informative messages or errors.

// In case of an error, NeroGetLastError() will return more information
// about the last error and NeroGetErrorLog() will show all recorded
// events.
//
// Both functions return NULL if no error is available.
//
// Memory is allocated for the string, which has to be freed with NeroFreeMem().
//
// Note: NeroCloseDrive() has to throw away all errors, because they
//       might be bound to the driver. Handle errors before calling it!
}
  NeroGetLastError: function(): PChar; cdecl;
  NeroGetErrorLog: function(): PChar; cdecl;


{
// Clear errors and log (done automatically for every read or write function,
// but can be used to avoid false memory leak warnings).
}
  NeroClearErrors: procedure(); cdecl;


{
// Version management for this API:
}

// This file is the interface for this version of NeroAPI
const
  NEROAPI_VERSION_MAJOR_HIGH = 5;
  NEROAPI_VERSION_MAJOR_LOW  = 5;
  NEROAPI_VERSION_MINOR_HIGH = 10;
  NEROAPI_VERSION_MINOR_LOW  = 15;

{ Fills the pointed numbers with version number and returns true for
   success. Extended in NeroAPI 5.5.9.9 to support multiple digits }
var
  NeroGetAPIVersionEx: function(var majhi, majlo, minhi, minlo: Word;
                                reserved: PVoid = nil // Must be NULL
                               ): BOOL; cdecl;

{ Using this function, an application can tell NeroAPI for which version of NeroAPI it was
designed to work. NeroAPI will then tries to behave as this version as much as possible. This
ensures the binary compatibility with future versions of NeroAPI. If this function is not called,
NeroAPI will behaves as NeroAPI 5.0.3.9. If your application uses NeroAPIGlue.c, this function
will be automatically called. Extended in NeroAPI 5.5.9.9 to support multiple digits
Returns true for success}
  NeroSetExpectedAPIVersionEx: function(majhi, majlo, minhi, minlo: Word;
                                        reserved: PVoid = nil// Must be NULL
                                       ): BOOL; cdecl;


{
// During writing or in several long running functions control
// is transfered to the DLL. The application has to provide services
// and dialog with the user via callback functions.
//
// NERO_CALLBACK_ATTR is defined in "NeroUserDialog.h" and ensures that
// the same conventions are used for passing of parameters.
}
type
  tag_NERO_CALLBACK = record
    ncCallbackFunction: Pointer; { actually, this is a pointer to one of several different callback functions defined below }
    ncUserData: Pointer;         { this will be passed to the function as first parameter }
  end;
  NERO_CALLBACK = tag_NERO_CALLBACK;
  PNERO_CALLBACK = ^NERO_CALLBACK;
  TNeroCallBack = NERO_CALLBACK;
  PNeroCallBack = PNERO_CALLBACK;


// typedef BOOL (NERO_CALLBACK_ATTR *NERO_IDLE_CALLBACK) (void *pUserData);
  NERO_IDLE_CALLBACK = function(pUserData: Pointer): BOOL; cdecl; { called regularly during long running activities; return TRUE if this activity shall be aborted }
  TNeroIdleCallback = NERO_IDLE_CALLBACK;


{
// The NeroAPI needs some information:
}
  tag_NERO_SETTINGS = record
    nstNeroFilesPath: PChar;  {* directory name with trailing '\' of where to find the additional Nero DLL and text files
                               * No trailing '\' or '/' is necessary on for NeroAPI Portable }

    nstVendor: PChar;
    nstSoftware: PChar;           { path for registry settings (use "ahead", "Nero - Burning Rom" for Nero application's settings) }
    nstLanguageFile: PChar;       { name of the Nero language file; relativ to nstNeroFilesPath (e.g. "Nero.txt") }
    nstIdle: NERO_CALLBACK;       { NERO_IDLE_CALLBACK, may be NULL }
    nstUserDialog: NERO_CALLBACK; { NERO_USER_DIALOG, must not be NULL, see "NeroUserDialog.h" for details }

    {
    // overburn settings:
    // overburning (writing more than the nominal capacity of a disc) is allowed if:
    //  - nstEnableOverburn == TRUE
    //  - nstOverburnSize >= amount of required blocks for compilation
    // and if
    //  - the drive supports it
    //  - DAO is used.
    // Even then, overburning has to be acknowledged via callback (see DLG_OVERBURN in "NeroUserDialog.h").
    }
    nstEnableOverburn: BOOL;
    nstOverburnSize: DWORD;    { in blocks }
  end;
  NERO_SETTINGS = tag_NERO_SETTINGS;
  PNERO_SETTINGS = ^NERO_SETTINGS;
  TNeroSettings = NERO_SETTINGS;
  PNeroSettings = PNERO_SETTINGS;

{
// Initialize the DLL. Must be successful before any of the remaining
// functions can be called. Settings structure and strings it points
// to are _not_ copied and function callbacks must be available all
// the time.
}

  NEROAPI_INIT_ERROR = (
    NEROAPI_INIT_OK = 0,
    NEROAPI_INIT_INVALID_ARGS,
    NEROAPI_INIT_UNSPECIFIED_ERROR,         // Unspecified error
    NEROAPI_INIT_INVALID_SERIAL_NUM,
    NEROAPI_INIT_DEMOVERSION_EXPIRED,
    NEROAPI_INIT_ALREADY_INITIALISED,
    NEROAPI_INIT_CANNOT_LOCK
  );
  TNeroApiInitError = NEROAPI_INIT_ERROR;

// Make sure to keep *all* the data including the strings valid as long as you're using NeroAPI,
// since Nero will only store a pointer to this structure, not make a copy.
function NeroInit(var NeroSettings: TNeroSettings; reserved: PChar = nil): NEROAPI_INIT_ERROR; overload;
function NeroInit(NeroSettings: PNeroSettings; reserved: PChar = nil): NEROAPI_INIT_ERROR; overload;


{
// Call this function before closing the DLL. This is necessary because
// some clean-up actions like stopping threads cannot be done in the
// close function of the DLL.
}
  procedure NeroDone; cdecl;

{
Call this function to change a global option of NeroAPI
}
type
  NEROAPI_OPTION = (
    NEROAPI_OPTION_MSG_FILE_NAME,       // Set the language file. The value points to a string containing the file name. This adress will be kept.
    NEROAPI_OPTION_WRITE_BUFFER_SIZE    // Set write buffer size. Value points onto an integer containing the size in byte
  );
  TNeroApiOption = NEROAPI_OPTION;

var
  NeroSetOption: function(option: NEROAPI_OPTION; value: Pointer): Integer; cdecl;

{
// Code to scan the SCSI/IDE bus and get information about
// the available WORM/CDROM drives:
}

type
  NEROAPI_SCSI_DEVTYPE = (
    NEA_SCSI_DEVTYPE_UNKNOWN,
    NEA_SCSI_DEVTYPE_WORM,              { can write }
    NEA_SCSI_DEVTYPE_CDROM,             { can only read }
    NEA_SCSI_DEVTYPE_UNSUPPORTED_WORM   { can write but is not supported by NeroAPI }
  );
  TNeroApiSCSIDevType = NEROAPI_SCSI_DEVTYPE;

  tag_NERO_SPEED_INFOS = record
    nsiNumSupportedSpeeds: DWORD;     { 1 if the speed cannot be changed }
    nsiBaseSpeedKBs: DWORD;           { Speed corresponding to 1X for the selected media in KB/s }
    nsiSupportedSpeedsKBs: array[0..64 - 1] of DWORD; { List of possible speeds in KB/s }
    nsiSupportedSpeeds: array[0..64 - 1] of DWORD;    { List of possible speeds in multiple of 150KB/s (1X for CD) (present for compatibility) }
    nsiReserved: array[0..32 - 1] of DWORD;
  end;
  NERO_SPEED_INFOS = tag_NERO_SPEED_INFOS;
  PNERO_SPEED_INFOS = ^NERO_SPEED_INFOS;
  TNeroSpeedInfos = NERO_SPEED_INFOS;
  PNeroSpeedInfos = PNERO_SPEED_INFOS;

{$WARNINGS OFF}
  tag_NERO_MEDIA_TYPE = (
    MEDIA_NONE          = 0,                            // No media present (NeroAPI>=5.5.9.4)
    MEDIA_CD            = $00001,					    // CD-R/RW
    MEDIA_DDCD          = $00002,					    // DDCD-R/RW
    MEDIA_DVD_M         = $00004,					    // DVD-R/RW
    MEDIA_DVD_P         = $00008,					    // DVD+RW
    MEDIA_DVD_ANY       = MEDIA_DVD_M or MEDIA_DVD_P,   // Any DVD-Recorder
    MEDIA_DVD_RAM       = $00010,					    // DVD-RAM
    MEDIA_ML            = $00020,					    // ML (Multi Level disc)
    MEDIA_MRW           = $00040,					    // Mt. Rainier

    //NeroAPI>=5.5.9.4:
    MEDIA_NO_CDR        = $00080,				        // Exclude CD-R
    MEDIA_NO_CDRW       = $00100,					    // Exclude CD-RW
    MEDIA_CDRW          = MEDIA_CD or MEDIA_NO_CDR, 	// CD-RW
    MEDIA_CDR           = MEDIA_CD or MEDIA_NO_CDRW,	// CD-R
    MEDIA_DVD_ROM       = $00200,					    // DVD-ROM (non writable)
    MEDIA_CDROM         = $00400,                       // CD-ROM (non writable)

    //NeroAPI>=5.5.9.10
    MEDIA_NO_DVD_M_RW   = $00800,						// Exclude DVD-RW
    MEDIA_NO_DVD_M_R    = $01000,						// Exclude DVD-R
    MEDIA_NO_DVD_P_RW   = $02000,						// Exclude DVD+RW
    MEDIA_NO_DVD_P_R    = $04000,						// Exclude DVD+R
    MEDIA_DVD_M_R       = MEDIA_DVD_M or MEDIA_NO_DVD_M_RW,	// DVD-R
    MEDIA_DVD_M_RW      = MEDIA_DVD_M or MEDIA_NO_DVD_M_R,	// DVD-RW
    MEDIA_DVD_P_R       = MEDIA_DVD_P or MEDIA_NO_DVD_P_RW,	// DVD+R
    MEDIA_DVD_P_RW      = MEDIA_DVD_P or MEDIA_NO_DVD_P_R,	// DVD+RW
    MEDIA_FPACKET       = $08000,						// Fixed Packetwriting
    MEDIA_VPACKET       = $10000,						// Variable Packetwriting
    MEDIA_PACKETW       = MEDIA_MRW or MEDIA_FPACKET	// a bit mask for packetwriting
                          or MEDIA_VPACKET,
	  //NeroAPI>=5.5.10.4
  	MEDIA_HDB           = $20000                        // HD-Burn
  );
{$WARNINGS ON}
  NERO_MEDIA_TYPE = tag_NERO_MEDIA_TYPE;
  TNeroMediaType = NERO_MEDIA_TYPE;

  NERO_MEDIA_SET = type DWORD; // Represents a set of several medias


// tag_NERO_SCSI_DEVICE_INFO.nsdiCapabilities
const                                       { drive capabilities: }
  NSDI_ALLOWED                = (1 shl 0);  { the drive can only be used if this bit is set }
  NSDI_DAO                    = (1 shl 1);  { can write in DAO. }
  NSDI_READ_CD_TEXT           = (1 shl 2);  { can read CD text }
  NSDI_VARIABLE_PAUSES_IN_TAO = (1 shl 3);  { see natPauseInBlksBeforeThisTrack below }
  NSDI_DAO_WRITE_CD_TEXT      = (1 shl 4);  { writes CD text in DAO (see natArtist/Title); never supported in TAO }
  NSDI_IMAGE_RECORDER         = (1 shl 6);  { drive is the image recorder }
  NSDI_UNDETECTED             = (1 shl 7);
  NSDI_IDE_BUS                = (1 shl 8);
  NSDI_SCSI_BUS               = (1 shl 9);
  NSDI_BUF_UNDERRUN_PROT      = (1 shl 10); { drive has a buffer underrun protection feature (not necessary Burn Proof) }
  NSDI_RESERVED               = (1 shl 11); { Must not be used }
  NSDI_RESERVED2              = (1 shl 12); { Must not be used }
  NSDI_ALLOW_CHANGE_BOOKTYPE  = (1 shl 13); { NeroAPI >5.5.10.7: DVD recorder can change booktype of burned medium }

type
  tag_NERO_SCSI_DEVICE_INFO = record
    nsdiDeviceName: array[0..64 - 1] of Char;
    nsdiHostAdapterName: array[0..8 - 1] of Char;
    nsdiHostAdapterNo: DWORD;
    nsdiDeviceID: DWORD;
    nsdiDevType: NEROAPI_SCSI_DEVTYPE;
    nsdiDriveLetter: Char;         { Windows drive letter or 0 if not available }

    nsdiCapabilities: DWORD;       { drive capabilities: see above}

    nsdiReadSpeeds: NERO_SPEED_INFOS;
    nsdiWriteSpeeds: NERO_SPEED_INFOS;
    nsdiDriver: Pointer;                               { opaque identifier of the internal driver, required by NeroOpenDevice() }
    nsdiBufUnderrunProtName: array[0..64 - 1] of Char; { Buffer underrun protection technology name }
                                                       { The string will be empty if the technology has no name }
    nsdiMandatoryBUPSpeed: DWORD;                      { it is highly recommanded to enable buffer
                                                         underrun protection protection when burning at this speed or
                                                         faster. Contains 0 if there is no recommandation }
    nsdiMediaSupport: NERO_MEDIA_SET;                  { NeroAPI>=5.5.4.1: Bit field of supported media (constructed with the NERO_MEDIA_TYPE enum)}

    nsdiDriveBufferSize: DWORD;                        { NeroAPI>=5.5.9.4: Drive buffer size (internal) in KB }

    nsdiReserved: array[0..63 - 1] of DWORD;           { Should be zero }
  end;
  NERO_SCSI_DEVICE_INFO = tag_NERO_SCSI_DEVICE_INFO;
  PNERO_SCSI_DEVICE_INFO = ^NERO_SCSI_DEVICE_INFO;
  TNeroSCSIDeviceInfo = NERO_SCSI_DEVICE_INFO;
  PNeroSCSIDeviceInfo = PNERO_SCSI_DEVICE_INFO;

  tag_NERO_SCSI_DEVICE_INFOS = record
    nsdisNumDevInfos: DWORD;  { number of the following entries }
    nsdisDevInfos: array[0..0] of NERO_SCSI_DEVICE_INFO;
  end;
  NERO_SCSI_DEVICE_INFOS = tag_NERO_SCSI_DEVICE_INFOS;
  PNERO_SCSI_DEVICE_INFOS = ^NERO_SCSI_DEVICE_INFOS;
  TNeroSCSIDeviceInfos = NERO_SCSI_DEVICE_INFOS;
  PNeroSCSIDeviceInfos = PNERO_SCSI_DEVICE_INFOS;

{ Gets a list of available WORM and CDROM devices, free with NeroFreeMem(). }
{ Returns NULL for error }
var
  NeroGetAvailableDrivesEx: function(mediaType: NERO_MEDIA_TYPE; // Provide speeds values for this kind of media
                                     reserved: PVoid = nil       // Must be NULL
                                     ): PNERO_SCSI_DEVICE_INFOS; cdecl;

{ Get a string describing the given bit field of supported media
   Free with NeroFreeMem();
}
  NeroGetTypeNameOfMedia: function(media: NERO_MEDIA_SET; reserved: PVoid = nil): PChar; cdecl;

{
// Open and close a device:
}
  NeroOpenDevice: function(pDevInfo: PNERO_SCSI_DEVICE_INFO): NERO_DEVICEHANDLE; cdecl; { NULL for errors }
  NeroCloseDevice: procedure(aDeviceHandle: NERO_DEVICEHANDLE); cdecl;

{
// Get available write speeds depending on medium type, free with NeroFreeMem().
// Returns NULL for error
}

type
  NERO_ACCESSTYPE = (
    ACCESSTYPE_WRITE,
    ACCESSTYPE_READ
  );
  TNeroAccessType = NERO_ACCESSTYPE;

var
  NeroGetAvailableSpeeds: function(aDeviceHandle: NERO_DEVICEHANDLE;
                                   accessType: NERO_ACCESSTYPE;
                                   mediaType: NERO_MEDIA_TYPE;
                                   reserved: PVoid = nil): PNERO_SPEED_INFOS; cdecl;


{
// NeroAPI > 5.5.10.7
// Get and set special low level options of devices
}
type
  NERO_DEVICEOPTION = (
    // change booktype of a DVD+R and DVD+RW for subsequent writes until
    // next power cycle to DVD-ROM.
    // void* is a pointer to BOOL in Nero(Set|Get)DeviceOption.
    // For setting the booktype to DVD-ROM, set parameter to TRUE, to reset
    // changing the booktype set to FALSE.
    // In NeroGetDeviceOption, TRUE is returned if the changing the booktype
    // to DVD-ROM is enabled for both DVD+R and DVD+RW, FALSE otherwise.
    NERO_DEVICEOPTION_BOOKTYPE_DVDROM = 0
  );
  TNeroDevieOption = NERO_DEVICEOPTION;

{
// Set a special option for a device
// returns 0 an success
}
var
  NeroSetDeviceOption: function(aDeviceHandle: NERO_DEVICEHANDLE;
                                aOption: NERO_DEVICEOPTION;
                                value: Pointer): Integer;

{
// Get an option from a device. The returned value must be freed with NeroFreeMem
// by the caller
}
  NeroGetDeviceOption: function(aDeviceHandle: NERO_DEVICEHANDLE;
                                aOption: NERO_DEVICEOPTION; reserved: PVoid = nil): Pointer;


{
// CD-Information:
}

type
  NERO_TRACK_TYPE = (
    NTT_UNKNOWN,
    NTT_DATA,
    NTT_AUDIO
  );
  TNeroTrackType = NERO_TRACK_TYPE;

  tag_NERO_TRACK_INFO = record
    ntiSessionNumber: DWORD;
    ntiTrackNumber: DWORD;
    ntiTrackType: NERO_TRACK_TYPE;
    ntiTrackStartBlk: DWORD;
    ntiTrackLengthInBlks: DWORD;
    ntiArtist: array[0..65 - 1] of Char;
    ntiTitle: array[0..65 - 1] of Char;
    ntiISRC: array[0..13 - 1] of Char;      { NeroAPI > 5.5.8.3: if NGCDI_READ_ISRC is present: 12 chars ISRC code + terminator }
    ntiReserved: array[0..29 - 1] of DWORD; { Should be zero }
  end;
  NERO_TRACK_INFO = tag_NERO_TRACK_INFO;
  TNeroTrackInfo = NERO_TRACK_INFO;

  NERO_MEDIUM_TYPE = (
    NMT_UNKNOWN,
    NMT_CD_ROM,
    NMT_CD_RECORDABLE,
    NMT_CD_REWRITEABLE
  );
  TNeroMeduimType = NERO_MEDIUM_TYPE;

  tag_NERO_CD_INFO = record
    ncdiFreeCapacityInBlocks: DWORD;
    ncdiIsWriteable: BOOL;                     { A disc can be non-writeable }
    ncdiMediumType: NERO_MEDIUM_TYPE;          { Old media type description, ncdiMediaType should be used instead }
    ncdiArtist: array[0..65 - 1] of Char;
    ncdiTitle: array[0..65 - 1] of Char;
    ncdiAvailableEraseModes: DWORD;            { This bitfield can be decoded using the NCDI_IS_ERASE_MODE_AVAILABLE macro }
    ncdiUnusedBlocks: DWORD;                   { difference beetween Lead-Out position and last possible Lead-Out position }
    ncdiMediaType: NERO_MEDIA_TYPE;            { NeroAPI>=5.5.9.4: type of media }
    ncdiReserved: array[0..29 - 1] of DWORD;   { Should be zero }
    ncdiNumTracks: DWORD;
    ncdiTrackInfos: array[0..0] of NERO_TRACK_INFO;
  end;
  NERO_CD_INFO = tag_NERO_CD_INFO;
  PNERO_CD_INFO = ^NERO_CD_INFO;
  TNeroCDInfo = NERO_CD_INFO;
  PNeroCDInfo = PNERO_CD_INFO;


// #define NCDI_IS_ERASE_MODE_AVAILABLE(cdInfo,eraseMode)	((cdInfo).ncdiAvailableEraseModes & (1<<(eraseMode)))
function {macro} NCDI_IS_ERASE_MODE_AVAILABLE(const cdInfo: NERO_CD_INFO; eraseMode: DWORD): BOOL;

{
// Get information about a CD. Free result with NeroFreeMem().
//
// aDeviceHandle: result of NeroOpenDevice()
//         flags: see below
//
// Returns NULL in case of error.
}
var
  NeroGetCDInfo: function(aDeviceHandle: NERO_DEVICEHANDLE; dwFlags: DWORD): PNERO_CD_INFO; cdecl;
const
  NGCDI_READ_CD_TEXT     = (1 shl 0); { also try to fill in }
  NGCDI_READ_ISRC        = (1 shl 1); { NeroAPI>=5.5.8.4 }

{
// NeroAPI>=5.5.9.16: Get information about a disc image. Result must be released using NeroFreeMem().
//
// imagePath: path to the image file
// reserved: reserved for future usage
//
// Returns NULL in case of error.
}
var
  NeroGetDiscImageInfo: function(imagePath: PChar; reserved: PVoid = nil): PNERO_CD_INFO; cdecl;


{
// A progress display could look like this:
//
// +------------------------------------------------------+
// | Log of Operation:                                    |
// | +--------------------------------------------------+ |
// | | [icon] text                                      | |
// | | ...........                                      | |
// | |                                                  | |
// | +--------------------------------------------------+ |
// | Current Phase: text                                  |
// |      Progress: ********............................  |
// |                                                      |
// |                       ABORT                          |
// +------------------------------------------------------+
//
// The application may provide callback functions to set
// the different parts of this display. All of them may
// be NULL.
}
type
// typedef BOOL  (NERO_CALLBACK_ATTR *NERO_PROGRESS_CALLBACK)(void *pUserData, DWORD dwProgressInPercent);
  NERO_PROGRESS_CALLBACK = function(pUserData: Pointer; dwProgressInPercent: DWORD): BOOL; cdecl; { Will return TRUE if the user wants to abort }
  TNeroProcessCallback = NERO_PROGRESS_CALLBACK;

// typedef BOOL  (NERO_CALLBACK_ATTR *NERO_ABORTED_CALLBACK)(void *pUserData);
  NERO_ABORTED_CALLBACK = function(pUserData: Pointer): BOOL; cdecl; { Will return TRUE if the user wants to abort }
  TNeroAbortedCallback = NERO_ABORTED_CALLBACK;

  NERO_TEXT_TYPE = (
    NERO_TEXT_INFO,        { informative text                     }
    NERO_TEXT_STOP,        { some operation stopped prematurely   }
    NERO_TEXT_EXCLAMATION, { important information                }
    NERO_TEXT_QUESTION,    { a question which requires an answer  }
    NERO_TEXT_DRIVE,       { a message concerning a CD-ROM drive or recorder }
    NERO_TEXT_FILE,        { a message concerning a file          }
    NERO_TEXT_UNSPECIFIED  { no type specified                    }
  );
  TNeroTextType = NERO_TEXT_TYPE;

  NERO_MAJOR_PHASE = (
    NERO_PHASE_UNSPECIFIED                  = -1,
    NERO_PHASE_START_CACHE                  = 24,
    NERO_PHASE_DONE_CACHE                   = 25,
    NERO_PHASE_START_TEST                   = 28,
    NERO_PHASE_DONE_TEST                    = 29,
    NERO_PHASE_START_SIMULATE               = 32,
    NERO_PHASE_DONE_SIMULATE                = 33,
    NERO_PHASE_START_WRITE                  = 36,
    NERO_PHASE_DONE_WRITE                   = 37,
    NERO_PHASE_START_SIMULATE_NOSPD         = 61,
    NERO_PHASE_DONE_SIMULATE_NOSPD          = 62,
    NERO_PHASE_START_WRITE_NOSPD            = 65,
    NERO_PHASE_DONE_WRITE_NOSPD             = 66,
    NERO_PHASE_ENCODE_VIDEO                 = 82,
    NERO_PHASE_SEAMLESSLINK_ACTIVATED       = 87,
    NERO_PHASE_BUP_ACTIVATED                = 90,
    NERO_PHASE_CONTINUE_FORMATTING          = 99,
    NERO_PHASE_FORMATTING_SUCCESSFUL        = 100,
    NERO_PHASE_DVDVIDEO_DETECTED            = 111,
    NERO_PHASE_DVDVIDEO_REALLOC_STARTED     = 112,
    NERO_PHASE_DVDVIDEO_REALLOC_COMPLETED   = 113,
    NERO_PHASE_DVDVIDEO_REALLOC_NOTNEEDED   = 114, // NeroAPI > 5.5.9.3
    NERO_PHASE_DVDVIDEO_REALLOC_FAILED      = 115  // NeroAPI > 5.5.9.3
  );
  TNeroMajorPhase = NERO_MAJOR_PHASE;

{ a one-line text to be displayed; text pointer becomes invalid after returning from this function }
// typedef void  (NERO_CALLBACK_ATTR *NERO_ADD_LOG_LINE_CALLBACK)(void *pUserData, NERO_TEXT_TYPE type, const char *text);
  NERO_ADD_LOG_LINE_CALLBACK = procedure(pUserData: Pointer; _type: NERO_TEXT_TYPE; text: PChar); cdecl;

{ set the phase line; text pointer becomes invalid after returning from this function }
// typedef void  (NERO_CALLBACK_ATTR *NERO_SET_PHASE_CALLBACK)(void *pUserData, const char *text);
  NERO_SET_PHASE_CALLBACK = procedure(pUserData: Pointer; text: PChar); cdecl;

{ Tell the main program whether the burn process can be interrupted or not }
// typedef void (NERO_CALLBACK_ATTR *NERO_DISABLE_ABORT_CALLBACK)(void *pUserData,BOOL abortEnabled);
  NERO_DISABLE_ABORT_CALLBACK = procedure(pUserData: Pointer; abortEnabled: BOOL); cdecl;

{ Let the application knows in which part of the burn process NeroAPI is }
// typedef void (NERO_CALLBACK_ATTR *NERO_SET_MAJOR_PHASE_CALLBACK)(void *pUserData,NERO_MAJOR_PHASE phase,void *reserved);
  NERO_SET_MAJOR_PHASE_CALLBACK = procedure(pUserData: Pointer; phase: NERO_MAJOR_PHASE; reserved: PVoid); cdecl;

  tag_NERO_PROGRESS = record
    npProgressCallback: NERO_PROGRESS_CALLBACK;
    npAbortedCallback: NERO_ABORTED_CALLBACK;
    npAddLogLineCallback: NERO_ADD_LOG_LINE_CALLBACK;
    npSetPhaseCallback: NERO_SET_PHASE_CALLBACK;
    npUserData: Pointer;
    npDisableAbortCallback: NERO_DISABLE_ABORT_CALLBACK;     { Will be called only if the NBF_DISABLE_ABORT flags is given to the NeroBurn function }
    npSetMajorPhaseCallback: NERO_SET_MAJOR_PHASE_CALLBACK;
    npSubTaskProgressCallback: NERO_PROGRESS_CALLBACK;       { provide the write buffer fill level }
  end;
  NERO_PROGRESS = tag_NERO_PROGRESS;
  PNERO_PROGRESS = ^NERO_PROGRESS;
  TNeroProgress = NERO_PROGRESS;
  PNeroProgress = PNERO_PROGRESS;

{
// Data exchange between application and NeroAPI is done with
// a function that gets a pointer to its own structure, a buffer
// pointer and the amount in bytes to be read or written. It
// shall return the actual amount of bytes transferred. Other
// functions indicate that the EOF file has been reached when
// reading or a serious error occured.
}
// typedef DWORD (NERO_CALLBACK_ATTR *NERO_IO_CALLBACK)(void *pUserData, BYTE *pBuffer, DWORD dwLen);
  NERO_IO_CALLBACK = function(pUserData: Pointer; pBuffer: PByte; dwLen: DWORD): DWORD; cdecl;
  TNeroIOCallback = NERO_IO_CALLBACK;
// typedef BOOL (NERO_CALLBACK_ATTR *NERO_STATUS_CALLBACK)(void *pUserData);
  NERO_STATUS_CALLBACK = function(pUserData: Pointer): BOOL;
  TNeroStatusCallback = NERO_STATUS_CALLBACK;

  tag_NERO_IO = record
    nioUserData: Pointer;
    nioIOCallback: NERO_IO_CALLBACK;
    nioEOFCallback: NERO_STATUS_CALLBACK;          // shall return TRUE if further IO calls will always fail to transfer any data, i.e. EOF reached
    nioErrorCallback: NERO_STATUS_CALLBACK;        // shall return TRUE if an error occured during an IO call
  end;
  NERO_IO = tag_NERO_IO;
  TNeroIO = NERO_IO;


{ A pointer on this structure will be passed with the DLG_WAITCD_MEDIA_INFO user dialog callback
   (NeroAPI>=5.5.9.4)
}

  NERO_DLG_WAITCD_MEDIA_INFO = record
    ndwmiSize: DWORD;
    ndwmiLastDetectedMedia: NERO_MEDIA_TYPE;
    ndwmiRequestedMedia: NERO_MEDIA_SET;
    ndwmiLastDetectedMediaName: PChar;
    ndwmiRequestedMediaName: PChar;
  end;
  TNeroDlgWaitCDMediaInfo = NERO_DLG_WAITCD_MEDIA_INFO;

{
// ISO track generation functions
}

  PNERO_ISO_ITEM = ^NERO_ISO_ITEM;
  tag_NERO_ISO_ITEM = record
    fileName: array[0..256 - 1] of Char;    // File name on the burnt CD
    isDirectory: BOOL;						// Is this item a directory ?
    isReference: BOOL;						// Is this item a reference to a file/directory of a previous session
      // when recording RockRidge, you can set the name of a directory to be used for
    // retrieving rockridge informations here
    sourceFilePath: array[0..256 - 1] of Char;  // Path to the file, including file name (ignored for a directory)
    subDirFirstItem: PNERO_ISO_ITEM;        // Point on the first item of the sub directory if the item is a directory
                                            // Can be NULL if the directory is empty
                                            // (ignored for a file)
    nextItem: PNERO_ISO_ITEM;               // Next item in the current directory
    userData: Pointer;                      // Can be used to store additional informations

    // Used to reference a file from a previous session
    dataStartSec: Longint;
    dataLength: Int64;
    entryTime: tm;
    itemSize: Integer;                      // Size of the structure
    importinfo: CImportInfo;                // ImportInfo
  end;
  NERO_ISO_ITEM = tag_NERO_ISO_ITEM;
  TNeroIsoItem = NERO_ISO_ITEM;
  PNeroIsoItem = PNERO_ISO_ITEM;

// NeroCreateIsoItem: Allocate an instance from the NERO_ISO_ITEM structure
//    The itemSize member of the structure will be automatically be filled by this
//    function
// #define NeroCreateIsoItem()	NeroCreateIsoItemOfSize(sizeof(NERO_ISO_ITEM))
function {macro} NeroCreateIsoItem(): PNERO_ISO_ITEM; cdecl;

var
  NeroCreateIsoItemOfSize: function(size: size_t): PNERO_ISO_ITEM; cdecl;

// Free an instance from the NERO_ISO_ITEM structure
  NeroFreeIsoItem: procedure(item: PNERO_ISO_ITEM); cdecl;


// NeroCopyIsoItem: Create a copy of an existing NERO_ISO_ITEM object.
//    This is a safe way to obtain an exact copy of NERO_ISO_ITEM objects imported
//    from a previous session
//    Note that the new NERO_ISO_ITEM's nextItem,userData and subDirFirstItem members are set to NULL
//    Available for NeroAPI versions >5.5.9.9
  NeroCopyIsoItem: function(iso_item: PNERO_ISO_ITEM): PNERO_ISO_ITEM; cdecl;


// Create an ISO track from a NERO_ISO_ITEM tree
// NeroAPI >= 5.5.9.0:
// For special needs you have to give a pointer to NeroCITEArgs instead of name.
// See declaration of NeroCiteArgs below. Set flags to NCITEF_USE_STRUCT,
// to tell NeroCreateIsoTrackEx that name is a NeroCITEArgs struct and set the flags
// for the burn options with NeroCITEArgs::dwBurnOptions. root should also be NULL
// in this case.
  NeroCreateIsoTrackEx: function(root: PNERO_ISO_ITEM;  // First item of the root directory
                                 name: PChar;     // Name of the CD
                                 flags: DWORD           // See constants below
                                 ): CNeroIsoTrack; cdecl;
type
// this struct can be used to give some more parameters to NeroCreateIsoTrackEx:
// - If a CD shall have two different filesystems (e.g. HFS+ CDs), you can give
// the second filesystem with firstRootItem_wrapper.
// - give some information to be written to the volume descriptor
  NeroCITEArgs = record
    size: Integer;   // ignored. Initialise whole struct with 0. The version of the
                     // struct will be taken from expected version of NeroAPI
    firstRootItem: PNERO_ISO_ITEM;
    firstRootItem_wrapper: PNERO_ISO_ITEM;
    name: PChar;
    dwBurnOptions: DWORD;
    // NeroAPI >= 5.5.9.26:
    systemIdentifier: PChar; // system identifier
    volumeSet: PChar;
    publisher: PChar;       // the publisher of this track
    dataPreparer: PChar;    // the preparer of this track
    application: PChar;     // the application, that created this track
    copyright: PChar;       // copyright file
    _abstract: PChar;       // abstract file
    bibliographic: PChar;   // bibliographic file
  end;
  TNeroCITEArgs = NeroCITEArgs;

const
  NCITEF_USE_JOLIET       = (1 shl 0);
  NCITEF_USE_MODE2        = (1 shl 1);
  NCITEF_USE_ROCKRIDGE    = (1 shl 2);
  NCITEF_CREATE_ISO_FS    = (1 shl 3);
  NCITEF_CREATE_UDF_FS    = (1 shl 4);
  NCITEF_CREATE_HFS_FS    = (1 shl 5);
  NCITEF_DVDVIDEO_REALLOC = (1 shl 6);  // NeroAPI>=5.5.7.8: Perform reallocation of files in the VIDEO_TS directory
  NCITEF_USE_STRUCT       = (1 shl 7);  // NeroAPI>=5.5.9.0: 'name' points to an argument struct instead of name. If set, 'root' and other 'flags' are ignored.
  NCITEF_RESERVED1        = (1 shl 8);  // Reserved
  NCITEF_USE_ALLSPACE     = (1 shl 9);  // NeroAPI>=5.5.9.17: Use all space available on the medium for the volume to be created. Supported for DVD+-RW only
  NCITEF_RESERVED2        = (1 shl 10); // Reserved
  NCITEF_RESERVED3        = (1 shl 11); // Reserved
  NCITEF_RESERVED4        = (1 shl 12); // Reserved

// Free an ISO track previously allocated with NeroCreateIsoTrackEx
var
  NeroFreeIsoTrack: procedure(track: CNeroIsoTrack); cdecl;

// Create a NERO_ISO_ITEM tree from an already existing ISO track in order to create a new session
// with reference to files from older sessions
// *ppCDStamp will be filled with a pointer on a CDStamp object which will have to be freed later

  NeroImportIsoTrackEx: function(pRecorder: NERO_DEVICEHANDLE;
                                 trackNumber: DWORD;
                                 var ppCDStamp: Pointer;
                                 flags: DWORD): PNERO_ISO_ITEM; cdecl;

const
  NIITEF_IMPORT_ROCKRIDGE = (1 shl 0); // Will be ignored, RockRidge is now always imported if present
  NIITEF_IMPORT_ISO_ONLY  = (1 shl 1);
  NIITEF_PREFER_ROCKRIDGE = (1 shl 2); // Will be ignored
  NIITEF_IMPORT_UDF       = (1 shl 3); // Import UDF Session

// Free a CD stamp allocated by NeroImportIsoTrackEx
var
  NeroFreeCDStamp: procedure(pCDStamp: Pointer); cdecl;

// Create a file system container for the NERO_FILE_SYSTEM_CONTAINER_MEDIA compilation type

{
type
  IFileSystemDescContainer = nero interface;  declared in NeroFileSystemContent
}

var
  NeroCreateFileSystemContainer: function(reserved: PVoid = nil): IFileSystemDescContainer; cdecl;

{
// Recording functions:
}
type
  NERO_DATA_EXCHANGE_TYPE = (
    NERO_ET_FILE,           { read/write to/from WAV file. }
    NERO_ET_IO_CALLBACK,    { exchange data with application directly }
    NERO_ET_FILE_MP3,       { read from MP3 file (not for DAE) }
    NERO_ET_FILE_WMA,       { read from MS audio file (not for DAE) }
    NERO_ET_FILE_RAW,       { for a Freestyle compilation,
                            * this and NERO_ET_IO_CALLBACK
                            * are the only types allowed
                            * at the moment.
                            * It will expect files
                            * to be in the format
                            * as to be written to the disc.
                            * This exchange type is valid
                            * for freestyle compilations only }

    NERO_ET_AUDIO_FILE      { audio file created with the plugin manager }
  );
  TNeroDataExchangeType = NERO_DATA_EXCHANGE_TYPE;

// typedef void * NERO_AUDIO_ITEM_HANDLE;
  _NERO_AUDIO_ITEM_HANDLE = record end;
  NERO_AUDIO_ITEM_HANDLE = ^_NERO_AUDIO_ITEM_HANDLE; // NERO_AUDIO_ITEM_HANDLE is a " void* "
  PNERO_AUDIO_ITEM_HANDLE = ^NERO_AUDIO_ITEM_HANDLE;

  tagNERO_AUDIO_ITEM_INFO = record
    naiiAudioItem: NERO_AUDIO_ITEM_HANDLE;
    naiiFileName: PChar;
  end;
  NERO_AUDIO_ITEM_INFO = tagNERO_AUDIO_ITEM_INFO;

{ use PCM, 44.1kHz, Stereo (left channel first), 16 bits per channel, LSB,
   when exchanging data with the NeroAPI }
  tag_NERO_DATA_EXCHANGE = record
    ndeType: NERO_DATA_EXCHANGE_TYPE;
    ndeData: record
      case Integer of
        0: (ndeFileName: array[0..256 - 1] of Char);  // NERO_WAV_FILE
        1: (ndeIO: NERO_IO);                          // NERO_IO/EOF/ERROR_CALLBACK
        2: (ndeAudioItemInfo: NERO_AUDIO_ITEM_INFO);
    end;
  end;
  NERO_DATA_EXCHANGE = tag_NERO_DATA_EXCHANGE;
  PNERO_DATA_EXCHANGE = ^NERO_DATA_EXCHANGE;
  TNeroDataExchange = NERO_DATA_EXCHANGE;
  PNeroDataExchange = PNERO_DATA_EXCHANGE;


  tag_NERO_AUDIO_TRACK = record
    natPauseInBlksBeforeThisTrack: DWORD;
    natNumIndexPositions: DWORD;
    natRelativeIndexBlkPositions: array[0..98 - 1] of DWORD;  { offsets between one index position and the next one }
    natTitle, natArtist: PChar;              { set to NULL if unknown or to be taken from source }
    natSourceDataExchg: NERO_DATA_EXCHANGE;
    natLengthInBlocks: DWORD;                { only used for NERO_IO_CALLBACK }
    natIndex0ContainsData: BOOL;             { NeroAPI 5.5.9.8: TRUE, if audio data shall be written into index
                                               0. Data for index 0 must be provided. }
    natReserved: array[0..31 - 1] of DWORD;  { Should be zero }
  end;
  NERO_AUDIO_TRACK = tag_NERO_AUDIO_TRACK;
  TNeroAudioTrack = NERO_AUDIO_TRACK;

  NERO_TRACKMODE_TYPE = (
    NERO_TRACKMODE_MODE1,         { 2048 Bytes per sector data track }
    NERO_TRACKMODE_MODE2_FORM1,   { 2048 Bytes per sector, used for multisession }
    NERO_TRACKMODE_AUDIO          { 2352 Bytes per sector, standard audio track }
  );
  TNeroTrackmodeType = NERO_TRACKMODE_TYPE;

  tag_NERO_FREESTYLE_TRACK = record
    nftStructureSize: DWORD;                  { size of this structure, to ensure binary compatibility }
    nftPauseInBlksBeforeThisTrack: DWORD;
    nftNumIndexPositions: DWORD;
    nftRelativeIndexBlkPositions: array[0..98 - 1] of DWORD;  { offsets between one index position and the next one }
    nftTitle, nftArtist: PChar;               { set to NULL if unknown or to be taken from source }
    nftSourceDataExchg: NERO_DATA_EXCHANGE;   { source for raw track data }
    nftLengthInBlocks: DWORD;                 { only used for NERO_IO_CALLBACK }
    nftTracktype: NERO_TRACKMODE_TYPE;        { specifies track type to be written }
  end;
  NERO_FREESTYLE_TRACK = tag_NERO_FREESTYLE_TRACK;
  TNeroFreestyleTrack = NERO_FREESTYLE_TRACK;

  NERO_VIDEO_ITEM_TYPE = (
    NERO_MPEG_ITEM,
    NERO_JPEG_ITEM,
    NERO_NONENCODED_VIDEO_ITEM, // The source file name will be an AVI file which will be encoded into MPG by NeroAPI
    NERO_DIB_ITEM               // NeroAPI>=5.5.7.6: The source is a DIB picture. Informations about it must be given in nviData.nviDIB
  );
  TNeroVideoItemType = NERO_VIDEO_ITEM_TYPE;

  tag_NERO_VIDEO_ITEM = record
    nviPauseAfterItem: DWORD;
    nviSourceFileName: array[0..236 - 1] of Char; // MPG, JPG or AVI file
    nviData: record // NeroAPI>=5.5.7.6
      nviDib: record
        case Integer of
          0: (pDIB: PBITMAPINFO);  // Points to the DIB header followed by data
          1: (size: size_t);       // DIB size
          2: (pixelRatio: Double); // Pixel ratio of the given picture (height/width). 1 means square pixels
      end;
	end;

    reserved: DWORD;
    nviItemType: NERO_VIDEO_ITEM_TYPE;
  end;
  NERO_VIDEO_ITEM = tag_NERO_VIDEO_ITEM;
  TNeroVideoItem = NERO_VIDEO_ITEM;

  NERO_CD_FORMAT = (
    NERO_ISO_AUDIO_MEDIA             = 0, // Burn either a CD or a DVD, depending on the nwcdMediaType member
    NERO_VIDEO_CD                    = 1,
    NERO_BURN_IMAGE_MEDIA            = 2, // Burn either a CD or a DVD from an image
    NERO_FREESTYLE_CD                = 3,
    NERO_FILE_SYSTEM_CONTAINER_MEDIA = 4, // Burn an IFileSystemDescContainer (see NeroFileSystemContainer.h)

    // For compatibility
    NERO_ISO_AUDIO_CD  = 0,
    NERO_BURN_IMAGE_CD = 2
  );

  tag_NERO_WRITE_CD = record
    { both may be NULL: }
    nwcdArtist: PChar;
    nwcdTitle: PChar;

    nwcdIsoTrack: CNeroIsoTrack;             { if not NULL, then the disc will have an ISO track - please refer to "NeroIsoTrack.h" }
    nwcdCDExtra: BOOL;                       { if TRUE and nwcdIsoTrack not NULL, then the resulting CD will have audio in the first session
                                                and the data track in the second, however, currently the NeroAPI does not add any of the
                                                special CD Extra files to the data track }
    nwcdpCDStamp: Pointer;                   // Point on a CDStamp object if a particular CD is requested, otherwise NULL
    nwcdNumTracks: DWORD;

    nwcdMediaType: NERO_MEDIA_TYPE;          { Media on which the data should be written }
    nwcdReserved: array[0..32 - 1] of DWORD; { Should be zero }

    nwcdTracks: array[0..0] of NERO_AUDIO_TRACK;
  end;
  NERO_WRITE_CD = tag_NERO_WRITE_CD;
  PNERO_WRITE_CD = ^NERO_WRITE_CD;
  TNeroWriteCD = NERO_WRITE_CD;
  PNeroWriteCD = ^TNeroWriteCD;

  tag_NERO_WRITE_VIDEO_CD = record
    nwvcdSVCD: BOOL;                        // If TRUE, write a SVCD
    nwvcdNumItems: DWORD;
    nwvcdIsoTrack: CNeroIsoTrack;
    nwvcdTempPath: array[0..256 - 1] of Char; { where the encoded files will be temporary stored }
    nwvcdCustomVCDEngine: Pointer;            { For internal usage }
    nwvcdReserved: array[0..31 - 1] of DWORD; { Should be zero }
    nwvcdItems: array[0..0] of NERO_VIDEO_ITEM;
  end;
  NERO_WRITE_VIDEO_CD = tag_NERO_WRITE_VIDEO_CD;
  PNERO_WRITE_VIDEO_CD = ^NERO_WRITE_VIDEO_CD;
  TNeroWriteVideoCD = NERO_WRITE_VIDEO_CD;
  PNeroWriteVideoCD = ^TNeroWriteVideoCD;

  tag_NERO_WRITE_IMAGE = record
    nwiImageFileName: array[0..256 - 1] of Char; { Name of the NRG file to burn
                                                   ISO and CUE files can also be burnt this way }
  end;
  NERO_WRITE_IMAGE = tag_NERO_WRITE_IMAGE;
  TNeroWriteImage = NERO_WRITE_IMAGE;

{* This structure will allow you to write any type of
 * CD Layout, e.g. containing a raw data track at the beginning of the
 * disc instead of a self-made ISO/UDF filesystem.
 * This is good for writing .iso images as they can be downloaded everywhere
 * on the net }
 tag_NERO_WRITE_FREESTYLE_CD = record
    nwfcdStructureSize: DWORD;                { fill this with sizeof(NERO_FREESTYLEWRITE_CD) }
    { both may be NULL: }
    nwfcdArtist: PChar;
    nwfcdTitle: PChar;

    nwfcdIsoTrack: CNeroIsoTrack;             { if not NULL, then the disc will have an ISO track - please refer to "NeroIsoTrack.h" }
    nwfcdCDExtra: BOOL;                       { if TRUE and nwfcdIsoTrack not NULL, then the resulting CD will have audio in the first session
                                                and the data track in the second, however, currently the NeroAPI does not add any of the
                                                special CD Extra files to the data track }
    nwfcdpCDStamp: Pointer;                   // Point on a CDStamp object if a particular CD is requested, otherwise NULL

    nwfcdNumTracks: DWORD;

    nwfcdBurnOptions: DWORD;                    { NeroAPI>=5.5.9.1: Combination of NCITEF flags }
    nwfcdFSContainer: IFileSystemDescContainer; { NeroAPI>=5.5.9.1: if not NULL, then the disc will have an ISO track described by
                                                  this container. nwfcdIsoTrack must be NULL, otherwise the container will be ignored }
    nwfcdMediaType: NERO_MEDIA_TYPE;            { NeroAPI >=5.5.9.1: Media on which the data should be written }
    nwfcdReserved: array[0..32 - 1] of DWORD;   { Should be zero }

    nwfcdTracks: array[0..0] of NERO_FREESTYLE_TRACK;
  end;
  NERO_WRITE_FREESTYLE_CD = tag_NERO_WRITE_FREESTYLE_CD;
  PNERO_WRITE_FREESTYLE_CD = ^NERO_WRITE_FREESTYLE_CD;
  TNeroWriteFreestyleCD = NERO_WRITE_FREESTYLE_CD;
  PNeroWriteFreestyleCD = PNERO_WRITE_FREESTYLE_CD;

// To burn an IFileSystemDescContainer object

  tag_NERO_WRITE_FILE_SYSTEM_CONTAINER = record
    nwfscSize: DWORD;                  { fill this with sizeof(NERO_WRITE_FILE_SYSTEM_CONTENT) }
    nwfscFSContainer: IFileSystemDescContainer;
    nwfscMediaType: NERO_MEDIA_TYPE;   { Media on which the data should be written }
    nwfscBurnOptions: DWORD;           { Combination of NCITEF flags }
    nwfscReserved: array[0..32 - 1] of DWORD;   { Should be zero }
  end;
  NERO_WRITE_FILE_SYSTEM_CONTENT = tag_NERO_WRITE_FILE_SYSTEM_CONTAINER;
  TNeroWriteFileSystemContent = NERO_WRITE_FILE_SYSTEM_CONTENT;

  NEROAPI_BURN_ERROR = (
    NEROAPI_BURN_OK = 0,
    NEROAPI_BURN_UNKNOWN_CD_FORMAT,
    NEROAPI_BURN_INVALID_DRIVE,
    NEROAPI_BURN_FAILED,
    NEROAPI_BURN_FUNCTION_NOT_ALLOWED,
    NEROAPI_BURN_DRIVE_NOT_ALLOWED,
    NEROAPI_BURN_USER_ABORT
  );
  TNeroApiBurnError = NEROAPI_BURN_ERROR;

var
  NeroBurn: function(aDeviceHandle: NERO_DEVICEHANDLE;
                     CDFormat: NERO_CD_FORMAT;
                     pWriteCD: Pointer; // Must point on a NERO_WRITE_CD or a NERO_WRITE_VIDEO_CD structure
                     dwFlags: DWORD;
                     dwSpeed: DWORD;  // In KB/s if NBF_SPEED_IN_KBS is present, in multiple of 150 KB/s otherwise
                     pNeroProgress: PNERO_PROGRESS): NEROAPI_BURN_ERROR; cdecl;
{ NeroBurn() flags: }
const
  NBF_SPEED_TEST              = (1 shl 0);  { test speed of source first }
  NBF_SIMULATE                = (1 shl 1);  { simulate writing before actually writing }
  NBF_WRITE                   = (1 shl 2);  { really write at the end }
  NBF_DAO                     = (1 shl 3);  { write in DAO }
  NBF_CLOSE_SESSION           = (1 shl 4);  { only close the session and not the whole disc }
  NBF_CD_TEXT                 = (1 shl 5);  { write CD text - will be ignore if not supported by drive }
  NBF_BUF_UNDERRUN_PROT       = (1 shl 6);  { enable saver burn mode  }
  NBF_DISABLE_ABORT           = (1 shl 7);  { The disable abort callback will be called }
  NBF_DETECT_NON_EMPTY_CDRW   = (1 shl 8);  { The DLG_NON_EMPTY_CDRW user callback will be called when trying to burn onto a non empty CDRW }
  NBF_DISABLE_EJECT           = (1 shl 9);  { CD will not be ejected at the end of the burn process }
  NBF_VERIFY                  = (1 shl 10); { Verify Filesystem after writing. Works for ISO only }
  NBF_SPEED_IN_KBS            = (1 shl 11); { NeroAPI>=5.5.5.5: Interpret the dwSpeed as KB/s instead of multiple of 150 KB/s }
  NBF_DVDP_BURN_30MM_AT_LEAST = (1 shl 12); { NeroAPI>=5.5.8.0: DVD+R/RW high compability mode (at least 1GB will be written) }
  NBF_CD_TEXT_IS_JAPANESE     = (1 shl 13); { NeroApi>=5.5.9.17: If NBF_CD_TEXT and NBF_CD_TEXT_IS_JAPANESE are set, then the CD Text is treated as japanese CD Text }
  NBF_BOOKTYPE_DVDROM         = (1 shl 14); { NeroAPI>5.5.10.7: If NBF_BOOKTYPE_DVDROM the booktype of a burned DVD will be set to DVDROM }
  NBF_RESERVED2               = (1 shl 30); { Reserved }
  NBF_RESERVED                = (1 shl 31); { Reserved }

{
// Digital Audio Extraction functions:
// - aborting will not be reported by NeroGetLastError()
// - incomplete target files are not deleted
// - the function will return 0 for success, else error
}
var
  NeroDAE: function(aDeviceHandle: NERO_DEVICEHANDLE;
                    dwTrackStartBlk: DWORD;
                    dwTrackLengthInBlks: DWORD;
                    pDestDataExchg: PNERO_DATA_EXCHANGE;
                    iSpeedInX: DWORD;     // speed of extraction, 0 means maximum speed
                    pNeroProgressCallback: PNERO_CALLBACK { has to be a NERO_PROGRESS_CALLBACK }
                   ): Integer; cdecl;

//
// Utility functions:
//

  NeroIsDeviceReady: function(aDeviceHandle: NERO_DEVICEHANDLE): Integer; cdecl; // 0 for ready, else error!
  NeroEjectLoadCD: function(aDeviceHandle: NERO_DEVICEHANDLE; eject: BOOL): Integer; cdecl; // 0 for success, else error!

// NeroAPI>=5.5.9.4: Use the nstUserDialog callback functions to request a CD
// Returns FALSE if the burn process should be aborted
  NeroWaitForMedia: function(aDeviceHandle: NERO_DEVICEHANDLE;
                             nms: NERO_MEDIA_SET;             // media types requested
                             dwFlags: DWORD;                  // Set of NBF_ flags
                             pCDStamp: Pointer                // Optional stamp of requested media
                            ): Integer; cdecl;

// NeroAPI>=5.5.9.10: Get localized WAIT_CD text
//	Returned string must be released using NeroFreeMem()
//	Function may return NULL if type is out of range
  NeroGetLocalizedWaitCDTexts: function(_type: NERO_WAITCD_TYPE): PChar; cdecl;


// CDRW erasing functions

type
  NEROAPI_CDRW_ERASE_MODE = (
    NEROAPI_ERASE_ENTIRE    = 0,
    NEROAPI_ERASE_QUICK     = 1
  );
  TNeroApiCDRWEraseMode = NEROAPI_CDRW_ERASE_MODE;


var
  NeroGetCDRWErasingTime: function(aDeviceHandle: NERO_DEVICEHANDLE; mode: NEROAPI_CDRW_ERASE_MODE): Integer; cdecl;
                    // Returns estimated blanking time for loaded CD-RW in seconds,
                    // -1 if no CD inserted,
                    // -2 if recorder doesn't support CDRW
                    // -3 if the inserted media is not rewritable

  NeroEraseCDRW: function(aDeviceHandle: NERO_DEVICEHANDLE; mode: NEROAPI_CDRW_ERASE_MODE): Integer; cdecl;// Erase the loaded CD


// AUDIO SUPPORT


// NERO_CONFIG_RESULT

type
  NERO_CONFIG_RESULT = (
    NCR_CANNOT_CONFIGURE,
    NCR_CHANGED,
    NCR_NOT_CHANGED
  );
  TNeroConfigResult = NERO_CONFIG_RESULT;

////////////////////////////////////////////////////// NERO_AUDIO_FORMAT_INFO //

  tagNERO_AUDIO_FORMAT_INFO = record
  // Data
    // smth. like "RIFF PCM WAV format"
    nafiDescription: array[0..256 - 1] of Char;

    // smth. like "wav,wave,riff"
    nafiExtList: array[0..256 - 1] of Char;

    nafiTgt,                 // Contains TRUE if this is a target plugin
    nafiConfigurable: BOOL;  // ConfigureItem will fail on items of
                             // this type if this member == false
  end;
  NERO_AUDIO_FORMAT_INFO = tagNERO_AUDIO_FORMAT_INFO;
  PNERO_AUDIO_FORMAT_INFO = ^NERO_AUDIO_FORMAT_INFO;
  TNeroAudioFormatInfo = NERO_AUDIO_FORMAT_INFO;
  PNeroAudioFormatInfo = PNERO_AUDIO_FORMAT_INFO;


//////////////////////////////////////////////////////////// Helper functions //
var
  NeroAudioCreateTargetItem: function(iFormatNumber: Integer): NERO_AUDIO_ITEM_HANDLE; cdecl;

  NeroAudioCloseItem: function(hItem: NERO_AUDIO_ITEM_HANDLE): BOOL; cdecl;

// Insead of hItem a value of NULL can be passed to configure the
// whole plugin manager.
  NeroAudioGUIConfigureItem: function(phItem: PNERO_AUDIO_ITEM_HANDLE; iNum: Integer): NERO_CONFIG_RESULT; cdecl;

// As soon as it returns false, it means that there are no more formats.
  NeroAudioGetFormatInfo: function(iNum: Integer; pFI: PNERO_AUDIO_FORMAT_INFO): BOOL; cdecl;

//
// Deprecated functions. Present for compatibility with previous versions
//

  NeroGetAPIVersion: function(): DWORD; cdecl; { Returns 1000 for 1.0.0.0 }

  NeroSetExpectedAPIVersion: function(iExpectedVersion: DWORD): BOOL; cdecl;



{ NeroAPIGlue.h }
{******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|*
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroAPIGlue.h
|*
|* PURPOSE: Functions for connecting to NeroAPI
******************************************************************************}

{
// This function has to be called first.
}

function NeroAPIGlueConnect(reserved: PVoid = nil): Boolean;

{
// This one cleans up after using the glue code.
}
procedure NeroAPIGlueDone;




{ NeroAPIGlue.lib }
{ === information from NeroAPI551015.pdf === }

var
  NeroAPIPath: AnsiString;

implementation
uses
  NeroPacketWriting;

const
  NeroAPI_dll = 'NeroAPI.dll';
  NeroAPIKey = 'SOFTWARE\Ahead\Shared';

var
  LibNeroAPI: HMODULE; // NeroAPI.dll module handle
  FNeroDone: Boolean;

// overloaded or extended functions
var
  _NeroInit: function(pNeroSettings: PNERO_SETTINGS; reserved: PChar): NEROAPI_INIT_ERROR; cdecl;
  _NeroDone: procedure(); cdecl;

procedure NeroNotImplemented; cdecl;
begin
  raise Exception.CreateFmt('Symbol not found in %s', [NeroAPI_dll]);
end;

function GetNeroProc(const Name: string): Pointer;
begin
  Result := GetProcAddress(LibNeroAPI, PChar(Name));
  if Result = nil then
    Result := @NeroNotImplemented;
end;

procedure InitNeroAPIFunctions;
begin
 // get dll functions
 { NeroAPI.h }
  NeroFreeMem                    := GetNeroProc('NeroFreeMem');
  NeroGetLastError               := GetNeroProc('NeroGetLastError');
  NeroGetErrorLog                := GetNeroProc('NeroGetErrorLog');
  NeroClearErrors                := GetNeroProc('NeroClearErrors');
  NeroGetAPIVersionEx            := GetNeroProc('NeroGetAPIVersionEx');
  NeroSetExpectedAPIVersionEx    := GetNeroProc('NeroSetExpectedAPIVersionEx');
  _NeroInit                      := GetNeroProc('NeroInit');
  _NeroDone                      := GetNeroProc('NeroDone');
  NeroSetOption                  := GetNeroProc('NeroSetOption');
  NeroGetAvailableDrivesEx       := GetNeroProc('NeroGetAvailableDrivesEx');
  NeroGetTypeNameOfMedia         := GetNeroProc('NeroGetTypeNameOfMedia');
  NeroOpenDevice                 := GetNeroProc('NeroOpenDevice');
  NeroCloseDevice                := GetNeroProc('NeroCloseDevice');
  NeroGetAvailableSpeeds         := GetNeroProc('NeroGetAvailableSpeeds');
  NeroSetDeviceOption            := GetNeroProc('NeroSetDeviceOption');
  NeroGetDeviceOption            := GetNeroProc('NeroGetDeviceOption');
  NeroGetCDInfo                  := GetNeroProc('NeroGetCDInfo');
  NeroGetDiscImageInfo           := GetNeroProc('NeroGetDiscImageInfo');
  NeroCreateIsoItemOfSize        := GetNeroProc('NeroCreateIsoItemOfSize');
  NeroFreeIsoItem                := GetNeroProc('NeroFreeIsoItem');
  NeroCopyIsoItem                := GetNeroProc('NeroCopyIsoItem');
  NeroCreateIsoTrackEx           := GetNeroProc('NeroCreateIsoTrackEx');
  NeroFreeIsoTrack               := GetNeroProc('NeroFreeIsoTrack');
  NeroImportIsoTrackEx           := GetNeroProc('NeroImportIsoTrackEx');
  NeroFreeCDStamp                := GetNeroProc('NeroFreeCDStamp');
  NeroCreateFileSystemContainer  := GetNeroProc('NeroCreateFileSystemContainer');
  NeroBurn                       := GetNeroProc('NeroBurn');
  NeroDAE                        := GetNeroProc('NeroDAE');
  NeroIsDeviceReady              := GetNeroProc('NeroIsDeviceReady');
  NeroEjectLoadCD                := GetNeroProc('NeroEjectLoadCD');
  NeroWaitForMedia               := GetNeroProc('NeroWaitForMedia');
  NeroGetLocalizedWaitCDTexts    := GetNeroProc('NeroGetLocalizedWaitCDTexts');
  NeroGetCDRWErasingTime         := GetNeroProc('NeroGetCDRWErasingTime');
  NeroEraseCDRW                  := GetNeroProc('NeroEraseCDRW');
  NeroAudioCreateTargetItem      := GetNeroProc('NeroAudioCreateTargetItem');
  NeroAudioCloseItem             := GetNeroProc('NeroAudioCloseItem');
  NeroAudioGUIConfigureItem      := GetNeroProc('NeroAudioGUIConfigureItem');
  NeroAudioGetFormatInfo         := GetNeroProc('NeroAudioGetFormatInfo');
  NeroGetAPIVersion              := GetNeroProc('NeroGetAPIVersion');
  NeroSetExpectedAPIVersion      := GetNeroProc('NeroSetExpectedAPIVersion');

 { NeroPacketWriting.h }
  NeroCreateBlockWriterInterface := GetNeroProc('NeroCreateBlockWriterInterface');
  NeroCreateBlockReaderInterface := GetNeroProc('NeroCreateBlockReaderInterface');
  NeroCreateBlockAccessFromImage := GetNeroProc('NeroCreateBlockAccessFromImage');
  NeroGetSupportedAccessModesForDevice := GetNeroProc('NeroGetSupportedAccessModesForDevice');
end;

{*******************************************************************************}

// *** macros ***

function {macro} NCDI_IS_ERASE_MODE_AVAILABLE(const cdInfo: NERO_CD_INFO; eraseMode: DWORD): BOOL;
begin
  Result := BOOL(cdInfo.ncdiAvailableEraseModes and (1 shl eraseMode));
end;

function {macro} NeroCreateIsoItem(): PNERO_ISO_ITEM;
begin
  Result := NeroCreateIsoItemOfSize(SizeOf(NERO_ISO_ITEM));
end;

{*******************************************************************************}

function NeroInit(var NeroSettings: TNeroSettings; reserved: PChar): NEROAPI_INIT_ERROR; overload;
begin
  Result := _NeroInit(@NeroSettings, reserved);
end;

function NeroInit(NeroSettings: PNeroSettings; reserved: PChar): NEROAPI_INIT_ERROR; overload;
begin
  Result := _NeroInit(NeroSettings, reserved);
end;


procedure NeroDone();
begin
  if not FNeroDone then _NeroDone;
  FNeroDone := True;
end;

function NeroAPIGlueConnect(reserved: PVoid): Boolean;
const
  Access = KEY_QUERY_VALUE;
var
  Key: HKEY;
  Len: DWORD;
  err: Integer;
begin
  Result := False;
  if LibNeroAPI <> 0 then
  begin
    Result := True;
    Exit;
  end;

 // read NeroAPI Path from registry
  err := RegOpenKeyEx(HKEY_LOCAL_MACHINE, NeroAPIKey, 0, Access, Key);
  if err = ERROR_SUCCESS then
  begin
    SetLength(NeroAPIPath, MAX_PATH);
    Len := Length(NeroAPIPath);
    if RegQueryValueEx(Key, 'NeroAPI', nil, nil, PByte(NeroAPIPath), @Len) = ERROR_SUCCESS then
      SetLength(NeroAPIPath, StrLen(PChar(NeroAPIPath))); // reset length
    RegCloseKey(Key);
  end;


  if NeroAPIPath <> '' then
  begin
   // add NeroAPI-Path to PATH-Environment variable so all needed DLLs could be loaded
    SetEnvironmentVariable('PATH', PChar(GetEnvironmentVariable('PATH') + ';' + NeroAPIPath));;

   // load NeroAPI.dll
    LibNeroAPI := SafeLoadLibrary(IncludeTrailingPathDelimiter(NeroAPIPath) + NeroAPI_dll);
    Result := LibNeroAPI <> 0;

    if Result then
    begin
      InitNeroAPIFunctions;
      FNeroDone := False;

      Result := NeroSetExpectedAPIVersionEx(NEROAPI_VERSION_MAJOR_HIGH,
                                            NEROAPI_VERSION_MAJOR_LOW,
                                            NEROAPI_VERSION_MINOR_HIGH,
                                            NEROAPI_VERSION_MINOR_LOW,
                                            nil);
    end;
  end;
end;

procedure NeroAPIGlueDone;
begin
  if LibNeroAPI <> 0 then
  begin
    NeroDone;
    if FreeLibrary(LibNeroAPI) then LibNeroAPI := 0;
  end;
end;

initialization

finalization
  if LibNeroAPI <> 0 then
    NeroAPIGlueDone;

end.
