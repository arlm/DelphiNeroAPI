object FMainForm: TFMainForm
  Left = 387
  Top = 644
  Width = 555
  Height = 452
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
    Top = 406
    Width = 547
    Height = 19
    Panels = <
      item
        Width = 200
      end>
  end
  object gbDevices: TGroupBox
    Left = 248
    Top = 120
    Width = 297
    Height = 73
    Caption = ' Writing Device '
    TabOrder = 1
    object lbWriteSpeeds: TLabel
      Left = 8
      Top = 43
      Width = 59
      Height = 13
      Caption = 'Write Speed'
    end
    object lbDeviceName: TLabel
      Left = 8
      Top = 19
      Width = 65
      Height = 13
      Caption = 'Device Name'
      FocusControl = cbDevices
    end
    object cbDevices: TComboBox
      Left = 80
      Top = 16
      Width = 193
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
      Left = 276
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
      Left = 80
      Top = 40
      Width = 193
      Height = 21
      Hint = 'Avaible Write Speeds|Choose the speed you want to burn'
      Style = csDropDownList
      Enabled = False
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object gbMedia: TGroupBox
    Left = 248
    Top = 8
    Width = 297
    Height = 105
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
      Width = 265
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
      Left = 224
      Top = 40
      Width = 65
      Height = 25
      Caption = 'Refresh'
      Enabled = False
      TabOrder = 1
      OnClick = btnRefreshClick
    end
    object btnMoreMedia: TButton
      Left = 275
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
    object btnErase: TButton
      Left = 8
      Top = 72
      Width = 65
      Height = 25
      Caption = 'Erase Disk'
      Enabled = False
      TabOrder = 3
      OnClick = btnEraseClick
    end
    object btnEject: TButton
      Left = 152
      Top = 72
      Width = 65
      Height = 25
      Caption = 'Eject CD'
      Enabled = False
      TabOrder = 4
      OnClick = btnEjectClick
    end
    object btnQuickErase: TButton
      Left = 80
      Top = 72
      Width = 65
      Height = 25
      Caption = 'Quick Erase'
      Enabled = False
      TabOrder = 5
      OnClick = btnQuickEraseClick
    end
    object btnLoad: TButton
      Left = 224
      Top = 72
      Width = 65
      Height = 25
      Caption = 'Load CD'
      Enabled = False
      TabOrder = 6
      OnClick = btnLoadClick
    end
  end
  object pcWrite: TPageControl
    Left = 3
    Top = 200
    Width = 539
    Height = 201
    ActivePage = tsAbout
    HotTrack = True
    TabOrder = 3
    OnChange = pcWriteChange
    object tsImage: TTabSheet
      Caption = 'Image'
      ImageIndex = 6
    end
    object tsISO: TTabSheet
      Caption = 'ISO (CD-ROM)'
    end
    object tsISOUDF: TTabSheet
      Caption = 'ISO / UDF (CD-ROM)'
      ImageIndex = 3
    end
    object tsUDF: TTabSheet
      Caption = 'UDF (CD-ROM)'
      ImageIndex = 2
    end
    object tsAudio: TTabSheet
      Caption = 'Audio  (CD-DA)'
      ImageIndex = 1
      object lbCDDATracks: TLabel
        Left = 8
        Top = 0
        Width = 33
        Height = 13
        Caption = 'Tracks'
        FocusControl = lbxCDDATracks
      end
      object lbCDDAArtist: TLabel
        Left = 264
        Top = 16
        Width = 23
        Height = 13
        Caption = 'Artist'
        FocusControl = edCDDAArtist
      end
      object lbCDDATitle: TLabel
        Left = 264
        Top = 40
        Width = 20
        Height = 13
        Caption = 'Title'
        FocusControl = edCDDATitle
      end
      object lbxCDDATracks: TListBox
        Left = 0
        Top = 13
        Width = 257
        Height = 160
        IntegralHeight = True
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 0
      end
      object edCDDAArtist: TEdit
        Left = 304
        Top = 13
        Width = 225
        Height = 21
        TabOrder = 1
        OnChange = edCDDAArtistChange
      end
      object edCDDATitle: TEdit
        Left = 304
        Top = 37
        Width = 225
        Height = 21
        TabOrder = 2
        OnChange = edCDDATitleChange
      end
      object btnBurnCDDA: TButton
        Left = 448
        Top = 144
        Width = 75
        Height = 25
        Caption = 'Burn CD-DA'
        TabOrder = 3
        OnClick = btnBurnCDDAClick
      end
    end
    object tsVCD: TTabSheet
      Caption = 'VCD'
      ImageIndex = 4
    end
    object tsSVCD: TTabSheet
      Caption = 'SVCD'
      ImageIndex = 5
    end
    object tsAbout: TTabSheet
      Caption = 'About'
      ImageIndex = 7
      object lbInstructions03: TLabel
        Left = 16
        Top = 48
        Width = 115
        Height = 13
        Caption = '* Insert the writing media'
      end
      object lbInstructions02: TLabel
        Left = 16
        Top = 32
        Width = 163
        Height = 13
        Caption = '* Choose the desired writing speed'
      end
      object lbInstructions01: TLabel
        Left = 16
        Top = 16
        Width = 166
        Height = 13
        Caption = '* Choose the desired writing device'
      end
      object lbInstructions0: TLabel
        Left = 8
        Top = 0
        Width = 60
        Height = 13
        Caption = 'Instructions :'
      end
      object lbInstructions04: TLabel
        Left = 16
        Top = 64
        Width = 155
        Height = 13
        Caption = '* Choose the desired writing style'
      end
      object lbInstructions05: TLabel
        Left = 16
        Top = 80
        Width = 176
        Height = 13
        Caption = '* Setup the files and info to be written'
      end
      object lbInstructions06: TLabel
        Left = 16
        Top = 96
        Width = 120
        Height = 13
        Caption = '* Start the writing process'
      end
    end
  end
  object gbSettings: TGroupBox
    Left = 8
    Top = 8
    Width = 233
    Height = 185
    Caption = ' Writing Settings '
    TabOrder = 4
    object lbWritingMethod: TLabel
      Left = 8
      Top = 163
      Width = 72
      Height = 13
      Caption = 'Writing Method'
      FocusControl = cbWritingMethod
    end
    object cbxSimulateBurn: TCheckBox
      Left = 8
      Top = 16
      Width = 169
      Height = 17
      Caption = 'Simulate Burn Intead of Writing'
      TabOrder = 0
    end
    object cbxTestSpeed: TCheckBox
      Left = 8
      Top = 32
      Width = 153
      Height = 17
      Caption = 'Test Speed Before Burning'
      TabOrder = 1
    end
    object cbxVerifyData: TCheckBox
      Left = 8
      Top = 48
      Width = 137
      Height = 17
      Caption = 'Verify Data After Burning'
      TabOrder = 2
    end
    object cbxEjectCD: TCheckBox
      Left = 8
      Top = 80
      Width = 129
      Height = 17
      Caption = 'Eject CD After Burning'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object cbxBufferUnderrun: TCheckBox
      Left = 8
      Top = 64
      Width = 145
      Height = 17
      Caption = 'Buffer Underrun Protection'
      TabOrder = 4
    end
    object cbxCloseSession: TCheckBox
      Left = 8
      Top = 96
      Width = 97
      Height = 17
      Caption = 'Close Session'
      Checked = True
      State = cbChecked
      TabOrder = 5
    end
    object cbWritingMethod: TComboBox
      Left = 88
      Top = 160
      Width = 137
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 6
      Text = 'TAO (Track At Once)'
      Items.Strings = (
        'TAO (Track At Once)'
        'DAO (Disc At Once)')
    end
  end
  object ApplicationEvents: TApplicationEvents
    OnShowHint = ApplicationEventsShowHint
  end
end
