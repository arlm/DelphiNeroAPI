/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* PROJECT: neroFiddles NeroAPI Example
|*
|* FILE: neroFiddlesDlg.cpp
|*
|* PURPOSE: Implementation of a dialog for interaction with the user.
******************************************************************************/


// neroFiddlesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "neroFiddles.h"
#include "neroFiddlesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeroFiddlesDlg dialog

CNeroFiddlesDlg::CNeroFiddlesDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CNeroFiddlesDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CNeroFiddlesDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNeroFiddlesDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CNeroFiddlesDlg)
	DDX_Control(pDX, IDOK, mOK);
	DDX_Control(pDX, IDCANCEL, mCancel);
  DDX_Control(pDX, IDC_ABORT, mbtnAbort);
  DDX_Control(pDX, IDC_PROGRESS1, mpgsProgress);
  DDX_Control(pDX, IDC_MESSAGES, medtMessages);
  DDX_Control(pDX, IDC_FILENAME, medtFileName);
  DDX_Control(pDX, IDC_DEVICES, mcbxDevices);
  DDX_Control(pDX, IDC_BURN, mbtnBurn);
  DDX_Control(pDX, IDC_BROWSE, mbtnBrowse);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNeroFiddlesDlg, CDialog)
  //{{AFX_MSG_MAP(CNeroFiddlesDlg)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
  ON_BN_CLICKED(IDC_BURN, OnBurn)
  ON_BN_CLICKED(IDC_ABORT, OnAbort)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeroFiddlesDlg message handlers

BOOL CNeroFiddlesDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  
  // TODO: Add extra initialization here

  // Initialize the NeroAPI

  NeroAPIInit();
  
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNeroFiddlesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    CDialog::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNeroFiddlesDlg::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNeroFiddlesDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

void CNeroFiddlesDlg::OnBrowse() 
{
  // browse for the MP3 file that is supposed to be burned on CD

  // provide information about the file type that we want to open

  static char BASED_CODE szFilter[] = "MP3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*||";

  // create a CFileDialog object. 
  // usage : CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
  //                      DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL,
  //                      CWnd* pParentWnd = NULL );
  //
  // bOpenFileDialog = TRUE, create a File Open dialog 
  // lpszDefExt = NULL, do not automatically append a file extension
  // dwFlags = OFN_FILEMUSTEXIST, only accepts file names for files that are present
  // szFilter = "MP3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*||"
  // pParentWnd = this, our current Dialog window is the parent

  CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

  // do nothing if IDCANCEL is returned

  if (dlgOpen.DoModal() == IDOK)
  {
    // retrieve and display the selected file name

    mstrPathName = dlgOpen.GetPathName();
    mstrFileName = dlgOpen.GetFileName();
    medtFileName.SetWindowText(mstrPathName);

    // check whether any devices have been found

    if (pndiDeviceInfos->nsdisNumDevInfos > 0)
    {
      // make the "Burn" button accessible

      mbtnBurn.EnableWindow(true);
    }
  }
}

