program DemoApp;

uses
  Forms,
  MainForm in 'MainForm.pas' {FMainForm},
  DeviceDetails in 'DeviceDetails.pas' {FDeviceInformation},
  MediaInformation in 'MediaInformation.pas' {FMediaInfo};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFMainForm, FMainForm);
  Application.CreateForm(TFDeviceInformation, FDeviceInformation);
  Application.CreateForm(TFMediaInfo, FMediaInfo);
  Application.Run;
end.
