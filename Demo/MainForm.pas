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
{ Alexandre Rocha Lima e Marcondes . All Rights Reserved.                                      }
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
|* 26/06/2003: Modified
|*    Andreas Hausladen
|*    memory error corrected on NeroSettings
|* 26/06/2003: Modified
|*    Alexandre Rocha Lima e Marcondes
|*    memory error corrected on NeroDeviceInfos, added Device List
|* 02/07/2003: Modified
|*    Alexandre Rocha Lima e Marcondes
|*    added Media detecting (NeroCDInfo)
|* 29/01/2004: Modified
|*    Alexandre Rocha Lima e Marcondes
|*    added CD-DA writing
|*    corrected memory allocation on NeroWriteCD structure (CD-DA)
|*    corrected general memory deallocation routines (ReallocMem instead of FreeMem)
|* 02/02/2004: Modified
|*    Alexandre Rocha Lima e Marcondes
|*    added Image writing
|*
******************************************************************************}

{******************************************************************************
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroAPITest.cpp and NeroAPITest.h
|*
|* PURPOSE: Test functions of Nero API DLL
******************************************************************************}
unit MainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, NeroAPI, NeroUserDialog, ComCtrls, StdCtrls, AppEvnts, ExtCtrls,
  JvImage, ShellAPI, ShellCtrls;

type
  TFMainForm = class(TForm)
    sbMain: TStatusBar;
    ApplicationEvents: TApplicationEvents;
    gbDevices: TGroupBox;
    cbDevices: TComboBox;
    btnMoreDevice: TButton;
    cbWriteSpeeds: TComboBox;
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
    tsUDF: TTabSheet;
    tsISOUDF: TTabSheet;
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
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ApplicationEventsShowHint(var HintStr: String;
      var CanShow: Boolean; var HintInfo: THintInfo);
    procedure cbDevicesChange(Sender: TObject);
    procedure btnMoreDeviceClick(Sender: TObject);
    procedure cbDevicesCloseUp(Sender: TObject);
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
  private
    { Private declarations }
  protected
    procedure WMDropFiles(var msg : TWMDropFiles); message WM_DROPFILES;
  public
    NeroSettings: PNeroSettings;
    NeroDeviceHandle: NERO_DEVICEHANDLE;
    NeroProgress: NERO_PROGRESS;
    NeroCDInfo: PNeroCDInfo;
    NeroWriteCD: PNeroWriteCD;
    NeroWriteVideoCD: PNeroWriteVideoCD;
    NeroWriteFreestyleCD: PNeroWriteFreestyleCD;
    NeroWriteImage: PNeroWriteImage;
    NeroDeviceInfos: PNeroSCSIDeviceInfos;

    procedure NeroError(Action: String);
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

uses DeviceDetails, Registry, MediaInformation;

{$R *.dfm}

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
begin
  Result := False;
end;

function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;
begin
  Result := DLG_WAITCD;
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
  Result := BOOL(GetLastError);
end;

procedure AddLogLine(pUserData: Pointer; _type: NERO_TEXT_TYPE; text: PChar); cdecl;
var
  Header: String;
begin
	case _type of
    NERO_TEXT_INFO:        // informative text
    begin
      header := 'i ';
    end;
    NERO_TEXT_STOP:        // some operation stopped prematurely
    begin
      header := '# ';
    end;
    NERO_TEXT_EXCLAMATION: // important information
    begin
      header := '! ';
    end;
    NERO_TEXT_QUESTION:    // a question which requires an answer
    begin
      header := '? ';
    end;
    NERO_TEXT_DRIVE:		   // a message concerning a CD-ROM drive or recorder
    begin
      header := '- ';
    end;
  end;

  ShowMessage(header + text);
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

end;

procedure TFMainForm.FormCreate(Sender: TObject);
var
  ver1, ver2, ver3,ver4: WORD;
  initErr: NEROAPI_INIT_ERROR;
  Callback_1, Callback_2: NERO_CALLBACK;
  DeviceCount: Integer;
  Registry: TRegistry;
