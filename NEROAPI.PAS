unit NEROAPI;

interface
uses NeroUserDialog, NeroIsoTrack,
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}


{$IFNDEF _NEROAPI_}
{$DEFINE _NEROAPI_}

{$IFDEF __cplusplus}
{$ENDIF}

{$IFDEF NEROAPI_PORTABLE}
{$ENDIF}

{$IFDEF __NEROAPIGLUE__}
{$DEFINE NEROAPI_API}
{$ELSE}

{$IFDEF NEROAPI}
  {$IFNDEF NEROAPI_PORTABLE}
//  const
//    NEROAPI_API = __declspec(dllexport);
  {$ELSE}
    {$DEFINE NEROAPI_API}
  {$ENDIF}
{$ELSE}
//  const
//    NEROAPI_API = __declspec(dllimport);
{$ENDIF /* NEROAPI*/}

{$ENDIF /* __NEROAPIGLUE__*/}

const
  NEROAPI_VERSION_MAJOR_HIGH = 5;
  NEROAPI_VERSION_MAJOR_LOW = 5;
  NEROAPI_VERSION_MINOR_HIGH = 10;
  NEROAPI_VERSION_MINOR_LOW = 15;

type
  CRecorderInfo = Integer;//class;
  PCRecorderInfo = ^CRecorderInfo;

  NERO_DEVICEHANDLE = PCRecorderInfo;


  NeroFreeMem = procedure(pMem: Pointer); stdcall;
  NeroGetLastError = function: PCHAR; stdcall;
  NeroGetErrorLog = function: PCHAR; stdcall;
  NeroClearErrors = procedure; stdcall;
  NeroGetAPIVersionEx = function(var majhi: PWord;
                                var majlo: Word;
                                var minhi: Word;
                                var minlo: Word;
                                reserved: Pointer): Boolean; stdcall;
  NeroSetExpectedAPIVersionEx = function(majhi: Word;
                                        majlo: Word;
                                        minhi: Word;
                                        minlo: Word;
                                        reserved: Pointer): Boolean; stdcall;
  tag_NERO_CALLBACK = record
    ncCallbackFunction: Pointer;
    ncUserData: Pointer;
  end;
  NERO_CALLBACK = tag_NERO_CALLBACK;

  NERO_IDLE_CALLBACK = function (PUSERDATA: Pointer): Boolean; cdecl;

  tag_NERO_SETTINGS = record
    nstNeroFilesPath: PCHAR;
    nstVendor: PCHAR;
    nstSoftware: PCHAR;
    nstLanguageFile: PCHAR;
    nstIdle: NERO_CALLBACK;
    nstUserDialog: NERO_CALLBACK;
    nstEnableOverburn: Boolean;
    nstOverburnSize: DWORD;
  end;
  NERO_SETTINGS = tag_NERO_SETTINGS;
  PNERO_SETTINGS = ^NERO_SETTINGS;

  NEROAPI_INIT_ERROR = (
    NEROAPI_INIT_OK,
    NEROAPI_INIT_INVALID_ARGS,
    NEROAPI_INIT_UNSPECIFIED_ERROR,
    NEROAPI_INIT_INVALID_SERIAL_NUM,
    NEROAPI_INIT_DEMOVERSION_EXPIRED,
    NEROAPI_INIT_ALREADY_INITIALISED,
    NEROAPI_INIT_CANNOT_LOCK  );

  NeroInit = function(const pNeroSettings: PNERO_SETTINGS;
                     const reserved: PChar): NEROAPI_INIT_ERROR; stdcall;

  NeroDone = procedure; stdcall;

  NEROAPI_OPTION = (
    NEROAPI_OPTION_MSG_FILE_NAME,
    NEROAPI_OPTION_WRITE_BUFFER_SIZE  );

  NeroSetOption = function(option: NEROAPI_OPTION; value: Pointer): Integer; stdcall;

  NEROAPI_SCSI_DEVTYPE = (
    NEA_SCSI_DEVTYPE_UNKNOWN,
    NEA_SCSI_DEVTYPE_WORM,
    NEA_SCSI_DEVTYPE_CDROM,
    NEA_SCSI_DEVTYPE_UNSUPPORTED_WORM);

  tag_NERO_SPEED_INFOS = record
    nsiNumSupportedSpeeds: DWORD;
    nsiBaseSpeedKBs: DWORD;
    nsiSupportedSpeedsKBs: Array[0..63] of DWORD;
    nsiSupportedSpeeds: Array[0..63] of DWORD;
    nsiReserved: Array[0..31] of DWORD;
  end;
  NERO_SPEED_INFOS = tag_NERO_SPEED_INFOS;
  PNERO_SPEED_INFOS = ^NERO_SPEED_INFOS;

  tag_NERO_MEDIA_TYPE = (
    MEDIA_NONE				=	0,								// No media present (NeroAPI>=5.5.9.4)
    MEDIA_CD				=	$00001,						// CD-R/RW
    MEDIA_DDCD				=	$00002,						// DDCD-R/RW
    MEDIA_DVD_M				=	$00004,						// DVD-R/RW
    MEDIA_DVD_P				=	$00008,						// DVD+RW
    MEDIA_DVD_ANY			=	MEDIA_DVD_M + MEDIA_DVD_P,		// Any DVD-Recorder
    MEDIA_DVD_RAM			=	$00010,						// DVD-RAM
    MEDIA_ML				=	$00020,						// ML (Multi Level disc)
    MEDIA_MRW				=	$00040,						// Mt. Rainier
    MEDIA_NO_CDR			=	$00080,						// Exclude CD-R
    MEDIA_NO_CDRW			=	$00100,						// Exclude CD-RW
    MEDIA_CDRW				=   MEDIA_CD + MEDIA_NO_CDR,			// CD-RW
    MEDIA_CDR				=   MEDIA_CD + MEDIA_NO_CDRW,			// CD-R
    MEDIA_DVD_ROM			=	$00200,						// DVD-ROM (non writable)
    MEDIA_CDROM				=	$00400,						// CD-ROM (non writable)
    MEDIA_NO_DVD_M_RW		=	$00800,						// Exclude DVD-RW
    MEDIA_NO_DVD_M_R		=	$01000,						// Exclude DVD-R
    MEDIA_NO_DVD_P_RW		=	$02000,						// Exclude DVD+RW
    MEDIA_NO_DVD_P_R		=	$04000,						// Exclude DVD+R
    MEDIA_DVD_M_R			=	MEDIA_DVD_M + MEDIA_NO_DVD_M_RW,	// DVD-R
    MEDIA_DVD_M_RW			=	MEDIA_DVD_M + MEDIA_NO_DVD_M_R,	// DVD-RW
    MEDIA_DVD_P_R			=	MEDIA_DVD_P + MEDIA_NO_DVD_P_RW,	// DVD+R
    MEDIA_DVD_P_RW			=	MEDIA_DVD_P + MEDIA_NO_DVD_P_R,	// DVD+RW
    MEDIA_FPACKET			=   $08000,						// Fixed Packetwriting
    MEDIA_VPACKET			=	$10000,						// Variable Packetwriting
    MEDIA_PACKETW			=	MEDIA_MRW + MEDIA_FPACKET	+	MEDIA_VPACKET,	// a bit mask for packetwriting
    MEDIA_HDB				=	$20000							// HD-Burn
  );
  NERO_MEDIA_TYPE = tag_NERO_MEDIA_TYPE;

  NERO_MEDIA_SET = LongInt;

  tag_NERO_SCSI_DEVICE_INFO = record
    nsdiDeviceName: Array[0..63] of Char;
    nsdiHostAdapterName: Array[0..7] of Char;
    nsdiHostAdapterNo: DWORD;
    nsdiDeviceID: DWORD;
    nsdiDevType: NEROAPI_SCSI_DEVTYPE;
    nsdiDriveLetter: Char;
    nsdiCapabilities: DWORD;
    nsdiReadSpeeds: NERO_SPEED_INFOS;
    nsdiWriteSpeeds: NERO_SPEED_INFOS;
    nsdiDriver: Pointer;
    nsdiBufUnderrunProtName: Array[0..63] of Char;
    nsdiMandatoryBUPSpeed: DWORD;
    nsdiMediaSupport: NERO_MEDIA_SET;
    nsdiDriveBufferSize: DWORD;
    nsdiReserved: Array[0..62] of DWORD;
  end;
  NERO_SCSI_DEVICE_INFO = tag_NERO_SCSI_DEVICE_INFO;
  PNERO_SCSI_DEVICE_INFO = ^NERO_SCSI_DEVICE_INFO;

