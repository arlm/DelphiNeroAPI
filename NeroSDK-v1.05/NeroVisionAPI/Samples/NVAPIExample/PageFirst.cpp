/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NVAPIExample
|*
|* PROGRAM: PageFirst.cpp
|*
|* PURPOSE: Implementation of the first page.
******************************************************************************/

#include "stdafx.h"
#include "NVAPIExample.h"
#include "PageFirst.h"
#include "PageData.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is our custom message.
// 
#define UM_QUIT_WITH_DELAY		(WM_APP + 1)


CPageFirst::CPageFirst(CSheet * pParent)
	: CPage(CPageFirst::IDD, pParent)
	, m_iVideoItemSequence (1)
	, m_iSlideshowItemSequence (1)
{
	//{{AFX_DATA_INIT(CPageFirst)
	m_iProjectType = 0;
	//}}AFX_DATA_INIT
}


void CPageFirst::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFirst)
	DDX_Control(pDX, IDC_SAVE, c_Save);
	DDX_Control(pDX, IDC_REMOVE, c_Remove);
	DDX_Control(pDX, IDC_PROJECT_TYPE, c_ProjectType);
	DDX_Control(pDX, IDC_LOAD, c_Load);
	DDX_Control(pDX, IDC_INSERT_VIDEO, c_InsertVideo);
	DDX_Control(pDX, IDC_INSERT_SLIDE, c_InsertSlide);
	DDX_Control(pDX, IDC_INSERT_IMAGE, c_InsertImage);
	DDX_Control(pDX, IDC_TRANSITION_TYPE, c_TransitionType);
	DDX_Control(pDX, IDC_CONTENT, c_Content);
	DDX_CBIndex(pDX, IDC_PROJECT_TYPE, m_iProjectType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageFirst, CPage)
//{{AFX_MSG_MAP(CPageFirst)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_INSERT_VIDEO, OnInsertVideo)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_INSERT_SLIDE, OnInsertSlide)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CONTENT, OnSelchangedContent)
	ON_CBN_SELCHANGE(IDC_TRANSITION_TYPE, OnSelchangeTransitionType)
	ON_BN_CLICKED(IDC_INSERT_IMAGE, OnInsertImage)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_CONTENT, OnBeginlabeleditContent)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_QUIT_WITH_DELAY, OnQuitWithDelay)
END_MESSAGE_MAP()

