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
******************************************************************************}
unit dnapiComponents;

interface
uses
 Windows, SysUtils, Classes, Forms, Controls, StdCtrls, NeroAPI, NeroUserDialog;

type
  TdnapiDevicesComboBox = class;
  TdnapiDeviceSpeedComboBox = class;

  TErrorEvent = procedure(Sender: TObject; Message: String) of object;
  TIdleCallback = function(pUserData: Pointer): Boolean of object;
  TUserDialogCallback = function(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut of object;

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
    FActive: Boolean;
    FEnableOverburn: BOOL;
    FOverBurnSize: DWORD;
    FVendor: String;
    FLanguageFile: String;
    FNeroFilesPath: String;
    FSoftware: String;
    FOnActivate: TNotifyEvent;
    FOnError: TErrorEvent;
    FOnDeActivate: TNotifyEvent;
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
    procedure SetActive(const Value: Boolean);
    procedure SetVersion(const Value: String);
    function GetOnActivate: TNotifyEvent;
    function GetOnDeActivate: TNotifyEvent;
    procedure SetOnActivate(const Value: TNotifyEvent);
    procedure SetOnDeActivate(const Value: TNotifyEvent);
    function GetOnError: TErrorEvent;
    procedure SetOnError(const Value: TErrorEvent);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetMessage(Value: String);

    property Message: String read FMessage;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    property NeroSettings: PNeroSettings read FNeroSettings;
    property NeroAPIMajorVersion: WORD read FMajorVersion;
    property NeroAPIMinorVersion: WORD read FMinorVersion;
    property NeroAPIMajorBuild: WORD read FMajorBuild;
    property NeroAPIMinorBuild: WORD read FMinorBuild;

  published
    property Active: Boolean read FActive write SetActive;
    property Devices: TdnapiDevicesComboBox read FDevices write FDevices;
    property NeroAPIVersion: String read FVersion write SetVersion;
    property NeroFilesPath: String read FNeroFilesPath write SetNeroFilesPath;
    property Vendor: String read FVendor write SetVendor;
    property Software: String read FSoftware write SetSoftware;
    property LanguageFile: String read FLanguageFile write SetLanguageFile;
    property EnableOverburn: BOOL read FEnableOverburn write SetEnableOverburn;
    property OverburnSize: DWORD read FOverBurnSize write SetOverburnSize;

    property OnIdle: TIdleCallback read GetOnIdle write SetOnIdle;
    property OnUserDialog: TUserDialogCallback read GetOnUserDialog write SetOnUserDialog;
    property OnError: TErrorEvent read GetOnError write SetOnError;
    property OnActivate: TNotifyEvent read GetOnActivate write SetOnActivate;
    property OnDeActivate: TNotifyEvent read GetOnDeActivate write SetOnDeActivate;
  end;

  TdnapiDevicesComboBox = class(TCustomComboBox)
  private
    FNeroDeviceInfos: PNeroSCSIDeviceInfos;
    FSettings: TdnapiSettings;
    FSelectedDeviceHandle: NERO_DEVICEHANDLE;
    FActive: Boolean;
    FDeviceSpeeds: TdnapiDeviceSpeedComboBox;
    procedure SetSettings(const Value: TdnapiSettings);
    function GetSelectedDevice: PNeroSCSIDeviceInfo;
    procedure SetActive(const Value: Boolean);
    procedure SetDeviceSpeeds(const Value: TdnapiDeviceSpeedComboBox);
  protected
    procedure GetDeviceInfo;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure Change; override;
    procedure CloseUp; override;
    property Style; {Must be published before Items}
    property OnMeasureItem;
    property CharCase;
    property Sorted;
    property Text;
    property ItemIndex default -1;
    property Items; { Must be published after OnMeasureItem }
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    property NeroDeviceInfos: PNeroSCSIDeviceInfos read FNeroDeviceInfos;
    property SelectedDevice: PNeroSCSIDeviceInfo read GetSelectedDevice;
    property SelectedDeviceHandle: NERO_DEVICEHANDLE read FSelectedDeviceHandle;
  published
    property Active: Boolean read FActive write SetActive;
    property Settings: TdnapiSettings read FSettings write SetSettings;
    property DeviceSpeeds: TdnapiDeviceSpeedComboBox read FDeviceSpeeds write SetDeviceSpeeds;
    property AutoComplete default True;
    property AutoDropDown default False;
    property AutoCloseUp default False;
    property BevelEdges;
    property BevelInner;
    property BevelKind default bkNone;
    property BevelOuter;
    property Anchors;
    property BiDiMode;
    property Color;
    property Constraints;
    property Ctl3D;
    property DragCursor;
    property DragKind;
    property DragMode;
    property DropDownCount;
    property Enabled;
    property Font;
    property ImeMode;
    property ImeName;
    property ItemHeight;
    property MaxLength;
    property ParentBiDiMode;
    property ParentColor;
    property ParentCtl3D;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnChange;
    property OnClick;
    property OnCloseUp;
    property OnContextPopup;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnDrawItem;
    property OnDropDown;
    property OnEndDock;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnSelect;
    property OnStartDock;
    property OnStartDrag;
  end;

  TSpeedKind = (skRead, skWrite);

  TdnapiDeviceSpeedComboBox = class(TCustomComboBox)
  private
    FDevice: TdnapiDevicesComboBox;
    FActive: Boolean;
    FKind: TSpeedKind;
    procedure SetDevice(const Value: TdnapiDevicesComboBox);
    procedure SetActive(const Value: Boolean);
    function GetBaseSpeedKBs: DWORD;
    function GetSpeed: Extended;
    function GetSpeedKBs: DWORD;
    procedure SetKind(const Value: TSpeedKind);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    property Style; {Must be published before Items}
    property OnMeasureItem;
    property CharCase;
    property Sorted;
    property Text;
    property ItemIndex default -1;
    property Items; { Must be published after OnMeasureItem }
  public
    constructor Create(AOwner: TComponent); override;

    property Speed: Extended read GetSpeed;
    property SpeedKBs: DWORD read GetSpeedKBs;
    property BaseSpeedKBs: DWORD read GetBaseSpeedKBs;
  published
    property Device: TdnapiDevicesComboBox read FDevice write SetDevice;
    property Kind: TSpeedKind read FKind write SetKind default skWrite;
    property Active: Boolean read FActive write SetActive;
    property AutoComplete default True;
    property AutoDropDown default False;
    property AutoCloseUp default False;
    property BevelEdges;
    property BevelInner;
    property BevelKind default bkNone;
    property BevelOuter;
    property Anchors;
    property BiDiMode;
    property Color;
    property Constraints;
    property Ctl3D;
    property DragCursor;
    property DragKind;
    property DragMode;
    property DropDownCount;
    property Enabled;
    property Font;
    property ImeMode;
    property ImeName;
    property ItemHeight;
    property MaxLength;
    property ParentBiDiMode;
    property ParentColor;
    property ParentCtl3D;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnChange;
    property OnClick;
    property OnCloseUp;
    property OnContextPopup;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnDrawItem;
    property OnDropDown;
    property OnEndDock;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnSelect;
    property OnStartDock;
    property OnStartDrag;
  end;

procedure Register;

implementation

uses Registry, Dialogs;

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
  RegisterComponents('DelphiNeroAPI', [TdnapiDeviceSpeedComboBox]);
  RegisterComponents('DelphiNeroAPI', [TdnapiSettings]);
end;

{ TdnapiDevicesComboBox }

procedure TdnapiDevicesComboBox.Change;
begin
  if Assigned(FDeviceSpeeds) then
  begin
    if Items.Count > 0 then
    begin
      if FDeviceSpeeds.Active then
        FDeviceSpeeds.SetActive(False);
      FDeviceSpeeds.SetActive(True);
    end;
  end;

  inherited Change;
end;

procedure TdnapiDevicesComboBox.CloseUp;
begin
  if Items.Count > 0 then
    GetSelectedDevice;

  inherited CloseUp;
end;

constructor TdnapiDevicesComboBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

  FActive := False;
  FSelectedDeviceHandle := nil;
  Style := csDropDownList;
end;

destructor TdnapiDevicesComboBox.Destroy;
begin
  if Assigned(FSelectedDeviceHandle) then
    NeroCloseDevice(FSelectedDeviceHandle);

  inherited;
end;

procedure TdnapiDevicesComboBox.GetDeviceInfo;
var
  DeviceCount: Integer;
begin
  if Assigned(Settings) then
    if Settings.Active then
    begin
      FNeroDeviceInfos := NeroGetAvailableDrivesEx(MEDIA_CD, nil);

      if not Assigned(FNeroDeviceInfos) then
        Settings.SetMessage('NeroGetAvailableDrives() error');

      Clear;
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
          SetItemIndex(DeviceCount);
          break;
        end;

      GetSelectedDevice;

      SetActive(True);
    end;
end;

function TdnapiDevicesComboBox.GetSelectedDevice: PNeroSCSIDeviceInfo;
begin
  if Assigned(FSelectedDeviceHandle) then
    NeroCloseDevice(FSelectedDeviceHandle);

  Result := @FNeroDeviceInfos.nsdisDevInfos[ItemIndex];
  FSelectedDeviceHandle := NeroOpenDevice(Result);
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
          SetSettings(TdnapiSettings(AComponent));
          FSettings.FreeNotification(self);
        end;
      end;
      opRemove:
      begin
        if Assigned(FSettings) and (FSettings = AComponent) then
        begin
          SetSettings(nil);
        end;
      end;
    end;

  if AComponent.InheritsFrom(TdnapiDeviceSpeedComboBox) then
    case Operation of
      opInsert:
      begin
        if not Assigned(FDeviceSpeeds) then
        begin
          SetDeviceSpeeds(TdnapiDeviceSpeedComboBox(AComponent));
          DeviceSpeeds.FreeNotification(self);
        end;
      end;
      opRemove:
      begin
        if Assigned(FDeviceSpeeds) and (FDeviceSpeeds = AComponent) then
        begin
          SetDeviceSpeeds(nil);
        end;
      end;
    end;
end;

procedure TdnapiDevicesComboBox.SetActive(const Value: Boolean);
begin
  if FActive <> Value then
  begin
    FActive := Value;

    if Value then
    begin
      if Assigned(FSelectedDeviceHandle) then
      begin
        NeroCloseDevice(FSelectedDeviceHandle);
        FSelectedDeviceHandle := nil;
      end;

      GetDeviceInfo;

      if Assigned(FDeviceSpeeds) then
        FDeviceSpeeds.SetActive(True);
    end
    else
    begin
      Clear;

      if Assigned(FSelectedDeviceHandle) then
      begin
        NeroCloseDevice(FSelectedDeviceHandle);
        FSelectedDeviceHandle := nil;
      end;
    end;
  end;
end;

procedure TdnapiDevicesComboBox.SetDeviceSpeeds(
  const Value: TdnapiDeviceSpeedComboBox);
begin
  if (FDeviceSpeeds <> Value) then
  begin
    FDeviceSpeeds := Value;

    if Assigned(Value) then
    begin
      FDeviceSpeeds.SetDevice(self);
    end;
  end;
end;

procedure TdnapiDevicesComboBox.SetSettings(const Value: TdnapiSettings);
begin
  if (FSettings <> Value) then
  begin
    FSettings := Value;

    if Assigned(Value) then
    begin
      FSettings.Devices := self;
      GetDeviceInfo;
    end
    else
    begin
      SetActive(False);
    end;
  end;
end;

{ TdnapiSettings }

constructor TdnapiSettings.Create(AOwner: TComponent);
var
  Registry: TRegistry;
begin
  inherited Create(AOwner);

  FNeroSettings := nil;
  FOnActivate := nil;
  FOnDeActivate := nil;

  FActive := False;


  Registry := TRegistry.Create(KEY_READ);
  Registry.RootKey := HKEY_LOCAL_MACHINE;
  Registry.OpenKey('SOFTWARE\Ahead\Shared', False);
  FNeroFilesPath := Registry.ReadString('NeroAPI');
  Registry.Free;

  FEnableOverburn := False;
  FLanguageFile := 'nero.txt';
  FOverburnSize := 0;
  FSoftware := 'ahead';
  FVendor := '';
  FVersion := 'NeroAPI not active';
end;

destructor TdnapiSettings.Destroy;
begin
  SetActive(False);

  inherited;
end;

function TdnapiSettings.GetOnActivate: TNotifyEvent;
begin
  Result := FOnActivate;
end;

function TdnapiSettings.GetOnDeActivate: TNotifyEvent;
begin
  Result := FOnDeActivate;
end;

function TdnapiSettings.GetOnError: TErrorEvent;
begin
  Result := FOnError;
end;

function TdnapiSettings.GetOnIdle: TIdleCallback;
begin
 Result := OnIdleCallback;
end;

function TdnapiSettings.GetOnUserDialog: TUserDialogCallback;
begin
  Result := OnUserDialogCallback;
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
          TdnapiDevicesComboBox(AComponent).SetSettings(self);
          FDevices.FreeNotification(self);
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

procedure TdnapiSettings.SetActive(const Value: Boolean);
var
  initErr: NEROAPI_INIT_ERROR;
  Callback_1, Callback_2: NERO_CALLBACK;
begin
  if FActive <> Value then
  begin
    if Value then
    begin
      if not NeroAPIGlueConnect(nil) then
      begin
        FMessage := 'Cannot connect to NeroAPI !';
        if Assigned(FOnError) then
          FOnError(self, FMessage);
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
        if Assigned(FOnError) then
          FOnError(self, FMessage);
        exit;
      end;

      FNeroSettings := AllocMem(sizeof(TNeroSettings));

      FNeroSettings.nstLanguageFile := PAnsiChar(FLanguageFile);
      FNeroSettings.nstNeroFilesPath := PAnsiChar(IncludeTrailingPathDelimiter(FNeroFilesPath));
      FNeroSettings.nstSoftware := PAnsiChar(FSoftware);
      FNeroSettings.nstVendor := PAnsiChar(FVendor);

      Callback_1.ncCallbackFunction := @IdleCallback;
      Callback_1.ncUserData := nil;
      NeroSettings.nstIdle :=  Callback_1;

      Callback_2.ncCallbackFunction := @UserDialog;
      Callback_2.ncUserData := nil;
      FNeroSettings.nstUserDialog := Callback_2;

      FNeroSettings.nstEnableOverburn := FEnableOverburn;
      FNeroSettings.nstOverburnSize := FOverBurnSize;

      initErr := NeroInit(@FNeroSettings, nil);
      case (initErr) of
        NEROAPI_INIT_OK:
        begin
          FActive := True;

          if Assigned(FDevices) then
            FDevices.SetActive(True);

          if Assigned(FOnActivate) then
            FOnActivate(Self);
        end;
        NEROAPI_INIT_ALREADY_INITIALISED:
        begin
          FActive := True;
          FMessage := 'NeroInit() : already initialized';

          if Assigned(FDevices) then
            FDevices.SetActive(True);

          if Assigned(FOnActivate) then
            FOnActivate(Self);
        end;
        NEROAPI_INIT_INVALID_ARGS:
        begin
          FMessage := 'NeroInit() : invalid args';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
        NEROAPI_INIT_INVALID_SERIAL_NUM:
        begin
          FMessage := 'NeroInit() : invalid serial number';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
        NEROAPI_INIT_DEMOVERSION_EXPIRED:
        begin
          FMessage := 'NeroInit() : demo version has expired';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
        NEROAPI_INIT_CANNOT_LOCK:
        begin
          FMessage := 'NeroInit() : cannot lock';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
        NEROAPI_INIT_UNSPECIFIED_ERROR:
        begin
          FMessage := 'NeroInit() : unspecified error';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
      else
        begin
          FMessage := 'NeroInit() : unspecified error';
          if Assigned(FOnError) then
            FOnError(self, FMessage);
        end;
      end;
    end
    else
    begin
      if Assigned(FNeroSettings) then
      begin
        ReallocMem(FNeroSettings, 0);
        FNeroSettings := nil;
      end;

      NeroClearErrors;
      NeroAPIGlueDone;

      FVersion := 'NeroAPI not active';

      if Assigned(FOnDeActivate) then
        FOnDeActivate(self);
    end;
  end;
end;

procedure TdnapiSettings.SetEnableOverburn(const Value: BOOL);
begin
  if Assigned(FNeroSettings) then
    FNeroSettings.nstEnableOverburn := Value;
end;

procedure TdnapiSettings.SetLanguageFile(const Value: String);
begin
  if Assigned(FNeroSettings) then
  begin
    StrPCopy(FNeroSettings.nstLanguageFile, Value);
    FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstLanguageFile) - 1] := #00;
  end;
