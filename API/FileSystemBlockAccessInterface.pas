{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: FileSystemBlockAccessInterface.h, released May 2003.   }
{ The original Pascal code is: NeroFileSystemAccessInterface.pas, released     }
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

{*****************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: FileSystemBlockAccessInterface.h
|*
|* PURPOSE: The file system block access interface
|* The NeroAPI packet writing API will return INeroFileSystemBlockAccess that
|* can be used to have block access to a file system.
******************************************************************************}
unit FileSystemBlockAccessInterface;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  Types, FileSystemBlockWriterInterface, FileSystemBlockAccessExtensions;

type

{ This interface contains an extension scheme that will allow us to
 * transparently extend the interface's functionality without losing binary
 * compatibility.
}
  INeroFileSystemBlockAccess = class(INeroFileSystemBlockWriter)
  public
	// Returns the number of supported extension fields
    function GetNumSupportedExtensions(): DWORD; virtual; cdecl; abstract;
    // In combination with the method above, this method can be used to copy a set of extensions
    // without knowing which ones are actually there. Extensions have to be passed through to
    // any of the Nero filesystem generators, so it is essential to have some means of copying them
    function GetFileExtensionByNumber(iNumExt: Integer): INeroFileSystemBlockAccessExtension; virtual; cdecl; abstract;
    // Returns specified extension or NULL if not present
    function GetFileExtension(eExtType: NeroFSBlockAccessExtensionsType): INeroFileSystemBlockAccessExtension; virtual; cdecl; abstract;
  end;

implementation

end.