BOOL CPageFirst::OnInitDialog() 
{
	CPage::OnInitDialog();

	// On the first update, set the proper state of controls.
	// 
	UpdateControls ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CPageFirst::Create (void)
{
	// This is a CPage virtual function. Just create the dialog and return
	// success.
	// 
	return CDialog::Create (m_lpszTemplateName, m_pParentWnd) != FALSE;
}

bool CPageFirst::OnNext (void)
{
	// This method will be called whenever a main window's Next button is
	// clicked. We can use it to override the default behavior by returning
	// true.
	// 
	IXMLDOMDocumentPtr pDocument = BuildXML ();

	if (pDocument != NULL)
	{
		// If XML was built successfully, set it to the common page
		// data and let the default behavior of the button switch
		// to the next page.
		// 
		USES_CONVERSION;
		GetPageData ()->m_sXML = W2CA (pDocument->xml);

		return false;
	}
	else
	{
		// If there was an error building XML, report it and don't
		// switch to the next page.
		// 
		AfxMessageBox (IDS_ERROR_BUILDING_XML);

		return true;
	}
}

void CPageFirst::OnChangeState (bool bActivate, bool bForward)
{
	if (bActivate && bForward)
	{
		// If we are activated in the forward direction (normally only
		// once at the beginning), check if project object was
		// successfully created. If not, fail miserably as we can't
		// proceed without it. We will actually post a message to ourselves
		// to delay the quitting and to allow the main window to be
		// displayed.
		// 
		if (GetPageData ()->m_pProject == NULL)
		{
			PostMessage (UM_QUIT_WITH_DELAY);
		}
	}
}

LRESULT CPageFirst::OnQuitWithDelay (WPARAM wParam, LPARAM lParam)
{
	// This handler will be called if NeroVisionAPI's Project object
	// could not have been created. We can't do anything but quit.
	// 
	AfxMessageBox (IDS_ERROR_INITIALIZING_NERO_VISION_API);
	PostQuitMessage (0);

	return 0;
}

void CPageFirst::OnLoad() 
{
	// This is a Load handler. Ask for a file to load.
	// 
	CString sFilter;
	sFilter.LoadString (IDS_XML_FILES_FILTER);
	CFileDialog dlg (TRUE, "xml", NULL,
		OFN_EXPLORER|OFN_HIDEREADONLY,
		sFilter, this);
	
	if (IDOK == dlg.DoModal ())
	{
		// If ok was clicked, create an instance of XML document and
		// load the document. If loaded successfully, parse the XML file
		// and fill the dialog controls accordingly.
		// 
		try
		{
			// Create object instance...
			// 
			IXMLDOMDocumentPtr pDocument;
			EVAL_HR (pDocument.CreateInstance ("Msxml2.DOMDocument.3.0"));

			// Load the document...
			// 
			VARIANT_BOOL bSuccess;
			bSuccess = pDocument->load ((LPCSTR) dlg.GetPathName ());
			EVAL_HR (bSuccess? S_OK: E_FAIL);

			// Parse the document...
			// 
			ParseXMLDocument (pDocument);
		}
		catch (...)
		{
			// If an error occurs, delete everything and display an error.
			// 
			c_Content.DeleteAllItems ();
			AfxMessageBox (IDS_ERROR_LOADING_XML);
		}

		// No matter if the document is loaded successfully or not,
		// update the controls to reflect the new state.
		// 
		UpdateControls ();
	}
}

void CPageFirst::OnSave() 
{
	// This is the save XML handler.
	// 
	IXMLDOMDocumentPtr pDocument;

	// Build the XML from the project settings.
	// 
	pDocument = BuildXML ();

	if (pDocument == NULL)
	{
		// If ther is an error, notify the user.
		// 
		AfxMessageBox (IDS_ERROR_BUILDING_XML);
	}
	else
	{
		// If no error, ask the user for a filename to save the XML to.
		// 
		CString sFilter;
		sFilter.LoadString (IDS_XML_FILES_FILTER);
		CFileDialog dlg (FALSE, "xml", NULL,
			OFN_HIDEREADONLY|OFN_EXPLORER|OFN_OVERWRITEPROMPT,
			sFilter, this);
		
		if (IDOK == dlg.DoModal ())
		{
			// If filename is given, use the document's save method to save
			// the XML to a file.
			// 
			try
			{
				EVAL_HR (pDocument->save ((LPCSTR) dlg.GetPathName ()));
			}
			catch (...)
			{
				// Display a message on error.
				// 
				AfxMessageBox (IDS_ERROR_SAVING_XML);
			}
		}
	}
}


void CPageFirst::OnInsertVideo() 
{
	// This is a handler to insert video to project. Ask for a video
	// filename.
	// 
	CString sFilter;
	sFilter.LoadString (IDS_VIDEO_FILES_FILTER);
	CFileDialog dlg (TRUE, NULL, NULL,
		OFN_EXPLORER|OFN_HIDEREADONLY,
		sFilter, this);
	
	if (IDOK == dlg.DoModal ())
	{
		// If video file is selected insert it into project.
		// 
		CString sFormat;
		CString sVideoItemName;
		sFormat.LoadString (IDS_VIDEO_TITLE_FORMAT);
		sVideoItemName.Format (sFormat, m_iVideoItemSequence++);
	
		InsertVideo (sVideoItemName, dlg.GetPathName ());

		// After insertion, update the controls.
		// 
		UpdateControls ();
	}
}

void CPageFirst::InsertVideo (LPCSTR psVideoItemName, LPCSTR psPath)
{
	// This method inserts the video into the project (tree ctrl).
	// 
	HTREEITEM hVideoItem = c_Content.InsertItem (psVideoItemName, 0, 0);
	
	c_Content.InsertItem (psPath, 0, 0, hVideoItem);
	c_Content.SetItemData (hVideoItem, CONTENTTYPE::VIDEOTITLE);
	
	c_Content.Expand (hVideoItem, TVE_EXPAND);
}

void CPageFirst::OnRemove() 
{
	// This is a remove handler. First find the selected tree item.
	// 
	HTREEITEM hSelectedItem = c_Content.GetSelectedItem ();
	
	// If there is one...
	// 
	if (hSelectedItem != NULL)
	{
		// Find the root item of the selected item.
		// 
		for (HTREEITEM hParentItem = hSelectedItem;
			hParentItem != NULL;
			hSelectedItem = hParentItem, hParentItem = c_Content.GetParentItem (hSelectedItem))
				;
		
		// Now remove it...
		// 
		c_Content.DeleteItem (hSelectedItem);
		
		UpdateControls ();
	}
}

void CPageFirst::OnInsertSlide() 
{
	// This method inserts an image into the project (tree ctrl) along
	// with the two transitions (one before and one after the image).
	// 
	CString sFilter;
	sFilter.LoadString (IDS_IMAGE_FILES_FILTER);
	CFileDialog dlg (TRUE, NULL, NULL,
		OFN_EXPLORER|OFN_HIDEREADONLY,
		sFilter, this);
	
	if (IDOK == dlg.DoModal ())
	{
		CString sFormat;
		CString sSlideshowItemName;
		sFormat.LoadString (IDS_SLIDE_SHOW_FORMAT);
		sSlideshowItemName.Format (sFormat, m_iSlideshowItemSequence++);
		
		HTREEITEM hSlideItem = InsertSlideshow (sSlideshowItemName);

		// Insert an "empty" transition before and after the image.
		// 
		InsertTransition (hSlideItem);
		InsertImage (hSlideItem, dlg.GetPathName ());
		InsertTransition (hSlideItem);
		
		c_Content.Expand (hSlideItem, TVE_EXPAND);
		
		UpdateControls ();
	}
}

HTREEITEM CPageFirst::InsertSlideshow (LPCSTR psSlideshowName)
{
	// This is a helper method for inserting a slide show image.
	// 
	HTREEITEM hSlideItem = c_Content.InsertItem (psSlideshowName, 0, 0);
	c_Content.SetItemData (hSlideItem, CONTENTTYPE::SLIDESHOW);

	return hSlideItem;
}

void CPageFirst::InsertTransition (HTREEITEM hSlideItem, CPageFirst::TRANSITION transition)
{
	// This is a helper method for inserting a transition.
	// 
	HTREEITEM hTransition = c_Content.InsertItem ("", 0, 0, hSlideItem);
	ChangeTransition (hTransition, transition);
}

void CPageFirst::InsertImage (HTREEITEM hSlideItem, LPCSTR psImagePath)
{
	// This is a helper method for inserting an image after an initial
	// image has been inserted into a slideshow with InsertSlideshow.
	// 
	HTREEITEM hPathName = c_Content.InsertItem (psImagePath, 0, 0, hSlideItem);
	c_Content.SetItemData (hPathName, TRANSITION::INVALID);
}

void CPageFirst::ChangeTransition (HTREEITEM hItem, const TRANSITION transition)
{
	// This method is used for changing the transition type in the project.
	// First make sure the transition is valid.
	// 
	ASSERT (NONE <= transition && transition <= MOVEOUT);

	CString str;
	CString sFormat;
	CString sTransitionName;
	
	// Get the actual transition name from the combobox. The strings should
	// be in the same order as the TRANSITION enums.
	// 
	c_TransitionType.GetLBText ((int) transition, sTransitionName);
	
	// Get the transition formatting string from the string table and
	// create the final string that we are going to set to this item.
	// 
	sFormat.LoadString (IDS_TRANSITION_FORMAT);
	str.Format (sFormat, sTransitionName);
	
	c_Content.SetItemText (hItem, str);
	c_Content.SetItemData (hItem, transition);
}

void CPageFirst::OnSelchangedContent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	// Every time the selection of tree ctrl changes, update the controls'
	// states.
	// 
	UpdateControls ();
	
	*pResult = 0;
}