void CNeroFiddlesDlg::OnBurn() 
{
  // TODO: Add your control notification handler code here

  // perform the burn process

  // check whether a file has been selected
  if (mstrFileName == "")
  {
    // Tell the user what went wrong

    AppendString("You have to choose a file before you can start burning!");
  }
  else
  {
    // a file has been selected; fill the NERO_ISO_ITEM struct

    strcpy(mniiFile.fileName, mstrFileName); 
    strcpy(mniiFile.sourceFilePath, mstrPathName);
    mniiFile.isDirectory=FALSE;
    mniiFile.isReference=FALSE;

    // we only have one item

    mniiFile.nextItem=NULL;


    // no CD stamp, artist or title required

    writeCD.nwcdpCDStamp=NULL;
    writeCD.nwcdArtist=NULL;
    writeCD.nwcdTitle=NULL;

    // no CD Extra information available

    writeCD.nwcdCDExtra=FALSE;

    // we have no Audio tracks

    writeCD.nwcdNumTracks=0;

	// we want to write to a CD
	writeCD.nwcdMediaType = MEDIA_CD;

    // get the currently selected device from the ComboBox

    int i = mcbxDevices.GetCurSel();

    // retrieve the NERO_SCSI_DEVICE_INFO pointer for the selected device
    // and assign it to a local variable

    NERO_SCSI_DEVICE_INFO* nsdiDevice = (NERO_SCSI_DEVICE_INFO*)mcbxDevices.GetItemDataPtr(i);

    // try to open the selected device

    ndhDeviceHandle = NeroOpenDevice(nsdiDevice);

    // check whether a valid handle was returned

    if (!ndhDeviceHandle)
    {
      // no handle available; tell the user what happened

      AppendString("Device could not be opened: "+(CString)nsdiDevice->nsdiDeviceName);
    }
    else
    {
      // we have a valid device handle

      // while burning the "Abort" button needs to be enabled
      // all the other buttons and controls have to be disabled

      mbtnAbort.EnableWindow(true);
      mCancel.EnableWindow(false);
      mOK.EnableWindow(false);
      mcbxDevices.EnableWindow(false);
      mbtnBrowse.EnableWindow(false);
      mbtnBurn.EnableWindow(false);

      // set the range for the progress control, we will display percent

      mpgsProgress.SetRange(0,100);

      // create an ISO track
      // usage : NeroCreateIsoTrack(struct NERO_ISO_ITEM *root, const char *name,
      //                            BOOL useJoliet, BOOL useMode2);
      //
      // root = mniiFile, the NERO_ISO_ITEM we filled before
      // name = neroFiddles


      writeCD.nwcdIsoTrack = NeroCreateIsoTrackEx(&mniiFile, "neroFiddles", NCITEF_CREATE_ISO_FS|NCITEF_USE_JOLIET);

      // start the burn process by calling NeroBurn
      // usage:NEROAPI_BURN_ERROR NADLL_ATTR NeroBurn( NERO_DEVICEHANDLE  aDeviceHandle,
      // NERO_CD_FORMAT  CDFormat, const void*  pWriteCD, DWORD  dwFlags, DWORD  dwSpeedInX,
      // NERO_PROGRESS*  pNeroProgress);
      //
      // aDeviceHandle = ndhDeviceHandle, the handle we got from NeroOpenDevice()
      // CDFormat = NERO_ISO_AUDIO_CD
      // pWriteCD = writeCD
      // dwFlags = NBF_WRITE, do not simulate - burn!
      // dwSpeedInX = 0, use maximum speed
      // pNeroProgress = npProgress, filled during NeroAPIInit()

      int iRes = NeroBurn(ndhDeviceHandle, NERO_ISO_AUDIO_CD, &writeCD, NBF_WRITE, 0, &npProgress);

      // free memory that was allocated for the track

      NeroFreeIsoTrack(writeCD.nwcdIsoTrack);

      // close the device

      NeroCloseDevice(ndhDeviceHandle);

      // burning is finished, disable "Abort" activate all other controls 

      mbtnAbort.EnableWindow(false);
      mCancel.EnableWindow(true);
      mOK.EnableWindow(true);
      mcbxDevices.EnableWindow(true);
      mbtnBrowse.EnableWindow(true);
      mbtnBurn.EnableWindow(true);

      // clear the progress bar

      mpgsProgress.SetPos(0);

      // make sure that aborted flag is not set if "Burn" button is pressed again

      mbAborted = false;

      // retrieve the error log

      char* Log = NeroGetErrorLog();

      // display the error log contents

      AppendString(Log);

	  // free the log
	  NeroFreeMem(Log);


      // tell the user how the burn process was finished

      switch(iRes)
      {
        case NEROAPI_BURN_OK:
          AppendString ("BurnCD() : burn successful");
          break;
        case NEROAPI_BURN_UNKNOWN_CD_FORMAT:
          AppendString ("BurnCD() : unknown CD format");
          break;
        case NEROAPI_BURN_INVALID_DRIVE:
          AppendString ("BurnCD() : invalid drive");
          break;
        case NEROAPI_BURN_FAILED:
          AppendString ("BurnCD() : burn failed");
          break;
        case NEROAPI_BURN_FUNCTION_NOT_ALLOWED:
          AppendString ("BurnCD() : function not allowed");
          break;
        case NEROAPI_BURN_DRIVE_NOT_ALLOWED:
          AppendString ("BurnCD() : drive not allowed");
          break;
		case NEROAPI_BURN_USER_ABORT:
          AppendString ("BurnCD() : user aborted");
          break;
		case NEROAPI_BURN_BAD_MESSAGE_FILE:
          AppendString ("BurnCD() : bad message file");
          break;
        default:
          AppendString ("BurnCD() : unknown error");
		  break;
      }
    }
  }
}