begin
  NeroDeviceHandle := nil;
  NeroDeviceInfos := nil;
  NeroCDInfo := nil;
  NeroWriteCD := nil;
  NeroWriteVideoCD := nil;
  NeroWriteImage := nil;
  NeroWriteFreestyleCD := nil;
  NeroSettings := nil;
  sbMain.SimplePanel := true;

  if (NeroAPIGlueConnect(nil)) then
    sbMain.SimpleText := 'Connected to NeroAPI !'
  else
  begin
    sbMain.SimpleText := 'Cannot connect to NeroAPI !';
    exit;
  end;

	if (NeroGetAPIVersionEx(ver1, ver2, ver3, ver4, nil)) then
    sbMain.SimpleText :=  'Nero API version ' + IntToStr(ver1) + '.' +
      IntToStr(ver2) + '.' + IntToStr(ver3) + '.' + IntToStr(ver4)
  else
  begin
    sbMain.SimpleText := 'Could not get NeroAPI version number !';
    exit;
  end;

  NeroSettings := AllocMem(sizeof(TNeroSettings));


  Registry := TRegistry.Create(KEY_READ);
  Registry.RootKey := HKEY_LOCAL_MACHINE;
  Registry.OpenKey('SOFTWARE\Ahead\Shared', False);
  NeroSettings.nstNeroFilesPath := PAnsiChar(Registry.ReadString('NeroAPI'));
  Registry.Free;

  NeroSettings.nstVendor := '';
  NeroSettings.nstSoftware := 'ahead';
  NeroSettings.nstLanguageFile := 'nero.txt';

  Callback_1.ncCallbackFunction := @IdleCallback;
  Callback_1.ncUserData := nil;
  NeroSettings.nstIdle :=  Callback_1;

  Callback_2.ncCallbackFunction := @UserDialog;
  Callback_2.ncUserData := nil;
  NeroSettings.nstUserDialog := Callback_2;

  NeroSettings.nstEnableOverburn := False;
  NeroSettings.nstOverburnSize := 0;

  initErr := NeroInit(@NeroSettings, nil);
  case (initErr) of
    NEROAPI_INIT_OK: begin end;
    NEROAPI_INIT_INVALID_ARGS:
      sbMain.SimpleText := 'NeroInit() : invalid args';
    NEROAPI_INIT_INVALID_SERIAL_NUM:
      sbMain.SimpleText := 'NeroInit() : invalid serial number';
    NEROAPI_INIT_DEMOVERSION_EXPIRED:
      sbMain.SimpleText := 'NeroInit() : demo version has expired';
    NEROAPI_INIT_CANNOT_LOCK:
      sbMain.SimpleText := 'NeroInit() : cannot lock';
    NEROAPI_INIT_UNSPECIFIED_ERROR:
      sbMain.SimpleText := 'NeroInit() : unspecified error';
  else
    sbMain.SimpleText := 'NeroInit() : unspecified error';
  end;

  if initErr <> NEROAPI_INIT_OK then
    Exit;

  NeroDeviceInfos := PNeroSCSIDeviceInfos(NeroGetAvailableDrivesEx(MEDIA_CD, nil));
	if not Assigned(NeroDeviceInfos) then
		sbMain.SimpleText := 'NeroGetAvailableDrives()';

  for DeviceCount := 0 to NeroDeviceInfos.nsdisNumDevInfos - 1 do
  begin
    if NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDriveLetter = #0 then
      cbDevices.Items.Add(NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDeviceName)
    else
      cbDevices.Items.Add(NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDeviceName + ' (' + UpperCase(NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDriveLetter) + ':)');
  end;
  cbDevices.Enabled := (cbDevices.Items.Count > 0);

  for DeviceCount := 0 to NeroDeviceInfos.nsdisNumDevInfos - 1 do
    if NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiWriteSpeeds.nsiNumSupportedSpeeds > 0 then
    begin
      cbDevices.ItemIndex := DeviceCount;
      btnMoreDevice.Enabled := True;

      break;
    end;

  if cbDevices.ItemIndex > -1 then
  begin
    cbWriteSpeeds.Clear;
    for DeviceCount := 0 to NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiNumSupportedSpeeds - 1 do
      cbWriteSpeeds.Items.Add(FloatToStrF(NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[DeviceCount] / NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[DeviceCount]) + ' KB/s)' );
    cbWriteSpeeds.Enabled := (cbWriteSpeeds.Items.Count > 0);
    lbWriteSpeeds.Enabled := (cbWriteSpeeds.Items.Count > 0);

    cbWriteSpeeds.ItemIndex := cbWriteSpeeds.Items.Count - 1;

    btnRefresh.Enabled := True;

    cbDevicesCloseUp(self);
  end;

  pcWrite.TabIndex := pcWrite.PageCount - 1;

  DragAcceptFiles(self.WindowHandle, True);

  NeroProgress.npProgressCallback := ProgressCallback;
  NeroProgress.npAbortedCallback := AbortedCallback;
  NeroProgress.npAddLogLineCallback := AddLogLine;
  NeroProgress.npSetPhaseCallback := SetPhaseCallback;
  NeroProgress.npUserData := NeroSettings;
  NeroProgress.npDisableAbortCallback := DisableAbortCallback;
  NeroProgress.npSetMajorPhaseCallback := SetMajorPhaseCallback;