void CPageFirst::UpdateControls (void)
{
	// This method updates the controls' states according to the state
	// of the project.
	// 
	HTREEITEM hSelectedItem = c_Content.GetSelectedItem ();

	// Save button should be enabled if there is at least one item in
	// the project tree ctrl (if there is something worth saving).
	// Remove button should be enbled if something is selected.
	// 
	c_Save.EnableWindow (c_Content.GetFirstVisibleItem () != NULL);
	c_Remove.EnableWindow (hSelectedItem != NULL);

	bool bEnableTransitionType = false;
	bool bEnableInsertImage = false;
	HTREEITEM hItemParent = c_Content.GetParentItem (hSelectedItem);
	
	if (hItemParent != NULL)
	{
		// This is the second level of items. See if the parent is a
		// slideshow item.
		// 
		if (c_Content.GetItemData (hItemParent) == CONTENTTYPE::SLIDESHOW)
		{
			// Yes it is a slideshow. Now check to see if the particular
			// item is a transition item.
			// 
			TRANSITION transition = (TRANSITION) c_Content.GetItemData (hSelectedItem);
			bEnableTransitionType = transition != TRANSITION::INVALID;
			if (bEnableTransitionType)
			{
				// Set the transition of the currently selected item.
				// 
				c_TransitionType.SetCurSel ((int) transition);
			}

			bEnableInsertImage = true;
		}
	}
	else
	{
		bEnableInsertImage = hSelectedItem != NULL &&
							c_Content.GetItemData (hSelectedItem) == CONTENTTYPE::SLIDESHOW;
	}

	// Enable transition type combobox and insert image button according
	// to the conditions evaluated previously.
	// 
	c_TransitionType.EnableWindow (bEnableTransitionType);
	c_InsertImage.EnableWindow (bEnableInsertImage);
}

