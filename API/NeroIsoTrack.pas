{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2004 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroISOTrack.h, released April 2003. The original      }
{ Pascal code is: NeroISOTrack.pas, released June 2003. The initial developer  }
{ of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).            }
{                                                                              }
{ Portions created by Andreas Hausladen are Copyright (C) 2003,2004            }
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
|* 16/06/2003: Modified
|*    Alexandre R. L. e Marcondes
|*    Identation
|* 07/03/2004: Modified
|*    Andreas Hausladen
|*    Nero 6 (NeroAPI SDK v1.04)
|*
******************************************************************************}

{******************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroIsoTrack.h
|*
|* PURPOSE: Classes for writing ISO 9660/Joliet track
|*
|* NOTE: In contrast to NeroAPI.h, this code is not pure C, but rather C++
******************************************************************************}
unit NeroIsoTrack;

{$INCLUDE NeroAPI.inc}

interface

uses
  Windows, Types;

type
  tm = record { from time.h }
    tm_sec, tm_min, tm_hour: Integer;
    tm_mday, tm_mon, tm_year, tm_wday, tm_yday: Integer;
    tm_isdst: Integer;
  end;

  TDestructorDone = class
  public
    procedure DestroyObject(DeleteMode: Integer = 3); virtual; cdecl; { 2: stack destroy; 3: dynamic free }
  end;

  CNeroDataCallback = class;
  CNeroIsoHandle = class;
  CNeroIsoIterator = class;
  CNeroIsoEntry = class;
  CNeroIsoTrack = class;
//
// The application has to specify the complete layout of the
// ISO track. The NeroAPI does not care at all where the
// data for the files comes from. This also means that the
// application has to provide access to the filename or the
// data itself when the API needs it.
//

//
// Data can be fed into the API directly (i.e. without intermediate
// files) with CNeroDataCallback:
//
  CNeroDataCallback = class(TDestructorDone)
  public
    function IOCallback(pBuffer: PByte; dwLen: DWORD): DWORD; virtual; cdecl; abstract; // same semantic as NERO_IO_CALLBACK in "NeroAPI.h"
    function EOFCallback(): BOOL; virtual; cdecl; abstract;                             //  "       "       NERO_IO.nioEOFCallback
    function ErrorCallback(): BOOL; virtual; cdecl; abstract;                           //  "       "       NERO_IO.nioErrorCallback
  end;

//
// The API builds an internal representation of the complete
// ISO tree and uses a CNeroIsoHandle acquired from the
// application for each file to access the data later.
// Usually only one file at once will be left open.
//
  CNeroIsoHandle = class(TDestructorDone)
  public
    function Clone(): CNeroIsoHandle; virtual; cdecl; abstract;              // make a copy of yourself

    function GetFileName(strBuffer: PChar; nBufferSize: UINT): Integer; virtual; cdecl; abstract;  // If the application wants the API to read files, it has to fill
                                                                      // the buffer of size nBufferSize with a null-terminated string and return
                                                                      // the length of the full name, even if the given buffer was to small.
                                                                      // The API will try again with a larger buffer then.

    // return 0 in GetFileName() if you want to provide the data via a CNeroDataCallback:
    function Open(): CNeroDataCallback; virtual; cdecl; abstract;     // return instance ready to read the data associated with this handle or NULL for error;
                                                                      // this instance will be deleted by NeroAPI;
                                                                      // usually only one file at once will be left open
  end;


//
// Iterators are used to walk through directories while the API builds
// its internal copy of the tree. Iterators point to an entry or to NULL,
// if the last entry was passed, and can only be incremented.
//
  CNeroIsoIterator = class(TDestructorDone)
  public
    function GetCurrentEntry(): CNeroIsoEntry; virtual; cdecl; abstract; // get pointer to current entry or NULL if last one passed;
                                                                         // entry not deleted by API, so the iterator may point to itself
                                                                         // and implement the required interface (as in the NeroAPI demo),
                                                                         // or to some permanent entry
    procedure Next(); virtual; cdecl; abstract;                          // go to next entry
  end;

