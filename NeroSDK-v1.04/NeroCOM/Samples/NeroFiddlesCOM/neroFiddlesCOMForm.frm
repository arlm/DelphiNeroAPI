VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form neroFiddlesCOMForm 
   Caption         =   "NeroFiddles COM"
   ClientHeight    =   6150
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6930
   LinkTopic       =   "Form1"
   ScaleHeight     =   6150
   ScaleWidth      =   6930
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog ImageFileDialog 
      Left            =   1680
      Top             =   4800
      _ExtentX        =   688
      _ExtentY        =   688
      _Version        =   393216
      DefaultExt      =   "nrg"
      DialogTitle     =   "Select Image File "
      Filter          =   "All Files (*.*)|*.*|Nero Image Files (*.nrg)|*.nrg"
   End
   Begin VB.Frame Frame4 
      Caption         =   "Available Devices"
      Height          =   735
      Left            =   120
      TabIndex        =   10
      Top             =   960
      Width           =   6495
      Begin VB.ComboBox AvailableDevices 
         Height          =   315
         ItemData        =   "neroFiddlesCOMForm.frx":0000
         Left            =   240
         List            =   "neroFiddlesCOMForm.frx":0002
         TabIndex        =   11
         Top             =   240
         Width           =   5895
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Progress"
      Height          =   735
      Left            =   120
      TabIndex        =   5
      Top             =   1800
      Width           =   6495
      Begin ComctlLib.ProgressBar ProgressBar 
         Height          =   375
         Left            =   240
         TabIndex        =   6
         Top             =   240
         Width           =   5895
         _ExtentX        =   10398
         _ExtentY        =   661
         _Version        =   327682
         Appearance      =   1
      End
   End
   Begin MSComDlg.CommonDialog SelectFileDialog 
      Left            =   1080
      Top             =   4800
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "mp3"
      DialogTitle     =   "Select File For Burning"
      Filter          =   "All Files (*.*)|*.*|MP3 Files (*.mp3)|*.mp3"
   End
   Begin VB.TextBox edtMessages 
      Height          =   2055
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   3840
      Width           =   5895
   End
   Begin VB.Frame Frame2 
      Caption         =   "Nero Messages"
      Height          =   2535
      Left            =   120
      TabIndex        =   1
      Top             =   3480
      Width           =   6495
   End
   Begin VB.Frame Frame1 
      Caption         =   "File Name"
      Height          =   735
      Index           =   1
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   6495
      Begin VB.CommandButton Browse 
         Caption         =   "Browse"
         Height          =   375
         Left            =   4680
         TabIndex        =   9
         Top             =   240
         Width           =   1455
      End
      Begin VB.TextBox edtFileName 
         Height          =   375
         Left            =   240
         Locked          =   -1  'True
         ScrollBars      =   1  'Horizontal
         TabIndex        =   4
         Top             =   240
         Width           =   4215
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Burn Control"
      Height          =   735
      Index           =   2
      Left            =   120
      TabIndex        =   3
      Top             =   2640
      Width           =   6495
      Begin VB.CommandButton Burn 
         Caption         =   "Burn"
         Enabled         =   0   'False
         Height          =   375
         Left            =   240
         TabIndex        =   8
         Top             =   240
         Width           =   4215
      End
      Begin VB.CommandButton btnAbort 
         Caption         =   "Abort"
         Enabled         =   0   'False
         Height          =   375
         Left            =   4680
         TabIndex        =   7
         Top             =   240
         Width           =   1455
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2400
      Top             =   4200
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "mp3"
      Filter          =   "All Files (*.*)|*.*|MP3 Files (*.mp3)|*.mp3"
   End
