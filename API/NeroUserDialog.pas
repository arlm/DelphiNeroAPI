{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2004 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroUserDialog.h, released March 2003. The original    }
{ Pascal code is: NeroUserDialog.pas, released June 2003. The initial          }
{ developer of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).  }
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
|* PROGRAM: NeroUserDialog.h
|*
|* PURPOSE: Ask how to proceed by offering the user some choices
******************************************************************************}
unit NeroUserDialog;

{$INCLUDE NeroAPI.inc}

interface

uses
  Windows, Types;

// Take care to use 2^n as values for constants:
const
  AUP_NO_PROBLEM        = 0;         // No problems found
  AUP_FIRST_TR_PAUSE    = 1;         // First track must have 2-3 secs pause!
  AUP_PAUSE_SETTINGS    = 2;         // Problem with audio pause settings (tracks > 1)
  AUP_INDEX_SETTINGS    = 4;         // Problem with audio index settings
  AUP_ISRC_SETTINGS     = 8;         // Problem with ISRC settings
  AUP_COPYPROT_SETTINGS = 16;        // Problem with copyright settings
  AUP_NOTRACK_FOUND     = 32;        // Problem because we don´t have any track
  AUP_MEGA_FATAL        = $FFFFFFFF; // Megafatal internal problem that can´t be fixed!