const
  NSDI_ALLOWED = (1 shl 0); {/* the drive can only be used if this bit is set*/}
  NSDI_DAO = (1 shl 1); {/* can write in DAO.*/}
  NSDI_READ_CD_TEXT = (1 shl 2); {/* can read CD text*/}
  NSDI_VARIABLE_PAUSES_IN_TAO = (1 shl 3); {/* see natPauseInBlksBeforeThisTrack below*/}
  NSDI_DAO_WRITE_CD_TEXT = (1 shl 4); {/* writes CD text in DAO (see natArtist/Title); never supported in TAO*/}
  NSDI_IMAGE_RECORDER = (1 shl 6); {/* drive is the image recorder*/}
  NSDI_UNDETECTED = (1 shl 7);
  NSDI_IDE_BUS = (1 shl 8);
  NSDI_SCSI_BUS = (1 shl 9);
  NSDI_BUF_UNDERRUN_PROT = (1 shl 10); {/* drive has a buffer underrun protection feature (not necessary Burn Proof)*/}
  NSDI_RESERVED = (1 shl 11); {/* Must not be used*/}
  NSDI_RESERVED2 = (1 shl 12); {/* Must not be used*/}
  NSDI_ALLOW_CHANGE_BOOKTYPE = (1 shl 13); {/* NeroAPI >5.5.10.7: DVD recorder can change booktype of burned medium*/}