End
Attribute VB_Name = "neroFiddlesCOMForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public WithEvents nero As nero
Attribute nero.VB_VarHelpID = -1
Public drives As INeroDrives
Attribute drives.VB_VarHelpID = -1
Public WithEvents drive As NeroDrive
Attribute drive.VB_VarHelpID = -1
Public cnt As Integer
Public Folder As INeroFolder
Public strMessages As String
Function NameFromPath(strPath As String) As String
    Dim lngPos          As Long
    Dim strPart         As String
    Dim blnIncludesFile As Boolean

    lngPos = InStrRev(strPath, "\")
    blnIncludesFile = InStrRev(strPath, ".") > lngPos
    strPart = ""

    If lngPos > 0 Then
        If blnIncludesFile Then
            strPart = Right$(strPath, Len(strPath) - lngPos)
        End If
    End If

    NameFromPath = strPart
End Function

Private Sub Browse_Click()
  SelectFileDialog.CancelError = True
  On Error GoTo ErrHandler
  SelectFileDialog.Flags = cdlOFNHideReadOnly
  SelectFileDialog.FilterIndex = 2
  SelectFileDialog.ShowOpen
  edtFileName.Text = SelectFileDialog.FileName
  Burn.Enabled = True
  Exit Sub
  
ErrHandler:
  Exit Sub
End Sub
Private Sub btnAbort_Click()
    nero.Abort
End Sub
Private Sub Burn_Click()
    btnAbort.Enabled = True
    Browse.Enabled = False
    Burn.Enabled = False

    Set Folder = New NeroFolder
    Dim drives As INeroDrives
    Set drives = nero.GetDrives(NERO_MEDIA_CDR)
    Set drive = drives(AvailableDevices.ListIndex)
    Dim isotrack As NeroISOTrack
    Set isotrack = New NeroISOTrack
    isotrack.Name = "TestTrack"
    isotrack.RootFolder = Folder
    Dim file As NeroFile
    Set file = New NeroFile
    Folder.Files.Add file
    file.Name = NameFromPath(edtFileName.Text)
    file.SourceFilePath = edtFileName.Text
    
    isotrack.BurnOptions = NERO_BURN_OPTION_CREATE_ISO_FS + NERO_BURN_OPTION_USE_JOLIET
    
    drive.BurnIsoAudioCD "Pop Star", "Title", 0, isotrack, Nothing, Nothing, NERO_BURN_FLAG_SIMULATE + NERO_BURN_FLAG_WRITE, 4, NERO_MEDIA_CD
    GoTo quit

handle_error:
    strMessages = strMessages + Err.Description + Chr(13) + Chr(10) + nero.LastError
    edtMessages = strMessages
quit:
End Sub
Private Sub drive_OnAborted(Abort As Boolean)
    Abort = False
End Sub
Private Sub drive_OnAddLogLine(TextType As NEROLib.NERO_TEXT_TYPE, Text As String)
    strMessages = strMessages + Text + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub drive_OnDoneBurn(StatusCode As NEROLib.NERO_BURN_ERROR)
    strMessages = strMessages + Chr(13) + Chr(10) + nero.ErrorLog + Chr(13) + Chr(10)
    strMessages = strMessages + nero.LastError + Chr(13) + Chr(10)
    strMessages = strMessages + "Burn finished "
    If StatusCode <> NEROLib.NERO_BURN_OK Then
        strMessages = strMessages + "NOT (" & StatusCode & ")"
    End If
    strMessages = strMessages + "successfully!" + Chr(13) + Chr(10)
    edtMessages = strMessages
    btnAbort.Enabled = False
    Browse.Enabled = True
    Burn.Enabled = True
    ProgressBar.Value = 0
End Sub
Private Sub drive_OnDoneWaitForMedia(Success As Boolean)
    strMessages = strMessages + "Done waiting for media." + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub drive_OnProgress(ProgressInPercent As Long, Abort As Boolean)
    Abort = False
    ProgressBar.Value = ProgressInPercent
End Sub
Private Sub drive_OnSetPhase(Text As String)
    strMessages = strMessages + Text + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub Form_Initialize()
    Set nero = New nero
    
    ProgressBar.Value = 0
    strMessages = ""
    Dim drives As INeroDrives
    Set drives = nero.GetDrives(NERO_MEDIA_CDR)
    
    For myIndex = 0 To drives.Count - 1
        AvailableDevices.AddItem drives(myIndex).DeviceName, myIndex
    Next
    AvailableDevices.ListIndex = 0
ErrHandler:
    Exit Sub
End Sub
Private Sub nero_OnFileSelImage(FileName As String)
      ImageFileDialog.CancelError = True
      On Error GoTo ErrHandler
      ImageFileDialog.Flags = cdlOFNHideReadOnly
      ImageFileDialog.FilterIndex = 2
      ImageFileDialog.ShowOpen
      FileName = ImageFileDialog.FileName
      Exit Sub
ErrHandler:
      Exit Sub
End Sub
Private Sub nero_OnMegaFatal()
    strMessages = strMessages + "A mega fatal error has occurred." + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub nero_OnNonEmptyCDRW(Response As NEROLib.NERO_RESPONSE)
  strMessages = strMessages + "CD-RW not empty!" + Chr(13) + Chr(10)
  edtMessages = strMessages
  Response = NERO_RETURN_EXIT
End Sub
Private Sub nero_OnRestart()
    strMessages = strMessages + "The system is being restarted." + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub nero_OnWaitCD(WaitCD As NEROLib.NERO_WAITCD_TYPE, WaitCDLocalizedText As String)
    strMessages = strMessages + WaitCDLocalizedText + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub nero_OnWaitCDDone()
    strMessages = strMessages + "Done waiting for CD." + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub nero_OnWaitCDMediaInfo(LastDetectedMedia As NEROLib.NERO_MEDIA_TYPE, LastDetectedMediaName As String, RequestedMedia As NEROLib.NERO_MEDIA_TYPE, RequestedMediaName As String)
    strMessages = strMessages + "Waiting for a particular media type:" + Chr(13) + Chr(10)
    strMessages = strMessages + RequestedMediaName + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
Private Sub nero_OnWaitCDReminder()
    strMessages = strMessages + "Still waiting for CD..." + Chr(13) + Chr(10)
    edtMessages = strMessages
End Sub