void CPageFirst::OnSelchangeTransitionType() 
{
	// When selection changes in the transition type combo box, update the
	// transition type of the item in the treectrl.
	// 
	HTREEITEM hSelectedItem = c_Content.GetSelectedItem ();
	
	if (hSelectedItem != NULL)
	{
		HTREEITEM hItemParent = c_Content.GetParentItem (hSelectedItem);
		if (hItemParent != NULL)
		{
			if (c_Content.GetItemData (hItemParent) == CONTENTTYPE::SLIDESHOW)
			{
				ChangeTransition (hSelectedItem, (TRANSITION) c_TransitionType.GetCurSel ());
			}
		}
	}
}

void CPageFirst::OnInsertImage() 
{
	// This method inserts an image into the project (tree ctrl) after an
	// initial slideshow has been created with InsertSlideshow.
	// 
	HTREEITEM hSelectedItem = c_Content.GetSelectedItem ();

	if (hSelectedItem != NULL)
	{
		HTREEITEM hParentItem = c_Content.GetParentItem (hSelectedItem);

		if (c_Content.GetItemData (hParentItem != NULL? hParentItem: hSelectedItem) == CONTENTTYPE::SLIDESHOW)
		{
			CString sFilter;
			sFilter.LoadString (IDS_IMAGE_FILES_FILTER);
			CFileDialog dlg (TRUE, NULL, NULL,
				OFN_EXPLORER|OFN_HIDEREADONLY,
				sFilter, this);
			
			if (IDOK == dlg.DoModal ())
			{
				// If an image filename has been chosen, insert it at the
				// end of an existing slideshow.
				// 
				HTREEITEM hSlideItem = hParentItem != NULL? hParentItem: hSelectedItem;
				
				InsertImage (hSlideItem, dlg.GetPathName ());
				InsertTransition (hSlideItem);

				c_Content.Expand (hSlideItem, TVE_EXPAND);
				
				UpdateControls ();
			}
		}
	}
}

