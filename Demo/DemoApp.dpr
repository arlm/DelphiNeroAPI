program DemoApp;

uses
  Forms,
  MainForm in 'MainForm.pas' {FMainForm},
  DeviceDetails in 'DeviceDetails.pas' {FDeviceInformation},
  MediaInformation in 'MediaInformation.pas' {FMediaInfo},
  FileSystemBlockAccessExtensions in '..\API\FileSystemBlockAccessExtensions.pas',
  FileSystemBlockAccessInterface in '..\API\FileSystemBlockAccessInterface.pas',
  FileSystemBlockReaderInterface in '..\API\FileSystemBlockReaderInterface.pas',
  FileSystemBlockWriterInterface in '..\API\FileSystemBlockWriterInterface.pas',
  NeroAPI in '..\API\NeroAPI.pas',
  NeroFileSystemContent in '..\API\NeroFileSystemContent.pas',
  NeroIsoTrack in '..\API\NeroIsoTrack.pas',
  NeroPacketWriting in '..\API\NeroPacketWriting.pas',
  NeroUserDialog in '..\API\NeroUserDialog.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFMainForm, FMainForm);
  Application.CreateForm(TFDeviceInformation, FDeviceInformation);
  Application.CreateForm(TFMediaInfo, FMediaInfo);
  Application.Run;
end.
