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
  Dialogs, NeroAPI, NeroUserDialog, ComCtrls, StdCtrls, AppEvnts;

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
  private
    { Private declarations }
  protected
  public
    NeroDeviceInfos: PNeroSCSIDeviceInfos;
    NeroSettings: PNeroSettings;
    NeroDeviceHandle: NERO_DEVICEHANDLE;
    NeroCDInfo: PNeroCDInfo;
    procedure NeroError(Action: String);
  end;

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;

var
  FMainForm: TFMainForm;

implementation

uses DeviceDetails, Registry, MediaInformation;

{$R *.dfm}

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
begin
  Result := True;
end;

function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;
begin
  Result := DLG_WAITCD;
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
end;

procedure TFMainForm.FormDestroy(Sender: TObject);
begin
  if Assigned(NeroDeviceHandle) then
    NeroCloseDevice(NeroDeviceHandle);

  if Assigned(NeroDeviceInfos) then
  	NeroFreeMem(NeroDeviceInfos);

  if Assigned(NeroCDInfo) then
  	NeroFreeMem(NeroCDInfo);

  if Assigned(NeroSettings) then
    FreeMemory(NeroSettings);

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
      lbFreeBlocks.Caption := IntToStr(NeroCDInfo.ncdiFreeCapacityInBlocks) + ' Free Blocks';
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
  NeroEjectLoadCD(NeroDeviceHandle, True);
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

end.
