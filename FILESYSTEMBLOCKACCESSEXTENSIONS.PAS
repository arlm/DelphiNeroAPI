unit FILESYSTEMBLOCKACCESSEXTENSIONS;

interface
uses
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}

{$IFNDEF FILESYSTEMBLOCKACCESSEXTENSIONS_H}
{$DEFINE FILESYSTEMBLOCKACCESSEXTENSIONS_H}

const
  IID_INeroFileSystemBlockAccessExtension: TGUID =
    '{CE753B47-019F-49BF-AF28-4AACDAA63681}';
type

  NeroFSBlockAccessExtensionsType = (
    etMRWReadDefectiveManagementInfo,
    etDVDPRWFormatExtension,
    etSectorMappingControlExtension,
    etBlankAreaControlExtension,
    etIllegalBlockAccessExtension);

  INeroFileSystemBlockAccessExtension = interface
    ['{CE753B47-019F-49BF-AF28-4AACDAA63681}']

    function GetExtensionType: NEROFSBLOCKACCESSEXTENSIONSTYPE; stdcall;
  end;

{$ENDIF // FILESYSTEMBLOCKACCESSEXTENSIONS_H}

implementation

end.
