{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: FileSystemBlockWriterInterface.h, released May 2003.   }
{ The original Pascal code is: NeroFileSystemWriterInterface.pas, released     }
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
|* 16/06/2003: Modifyied
|*    Alexandre R. L. e Marcondes
|*    Identation
******************************************************************************}

{*****************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: FileSystemBlockWriterInterface.h
|*
|* PURPOSE: The FileSystem block writer interface is derived from the block
|*          reader interface. It defines a path of access to RW filesystems
|*          and partitions.
*****************************************************************************}
unit FileSystemBlockWriterInterface;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  FileSystemBlockReaderInterface;

type
// Specifies the block writer type.
// You can use this information to down-cast the interface to obtain specialized functionality...

// No extensions to the normal blockwrite interface are available so far...
  InterfaceType = (
    eBWIUnknown
  );
  TInterfaceType = InterfaceType;

  INeroFileSystemBlockWriter = class(INeroFileSystemBlockReader)
  public
	// As is the case with the reader interface, the writer interface also provides two methods for sector
	// access. While WriteSectorsUnBuffered will merely ensure the consistency of the read cache (write thru),
	// WriteSectorsBuffered will not write anything to the block device immediately but will cache
	// a certain amount of sectors before doing so.
	// The latter increases performance considerably but is prone to data loss in an unstable environment.
	// Please note that regardless of which method you use, you *must* call FlushSectorCache() if you want
	// all your data to be at their final physical location because even when writing in UnBuffered mode,
	// the driver may decide to not write away your data immediately, depending on the underlying
	// writing scheme (e.g. packet writing will always try to collect a certain amount of sectors)
	function WriteSectorsBuffered(const pData; startSector, noSectors: NeroFSSecNo;
      var noSectorsWritten: NeroFSSecNo): NeroFSError; virtual; cdecl; abstract;
	function WriteSectorsUnBuffered(const pData; startSector, noSectors: NeroFSSecNo;
      var noSectorsWritten: NeroFSSecNo): NeroFSError; virtual; cdecl; abstract;
	// FlushSectorCache will be performed implicitly upon deleting the block writer object
	procedure FlushSectorCache(); virtual; cdecl; abstract;

	// Runtime type information to be used for downcasting into specialized interfaces...
	function GetBlockWriterType(): InterfaceType; virtual; cdecl; abstract;
  end;

implementation

end.

