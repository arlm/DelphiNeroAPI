{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2004 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroAPI.h/NeroAPIGlue.h, released March 2003. The      }
{ original Pascal code is: NeroAPI.pas, released June 2003. The initial        }
{ developer of the Pascal code is Alexandre Rocha Lima e Marcondes             }
{ (arlm@users.sourceforge.net).                                                }
{                                                                              }
{ Portions created by Alexandre Rocha Lima e Marcondesare Copyright (C) 2004   }
{ Alexandre Rocha Lima e Marcondes. All Rights Reserved.                       }
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
|* PROGRAM: NeroCBUI.h
|*
|* PURPOSE: Main interface for NeroCBUI
******************************************************************************}
unit NeroCBUI;

{$DEFINE NEROCBUI_UNIT}
{$INCLUDE NeroAPI.inc}

interface

uses
  Windows, Types, SysUtils, NeroAPI;

type

IID = TGUID;
CLSID = IID;

const
  LIBID_NEROCBUILIB: IID =              '{B3267063-8AB4-464D-A13C-1517BD6DC6F4}';

  IID_IMODELESSDIALOG: IID =            '{98654976-9086-4817-841C-B75B0AC0AAA6}';
  IID_INERO_SCSI_DEVICE_INFO: IID =     '{8268ED13-82F5-4DCC-BB13-95B5C7A64590}';
  IID_IRECORDERCOMBOBOXCALLBACKS: IID = '{3BD2799A-B364-405A-A63B-104D7FBFEB8A}';
  IID_IRECORDERCOMBOBOX: IID =          '{C76F66EF-B4D7-496B-9AB7-409A965D9C43}';
  IID_IRECORDERCOMBOBOX2: IID =         '{DE6F71CE-1FAF-405C-8E8E-0A32DC023B59}';
  IID_IRECORDERCOMBOBOX3: IID =         '{40A779DC-9DDC-4D02-BF07-717F419C00AA}';
  IID_IBURNSETTINGS: IID =              '{29C0C344-4C3C-4D4C-BD49-622CCFBD2C2E}';
  IID_IBURNSETTINGSDLG: IID =           '{0E17506D-EF14-4F3F-92BC-D3AE0739D079}';
  IID_IBURNCALLBACKS: IID =             '{01E72686-14EC-4A44-BE83-6C1CF9BFA2C0}';
  IID_IBURNPROGRESSDLGCALLBACKS: IID =  '{EE2AE31B-C11D-40EA-A75B-884837328387}';
  IID_IBURNPROGRESSDLG: IID =           '{F9DA148D-0052-4B6F-BB4F-C35E1FD4C5A3}';
  IID_IBURNPROGRESSDLG2: IID =          '{2053E9D5-8460-4E52-ABA2-832202624365}';
  IID_IEXTERNALCHILDWINDOW: IID =       '{FDA257A8-46CA-452E-9F3C-05798D3382C0}';
  IID_IBURNPROGRESSDLG3: IID =          '{4AA37A65-74C2-4DA1-B98B-3803C6B9C592}';
  IID_IBURNPROGRESSDLGEX: IID =         '{3EF6E092-CB60-4EDB-BAD2-DBCF097C452A}';
  IID_IMODALDIALOG: IID =               '{D0509114-6204-41F6-A6DA-8FD32EABC82F}';
  IID_INEROAPI_CDRW_ERASE_MODE: IID =   '{30603428-C6BB-45C1-8B35-A02CDA5C7086}';
  IID_IERASEDISCDLG: IID =              '{9A45A9F6-FE69-4FE8-9862-751693DC87DF}';
  IID_IERASEDISCDLG2: IID =             '{B28DC5D4-9593-4179-AAAA-DF3C8F28DB72}';
  IID_IERASEDISCCALLBACKS: IID =        '{62B3F282-AD7A-42F7-BDB1-B27772BDB61D}';
  IID_IERASEDISCDLG3: IID =             '{79B3261B-B57F-493E-A7BD-3325B5F58350}';
  IID_IERASEDISCDLG4: IID =             '{D658288D-1D49-4EB9-869E-10E5DDD40D16}';
  IID_IERASESETTINGSDLG: IID =          '{CD72CAD8-D41A-40B2-9943-01F30B1507CC}';
  IID_IERASESETTINGSDLG2: IID =         '{0040D3ED-84A2-4E56-9539-646BDC57DE4A}';
  IID_IINITSETTINGS: IID =              '{0F5EBCFD-2D94-4896-8169-088870DFDBAF}';
  IID_IINITSETTINGS2: IID =             '{4BAF9833-70BB-4523-8349-5209B5644587}';
  IID_IINITSETTINGS3: IID =             '{9964816B-DF5F-44AA-9B87-F0DE3F4C57FC}';
  IID_IINFORMATION: IID =               '{5DB904AA-9C92-494E-897C-5AAA5337CF2D}';
  IID_ICHILDWINDOW: IID =               '{F714BDC1-AEC8-41DE-83D2-DB9C9437FDB2}';
  IID_IIMAGEINFODLG: IID =              '{2302B658-DE28-4233-96BD-3BB5FB7B747E}';
  IID_ICHOOSESESSIONDLG: IID =          '{35E68486-0C10-41C5-A52A-55D8C0BA61F2}';
  IID_ISPEEDCOMBOBOXCALLBACKS: IID =    '{EFBE7CFF-6878-4DCE-B40D-E21C5D7698B6}';
  IID_ISPEEDCOMBOBOX: IID =             '{4855A95F-969F-49CD-8F5A-CA04E2AA7A62}';
  IID_ISPEEDCOMBOBOX2: IID =            '{6C373D24-7575-4507-972C-1814914570C9}';
  IID_IWAITFORMEDIADLG: IID =           '{ED8B6CB0-5AB6-4DB4-9D61-5DCF28F73D05}';
  IID_IUSERDLGHANDLER: IID =            '{911FB1F9-6576-4947-BF24-476BABE78016}';
  IID_IMFCPROPERTYPAGE: IID =           '{25398F04-EB36-4CD3-921E-AF1AAC1A3E61}';
  IID_IPRIVATEDEVICEINFOS: IID =        '{A8A66560-7A62-444D-B5E3-629DD8865C80}';
  IID_IPRIVATEIMAGEINFODLG: IID =       '{671FD79B-C0AF-4BB3-9738-E229871732F9}';

