{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
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
|* NeroSDK / NeroAPI
|*
|* PURPOSE: DelphiNeroAPI Visual Component Classes
******************************************************************************}unit dnapiComponents;

interface

uses
 Windows, SysUtils, Classes, Forms, Controls, StdCtrls, NeroAPI, NeroUserDialog;

type
  TdnapiDevicesComboBox = class;
  TIdleCallback = function(pUserData: Pointer): Boolean;
  TUserDialogCallback = function(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut;

  TdnapiSettings = class(TComponent)
  private
    FNeroSettings: PNeroSettings;
    FDevices: TdnapiDevicesComboBox;
    FMessage: String;
    FVersion: String;
    FMinorVersion: WORD;
    FMajorVersion: WORD;
    FMinorBuild: WORD;
    FMajorBuild: WORD;
    function GetEnableOverburn: BOOL;
    function GetLanguageFile: String;
    function GetNeroFilesPath: String;
    function GetOverBurnSize: DWORD;
    function GetSoftware: String;
    function GetVendor: String;
    procedure SetLanguageFile(const Value: String);
    procedure SetNeroFilesPath(const Value: String);
    procedure SetOverburnSize(const Value: DWORD);
    procedure SetSoftware(const Value: String);
    procedure SetVendor(const Value: String);
    function GetOnIdle: TIdleCallback;
    function GetOnUserDialog: TUserDialogCallback;
    procedure SetOnIdle(const Value: TIdleCallback);
    procedure SetEnableOverburn(const Value: BOOL);
    procedure SetOnUserDialog(const Value: TUserDialogCallback);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetMessage(Value: String);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    property NeroSettings: PNeroSettings read FNeroSettings;
    property NeroAPIMajorVersion: WORD read FMajorVersion;
    property NeroAPIMinorVersion: WORD read FMinorVersion;
    property NeroAPIMajorBuild: WORD read FMajorBuild;
    property NeroAPIMinorBuild: WORD read FMinorBuild;

    property OnIdle: TIdleCallback read GetOnIdle write SetOnIdle;
    property OnUserDialog: TUserDialogCallback read GetOnUserDialog write SetOnUserDialog;
  published
    property Devices: TdnapiDevicesComboBox read FDevices write FDevices;
    property Message: String read FMessage;
    property NeroAPIVersion: String read FVersion;
    property NeroFilesPath: String read GetNeroFilesPath write SetNeroFilesPath;
    property Vendor: String read GetVendor write SetVendor;
    property Software: String read GetSoftware write SetSoftware;
    property LanguageFile: String read GetLanguageFile write SetLanguageFile;
    property EnableOverburn: BOOL read GetEnableOverburn write SetEnableOverburn;
    property OverburnSize: DWORD read GetOverBurnSize write SetOverburnSize;
  end;

  TdnapiDevicesComboBox = class(TCustomComboBox)
  private
    FNeroDeviceInfos: PNeroSCSIDeviceInfos;
    FSettings: TdnapiSettings;
    procedure SetSettings(const Value: TdnapiSettings);
  protected
    procedure GetDeviceInfo;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    property NeroDeviceInfos: PNeroSCSIDeviceInfos read FNeroDeviceInfos;
  published
    property Settings: TdnapiSettings read FSettings write SetSettings;
  end;

procedure Register;

implementation

uses Registry;

var
  OnIdleCallback: TIdleCallback;
  OnUserDialogCallback: TUserDialogCallback;

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
begin
  if Assigned(OnIdleCallback) then
    Result := OnIdleCallback(pUserData)
  else
  begin
    Application.ProcessMessages;

    Result := False;
  end;
end;

function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;
begin
  if Assigned(OnUserDialogCallback) then
    Result := OnUserDialogCallback(pUserData, Dtype, data)
  else
    Result := DLG_RETURN_EXIT;
end;

procedure Register;
begin
  RegisterComponents('DelphiNeroAPI', [TdnapiDevicesComboBox]);
  RegisterComponents('DelphiNeroAPI', [TdnapiSettings]);
end;

{ TdnapiDevicesComboBox }

constructor TdnapiDevicesComboBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

end;

destructor TdnapiDevicesComboBox.Destroy;
begin

  inherited;
end;

procedure TdnapiDevicesComboBox.GetDeviceInfo;
var
  DeviceCount: Integer;
begin
  if Assigned(Settings) then
  begin
    FNeroDeviceInfos := PNeroSCSIDeviceInfos(NeroGetAvailableDrivesEx(MEDIA_CD, nil));
    if not Assigned(FNeroDeviceInfos) then
      Settings.SetMessage('NeroGetAvailableDrives() error');

    for DeviceCount := 0 to NeroDeviceInfos.nsdisNumDevInfos - 1 do
    begin
      if FNeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDriveLetter = #0 then
        Items.Add(FNeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDeviceName)
      else
        Items.Add(FNeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDeviceName + ' (' + UpperCase(NeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiDriveLetter) + ':)');
    end;
    Enabled := (Items.Count > 0);

    for DeviceCount := 0 to FNeroDeviceInfos.nsdisNumDevInfos - 1 do
      if FNeroDeviceInfos.nsdisDevInfos[DeviceCount].nsdiWriteSpeeds.nsiNumSupportedSpeeds > 0 then
      begin
        ItemIndex := DeviceCount;
        break;
      end;
  end;
end;

procedure TdnapiDevicesComboBox.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);

  if AComponent.InheritsFrom(TdnapiSettings) then
    case Operation of
      opInsert:
      begin
        if not Assigned(FSettings) then
        begin
          FSettings := TdnapiSettings(AComponent);
          TdnapiSettings(AComponent).Devices := self;
        end;
      end;
      opRemove:
      begin
        if Assigned(FSettings) and (FSettings = AComponent) then
        begin
          FSettings := nil;
        end;
      end;
    end;
