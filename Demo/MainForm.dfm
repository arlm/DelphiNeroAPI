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
  object lbDevices: TLabel
    Left = 16
    Top = 10
    Width = 39
    Height = 13
    Caption = '&Devices'
    FocusControl = cbDevices
  end
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
  object cbDevices: TComboBox
    Left = 64
    Top = 8
    Width = 209
    Height = 21
    Hint = 'Avaible Devices|Choose one device to perform tests'
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    OnChange = cbDevicesChange
  end
  object btnMore: TButton
    Left = 280
    Top = 10
    Width = 17
    Height = 19
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
    TabOrder = 2
    OnClick = btnMoreClick
  end
  object ApplicationEvents: TApplicationEvents
    OnShowHint = ApplicationEventsShowHint
  end
end