_bstr_t CPageFirst::PrettyFormatXML (/*[in]*/ BSTR bstrInputXML)
{
	// This method is used for pretty printing the XML file.
	// 
	try
	{
		ISAXXMLReaderPtr pSAXXReader;
		IMXWriterPtr pMXWriter;
		
		EVAL_HR (pSAXXReader.CreateInstance ("MSXML2.SAXXMLReader.3.0"));
		EVAL_HR (pMXWriter.CreateInstance ("MSXML2.MXXMLWriter.3.0"));
		
		pMXWriter->indent = VARIANT_TRUE;
		pMXWriter->standalone = VARIANT_TRUE;
		
		ISAXContentHandlerPtr pSAXContentHandler (pMXWriter);
		EVAL_HR (pSAXXReader->putContentHandler (pSAXContentHandler));

		EVAL_HR (pSAXXReader->parse (bstrInputXML));
		
		_variant_t varOutput = pMXWriter->output;

		EVAL_HR (varOutput.vt == VT_BSTR? S_OK: E_INVALIDARG);
		_bstr_t bstrRet (varOutput.bstrVal);

		return bstrRet;
	}
	catch (...)
	{
		return "";
	}
}

IXMLDOMDocumentPtr CPageFirst::BuildXML (void)
{
	// This method is used to build an XML from the project.
	// 
	IXMLDOMDocumentPtr pDocument;

	try
	{
		EVAL_HR (pDocument.CreateInstance ("Msxml2.DOMDocument"));
		
		_bstr_t bstrTarget ("xml");
		_bstr_t bstrData ("version='1.0' encoding='ISO-8859-1'");
		IXMLDOMProcessingInstructionPtr pPI;
		pPI = pDocument->createProcessingInstruction (bstrTarget, bstrData);
		pDocument->appendChild (pPI);

		IXMLDOMElementPtr pNeroProjectElement;
		pNeroProjectElement = pDocument->createElement ("nerovision-project");
		pNeroProjectElement->setAttribute ("version", 1L);
		pNeroProjectElement->setAttribute ("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		pNeroProjectElement->setAttribute ("xsi:noNamespaceSchemaLocation", _variant_t ("NeroVisionAPI.xsd"));
		pDocument->appendChild (pNeroProjectElement);

		// Get the project type string directly from the project type
		// combobox.
		// 
		int iProjectTypeCurSel = c_ProjectType.GetCurSel ();
		ASSERT (iProjectTypeCurSel != -1);
		CString sProjectType;
		c_ProjectType.GetLBText (iProjectTypeCurSel, sProjectType);

		// Insert a project type tag with a fixed PAL encoding.
		// 
		IXMLDOMElementPtr pProjectType;
		pProjectType = pDocument->createElement ((LPCSTR) sProjectType);
		pProjectType->setAttribute ("encoding", "PAL");
		pNeroProjectElement->appendChild (pProjectType);

		// Insert a hardcoded label.
		// 
		IXMLDOMElementPtr pLabel;
		pLabel = pDocument->createElement ("label");
		pLabel->put_text (_bstr_t ("This is a label!"));
		pProjectType->appendChild (pLabel);

		// Start the content tag...
		// 
		IXMLDOMElementPtr pContent;
		pContent = pDocument->createElement ("content");
		pProjectType->appendChild (pContent);
		
		int iVideoitemID = 1;

		for (HTREEITEM hChild = c_Content.GetChildItem (NULL);
			hChild != NULL;
			hChild = c_Content.GetNextSiblingItem (hChild))
		{
			if (CONTENTTYPE::VIDEOTITLE == c_Content.GetItemData (hChild))
			{
				// This is a video. Add videotitle tag with a name attribute
				// whose value is the tree item caption.
				// 
				IXMLDOMElementPtr pVideoTitle;
				
				pVideoTitle = pDocument->createElement ("videotitle");
				pVideoTitle->setAttribute ("name", (LPCSTR) c_Content.GetItemText (hChild));

				CString sID;
				sID.Format ("t%d", iVideoitemID++);
				pVideoTitle->setAttribute ("id", (LPCSTR) sID);
				pContent->appendChild (pVideoTitle);
				
				HTREEITEM hPathItem = c_Content.GetChildItem (hChild);
				ASSERT (hPathItem != NULL);
				
				if (hPathItem != NULL)
				{
					IXMLDOMElementPtr pVideo;
					
					pVideo = pDocument->createElement ("video");
					pVideo->setAttribute ("src", (LPCSTR) c_Content.GetItemText (hPathItem));
					pVideoTitle->appendChild (pVideo);
				}
			}
			else
			{
				// This is a slide show. Add a slideshow tag with a name
				// attribute whose value is the tree item caption.
				// 
				IXMLDOMElementPtr pSlideshowTitle;
				
				pSlideshowTitle = pDocument->createElement ("slideshow");
				pSlideshowTitle->setAttribute ("name", (LPCSTR) c_Content.GetItemText (hChild));
				pContent->appendChild (pSlideshowTitle);

				// Now, iterate the children and add transitions and images.
				// 
				for (HTREEITEM hSlideChild = c_Content.GetChildItem (hChild);
					hSlideChild != NULL;
					hSlideChild = c_Content.GetNextSiblingItem (hSlideChild))
				{
					TRANSITION transition;

					transition = (TRANSITION) c_Content.GetItemData (hSlideChild);
					if (transition != TRANSITION::INVALID)
					{
						// This is a transition. Get its name from the
						// combobox. We have set the values so that they
						// are exactly the ones as required by the XML
						// format. If transition is TRANSITION::NONE,
						// this means <none> and we should skip it.
						// 
						if (transition != TRANSITION::NONE)
						{
							CString sTransitionName;
							c_TransitionType.GetLBText ((int) transition, sTransitionName);

							IXMLDOMElementPtr pTransition;

							pTransition = pDocument->createElement ("transition");
							pTransition->setAttribute ("type", (LPCSTR) sTransitionName);
							pSlideshowTitle->appendChild (pTransition);
						}
					}
					else
					{
						// This is an image path.
						// 
						IXMLDOMElementPtr pImage;

						pImage = pDocument->createElement ("image");
						pImage->setAttribute ("src", (LPCSTR) c_Content.GetItemText (hSlideChild));
						pImage->setAttribute ("duration", "5");
						pSlideshowTitle->appendChild (pImage);
					}
				}
			}
		}

		IXMLDOMElementPtr pMenu;
		pMenu = pDocument->createElement ("menu");
		pMenu->setAttribute ("default-thumbnail", "FirstNonEmptyFrame");
		pProjectType->appendChild (pMenu);

		IXMLDOMElementPtr pDefaultTemplate;
		pDefaultTemplate = pDocument->createElement ("default-template");
		pDefaultTemplate->setAttribute ("id", "templ1");
		pDefaultTemplate->setAttribute ("name", "Island");
		pMenu->appendChild (pDefaultTemplate);

		IXMLDOMElementPtr pMainMenu;
		pMainMenu = pDocument->createElement ("main-menu");
		pMenu->appendChild (pMainMenu);

		for (int i = 1; i < iVideoitemID; i ++)
		{
			IXMLDOMElementPtr pChapterMenu;
			pChapterMenu = pDocument->createElement ("chapter-menu");

			CString sID;
			sID.Format ("t%d", i);
			pChapterMenu->setAttribute ("title-id", (LPCSTR) sID);
			pMenu->appendChild (pChapterMenu);
		}
	}
	catch (...)
	{
		// If an exception is caught, release the unfinished document.
		// 
		pDocument = NULL;
	}

	return pDocument;
}

void CPageFirst::OnBeginlabeleditContent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	// Allow label editing on the first level only! This means editing is
	// allowed for video and slideshow item names only. Return TRUE to
	// disable editing.
	// 
	*pResult = c_Content.GetParentItem (pTVDispInfo->item.hItem) != NULL;
}