BOOL NERO_CALLBACK_ATTR CNeroFiddlesDlg::IdleCallback(void *pUserData)
{
  // idle callback is called frequently by NeroAPI

  // make sure that messages from other controls can be handled

  static MSG msg;
  while (!(((CNeroFiddlesDlg*)pUserData)->mbAborted) && ::PeekMessage(&msg,NULL,NULL,NULL,PM_NOREMOVE))
  {
    if (!AfxGetThread()->PumpMessage())
	  {
      break;
	  }
	}

  // aborted-flag serves as function result

  return ((CNeroFiddlesDlg*)pUserData)->mbAborted;
}

void CNeroFiddlesDlg::NeroAPIInit()
{
  // initialization part, provide necessary information and check status

  mbAborted = false;

  // try to open the NeroAPI DLL

  if (!NeroAPIGlueConnect (NULL))
  {
    AppendString("Cannot open NeroAPI.DLL");

    // it makes no sense to continue after loading the DLL failed

    return;
  }

  // the NeroAPI DLL could be openend, get version information

  AppendString("Retrieving version information.");

  WORD majhi, majlo, minhi, minlo;

  NeroGetAPIVersionEx(&majhi, &majlo, &minhi, &minlo, NULL);


  // format and display the version information

  CString strVersion;
  strVersion.Format("NeroAPI version %d.%d.%d.%d",
                    majhi, majlo, minhi, minlo);

  AppendString(strVersion);

  // setup of structures that the NeroAPI needs

  AppendString("Filling NERO_SETTINGS structure");

  // Information for registry access

  strcpy(pcNeroFilesPath, "NeroFiles");
  strcpy(pcVendor, "ahead");
  strcpy(pcSoftware, "Nero - Burning Rom");

  // use the US-English error message file

  strcpy(pcLanguageFile, "Nero.txt");

  nsSettings.nstNeroFilesPath = pcNeroFilesPath;
  nsSettings.nstVendor = pcVendor;

  // set pointers to various callback functions

  nsSettings.nstIdle.ncCallbackFunction = IdleCallback;      

  // this pointer is required to access non-static variables from callback functions

  nsSettings.nstIdle.ncUserData = this;
  nsSettings.nstSoftware = pcSoftware;
  nsSettings.nstUserDialog.ncCallbackFunction = UserDialog; 
  nsSettings.nstUserDialog.ncUserData = this;
  nsSettings.nstLanguageFile =pcLanguageFile;

  // npProgress will be used during the burn process

  npProgress.npAbortedCallback = AbortedCallback;
  npProgress.npAddLogLineCallback = AddLogLine;
  npProgress.npDisableAbortCallback = NULL;
  npProgress.npProgressCallback = ProgressCallback;
  npProgress.npSetPhaseCallback = SetPhaseCallback;
  npProgress.npUserData = this;
  npProgress.npSetMajorPhaseCallback=NULL;	
  npProgress.npSubTaskProgressCallback=NULL;


  // no devices available yet

  pndiDeviceInfos = NULL;

  // initialize the NeroAPI with nsSettings and the 
  // Serial Number that we got from the Registry

  NEROAPI_INIT_ERROR initErr;
  initErr = NeroInit (&nsSettings, NULL);

  // display the result of NeroInit()

  switch (initErr)
  {
    case NEROAPI_INIT_OK:
      AppendString("Initialization of the NeroAPI successful.");
      break;
    case NEROAPI_INIT_INVALID_ARGS:
      AppendString("The arguments are not valid.");
      break;
    case NEROAPI_INIT_INVALID_SERIAL_NUM:
      AppendString("The Serial Number is not valid.");
      break;
    default:
      AppendString("An error occured. The type of error cannot be determined.");
      break;
  }

  // get a list of available drives

  pndiDeviceInfos = NeroGetAvailableDrivesEx (MEDIA_CD, NULL);

  // check whether any devices have been found 

  if (!pndiDeviceInfos)
  {
    // no device found, let the user know

    AppendString("NeroGetAvailableDrivesEx() returned no available devices.");
  }
  else
  {
    // devices found

    // check the number of available devices to be sure

    if (pndiDeviceInfos->nsdisNumDevInfos > 0)
    {
      // we have some devices, now fill the ComboBox

      AppendString("Found the following devices:");
      for (DWORD dDeviceCounter = 0; dDeviceCounter < pndiDeviceInfos->nsdisNumDevInfos; dDeviceCounter++)
      {
        AppendString(pndiDeviceInfos->nsdisDevInfos[dDeviceCounter].nsdiDeviceName);

        // add the device name to the ComboBox and get the index number

        int i = mcbxDevices.AddString(pndiDeviceInfos->nsdisDevInfos[dDeviceCounter].nsdiDeviceName);

        // use the index number to access the corresponding entry
        // connect the entry's ItemData pointer to a NERO_DEVICE_INFO structure

        mcbxDevices.SetItemDataPtr(i, &pndiDeviceInfos->nsdisDevInfos[dDeviceCounter]);
      }

      // select the first ComboBox entry

      mcbxDevices.SelectString(-1, pndiDeviceInfos->nsdisDevInfos[0].nsdiDeviceName);
    }
    else
    {
      AppendString("The number of available devices is 0.");
    }
  }
}

