{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroUserDialog.h, released March 2003. The original    }
{ Pascal code is: NeroUserDialog.pas, released June 2003. The initial          }
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
|* PROGRAM: NeroUserDialog.h
|*
|* PURPOSE: Ask how to proceed by offering the user some choices
******************************************************************************}
unit NeroUserDialog;
{$ALIGN 8}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

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
  { default return codes: }
    DLG_RETURN_EXIT = 0,   { Exit application / stop writing }
    DLG_RETURN_FALSE = 0,  { false/no }
    DLG_RETURN_TRUE = 1,   { true/yes }
  {
  "Disconnect is turned off in the system configuration.
   This may cause serious problems while burning: your CD might
   be damaged, or the system might hang up."
  }
    DLG_DISCONNECT,
    DLG_RETURN_ON_RESTART, { turn on disconnect and restart windows }
    DLG_RETURN_RESTART,    { Don't change disconnect option and restart windows }
    DLG_RETURN_CONTINUE,   { Continue at your own risk }
    { DLG_RETURN_EXIT }

  { same as DLG_DISCONNECT, but restarting has been selected
     already and must not be canceled, so valid return codes
     are only DLG_RETURN_ON_RESTART and DLG_RETURN_RESTART }
    DLG_DISCONNECT_RESTART,

  {
  "Auto Insert Notification is turned on in the system configuration.
   This may cause serious problems while burning: your CD might be damaged,
   or the system might hang up.

   Nero is able to burn CDs with Auto Insert Notification turned on if all
   necessary drivers are installed."
  }
    DLG_AUTO_INSERT,
    DLG_RETURN_INSTALL_DRIVER, { Install IO driver which temporarily disables auto insert. }
                               { Note: this only works if the additional argument for the callback is not NULL,
                            otherwise it should not be offered to the user. }
    DLG_RETURN_OFF_RESTART,    { Change autoinsert and restart Windows }
    {
    as above:
    DLG_RETURN_EXIT,
    DLG_RETURN_CONTINUE,
    }

  {
  "Please restart Windows now."
  }
    DLG_RESTART,
    { return code irrelevant }

  {
  "Auto Insert Notification is now OFF. You should restart Windows."
  (displayed after rebooting within program failed and user has to do it manually)
  }
    DLG_AUTO_INSERT_RESTART,
    { return code irrelevant }

  {
  "Nero detected some modifications of your PC system configuration
   and needs to modify some settings. Please restart your PC to make
   the changes become effective."
  }
    DLG_SETTINGS_RESTART,
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
    DLG_OVERBURN,
    {
    DLG_RETURN_TRUE/FALSE
    }


  {
  The tracks cannot be written as requested. A detailed
  description of the problem is found in the "data" parameter.
  It is a DWORD of with bits set according to the AUP constants above
  }
    DLG_AUDIO_PROBLEMS,

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
    DLG_WAITCD,
  {
  It is time to remind the user of inserting the CD: play a jingle, flash the screen, etc.
  Called only once after a certain amount of time of no CD being inserted.
  }
    DLG_WAITCD_REMINDER,
  {
  Close the message box again, we are done.
  }
    DLG_WAITCD_DONE,
  {
  Tell the user that there will be quality loss during the copy and ask if he wants
  to continue anyway
  }
    DLG_COPY_QUALITY_LOSS,
  {
  PROCEED AT YOUR OWN RISK message
  }
    DLG_COPY_FULLRISK,
  {
  Ask the user the path of the file which will be generated by the Image Recorder.
  The "data" argument points on a 256 bytes buffer that has to be filled with the image path
  Returning DLG_RETURN_EXIT will stop the burn process
  }
    DLG_FILESEL_IMAGE,
  {
  Tell that there is not enough space on disk to produce this image
  }
    DLG_BURNIMAGE_CANCEL,

  {
  Tell the user that the CDRW is not empty
  Starting from NeroAPI 5.5.3.0, the "data" argument contains the device handle from the recorder
  Will be called only if the NBF_DETECT_EMPTY_CDRW flags is given to the NeroBurn function
  Returning DLG_RETURN_EXIT will stop the burn process
  Returning DLG_RETURN_CONTINUE will continue the burn process
  Returning DLG_RETURN_RESTART will ask the user for an other CD
  }
    DLG_NON_EMPTY_CDRW,

  {
  NeroAPI 5.5.3.2: tell the user that the compilation cannot be written on that particular
  recorder and that the user shoud modify his compilation settings or burn the CD on
  another recorder, that supports the required medium type
  }
    DLG_COMP_REC_CONFLICT,

  {
  NeroAPI 5.5.3.2: another type of medium must be used to burn this compilation
  }
    DLG_WRONG_MEDIUM,
  {* Implementation of the DLG_ROBO_MOVECD dialog types must behave
   * like the DLG_WAITCD type, that is, operate in a non-blocking way.
   * The data structure passed to this callback is specified as
   * ROBOMOVEMESSAGE below }
    DLG_ROBO_MOVECD,
  {* Destroy a MoveCD dialog. (void*)data cast to an int will contain the
   * id of the MoveCD dialog to be removed }
    DLG_ROBO_MOVECD_DONE,

  {* Show dialog message transmitted by the Robo driver.
   * Must return one of the constants below.
   * The data structure passed as the data pointer is specified as
   * ROBOUSERMESSAGE below.
   * Return DLG_RETURN_FALSE or DLG_RETURN_TRUE here }
    DLG_ROBO_USERMESSAGE,

  {* Provide informations about which media is expected and which media is
   * currently present in the recorder.
     The data pointer passed is a pointer on the NERO_DLG_WAITCD_MEDIA_INFO structure
     declared in NeroAPI.h.
     The value returned is ignored}
    DLG_WAITCD_MEDIA_INFO,

    DLG_MAX
  );
  NeroUserDlgInOut = NeroUserDlgInOutEnum;
  TNeroUserDlgInOut = NeroUserDlgInOut;


 { enum ROBOUSERMESSAGETYPE }
  ROBOUSERMESSAGETYPE = (
    RUMT_ERROR,
    RUMT_WARNING,
    RUMT_QUESTION,
    RUMT_HINT
  );
  TRoboUserMessageType = ROBOUSERMESSAGETYPE;

 { struct ROBOUSERMESSAGETYPE }
  ROBOUSERMESSAGE = record
    message_type: ROBOUSERMESSAGETYPE; // The type of message, see constants above */
    message: PChar;
  end;
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

 { struct ROBOMOVEMESSAGE }
  ROBOMOVEMESSAGE = record
    id: Integer; {* In future versions, we may have more than one Robo moving
	              * at a time. So this ID identifies the movement action
                  * and will be used to remove it with DLG_ROBO_MOVECD_DONE }
    source: ROBOMOVENODE;
    destination: ROBOMOVENODE;
  end;
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
    NERO_WAITCD_WRONG_MEDIUM,		// NeroAPI>=5.5.5.6
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
    (_type: NERO_WAITCD_WRITE;              text: 'Please insert the CD to write to...'),
    (_type: NERO_WAITCD_SIMULATION;         text: 'Please insert a CD to use during simulation...\n\n(Nothing will be written on the CD.)'),
    (_type: NERO_WAITCD_AUTOEJECTLOAD;      text: 'Please do not remove the CD!\n\nYour recorder requires this eject between simulation and burning. The CD will be reloaded automatically before continuing with burning...'),
    (_type: NERO_WAITCD_REINSERT;           text: 'Please do not remove the CD!\n\nYour recorder requires this eject between simulation and burning. Please reinsert the CD...'),
    (_type: NERO_WAITCD_NEXTCD;             text: 'Please remove the CD and  insert the next CD-Recordable to write to... '),
    (_type: NERO_WAITCD_ORIGINAL;           text: 'Please insert the original CD.'),
    (_type: NERO_WAITCD_WRITEPROTECTED;     text: 'This CD is not writable.\n\nPlease insert a writable CD...'),
    (_type: NERO_WAITCD_NOTENOUGHSPACE;     text: 'There is not enough space to burn this compilation onto this CD.\n\nPlease insert another CD that provides more space...'),
    (_type: NERO_WAITCD_NEWORIGINAL;        text: 'The CD is blank, invalid\nor a multisession CD.\n\nPlease insert original CD ...'),
    (_type: NERO_WAITCD_EMPTYCD;            text: 'The CD is not empty.\n\nPlease insert an empty CD.'),
    (_type: NERO_WAITCD_WRITE_EMPTY;        text: 'Please insert an empty CD to write to...'),
    (_type: NERO_WAITCD_SIMULATION_EMPTY;   text: 'Please insert an empty CD to use during simulation...\n\n(Nothing will be written on the CD.)'),
    (_type: NERO_WAITCD_WRITEWAVE;          text: 'The CD is blank.\n\nPlease insert original CD...'),
    (_type: NERO_WAITCD_MULTISESSION;       text: 'Nero is checking for the CD, please wait ...\n\nTo burn this multisession compilation you need the CD, that  contains the previous backup sessions. Please insert this CD if you haven''t done it before.'),
    (_type: NERO_WAITCD_MULTISESSION_SIM;   text: 'To simulate this multisession compilation you need the CD, that contains the previous backup sessions. Please insert this CD. (Nothing will be written on CD).'),
    (_type: NERO_WAITCD_MULTI_REINSERT;     text: 'Please do not remove the CD!\n\nYour recorder requires this eject between simulation and burning. Please reinsert the\n same Multisession CD...'),
    (_type: NERO_WAITCD_DISCINFOS_FAILED;   text: 'Disc analysis failed. The error log\ncontains more information about the reason.'),
    (_type: NERO_WAITCD_MEDIUM_UNSUPPORTED; text: 'The recorder does not support this type of media!\n\nPlease insert a correct CD to write to...'),
    (_type: NERO_WAITCD_AUTOEJECTLOAD_VER;  text: 'Please do not remove the CD!\n\nYour recorder requires that the  CD be ejected between burning and verification. The CD will be reloaded automatically when burning is to continue...'),
    (_type: NERO_WAITCD_REINSERT_VER;       text: 'Please do not remove the CD!\n\nYour recorder requires that the  CD be ejected between burning and verification.  Please reinsert the CD....'),
    (_type: NERO_WAITCD_NOFORMAT;           text: 'Medium is not formatted. Please insert a formatted medium.'),
    (_type: NERO_WAITCD_WRONG_MEDIUM;       text: 'Sorry, your compilation cannot be written on this kind of medium. Please insert a medium of the correct type or modify the settings of your compilation to make them compatible with the current medium.'),
    (_type: NERO_WAITCD_MAX;                text: 'unknown NERO_WAITCD_TYPE')
  );
var i: NERO_WAITCD_TYPE;
begin
  i := NERO_WAITCD_WRITE;
  while (mapping[i]._type <> _type) and (mapping[i]._type <> NERO_WAITCD_MAX) do
    Inc(i);

  Assert(mapping[i]._type <> NERO_WAITCD_MAX);
  Result := mapping[i].text;
end;


end.
