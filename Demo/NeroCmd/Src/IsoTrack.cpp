/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroCmd
|*
|* PROGRAM: IsoTrack.cpp
|*
|* PURPOSE: ISO tree handling
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"
#include "FindFile.h"


// This function is used solely for debug purposes in order to print the
// whole ISO tree.
// 
void CBurnContext::DebugPrintIsoTrack (const NERO_ISO_ITEM * pItem, int iLevel)
{
	while (pItem)
	{
		// Indent each level a little bit.
		// 
		for (int i = 0; i <= iLevel; i ++)
		{
			printf ("  ");
		}

		printf ((pItem->isDirectory)? "[%s]\n": "%s\n", pItem->fileName);

		if (pItem->isDirectory)
		{
			DebugPrintIsoTrack (pItem->subDirFirstItem, iLevel + 1);
		}

		pItem = pItem->nextItem;
	}
}

// This function creates a CNeroIsoTrack from the user supplied parameters.
// It imports previous session (if any) and builds the file and directory
// tree.

CExitCode CBurnContext::GetIsoTrack (const PARAMETERS & params, CNeroIsoTrack** ppIsoTrack, NERO_ISO_ITEM** ppItem)
{
	*ppIsoTrack = NULL;

	// Make sure that either the user supplied us with the session number
	// or that there is at least on session to import (if we need to choose
	// one ourselves).
	// 
	if (-1 != params.GetSessionToImport() || (m_NeroCDInfo != NULL && 0 < m_NeroCDInfo->ncdiNumTracks))
	{
		// The the user's choice for a session, if one is provided. If not,
		// take the last session.
		int iSessionToImport = (-1 != params.GetSessionToImport())? params.GetSessionToImport (): (m_NeroCDInfo->ncdiNumTracks - 1);

		// Make sure that NeroGetCDInfo has not been called before to prevent multiple 
		// allocation of memory for NERO_CD_INFO.

		_ASSERTE (m_NeroCDInfo == NULL);

		// First get the CD info to obtain information about all available sessions

		m_NeroCDInfo = NeroGetCDInfo (m_NeroDeviceHandle, 0);
		if (NULL == m_NeroCDInfo)
		{
			return EXITCODE_ERROR_GETTING_CD_INFO;
		}

		// Check the numbers and make sure that the requested session exists.

		if (params.GetSessionToImport() >= (int)(m_NeroCDInfo->ncdiNumTracks))
		{
			return EXITCODE_BAD_IMPORT_SESSION_NUMBER;
		}

		DWORD dwFlags = 0;

		// Determine the format to be imported

		// NIITEF_IMPORT_ROCKRIDGE flag is obsolete so we commented the
		// code below.
		//
/*		if (params.GetImportRockridge())
		{
			dwFlags |= NIITEF_IMPORT_ROCKRIDGE;
		}*/

		if (params.GetImportUDF())
		{
			dwFlags |= NIITEF_IMPORT_UDF;
		}
		if (params.GetImportIsoOnly())
		{
			dwFlags |= NIITEF_IMPORT_ISO_ONLY;
		}
		if (params.GetPreferRockRidge())
		{
			dwFlags |= NIITEF_PREFER_ROCKRIDGE;
		}

		// Now, import the session. If the function fails, it's probably
		// due to no CD in drive.
		// NeroImportIsoTrackEx creates a NERO_ISO_ITEM tree from an already
		// existing ISO track in order to create a new session with reference
		// to files from older sessions.
		// m_pCDStamp will be filled with a pointer to a CDStamp object
		// which will have to be freed later by the CBurnContext destructor.

		// ppItem is a reference to a pointer to a NERO_ISO_ITEM
		// So to get the required pointer to a NERO_ISO_ITEM we have to
		// de-reference ppItem once.

		*ppItem = NeroImportIsoTrackEx (m_NeroDeviceHandle,
										iSessionToImport,
										&m_pCDStamp,
										dwFlags);

		// The NERO_ISO_ITEM pointer must not be NULL

		if (NULL == *ppItem)
		{
			return EXITCODE_NO_CD_INSERTED;
		}

	}  // if (-1 != params.m_iSessionToImport)

	// Iterate through the file list and it each one to the tree.
	// If directory is stumbled upon, recurse it and it all of
	// its contents.

	for (int i = 0; i < params.GetFileListSize(); i ++)
	{
		NERO_ISO_ITEM* pItem;
		EXITCODE code;

		// Create a tree from the filename supplied.

		code = CreateIsoTree (params, params.GetFileList().vect[i], &pItem);

		// If there was a problem creating the tree then delete 
		// the whole tree that has been created so far and
		// return the error code.

		if (code != EXITCODE_OK)
		{
			DeleteIsoItemTree (*ppItem);
			return code;
		}

		// Add the file to the beginning of the root directory.

		if (NULL != *ppItem)
		{
			if (pItem != NULL)
			{
				NERO_ISO_ITEM * p = pItem;

				while (p->nextItem)
				{
					p = p->nextItem;
				}

				p->nextItem = *ppItem;
			}
		}
		*ppItem = pItem;
	}

	if (NULL != *ppItem)
	{
		DWORD dwFlags = 0;

		if (!params.GetDontUseJoliet())
		{
			dwFlags |= NCITEF_USE_JOLIET;
		}
		if (params.GetUseMode2())
		{
			dwFlags |= NCITEF_USE_MODE2;
		}
		if (params.GetUseRockridge())
		{
			dwFlags |= NCITEF_USE_ROCKRIDGE;
		}
		if (params.GetCreateIsoFs())
		{
			dwFlags |= NCITEF_CREATE_ISO_FS;
		}
		if (params.GetCreateUdfFS())
		{
			dwFlags |= NCITEF_CREATE_UDF_FS;
		}
		if (params.GetDVDVideoRealloc ())
		{
			dwFlags |= NCITEF_DVDVIDEO_REALLOC;
		}

		// This is used only for debugging purposese. Never allow this
		// call to take place in Release code.
		// 
//		DebugPrintIsoTrack (*ppItem);
		
		// Finally, create the ISO track.

		*ppIsoTrack = NeroCreateIsoTrackEx (*ppItem,
											params.GetVolumeName(),
											dwFlags);
		
		// If the ISO track could not be created then delete the 
		// ISO item tree and return with an error

		if (NULL == *ppIsoTrack)
		{
			DeleteIsoItemTree (*ppItem);
			return EXITCODE_FAILED_TO_CREATE_ISO_TRACK;
		}
	}

	return EXITCODE_OK;
}

