{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroAPI.h/NeroAPIGlue.h, released March 2003. The      }
{ original Pascal code is: NeroAPI.pas, released June 2003. The initial        }
{ developer of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).  }
{                                                                              }
{ Portions created by Alexandre Rocha Lima e Marcondes are Copyright (C) 2003  }
{ Alexandre Rocha Lima e Marcondes . All Rights Reserved.                      }
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
|* CREATOR: Alexandre Rocha Lima e Marcondes
|*
******************************************************************************}

{******************************************************************************
|* DelphiNeroAPI
|*
|* PURPOSE: Test functions DelphiNeroAPI components
******************************************************************************}
unit MainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, NeroAPI, NeroUserDialog, NeroIsoTrack, ComCtrls, StdCtrls, AppEvnts,
  ExtCtrls, ShellAPI, ShellCtrls, dnapiComponents;

type
  TFMainForm = class(TForm)
    sbMain: TStatusBar;
    ApplicationEvents: TApplicationEvents;
    gbDevices: TGroupBox;
    btnMoreDevice: TButton;
    lbWriteSpeeds: TLabel;
    gbMedia: TGroupBox;
    stMedia: TStaticText;
    btnRefresh: TButton;
    btnMoreMedia: TButton;
    lbFreeBlocks: TLabel;
    lbTracks: TLabel;
    btnErase: TButton;
    btnEject: TButton;
    btnQuickErase: TButton;
    pcWrite: TPageControl;
    tsISO: TTabSheet;
    tsAudio: TTabSheet;
    tsFreeStyle: TTabSheet;
    tsVCD: TTabSheet;
    tsImage: TTabSheet;
    lbxCDDATracks: TListBox;
    lbCDDATracks: TLabel;
    tsAbout: TTabSheet;
    btnLoad: TButton;
    lbInstructions03: TLabel;
    lbInstructions02: TLabel;
    lbInstructions01: TLabel;
    lbInstructions0: TLabel;
    lbInstructions04: TLabel;
    lbInstructions05: TLabel;
    lbInstructions06: TLabel;
    lbCDDAArtist: TLabel;
    lbCDDATitle: TLabel;
    edCDDAArtist: TEdit;
    edCDDATitle: TEdit;
    btnBurnCDDA: TButton;
    gbSettings: TGroupBox;
    cbxSimulateBurn: TCheckBox;
    cbxTestSpeed: TCheckBox;
    cbxVerifyData: TCheckBox;
    cbxEjectCD: TCheckBox;
    cbxBufferUnderrun: TCheckBox;
    lbDeviceName: TLabel;
    cbxCloseSession: TCheckBox;
    cbWritingMethod: TComboBox;
    lbWritingMethod: TLabel;
    lbxVCDTracks: TListBox;
    pcVCD: TPageControl;
    tsVCDTemp: TTabSheet;
    tsVCDIsoTrack: TTabSheet;
    stvVCDTemp: TShellTreeView;
    pcdVCDOptions: TTabSheet;
    rgType: TRadioGroup;
    lbVCDTracks: TLabel;
    lbImageName: TLabel;
    edImageName: TEdit;
    btnBurnImage: TButton;
    btnSVCDBurn: TButton;
    lbVersion0: TLabel;
    lbVersion01: TLabel;
    lbFileFormats0: TLabel;
    lbFIleFormats01: TLabel;
    tvISO: TTreeView;
    pnISO: TPanel;
    btnBurnISOCD: TButton;
    lvISO: TListView;
    sISO: TSplitter;
    edCDROMTrackName: TEdit;
    cbxCDROMISOFS: TCheckBox;
    cbxCDROMUDFFS: TCheckBox;
    cbxCDROMJoliet: TCheckBox;
    cbxCDROMRockridge: TCheckBox;
    lbCDROMTrackName: TLabel;
    cbxCDROMMode2: TCheckBox;
    cbxCDROMUseAllSpace: TCheckBox;
    cbxCDROMDVDVideoRealloc: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ApplicationEventsShowHint(var HintStr: string;
      var CanShow: Boolean; var HintInfo: THintInfo);
    procedure btnMoreDeviceClick(Sender: TObject);
    procedure btnRefreshClick(Sender: TObject);
    procedure btnMoreMediaClick(Sender: TObject);
    procedure btnEraseClick(Sender: TObject);
    procedure btnEjectClick(Sender: TObject);
    procedure btnQuickEraseClick(Sender: TObject);
    procedure btnLoadClick(Sender: TObject);
    procedure pcWriteChange(Sender: TObject);
    procedure edCDDAArtistChange(Sender: TObject);
    procedure edCDDATitleChange(Sender: TObject);
    procedure btnBurnCDDAClick(Sender: TObject);
    procedure rgTypeClick(Sender: TObject);
    procedure stvVCDTempClick(Sender: TObject);
    procedure btnBurnImageClick(Sender: TObject);
    procedure btnBurnISOCDClick(Sender: TObject);
    procedure btnSVCDBurnClick(Sender: TObject);
    procedure dnapiSettingsError(Sender: TObject; Message: string);
    procedure dnapiDevicesChange(Sender: TObject);
    procedure dnapiDevicesCloseUp(Sender: TObject);
  private
    { Private declarations }
  protected
    procedure WMDropFiles(var msg : TWMDropFiles); message WM_DROPFILES;
    procedure FreeIsoItem(var item: PNeroIsoItem);
    procedure AddFileToRootIsoItem(var RootItem: PNeroIsoItem; FileName: string);


  public
    NeroIsoTrack: CNeroIsoTrack;
    RootIsoItem: PNeroIsoItem;

    NeroProgress: NERO_PROGRESS;
    NeroCDInfo: PNeroCDInfo;
    NeroWriteCD: PNeroWriteCD;
    NeroWriteVideoCD: PNeroWriteVideoCD;
    NeroWriteFreestyleCD: PNeroWriteFreestyleCD;
    NeroWriteImage: PNeroWriteImage;

    procedure NeroError(Action: string);
  end;

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;

function ProgressCallback(pUserData: Pointer; dwProgressInPercent: DWORD): BOOL; cdecl;
function AbortedCallback(pUserData: Pointer): BOOL; cdecl;
procedure AddLogLine(pUserData: Pointer; _type: NERO_TEXT_TYPE; text: PChar); cdecl;
procedure SetPhaseCallback(pUserData: Pointer; text: PChar); cdecl;
procedure DisableAbortCallback(pUserData: Pointer; abortEnabled: BOOL); cdecl;
procedure SetMajorPhaseCallback(pUserData: Pointer; phase: NERO_MAJOR_PHASE; reserved: PVoid); cdecl;

function WriteIOCallback(pUserData: Pointer; pBuffer: PByte; dwLen: DWORD): DWORD; cdecl;
function ReadIOCallback(pUserData: Pointer; pBuffer: PByte; dwLen: DWORD): DWORD; cdecl;
function EOFCallback(pUserData: Pointer): BOOL; cdecl;
function ErrorCallback(pUserData: Pointer): BOOL; cdecl;

var
  FMainForm: TFMainForm;

implementation

uses DeviceDetails, Registry, MediaInformation, DateUtils;

{$R *.dfm}

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
begin
  Application.ProcessMessages;

  Result := False;
end;

function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;
var
  sBuffer: string;
  pacBuffer: PAnsiChar;