type
  tag_NERO_SCSI_DEVICE_INFOS = record
    nsdisNumDevInfos: LongInt;
    nsdisDevInfos: Array[0..1-1] of NERO_SCSI_DEVICE_INFO;
  end;
  NERO_SCSI_DEVICE_INFOS = tag_NERO_SCSI_DEVICE_INFOS;
  PNERO_SCSI_DEVICE_INFOS = ^NERO_SCSI_DEVICE_INFOS;

  NeroGetAvailableDrivesEx = function(mediaType: NERO_MEDIA_TYPE;
                                     reserved: Pointer): PNERO_SCSI_DEVICE_INFOS; stdcall;

  NeroGetTypeNameOfMedia = function(media: NERO_MEDIA_SET;
                                   reserved: Pointer): PCHAR; stdcall;

  NeroOpenDevice = function(const pDevInfo: PNERO_SCSI_DEVICE_INFO): NERO_DEVICEHANDLE; stdcall;
  NeroCloseDevice = procedure(aDeviceHandle: NERO_DEVICEHANDLE); stdcall;

  NERO_ACCESSTYPE = (
    ACCESSTYPE_WRITE,
    ACCESSTYPE_READ  );

  NeroGetAvailableSpeeds = function(aDeviceHandle: NERO_DEVICEHANDLE;
                                   accessType: NERO_ACCESSTYPE;
                                   mediaType: NERO_MEDIA_TYPE;
                                   reserved: Pointer): PNERO_SPEED_INFOS; stdcall;
  NERO_DEVICEOPTION = (
	NERO_DEVICEOPTION_BOOKTYPE_DVDROM = 0 );


  NeroSetDeviceOption = function(aDeviceHandle: NERO_DEVICEHANDLE;
                                aOption: NERO_DEVICEOPTION;
                                value: Pointer): Integer; stdcall;

  NeroGetDeviceOption = function(aDeviceHandle: NERO_DEVICEHANDLE;
                                aOption: NERO_DEVICEOPTION;
                                reserved: Pointer): Pointer; stdcall;

  NERO_TRACK_TYPE = (
    NTT_UNKNOWN,
    NTT_DATA,
    NTT_AUDIO  );

  tag_NERO_TRACK_INFO = record
    ntiSessionNumber: DWORD;
    ntiTrackNumber: DWORD;
    ntiTrackType: NERO_TRACK_TYPE;
    ntiTrackStartBlk: DWORD;
    ntiTrackLengthInBlks: DWORD;
    ntiArtist: Array[0..64] of Char;
    ntiTitle: Array[0..64] of Char;
    ntiISRC: Array[0..12] of Char;
    ntiReserved: Array[0..28] of DWORD;
  end;
  NERO_TRACK_INFO = tag_NERO_TRACK_INFO;

  NERO_MEDIUM_TYPE = (
    NMT_UNKNOWN,
    NMT_CD_ROM,
    NMT_CD_RECORDABLE,
    NMT_CD_REWRITEABLE  );

  tag_NERO_CD_INFO = record
    ncdiFreeCapacityInBlocks: DWORD;
    ncdiIsWriteable: Boolean;
    ncdiMediumType: NERO_MEDIUM_TYPE;
    ncdiArtist: Array[0..64] of Char;
    ncdiTitle: Array[0..64] of Char;
    ncdiAvailableEraseModes: DWORD;
    ncdiUnusedBlocks: DWORD;
    ncdiMediaType: NERO_MEDIA_TYPE;
    ncdiReserved: Array[0..28] of DWORD;
    ncdiNumTracks: LongInt;
    ncdiTrackInfos: Array[0..0] of NERO_TRACK_INFO;
  end;
  NERO_CD_INFO = tag_NERO_CD_INFO;
  PNERO_CD_INFO = ^NERO_CD_INFO;

//const
//  NCDI_IS_ERASE_MODE_AVAILABLE(cdInfo,eraseMode) = ((cdInfo).ncdiAvailableEraseModes & (1<<(eraseMode)));

  NeroGetCDInfo = function(aDeviceHandle: NERO_DEVICEHANDLE;
                          dwFlags: DWORD): NERO_CD_INFO; stdcall;
const
  NGCDI_READ_CD_TEXT = (1 shl 0); {/* also try to fill in*/}
  NGCDI_READ_ISRC = (1 shl 1); {/* NeroAPI>=5.5.8.4*/}

