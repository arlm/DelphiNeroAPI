object FMainForm: TFMainForm
  Left = 1023
  Top = 777
  Width = 516
  Height = 370
  Caption = 'Delphi Nero API 1.02'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  ShowHint = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object sbMain: TStatusBar
    Left = 0
    Top = 324
    Width = 508
    Height = 19
    Panels = <
      item
        Width = 200
      end>
  end
  object gbDevices: TGroupBox
    Left = 0
    Top = 8
    Width = 249
    Height = 73
    Caption = ' Writing Device '
    TabOrder = 1
    object lbWriteSpeeds: TLabel
      Left = 8
      Top = 42
      Width = 59
      Height = 13
      Caption = 'Write Speed'
    end
    object cbDevices: TComboBox
      Left = 8
      Top = 16
      Width = 209
      Height = 21
      Hint = 'Avaible Devices|Choose one device to perform tests'
      Style = csDropDownList
      Enabled = False
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbDevicesChange
      OnCloseUp = cbDevicesCloseUp
    end
    object btnMoreDevice: TButton
      Left = 220
      Top = 17
      Width = 17
      Height = 17
      Hint = 
        'More information on this Device|Retrieve Read Speeds, Write Spee' +
        'ds, BufferUnderrun Protection and more ...'
      Caption = '?'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = btnMoreDeviceClick
    end
    object cbWriteSpeeds: TComboBox
      Left = 72
      Top = 40
      Width = 145
      Height = 21
      Hint = 'Avaible Write Speeds|Choose the speed you want to burn'
      Style = csDropDownList
      Enabled = False
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object gbMedia: TGroupBox
    Left = 256
    Top = 8
    Width = 249
    Height = 73
    Caption = ' Media '
    TabOrder = 2
    object lbFreeBlocks: TLabel
      Left = 16
      Top = 37
      Width = 65
      Height = 13
      Caption = '0 Free Blocks'
      FocusControl = btnMoreMedia
    end
    object lbTracks: TLabel
      Left = 16
      Top = 53
      Width = 42
      Height = 13
      Caption = '0 Tracks'
      FocusControl = btnMoreMedia
    end
    object stMedia: TStaticText
      Left = 8
      Top = 16
      Width = 217
      Height = 17
      Hint = 
        'Media Description|This is the media description of the Disk inse' +
        'rted in the device'
      Alignment = taCenter
      AutoSize = False
      BorderStyle = sbsSunken
      Caption = 'Device Not Selected'
      FocusControl = btnMoreMedia
      TabOrder = 0
    end
    object btnRefresh: TButton
      Left = 168
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Refresh'
      Enabled = False
      TabOrder = 1
      OnClick = btnRefreshClick
    end
    object btnMoreMedia: TButton
      Left = 227
      Top = 16
      Width = 17
      Height = 17
      Hint = 
        'More information on this Media|Retrieve free blocks, recorded tr' +
        'acks and more ...'
      Caption = '?'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btnMoreMediaClick
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnShowHint = ApplicationEventsShowHint
  end
end