begin
  Result := DLG_MAX;

  case Dtype of
    DLG_AUTO_INSERT:
    begin
{ TODO : UserDialog: Auto insert dialog }
{
				static const CResponse mapping[] =
          "Install drivers & restart", DLG_RETURN_INSTALL_DRIVER,
					"Turn off & restart", DLG_RETURN_OFF_RESTART,
					"Exit", DLG_RETURN_EXIT,
					"Continue at own risk", DLG_RETURN_CONTINUE,
					NULL

				puts ("Auto Insert Notification is turned on in the system configuration.\n"
					"This may cause serious problems while burning: your CD might be damaged,\n"
					"or the system might hang up.\n"
					"\n"
					"Nero is able to burn CDs with Auto Insert Notification turned on if all\n"
					"necessary drivers are installed.\n"
					"\n"
					"You can do the following:\n"
					"Install drivers and restart Windows\n"
					"Turn off Auto Insert Notification and restart Windows\n"
					"Exit Nero\n"
					"Continue at your own risk\n");
}
      Result := DLG_RETURN_INSTALL_DRIVER;
    end;
		DLG_DISCONNECT_RESTART:
    begin
{ TODO : UserDialog: Disconnect and Restart dialog }
{
				puts ("Disconnect is turned off in the system configuration.\n"
					"This may cause serious problems while burning: your CD\n"
					"might be damaged, or the system might hang up.\n");

					static const CResponse mapping[] =
						"Turn on & restart", DLG_RETURN_ON_RESTART,
						"Don't turn on & restart\n", DLG_RETURN_RESTART,
						NULL
}
      Result := DLG_RETURN_ON_RESTART;
    end;
		DLG_DISCONNECT:
    begin
{ TODO : UserDialog: Disconnect dialog }
{
				puts ("Disconnect is turned off in the system configuration.\n"
					"This may cause serious problems while burning: your CD\n"
					"might be damaged, or the system might hang up.\n");

					static const CResponse mapping[] =
						"Turn on & restart", DLG_RETURN_ON_RESTART,
						"Don't turn on & restart", DLG_RETURN_RESTART,
						"Continue at own risk", DLG_RETURN_CONTINUE,
						NULL
}
      Result := DLG_RETURN_ON_RESTART;
    end;
		DLG_AUTO_INSERT_RESTART:
    begin
      MessageDlg('Auto Insert Notification is now OFF. ' + #13#10 +
        'You should restart Windows.' + #13#10, mtInformation, [mbOK], 0);

			Result := DLG_RETURN_EXIT;
    end;
		DLG_RESTART:
    begin
      MessageDlg('Please restart Windows now.' + #13#10, mtInformation, [mbOK], 0);

			Result := DLG_RETURN_EXIT;
    end;
		DLG_SETTINGS_RESTART:
    begin
{ TODO : UserDialog: Settings and Restart dialog }
{
				static const CResponse mapping[] =
					"Restart", DLG_RETURN_RESTART,
					"Continue at own risk", DLG_RETURN_CONTINUE,
					NULL

				puts ("Nero detected some modifications of your PC system configuration\n"
					"and needs to modify some settings. Please restart your PC to make\n"
					"the changes become effective.\n");
}
      Result := DLG_RETURN_RESTART;
    end;
		DLG_OVERBURN:
    begin
      if MessageDlg('Sorry, this compilation contains too much data to fit on the CD' + #13#10 +
				'with respect to the normal CD capacity. Do you want to try' + #13#10 +
				'overburn writing at your own risk (this might cause read' + #13#10 +
				'errors at the end of the CD or might even damage your recorder)?' + #13#10#13#10 +
				'Note: It is also possible, that SCSI/Atapi errors occur at the end' + #13#10 +
				'of the simulation or burning. Even in this case there is a certain' + #13#10 +
				'chance, that the CD is readable.' + #13#10, mtWarning, [mbYes,mbNo], 0) = mrYes then
      begin
        Result := DLG_RETURN_TRUE;
      end
      else
      begin
        Result := DLG_RETURN_FALSE;
      end;
    end;
		DLG_COPY_QUALITY_LOSS:
    begin
      if MessageDlg('Disc must be written as "track at once" ("disc at once" not' + #13#10 +
				'supported or not able to write such a disc). This means' + #13#10 +
				'there might be some minor quality loss (e.g. lost audio index' + #13#10 +
				'or different pause between audio tracks). Do you want to' + #13#10 +
        'proceed anyway?' + #13#10, mtWarning, [mbYes,mbNo], 0) = mrYes then
      begin
        Result := DLG_RETURN_TRUE;
      end
      else
      begin
        Result := DLG_RETURN_FALSE;
      end;
    end;
		DLG_COPY_FULLRISK:
    begin
      if MessageDlg('Disc must be written as "track at once" ("disc at once" not' + #13#10 +
				'supported or not able to write such a disc).  Unfortunately' + #13#10 +
				'your image has a special format which can most likely only' + #13#10 +
				'be written correctly with "disc at once". But you may' + #13#10 +
				'PROCEED AT YOUR OWN RISK. Do you want to continue' + #13#10 +
				'burning?' + #13#10, mtWarning, [mbYes,mbNo], 0) = mrYes then
      begin
        Result := DLG_RETURN_TRUE;
      end
      else
      begin
        Result := DLG_RETURN_FALSE;
      end;
    end;
		DLG_AUDIO_PROBLEMS:
    begin
			if (DWORD(data) and AUP_NOTRACK_FOUND = AUP_NOTRACK_FOUND) then
      begin
        MessageDlg('No tracks given.', mtInformation, [mbOK], 0);
			  Result := DLG_RETURN_EXIT;
        exit;
      end;

			if (DWORD(data) and AUP_MEGA_FATAL = AUP_MEGA_FATAL) then
      begin
				MessageDlg('Fatal internal problem.', mtError, [mbOK], 0);
				Result := DLG_RETURN_EXIT;
        exit;
      end;

      sBuffer := 'Nero has detected that the following audio properties are not' + #13#10 +
				'supported by your recorder in the current write mode and need' + #13#10 +
				'to be modified:' + #13#10;

			if (DWORD(data) and AUP_FIRST_TR_PAUSE = AUP_FIRST_TR_PAUSE) then
        sBuffer := sBuffer + '  - CD specification allows only 2-3 Seconds pause for the first track' + #13#10;
			if (DWORD(data) and AUP_PAUSE_SETTINGS = AUP_PAUSE_SETTINGS) then
        sBuffer := sBuffer + '  - Pause length between the tracks not supported' + #13#10;
			if (DWORD(data) and AUP_INDEX_SETTINGS = AUP_INDEX_SETTINGS) then
        sBuffer := sBuffer + '  - Additional index positions not supported' + #13#10;
			if (DWORD(data) and AUP_ISRC_SETTINGS = AUP_ISRC_SETTINGS) then
        sBuffer := sBuffer + '  - ISRC codes not supported' + #13#10;
			if (DWORD(data) and AUP_COPYPROT_SETTINGS = AUP_COPYPROT_SETTINGS) then
        sBuffer := sBuffer + '  - Copy protection bit not supported' + #13#10;

      sBuffer := sBuffer + 'Nero can change the audio track settings for you to fit the' + #13#10 +
				'capabilities of your recorder. This might cause some audio' + #13#10 +
				'properties to be lost. Do you want Nero to change the track' + #13#10 +
				'settings for you?' + #13#10;

      if MessageDlg(sBuffer, mtInformation, [mbYes,mbNo], 0) = mrYes then
      begin
        Result := DLG_RETURN_TRUE;
      end
      else
      begin
        Result := DLG_RETURN_FALSE;
      end;
    end;
		DLG_WAITCD:
    begin
				pacBuffer := NeroGetLocalizedWaitCDTexts(NERO_WAITCD_TYPE(Integer(data)));
				if pacBuffer <> nil then
        begin
					MessageDlg(pacBuffer, mtInformation, [mbOK], 0);
					NeroFreeMem(pacBuffer);
        end;

        Result := DLG_RETURN_EXIT;
    end;
		DLG_WAITCD_REMINDER:
    begin
				pacBuffer := NeroGetLocalizedWaitCDTexts(NERO_WAITCD_TYPE(Integer(data)));
				if pacBuffer <> nil then
        begin
					MessageDlg(pacBuffer, mtInformation, [mbOK], 0);
					NeroFreeMem(pacBuffer);
        end;

        Result := DLG_RETURN_EXIT;
    end;
    DLG_WAITCD_DONE:
    begin
			// Nothing to be done in the text interface, should close dialog box in a GUI
    end;
		DLG_FILESEL_IMAGE:
    begin
      InputQuery('Image File Not Found', 'Enter file name to save image to: ', sBuffer);

      StrPCopy(PAnsiChar(data), sBuffer);
      PAnsiChar(data)[SizeOf(PAnsiChar(data)) - 1] := #00;

			Result := DLG_RETURN_TRUE;
    end;
		DLG_BURNIMAGE_CANCEL:
    begin
      MessageDlg('There is not enough space available to burn the image.' + #13#10, mtInformation, [mbOK], 0);

      Result := DLG_RETURN_EXIT;
    end;
		DLG_NON_EMPTY_CDRW:
    begin
{ TODO : UserDialog: Non-empty CDRW dialog }
{
			static const CResponse mapping[] =
				"Erase CD", DLG_RETURN_CONTINUE,
				"Eject CD", DLG_RETURN_RESTART,
				"Cancel", DLG_RETURN_EXIT,

			puts ("This CDRW is not empty.");

			if (DLG_RETURN_CONTINUE == res)
      [
				// Erase the CDRW

				NEROAPI_CDRW_ERASE_MODE mode = NEROAPI_ERASE_QUICK;

				int time = NeroGetCDRWErasingTime(((CBurnContext*)pUserData)->m_NeroDeviceHandle,mode);

				// If time is negative, it means error.
				//
				switch (time)
				[
				case -1:
					puts("No CD inserted!");
					break;

				case -2:
					puts("This CD recorder does not support CDRW!");
					break;

				case -3:
					puts ("The inserted media is NOT rewritable!");
					break;

				default:
					if (time < 0)
					[
						// If this is some unknown error (negative value)
						// we should print generic error message and not
						// even attepmt erasing.
						//
						puts ("Unknown error while trying to erase CDRW!");
					]
					else
					[
						// If the value is positive, it is the approximate
						// second count the process will take.
						//
						printf("Erasing CDRW. This will take %d seconds.\n",time);

						int err = NeroEraseCDRW(((CBurnContext*)pUserData)->m_NeroDeviceHandle,mode);
						if (err)
						[
							puts("Error erasing the CDRW");
						]
					]
				]
			]
}
			Result := DLG_RETURN_RESTART;
    end;
		DLG_WAITCD_MEDIA_INFO:
    begin
{ TODO : UserDialog: WaitCD Media INfor dialog }
{
				const NERO_DLG_WAITCD_MEDIA_INFO * pMediaInfo = (const NERO_DLG_WAITCD_MEDIA_INFO *) data;

				printf ("Last detected media: %s\n", pMediaInfo->ndwmiLastDetectedMediaName);
				printf ("Requested media: %s\n", pMediaInfo->ndwmiRequestedMediaName);

				// The return value is ignored.
				//
}
      Result := DLG_RETURN_EXIT;
    end;
		DLG_COMP_REC_CONFLICT:
    begin
      MessageDlg('The compilation cannot be written on this recorder! ' + #13#10 +
					'You should modify your compilation settings or burn ' + #13#10 +
					'the disc on another recorder, that supports the required medium type.' + #13#10, mtInformation, [mbOK], 0);

      Result := DLG_RETURN_EXIT;
    end;
		DLG_WRONG_MEDIUM:
    begin
			MessageDlg('Another type of medium must be used to burn this compilation!', mtInformation, [mbOK], 0);

      Result := DLG_RETURN_EXIT;
    end;
    else
    begin
      Result := DLG_RETURN_EXIT;
    end;
  end;

  if Result = DLG_MAX then
    Result := DLG_RETURN_EXIT;
end;

function WriteIOCallback(pUserData: Pointer; pBuffer: PByte; dwLen: DWORD): DWORD; cdecl;
begin
  Result := FileWrite(Integer(pUserData^), pBuffer, dwLen) div SizeOf(pBuffer);
end;

function ReadIOCallback(pUserData: Pointer; pBuffer: PByte; dwLen: DWORD): DWORD; cdecl;
begin
  Result := FileRead(Integer(pUserData^), pBuffer, dwLen);
end;

function EOFCallback(pUserData: Pointer): BOOL; cdecl;
var
  FilePosition, FileLength: Int64;
begin
  FilePosition := FileSeek(Integer(pUserData^), 0, 1);
  FileLength := GetFileSize(Integer(pUserData^), nil);
  Result := (FilePosition = FileLength);
end;

function ErrorCallback(pUserData: Pointer): BOOL; cdecl;
begin
  Result := BOOL(GetLastError);
end;

function ProgressCallback(pUserData: Pointer; dwProgressInPercent: DWORD): BOOL; cdecl;
begin
  FMainForm.sbMain.SimplePanel := True;
	FMainForm.sbMain.SimpleText := 'Track extraction in progress (' + FormatFloat('000 ', dwProgressInPercent) + '%)';

  Application.ProcessMessages;

  Result := IdleCallback(pUserData);
end;

function AbortedCallback(pUserData: Pointer): BOOL; cdecl;
begin
  Result := True;
end;

procedure AddLogLine(pUserData: Pointer; _type: NERO_TEXT_TYPE; text: PChar); cdecl;
var
  Header: string;
begin
	case _type of
    NERO_TEXT_INFO:        // informative text
    begin
      MessageDlg(text, mtInformation, [mbOK], 0);
    end;
    NERO_TEXT_STOP:        // some operation stopped prematurely
    begin
      MessageDlg(text, mtError, [mbOK], 0);
      header := '# ';
    end;
    NERO_TEXT_EXCLAMATION: // important information
    begin
      MessageDlg(text, mtWarning, [mbOK], 0);
      header := '! ';
    end;
    NERO_TEXT_QUESTION:    // a question which requires an answer
    begin
      MessageDlg(text, mtConfirmation, [mbOK], 0);
    end;
    NERO_TEXT_DRIVE:		   // a message concerning a CD-ROM drive or recorder
    begin
      MessageDlg(text, mtInformation, [mbOK], 0);
    end;
  end;
end;

procedure SetPhaseCallback(pUserData: Pointer; text: PChar); cdecl;
begin
  ShowMessage(text);
end;

procedure DisableAbortCallback(pUserData: Pointer; abortEnabled: BOOL); cdecl;
begin
  if abortEnabled then
		ShowMessage('The current process cannot be interrupted')
	else
    ShowMessage('The process can be interrupted again');
end;

procedure SetMajorPhaseCallback(pUserData: Pointer; phase: NERO_MAJOR_PHASE; reserved: PVoid); cdecl;
begin
  case phase of
    NERO_PHASE_BUP_ACTIVATED: ShowMessage('BUP Activated');
    NERO_PHASE_CONTINUE_FORMATTING: ShowMessage('Continue Formating');
    NERO_PHASE_DONE_CACHE: ShowMessage('Done Caching');
    NERO_PHASE_DONE_SIMULATE: ShowMessage('Done Simulation');
    NERO_PHASE_DONE_SIMULATE_NOSPD: ShowMessage('Done Simulation - No SPD');
    NERO_PHASE_DONE_TEST: ShowMessage('Done Testing');
    NERO_PHASE_DONE_WRITE: ShowMessage('Done Writing');
    NERO_PHASE_DONE_WRITE_NOSPD: ShowMessage('Done Writing - No SPD');
    NERO_PHASE_DVDVIDEO_DETECTED: ShowMessage('DVD Video Detected');
    NERO_PHASE_DVDVIDEO_REALLOC_COMPLETED: ShowMessage('DVD Video Relloc Completed');
    NERO_PHASE_DVDVIDEO_REALLOC_FAILED: ShowMessage('DVD Video Realloc Failed');
    NERO_PHASE_DVDVIDEO_REALLOC_NOTNEEDED: ShowMessage('DVD Video Realloc Not Needed');
    NERO_PHASE_DVDVIDEO_REALLOC_STARTED: ShowMessage('DVD Video Relloc Started');
    NERO_PHASE_ENCODE_VIDEO: ShowMessage('Encoding Video');
    NERO_PHASE_FORMATTING_SUCCESSFUL: ShowMessage('Formating Successful');
    NERO_PHASE_SEAMLESSLINK_ACTIVATED: ShowMessage('Seamless Link Activated');
    NERO_PHASE_START_CACHE: ShowMessage('Caching Started');
    NERO_PHASE_START_SIMULATE: ShowMessage('Simulation Started');
    NERO_PHASE_START_SIMULATE_NOSPD: ShowMessage('Simulation Started - No SPD');
    NERO_PHASE_START_TEST: ShowMessage('Testing Started');
    NERO_PHASE_START_WRITE: ShowMessage('Writing Started');
    NERO_PHASE_START_WRITE_NOSPD: ShowMessage('Writing Started - No SPD');
    NERO_PHASE_UNSPECIFIED: ShowMessage('BUP Activated');
  end;
end;

procedure TFMainForm.FormCreate(Sender: TObject);
var
  lpdwSize, lpdwHandle: Cardinal;
  lpVerInfo, lpVS_FixedFileInfo: Pointer;
  Counter: Integer;
  nafi: PNeroAudioFormatInfo;
begin
  NeroIsoTrack := nil;
  RootIsoItem := nil;

  NeroCDInfo := nil;
  NeroWriteCD := nil;
  NeroWriteVideoCD := nil;
  NeroWriteImage := nil;
  NeroWriteFreestyleCD := nil;
  sbMain.SimplePanel := true;

  dnapiSettings.Active := True;

  sbMain.SimpleText := dnapiSettings.NeroAPIVersion;

  lpdwSize := GetFileVersionInfoSize(PAnsiChar(Application.ExeName), lpdwHandle);
  if lpdwSize > 0  then
  begin
    GetMem (lpVerInfo, lpdwSize);

    if GetFileVersionInfo(PAnsiChar(Application.ExeName), 0, lpdwSize, lpVerInfo) then
    begin
      if VerQueryValue(lpVerInfo, '\', lpVS_FixedFileInfo, lpdwSize) then
      begin
        lbVersion01.Caption := lbVersion01.Caption +  #13#10 + '* DelphiNeroAPI Version '+
          IntToStr (HiWord (TVSFixedFileInfo (lpVS_FixedFileInfo^).dwFileVersionMS)) + '.' +
          IntToStr (LoWord (TVSFixedFileInfo (lpVS_FixedFileInfo^).dwFileVersionMS)) + '.' +
          IntToStr (HiWord (TVSFixedFileInfo (lpVS_FixedFileInfo^).dwFileVersionLS)) + '.' +
          IntToStr (LoWord (TVSFixedFileInfo (lpVS_FixedFileInfo^).dwFileVersionLS));
      end;

      FreeMem(lpVerInfo);
    end;
  end;

  Counter := 0;
  nafi := nil;

  while NeroAudioGetFormatInfo(Counter, nafi) do
  begin
    lbVersion01.Caption := lbVersion01.Caption + '* ' +
      nafi.nafiDescription + ' (' +
      nafi.nafiExtList + ') [';

    if nafi.nafiTgt then
      lbVersion01.Caption := lbVersion01.Caption + 'Target';

    if nafi.nafiConfigurable then
    begin
      if nafi.nafiTgt then
        lbVersion01.Caption := lbVersion01.Caption + ', Configurable'
      else
        lbVersion01.Caption := lbVersion01.Caption + 'Configurable';
    end;

    lbVersion01.Caption := lbVersion01.Caption + ']' + #13#10;

    Inc(Counter);
  end;

  pcWrite.TabIndex := pcWrite.PageCount - 1;

  DragAcceptFiles(self.WindowHandle, True);

  NeroProgress.npProgressCallback := ProgressCallback;
  NeroProgress.npAbortedCallback := AbortedCallback;
  NeroProgress.npAddLogLineCallback := AddLogLine;
  NeroProgress.npSetPhaseCallback := SetPhaseCallback;
  NeroProgress.npUserData := dnapiSettings.NeroSettings;
  NeroProgress.npDisableAbortCallback := DisableAbortCallback;
  NeroProgress.npSetMajorPhaseCallback := SetMajorPhaseCallback;
end;

procedure TFMainForm.FormDestroy(Sender: TObject);
begin
  DragAcceptFiles(self.WindowHandle, False);

  if Assigned(NeroWriteCD) then
  	ReallocMem(NeroWriteCD, 0);

  if Assigned(NeroWriteVideoCD) then
  	ReallocMem(NeroWriteVideoCD, 0);

  if Assigned(NeroWriteFreestyleCD) then
  	ReallocMem(NeroWriteFreestyleCD, 0);

  if Assigned(NeroWriteImage) then
  	ReallocMem(NeroWriteImage, 0);

  if Assigned(NeroCDInfo) then
  	NeroFreeMem(NeroCDInfo);

  if Assigned(NeroIsoTrack) then
    NeroFreeIsoTrack(NeroIsoTrack);

  if Assigned(RootIsoItem) then
    FreeIsoItem(RootIsoItem);
end;

procedure TFMainForm.ApplicationEventsShowHint(var HintStr: string;
  var CanShow: Boolean; var HintInfo: THintInfo);
begin
  if CanShow then
		sbMain.SimpleText := Application.Hint;
end;

procedure TFMainForm.btnMoreDeviceClick(Sender: TObject);
begin
  FDeviceInformation.ShowModal;
end;

procedure TFMainForm.btnRefreshClick(Sender: TObject);
begin
  if Assigned(dnapiDevices.SelectedDeviceHandle) then
  begin
    if Assigned(NeroCDInfo) then
      NeroFreeMem(NeroCDInfo);

    NeroCDInfo := NeroGetCDInfo(dnapiDevices.SelectedDeviceHandle, NGCDI_READ_CD_TEXT or NGCDI_READ_ISRC);
    if Assigned(NeroCDInfo) then
    begin
      case(NeroCDInfo.ncdiMediumType) of
        NMT_CD_RECORDABLE: stMedia.Caption := 'Recordable media ';
        NMT_CD_REWRITEABLE: stMedia.Caption := 'Rewriteable media ';
        NMT_CD_ROM: stMedia.Caption := 'Read-only media ';
        NMT_UNKNOWN: stMedia.Caption := 'Unknown media type ';
      end;
      stMedia.Caption := stMedia.Caption + '(' + NeroGetTypeNameOfMedia(NERO_MEDIA_SET(NeroCDInfo.ncdiMediaType)) + ')';

      btnMoreMedia.Enabled := True;
      btnEject.Enabled := True;
      lbFreeBlocks.Caption := IntToStr(NeroCDInfo.ncdiFreeCapacityInBlocks) + ' Free Blocks (' + FloatToStrF(NeroCDInfo.ncdiFreeCapacityInBlocks * 2352 / 1024 / 1024 ,ffGeneral, 3, 3) + ' MB)';
      lbFreeBlocks.Visible := NeroCDInfo.ncdiIsWriteable;
      if NeroCDInfo.ncdiNumTracks > 1 then
        lbTracks.Caption := IntToStr(NeroCDInfo.ncdiNumTracks) + ' Tracks'
      else
        lbTracks.Caption := IntToStr(NeroCDInfo.ncdiNumTracks) + ' Track';

      lbTracks.Visible := (NeroCDInfo.ncdiNumTracks > 0);
      btnQuickErase.Enabled := NCDI_IS_ERASE_MODE_AVAILABLE(NeroCDInfo^, Cardinal(NEROAPI_ERASE_QUICK)) and lbTracks.Visible;
      btnErase.Enabled := NCDI_IS_ERASE_MODE_AVAILABLE(NeroCDInfo^, Cardinal(NEROAPI_ERASE_ENTIRE)) and lbTracks.Visible;
    end
    else
    begin
      btnMoreMedia.Enabled := False;
      stMedia.Caption := 'No midia inserted';
      lbTracks.Visible := False;
      lbFreeBlocks.Visible := False;
      btnErase.Enabled := False;
      btnQuickErase.Enabled := False;
      btnEject.Enabled := False;
    end;
  end;
end;

procedure TFMainForm.btnMoreMediaClick(Sender: TObject);
begin
  FMediaInfo.ShowModal;
end;

procedure TFMainForm.btnEraseClick(Sender: TObject);
var
  Time: Integer;
begin
  Time := NeroGetCDRWErasingTime(dnapiDevices.SelectedDeviceHandle, NEROAPI_ERASE_ENTIRE);
  if (Time = -1) then
    NeroError('No CD inserted')
  else
    if (Time = -2) then
      NeroError('This CD recorder does not support CD-RW')
    else
      if (Time = -3) then
        NeroError('This media is not rewritable');
  sbMain.SimpleText := 'Erasing CD-RW. This will take ' + IntToStr(Time) + ' seconds.';
  time := NeroEraseCDRW(dnapiDevices.SelectedDeviceHandle, NEROAPI_ERASE_ENTIRE);
  if (Time <> 0) then
    NeroError('Error erasing the CD-RW');

  btnRefreshClick(self);
end;

procedure TFMainForm.btnEjectClick(Sender: TObject);
begin
  NeroEjectLoadCD(dnapiDevices.SelectedDeviceHandle, true);
  btnLoad.Enabled := True;
  btnEject.Enabled := False;
  btnRefreshClick(Sender);
end;

procedure TFMainForm.NeroError(Action: string);
var
  Error: PChar;
begin
	Error := NeroGetLastError();
  if (Error <> '') then
  	MessageBox(Application.Handle, Error, PChar(Action), MB_ICONERROR)
  else
  	MessageBox(Application.Handle, 'Failed', PChar(Action), MB_ICONERROR);

	NeroFreeMem(Error);
end;

procedure TFMainForm.btnQuickEraseClick(Sender: TObject);
var
  Time: Integer;
begin
  Time := NeroGetCDRWErasingTime(dnapiDevices.SelectedDeviceHandle, NEROAPI_ERASE_QUICK);
  if (Time = -1) then
    NeroError('No CD inserted')
  else
    if (Time = -2) then
      NeroError('This CD recorder does not support CD-RW')
    else
      if (Time = -3) then
        NeroError('This media is not rewritable');
  sbMain.SimpleText := 'Erasing CD-RW. This will take ' + IntToStr(Time) + ' seconds.';
  time := NeroEraseCDRW(dnapiDevices.SelectedDeviceHandle, NEROAPI_ERASE_QUICK);
  if (Time <> 0) then
    NeroError('Error erasing the CD-RW');

  btnRefreshClick(self);
end;

procedure TFMainForm.WMDropFiles(var msg: TWMDropFiles);
var
  cFileName: array [0 .. MAX_PATH] of Char;
  WhichFiles: TStringList;
  index, i, FilesCount, FileHandle: Integer;
  TrackName: string;
  paBuffer: string;
  Flags: Cardinal;
begin
  WhichFiles := TStringList.Create;
  try
    FilesCount := DragQueryFile(Msg.Drop, $FFFFFFFF, cFileName, MAX_PATH);
    for i := 0 to Pred(FilesCount) do
    begin
      if DragQueryFile(Msg.Drop, i, cFileName, MAX_PATH) > 0 then
      begin
        WhichFiles.Add(cFileName);
      end;
    end;

    if WhichFiles.Count > 0 then
    begin
      Screen.Cursor := crHourGlass;
      for i := 0 to Pred(WhichFiles.Count) do
      begin
        case pcWrite.TabIndex of
          0:
          begin
            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.nrg') then
            begin
              if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.iso') then
              begin
                if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.bin') then
                begin
                  if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.cue') then
                  begin
                    continue;
                  end;
                end;
              end;
            end;

            StrPCopy(NeroWriteImage.nwiImageFileName, WhichFiles.Strings[i]);
            NeroWriteImage.nwiImageFileName[SizeOf(NeroWriteImage.nwiImageFileName) - 1] := #00;
            edImageName.Text := WhichFiles.Strings[i];
          end;
          1:
          begin
            if Assigned(NeroWriteCD) then
              ReallocMem(NeroWriteCD, SizeOf(NeroWriteCD))
            else
              NeroWriteCD :=AllocMem(SizeOf(NERO_WRITE_CD));

            if not Assigned(RootIsoItem) then
            begin
              RootIsoItem := NeroCreateIsoItem();
              RootIsoItem.fileName := '';
            end;
{ TODO : Add Visual return of added files and directories }
            AddFileToRootIsoItem(RootIsoItem, WhichFiles.Strings[i]);
          end;
          2:
          begin
          end;
          3:
          begin
            if Assigned(NeroWriteCD) then
              ReallocMem(NeroWriteCD, SizeOf(NeroWriteCD) + SizeOf(NERO_AUDIO_TRACK) * (WhichFiles.Count - 1))
            else
              NeroWriteCD :=AllocMem(SizeOf(NERO_WRITE_CD) + SizeOf(NERO_AUDIO_TRACK) * (WhichFiles.Count - 1));

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.wav') then
            begin
              if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.mp3') then
              begin
                if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.wma') then
                begin
                  if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.pcm') then
                  begin
                    continue;
                  end;
                end;
              end;
            end;

            TrackName := ExtractFileName(WhichFiles.Strings[i]);
            index := lbxCDDATracks.Items.Add('');
            lbxCDDATracks.Items[index] := '[' + IntToStr(index + 1) + '] ' + TrackName + ' [Pause 00s]';

            StrPCopy(NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeFileName, WhichFiles.Strings[i]);
            NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeFileName[SizeOf(NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeFileName) - 1] := #00;

            if index = 0 then
            begin
              NeroWriteCD.nwcdTracks[index].natPauseInBlksBeforeThisTrack := 2 * 75;
              NeroWriteCD.nwcdTracks[index].natIndex0ContainsData := False;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.wav' then
            begin
              Inc(NeroWriteCD.nwcdNumTracks);
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mp3' then
            begin
              Inc(NeroWriteCD.nwcdNumTracks);
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE_MP3;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.wma' then
            begin
              Inc(NeroWriteCD.nwcdNumTracks);
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE_WMA;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.pcm' then
            begin
              Inc(NeroWriteCD.nwcdNumTracks);
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_IO_CALLBACK;
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeIO.nioIOCallback := ReadIOCallback;
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeIO.nioEOFCallback := EOFCallback;
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeIO.nioErrorCallback := ErrorCallback;

              FileHandle := FileOpen(WhichFiles.Strings[i], fmOpenRead);
              if FileHandle = -1 then
                continue;

              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeData.ndeIO.nioUserData := @FileHandle;
              NeroWriteCD.nwcdTracks[i].natLengthInBlocks := GetFileSize(FileHandle, nil) div 2352;

              FileClose(FileHandle);
              continue;
            end;
          end;
          4:
          begin
            if Assigned(NeroWriteVideoCD) then
              ReallocMem(NeroWriteVideoCD, SizeOf(NeroWriteVideoCD) + SizeOf(NERO_VIDEO_ITEM) * (WhichFiles.Count - 1))
            else
              NeroWriteVideoCD :=AllocMem(SizeOf(NERO_WRITE_VIDEO_CD) + SizeOf(NERO_VIDEO_ITEM) * (WhichFiles.Count - 1));

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.jpg') then
            begin
              if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.jpeg') then
              begin
                if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.avi') then
                begin
                  if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.mpg') then
                  begin
                    if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) <> '.mpeg') then
                    begin
                      continue;
                    end;
                  end;
                end;
              end;
            end;

            TrackName := ExtractFileName(WhichFiles.Strings[i]);
            index := lbxVCDTracks.Items.Add('');
            lbxVCDTracks.Items[index] := '[' + IntToStr(index + 1) + '] ' + TrackName;

            StrPCopy(NeroWriteVideoCD.nwvcdItems[i].nviSourceFileName, WhichFiles.Strings[i]);
            NeroWriteVideoCD.nwvcdItems[i].nviSourceFileName[SizeOf(NeroWriteVideoCD.nwvcdItems[i].nviSourceFileName) - 1] := #00;

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.jpg') or
              (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.jpeg') then
            begin
              Inc(NeroWriteVideoCD.nwvcdNumItems);
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_JPEG_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := $FFFFFFFF;
              continue;
            end;

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.avi') then
            begin
              Inc(NeroWriteVideoCD.nwvcdNumItems);
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_NONENCODED_VIDEO_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := 0;
              continue;
            end;

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mpg') or
              (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mpeg') then
            begin
              Inc(NeroWriteVideoCD.nwvcdNumItems);
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_MPEG_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := 0;
              continue;
            end;
          end;
        end;
      end;

      case pcWrite.TabIndex of
        1:
        begin
          Flags := 0;

          if cbxcDROMISOFS.Checked then
            Flags := Flags + NCITEF_CREATE_ISO_FS;
          if cbxCDROMUDFFS.Checked then
            Flags := Flags + NCITEF_CREATE_UDF_FS;
          if cbxCDROMJoliet.Checked then
            Flags := Flags + NCITEF_USE_JOLIET;
          if cbxCDROMRockridge.Checked then
            Flags := Flags + NCITEF_USE_ROCKRIDGE;
          if cbxCDROMMode2.Checked then
            Flags := Flags + NCITEF_USE_MODE2;
          if cbxCDROMDVDVideoRealloc.Checked then
            Flags := Flags + NCITEF_DVDVIDEO_REALLOC;

          NeroIsoTrack := NeroCreateIsoTrackEx(RootIsoItem, PCHAR(edCDROMTrackName.Text),  Flags);
          NeroWriteCD.nwcdCDExtra := False;
          NeroWriteCD.nwcdMediaType := NeroCDInfo.ncdiMediaType;
          NeroWriteCD.nwcdpCDStamp := nil;
          NeroWriteCD.nwcdIsoTrack := NeroIsoTrack;
        end;
        2:
        begin
        end;
        3:
        begin
          NeroIsoTrack := NeroCreateIsoTrackEx(nil, PChar(edCDROMTrackName.Text), 0);

          NeroWriteCD.nwcdCDExtra := False;
          NeroWriteCD.nwcdMediaType := NeroCDInfo.ncdiMediaType;{ TODO : Add support to CDExtra }
          NeroWriteCD.nwcdpCDStamp := nil;
          NeroWriteCD.nwcdIsoTrack := NeroIsoTrack;
        end;
        4:
        begin
          NeroIsoTrack := NeroCreateIsoTrackEx(nil, PChar(edCDROMTrackName.Text), 0);

          NeroWriteVideoCD.nwvcdCustomVCDEngine := nil;

          if NeroWriteVideoCD.nwvcdTempPath = '' then
          begin
            SetLength(paBuffer, MAX_PATH);
            SetLength(paBuffer, GetTempPath(MAX_PATH, PChar(paBuffer)));
            if paBuffer = '' then
            begin
              if DirectoryExists('C:\TEMP') then
                paBuffer := 'C:\TEMP'
              else
              begin
                if DirectoryExists('C:\TMP') then
                  paBuffer := 'C:\TMP'
                else
                  paBuffer := 'C:\';
              end;
            end;

            StrPCopy(NeroWriteVideoCD.nwvcdTempPath, paBuffer);
            NeroWriteVideoCD.nwvcdTempPath[SizeOf(NeroWriteVideoCD.nwvcdTempPath) - 1] := #00;
          end;

          NeroWriteVideoCD.nwvcdIsoTrack := NeroIsoTrack;
        end;
      end;

      Screen.Cursor := crDefault;
    end;
  finally
    DragFinish(Msg.Drop);
    WhichFiles.Free;
  end;
end;
procedure TFMainForm.btnLoadClick(Sender: TObject);
begin
  NeroEjectLoadCD(dnapiDevices.SelectedDeviceHandle, false);
  btnRefreshClick(Sender);
  btnLoad.Enabled := False;
  btnEject.Enabled := False;
end;

procedure TFMainForm.pcWriteChange(Sender: TObject);
var
  lpdwSize, lpdwHandle: Cardinal;
  ver1, ver2, ver3,ver4: WORD;
  Counter: Integer;
  nafi: PNeroAudioFormatInfo;
  lpVerInfo, lpVS_FixedFileInfo: Pointer;
begin
  if pcWrite.TabIndex <= 5 then
  begin
    case pcWrite.TabIndex of
      0:
      begin
        if Assigned(NeroWriteImage) then
          ZeroMemory(NeroWriteImage, SizeOf(NeroWriteImage))
        else
          NeroWriteImage := PNeroWriteImage(AllocMem(SizeOf(NERO_WRITE_IMAGE)));

        if Assigned(NeroWriteCD) then
          ReallocMem(NeroWriteCD, 0);

        if Assigned(NeroWriteFreestyleCD) then
          ReallocMem(NeroWriteFreestyleCD, 0);

        if Assigned(NeroWriteVideoCD) then
          ReallocMem(NeroWriteVideoCD, 0);

        if Assigned(NeroIsoTrack) then
          NeroFreeIsoTrack(NeroIsoTrack);

        if Assigned(RootIsoItem) then
          FreeIsoItem(RootIsoItem);
      end;
      1:
      begin
        if Assigned(NeroWriteCD) then
          ZeroMemory(NeroWriteCD, SizeOf(NeroWriteCD))
        else
          NeroWriteCD := PNeroWriteCD(AllocMem(SizeOf(NERO_WRITE_CD)));

        if Assigned(NeroWriteVideoCD) then
          ReallocMem(NeroWriteVideoCD, 0);

        if Assigned(NeroWriteFreestyleCD) then
          ReallocMem(NeroWriteFreestyleCD, 0);

        if Assigned(NeroWriteImage) then
          ReallocMem(NeroWriteImage, 0);

        if Assigned(NeroIsoTrack) then
          NeroFreeIsoTrack(NeroIsoTrack);

        if Assigned(RootIsoItem) then
          FreeIsoItem(RootIsoItem);
      end;
      2:
      begin
      end;
      3:
      begin
        if Assigned(NeroWriteCD) then
          ZeroMemory(NeroWriteCD, SizeOf(NeroWriteCD))
        else
          NeroWriteCD := PNeroWriteCD(AllocMem(SizeOf(NERO_WRITE_CD)));

        if Assigned(NeroWriteVideoCD) then
          ReallocMem(NeroWriteVideoCD, 0);

        if Assigned(NeroWriteFreestyleCD) then
          ReallocMem(NeroWriteFreestyleCD, 0);

        if Assigned(NeroWriteImage) then
          ReallocMem(NeroWriteImage, 0);

        if Assigned(NeroIsoTrack) then
          NeroFreeIsoTrack(NeroIsoTrack);

        if Assigned(RootIsoItem) then
          FreeIsoItem(RootIsoItem);

        edCDDAArtist.Text := '';
        edCDDATitle.Text := '';
        lbxCDDATracks.Items.Clear;

        NeroWriteCD.nwcdNumTracks := 0;
        NeroWriteCD.nwcdArtist := '';
        NeroWriteCD.nwcdTitle := '';
      end;
      4:
      begin
        if Assigned(NeroWriteVideoCD) then
          ZeroMemory(NeroWriteVideoCD, SizeOf(NeroWriteVideoCD))
        else
          NeroWriteVideoCD := PNeroWriteVideoCD(AllocMem(SizeOf(NERO_WRITE_VIDEO_CD)));

        if Assigned(NeroWriteCD) then
          ReallocMem(NeroWriteCD, 0);

        if Assigned(NeroWriteFreestyleCD) then
          ReallocMem(NeroWriteFreestyleCD, 0);

        if Assigned(NeroWriteImage) then
          ReallocMem(NeroWriteImage, 0);

        if Assigned(NeroIsoTrack) then
          NeroFreeIsoTrack(NeroIsoTrack);

        if Assigned(RootIsoItem) then
          FreeIsoItem(RootIsoItem);

        NeroWriteVideoCD.nwvcdSVCD := False;
        NeroWriteVideoCD.nwvcdNumItems := 0;
        NeroWriteVideoCD.nwvcdIsoTrack := nil;
        NeroWriteVideoCD.nwvcdTempPath := '';
      end;
      5:
      begin
        if NeroGetAPIVersionEx(ver1, ver2, ver3, ver4, nil) then
        begin
          lbVersion01.Caption :=  '* Nero API Version ' + IntToStr(ver1) + '.' +
            IntToStr(ver2) + '.' + IntToStr(ver3) + '.' + IntToStr(ver4);
        end;

        lpdwSize := GetFileVersionInfoSize(PAnsiChar(Application.ExeName), lpdwHandle);
        if lpdwSize > 0  then
        begin
          GetMem (lpVerInfo, lpdwSize);

          if GetFileVersionInfo(PAnsiChar(Application.ExeName), 0, lpdwSize, lpVerInfo) then
          begin
            if VerQueryValue(lpVerInfo, '\', lpVS_FixedFileInfo, lpdwSize) then
            begin
              lbVersion01.Caption := lbVersion01.Caption +  #13#10 + '* DelphiNeroAPI Version '+
                IntToStr(HiWord(TVSFixedFileInfo(lpVS_FixedFileInfo^).dwFileVersionMS)) + '.' +
                IntToStr(LoWord(TVSFixedFileInfo(lpVS_FixedFileInfo^).dwFileVersionMS)) + '.' +
                IntToStr(HiWord(TVSFixedFileInfo(lpVS_FixedFileInfo^).dwFileVersionLS)) + '.' +
                IntToStr(LoWord(TVSFixedFileInfo(lpVS_FixedFileInfo^).dwFileVersionLS));
            end;

            FreeMem(lpVerInfo);
          end;
        end;

        Counter := 0;
        nafi := nil;

        while NeroAudioGetFormatInfo(Counter, nafi) do
        begin
          lbVersion01.Caption := lbVersion01.Caption + '* ' +
            nafi.nafiDescription + ' (' +
            nafi.nafiExtList + ') [';

          if nafi.nafiTgt then
            lbVersion01.Caption := lbVersion01.Caption + 'Target';

          if nafi.nafiConfigurable then
          begin
            if nafi.nafiTgt then
              lbVersion01.Caption := lbVersion01.Caption + ', Configurable'
            else
              lbVersion01.Caption := lbVersion01.Caption + 'Configurable';
          end;

          lbVersion01.Caption := lbVersion01.Caption + ']' + #13#10;

          Inc(Counter);
        end;
      end;
    end;
  end;
end;

procedure TFMainForm.edCDDAArtistChange(Sender: TObject);
begin
  NeroWriteCD.nwcdArtist := PAnsiChar(edCDDAArtist.Text);
end;

procedure TFMainForm.edCDDATitleChange(Sender: TObject);
begin
  NeroWriteCD.nwcdTitle := PAnsiChar(edCDDATitle.Text);
end;

procedure TFMainForm.btnBurnCDDAClick(Sender: TObject);
var
  Flags: Cardinal;
  Counter: Integer;
begin
  if cbxSimulateBurn.Checked then
    Flags := NBF_SIMULATE
  else
    Flags := NBF_WRITE;

  Flags := Flags + NBF_DISABLE_ABORT + NBF_DETECT_NON_EMPTY_CDRW +
    NBF_SPEED_IN_KBS + NBF_CD_TEXT;

  if cbxCloseSession.Checked then
    Flags := Flags + NBF_CLOSE_SESSION;

  if cbxTestSpeed.Checked then
    Flags := Flags + NBF_SPEED_TEST;

  if cbxBufferUnderrun.Checked then
    Flags := Flags + NBF_BUF_UNDERRUN_PROT;

  if cbxVerifyData.Checked then
    Flags := Flags + NBF_VERIFY;

  if not cbxEjectCD.Checked then
    Flags := Flags + NBF_DISABLE_EJECT;

  case cbWritingMethod.ItemIndex of
    0: // TAO
    begin
      //TAO is the default, do nothing
    end;
    1: //DAO
    begin
      Flags := Flags + NBF_DAO;
    end;
  end;

  NeroBurn(dnapiDevices.SelectedDeviceHandle, NERO_ISO_AUDIO_CD, NeroWriteCD, Flags,
    dnapiDeviceSpeed.SpeedKBs, @NeroProgress);

	for Counter := 0 to NeroWriteCD.nwcdNumTracks do
  begin
    if (NeroWriteCD.nwcdTracks[Counter].natSourceDataExchg.ndeType = NERO_ET_IO_CALLBACK) and
			Assigned(NeroWriteCD.nwcdTracks[Counter].natSourceDataExchg.ndeData.ndeIO.nioUserData) then
    begin
      FileClose(Integer(NeroWriteCD.nwcdTracks[Counter].natSourceDataExchg.ndeData.ndeIO.nioUserData^));
    end;
  end;

  if Assigned(NeroWriteCD) then
    ReallocMem(NeroWriteCD, 0);

  if Assigned(NeroIsoTrack) then
    NeroFreeIsoTrack(NeroIsoTrack);

  if Assigned(RootIsoItem) then
    FreeIsoItem(RootIsoItem);

  if cbxEjectCD.Checked then
  begin
    btnLoad.Enabled := True;
    btnRefreshClick(Self);
  end;

  lbxCDDATracks.Clear;
  edCDDAArtist.Clear;
  edCDDATitle.Clear;

  pcWrite.TabIndex := pcWrite.PageCount - 1;
end;

procedure TFMainForm.rgTypeClick(Sender: TObject);
begin
  NeroWriteVideoCD.nwvcdSVCD := (rgType.ItemIndex = 1);
end;

procedure TFMainForm.stvVCDTempClick(Sender: TObject);
begin
  if stvVCDTemp.SelectedFolder.IsFolder then
  begin
    if (fpFileSystem in stvVCDTemp.SelectedFolder.Properties) then
    begin
      StrPCopy(NeroWriteVideoCD.nwvcdTempPath, stvVCDTemp.SelectedFolder.PathName);
      NeroWriteVideoCD.nwvcdTempPath[SizeOf(NeroWriteVideoCD.nwvcdTempPath) - 1] := #00;
    end;
  end;
end;

procedure TFMainForm.btnBurnImageClick(Sender: TObject);
var
  Flags: Cardinal;
begin
  if cbxSimulateBurn.Checked then
    Flags := NBF_SIMULATE
  else
    Flags := NBF_WRITE;

  Flags := Flags + NBF_DISABLE_ABORT + NBF_DETECT_NON_EMPTY_CDRW +
    NBF_SPEED_IN_KBS + NBF_CD_TEXT;

  if cbxCloseSession.Checked then
    Flags := Flags + NBF_CLOSE_SESSION;

  if cbxTestSpeed.Checked then
    Flags := Flags + NBF_SPEED_TEST;

  if cbxBufferUnderrun.Checked then
    Flags := Flags + NBF_BUF_UNDERRUN_PROT;

  if cbxVerifyData.Checked then
    Flags := Flags + NBF_VERIFY;

  if not cbxEjectCD.Checked then
    Flags := Flags + NBF_DISABLE_EJECT;

  case cbWritingMethod.ItemIndex of
    0: // TAO
    begin
      //TAO is the default, do nothing
    end;
    1: //DAO
    begin
      Flags := Flags + NBF_DAO;
    end;
  end;

  NeroBurn(dnapiDevices.SelectedDeviceHandle, NERO_BURN_IMAGE_CD, NeroWriteImage, Flags,
    dnapiDeviceSpeed.SpeedKBs, @NeroProgress);

  if Assigned(NeroWriteImage) then
    ReallocMem(NeroWriteImage, 0);

  if cbxEjectCD.Checked then
  begin
    btnLoad.Enabled := True;
    btnRefreshClick(Self);
  end;

  edImageName.Clear;

  pcWrite.TabIndex := pcWrite.PageCount - 1;
end;


procedure TFMainForm.btnBurnISOCDClick(Sender: TObject);
var
  Flags: Cardinal;
begin
  if cbxSimulateBurn.Checked then
    Flags := NBF_SIMULATE
  else
    Flags := NBF_WRITE;

  Flags := Flags + NBF_DISABLE_ABORT + NBF_DETECT_NON_EMPTY_CDRW +
    NBF_SPEED_IN_KBS + NBF_CD_TEXT;

  if cbxCloseSession.Checked then
    Flags := Flags + NBF_CLOSE_SESSION;

  if cbxTestSpeed.Checked then
    Flags := Flags + NBF_SPEED_TEST;

  if cbxBufferUnderrun.Checked then
    Flags := Flags + NBF_BUF_UNDERRUN_PROT;

  if cbxVerifyData.Checked then
    Flags := Flags + NBF_VERIFY;

  if not cbxEjectCD.Checked then
    Flags := Flags + NBF_DISABLE_EJECT;

  case cbWritingMethod.ItemIndex of
    0: // TAO
    begin
      //TAO is the default, do nothing
    end;
    1: //DAO
    begin
      Flags := Flags + NBF_DAO;
    end;
  end;

  NeroBurn(dnapiDevices.SelectedDeviceHandle, NERO_ISO_AUDIO_CD, NeroWriteCD, Flags,
    dnapiDeviceSpeed.SpeedKBs, @NeroProgress);

  if Assigned(NeroWriteCD) then
    ReallocMem(NeroWriteCD, 0);

  if Assigned(NeroIsoTrack) then
    NeroFreeIsoTrack(NeroIsoTrack);

  if Assigned(RootIsoItem) then
    FreeIsoItem(RootIsoItem);

  if cbxEjectCD.Checked then
  begin
    btnLoad.Enabled := True;
    btnRefreshClick(Self);
  end;

  edImageName.Clear;

  pcWrite.TabIndex := pcWrite.PageCount - 1;
end;

procedure TFMainForm.FreeIsoItem(var item: PNeroIsoItem);
begin
  if Assigned(item) then
  begin
    if Assigned(item.nextItem) then
    begin
      FreeIsoItem(item.nextItem);
      item.nextItem := nil;
    end;

    if item.isDirectory then
      if Assigned(item.subDirFirstItem) then
      begin
        FreeIsoItem(item.subDirFirstItem);
        item.subDirFirstItem := nil;
      end;

    if (not Assigned(item.nextItem)) and
      (not Assigned(item.subDirFirstItem)) then
    begin
      if item.isReference then
        NeroFreeMem(item)
      else
        NeroFreeIsoItem(item);
      item := nil;
    end;
  end;
end;

procedure TFMainForm.AddFileToRootIsoItem(var RootItem: PNeroIsoItem; FileName: string);
var
  FileTime: TDateTime;
  tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec, tm_msec: WORD;
  TempItem, SubDirItem: PNeroIsoItem;
  sr: TSearchRec;
begin
  TempItem := RootItem;

  if not (RootItem.fileName = '') then
  begin
    while Assigned(TempItem.nextItem) do
      TempItem := TempItem.nextItem;

    TempItem.nextItem := NeroCreateIsoItem();
    TempItem := TempItem.nextItem;
  end;

  StrPCopy(TempItem.fileName, ExtractFileName(FileName));
  TempItem.fileName[SizeOf(TempItem.fileName) - 1] := #00;

  StrPCopy(TempItem.sourceFilePath, FileName);
  TempItem.fileName[SizeOf(TempItem.sourceFilePath) - 1] := #00;

  FileTime := FileDateToDateTime(FileAge(FileName));
  DecodeDateTime(FileTime, tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec, tm_msec);

  TempItem.entryTime.tm_year := tm_year;
  TempItem.entryTime.tm_mon := tm_mon;
  TempItem.entryTime.tm_wday := DayOfTheWeek(FileTime);
  TempItem.entryTime.tm_mday := DayOfTheMonth(FileTime);
  TempItem.entryTime.tm_yday := DayOfTheYear(FileTime);
  TempItem.entryTime.tm_isdst := WORD(False);
  TempItem.entryTime.tm_hour := tm_hour;
  TempItem.entryTime.tm_min := tm_min;
  TempItem.entryTime.tm_sec := tm_min;

  TempItem.isReference := False;
  TempItem.isDirectory := DirectoryExists(FileName);
  TempItem.importinfo := nil;
  TempItem.userData := nil;
  TempItem.subDirFirstItem := nil;
  SubDirItem := nil;

  if TempItem.isDirectory then
    if FindFirst(IncludeTrailingPathDelimiter(FileName) + '*.*', faAnyFile + faHidden + faArchive + faReadOnly + faSysFile + faDirectory, sr) = 0 then
    begin
      repeat
        if Assigned(SubDirItem) then
        begin
          SubDirItem.nextItem := NeroCreateIsoItem();
          SubDirItem.fileName := '';
          SubDirItem := SubDirItem.nextItem;
        end
        else
        begin
          SubDirItem := NeroCreateIsoItem();
          SubDirItem.fileName := '';
          TempItem.subDirFirstItem := SubDirItem;
        end;

        AddFileToRootIsoItem(SubDirItem, sr.Name);
      until FindNext(sr) <> 0;

      FindClose(sr);
    end;
end;

procedure TFMainForm.btnSVCDBurnClick(Sender: TObject);
var
  Flags: Cardinal;
begin
  if cbxSimulateBurn.Checked then
    Flags := NBF_SIMULATE
  else
    Flags := NBF_WRITE;

  Flags := Flags + NBF_DISABLE_ABORT + NBF_DETECT_NON_EMPTY_CDRW +
    NBF_SPEED_IN_KBS + NBF_CD_TEXT;

  if cbxCloseSession.Checked then
    Flags := Flags + NBF_CLOSE_SESSION;

  if cbxTestSpeed.Checked then
    Flags := Flags + NBF_SPEED_TEST;

  if cbxBufferUnderrun.Checked then
    Flags := Flags + NBF_BUF_UNDERRUN_PROT;

  if cbxVerifyData.Checked then
    Flags := Flags + NBF_VERIFY;

  if not cbxEjectCD.Checked then
    Flags := Flags + NBF_DISABLE_EJECT;

  case cbWritingMethod.ItemIndex of
    0: // TAO
    begin
      //TAO is the default, do nothing
    end;
    1: //DAO
    begin
      Flags := Flags + NBF_DAO;
    end;
  end;

  NeroBurn(dnapiDevices.SelectedDeviceHandle, NERO_VIDEO_CD, NeroWriteVideoCD, Flags,
    dnapiDeviceSpeed.SpeedKBs, @NeroProgress);

  if Assigned(NeroWriteVideoCD) then
    ReallocMem(NeroWriteVideoCD, 0);

  if Assigned(NeroIsoTrack) then
    NeroFreeIsoTrack(NeroIsoTrack);

  if Assigned(RootIsoItem) then
    FreeIsoItem(RootIsoItem);

  if cbxEjectCD.Checked then
  begin
    btnLoad.Enabled := True;
    btnRefreshClick(Self);
  end;

  lbxVCDTracks.Clear;
  rgType.ItemIndex := 0;

  pcWrite.TabIndex := pcWrite.PageCount - 1;
end;

procedure TFMainForm.dnapiSettingsError(Sender: TObject; Message: string);
begin
  ShowMessage(Message);
end;

procedure TFMainForm.dnapiDevicesChange(Sender: TObject);
begin
  btnMoreDevice.Enabled := dnapiDevices.Active;

  if dnapiDevices.Active then
  begin
    cbxBufferUnderrun.Checked := dnapiDevices.SelectedDevice.nsdiMandatoryBUPSpeed > 0;

    btnRefresh.Enabled := True;
  end
  else
  begin
    btnRefresh.Enabled := False;
    btnMoreDevice.Enabled := False;
    btnMoreMedia.Enabled := False;
    stMedia.Caption := 'Device not selected';
    stMedia.Enabled := False;
    lbWriteSpeeds.Enabled := False;
  end;
end;

procedure TFMainForm.dnapiDevicesCloseUp(Sender: TObject);
begin
  btnRefreshClick(self);
end;

end.