end;

procedure TdnapiSettings.SetMessage(Value: String);
begin
  FMessage := Value;
end;

procedure TdnapiSettings.SetNeroFilesPath(const Value: String);
begin
  if Assigned(FNeroSettings) then
  begin
    StrPCopy(FNeroSettings.nstNeroFilesPath, Value);
    FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstNeroFilesPath) - 1] := #00;
  end;
end;

procedure TdnapiSettings.SetOnActivate(const Value: TNotifyEvent);
begin
    FOnActivate := Value;
end;

procedure TdnapiSettings.SetOnDeActivate(const Value: TNotifyEvent);
begin
    FOnDeActivate := Value;
end;

procedure TdnapiSettings.SetOnError(const Value: TErrorEvent);
begin
  FOnError := Value;
end;

procedure TdnapiSettings.SetOnIdle(const Value: TIdleCallback);
begin
  OnIdleCallback := Value;
end;

procedure TdnapiSettings.SetOnUserDialog(const Value: TUserDialogCallback);
begin
  OnUserDialogCallback := Value;
end;

procedure TdnapiSettings.SetOverburnSize(const Value: DWORD);
begin
  if Assigned(FNeroSettings) then
    FNeroSettings.nstOverburnSize := Value;
end;

procedure TdnapiSettings.SetSoftware(const Value: String);
begin
  if Assigned(FNeroSettings) then
  begin
    StrPCopy(FNeroSettings.nstSoftware, Value);
    FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstSoftware) - 1] := #00;
  end;