void CNeroFiddlesDlg::AppendString(CString str)
{
  // a CString for temporary use

  CString   strBuffer;

  // retrieve the content of the EditControl we use for messages

  medtMessages.GetWindowText (strBuffer);

  // add a new line if the EditControl is not empty

  if (!strBuffer.IsEmpty())
  {
     strBuffer += "\r\n";
  }

  // append the string the function got as a parameter

  strBuffer += str;

  // update the EditiControl with the new content

  medtMessages.SetWindowText (strBuffer);

  // Scroll the edit control to the end

  medtMessages.LineScroll (medtMessages.GetLineCount(), 0);
}

NeroUserDlgInOut NERO_CALLBACK_ATTR CNeroFiddlesDlg::UserDialog(void *pUserData, NeroUserDlgInOut type, void *data)
{
  // handling of messages that require the user to perform an action
  // for reasons of brevity we only deal with the messages that 
  // are absolutely mandatory for this application

  switch (type)
  {
    case DLG_AUTO_INSERT:
      return DLG_RETURN_CONTINUE;
      break;
    case DLG_DISCONNECT_RESTART:
      return DLG_RETURN_ON_RESTART;
      break;
    case DLG_DISCONNECT:
      return DLG_RETURN_CONTINUE;
      break;
    case DLG_AUTO_INSERT_RESTART:
      return DLG_RETURN_EXIT;
      break;
    case DLG_RESTART:
      return DLG_RETURN_EXIT;
      break;
    case DLG_SETTINGS_RESTART:
      return DLG_RETURN_CONTINUE;
      break;
    case DLG_OVERBURN:
      return DLG_RETURN_TRUE;
      break;
    case DLG_AUDIO_PROBLEMS:
      return DLG_RETURN_EXIT;
      break;
    case DLG_FILESEL_IMAGE:
      {
        // create filter for image files

        static char BASED_CODE szFilter[] = "Image Files (*.nrg)|*.nrg|All Files (*.*)|*.*||";

        // create a CFileDialog object. 
        // usage : CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
        //                      DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL,
        //                      CWnd* pParentWnd = NULL );
        //
        // bOpenFileDialog = TRUE, create a File Open dialog 
        // lpszDefExt = NULL, do not automatically append a file extension
        // dwFlags = OFN_OVERWRITEPROMPT, makes no sense during file open,
        //           just in case we decide to use File Save later
        // szFilter = "Image Files (*.nrg)|*.nrg|All Files (*.*)|*.*||"
        // pParentWnd = ((CNeroFiddlesDlg*)pUserData), our current Dialog window is the parent

        CFileDialog dlgOpen(TRUE, NULL, "test.nrg", OFN_OVERWRITEPROMPT, szFilter, ((CNeroFiddlesDlg*)pUserData));

        // check how the dialog was ended

        if (dlgOpen.DoModal() == IDOK)
        {
          // user pressed "OK", copy the file name to the data parameter

          strcpy((char*)data,dlgOpen.GetPathName());

          // proceed with the burn process

          return DLG_RETURN_TRUE; 
        }
        else
        {
          // user canceled, do not proceed with the burn process

          return DLG_BURNIMAGE_CANCEL;
        }
      }
      break;
    case DLG_WAITCD:
    {
      NERO_WAITCD_TYPE waitcdType = (NERO_WAITCD_TYPE) (int)data;
	  char *waitcdString = NeroGetLocalizedWaitCDTexts (waitcdType);
      ((CNeroFiddlesDlg*)pUserData)->AppendString(waitcdString);
	  NeroFreeMem(waitcdString);
      return DLG_RETURN_EXIT;
      break;
    }
    default:
      break;
  }

  // default return value, in case we forgot to handle a request
  
  return DLG_RETURN_EXIT;
}