end;

procedure TdnapiDevicesComboBox.SetSettings(const Value: TdnapiSettings);
begin
  if Assigned(Value) and (FSettings <> Value) then
  begin
    FSettings := Value;

    FSettings.Devices := self;
    GetDeviceInfo;
  end;
end;

{ TdnapiSettings }

constructor TdnapiSettings.Create(AOwner: TComponent);
var
  initErr: NEROAPI_INIT_ERROR;
  Callback_1, Callback_2: NERO_CALLBACK;
  Registry: TRegistry;
begin
  inherited Create(AOwner);

  if not NeroAPIGlueConnect(nil) then
  begin
    FMessage := 'Cannot connect to NeroAPI !';
    exit;
  end;

	if NeroGetAPIVersionEx(FMajorVersion, FMinorVersion, FMajorBuild, FMinorBuild,
    nil) then
  begin
    FVersion :=  IntToStr(FMajorVersion) + '.' + IntToStr(FMinorVersion) + '.' +
      IntToStr(FMajorBuild) + '.' + IntToStr(FMinorBuild);
  end
  else
  begin
    FMessage := 'Could not get NeroAPI version number !';
    exit;
  end;

  FNeroSettings := AllocMem(sizeof(TNeroSettings));

  Registry := TRegistry.Create(KEY_READ);
  Registry.RootKey := HKEY_LOCAL_MACHINE;
  Registry.OpenKey('SOFTWARE\Ahead\Shared', False);
  FNeroSettings.nstNeroFilesPath := PAnsiChar(Registry.ReadString('NeroAPI'));
  Registry.Free;

  FNeroSettings.nstVendor := '';
  FNeroSettings.nstSoftware := 'ahead';
  FNeroSettings.nstLanguageFile := 'nero.txt';

  Callback_1.ncCallbackFunction := @IdleCallback;
  Callback_1.ncUserData := nil;
  NeroSettings.nstIdle :=  Callback_1;

  Callback_2.ncCallbackFunction := @UserDialog;
  Callback_2.ncUserData := nil;
  FNeroSettings.nstUserDialog := Callback_2;

  FNeroSettings.nstEnableOverburn := False;
  FNeroSettings.nstOverburnSize := 0;

  initErr := NeroInit(@FNeroSettings, nil);
  case (initErr) of
    NEROAPI_INIT_OK:
    begin
    end;
    NEROAPI_INIT_INVALID_ARGS:
      FMessage := 'NeroInit() : invalid args';
    NEROAPI_INIT_INVALID_SERIAL_NUM:
      FMessage := 'NeroInit() : invalid serial number';
    NEROAPI_INIT_DEMOVERSION_EXPIRED:
      FMessage := 'NeroInit() : demo version has expired';
    NEROAPI_INIT_CANNOT_LOCK:
      FMessage := 'NeroInit() : cannot lock';
    NEROAPI_INIT_UNSPECIFIED_ERROR:
      FMessage := 'NeroInit() : unspecified error';
  else
    FMessage := 'NeroInit() : unspecified error';
  end;

  if initErr <> NEROAPI_INIT_OK then
    Exit;