end;

procedure TFMainForm.FormDestroy(Sender: TObject);
begin
  DragAcceptFiles(self.WindowHandle, False);

  if Assigned(NeroDeviceHandle) then
    NeroCloseDevice(NeroDeviceHandle);

  if Assigned(NeroDeviceInfos) then
  	NeroFreeMem(NeroDeviceInfos);

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

  if Assigned(NeroSettings) then
    ReallocMem(NeroSettings, 0);

	NeroClearErrors;
	NeroDone;

	NeroAPIGlueDone;
end;

procedure TFMainForm.ApplicationEventsShowHint(var HintStr: String;
  var CanShow: Boolean; var HintInfo: THintInfo);
begin
  if CanShow then
		sbMain.SimpleText := Application.Hint;
end;

procedure TFMainForm.cbDevicesChange(Sender: TObject);
var
  DeviceCount: Integer;
begin
  btnMoreDevice.Enabled := (cbDevices.ItemIndex <> -1);

  if cbDevices.ItemIndex > -1 then
  begin
    cbWriteSpeeds.Clear;
    for DeviceCount := 0 to NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiNumSupportedSpeeds - 1 do
      cbWriteSpeeds.Items.Add(FloatToStrF(NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[DeviceCount] / NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[DeviceCount]) + ' KB/s)' );
    cbWriteSpeeds.Enabled := (cbWriteSpeeds.Items.Count > 0);
    lbWriteSpeeds.Enabled := (cbWriteSpeeds.Items.Count > 0);

    cbWriteSpeeds.ItemIndex := cbWriteSpeeds.Items.Count - 1;
    cbxBufferUnderrun.Checked := NeroDeviceInfos.nsdisDevInfos[FMainForm.cbDevices.itemIndex].nsdiMandatoryBUPSpeed > 0;

    btnRefresh.Enabled := True;
  end
  else
  begin
    btnRefresh.Enabled := False;
    cbWriteSpeeds.Enabled := False;
    btnMoreDevice.Enabled := False;
    btnMoreMedia.Enabled := False;
    stMedia.Caption := 'Device not selected';
    stMedia.Enabled := False;
    lbWriteSpeeds.Enabled := False;
  end;

end;

procedure TFMainForm.btnMoreDeviceClick(Sender: TObject);
begin
  FDeviceInformation.ShowModal;
end;

procedure TFMainForm.cbDevicesCloseUp(Sender: TObject);
begin
  if Assigned(NeroDeviceHandle) then
    NeroCloseDevice(NeroDeviceHandle);

  NeroDeviceHandle := NeroOpenDevice(@NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex]);

  btnRefreshClick(self);
end;

procedure TFMainForm.btnRefreshClick(Sender: TObject);
begin
  if Assigned(NeroDeviceHandle) then
  begin
    if Assigned(NeroCDInfo) then
      NeroFreeMem(NeroCDInfo);

    NeroCDInfo := NeroGetCDInfo(NeroDeviceHandle, NGCDI_READ_CD_TEXT or NGCDI_READ_ISRC);
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
  Time := NeroGetCDRWErasingTime(NeroDeviceHandle, NEROAPI_ERASE_ENTIRE);
  if (Time = -1) then
    NeroError('No CD inserted')
  else
    if (Time = -2) then
      NeroError('This CD recorder does not support CD-RW')
    else
      if (Time = -3) then
        NeroError('This media is not rewritable');
  sbMain.SimpleText := 'Erasing CD-RW. This will take ' + IntToStr(Time) + ' seconds.';
  time := NeroEraseCDRW(NeroDeviceHandle, NEROAPI_ERASE_ENTIRE);
  if (Time <> 0) then
    NeroError('Error erasing the CD-RW');

  btnRefreshClick(self);
end;

procedure TFMainForm.btnEjectClick(Sender: TObject);
begin
  NeroEjectLoadCD(NeroDeviceHandle, true);
  btnLoad.Enabled := True;
  btnEject.Enabled := False;
  btnRefreshClick(Sender);
