{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroPacketWriting.h, released May 2003. The original   }
{ Pascal code is: NeroPacketWriting.pas, released June 2003. The initial       }
{ developer of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).  }                                                  
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
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroPacketWriting.h
|*
|* PURPOSE: This file defines a lowlevel packetwriting/MRW API for NeroAPI
******************************************************************************}
unit NeroPacketWriting;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  Types, NeroAPI,
  FileSystemBlockReaderInterface, FileSystemBlockAccessInterface;

type
  AccessMode = (
    eNoWriting          = $0000,        { Use this to instantiate an INeroFileSystemBlockAccess object for read-only access }
    ePacketWriting      = $0001,        { Use this for DVD+RW,DVD-RW,CD-RW media in non-MRW mode }
    eManagedMRW         = $0002,        { Use this for defective managed MRW mode for all media types }
    eRawMRW             = $0004,        { Use this for raw MRW mode (defective management turned off) }
    eIllegalAccessMode	= Integer($ffffffff)
  );
  TAccessModeType = AccessMode;

{ Use the following two functions to obtain a block reader/writer to a specified NeroAPI device.
 Please note that ownership of the aDeviceHandle is *not* transferred to the block writer/reader so you're
 still responsible to dispose of the device handle after disposing of the writer/reader interface.

 Please note that only one object created by either NeroCreateBlockWriterInterface or
 NeroCreateBlockReaderInterface may exist at a time. Also make sure to delete the object before using
 the referred drive for another purpose (e.g. importing multisession data, starting a recording- or
 digital audio extraction process).
 Opening a secondary device handle for the drive is *not* sufficient! }
var
  NeroCreateBlockWriterInterface: function(aDeviceHandle: NERO_DEVICEHANDLE;
                                           eAccessMode: AccessMode
                                           ): INeroFileSystemBlockAccess;
  NeroCreateBlockReaderInterface: function(aDeviceHandle: NERO_DEVICEHANDLE;
                                           eAccessMode: AccessMode
                                           ): INeroFileSystemBlockReader;

type
  ImageAccessMode = (
    eIAReadOnly	          = $0000,
    eIAReadWrite			    = $0001,
    eIAIllegalAccessMode	= Integer($ffffffff)
  );
  TImageAccessModeType = ImageAccessMode;

{ Create a block access interface for the specified image file
 Instead of an image file, you may pass a drive letter
 here to read from a specific device supported by the operating system }
var
  NeroCreateBlockAccessFromImage: function(szFilename: PChar; eAccessMode: ImageAccessMode): INeroFileSystemBlockAccess;

{ This function will return a DWORD mask containing values as declared in enum AccessMode.
 Use ((result&eDesiredMode)!=0) to determine whether a specific mode is supported. }
  NeroGetSupportedAccessModesForDevice: function(aDeviceHandle: NERO_DEVICEHANDLE): DWORD;

implementation

end.