// This function deletes the iso tree recursively.

void CBurnContext::DeleteIsoItemTree (NERO_ISO_ITEM * pItem)
{
	// Step through the tree until the 
	// ISO item tree pointer becomes NULL

	while (NULL != pItem)
	{
		NERO_ISO_ITEM* pNextItem = pItem->nextItem;

		if (pItem->isDirectory)
		{
			// We have encountered another ISO item tree;
			// recurse another level.

			DeleteIsoItemTree (pItem->subDirFirstItem);
		}

		if (pItem->isReference)
		{
			NeroFreeMem (pItem);
		}
		else
		{
			NeroFreeIsoItem (pItem);
		}

		pItem = pNextItem;
	}
}


// This function searches for a specified path and recursively adds
// all files and directories that our found.

CExitCode CBurnContext::CreateIsoTree (const PARAMETERS & params, LPCSTR psFilename, NERO_ISO_ITEM ** ppItem, int iLevel)
{
	// CFindFiles is a helper class for file and subdirectory handling 

	CFindFiles ff (psFilename);

	*ppItem = NULL;

	if (!ff.IsValidEntry())
	{
		if (0 == iLevel)
		{
			// If we haven't found any entries and we are on the
			// first level of recursion then this should be
			// reported as an error.

			m_ErrorLog.printf ("File specification '%s' resulted in no matches!\n", psFilename);

			return EXITCODE_FILE_NOT_FOUND;
		}
		else
		{
			// If we are on a level other than first, it is ok
			// not to find any entries. This simply means we
			// stumbled upon an empty directory somewhere in a tree.

			return EXITCODE_OK;
		}
	}

	char sPath[MAX_PATH];

	// Make sure that we have no relative path names, but only absolute paths

	if (NULL == _fullpath (sPath, psFilename, sizeof (sPath)))
	{
		// Our path buffer is too small. Bail out!

		return EXITCODE_INTERNAL_ERROR;
	}

	// Find the last blackslash and remove it if found.
	// This will leave us with a root directory.

	LPSTR psBackslash = strrchr (sPath, '\\');
	if (NULL != psBackslash)
	{
		*psBackslash = '\0';
	}

	do
	{
		std::string sNewPath;

		sNewPath = sPath;

		sNewPath += "\\";
		sNewPath += ff.GetName ();

		if (ff.IsSubDir())
		{
			// If we the user wants recursive search, only then do we
			// actually recurse at deeper levels otherwise ignore directories
			// alltogether.
			// 
			if (params.GetRecursive ())
			{
				// Here we handle subdirectories

				// strcmp returns 0 on equal strings.
				// Proceed if name contains none of "." or ".."

				if ((0 != strcmp (ff.GetName (), ".")) && (0 != strcmp (ff.GetName (), "..")))
				{
					// Append a wildcard to the path and do a recursive search.

					sNewPath += "\\";
					sNewPath += ff.GetWildcard ();

					NERO_ISO_ITEM * pNewItem = NeroCreateIsoItem ();
					if (NULL == pNewItem)
					{
						DeleteIsoItemTree (*ppItem);
						return EXITCODE_OUT_OF_MEMORY;
					}

					// Attach this item to the beginning of the list.

					if (*ppItem != NULL)
					{
						pNewItem->nextItem = *ppItem;
					}
					*ppItem = pNewItem;

					pNewItem->isDirectory = TRUE;
					time_t t = ff.GetCreateTime ();
					pNewItem->entryTime = *localtime (&t);
					strcpy (pNewItem->fileName, ff.GetName ());

					// Create an ISO item tree at a deeper level

					EXITCODE code = CreateIsoTree (params, sNewPath.c_str (), &pNewItem->subDirFirstItem, iLevel + 1);
					if (EXITCODE_OK != code)
					{
						DeleteIsoItemTree (*ppItem);
						return code;
					}

					// We don't allow empty directories. This should probably
					// be regulated by a command line switch.
					// 
					if (pNewItem->subDirFirstItem == NULL)
					{
						// If the newly added directory is empty, remove it!
						// We first detach it from the list and then
						// deallocate it.
						// 
						*ppItem = pNewItem->nextItem;
						pNewItem->nextItem = NULL;
						DeleteIsoItemTree (pNewItem);
					}
				}
			}
		}
		else
		{
			// Here we handle regular files

			NERO_ISO_ITEM * pNewItem = NeroCreateIsoItem ();
			if (NULL == pNewItem)
			{
				DeleteIsoItemTree (*ppItem);
				return EXITCODE_OUT_OF_MEMORY;
			}

			strcpy (pNewItem->sourceFilePath, sNewPath.c_str ());
			pNewItem->isDirectory = FALSE;
			time_t t = ff.GetCreateTime ();
			pNewItem->entryTime = *localtime (&t);
			strcpy (pNewItem->fileName, ff.GetName ());

			// Attach this item to the beginning of the list.

			if (*ppItem != NULL)
			{
				pNewItem->nextItem = *ppItem;
			}
			*ppItem = pNewItem;
		}

		ff.FindNext ();
	}
	while (ff.IsValidEntry ());

	return EXITCODE_OK;
}