//
// An entry (directory or file) is described like this:
//
  CImportInfo = Pointer;

  CNeroIsoEntry = class(TDestructorDone)
  public
    function CreateDirectoryIterator(): CNeroIsoIterator; virtual; cdecl; abstract; // NULL if no directory, otherwise an iterator to step through all child entries;
                                                                                    // iterator will be deleted by NeroAPI

    function GetName(): PChar; virtual; cdecl; abstract;               // the name for this entry; will be copied by API
    function GetLength(): Int64; virtual; cdecl; abstract;             // the size of this entry in bytes, or -1 if a directory
    function CreateHandle(): CNeroIsoHandle; virtual; cdecl; abstract; // creates a handle stored by the API to open a file later, NULL for directory;
                                                                       // handle will be deleted by NeroAPI when deleting the internal ISO tree

    // The following entries are only needed when e.g. creating your
    // own Video CD ISO track and not implemented yet.
    {$IFDEF NotDefined}
    function IsMode2(): BOOL; virtual; cdecl;                   // TRUE if the application delivers mode 2 data (2336 bytes/block);
                                                                // NOTE: the size above are the number of bytes delivered by the application
                                                                // NOTE to ahead implementor: in contrast, the ISO entry length always assumes a
                                                                // lock size of 2048 and thus GetSize() has to be multiplied by 2048/2336 before using it as CIsoListEntry::size
    function GetBlockOffset(): Integer; virtual; cdecl;         // file data is to be written in this block (relative to beginning of ISO track),
                                                                // or in a block chosen by NeroAPI if -1
    {$ENDIF NotDefined}
    // Can be used to reference files from previous session
    function GetDataStartSec(): DWORD; virtual; cdecl;
    function IsDataFixed(): BOOL; virtual; cdecl;
    function GetEntryTime(var tm: tm): BOOL; virtual; cdecl;

    // This method was formerly known as GetRockRidgeInfo.
    // The object returned is a bit different internally now.
    // Since it is a private structure of NeroAPI this change doesn't matter.
    function GetImportInfo(): CImportInfo; virtual; cdecl;
    procedure GetPriorities(var iPriority: Integer; var iDirPriority: Integer); virtual; cdecl;

    // Up from NeroAPI 5.5.9.0
    function CreateDirectoryIteratorWrapper(): CNeroIsoIterator; virtual; cdecl;
    // See CreateHandle(). Creates rsc fork handle for HFS filesystems
    // Will be preferred to reading the resource fork from the file specified by GetName() if !=NULL
    function CreateResourceHandle(): CNeroIsoHandle; virtual; cdecl;

    {$IFDEF NERO_6}
    function GetUnicodeName(): PWideChar; virtual; cdecl; // the name for this entry in unicode format; will be copied by API

    // NeroAPI>=6.0.0.14: Not necessary to implement this. Only used for internal purposes.
    function GetInterface(name: PChar): Pointer; virtual; cdecl;
    {$ENDIF NERO_6}
  private
    // Reserved for future use
{$HINTS OFF} // private Symbols 'reserved1..9' not used
    // Reserved for future use
    function reserved1(): Integer; virtual; cdecl;
    function reserved2(): Integer; virtual; cdecl;
    function reserved3(): Integer; virtual; cdecl;
    function reserved4(): Integer; virtual; cdecl;
    function reserved5(): Integer; virtual; cdecl;
    function reserved6(): Integer; virtual; cdecl;
    function reserved7(): Integer; virtual; cdecl;
    {$IFDEF NERO6}
    {$ELSE}
    function reserved8(): Integer; virtual; cdecl;
    function reserved9(): Integer; virtual; cdecl;
    {$ENDIF NERO6}
{$HINTS ON}
  end;

//
// An ISO track is a special directory entry:
//
  CNeroIsoTrack = class(CNeroIsoEntry)
  private
{
    friend class CNeroIsoTrackProxy5039;	// Internal compatibility stuff;
    friend class CNeroIsoTrackProxy55915;   // Internal compatibility stuff;
}
  public
    // essential functions:
    function GetName(): PChar; reintroduce; virtual; cdecl; abstract;        // ISO volume name, copied by API
    function CreateDirectoryIterator(): CNeroIsoIterator; reintroduce; virtual; cdecl; abstract; // iterator for root directory; will be deleted by API

    // these new functions have reasonable defaults:
    function UseJoliet(): BOOL; virtual; cdecl;   // TRUE if track shall contain Joliet names in addition to ISO
    function UseMode2(): BOOL; virtual; cdecl;    // TRUE if track shall be written as mode 2/XA

    // The following 3 functions exist from NeroAPI version 5.5.0.0
    function UseRockRidge(): BOOL; virtual; cdecl; // RockRidge requires additional informations, so it is off by default
    function BurnISO(): BOOL; virtual; cdecl;      // TRUE if ISO should be created
    function BurnUDF(): BOOL; virtual; cdecl;      // TRUE if UDF should be created
{$HINTS OFF} // visiblility from public -> protected
  protected
    function GetLength(): Int64; override; cdecl;                // we are a directory, ...
    function CreateHandle(): CNeroIsoHandle; override;           // ... so we cannot be read
    function CreateResourceHandle(): CNeroIsoHandle; override;   // ... so we cannot be read
  public
    // From NeroAPI version 5.5.1.2
    // You can set your burn options simply be redefining this function instead of
    // UseJoliet, UseMode2, UseRockRidge, BurnISO and BurnUDF
    // See NeroAPI.h for the signification of the NCITEF flags
    function BurnOptions(): DWORD; virtual; cdecl;

    // Up from NeroAPI 5.5.9.0
    function CreateDirectoryIteratorWrapper(): CNeroIsoIterator; override;

    function HasWrapper(): BOOL; virtual; cdecl;

    // for internal use only. Do not reimplement this method!
    procedure dummy(); virtual; cdecl;

    procedure GetVolumeDescriptor(var systemIdentifier, volumeSet,
      publisher, dataPreparer, application,
      copyright, _abstract, bibliographic: PChar); virtual; cdecl;

    // Reserved for future use
    function reserved1(): Integer; reintroduce; virtual; cdecl;
    function reserved2(): Integer; reintroduce; virtual; cdecl;
    function reserved3(): Integer; reintroduce; virtual; cdecl;
    function reserved4(): Integer; reintroduce; virtual; cdecl;
    function reserved5(): Integer; reintroduce; virtual; cdecl;
    function reserved6(): Integer; reintroduce; virtual; cdecl;
    function reserved7(): Integer; reintroduce; virtual; cdecl;
    {$IFDEF NERO_6}
    {$ELSE}
    function reserved8(): Integer; reintroduce; virtual; cdecl;
    {$ENDIF NERO_6}
  end;
{$HINTS ON}