end;

procedure TFMainForm.NeroError(Action: String);
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
  Time := NeroGetCDRWErasingTime(NeroDeviceHandle, NEROAPI_ERASE_QUICK);
  if (Time = -1) then
    NeroError('No CD inserted')
  else
    if (Time = -2) then
      NeroError('This CD recorder does not support CD-RW')
    else
      if (Time = -3) then
        NeroError('This media is not rewritable');
  sbMain.SimpleText := 'Erasing CD-RW. This will take ' + IntToStr(Time) + ' seconds.';
  time := NeroEraseCDRW(NeroDeviceHandle, NEROAPI_ERASE_QUICK);
  if (Time <> 0) then
    NeroError('Error erasing the CD-RW');

  btnRefreshClick(self);
end;

procedure TFMainForm.WMDropFiles(var msg: TWMDropFiles);
var
  CFileName: array [0 .. MAX_PATH] of Char;
  WhichFiles: TStringList;
  index, i, FilesCount, FileHandle: Integer;
  TrackName: String;
begin
  WhichFiles := TStringList.Create;
  try
    FilesCount := DragQueryFile(Msg.Drop, $FFFFFFFF, CFileName, MAX_PATH);
    for i := 0 to Pred(FilesCount) do
    begin
      if DragQueryFile(Msg.Drop, i, CFileName, MAX_PATH) > 0 then
      begin
        WhichFiles.Add(CFileName);
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
          end;
          2:
          begin
          end;
          3:
          begin
          end;
          4:
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
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mp3' then
            begin
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE_MP3;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.wma' then
            begin
              NeroWriteCD.nwcdTracks[i].natSourceDataExchg.ndeType := NERO_ET_FILE_WMA;
              continue;
            end;

            if LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.pcm' then
            begin
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
          5:
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
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_JPEG_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := $FFFFFFFF;
              continue;
            end;

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.avi') then
            begin
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_NONENCODED_VIDEO_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := 0;
              continue;
            end;

            if (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mpg') or
              (LowerCase(ExtractFileExt(WhichFiles.Strings[i])) = '.mpeg') then
            begin
              NeroWriteVideoCD.nwvcdItems[i].nviItemType := NERO_MPEG_ITEM;
              NeroWriteVideoCD.nwvcdItems[i].nviPauseAfterItem := 0;
              continue;
            end;
          end;
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
  NeroEjectLoadCD(NeroDeviceHandle, false);
  btnRefreshClick(Sender);
  btnLoad.Enabled := False;
  btnEject.Enabled := False;
end;

procedure TFMainForm.pcWriteChange(Sender: TObject);
begin
  if pcWrite.TabIndex < 6 then
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
      end;
      1:
      begin
      end;
      2:
      begin
      end;
      3:
      begin
      end;
      4:
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

        if Assigned(NeroCDInfo) then
        begin
          if NeroCDInfo.ncdiMediumType = NMT_UNKNOWN then
            NeroWriteCD.nwcdMediaType := MEDIA_DVD_ANY
          else
            NeroWriteCD.nwcdMediaType := MEDIA_CD;
        end
        else
            NeroWriteCD.nwcdMediaType := MEDIA_CD;

        edCDDAArtist.Text := '';
        edCDDATitle.Text := '';
        lbxCDDATracks.Items.Clear;

        NeroWriteCD.nwcdNumTracks := 0;
        NeroWriteCD.nwcdArtist := '';
        NeroWriteCD.nwcdTitle := '';
      end;
      5:
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

        NeroWriteVideoCD.nwvcdSVCD := False;
        NeroWriteVideoCD.nwvcdNumItems := 0;
        NeroWriteVideoCD.nwvcdIsoTrack := nil;
        NeroWriteVideoCD.nwvcdTempPath := '';
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

  NeroBurn(NeroDeviceHandle, NERO_ISO_AUDIO_CD, NeroWriteCD, Flags,
    NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[cbWriteSpeeds.ItemIndex],
    @NeroProgress);

  if Assigned(NeroWriteCD) then
    ReallocMem(NeroWriteCD, 0);

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

  NeroBurn(NeroDeviceHandle, NERO_BURN_IMAGE_CD, NeroWriteImage, Flags,
    NeroDeviceInfos.nsdisDevInfos[cbDevices.ItemIndex].nsdiWriteSpeeds.nsiSupportedSpeedsKBs[cbWriteSpeeds.ItemIndex],
    @NeroProgress);

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


end.