void CPageFirst::ParseXMLDocument (const IXMLDOMDocumentPtr pDocument)
{
	// First, clear the treectrl.
	// 
	c_Content.DeleteAllItems ();

	// Loop through all the nodes, look for elements.
	// 
	for (IXMLDOMNodePtr pNode = pDocument->firstChild;
		pNode != NULL;
		pNode = pNode->nextSibling)
	{
		IXMLDOMElementPtr pElement (pNode);
		
		// If node is an element, the interface pointer will be non-NULL.
		// 
		if (pElement != NULL)
		{
			// Check to see if the tag name is what we are looking for.
			// 
			if (0 == wcscmp ((BSTR) pElement->tagName, L"nerovision-project"))
			{
				ParseNeroVisionProject (pElement);
				
				// Once the project tag is parsed, we need parse no more.
				// 
				break;
			}
		}
	}
}

void CPageFirst::ParseNeroVisionProject (const IXMLDOMElementPtr pProject)
{
	// Ok, we are now looking for the project type (vcd, svcd or dvd).
	// 
	for (IXMLDOMNodePtr pNode = pProject->firstChild;
		pNode != NULL;
		pNode = pNode->nextSibling)
	{
		IXMLDOMElementPtr pElement (pNode);

		if (pElement != NULL)
		{
			USES_CONVERSION;

			_bstr_t tagName = pElement->tagName;
			LPCSTR psTagName = W2CA (tagName);

			// Instead of hardcoding the strings, we will now see if the
			// tag name matches any of the strings in the project type
			// combobox. We could use CComboBox::FindString but this
			// method uses case insensitive search and we need it to be
			// case sensitive.
			// 
			for (int i = c_ProjectType.GetCount () - 1; i >= 0; i --)
			{
				CString sProjectType;
				c_ProjectType.GetLBText (i, sProjectType);

				if (0 == strcmp (psTagName, sProjectType))
				{
					c_ProjectType.SetCurSel (i);
					break;
				}
			}

			// Make sure the appropriate project type was found!
			// 
			EVAL_HR (i >= 0? S_OK: E_FAIL);

			// If the subproject tag was found, parse its inner tags.
			// 
			ParseSubproject (pElement);

			// Then break as only one subproject is supported.
			// 
			break;
		}
	}
}