implementation

uses
  NeroAPI;

{ TDestructorDone }

procedure TDestructorDone.DestroyObject;
begin
 { Because it is an "interface" class this code may never execute. }
  Free;
end;

{ CNeroIsoEntry }

function CNeroIsoEntry.CreateDirectoryIteratorWrapper: CNeroIsoIterator;
begin
  Result := nil;
end;

function CNeroIsoEntry.CreateResourceHandle: CNeroIsoHandle;
begin
  Result := nil;
end;

{$IFDEF NERO_6}
function CNeroIsoEntry.GetUnicodeName(): PWideChar;
begin
  Result := nil;
end;

function CNeroIsoEntry.GetInterface(name: PChar): Pointer;
begin
  Result := nil;
end;
{$ENDIF NERO_6}

{$IFDEF NotDefined}
function CNeroIsoEntry.IsMode2: BOOL;
begin
  Result := False;
end;

function CNeroIsoEntry.GetBlockOffset: Integer;
begin
  Result := 0;
end;
{$ENDIF NotDefined}

function CNeroIsoEntry.GetDataStartSec: DWORD;
begin
  Result := 0;
end;

function CNeroIsoEntry.GetEntryTime(var tm: tm): BOOL;
begin
  Result := False;
end;

function CNeroIsoEntry.GetImportInfo: CImportInfo;
begin
  Result := nil;
end;

procedure CNeroIsoEntry.GetPriorities(var iPriority, iDirPriority: Integer);
begin
  iPriority := 0;
  iDirPriority := 0;
end;

function CNeroIsoEntry.IsDataFixed: BOOL;
begin
  Result := False;
end;

function CNeroIsoEntry.reserved1(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved2(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved3(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved4(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved5(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved6(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved7(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved8(): Integer; begin Result := 0; end;
function CNeroIsoEntry.reserved9(): Integer; begin Result := 0; end;

{ CNeroIsoTrack }

function CNeroIsoTrack.BurnISO: BOOL;
begin
  Result := True;
end;

function CNeroIsoTrack.BurnOptions: DWORD;
begin
  Result := 0;
  if UseJoliet    then Result := Result or NCITEF_USE_JOLIET;
  if UseMode2     then Result := Result or NCITEF_USE_MODE2;
  if UseRockRidge then Result := Result or NCITEF_USE_ROCKRIDGE;
  if BurnISO      then Result := Result or NCITEF_CREATE_ISO_FS;
  if BurnUDF      then Result := Result or NCITEF_CREATE_UDF_FS;
end;

function CNeroIsoTrack.BurnUDF: BOOL;
begin
  Result := False;
end;

function CNeroIsoTrack.CreateDirectoryIteratorWrapper: CNeroIsoIterator;
begin
  Result := nil;
end;

function CNeroIsoTrack.CreateHandle: CNeroIsoHandle;
begin
  Result := nil;
end;

function CNeroIsoTrack.CreateResourceHandle: CNeroIsoHandle;
begin
  Result := nil;
end;

procedure CNeroIsoTrack.dummy();
begin

end;

function CNeroIsoTrack.GetLength: Int64;
begin
  Result := -1;
end;

function CNeroIsoTrack.HasWrapper: BOOL;
begin
  Result := False;
end;

function CNeroIsoTrack.UseJoliet: BOOL;
begin
  Result := True;
end;

function CNeroIsoTrack.UseMode2: BOOL;
begin
  Result := False;
end;

function CNeroIsoTrack.UseRockRidge: BOOL;
begin
  Result := False;
end;

procedure CNeroIsoTrack.GetVolumeDescriptor(var systemIdentifier, volumeSet,
  publisher, dataPreparer, application,
  copyright, _abstract, bibliographic: PChar);
begin
  systemIdentifier := nil;
  volumeSet := nil;
  publisher := nil;
  dataPreparer := nil;
  application := nil;
  copyright := nil;
  _abstract := nil;
  bibliographic := nil;
end;


function CNeroIsoTrack.reserved1(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved2(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved3(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved4(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved5(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved6(): Integer; begin Result := 0; end;
function CNeroIsoTrack.reserved7(): Integer; begin Result := 0; end;
{$IFDEF NERO_6}
{$ELSE}
function CNeroIsoTrack.reserved8(): Integer; begin Result := 0; end;
{$ENDIF NERO_6}


end.