const
  CLSID_INITSETTINGS: CLSID =            '{9871F8AF-152A-4651-834C-CDC5FE61C14C}';
type
  InitSettings = interface              ['{9871F8AF-152A-4651-834C-CDC5FE61C14C}']
  end;

const
  CLSID_BURNSETTINGS: CLSID =            '{EC39BF14-CA12-46CD-8EA2-B48D5A44350A}';
type
  BurnSettings = interface              ['{EC39BF14-CA12-46CD-8EA2-B48D5A44350A}']
  end;

const
  CLSID_RECORDERCOMBOBOX: CLSID =        '{F495EBBE-A068-41FB-89B6-C605D20A2DF3}';
type
  RecorderCombobox = interface          ['{F495EBBE-A068-41FB-89B6-C605D20A2DF3}']
  end;

const
  CLSID_BURNSETTINGSDLG: CLSID =          '{E6028AF3-EE0A-4E49-A043-C44437680AD8}';
type
  BurnSettingsDlg = interface           ['{E6028AF3-EE0A-4E49-A043-C44437680AD8}']
  end;

const
  CLSID_BURNSETTINGSDLGPARAM: CLSID =    '{0B1511CD-37EE-4F0A-9647-CB2785B68A29}';
type
  BurnSettingsDlgParam = interface      ['{0B1511CD-37EE-4F0A-9647-CB2785B68A29}']
  end;

const
  CLSID_BURNPROGRESSDLG: CLSID =         '{A861A366-0C7A-484B-9116-F366BF0FA23F}';
type
  BurnProgressDlg = interface           ['{A861A366-0C7A-484B-9116-F366BF0FA23F}']
  end;

const
  CLSID_CHOOSERECORDERDLG: CLSID =       '{0EDCDB7D-CD9E-44E6-9E9A-ADBAA85540E8}';
type
  ChooseRecorderDlg = interface         ['{0EDCDB7D-CD9E-44E6-9E9A-ADBAA85540E8}']
  end;

const
  CLSID_ERASESETTINGSDLG: CLSID =        '{1C613F47-70C5-4551-A264-F7254139854C}';
type
  EraseSettingsDlg = interface          ['{1C613F47-70C5-4551-A264-F7254139854C}']
  end;

const
  CLSID_ERASEDISCDLG: CLSID =            '{7B9717B1-2D9B-4D14-B2DA-D4BF5A28C6AF}';
type
  EraseDiscDlg = interface              ['{7B9717B1-2D9B-4D14-B2DA-D4BF5A28C6AF}']
  end;

const
  CLSID_DISCINFODLG: CLSID =             '{F1F2ECE6-0289-4992-A536-F82DFC6F6D6E}';
type
  DiscInfoDlg = interface               ['{F1F2ECE6-0289-4992-A536-F82DFC6F6D6E}']
  end;

const
  CLSID_IMAGEINFODLG: CLSID =            '{940F79D9-2062-41B7-A22F-9E99FFDD1B85}';
type
  ImageInfoDlg = interface              ['{940F79D9-2062-41B7-A22F-9E99FFDD1B85}']
  end;