void CPageFirst::ParseSubproject (const IXMLDOMElementPtr pSubProject)
{
	// Now we are looking for the label and content tags. Actually, we
	// don't care about the label as we don't have facility to neither
	// display nor modify it. So, content tag is all we want. We also
	// don't care about the encoding attribute as we don't use it. It is
	// always PAL.
	// 
	for (IXMLDOMNodePtr pNode = pSubProject->firstChild;
		pNode != NULL;
		pNode = pNode->nextSibling)
	{
		IXMLDOMElementPtr pElement (pNode);
		
		if (pElement != NULL)
		{
			if (0 == wcscmp ((BSTR) pElement->tagName, L"content"))
			{
				// Once the content tag is found, parse it, then break as
				// only one content tag is allowed.
				// 
				ParseContent (pElement);
				
				break;
			}
		}
	}
}

void CPageFirst::ParseContent (const IXMLDOMElementPtr pContent)
{
	// Here we want videotitle and slideshow tags. Any number of these
	// can appear in any order.
	// 
	for (IXMLDOMNodePtr pNode = pContent->firstChild;
		pNode != NULL;
		pNode = pNode->nextSibling)
	{
			IXMLDOMElementPtr pElement (pNode);
			
			if (pElement != NULL)
			{
				if (0 == wcscmp ((BSTR) pElement->tagName, L"videotitle"))
				{
					ParseVideotitle (pElement);
				}
				else if (0 == wcscmp ((BSTR) pElement->tagName, L"slideshow"))
				{
					ParseSlideshow (pElement);
				}
			}
		}
}

