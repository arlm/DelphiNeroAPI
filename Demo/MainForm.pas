unit MainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, NeroAPI, NeroUserDialog, ComCtrls;

type
  TFMainForm = class(TForm)
    sbMain: TStatusBar;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
  protected
    NeroDeviceHandle: NERO_DEVICEHANDLE;
    NeroDeviceInfos: PNERO_SCSI_DEVICE_INFOS;
    NeroCDInfo: PNERO_CD_INFO;
    NeroSettings: PNERO_SETTINGS;
  public
    { Public declarations }
  end;

function IdleCallback(pUserData: Pointer): Boolean; cdecl;
function UserDialog(pUserData: Pointer; Dtype: NeroUserDlgInOut; data: Pointer): NeroUserDlgInOut; cdecl;

var
  FMainForm: TFMainForm;

implementation

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
begin
  NeroDeviceHandle := nil;
  NeroDeviceInfos := nil;
  NeroCDInfo := nil;
  NeroSettings := nil;

  if (NeroAPIGlueConnect(nil)) then
    sbMain.Panels[0].Text := 'Connected to NeroAPI !'
  else
  begin
    sbMain.Panels[0].Text := 'Cannot connect to NeroAPI !';
    exit;
  end;

	if (NeroGetAPIVersionEx(ver1, ver2, ver3, ver4, nil)) then
    sbMain.Panels[1].Text := 'Nero API version ' + IntToStr(ver1) + '.' +
      IntToStr(ver2) + '.' + IntToStr(ver3) + '.' + IntToStr(ver4)
  else
  begin
    sbMain.Panels[0].Text := 'Could not get NeroAPI version number !';
    exit;
  end;

  NeroSettings := AllocMem(sizeof(TNeroSettings));

  NeroSettings.nstNeroFilesPath := 'D:\Programme\Ahead\Nero';
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

  initErr := NeroInit(NeroSettings, nil);
  case (initErr) of
    NEROAPI_INIT_OK:
      sbMain.Panels[0].Text := 'NeroAPI init() OK !';
    NEROAPI_INIT_INVALID_ARGS:
      sbMain.Panels[0].Text := 'NeroInit() : invalid args';
    NEROAPI_INIT_INVALID_SERIAL_NUM:
      sbMain.Panels[0].Text := 'NeroInit() : invalid serial number';
    NEROAPI_INIT_DEMOVERSION_EXPIRED:
      sbMain.Panels[0].Text := 'NeroInit() : demo version has expired';
    NEROAPI_INIT_CANNOT_LOCK:
      sbMain.Panels[0].Text := 'NeroInit() : cannot lock';
    NEROAPI_INIT_UNSPECIFIED_ERROR:
      sbMain.Panels[0].Text := 'NeroInit() : unspecified error';

  else
    sbMain.Panels[0].Text := 'NeroInit() : unspecified error';
  end;
  if initErr <> NEROAPI_INIT_OK then Exit;

//  NeroDeviceInfos := AllocMem(sizeof(NeroDeviceInfos));
  NeroDeviceInfos := NeroGetAvailableDrivesEx(MEDIA_CD, nil);
//  NeroDeviceInfos := NeroGetAvailableDrivesEx(MEDIA_DVD_ANY , nil);
	if not Assigned(NeroDeviceInfos) then
		sbMain.Panels[0].Text := 'NeroGetAvailableDrives()';


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

end.
