object FDeviceInformation: TFDeviceInformation
  Left = 468
  Top = 392
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Device Information'
  ClientHeight = 451
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lbReadSpeeds: TLabel
    Left = 152
    Top = 266
    Width = 103
    Height = 13
    Caption = 'Avaible Read Speeds'
    FocusControl = lbxReadSpeeds
  end
  object lbWriteSpeeds: TLabel
    Left = 8
    Top = 266
    Width = 102
    Height = 13
    Caption = 'Avaible Write Speeds'
    FocusControl = lbxWriteSpeeds
  end
  object lbHostAdapter: TLabel
    Left = 16
    Top = 32
    Width = 68
    Height = 13
    Caption = 'Host Adapter: '
  end
  object lbBurnProofSpeed: TLabel
    Left = 16
    Top = 64
    Width = 161
    Height = 13
    Caption = 'Burn-proof Recommended Speed:'
  end
  object lbMediaTypes: TLabel
    Left = 16
    Top = 104
    Width = 113
    Height = 13
    Caption = 'Supported Media Types'
    FocusControl = lbxMediaTypes
  end
  object lbCapabilities: TLabel
    Left = 160
    Top = 104
    Width = 90
    Height = 13
    Caption = 'Device Capabilities'
    FocusControl = lbxCapabilites
  end
  object lbBurnProofMethod: TLabel
    Left = 16
    Top = 48
    Width = 94
    Height = 13
    Caption = 'Burn-proof Method: '
  end
  object lbBuffer: TLabel
    Left = 16
    Top = 80
    Width = 54
    Height = 13
    Caption = 'Buffer Size:'
  end
  object lbxReadSpeeds: TListBox
    Left = 147
    Top = 282
    Width = 142
    Height = 134
    IntegralHeight = True
    ItemHeight = 13
    TabOrder = 0
  end
  object lbxWriteSpeeds: TListBox
    Left = 0
    Top = 281
    Width = 142
    Height = 134
    IntegralHeight = True
    ItemHeight = 13
    TabOrder = 1
  end
  object stName: TStaticText
    Left = 8
    Top = 8
    Width = 273
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    TabOrder = 2
  end
  object lbxMediaTypes: TListBox
    Left = 0
    Top = 119
    Width = 142
    Height = 134
    IntegralHeight = True
    ItemHeight = 13
    Sorted = True
    TabOrder = 3
  end
  object lbxCapabilites: TListBox
    Left = 147
    Top = 119
    Width = 142
    Height = 134
    IntegralHeight = True
    ItemHeight = 13
    Sorted = True
    TabOrder = 4
  end
  object btnClose: TButton
    Left = 104
    Top = 425
    Width = 75
    Height = 25
    Caption = '&Close'
    Default = True
    TabOrder = 5
    OnClick = btnCloseClick
  end
end
