unit NEROISOTRACK;

interface
uses
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}

{$IFNDEF _NEROISOTRACK_}
{$DEFINE _NEROISOTRACK_}

{$IFDEF __cplusplus}

{$ENDIF}

type
  CNeroDataCallback = class
  public
    destructor Destroy; virtual; abstract;
    function IOCallback(var pBuffer: BYTE;
                         dwLen: LongInt): DWORD; virtual; abstract;
    function EOFCallback: Boolean; virtual; abstract;
    function ErrorCallback: Boolean; virtual; abstract;
  end;
  PCNeroDataCallback = ^CCNeroDataCallback;

  CNeroIsoHandle = class;
  PCNeroIsoHandle = ^CNeroIsoHandle;

  CNeroIsoHandle = class
  public
    function Clone: PCNEROISOHANDLE; virtual; abstract;
    function GetFileName(strBuffer: PChar;
                          nBufferSize: Word): Integer; virtual; abstract;
    function Open: PCNERODATACALLBACK; virtual; abstract;
  end;

  CNeroIsoEntry = class;
  PCNeroIsoEntry = ^CNeroIsoEntry;

  CNeroIsoIterator = class
  public
    function GetCurrentEntry: PCNEROISOENTRY; virtual; abstract;
    procedure Next; virtual; abstract;
  end;
  PCNeroIsoIterator = ^CNeroIsoIterator;

  CImportInfo = class;
  PCImportInfo = ^CImportInfo;

  CNeroIsoEntry = class
  private
    function reserved1: Integer; virtual; abstract;
    function reserved2: Integer; virtual; abstract;
    function reserved3: Integer; virtual; abstract;
    function reserved4: Integer; virtual; abstract;
    function reserved5: Integer; virtual; abstract;
    function reserved6: Integer; virtual; abstract;
    function reserved7: Integer; virtual; abstract;
    function reserved8: Integer; virtual; abstract;
    function reserved9: Integer; virtual; abstract;
  public
    function CreateDirectoryIterator: PCNEROISOITERATOR; virtual; abstract;
    function GetName: PCHAR; virtual; abstract;
    function GetLength: Int64; virtual; abstract;
    function CreateHandle: PCNEROISOHANDLE; virtual; abstract;
    function IsMode2: Boolean; virtual; abstract;
    function GetBlockOffset: Integer; virtual; abstract;
    function GetDataStartSec: DWORD; virtual; abstract;
    function IsDataFixed: Boolean; virtual; abstract;
    function GetEntryTime: Boolean; virtual; abstract;
    function GetImportInfo: PCIMPORTINFO; virtual; abstract;
    function GetPriorities(var iPriority: Integer;
                            var iDirPriority: Integer): PCNEROISOITERATOR; virtual; abstract;
    function CreateDirectoryIteratorWrapper: PCNEROISOITERATOR; virtual; abstract;
    function CreateResourceHandle: PCNEROISOHANDLE; virtual; abstract;
  end;

  CNeroIsoTrackProxy5039 = class;
  CNeroIsoTrackProxy55915 = class;
  CNeroIsoTrack = class (CNeroIsoEntry)

  end;

  GetName: function: PVIRTUAL CONST CHAR cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  CreateDirectoryIterator: var function: VIRTUAL CNEROISOITERATOR cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  UseJoliet: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  UseMode2: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  UseRockRidge: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  BurnISO: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  BurnUDF: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  GetLength: var function: ROTECTED: VIRTUAL __INT64 cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  CreateHandle: var function: VIRTUAL CNEROISOHANDLE cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  CreateResourceHandle: var function: VIRTUAL CNEROISOHANDLE cdecl  {$IFDEF WIN32} stdcall {$ENDIF};

  BurnOptions: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  return: function(0: USEJOLIET() ? NCITEF_USE_JOLIET : 0) |(USEMODE2() ? NCITEF_USE_MODE2 : 0) |(USEROCKRIDGE() ? NCITEF_USE_ROCKRIDGE : 0) |(BURNISO() ? NCITEF_CREATE_ISO_FS : 0) |(BURNUDF() ? NCITEF_CREATE_UDF_FS :): Integer cdecl  {$IFDEF WIN32} std
  CreateDirectoryIteratorWrapper: var function: VIRTUAL CNEROISOITERATOR cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  HasWrapper: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  dummy: function cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  GetVolumeDescriptor: function(const systemIdentifier: PPChar;
                                const volumeSet: PPChar;
                                const publisher: PPChar;
                                const dataPreparer: PPChar;
                                const application: PPChar;
                                const copyright: PPChar;
                                const abstract: PPChar;
                                const bibliographic: PPChar) cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved1: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved2: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved3: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved4: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved5: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved6: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved7: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};
  reserved8: function: VIRTUAL cdecl  {$IFDEF WIN32} stdcall {$ENDIF};


{$ENDIF /* __cplusplus*/}


{$ENDIF /* _NEROISOTRACK_*/}

implementation

end.
