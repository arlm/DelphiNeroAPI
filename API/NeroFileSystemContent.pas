{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroFileSystemContent.h, released March 2003. The      }
{ original Pascal code is: NeroFileSystemContent.pas, released June 2003. The  }
{ initial developer of the Pascal code is Andreas Hausladen                    }
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

{******************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroFileSystemContent.h
|*
|* PURPOSE: 
|* This is the third NeroAPI interface for preparing data CDs/DVDs. Unlike NeroIsoTrack.h,
|* it is not much "callback based",thus most of the process will be driven by the 
|* application, making it easier to write. This interface is closely connected to the
|* internal engine of NeroAPI, this improves the cooperation of NeroAPI and the application.
|*
|* This set of classes describe the content of the file system of a disc.
|* The application will build a file structure using the IFileSystemContent object. 
|* During the burn process, NeroAPI will request the content of files using the 
|* IFileContent interface.
|*
|* Use the NeroCreateFileSystemContainer function of NeroAPI.h to get an instance of an
|* IFileSystemDescContainer object. Then, use the NERO_WRITE_FILE_SYSTEM_CONTAINER structure 
|* to burn the file structure created.
******************************************************************************}
unit NeroFileSystemContent;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface
uses
  Windows, Types;
  
type
  InterfaceBase = class
  public
    // Get another interface for the same object. This will be used to extend the DLL interface without
    // loosing binary compatibility. Returns NULL if no interface with this ID was found
    // This is inspired from the COM QueryInterface function
    function GetOtherInterface(interfaceId: Integer): Pointer;       overload; virtual; cdecl;  // Using an ID number
    function GetOtherInterface(const interfaceName: PChar): Pointer; overload; virtual; cdecl;  // Using a string
  protected
    procedure DestroyInterface(DeleteMode: Integer = 3);             virtual; cdecl; { 2: stack destroy; 3: dynamic free }
  end;

////////////////////////////////////////////////////////////////////////////////////////
// This first set of interfaces will be used by the burn engine to read the content of
// the file system
////////////////////////////////////////////////////////////////////////////////////////
  IFileContent = class(InterfaceBase)
  public
    function Read(pBuffer: Pointer; length: Cardinal): Cardinal; virtual; cdecl; abstract;
    function EndOfFile(): BOOL;                                  virtual; cdecl; abstract;
    function Error(): BOOL;                                      virtual; cdecl; abstract;

    // Called by the application when the object is not needed anymore
    procedure Release();                                         virtual; cdecl; abstract;
  end;

  ENTRY_ERROR = (
    ENTRY_NO_ERROR,
    SEQUENCING_ERROR,		// The content for this file may not be requested at this moment
    ERROR_NOT_A_FILE,		// This entry is not a file
    NOT_AVAILABLE,			// The content of this file cannot be requested at all
    INTERFACE_ERROR,		// The overriden function has tried to get an other interface for one object and has failed
    FEATURE_NOT_AVAILABLE	// This feature is not available for this file system type
  );

  IDirectoryEntry__Enum = (
    MODE2_FORM2                = 1 shl 0,
    FIXED_INSIDE_VOLUME_SPACE  = 1 shl 1,
    FIXED_OUTSIDE_VOLUME_SPACE = 1 shl 2,
    NO_OWN_CONTENT             = 1 shl 3
  );

  IDirectory = class;

  IDirectoryEntry = class(InterfaceBase)
  public
    function GetName(): PChar;                      virtual; cdecl; abstract; // File or directory name

    function GetSubDirectory(): IDirectory;         virtual; cdecl; abstract;
    function GetContent(var FileContent: IFileContent): ENTRY_ERROR; virtual; cdecl; abstract;
    function GetSourceFilePath(): PChar;            virtual; cdecl; abstract;	// Return the source file path, NULL if the file is generated
    function GetSize(): Int64;                      virtual; cdecl; abstract;
    function GetFilePriority(): Integer;            virtual; cdecl; abstract;
    function GetDirOrder(): Integer;                virtual; cdecl; abstract;
    function GetId(): Integer;                      virtual; cdecl; abstract;	// Id number that can be used to find the file again later
    function GetDataStartSec(): Cardinal;           virtual; cdecl; abstract;
  end;

  IDirectory = class(InterfaceBase)
  public
    function GetNumEntries(): Integer;                       virtual; cdecl; abstract;
    function GetDirectoryEntry(i: Integer): IDirectoryEntry; virtual; cdecl; abstract;
  end;

  IFileSystemContent = class(InterfaceBase)
  public
    function GetName(): PChar;      virtual; cdecl; abstract;      // Volume name
    function GetRoot(): IDirectory; virtual; cdecl; abstract;
  end;


////////////////////////////////////////////////////////////////////////////////////////
// This second set of interfaces will be used by the application to produce the content of
// the file system
////////////////////////////////////////////////////////////////////////////////////////


// Allows the file producer to return the data
  IDataInputStream = class(InterfaceBase)
  public
    procedure Write(const buffer: Pointer; size: Integer); virtual; cdecl; abstract;
  end;

