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
|* PURPOSE: Device Information
******************************************************************************}
unit DeviceDetails;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, NeroAPI;

type
  TFDeviceInformation = class(TForm)
    lbxReadSpeeds: TListBox;
    lbReadSpeeds: TLabel;
    lbxWriteSpeeds: TListBox;
    lbWriteSpeeds: TLabel;
    stName: TStaticText;
    lbHostAdapter: TLabel;
    lbBurnProofSpeed: TLabel;
    lbxMediaTypes: TListBox;
    lbMediaTypes: TLabel;
    lbxCapabilites: TListBox;
    lbCapabilities: TLabel;
    lbBurnProofMethod: TLabel;
    lbBuffer: TLabel;
    btnClose: TButton;
    procedure FormShow(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
  private
    NeroDeviceInfo: PNeroSCSIDeviceInfo;
  public
    { Public declarations }
  end;

var
  FDeviceInformation: TFDeviceInformation;

implementation

uses MainForm, StrUtils;

{$R *.dfm}

procedure TFDeviceInformation.FormShow(Sender: TObject);
var
  Counter: Integer;
  Devices: String;
begin
  NeroDeviceInfo := FMainForm.dnapiDevices.SelectedDevice;

  if NeroDeviceInfo.nsdiDriveLetter = #0 then
    stName.Caption := NeroDeviceInfo.nsdiDeviceName
  else
    stName.Caption := NeroDeviceInfo.nsdiDeviceName + ' (' + UpperCase(NeroDeviceInfo.nsdiDriveLetter) + ':)';

  if NeroDeviceInfo.nsdiHostAdapterNo = DWORD(-1) then
    lbHostAdapter.Caption := 'Host Adapter : ' + NeroDeviceInfo.nsdiHostAdapterName
  else
    lbHostAdapter.Caption := 'Host Adapter : ' + NeroDeviceInfo.nsdiHostAdapterName + ' (' + IntToStr(NeroDeviceInfo.nsdiHostAdapterNo) + ':' + IntToStr(NeroDeviceInfo.nsdiDeviceID) + ')';

  lbBurnProofMethod.Caption := 'Burn-proof Method : ' + NeroDeviceInfo.nsdiBufUnderrunProtName;
  lbBurnProofMethod.Visible := (NeroDeviceInfo.nsdiBufUnderrunProtName <> '');

  lbBurnProofSpeed.Caption := 'Burn-proof Recommended Speed : ' + IntToStr(NeroDeviceInfo.nsdiMandatoryBUPSpeed);
  lbBurnProofSpeed.Visible := (NeroDeviceInfo.nsdiMandatoryBUPSpeed > 0);

  if NeroDeviceInfo.nsdiDriveBufferSize > 1024 then
    lbBuffer.Caption := 'Buffer Size : ' + FloatToStrF(NeroDeviceInfo.nsdiDriveBufferSize / 1024, ffFixed, 1, 1) + ' MB (' + IntToStr(NeroDeviceInfo.nsdiDriveBufferSize) + ' KB)'
  else
    lbBuffer.Caption := 'Buffer Size : ' + IntToStr(NeroDeviceInfo.nsdiDriveBufferSize) + ' KB';
  lbBuffer.Visible := (NeroDeviceInfo.nsdiDriveBufferSize > 0);

  lbxMediaTypes.Clear;
  Devices := NeroGetTypeNameOfMedia(NeroDeviceInfo.nsdiMediaSupport);
  if Devices = '' then
    lbxMediaTypes.Items.Add('No writeable media supported')
  else
  begin
    while LastDelimiter(';', Devices) > 0 do
    begin
      lbxMediaTypes.Items.Add(Trim(RightStr(Devices, Length(Devices) - LastDelimiter(';', Devices))));
      Devices := LeftStr(Devices, LastDelimiter(';', Devices) - 1);
    end;
      lbxMediaTypes.Items.Add(Trim(Devices));
  end;

  lbxCapabilites.Clear;
  if not ((NeroDeviceInfo.nsdiCapabilities and NSDI_ALLOWED) = NSDI_ALLOWED) then
    lbxCapabilites.Items.Add('Not Allowed !');

  if (NeroDeviceInfo.nsdiCapabilities and NSDI_DAO) = NSDI_DAO then
    lbxCapabilites.Items.Add('Can write in DAO');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_READ_CD_TEXT) = NSDI_READ_CD_TEXT then
    lbxCapabilites.Items.Add('Can read CD TEXT');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_VARIABLE_PAUSES_IN_TAO) = NSDI_VARIABLE_PAUSES_IN_TAO then
    lbxCapabilites.Items.Add('Can write valiable pauses in TAO');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_DAO_WRITE_CD_TEXT) = NSDI_DAO_WRITE_CD_TEXT then
    lbxCapabilites.Items.Add('Can write CD TEXT in DAO');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_IMAGE_RECORDER) = NSDI_IMAGE_RECORDER then
    lbxCapabilites.Items.Add('Drive is the image recorder');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_UNDETECTED) = NSDI_UNDETECTED then
    lbxCapabilites.Items.Add('Undetected');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_IDE_BUS) = NSDI_IDE_BUS then
    lbxCapabilites.Items.Add('IDE Bus');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_SCSI_BUS) = NSDI_SCSI_BUS then
    lbxCapabilites.Items.Add('SCSI Bus');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_BUF_UNDERRUN_PROT) = NSDI_BUF_UNDERRUN_PROT then
    lbxCapabilites.Items.Add('Buffer underrun protection');
  if (NeroDeviceInfo.nsdiCapabilities and NSDI_ALLOW_CHANGE_BOOKTYPE) = NSDI_ALLOW_CHANGE_BOOKTYPE then
    lbxCapabilites.Items.Add('DVD recorder can change booktype of burned medium');

  lbxWriteSpeeds.Clear;
  for Counter := 0 to NeroDeviceInfo.nsdiWriteSpeeds.nsiNumSupportedSpeeds - 1 do
    lbxWriteSpeeds.Items.Add(FloatToStrF(NeroDeviceInfo.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[Counter] / NeroDeviceInfo.nsdiWriteSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(NeroDeviceInfo.nsdiWriteSpeeds.nsiSupportedSpeedsKBs[Counter]) + ' KB/s)' );
  lbxWriteSpeeds.Enabled := (lbxWriteSpeeds.Items.Count > 0);
  lbWriteSpeeds.Enabled := (lbxWriteSpeeds.Items.Count > 0);
  
  lbxReadSpeeds.Clear;
  for Counter := 0 to NeroDeviceInfo.nsdiReadSpeeds.nsiNumSupportedSpeeds - 1 do
    if (NeroDeviceInfo.nsdiReadSpeeds.nsiSupportedSpeedsKBs[Counter] < 65535) then
      lbxReadSpeeds.Items.Add(FloatToStrF(NeroDeviceInfo.nsdiReadSpeeds.nsiSupportedSpeedsKBs[Counter] / NeroDeviceInfo.nsdiReadSpeeds.nsiBaseSpeedKBs, ffFixed, 0, 0) + 'x (' + IntToStr(NeroDeviceInfo.nsdiReadSpeeds.nsiSupportedSpeedsKBs[Counter]) + ' KB/s)' );
  lbxReadSpeeds.Enabled := (lbxReadSpeeds.Items.Count > 0);
  lbReadSpeeds.Enabled := (lbxReadSpeeds.Items.Count > 0);

end;

procedure TFDeviceInformation.btnCloseClick(Sender: TObject);
begin
  Close;
end;

end.
