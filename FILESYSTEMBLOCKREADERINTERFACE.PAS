unit FILESYSTEMBLOCKREADERINTERFACE;

interface
uses
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}

{$IFNDEF FILESYSTEMBLOCKREADERINTERFACE_H}
{$DEFINE FILESYSTEMBLOCKREADERINTERFACE_H}

const
  IID_INeroFileSystemBlockReader: TGUID =
    '{EA69E72E-C989-4BCF-A41B-8732B2AFBABC}';
type
  NeroFSSecNo = int64;

  NeroFSError = (
    errOK{=0},
    errEndOfDir,
    errEndOfFile,
    errReadError,
    errInvalidFS,
    errNoDirectory,
    errNoFile,
    errNotSupported,
    errIllegalArgument,
    errWriteError,
    errInternalError,
    errFileLocked  );

  NeroFSTrackType = (
    vtData{=0},
    vtAudio  );

  NeroFSPartitionInfo = record
    PartitionNum: Integer;
    PartitionStart: NEROFSSECNO;
    PartitionSize: NEROFSSECNO;
    PartitionType: NEROFSTRACKTYPE;
    sectorSize: LongInt;
  end;

  INeroFileSystemBlockReader = interface
    ['{EA69E72E-C989-4BCF-A41B-8732B2AFBABC}']

    function GetNumPartitions: Integer;   stdcall;
    function GetPartitionInfo(iNumPartition: Integer): NeroFSPartitionInfo; stdcall;
    function GetPartitionForSector(secNo: NEROFSSECNO): NeroFSPartitionInfo; stdcall;
    function ReadSectorsBuffered(pData: Pointer;
                                startSector: NEROFSSECNO;
                                noSectors: NEROFSSECNO;
                                var noSectorsRead: NEROFSSECNO): NeroFSError; stdcall;
    function ReadSectorsUnBuffered(pData: Pointer;
                                  startSector: NEROFSSECNO;
                                  noSectors: NEROFSSECNO;
                                  var noSectorsRead: NEROFSSECNO): NeroFSError; stdcall;
  end;


{$ENDIF // FILESYSTEMBLOCKREADERINTERFACE_H}

implementation

end.