const
  CLSID_IMAGEINFODLGPARAM: CLSID =      '{712A2867-02B2-402B-8F8D-74437494DCFB}';
type
  ImageInfoDlgParam = interface        ['{712A2867-02B2-402B-8F8D-74437494DCFB}']
  end;

const
  CLSID_CHOOSESESSIONDLG: CLSID =       '{E5B2709A-0E6B-45D3-83C8-EF90C2ED5340}';
type
  ChooseSessionDlg = interface         ['{E5B2709A-0E6B-45D3-83C8-EF90C2ED5340}']
  end;

const
  CLSID_SPEEDCOMBOBOX: CLSID =          '{612FBD09-AAD2-4F1C-BA97-F56658B1161B}';
type
  SpeedCombobox = interface            ['{612FBD09-AAD2-4F1C-BA97-F56658B1161B}']
  end;

const
  CLSID_WAITFORMEDIADLG: CLSID =        '{9E42F1B8-DE23-4AF5-A79A-0976E9EC5781}';
type
  WaitForMediaDlg = interface          ['{9E42F1B8-DE23-4AF5-A79A-0976E9EC5781}']
  end;

const
  CLSID_USERDLGHANDLER: CLSID =         '{BC91ED21-E702-44E5-AA88-9F2F70E986C6}';
type
  UserDlgHandler = interface           ['{BC91ED21-E702-44E5-AA88-9F2F70E986C6}']
  end;
{
  IModelessDialog = interface;
  INERO_SCSI_DEVICE_INFO = interface;
  IRecorderComboboxCallbacks = interface;
  IRecorderCombobox = interface;
  IRecorderCombobox2 = interface;
  IRecorderCombobox3 = interface;
  IBurnSettings = interface;
  IBurnSettingsDlg = interface;
  IBurnCallbacks = interface;
  IBurnProgressDlgCallbacks = interface;
  IBurnProgressDlg = interface;
  IBurnProgressDlg2 = interface;
  IExternalChildWindow = interface;
  IBurnProgressDlg3 = interface;
  IBurnProgressDlgEx = interface;
  IModalDialog = interface;
  INEROAPI_CDRW_ERASE_MODE = interface;
  IEraseDiscDlg = interface;
  IEraseDiscDlg2 = interface;
  IEraseDiscCallbacks = interface;
  IEraseDiscDlg3 = interface;
  IEraseDiscDlg4 = interface;
  IEraseSettingsDlg = interface;
  IEraseSettingsDlg2 = interface;
  IInitSettings = interface;
  IInitSettings2 = interface;
  IInitSettings3 = interface;
  IInformation = interface;
  IChildWindow = interface;
  IImageInfoDlg = interface;
  IChooseSessionDlg = interface;
  ISpeedComboboxCallbacks = interface;
  ISpeedCombobox = interface;
  ISpeedCombobox2 = interface;
  IWaitForMediaDlg = interface;
  IUserDlgHandler = interface;
  IMfcPropertyPage = interface;
  IPrivateDeviceInfos = interface;
  IPrivateImageInfoDlg = interface;
}
  size_t = WORD;
  MIDL_user_allocate = function(Value: size_t):Pointer; cdecl;
  MIDL_user_free = procedure(Value: Pointer); cdecl;

  PCNERO_SCSI_DEVICE_INFO = PNERO_SCSI_DEVICE_INFO;
  PCNERO_SCSI_DEVICE_INFOS = PNERO_SCSI_DEVICE_INFOS;

  LPNERO_SCSI_DEVICE_INFO = PNERO_SCSI_DEVICE_INFO;
  LPCNERO_SCSI_DEVICE_INFO = PCNERO_SCSI_DEVICE_INFO;
  LPNERO_SCSI_DEVICE_INFOS = PNERO_SCSI_DEVICE_INFOS;
  LPCNERO_SCSI_DEVICE_INFOS = PCNERO_SCSI_DEVICE_INFOS;

  __MIDL_itf_NeroCBUI_0000_v0_0_c_ifspec = function:Pointer; {external;}
  __MIDL_itf_NeroCBUI_0000_v0_0_s_ifspec = function:Pointer; {external;}

  { TODO : external MIDL }


{ NeroCBUIGlue.h }
{******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|*
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroAPI
|*
|* PROGRAM: NeroCBUIGlue.h
|*
|* PURPOSE: Functions for connecting to NeroCBUI
******************************************************************************}

{
//	Get an instance of the NeroAPI compatibility manager to be passed
//  to NeroCBUI with IInitSettings::put_CompatibilityMgr
}
NeroCBUIGlueGetCompatibilityMgr = function(hNeroAPI: Pointer; reserved: Pointer):IUnknown;  cdecl;


implementation



end.