type
  NeroGetDiscImageInfo = function(const imagePath: PChar; reserved: Pointer): PNERO_CD_INFO; stdcall;

  NERO_PROGRESS_CALLBACK = function(PUSERDATA: Pointer; DWPROGRESSINPERCENT: DWORD): BOOL; stdcall;
  NERO_ABORTED_CALLBACK = function(PUSERDATA: Pointer): BOOL; stdcall;

  NERO_TEXT_TYPE = (
    NERO_TEXT_INFO,        //* informative text                     */
    NERO_TEXT_STOP,        //* some operation stopped prematurely   */
    NERO_TEXT_EXCLAMATION, //* important information                */
    NERO_TEXT_QUESTION,    //* a question which requires an answer  */
    NERO_TEXT_DRIVE,       //* a message concerning a CD-ROM drive or recorder */
    NERO_TEXT_FILE,        //* a message concerning a file          */
    NERO_TEXT_UNSPECIFIED  //* no type specified                    */
  );

  NERO_MAJOR_PHASE = (
    NERO_PHASE_UNSPECIFIED					=-1,
    NERO_PHASE_START_CACHE					=24,
    NERO_PHASE_DONE_CACHE					=25,
    NERO_PHASE_START_TEST					=28,
    NERO_PHASE_DONE_TEST					=29,
    NERO_PHASE_START_SIMULATE				=32,
    NERO_PHASE_DONE_SIMULATE				=33,
    NERO_PHASE_START_WRITE					=36,
    NERO_PHASE_DONE_WRITE					=37,
    NERO_PHASE_START_SIMULATE_NOSPD			=61,
    NERO_PHASE_DONE_SIMULATE_NOSPD			=62,
    NERO_PHASE_START_WRITE_NOSPD			=65,
    NERO_PHASE_DONE_WRITE_NOSPD				=66,
    NERO_PHASE_ENCODE_VIDEO					=82,
    NERO_PHASE_SEAMLESSLINK_ACTIVATED      = 87,
    NERO_PHASE_BUP_ACTIVATED				=90,
    NERO_PHASE_CONTINUE_FORMATTING			=99,
    NERO_PHASE_FORMATTING_SUCCESSFUL		=100,
    NERO_PHASE_DVDVIDEO_DETECTED			=111,
    NERO_PHASE_DVDVIDEO_REALLOC_STARTED		=112,
    NERO_PHASE_DVDVIDEO_REALLOC_COMPLETED	=113,
    NERO_PHASE_DVDVIDEO_REALLOC_NOTNEEDED	=114, // NeroAPI > 5.5.9.3
    NERO_PHASE_DVDVIDEO_REALLOC_FAILED		=115  // NeroAPI > 5.5.9.3
  );

  NERO_ADD_LOG_LINE_CALLBACK = procedure (PUSERDATA: POinter; txtType: NERO_TEXT_TYPE; TEXT: PChar); stdcall;
  NERO_SET_PHASE_CALLBACK = procedure (PUSERDATA: POinter; TEXT: PCHAR);  stdcall;
  NERO_DISABLE_ABORT_CALLBACK = procedure (PUSERDATA: POinter; ABORTENABLED: BOOL); stdcall;
  NERO_SET_MAJOR_PHASE_CALLBACK = procedure (PUSERDATA: POinter; PHASEL: NERO_MAJOR_PHASE; RESERVED: POinter); stdcall;

  tag_NERO_PROGRESS = record
    npProgressCallback: NERO_PROGRESS_CALLBACK;
    npAbortedCallback: NERO_ABORTED_CALLBACK;
    npAddLogLineCallback: NERO_ADD_LOG_LINE_CALLBACK;
    npSetPhaseCallback: NERO_SET_PHASE_CALLBACK;
    npUserData: Pointer;
    npDisableAbortCallback: NERO_DISABLE_ABORT_CALLBACK;
    npSetMajorPhaseCallback: NERO_SET_MAJOR_PHASE_CALLBACK;
    npSubTaskProgressCallback: NERO_PROGRESS_CALLBACK;
  end;
  NERO_PROGRESS = tag_NERO_PROGRESS;

  NERO_IO_CALLBACK = function (PUSERDATA: Pointer; PBUFFER: PByte; DWLEN: DWORD): DWORD; cdecl;
  NERO_STATUS_CALLBACK = function (PUSERDATA: Pointer): BOOL; cdecl;

  tag_NERO_IO = record
    nioUserData: Pointer;
    nioIOCallback: NERO_IO_CALLBACK;
    nioEOFCallback: NERO_STATUS_CALLBACK;
    nioErrorCallback: NERO_STATUS_CALLBACK;
  end;
  NERO_IO = tag_NERO_IO;

  NERO_DLG_WAITCD_MEDIA_INFO = record
    ndwmiSize: DWORD;
    ndwmiLastDetectedMedia: NERO_MEDIA_TYPE;
    ndwmiRequestedMedia: NERO_MEDIA_SET;
    ndwmiLastDetectedMediaName: PCHAR;
    ndwmiRequestedMediaName: PCHAR;
  end;

  TM = record
    tm_sec: Integer;        //seconds after the minute (from 0)
    tm_min: Integer;        //minutes after the hour (from 0)
    tm_hour: Integer;       //hour of the day (from 0)
    tm_mday: Integer;       //day of the month (from 1)
    tm_mon: Integer;        //month of the year (from 0)
    tm_year: Integer;       //years since 1900 (from 0)
    tm_wday: Integer;       //days since Sunday (from 0)
    tm_yday: Integer;       //day of the year (from 0)
    tm_isdst: Integer;      //Daylight Saving Time flag
  end;

  PTAG_NERO_ISO_ITEM = ^tag_NERO_ISO_ITEM;
  tag_NERO_ISO_ITEM = record
    fileName: Array[0..255] of Char;
    isDirectory: Boolean;
    isReference: Boolean;
    sourceFilePath: Array[0..255] of Char;
    subDirFirstItem: PTAG_NERO_ISO_ITEM;
    nextItem: PTAG_NERO_ISO_ITEM;
    userData: Pointer;
    dataStartSec: LongInt;
    dataLength: INT64;
    entryTime: TM;
    itemSize: Integer;
    importinfo: PCIMPORTINFO;
  end;
  NERO_ISO_ITEM = tag_NERO_ISO_ITEM;

