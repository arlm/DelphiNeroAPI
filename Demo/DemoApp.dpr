program DemoApp;

uses
  Forms,
  MainForm in 'MainForm.pas' {FMainForm},
  NeroAPI in '..\New\NeroAPI.pas',
  NeroFileSystemContent in '..\New\NeroFileSystemContent.pas',
  NeroIsoTrack in '..\New\NeroIsoTrack.pas',
  NeroPacketWriting in '..\New\NeroPacketWriting.pas',
  NeroUserDialog in '..\New\NeroUserDialog.pas',
  FileSystemBlockAccessExtensions in '..\New\NeroFileSystemManager\FileSystemBlockAccessExtensions.pas',
  FileSystemBlockAccessInterface in '..\New\NeroFileSystemManager\FileSystemBlockAccessInterface.pas',
  FileSystemBlockReaderInterface in '..\New\NeroFileSystemManager\FileSystemBlockReaderInterface.pas',
  FileSystemBlockWriterInterface in '..\New\NeroFileSystemManager\FileSystemBlockWriterInterface.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFMainForm, FMainForm);
  Application.Run;
end.
