{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2004 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: FileSystemBlockAcccessExtension.h, released May 2003.  }
{ The original Pascal code is: FileSystemBlockAccessExtension.pas, released    }
{ June 2003. The initial developer of the Pascal code is Andreas Hausladen     }
{ (ahuser@sourceforge.net).                                                    }
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
|* 2004-03-07: Modified
|*    Andreas Hausladen
|*    Nero 6 (NeroAPI SDK v1.04)
|* 2004-07-23: Modified
|*    Andreas Hausladen
|*    NeroAPI SDK v1.05
|*
******************************************************************************}

{*****************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: FileSystemBlockAccessExtensions.h
|*
|* PURPOSE: All block device access extensions are derived from this one.
|*
******************************************************************************}
unit FileSystemBlockAccessExtensions;

{$INCLUDE NeroAPI.inc}

interface

type
 {
 * Type of an extension.
 * Currently no extension is provided within the NeroSDK
 }
  NeroFSBlockAccessExtensionsType = (
    etMRWReadDefectiveManagementInfo,
    etDVDPRWFormatExtension,
    etSectorMappingControlExtension,
    etBlankAreaControlExtension,
    {$IFDEF NERO_6}
    etIllegalBlockAccessExtension,
    etHDPartitionInfo,
    etHDUsedBlockAccessExtention,
    etSectorPatchControlExtension,
    etHDPartitionLocker,
    etMediumCDStamp,
    etFragmentReservation,
    etUDFImageEditExtension,
    etSessionControl,
    etNeroFSBAExtensionReserved1,
    etNeroFSBAExtensionReserved2,
    etMediumInfo
    {$ELSE}
    etIllegalBlockAccessExtension
    {$ENDIF NERO_6}
  );
  TNeroFSBlockAccessExtensionsType = NeroFSBlockAccessExtensionsType;

  INeroFileSystemBlockAccessExtension = class
  public
    function GetExtensionType(): NeroFSBlockAccessExtensionsType; virtual; cdecl; abstract;
    procedure DestroyInterface(DeleteMode: Integer = 3); virtual; cdecl; { 2: stack destroy; 3: dynamic free }
  end;


implementation

{ INeroFileSystemBlockAccessExtension }

procedure INeroFileSystemBlockAccessExtension.DestroyInterface;
begin
 { Because it is an "interface" class this code may never execute. }
  Free;
end;

end.
