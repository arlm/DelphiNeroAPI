object FMediaInfo: TFMediaInfo
  Left = 522
  Top = 376
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Media Information'
  ClientHeight = 451
  ClientWidth = 513
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
  object lbFreeBlocks: TLabel
    Left = 16
    Top = 37
    Width = 65
    Height = 13
    Caption = '0 Free Blocks'
  end
  object lbTracks: TLabel
    Left = 16
    Top = 53
    Width = 42
    Height = 13
    Caption = '0 Tracks'
  end
  object lbTrackList: TLabel
    Left = 16
    Top = 120
    Width = 33
    Height = 13
    Caption = 'Tracks'
  end
  object lbArtist: TLabel
    Left = 16
    Top = 78
    Width = 23
    Height = 13
    Caption = 'Artist'
  end
  object lbTitle: TLabel
    Left = 16
    Top = 94
    Width = 52
    Height = 13
    Caption = 'Album Title'
  end
  object stMedia: TStaticText
    Left = 8
    Top = 8
    Width = 497
    Height = 17
    Hint = 
      'Media Description|This is the media description of the Disk inse' +
      'rted in the device'
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Device Not Selected'
    TabOrder = 0
  end
  object btnClose: TButton
    Left = 219
    Top = 424
    Width = 75
    Height = 25
    Caption = 'Close'
    Default = True
    TabOrder = 1
    OnClick = btnCloseClick
  end
  object tvTracks: TTreeView
    Left = 0
    Top = 136
    Width = 513
    Height = 281
    Indent = 19
    TabOrder = 2
  end
end