end;

destructor TdnapiSettings.Destroy;
begin
  if Assigned(FNeroSettings) then
    ReallocMem(FNeroSettings, 0);

	NeroClearErrors;
	NeroDone;

	NeroAPIGlueDone;

  inherited;
end;

function TdnapiSettings.GetEnableOverburn: BOOL;
begin
  Result := FNeroSettings.nstEnableOverburn;
end;

function TdnapiSettings.GetLanguageFile: String;
begin
  Result := FNeroSettings.nstLanguageFile;
end;

function TdnapiSettings.GetNeroFilesPath: String;
begin
  Result := FNeroSettings.nstNeroFilesPath
end;

function TdnapiSettings.GetOnIdle: TIdleCallback;
begin
 Result := OnIdleCallback;
end;

function TdnapiSettings.GetOnUserDialog: TUserDialogCallback;
begin
  Result := OnUserDialogCallback;
end;

function TdnapiSettings.GetOverBurnSize: DWORD;
begin
  Result := FNeroSettings.nstOverburnSize;
end;

function TdnapiSettings.GetSoftware: String;
begin
  Result := FNeroSettings.nstSoftware;
end;

function TdnapiSettings.GetVendor: String;
begin
  Result := FNeroSettings.nstVendor;
end;

procedure TdnapiSettings.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);

  if AComponent.InheritsFrom(TdnapiDevicesComboBox) then
    case Operation of
      opInsert:
      begin
        if not Assigned(FDevices) then
        begin
          FDevices := TdnapiDevicesComboBox(AComponent);
          TdnapiDevicesComboBox(AComponent).Settings := self;
        end;
      end;
      opRemove:
      begin
        if Assigned(FDevices) and (FDevices = AComponent) then
        begin
          FDevices := nil;
        end;
      end;
    end;
end;

procedure TdnapiSettings.SetEnableOverburn(const Value: BOOL);
begin
  FNeroSettings.nstEnableOverburn := Value;
end;

procedure TdnapiSettings.SetLanguageFile(const Value: String);
begin
  StrPCopy(FNeroSettings.nstLanguageFile, Value);
  FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstLanguageFile) - 1] := #00;
end;

procedure TdnapiSettings.SetMessage(Value: String);
begin
  FMessage := Value;
end;

procedure TdnapiSettings.SetNeroFilesPath(const Value: String);
begin
  StrPCopy(FNeroSettings.nstNeroFilesPath, Value);
  FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstNeroFilesPath) - 1] := #00;
end;

procedure TdnapiSettings.SetOnIdle(const Value: TIdleCallback);
begin
  if Assigned(Value) and (@OnIdleCallback <> @Value) then
    OnIdleCallback := Value;
end;

procedure TdnapiSettings.SetOnUserDialog(const Value: TUserDialogCallback);
begin
  if Assigned(Value) and (@OnUserDialogCallback <> @Value) then
    OnUserDialogCallback := Value;
end;

procedure TdnapiSettings.SetOverburnSize(const Value: DWORD);
begin
  FNeroSettings.nstOverburnSize := Value;
end;

procedure TdnapiSettings.SetSoftware(const Value: String);
begin
  StrPCopy(FNeroSettings.nstSoftware, Value);
  FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstSoftware) - 1] := #00;
end;

procedure TdnapiSettings.SetVendor(const Value: String);
begin
  StrPCopy(FNeroSettings.nstVendor, Value);
  FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstVendor) - 1] := #00;
end;

initialization
  OnIdleCallback := nil;
  OnUserDialogCallback := nil;

finalization

end.