void CPageFirst::ParseVideotitle (const IXMLDOMElementPtr pVideotitle)
{
	// Videotitle has a mandatory attribute "name". That is what we are
	// after. A sub-tag "video" is also of interest to us.
	// 
	IXMLDOMAttributePtr pNameAttr = pVideotitle->attributes->getNamedItem ("name");
	if (pNameAttr != NULL)
	{
		// Look for video tag.
		// 
		for (IXMLDOMNodePtr pNode = pVideotitle->firstChild;
			pNode != NULL;
			pNode = pNode->nextSibling)
		{
			IXMLDOMElementPtr pElement (pNode);
			
			if (pElement != NULL)
			{
				if (0 == wcscmp ((BSTR) pElement->tagName, L"video"))
				{
					// Video tag is found. Take its "src" attribute.
					// 
					IXMLDOMAttributePtr pSrcAttr = pElement->attributes->getNamedItem ("src");
					if (pSrcAttr != NULL)
					{
						// Once we have both name and src attributes,
						// insert the video to the project.
						// 
						USES_CONVERSION;
						_bstr_t bstrName (pNameAttr->value);
						_bstr_t bstrPath (pSrcAttr->value);

						InsertVideo (W2CA (bstrName), W2CA (bstrPath));

						// Then break. Only one video tag is allowed per
						// videotitle tag.
						// 
						break;
					}
				}
			}
		}
	}
}

void CPageFirst::ParseSlideshow (const IXMLDOMElementPtr pSlideshow)
{
	// Slideshow has a mandatory attribute "name".
	// 
	IXMLDOMAttributePtr pNameAttr = pSlideshow->attributes->getNamedItem ("name");
	if (pNameAttr != NULL)
	{
		// If "name" attribute is found, let's insert a slideshow into the/
		// project.
		// 
		USES_CONVERSION;
		_bstr_t bstrName = pNameAttr->value;
		HTREEITEM hSlideItem = InsertSlideshow (W2CA (bstrName));

		// Look for transition and image tags.
		// 
		for (IXMLDOMNodePtr pNode = pSlideshow->firstChild;
			pNode != NULL;
			pNode = pNode->nextSibling)
		{
			IXMLDOMElementPtr pElement (pNode);
			
			if (pElement != NULL)
			{
				if (0 == wcscmp ((BSTR) pElement->tagName, L"transition"))
				{
					// A transition tag must have a "type" attribute.
					// 
					IXMLDOMAttributePtr pTypeAttr = pElement->attributes->getNamedItem ("type");
					if (pTypeAttr != NULL)
					{
						_bstr_t bstrTransitionType (pTypeAttr->value);

						// Instead of hardcoding the strings, we will now see if the
						// type attribute matches any of the strings in the transition type
						// combobox.
						// 
						for (int i = c_TransitionType.GetCount () - 1; i >= 0; i --)
						{
							CString sTransitionType;
							c_TransitionType.GetLBText (i, sTransitionType);
							
							if (0 == strcmp (W2CA (bstrTransitionType), sTransitionType))
							{
								// Once the transition type was found in
								// the combobox, insert it into the
								// project.
								// 
								InsertTransition (hSlideItem, (TRANSITION) i);
								break;
							}
						}
						
						// Make sure the appropriate transition type was
						// found!
						// 
						EVAL_HR (i >= 0? S_OK: E_FAIL);
					}
				}
				else if (0 == wcscmp ((BSTR) pElement->tagName, L"image"))
				{
					// When image tag is found, look for its "src"
					// attribute.
					// 
					IXMLDOMAttributePtr pSrcAttr = pElement->attributes->getNamedItem ("src");
					if (pSrcAttr != NULL)
					{
						// When found, insert the image into the project.
						// 
						_bstr_t bstrImagePath (pSrcAttr->value);

						InsertImage (hSlideItem, W2CA (bstrImagePath));
					}
				}
			}
		}

		// When all is parsed, expand the tree item.
		// 
		c_Content.Expand (hSlideItem, TVE_EXPAND);
	}
}

