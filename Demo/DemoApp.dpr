program DemoApp;

uses
  Forms,
  MainForm in 'MainForm.pas' {FMainForm},
  DeviceDetails in 'DeviceDetails.pas' {FDeviceInformation};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFMainForm, FMainForm);
  Application.CreateForm(TFDeviceInformation, FDeviceInformation);
  Application.Run;
end.
