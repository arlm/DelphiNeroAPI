object FMainForm: TFMainForm
  Left = 342
  Top = 240
  Width = 640
  Height = 370
  Caption = 'Delphi Nero API 1.02'
  Color = clBtnFace
  Constraints.MinWidth = 640
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ShowHint = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object sbMain: TStatusBar
    Left = 0
    Top = 324
    Width = 632
    Height = 19
    Panels = <
      item
        Width = 200
      end>
  end
  object gbDevices: TGroupBox
    Left = 8
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
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnShowHint = ApplicationEventsShowHint
  end
end