end;

procedure TdnapiSettings.SetVendor(const Value: String);
begin
  if Assigned(FNeroSettings) then
  begin
    StrPCopy(FNeroSettings.nstVendor, Value);
    FNeroSettings.nstLanguageFile[SizeOf(FNeroSettings.nstVendor) - 1] := #00;
  end;
end;

procedure TdnapiSettings.SetVersion(const Value: String);
begin
  // Do nothig because this is a read-only property
end;

{ TdnapiDeviceSpeedComboBox }

constructor TdnapiDeviceSpeedComboBox.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

  FActive := False;
  FDevice := nil;
  Style := csDropDownList;
  FKind := skWrite;
end;

function TdnapiDeviceSpeedComboBox.GetBaseSpeedKBs: DWORD;
begin
  Result := 0;

  if Assigned(FDevice) then
  begin
    if FDevice.Active then
    begin
      if Kind = skRead then
        Result := FDevice.SelectedDevice.nsdiReadSpeeds.nsiBaseSpeedKBs;
      if Kind = skWrite then
        Result := FDevice.SelectedDevice.nsdiReadSpeeds.nsiBaseSpeedKBs;
    end;
  end;
end;

function TdnapiDeviceSpeedComboBox.GetSpeed: Extended;
begin
  Result := 0;

  if Assigned(FDevice) then
  begin
    if FDevice.Active then
    begin
      if Kind = skRead then
      begin
        Result := FDevice.SelectedDevice.nsdiReadSpeeds.nsiSupportedSpeedsKBs[ItemIndex];
        Result := Result / FDevice.SelectedDevice.nsdiReadSpeeds.nsiBaseSpeedKBs;
      end;

      if Kind = skWrite then
      begin
        Result := FDevice.SelectedDevice.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[ItemIndex];
        Result := Result / FDevice.SelectedDevice.nsdiWriteSpeeds.nsiBaseSpeedKBs;
      end;
    end;
  end;
