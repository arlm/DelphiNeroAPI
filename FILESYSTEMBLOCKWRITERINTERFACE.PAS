unit FILESYSTEMBLOCKWRITERINTERFACE;

interface
uses FileSystemBlockReaderInterface,
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}


{$IFNDEF FILESYSTEMBLOCKWRITERINTERFACE_H}
{$DEFINE FILESYSTEMBLOCKWRITERINTERFACE_H}
const
  IID_INeroFileSystemBlockWriter: TGUID =
    '{4D83EA2B-498A-460D-A882-74D24AE13CA5}';

type
  InterfaceType = (eBWIUnknown);

  INeroFileSystemBlockWriter = interface(INeroFileSystemBlockReader)
    ['{4D83EA2B-498A-460D-A882-74D24AE13CA5}']

    function WriteSectorsBuffered(const pData: Pointer;
      startSector: NEROFSSECNO; noSectors: NEROFSSECNO;
      var noSectorsWritten: NEROFSSECNO): NeroFSError; stdcall;
    function WriteSectorsUnBuffered(const pData: Pointer;
      startSector: NEROFSSECNO; noSectors: NEROFSSECNO;
      var noSectorsWritten: NEROFSSECNO): NeroFSError; stdcall;
    procedure FlushSectorCache; stdcall;
    function GetBlockWriterType: InterfaceType; stdcall;
  end;

{$ENDIF // FILESYSTEMBLOCKWRITERINTERFACE_H}

implementation


end.