BOOL NERO_CALLBACK_ATTR CNeroFiddlesDlg::ProgressCallback(void *pUserData, DWORD dwProgressInPercent)
{
  // the NeroAPI updates the current progress counter

  // set the progress bar to the percentage value that was passed to this function

  ((CNeroFiddlesDlg*)pUserData)->mpgsProgress.SetPos(dwProgressInPercent);

  return true;
}

BOOL NERO_CALLBACK_ATTR CNeroFiddlesDlg::AbortedCallback(void *pUserData)
{
  // do not ask the user if he really wants to abort
  // just return the aborted flag

  return ((CNeroFiddlesDlg*)pUserData)->mbAborted;
}

void NERO_CALLBACK_ATTR CNeroFiddlesDlg::AddLogLine(void *pUserData, NERO_TEXT_TYPE type, const char *text)
{
  // Add the text that was passed to this function to the message log
  CString csTemp(text);
  ((CNeroFiddlesDlg*)pUserData)->AppendString("Log line:" + csTemp);
  return;
}

void NERO_CALLBACK_ATTR CNeroFiddlesDlg::SetPhaseCallback(void *pUserData, const char *text)
{
  // display the current phase the burn process is currently going through
  CString csTemp(text);
  ((CNeroFiddlesDlg*)pUserData)->AppendString("Phase: " + csTemp);
  return;
}

void CNeroFiddlesDlg::NeroAPIFree()
{
  // free the resources that have been used

  // make sure there is something to free so we do not run into an exception
  if (pndiDeviceInfos)
  {
    NeroFreeMem(pndiDeviceInfos);
  }

  // nothing to check before calling these functions

  NeroClearErrors();
  if(NeroDone())
  {
	  AfxMessageBox("Detected memory leaks in NeroFiddles");
  }

  NeroAPIGlueDone();

  return;
}

void CNeroFiddlesDlg::OnOK() 
{
  // TODO: Add extra validation here

  // user decides to quit by pressing "OK"

  NeroAPIFree();
  
  CDialog::OnOK();
}

void CNeroFiddlesDlg::OnCancel() 
{
  // TODO: Add extra cleanup here

  // user decides to quit by pressing "Cancel"
  // we handle this like the "OK" button

  NeroAPIFree();
  
  CDialog::OnCancel();
}

void CNeroFiddlesDlg::OnAbort() 
{
  // TODO: Add your control notification handler code here

  // nothing more required but setting the aborted flag

  mbAborted = true;
}