type
 { enum NeroUserDlgInOutEnum }
  NeroUserDlgInOutEnum = (
    {$IFDEF NERO_6}
  { return codes for DLG_MESSAGEBOX: }
    DLG_RETURN_OK = -8,     { NeroAPI >= 6.0.0.6: ok }
    DLG_RETURN_YES = -7,    { NeroAPI >= 6.0.0.6: yes }
    DLG_RETURN_RETRY = -6,  { NeroAPI >= 6.0.0.6: retry }
    DLG_RETURN_IGNORE = -5, { NeroAPI >= 6.0.0.6: ignore }
    DLG_RETURN_NO = -4,     { NeroAPI >= 6.0.0.6: no }
    DLG_RETURN_CANCEL = -3, { NeroAPI >= 6.0.0.6: cancel }
    DLG_RETURN_ABORT = -2,  { NeroAPI >= 6.0.0.6: abort }

  {
  // NeroAPI >= 6.0.0.6:
  // return this if an enum is not handled by the callback
  }
    DLG_RETURN_NOT_HANDLED = -1,

    {$ENDIF NERO_6}
  { return codes for other dialogs }
    DLG_RETURN_EXIT = 0,   { Exit application / stop writing }
    DLG_RETURN_FALSE = 0,  { false }
    DLG_RETURN_TRUE = 1,   { true }
  {
  "Disconnect is turned off in the system configuration.
   This may cause serious problems while burning: your CD might
   be damaged, or the system might hang up."
  }
    DLG_DISCONNECT         = 2,
    DLG_RETURN_ON_RESTART  = 3, { turn on disconnect and restart windows }
    DLG_RETURN_RESTART     = 4, { Don't change disconnect option and restart windows }
    DLG_RETURN_CONTINUE    = 5, { Continue at your own risk }
    { DLG_RETURN_EXIT }

  { same as DLG_DISCONNECT, but restarting has been selected
     already and must not be canceled, so valid return codes
     are only DLG_RETURN_ON_RESTART and DLG_RETURN_RESTART }
    DLG_DISCONNECT_RESTART = 6,

  {
  "Auto Insert Notification is turned on in the system configuration.
   This may cause serious problems while burning: your CD might be damaged,
   or the system might hang up.

   Nero is able to burn CDs with Auto Insert Notification turned on if all
   necessary drivers are installed."
  }
    DLG_AUTO_INSERT           = 7,
    DLG_RETURN_INSTALL_DRIVER = 8, { Install IO driver which temporarily disables auto insert. }
                                   { Note: this only works if the additional argument for the callback is not NULL,
                                     otherwise it should not be offered to the user. }
    DLG_RETURN_OFF_RESTART    = 9, { Change autoinsert and restart Windows }
    {
    as above:
    DLG_RETURN_EXIT,
    DLG_RETURN_CONTINUE,
    }

  {
  "Please restart Windows now."
  }
    DLG_RESTART               = 10,
    { return code irrelevant }

  {
  "Auto Insert Notification is now OFF. You should restart Windows."
  (displayed after rebooting within program failed and user has to do it manually)
  }
    DLG_AUTO_INSERT_RESTART   = 11,
    { return code irrelevant }

  {
  "Nero detected some modifications of your PC system configuration
   and needs to modify some settings. Please restart your PC to make
   the changes become effective."
  }
    DLG_SETTINGS_RESTART      = 12,
    {
    DLG_RETURN_RESTART,
    DLG_RETURN_CONTINUE,
    }

  {
  "Sorry, this compilation contains too much data to fit on the CD"
   with respect to the normal CD capacity. Do you want to try
   overburn writing at your own risk (this might cause read
   errors at the end of the CD or might even damage your recorder)?"
  "Note: It is also possible, that SCSI/Atapi errors occur at the end
   of the simulation or burning. Even in this case there is a certain
   chance, that the CD is readable."
  }
    DLG_OVERBURN              = 13,
    {
    DLG_RETURN_TRUE/FALSE
    }


  {
  The tracks cannot be written as requested. A detailed
  description of the problem is found in the "data" parameter.
  It is a DWORD of with bits set according to the AUP constants above
  }
    DLG_AUDIO_PROBLEMS        = 14,

    {
    DLG_RETURN_TRUE = fix the problems by adapting the track settings
    DLG_RETURN_FALSE = stop writing
    }


  {
  This dialog type differs slightly from the other ones:
  it should pop up a message and return immediately while still showing
  the message, so that the API can test for the expected CD in the meantime.

  During this time, the NERO_IDLE_CALLBACK will be called to give the
  application a chance to update its display and to test for user abort.
  The API might call call DLG_WAITCD several times to change the text.

  The text depends on the "data" argument that is passed to the
  NERO_USER_DIALOG callback. It is the enumeration NERO_WAITCD_TYPE
  specified below.
  }
    DLG_WAITCD = 15,
  {
  It is time to remind the user of inserting the CD: play a jingle, flash the screen, etc.
  Called only once after a certain amount of time of no CD being inserted.
  }
    DLG_WAITCD_REMINDER = 16,
  {
  Close the message box again, we are done.
  }
    DLG_WAITCD_DONE = 17,
  {
  Tell the user that there will be quality loss during the copy and ask if he wants
  to continue anyway
  }
    DLG_COPY_QUALITY_LOSS = 18,
  {
  PROCEED AT YOUR OWN RISK message
  }
    DLG_COPY_FULLRISK = 19,
  {
  Ask the user the path of the file which will be generated by the Image Recorder.
  The "data" argument points on a 256 bytes buffer that has to be filled with the image path
  Returning DLG_RETURN_EXIT will stop the burn process
  }
    DLG_FILESEL_IMAGE = 20,
  {
  Tell that there is not enough space on disk to produce this image
  }
    DLG_BURNIMAGE_CANCEL = 21,

  {
  Tell the user that the CDRW is not empty
  Starting from NeroAPI 5.5.3.0, the "data" argument contains the device handle from the recorder
  Will be called only if the NBF_DETECT_EMPTY_CDRW flags is given to the NeroBurn function
  Returning DLG_RETURN_EXIT will stop the burn process
  Returning DLG_RETURN_CONTINUE will continue the burn process
  Returning DLG_RETURN_RESTART will ask the user for an other CD
  }
    DLG_NON_EMPTY_CDRW = 22,

  {
  NeroAPI 5.5.3.2: tell the user that the compilation cannot be written on that particular
  recorder and that the user shoud modify his compilation settings or burn the CD on
  another recorder, that supports the required medium type
  }
    DLG_COMP_REC_CONFLICT = 23,

  {
  NeroAPI 5.5.3.2: another type of medium must be used to burn this compilation
  }
    DLG_WRONG_MEDIUM = 24,
  {* Implementation of the DLG_ROBO_MOVECD dialog types must behave
   * like the DLG_WAITCD type, that is, operate in a non-blocking way.
   * The data structure passed to this callback is specified as
   * ROBOMOVEMESSAGE below }
    DLG_ROBO_MOVECD = 25,
  {* Destroy a MoveCD dialog. (void*)data cast to an int will contain the
   * id of the MoveCD dialog to be removed }
    DLG_ROBO_MOVECD_DONE = 26,

  {* Show dialog message transmitted by the Robo driver.
   * Must return one of the constants below.
   * The data structure passed as the data pointer is specified as
   * ROBOUSERMESSAGE below.
   * Return DLG_RETURN_FALSE or DLG_RETURN_TRUE here }
    DLG_ROBO_USERMESSAGE = 27,

  {* Provide informations about which media is expected and which media is
   * currently present in the recorder.
     The data pointer passed is a pointer on the NERO_DLG_WAITCD_MEDIA_INFO structure
     declared in NeroAPI.h.
     The value returned is ignored}
    DLG_WAITCD_MEDIA_INFO = 28,

    {$IFDEF NERO_6}
    {* NeroAPI >= 6.0.0.6:
     * Open a custom messagebox dialog. The type and the message of the dialog are described
     * with a struct NERODLG_MESSAGEBOX which is given as data pointer.
     * See comments for NERODLG_MESSAGE_TYPE which values to return.
     *}
    DLG_MESSAGEBOX = 29,
    {$ENDIF NERO_6}

    DLG_MAX
  );
  NeroUserDlgInOut = NeroUserDlgInOutEnum;
  TNeroUserDlgInOut = NeroUserDlgInOut;


{$IFDEF NERO_6}
  { NeroAPI >= 6.0.0.6 }
  NERODLG_ICON_TYPE = (
    NDIT_INFO     = 0, { an info icon }
    NDIT_WARNING  = 1, { a warning icon }
    NDIT_ERROR    = 2, { an error icon }
    NDIT_QUESTION = 3  { a question icon }
  );

  { NeroAPI >= 6.0.0.6 }
  NERODLG_MESSAGE_TYPE = (
    { An info dialog with only an OK button. The return value is ignored. }
    NDMT_OK = 0,

    { A dialog with a yes and a no button. Return DLG_RETURN_YES for Yes
      and DLG_RETURN_NO for No. }
    NDMT_YESNO = 1,

    { A dialog with a ok and a cancel button. Return DLG_RETURN_OK for OK
      and DLG_RETURN_CANCEL for Cancel. }
    NDMT_OKCANCEL = 2,

    { A dialog with a retry and a cancel button. Return DLG_RETURN_RETRY
      for Retry and DLG_RETURN_CANCEL for Cancel. }
    NDMT_RETRYCANCEL = 3,

    { A dialog with a abort, a retry and a ignore button.
      Return DLG_RETURN_IGNORE for Ignore, DLG_RETURN_RETRY for Retry
      and DLG_RETURN_ABORT for Abort. }
    NDMT_ABORTRETRYIGNORE = 4,

    { A dialog with a yes, a no and a cancel button.
      Return DLG_RETURN_YES for Yes, DLG_RETURN_NO for No
      and DLG_RETURN_CANCEL for Cancel. }
    NDMT_YESNOCANCEL = 5
  );

  { NeroAPI >= 6.0.0.6 }
  tag_NERODLG_MESSAGEBOX = record
    typ: NERODLG_MESSAGE_TYPE;       { the type of the message, see DLG_MESSAGE_TYPE }
    icon: NERODLG_ICON_TYPE;         { the icon for the message, see DLG_ICON_TYPE }
    defaultReturn: NeroUserDlgInOut; { the default return value }
    message: PChar;                  { the message to display }
  end;
  NERODLG_MESSAGEBOX = tag_NERODLG_MESSAGEBOX;
  PNERODLG_MESSAGEBOX = ^NERODLG_MESSAGEBOX;
  TNeroDlgMessageBox = NERODLG_MESSAGEBOX;
  PNeroDlgMessageBox = PNERODLG_MESSAGEBOX;
{$ENDIF NERO_6}

 { enum ROBOUSERMESSAGETYPE }
  tag_ROBOUSERMESSAGETYPE = (
    RUMT_ERROR,
    RUMT_WARNING,
    RUMT_QUESTION,
    RUMT_HINT
  );
  ROBOUSERMESSAGETYPE = tag_ROBOUSERMESSAGETYPE;
  PROBOUSERMESSAGETYPE = ^ROBOUSERMESSAGETYPE;
  TRoboUserMessageType = ROBOUSERMESSAGETYPE;

 { struct ROBOUSERMESSAGETYPE }
  tag_ROBOUSERMESSAGE = record
    message_type: ROBOUSERMESSAGETYPE; // The type of message, see constants above */
    message: PChar;
  end;
  ROBOUSERMESSAGE = tag_ROBOUSERMESSAGE;
  PROBOUSERMESSAGE = ^ROBOUSERMESSAGE;
  TRoboUserMessage = ROBOUSERMESSAGE;

 { enum ROBOMOVENODE }
  ROBOMOVENODE = (
    RMN_INPUT,
    RMN_RECORDER,
    RMN_OUTPUT,
    RMN_PRINTER,
    RMN_WASTEBIN
  );
  TRoboMoveNode = ROBOMOVENODE;

{$IFDEF NERO_6}
// NeroAPI >= 6.0.0.27: Additional information when DLG_OVERBURN is called
  tag_DLG_OVERBURN_INFO = record
    dwTotalBlocksOnCD: DWORD;            // total blocks to be written to disc
    dwTotalCapacity: DWORD;              // free capacity on disc in blocks
    reserved: array[0..32 - 1] of DWORD; // reserved for future usage
  end;
  DLG_OVERBURN_INFO = tag_DLG_OVERBURN_INFO;
  PDLG_OVERBURN_INFO = ^DLG_OVERBURN_INFO;
  TDlgOverburnInfo = DLG_OVERBURN_INFO;
  PDlgOverburnInfo = PDLG_OVERBURN_INFO;
{$ENDIF NERO_6}

 { struct ROBOMOVEMESSAGE }
  tag_ROBOMOVEMESSAGE = record
    id: Integer; {* In future versions, we may have more than one Robo moving
                  * at a time. So this ID identifies the movement action
                  * and will be used to remove it with DLG_ROBO_MOVECD_DONE }
    source: ROBOMOVENODE;
    destination: ROBOMOVENODE;
  end;
  ROBOMOVEMESSAGE = tag_ROBOMOVEMESSAGE;
  PROBOMOVEMESSAGE = ^ROBOMOVEMESSAGE;
  TRoboMoveMessage = ROBOMOVEMESSAGE;

{
// This function gets a requester type and shall return a suitable response to it.
// Depending on the "type", "data" might contain additional information.
//
// Argument passing is in standard C order (on the stack, right to left),
// aka MS Visual++ __cdecl.
}


// typedef NeroUserDlgInOut (NERO_CALLBACK_ATTR *NERO_USER_DIALOG) (void *pUserData, NeroUserDlgInOut type, void *data);
  NERO_USER_DIALOG = function(pUserData: Pointer; _type: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;
  TNeroUserDialogCallback = NERO_USER_DIALOG;

{
// see below for a description of the enumeration values
}
 { enum NERO_WAITCD_TYPE }
  NERO_WAITCD_TYPE = (
    NERO_WAITCD_WRITE,
    NERO_WAITCD_SIMULATION,
    NERO_WAITCD_AUTOEJECTLOAD,
    NERO_WAITCD_REINSERT,
    NERO_WAITCD_NEXTCD,
    NERO_WAITCD_ORIGINAL,
    NERO_WAITCD_WRITEPROTECTED,
    NERO_WAITCD_NOTENOUGHSPACE,
    NERO_WAITCD_NEWORIGINAL,
    NERO_WAITCD_EMPTYCD,
    NERO_WAITCD_WRITE_EMPTY,
    NERO_WAITCD_SIMULATION_EMPTY,
    NERO_WAITCD_WRITEWAVE,
    NERO_WAITCD_MULTISESSION,
    NERO_WAITCD_MULTISESSION_SIM,
    NERO_WAITCD_MULTI_REINSERT,
    NERO_WAITCD_DISCINFOS_FAILED,
    NERO_WAITCD_MEDIUM_UNSUPPORTED,
    NERO_WAITCD_AUTOEJECTLOAD_VER,
    NERO_WAITCD_REINSERT_VER,
    NERO_WAITCD_NOFORMAT,
    NERO_WAITCD_WRONG_MEDIUM,  // NeroAPI>=5.5.5.6
    NERO_WAITCD_WAITING,       // NeroAPI>=5.5.10.26
    {$IFDEF NERO_6}
    NERO_WAITCD_EMPTYCDRW,          // NeroAPI>=6.0.0.20
    NERO_WAITCD_NOTENOUGHSPACERW,   // NeroAPI>=6.0.0.20
    NERO_WAITCD_NOTENOUGHSPACE_80MIN,
    {$ENDIF NERO_6}
    NERO_WAITCD_MAX
  );
  TNeroWaitCDType = NERO_WAITCD_TYPE;

{ If NeroAPI>=5.5.9.10 is present, it is recommanded to use NeroGetLocalizedWaitCDTexts instead since it
   returns a localized string }
function NeroGetWaitCDTexts(_type: NERO_WAITCD_TYPE): PChar;

implementation

function NeroGetWaitCDTexts(_type: NERO_WAITCD_TYPE): PChar;
const
  mapping: array[NERO_WAITCD_TYPE] of record
                                        _type: NERO_WAITCD_TYPE;
                                        text: PChar;
                                      end = (
    (_type: NERO_WAITCD_WRITE;              text: 'Please insert the disc to write to...'),
    (_type: NERO_WAITCD_SIMULATION;         text: 'Please insert a disc to use during simulation...\n\n(Nothing will be written on the disc.)'),
    (_type: NERO_WAITCD_AUTOEJECTLOAD;      text: 'Please do not remove the disc!\n\nYour recorder requires this eject between simulation and burning. The disc will be reloaded automatically before continuing with burning...'),
    (_type: NERO_WAITCD_REINSERT;           text: 'Please do not remove the disc!\n\nYour recorder requires this eject between simulation and burning. Please reinsert the disc...'),
    (_type: NERO_WAITCD_NEXTCD;             text: 'Please remove the disc and  insert the next disc-Recordable to write to... '),
    (_type: NERO_WAITCD_ORIGINAL;           text: 'Please insert the original disc.'),
    (_type: NERO_WAITCD_WRITEPROTECTED;     text: 'This disc is not writable.\n\nPlease insert a writable disc...'),
    (_type: NERO_WAITCD_NOTENOUGHSPACE;     text: 'There is not enough space to burn this compilation onto this disc.\n\nPlease insert another disc that provides more space...'),
    (_type: NERO_WAITCD_NEWORIGINAL;        text: 'The disc is blank, invalid\nor a multisession disc.\n\nPlease insert original disc ...'),
    (_type: NERO_WAITCD_EMPTYCD;            text: 'The disc is not empty.\n\nPlease insert an empty disc.'),
    (_type: NERO_WAITCD_WRITE_EMPTY;        text: 'Please insert an empty disc to write to...'),
    (_type: NERO_WAITCD_SIMULATION_EMPTY;   text: 'Please insert an empty disc to use during simulation...\n\n(Nothing will be written on the disc.)'),
    (_type: NERO_WAITCD_WRITEWAVE;          text: 'The disc is blank.\n\nPlease insert original disc...'),
    (_type: NERO_WAITCD_MULTISESSION;       text: 'Nero is checking for the disc, please wait ...\n\nTo burn this multisession compilation you need the disc, that  contains the previous backup sessions. Please insert this disc if you haven''t done it before.'),
    (_type: NERO_WAITCD_MULTISESSION_SIM;   text: 'To simulate this multisession compilation you need the disc, that contains the previous backup sessions. Please insert this disc. (Nothing will be written on disc).'),
    (_type: NERO_WAITCD_MULTI_REINSERT;     text: 'Please do not remove the disc!\n\nYour recorder requires this eject between simulation and burning. Please reinsert the\n same Multisession disc...'),
    (_type: NERO_WAITCD_DISCINFOS_FAILED;   text: 'Disc analysis failed. The error log\ncontains more information about the reason.'),
    (_type: NERO_WAITCD_MEDIUM_UNSUPPORTED; text: 'The recorder does not support this type of media!\n\nPlease insert a correct disc to write to...'),
    (_type: NERO_WAITCD_AUTOEJECTLOAD_VER;  text: 'Please do not remove the disc!\n\nYour recorder requires that the  disc be ejected between burning and verification. The disc will be reloaded automatically when burning is to continue...'),
    (_type: NERO_WAITCD_REINSERT_VER;       text: 'Please do not remove the disc!\n\nYour recorder requires that the  disc be ejected between burning and verification.  Please reinsert the disc....'),
    (_type: NERO_WAITCD_NOFORMAT;           text: 'Medium is not formatted. Please insert a formatted medium.'),
    (_type: NERO_WAITCD_WRONG_MEDIUM;       text: 'Sorry, your compilation cannot be written on this kind of medium. Please insert a medium of the correct type or modify the settings of your compilation to make them compatible with the current medium.'),
    (_type: NERO_WAITCD_WAITING;            text: '--- Accessing disc, please wait ---'),
    {$IFDEF NERO_6}
    (_type: NERO_WAITCD_EMPTYCDRW;          text: 'The disc is not empty.'),
    (_type: NERO_WAITCD_NOTENOUGHSPACERW;   text: 'There is not enough space to burn the compilation onto this disc.'),
    (_type: NERO_WAITCD_NOTENOUGHSPACE_80MIN; text: 'There is not enough space to burn the compilation onto this disc.\n\nPlease insert a 80min/700MB media'),
    {$ENDIF NERO_6}
    (_type: NERO_WAITCD_MAX;                text: 'unknown NERO_WAITCD_TYPE')
  );
var
  T: NERO_WAITCD_TYPE;
  I: Integer;
begin
  T := NERO_WAITCD_WRITE;
  while (mapping[T]._type <> _type) and (mapping[T]._type <> NERO_WAITCD_MAX) do
    Inc(T);

  Assert(mapping[T]._type <> NERO_WAITCD_MAX);
  Result := mapping[T].text;
  for I := 1 to Length(Result) do
    if (Result[I] = '\') and (Result[I + 1] = 'n') then
    begin
      Result[I] := #10;
      Result[I + 1] := #13;
    end;
end;


end.