end;

function TdnapiDeviceSpeedComboBox.GetSpeedKBs: DWORD;
begin
  Result := 0;

  if Assigned(FDevice) then
  begin
    if FDevice.Active then
    begin
      if Kind = skRead then
        Result := FDevice.SelectedDevice.nsdiReadSpeeds.nsiSupportedSpeedsKBs[ItemIndex];
      if Kind = skWrite then
        Result := FDevice.SelectedDevice.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[ItemIndex];
    end;
  end;
end;

procedure TdnapiDeviceSpeedComboBox.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);

  if AComponent.InheritsFrom(TdnapiDevicesComboBox) then
    case Operation of
      opInsert:
      begin
        if not Assigned(FDevice) then
        begin
          SetDevice(TdnapiDevicesComboBox(AComponent))
        end;
      end;
      opRemove:
      begin
        if Assigned(FDevice) and (FDevice = AComponent) then
        begin
          SetDevice(nil);
        end;
      end;
    end;
end;

procedure TdnapiDeviceSpeedComboBox.SetActive(const Value: Boolean);
var
  SpeedCount: Integer;
begin
  if Value <> FActive then
  begin
    FActive := Value;

    if Value then
    begin
      if Assigned(FDevice) then
      begin
        if FDevice.Active then
        begin
          Clear;

          if Kind = skRead then
            for SpeedCount := 0 to FDevice.SelectedDevice.nsdiReadSpeeds.nsiNumSupportedSpeeds - 1 do
              Items.Add(FloatToStrF(FDevice.SelectedDevice.nsdiReadSpeeds.nsiSupportedSpeedsKBs[SpeedCount] / FDevice.SelectedDevice.nsdiReadSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(FDevice.SelectedDevice.nsdiReadSpeeds.nsiSupportedSpeedsKBs[SpeedCount]) + ' KB/s)' );

          if Kind = skWrite then
            for SpeedCount := 0 to FDevice.SelectedDevice.nsdiWriteSpeeds.nsiNumSupportedSpeeds - 1 do
              Items.Add(FloatToStrF(FDevice.SelectedDevice.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[SpeedCount] / FDevice.SelectedDevice.nsdiWriteSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(FDevice.SelectedDevice.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[SpeedCount]) + ' KB/s)' );

          ItemIndex := Items.Count - 1;
        end
        else
          FActive:= False;
      end
      else
        FActive:= False;
    end
    else
    begin
      Clear;
    end;
  end;
end;

procedure TdnapiDeviceSpeedComboBox.SetDevice(
  const Value: TdnapiDevicesComboBox);
begin
  if (FDevice <> Value) then
  begin
    FDevice := Value;

    if Assigned(Value) then
    begin
      FDevice.SetDeviceSpeeds(self);
      SetActive(FDevice.Active);
      FDevice.FreeNotification(self);
    end
    else
    begin
      SetActive(False);
    end;
  end;
end;

procedure TdnapiDeviceSpeedComboBox.SetKind(const Value: TSpeedKind);
begin
  FKind := Value;
end;

initialization
  OnIdleCallback := nil;
  OnUserDialogCallback := nil;

finalization

end.
