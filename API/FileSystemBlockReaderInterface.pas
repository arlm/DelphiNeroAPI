{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: FileSystemBlockReaderInterface.h, released May 2003.   }
{ The original Pascal code is: NeroFileSystemReaderInterface.pas, released     }
{ June 2003. The initial developer of the Pascal code is Andreas Hausladen     }
{ (ahuser@sourceforge.net).                                                    }
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
******************************************************************************}

{*****************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: FileSystemBlockReaderInterface.h
|*
|* PURPOSE: This file contains an abstract interface for reading from block
|*          devices. It will provide necessary data about the underlying
|*          medium as well as cache data if necessary.
*****************************************************************************}
unit FileSystemBlockReaderInterface;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  Types;

type
  NeroFSSecNo = Int64; // All sector references use this type. LBA adressing is used throughout the interface

  NeroFSError = (
    errOK = 0,
    errEndOfDir,    // Deprecated. Should never be returned, to be treated as errOK
    errEndOfFile,   // Behaviour see libc read command
    errReadError,
    errInvalidFS,
    errNoDirectory,
    errNoFile,
    errNotSupported,
    errIllegalArgument,
    errWriteError,
    errInternalError,
    errFileLocked
  );
  TNeroFSErrorType = NeroFSError;

  NeroFSTrackType = (
    vtData = 0,
    vtAudio
  );
  TNeroFSTrackType = NeroFSTrackType;

  NeroFSPartitionInfo = record
	PartitionNum: Integer;           // The current partition number
	PartitionStart: NeroFSSecNo;     // The start sector for this Partition
	PartitionSize: NeroFSSecNo;      // The number of sectors this Partition contains
	PartitionType: NeroFSTrackType;  // The type of Partition
	sectorSize: DWORD;               // Sector size for this Partition
  end;
  PNeroFSPartitionInfo = ^NeroFSPartitionInfo;
  TNeroFSPartitionInfo = NeroFSPartitionInfo;

  INeroFileSystemBlockReader = class
  public
	function GetNumPartitions(): Integer; virtual; cdecl; abstract;
{translation issue: NeroFSPartitionInfo or PNeroFSPartitionInfo from "NeroFSPartitionInfo &"}
	function GetPartitionInfo(iNumPartition: Integer): NeroFSPartitionInfo; virtual; cdecl; abstract;

	// Returns the partition a given sector resides in
{translation issue: NeroFSPartitionInfo or PNeroFSPartitionInfo from "NeroFSPartitionInfo &"}
	function GetPartitionForSector(secNo: NeroFSSecNo): NeroFSPartitionInfo; virtual; cdecl; abstract;

	// Reading methods. The Buffered varient will use a cache to optimize filesystem access.
	// It should be used when reading directory structures while the UnBuffered method should be
	// used when reading file contents
	// Both methods return error codes as described in NeroFSError
	// Your read requests may not cross partition boundaries!
	function ReadSectorsBuffered(var pData; startSector, noSectors: NeroFSSecNo;
      var noSectorsRead: NeroFSSecNo): NeroFSError; virtual; cdecl; abstract;
	function ReadSectorsUnBuffered(var pData; startSector, noSectors: NeroFSSecNo;
      var noSectorsRead: NeroFSSecNo): NeroFSError; virtual; cdecl; abstract;

    procedure DestroyInterface(DeleteMode: Integer = 3); virtual; cdecl; { 2: stack destroy; 3: dynamic free }
  end;

implementation

{ INeroFileSystemBlockReader }

procedure INeroFileSystemBlockReader.DestroyInterface;
begin
 { Because it is an "interface" class this code may never execute. }
  Free;
end;


end.