// Produce the content of a file. This interface must be derived and its implementation must
// create the content of the file in the ProduceFile function
  IFileProducer = class(InterfaceBase)
  public
	// Calling this method will automatically update the file size to the amount of data
	// delivered by the producer
    function ProduceFile(str: IDataInputStream): ENTRY_ERROR; virtual; cdecl; abstract;

	// Called by NeroAPI when the object is not needed anymore
    procedure Release(); virtual; cdecl; abstract;
  end;


  IDirectoryContainer = class;

  // This object can be accessed in several ways
  IDirectoryEntryContainer__Enum = (
    IID_IDirectoryEntryContainer,
    IID_IFileProducer,				// If the file entry was created using an IFileProducer
                                      // object, this one can be retrieved using GetOtherInterface
    IID_IDirectoryEntryContainer2,	// Reserved
    IID_IDirectoryEntry2			// Reserved
  );

// Description of a file
  IDirectoryEntryContainer = class(IDirectoryEntry)
  public
	// Using this function, the file size can be changed after having added the entry to the directory
    procedure SetSize(size: Int64);                      virtual; cdecl; abstract;

	// The two functions below can be used to readjust the directory priority
	// Priority numbers will be used in upward order: the file with smaller values first
    procedure SetPriority(priority: Integer);            virtual; cdecl; abstract;
    procedure SetDirOrder(directoryPriority: Integer);   virtual; cdecl; abstract;

	// Set the sector number that will be saved into the directory structure
    procedure SetDataStartSec(num: Cardinal);            virtual; cdecl; abstract;

	// Set the physical position of the file in the filesystem
    procedure SetFixedDataStartSec(position: Cardinal);  virtual; cdecl; abstract;

    procedure SetFileNumber(num: Integer);               virtual; cdecl; abstract;
    procedure SetId(id: Integer);                        virtual; cdecl; abstract;
    procedure SetFlags(enable: BOOL; f: Cardinal);       virtual; cdecl; abstract; // Enable/disable the given flag
  end;

// Extension of the IDirectoryEntryContainer interface
  IDirectoryEntryContainer2 = class(IDirectoryEntryContainer)
  public
	// If the file entry was created using an IFileProducer, returns a pointer on it
    function GetFileProducer(): IFileProducer;           virtual; cdecl; abstract;

	// Update the size attribute of this file by producing its content without writing
	// it anywhere
    function MeasureSize(): ENTRY_ERROR;                 virtual; cdecl; abstract;

	// Set the size that is stored in the media directory record but do not change the
	// size of allocated and requested data
	// This is currently only available for ISO filesystems
    function SetDirRecordSize(size: Int64): ENTRY_ERROR; virtual; cdecl; abstract;
  end;


// Represents the content of a directory
  IDirectoryContainer = class(IDirectory)
  public
	// Add a directory a returns a pointer on it
	// directoryPriority specifies the position in the directory. See this->AddFile
	// for details
    function AddDirectory(const name: PChar; directoryPriority: Integer): IDirectoryContainer; virtual; cdecl; abstract;

  // Add a file the directory. The fp object will be automatically deleted when the directory
	// container will be deleted
	//
	// the filesize passed here does *not* need to be correct, it will be used by the
	// filesystem generator to preallocate space so it must be the *maximum* space the final
	// version of the file may need (worst-case).
	//
	// Priority specifies some user-defined ordinal defining the order in which the files are
	// being written to the disc physically (like .ifo comes before .vob).
	// Priorities are valid across directories
	// The fileentry order in a directory is defined by the directoryPriority parameter which is the primary
	// sort criterium when arranging the files in a directory (Note that this is only true for
	// filesystems that do not require files to be sorted in the directory, e.g. UDF)
	// If any of the priority specifiers is -1, the producer doesn't care about the priority
	// and Nero will put the file where it thinks it fit
	// AddFile will return NULL if a file with the same name already exists
    function AddFile(const name: PChar; const fp: IFileProducer; size: Int64;
      priority: Integer; directoryPriority: Integer): IDirectoryEntryContainer; overload; virtual; cdecl; abstract;

    // Add a file which exists in the real file system
    function AddFile(const name: PChar; const sourcePath: PChar;
                     priority: Integer; directoryPriority: Integer): IDirectoryEntryContainer; overload; virtual; cdecl; abstract;

    // Remove an entry from the directory
    function RemoveEntry(const name: PChar): BOOL;                 virtual; cdecl; abstract;

    function Entry(const name: PChar): IDirectoryEntryContainer;   overload; virtual; cdecl; abstract;
    function Entry(i: Integer): IDirectoryEntryContainer;          overload; virtual; cdecl; abstract;
    function SubDirectory(const name: PChar): IDirectoryContainer; virtual; cdecl; abstract;
  end;


// Represents the content of a file system
  IFileSystemDescContainer = class(IFileSystemContent)
  public
    procedure SetName(const name: PChar); virtual; cdecl; abstract; // Set the volume name of the file system
    function Root(): IDirectoryContainer; virtual; cdecl; abstract;// Access the root directory for changing it

    // Called by the application when the object is not needed anymore
    procedure Release();                  virtual; cdecl; abstract;
  end;

implementation

{ InterfaceBase }

procedure InterfaceBase.DestroyInterface;
begin
 { Because it is an "interface" class this code may never execute. }
  Free;
end;

function InterfaceBase.GetOtherInterface(interfaceId: Integer): Pointer;
begin
  Result := nil; // No other interface available by default
end;

function InterfaceBase.GetOtherInterface(const interfaceName: PChar): Pointer;
begin
  Result := nil; // No other interface available by default
end;

end.