{/// NeroCreateIsoItem: Allocate an instance from the NERO_ISO_ITEM structure }
{/// The itemSize member of the structure will be automatically be filled by this }
{/// function }
const
  NeroCreateIsoItem() = NeroCreateIsoItemOfSize(sizeof(NERO_ISO_ITEM));
var
  NeroCreateIsoItemOfSize: function(_1: SIZE_T): PNEROAPI_API NERO_ISO_ITEM cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// Free an instance from the NERO_ISO_ITEM structure }
var
  NeroFreeIsoItem: function(var _1: NERO_ISO_ITEM) cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


{/// NeroCopyIsoItem: Create a copy of an existing NERO_ISO_ITEM object. }
{/// This is a safe way to obtain an exact copy of NERO_ISO_ITEM objects imported }
{/// from a previous session }
{/// Note that the new NERO_ISO_ITEM's nextItem,userData and subDirFirstItem members are set to NULL }
{/// Available for NeroAPI versions >5.5.9.9 }
var
  NeroCopyIsoItem: function(const iso_item: PNERO_ISO_ITEM): PNEROAPI_API NERO_ISO_ITEM cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// Create an ISO track from a NERO_ISO_ITEM tree }
{/// NeroAPI >= 5.5.9.0: }
{/// For special needs you have to give a pointer to NeroCITEArgs instead of name. }
{/// See declaration of NeroCiteArgs below. Set flags to NCITEF_USE_STRUCT, }
{/// to tell NeroCreateIsoTrackEx that name is a NeroCITEArgs struct and set the flags }
{/// for the burn options with NeroCITEArgs::dwBurnOptions. root should also be NULL }
{/// in this case. }
type
  CNeroIsoTrack* NADLL_ATTR NeroCreateIsoTrackEx(NERO_ISO_ITEM*root, const char*name, DWORD flags); = NEROAPI_API;
    }: /// THIS CAN BE USED TO GIVE SOME MORE PARAMETERS TO NEROCREATEISOTRACKEX:;
{/// - If a CD shall have two different filesystems (e.g. HFS+ CDs), you can give }
{/// the second filesystem with firstRootItem_wrapper. }
{/// - give some information to be written to the volume descriptor }
        size: Integer;
{/// struct will be taken from expected version of NeroAPI }
    firstRootItem: PNERO_ISO_ITEM;
    firstRootItem_wrapper: PNERO_ISO_ITEM;
    name: PCONST CHAR;
    dwBurnOptions: LongInt;
{/// NeroAPI >= 5.5.9.26: }
    systemIdentifier: PCONST CHAR;
    volumeSet: PCONST CHAR;
    publisher: PCONST CHAR;
    dataPreparer: PCONST CHAR;
    application: PCONST CHAR;
    copyright: PCONST CHAR;
    abstract: PCONST CHAR;
    bibliographic: PCONST CHAR;
  end {};

const
  NCITEF_USE_JOLIET = (1<<0);
const
  NCITEF_USE_MODE2 = (1<<1);
const
  NCITEF_USE_ROCKRIDGE = (1<<2);
const
  NCITEF_CREATE_ISO_FS = (1<<3);
const
  NCITEF_CREATE_UDF_FS = (1<<4);
const
  NCITEF_CREATE_HFS_FS = (1<<5);
const
  NCITEF_DVDVIDEO_REALLOC = (1<<6); {// NeroAPI>=5.5.7.8: Perform reallocation of files in the VIDEO_TS directory}
const
  NCITEF_USE_STRUCT = (1<<7); {// NeroAPI>=5.5.9.0: 'name' points to an argument struct instead of name. If set, 'root' and other 'flags' are ignored.}
const
  NCITEF_RESERVED1 = (1<<8); {// Reserved}
const
  NCITEF_USE_ALLSPACE = (1<<9); {// NeroAPI>=5.5.9.17: Use all space available on the medium for the volume to be created. Supported for DVD+-RW only}
const
  NCITEF_RESERVED2 = (1<<10); {// Reserved}
const
  NCITEF_RESERVED3 = (1<<11); {// Reserved}
const
  NCITEF_RESERVED4 = (1<<12); {// Reserved}

{/// Free an ISO track previously allocated with NeroCreateIsoTrackEx }

var
  NeroFreeIsoTrack: function(track: PCNEROISOTRACK) cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// Create a NERO_ISO_ITEM tree from an already existing ISO track in order to create a new session }
{/// with reference to files from older sessions }
{///*ppCDStamp will be filled with a pointer on a CDStamp object which will have to be freed later }

var
  NeroImportIsoTrackEx: function(pRecorder: NERO_DEVICEHANDLE; 
                                 trackNumber: LongInt; 
                                 var ppCDStamp: Pointer; 
                                 flags: var LongInt): NEROAPI_API NERO_ISO_ITEM cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
const
  NIITEF_IMPORT_ROCKRIDGE = (1<<0); {// Will be ignored, RockRidge is now always imported if present}
const
  NIITEF_IMPORT_ISO_ONLY = (1<<1);
const
  NIITEF_PREFER_ROCKRIDGE = (1<<2); {// Will be ignored}
const
  NIITEF_IMPORT_UDF = (1<<3); {// Import UDF Session}

{/// Free a CD stamp allocated by NeroImportIsoTrackEx }

var
  NeroFreeCDStamp: function(pCDStamp: Pointer) cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// Create a file system container for the NERO_FILE_SYSTEM_CONTAINER_MEDIA compilation type }

{$IFDEF __cplusplus}
type
  IFileSystemDescContainer; = record
    //__cplusplus: $ELSE;
    IFileSystemDescContainer: Integer;
{$ENDIF //__cplusplus}

  end {IFileSystemDescContainer;};
type
  NERO_ET_IO_CALLBACK = record
    //__cplusplus: $ENDIF;
    reserved): PIFILESYSTEMDESCCONTAINER*NADLL_ATTR NEROCREATEFILESYSTEMCONTAINER(VOID;
{+// }
{/// Recording functions: }
{= }

      end {NERO_ET_IO_CALLBACK};
  exchange = NERO_ET_IO_CALLBACK;
  data = NERO_ET_IO_CALLBACK;
  with = NERO_ET_IO_CALLBACK;
  application = NERO_ET_IO_CALLBACK;
  directly = NERO_ET_IO_CALLBACK;
var
  file: function(}: NOT FOR DAE); 
                 _2: NERO_ET_FILE_WMA; 
                 )
{= read from MS audio file (not for DAE) }
                 _4: NERO_ET_FILE_RAW; 
                 )

                 _6: }; 
                 )
{-* this and NERO_ET_IO_CALLBACK }
                 )
{-* are the only types allowed }
                 )
{-* at the moment. }
                 )
{-* It will expect files }
                 )
{-* to be in the format }
                 )
{-* as to be written to the disc. }
                 )
{-* This exchange type is valid }
                 )
{=* for freestyle compilations only }
                 )
: NERO_ET_FILE_MP3 {= READ FROM cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


type
  NERO_AUDIO_ITEM_HANDLE = Pointer;

type
  tagNERO_AUDIO_ITEM_INFO = record
    naiiAudioItem: NERO_AUDIO_ITEM_HANDLE;
    naiiFileName: PCONST CHAR;
  end {tagNERO_AUDIO_ITEM_INFO};

{+// use PCM, 44.1kHz, Stereo (left channel first), 16 bits per channel, LSB, }
{=when exchanging data with the NeroAPI }
type
  tag_NERO_DATA_EXCHANGE = record
    ndeType: NERO_DATA_EXCHANGE_TYPE;
        ndeFileName: Array[0..256-1] of Char;
    ndeIO: NERO_IO;
    ndeAudioItemInfo: NERO_AUDIO_ITEM_INFO;
  end {tag_NERO_DATA_EXCHANGE};

type
  tag_NERO_AUDIO_TRACK = record
    natPauseInBlksBeforeThisTrack: LongInt;
    natNumIndexPositions: LongInt;
    natRelativeIndexBlkPositions: Array[0..98-1] of LongInt;
{= offsets between one index position and the next one }
    natTitle,*natArtist: PCONST CHAR;
{= set to NULL if unknown or to be taken from source }
    natSourceDataExchg: NERO_DATA_EXCHANGE;
    natLengthInBlocks: LongInt;
{= only used for NERO_IO_CALLBACK }
    natIndex0ContainsData: Bool;
{- NeroAPI 5.5.9.8: TRUE, if audio data shall be written into index }
{=0. Data for index 0 must be provided. }
    natReserved: Array[0..31-1] of LongInt;
{= Should be zero }
  end {tag_NERO_AUDIO_TRACK};

type
  tag_NERO_FREESTYLE_TRACK = (
    NERO_TRACKMODE_MODE1, 
    {{= 2048 Bytes per sector data track } );

type
  tag_NERO_FREESTYLE_TRACK = record
    nftStructureSize: LongInt;
{= size of this structure, to ensure binary compatibility }
    nftPauseInBlksBeforeThisTrack: LongInt;
    nftNumIndexPositions: LongInt;
    nftRelativeIndexBlkPositions: Array[0..98-1] of LongInt;
{= offsets between one index position and the next one }
    nftTitle,*nftArtist: PCONST CHAR;
{= set to NULL if unknown or to be taken from source }
    nftSourceDataExchg: NERO_DATA_EXCHANGE;
{= source for raw track data }
    nftLengthInBlocks: LongInt;
{= only used for NERO_IO_CALLBACK }
    nftTracktype: NERO_TRACKMODE_TYPE;
{= specifies track type to be written }
  end {tag_NERO_FREESTYLE_TRACK};

type
  tag_NERO_VIDEO_ITEM = (
    NERO_MPEG_ITEM, 
    NERO_JPEG_ITEM, 
    NERO_NONENCODED_VIDEO_ITEM, 
    NERO_DIB_ITEM  );

type
  tag_NERO_VIDEO_ITEM = record
    nviPauseAfterItem: LongInt;
    nviSourceFileName: Array[0..236-1] of Char;
            pDIB: PBitmapInfo;
    size: SIZE_T;
    pixelRatio: Double;
  end {tag_NERO_VIDEO_ITEM};


type
  tag_NERO_WRITE_CD = (
    NERO_ISO_AUDIO_MEDIA {=0}, 
    NERO_VIDEO_CD {=1}, 
    NERO_BURN_IMAGE_MEDIA {=2}, 
    NERO_FREESTYLE_CD {=3}, 
    NERO_FILE_SYSTEM_CONTAINER_MEDIA{=4}, 
    {/// For compatibility  );

type
  tag_NERO_WRITE_CD = record
{+// both may be NULL:*/ }
    nwcdArtist: PCONST CHAR;
    nwcdTitle: PCONST CHAR;
    nwcdIsoTrack: PCNEROISOTRACK;
{= if not NULL, then the disc will have an ISO track - please refer to "NeroIsoTrack.h" }
    nwcdCDExtra: Bool;
{- if TRUE and nwcdIsoTrack not NULL, then the resulting CD will have audio in the first session }
{-and the data track in the second, however, currently the NeroAPI does not add any of the }
{=special CD Extra files to the data track }
    nwcdpCDStamp: Pointer;
    nwcdNumTracks: LongInt;
    nwcdMediaType: NERO_MEDIA_TYPE;
{= Media on which the data should be written }
    nwcdReserved: Array[0..32-1] of LongInt;
{= Should be zero }

    nwcdTracks: Array[0..1-1] of NERO_AUDIO_TRACK;
  end {tag_NERO_WRITE_CD};

{$IFDEF __cplusplus}
type
  IVCDFSContentGenerator; = record
    $ENDIF: Integer;
        nwvcdSVCD: Bool;
    nwvcdNumItems: LongInt;
    nwvcdIsoTrack: PCNEROISOTRACK;
    nwvcdTempPath: Array[0..256-1] of Char;
{= where the encoded files will be temporary stored }
    nwvcdCustomVCDEngine: Pointer;
{= For internal usage }
    nwvcdReserved: Array[0..31-1] of LongInt;
{= Should be zero }
    nwvcdItems: Array[0..1-1] of NERO_VIDEO_ITEM;
  end {IVCDFSContentGenerator;};

type
  tag_NERO_WRITE_IMAGE = record
    nwiImageFileName: Array[0..256-1] of Char;
{- Name of the NRG file to burn }
{=ISO and CUE files can also be burnt this way }
  end {tag_NERO_WRITE_IMAGE};

{+// This structure will allow you to write any type of }
{-* CD Layout, e.g. containing a raw data track at the beginning of the }
{-* disc instead of a self-made ISO/UDF filesystem. }
{-* This is good for writing .iso images as they can be downloaded everywhere }
{=* on the net }
type
  tag_NERO_WRITE_FREESTYLE_CD = record
    nwfcdStructureSize: LongInt;
{= fill this with sizeof(NERO_FREESTYLEWRITE_CD) }
{+// both may be NULL:*/ }
    nwfcdArtist: PCONST CHAR;
    nwfcdTitle: PCONST CHAR;
    nwfcdIsoTrack: PCNEROISOTRACK;
{= if not NULL, then the disc will have an ISO track - please refer to "NeroIsoTrack.h" }
    nwfcdCDExtra: Bool;
{- if TRUE and nwfcdIsoTrack not NULL, then the resulting CD will have audio in the first session }
{-and the data track in the second, however, currently the NeroAPI does not add any of the }
{=special CD Extra files to the data track }
    nwfcdpCDStamp: Pointer;
{= Point on a CDStamp object if a particular CD is requested, otherwise NULL }

    nwfcdNumTracks: LongInt;
    nwfcdBurnOptions: LongInt;
{= NeroAPI>=5.5.9.1: Combination of NCITEF flags (ignored if nwfcdFSContainer is NULL) }
{$IFDEF __cplusplus}
  end {tag_NERO_WRITE_FREESTYLE_CD};
type
  NERO_WRITE_FREESTYLE_CD = record
    //__cplusplus: $ENDIF;
    nwfcdFSContainer: PIFILESYSTEMDESCCONTAINER;
{- NeroAPI>=5.5.9.1: if not NULL, then the disc will have an ISO track described by }
{=this container. nwfcdIsoTrack must be NULL, otherwise the container will be ignored }
    nwfcdMediaType: NERO_MEDIA_TYPE;
{= NeroAPI >=5.5.9.1: Media on which the data should be written }
    nwfcdReserved: Array[0..32-1] of LongInt;
{= Should be zero }

    nwfcdTracks: Array[0..1-1] of NERO_FREESTYLE_TRACK;
  end {NERO_WRITE_FREESTYLE_CD};


{/// To burn an IFileSystemDescContainer object }

type
  tag_NERO_WRITE_FILE_SYSTEM_CONTAINER = record
    nwfscSize: LongInt;
{= fill this with sizeof(NERO_WRITE_FILE_SYSTEM_CONTENT) }
{$IFDEF __cplusplus}
  end {tag_NERO_WRITE_FILE_SYSTEM_CONTAINER};
type
  NERO_WRITE_FILE_SYSTEM_CONTENT = record
    //__cplusplus: $ENDIF;
    nwfscFSContainer: PIFILESYSTEMDESCCONTAINER;
    nwfscMediaType: NERO_MEDIA_TYPE;
{= Media on which the data should be written }
    nwfscBurnOptions: LongInt;
{= Combination of NCITEF flags }
    nwfscReserved: Array[0..32-1] of LongInt;
{= Should be zero }
  end {NERO_WRITE_FILE_SYSTEM_CONTENT};

type
  tagNERO_AUDIO_FORMAT_INFO = (
    NEROAPI_BURN_OK{=0}, 
    NEROAPI_BURN_UNKNOWN_CD_FORMAT, 
    NEROAPI_BURN_INVALID_DRIVE, 
    NEROAPI_BURN_FAILED, 
    NEROAPI_BURN_FUNCTION_NOT_ALLOWED, 
    NEROAPI_BURN_DRIVE_NOT_ALLOWED, 
    NEROAPI_BURN_USER_ABORT  );

var
  NeroBurn: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                     CDFormat: NERO_CD_FORMAT; 
                     const pWriteCD: Pointer; 
                     dwFlags: LongInt; 
                     dwSpeed: LongInt; 
                     var pNeroProgress: NERO_PROGRESS): NEROAPI_API NEROAPI_BURN_ERROR cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
{+// NeroBurn() flags:*/ }
const
  NBF_SPEED_TEST = (1<<0); {/* test speed of source first*/}
const
  NBF_SIMULATE = (1<<1); {/* simulate writing before actually writing*/}
const
  NBF_WRITE = (1<<2); {/* really write at the end*/}
const
  NBF_DAO = (1<<3); {/* write in DAO*/}
const
  NBF_CLOSE_SESSION = (1<<4); {/* only close the session and not the whole disc*/}
const
  NBF_CD_TEXT = (1<<5); {/* write CD text - will be ignore if not supported by drive*/}
const
  NBF_BUF_UNDERRUN_PROT = (1<<6); {/* enable saver burn mode*/}
const
  NBF_DISABLE_ABORT = (1<<7); {/* The disable abort callback will be called*/}
const
  NBF_DETECT_NON_EMPTY_CDRW = (1<<8); {/* The DLG_NON_EMPTY_CDRW user callback will be called when trying to burn onto a non empty CDRW*/}
const
  NBF_DISABLE_EJECT = (1<<9); {/* CD will not be ejected at the end of the burn process*/}
const
  NBF_VERIFY = (1<<10); {/* Verify Filesystem after writing. Works for ISO only*/}
const
  NBF_SPEED_IN_KBS = (1<<11); {/* NeroAPI>=5.5.5.5: Interpret the dwSpeed as KB/s instead of multiple of 150 KB/s*/}
const
  NBF_DVDP_BURN_30MM_AT_LEAST = (1<<12); {/* NeroAPI>=5.5.8.0: DVD+R/RW high compability mode (at least 1GB will be written)*/}
const
  NBF_CD_TEXT_IS_JAPANESE = (1<<13); {/* NeroApi>=5.5.9.17: If NBF_CD_TEXT and NBF_CD_TEXT_IS_JAPANESE are set, then the CD Text is treated as japanese CD Text*/}
const
  NBF_BOOKTYPE_DVDROM = (1<<14); {/* NeroAPI>5.5.10.7: If NBF_BOOKTYPE_DVDROM the booktype of a burned DVD will be set to DVDROM*/}
const
  NBF_RESERVED2 = (1<<30); {/* Reserved*/}
const
  NBF_RESERVED = (1<<31); {/* Reserved*/}

{+// }
{/// Digital Audio Extraction functions: }
{/// - aborting will not be reported by NeroGetLastError() }
{/// - incomplete target files are not deleted }
{/// - the function will return 0 for success, else error }
{= }

var
  NeroDAE: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                    dwTrackStartBlk: LongInt; 
                    dwTrackLengthInBlks: LongInt; 
                    const pDestDataExchg: PNERO_DATA_EXCHANGE; 
                    iSpeedInX: LongInt; 
                    var pNeroProgressCallback: NERO_CALLBACK): NEROAPI_API INT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
{= has to be a NERO_PROGRESS_CALLBACK }


{/// }
{/// Utility functions: }
{/// }

var
  NeroIsDeviceReady: function(aDeviceHandle: NERO_DEVICEHANDLE): NEROAPI_API INT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
var
  NeroEjectLoadCD: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                            eject: Bool): NEROAPI_API INT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// NeroAPI>=5.5.9.4: Use the nstUserDialog callback functions to request a CD }
{/// Returns FALSE if the burn process should be aborted }
var
  NeroWaitForMedia: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                             nms: NERO_MEDIA_SET;
                             dwFlags: LongInt; 
                             pCDStamp: Pointer): NEROAPI_API BOOL cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// NeroAPI>=5.5.9.10: Get localized WAIT_CD text }
{/// Returned string must be released using NeroFreeMem() }
{/// Function may return NULL if type is out of range }
var
  NeroGetLocalizedWaitCDTexts: function(type: var NERO_WAITCD_TYPE): NEROAPI_API CHAR cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


{/// CDRW erasing functions }

type
  tagNERO_AUDIO_FORMAT_INFO = (
    NEROAPI_ERASE_ENTIRE {=0}, 
    NEROAPI_ERASE_QUICK {=1} );


var
  NeroGetCDRWErasingTime: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                                   mode: NEROAPI_CDRW_ERASE_MODE): NEROAPI_API INT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
{/// Returns estimated blanking time for loaded CD-RW in seconds, }
{/// -1 if no CD inserted, }
{/// -2 if recorder doesn't support CDRW }
{/// -3 if the inserted media is not rewritable }

var
  NeroEraseCDRW: function(aDeviceHandle: NERO_DEVICEHANDLE; 
                          mode: NEROAPI_CDRW_ERASE_MODE): NEROAPI_API INT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


{/// NeroAPI > 5.5.9.8: AUDIO SUPPORT }


{/// NERO_CONFIG_RESULT }

type
  tagNERO_AUDIO_FORMAT_INFO = (
    NCR_CANNOT_CONFIGURE, 
    NCR_CHANGED, 
    NCR_NOT_CHANGED  );

{/////////////////////////////////////////////////////// NERO_AUDIO_FORMAT_INFO // }

type
  tagNERO_AUDIO_FORMAT_INFO = record
{/// Data }
{/// smth. like "RIFF PCM WAV format" }
    nafiDescription: Array[0..256-1] of Char;
{/// smth. like "wav,wave,riff" }
    nafiExtList: Array[0..256-1] of Integer;
    nafiTgt, nafiConfigurable: Bool;
{/// this type if this member == false }
  end {tagNERO_AUDIO_FORMAT_INFO};

{///////////////////////////////////////////////////////////// Helper functions // }

var
  NeroAudioCreateTargetItem: function(iFormatNumber: Integer): NEROAPI_API cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

var
  NeroAudioCloseItem: function(hItem: NERO_AUDIO_ITEM_HANDLE): NEROAPI_API cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// Insead of hItem a value of NULL can be passed to configure the }
{/// whole plugin manager. }
var
  \: function(var phItem: NERO_AUDIO_ITEM_HANDLE; 
              iNum: Integer): NEROAPI_API NERO_CONFIG_RESULT cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// As soon as it returns false, it means that there are no more formats. }
var
  \: function(iNum: Integer; 
              var pFI: NERO_AUDIO_FORMAT_INFO): NEROAPI_API BOOL cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{/// }
{/// Deprecated functions. Present for compatibility with previous versions }
{/// }

var
  NeroGetAPIVersion: function: NEROAPI_API DWORD cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 
{= Returns 1000 for 1.0.0.0 }

var
  NeroSetExpectedAPIVersion: function(_1: LongInt): NEROAPI_API BOOL cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


{$IFDEF __cplusplus}
{$ENDIF}

{$ENDIF // _NEROAPI_}

implementation

end.
