unit FILESYSTEMBLOCKACCESSINTERFACE;

interface
uses FileSystemBlockWriterInterface, FileSystemBlockAccessExtensions,
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}

{$IFNDEF FILESYSTEMBLOCKACCESSINTERFACE_H}
{$DEFINE FILESYSTEMBLOCKACCESSINTERFACE_H}

const
  IID_INeroFileSystemBlockAccess: TGUID =
    '{9A43ACE3-5894-4633-B0B1-3BB80ECA6DC6}';
type

  INeroFileSystemBlockAccess = interface(INeroFileSystemBlockWriter)
    ['{9A43ACE3-5894-4633-B0B1-3BB80ECA6DC6}']

    function GetNumSupportedExtensions: DWORD; stdcall;
    function GetFileExtensionByNumber(iNumExt: Integer): INeroFileSystemBlockAccessExtension; stdcall;
    function GetFileExtension(eExtType: NEROFSBLOCKACCESSEXTENSIONSTYPE): INeroFileSystemBlockAccessExtension; stdcall;
  end;

{$ENDIF // FILESYSTEMBLOCKACCESSINTERFACE_H}

implementation

end.
