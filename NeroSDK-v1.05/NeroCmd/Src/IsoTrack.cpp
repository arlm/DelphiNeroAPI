/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2004 Ahead Software AG. All Rights Reserved.
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
#include "Response.h"


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

		printf ((pItem->isDirectory)? "[%s]\n": "%s\n", (pItem->longFileName != NULL)? pItem->longFileName: pItem->fileName);

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

	// Make sure that the user wanted to import a session at all.
	// 
	if (params.GetDoImportSession ())
	{
		// Make sure that NeroGetCDInfo has not been called before to prevent multiple 
		// allocation of memory for NERO_CD_INFO.

		_ASSERTE (m_NeroCDInfo == NULL);

		// First get the CD info to obtain information about all available sessions

		m_NeroCDInfo = NeroGetCDInfo (m_NeroDeviceHandle, 0);
		if (NULL == m_NeroCDInfo)
		{
			return EXITCODE_ERROR_GETTING_CD_INFO;
		}

		// The the user's choice for a session, if one is provided. If not,
		// take the last session.
		// 
		int iSessionToImport = -1;
		if(params.GetImportVMSSession())
		{
			NERO_VMS_INFO *pVMSInfo = NeroGetVMSInfo(m_NeroDeviceHandle,0);

			if(!pVMSInfo)
			{
				return EXITCODE_ERROR_GETTING_VMS_INFO;
			}

			int iNumSessions = pVMSInfo->nvmsiNumSessions;

			NeroFreeMem(pVMSInfo);
			pVMSInfo = NULL;

			iSessionToImport = (-1 != params.GetSessionToImport())? params.GetSessionToImport (): (iNumSessions - 1);
			
			// Check the numbers and make sure that the requested session exists.
			// 
			if (iSessionToImport < 0 ||
				iSessionToImport >= iNumSessions)
			{
				return EXITCODE_BAD_IMPORT_SESSION_NUMBER;
			}
		}
		else
		{
			iSessionToImport = (-1 != params.GetSessionToImport())? params.GetSessionToImport (): (m_NeroCDInfo->ncdiNumTracks - 1);
		
			// Check the numbers and make sure that the requested session exists.
			// 
			if (iSessionToImport < 0 ||
				iSessionToImport >= (int)(m_NeroCDInfo->ncdiNumTracks))
			{
				return EXITCODE_BAD_IMPORT_SESSION_NUMBER;
			}
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
/*		if (params.GetImportIsoOnly())
		{
			dwFlags |= NIITEF_IMPORT_ISO_ONLY;
		} */
/*		if (params.GetPreferRockRidge())
		{
			dwFlags |= NIITEF_PREFER_ROCKRIDGE;
		} */
		if (params.GetImportVMSSession())
		{
			dwFlags |= NIITEF_IMPORT_VMS_SESSION;
		}
		
		// Now, import the session. If the function fails, it's probably
		// due to no CD in drive.
		// NeroImportDataTrack creates a NERO_ISO_ITEM tree from an already
		// existing ISO track in order to create a new session with reference
		// to files from older sessions.
		// m_pCDStamp will be filled with a pointer to a CDStamp object
		// which will have to be freed later by the CBurnContext destructor.

		// ppItem is a reference to a pointer to a NERO_ISO_ITEM
		// So to get the required pointer to a NERO_ISO_ITEM we have to
		// de-reference ppItem once.

		NERO_IMPORT_DATA_TRACK_INFO nidti;
		NERO_IMPORT_DATA_TRACK_RESULT nidtr;

		// Prepare the struct.
		// 
		memset (&nidti, 0, sizeof (nidti));
		nidti.nidtiSize = sizeof (nidti);

		*ppItem = NeroImportDataTrack (m_NeroDeviceHandle,
										iSessionToImport,
										&m_pCDStamp,
										&nidti,
										dwFlags,
										&nidtr,
										NULL);

		// If there is a volume name after import, print it out.
		// 
		if (NULL != nidti.nidtipVolumeName)
		{
			printf ("\nImported volume name: %s\n", nidti.nidtipVolumeName);
			NeroFreeMem (nidti.nidtipVolumeName);
		}

		// If there was an error during import, let the user know about it.
		// 
		if (NIDTR_NO_ERROR != nidtr)
		{
			static LPCSTR errors[] = {
				"an unknown error",
				"a generic error",
				"a drive error",
				"a read error",
				"a filesystem error",
			};

			if (nidtr > NIDTR_INVALID_FS)
			{
				nidtr = NIDTR_NO_ERROR;
			}

			printf ("\nThere was %s while importing the track!\n", errors[nidtr]);
		}

		// The NERO_ISO_ITEM pointer must not be NULL

		if (NULL == *ppItem)
		{
			return EXITCODE_NO_CD_INSERTED;
		}

	}  // if (params.GetDoImportSession ())

	// Iterate through the file list and it each one to the tree.
	// If directory is stumbled upon, recurse it and it all of
	// its contents.

	for (int i = 0; i < params.GetFileListSize(); i ++)
	{
		NERO_ISO_ITEM* pItem=NULL;
		EXITCODE code;

		// Create a tree from the filename supplied.

		code = CreateIsoTree (params, params.GetFileList().vect[i], &pItem);

		// If there was a problem creating the tree then delete 
		// the whole tree that has been created so far and
		// return the error code.

		if (code != EXITCODE_OK)
		{
			DeleteIsoItemTree (*ppItem);
			*ppItem=NULL;
			return code;
		}

		// Merge the new track with the existing one. The user could
		// specify similar paths/content on the command line. We must make
		// sure the duplicates are weeded out. If return value is false,
		// we need to quit.
		// 
		if (!MergeIsoTrack (params, ppItem, pItem))
		{
			return EXITCODE_FAILED_TO_CREATE_ISO_TRACK;
		}
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
			dwFlags |= NCITEF_DVDVIDEO_CMPT;
		}
		if (params.GetUseAllSpace ())
		{
			dwFlags |= NCITEF_USE_ALLSPACE;
		}
		if (params.GetRelaxJoliet ())
		{
			dwFlags |= NCITEF_RELAX_JOLIET;
		}
		if (params.GetDVDVideoCmpt())
		{
			dwFlags |= NCITEF_DVDVIDEO_CMPT;
		}
		
		// This is used only for debugging purposese. Never allow this
		// call to take place in Release code.
		// 
//		DebugPrintIsoTrack (*ppItem);

		NERO_CITE_ARGS citeArgs;

		memset (&citeArgs, 0, sizeof (citeArgs));

		citeArgs.dwBurnOptions = dwFlags;
		citeArgs.name = params.GetVolumeName();
		citeArgs.firstRootItem = *ppItem;
		citeArgs.abstract = params.GetAbstract ();
		citeArgs.application = params.GetApplication ();
		citeArgs.bibliographic = params.GetBibliographic ();
		citeArgs.copyright = params.GetCopyright ();
		citeArgs.dataPreparer = params.GetDataPreparer ();
		citeArgs.publisher = params.GetPublisher ();
		citeArgs.systemIdentifier = params.GetSystemIdentifier ();
		citeArgs.volumeSet = params.GetVolumeSet ();
		
		// Finally, create the ISO track.

		*ppIsoTrack = NeroCreateIsoTrackEx (NULL,
											(const char *) &citeArgs,
											NCITEF_USE_STRUCT);
		
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

// A helper to get the correct filename in a NERO_ISO_ITEM.
// 
inline LPCSTR GetFilename (const NERO_ISO_ITEM * pItem)
{
	return (pItem->longFileName != NULL)? pItem->longFileName: pItem->fileName;
}

// A helper to get the correct filename source path in a NERO_ISO_ITEM.
// 
inline LPCSTR GetFilenameSourcePath (const NERO_ISO_ITEM * pItem)
{
	return (pItem->longSourceFilePath != NULL)? pItem->longSourceFilePath: pItem->sourceFilePath;
}

// The following function performs a merge operation between two iso item
// trees. The second tree is added onto the first one and the extra items
// are deleted. A "--backup" option is honored. If specified, only the new
// items in the second tree replace the corresponding items in the first
// tree.
// 
// If merging two non-imported iso trees, if file name conflicts are found
// the user decides what to do (unless there should be no user interaction).
// 
// False return value means that the user chose to quit!
// 
bool CBurnContext::MergeIsoTrack (const PARAMETERS & params, NERO_ISO_ITEM ** ppItemFirst, NERO_ISO_ITEM * pItemToAdd)
{
	bool bSuccess = true;

	// Two loops. Outter loops the first tree, the inner loops the second
	// tree.
	// 
	for (; bSuccess && *ppItemFirst != NULL; ppItemFirst = &(*ppItemFirst)->nextItem)
	{
		for (NERO_ISO_ITEM ** ppItemSecond = &pItemToAdd; *ppItemSecond != NULL; )
		{
			// Compare entry names...
			// 
			if ((*ppItemFirst)->isDirectory == (*ppItemSecond)->isDirectory &&
				0 == stricmp (GetFilename (*ppItemFirst), GetFilename (*ppItemSecond)))
			{
				bool bReplace = true;

				// The items point to the same file/directory. We need
				// to remove one of them. Which one is removed depends
				// on whether "--backup" is specified on command line.
				// If it is a directory, make sure to recurse anyway
				// because the trees below may not be identical.
				// 
				if ((*ppItemFirst)->isDirectory)
				{
					bSuccess = MergeIsoTrack (params, &(*ppItemFirst)->subDirFirstItem, (*ppItemSecond)->subDirFirstItem);
					(*ppItemSecond)->subDirFirstItem = NULL;
					
					if (!bSuccess)
					{
						break;
					}
					
					// Since the item is a directory, we won't replace
					// the old one as it doesn't matter which one we
					// keep. Directory is just a name. It has no file
					// access time stamp.
					// 
					bReplace = false;
				}
				else
				{
					// If there is a file name conflict between iso items
					// that don't belong to imported sessions, ask the user
					// what to do.
					// 
					if (!(*ppItemFirst)->isReference)
					{
						printf ("\nThere is a file name conflict!\n"
							"%s\n"
							"%s\n"
							"Do you want to use the first or second file, or to exit?\n",
							GetFilenameSourcePath (*ppItemFirst),
							GetFilenameSourcePath (*ppItemSecond));

						static const CResponsePairs mapping[] = {
							"First", DLG_RETURN_TRUE,
							"Second", DLG_RETURN_FALSE,
							"Exit", DLG_RETURN_CANCEL,
							NULL};
						CResponse response (mapping, 0);
							
						NeroUserDlgInOut result = response;

						// If the user chose to quit, then obey and quit.
						// 
						if (result == DLG_RETURN_CANCEL)
						{
							bSuccess = false;
							break;
						}
						else
						{
							// Otherwise, choose between first and second
							// file.
							// 
							bReplace = (result == DLG_RETURN_FALSE);
						}
					}
					else
					{
						// If no "--backup" was specified, always replace
						// the old files.
						// 
						if (!params.GetBackup ())
						{
							bReplace = true;
						}
						else
						{
							// If there is a "--backup" command line,
							// replace the old one only if older in terms
							// of access times.
							// 
							time_t timeOld = mktime (&(*ppItemFirst)->entryTime);
							time_t timeNew = mktime (&(*ppItemSecond)->entryTime);
							
							bReplace = timeOld < timeNew;
						}
					}
				}
				
				if (bReplace)
				{
					// We will now switch places of items in the first and
					// second tree. Since one of the items has to be deleted
					// eventually, this operation will essentially keep
					// the item from the second tree and delete the item
					// from the first tree.
					// 
					NERO_ISO_ITEM * pTempItem = *ppItemSecond;
					*ppItemSecond = *ppItemFirst;
					*ppItemFirst = pTempItem;
					pTempItem = (*ppItemSecond)->nextItem;
					(*ppItemSecond)->nextItem = (*ppItemFirst)->nextItem;
					(*ppItemFirst)->nextItem = pTempItem;
				}

				// Remove the item from the second tree.
				// 
				NERO_ISO_ITEM * pTempItem = *ppItemSecond;
				*ppItemSecond = pTempItem->nextItem;
				pTempItem->nextItem = NULL;
				DeleteIsoItemTree (pTempItem);
			}
			else
			{
				// No match, advance to the next item.
				// 
				ppItemSecond = &(*ppItemSecond)->nextItem;
			}
		}
	}

	// Attach whatever is left of the new tree to the main tree.
	// 
	*ppItemFirst = pItemToAdd;

	// Returning true means, everything is fine, continue.
	// 
	return bSuccess;
}

// This function deletes the iso tree recursively.

void CBurnContext::DeleteIsoItemTree (NERO_ISO_ITEM * pItem)
{
	// First free our own long filename strings, then free the whole tree.
	// 
	FreeOurOwnResources (pItem);
	NeroFreeIsoItemTree (pItem);
}

void CBurnContext::FreeOurOwnResources (NERO_ISO_ITEM * pItem)
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

			FreeOurOwnResources (pItem->subDirFirstItem);
		}

		// It the item is not a reference, free its associated long
		// filenames, if any.
		// 
		if (!pItem->isReference)
		{
			delete pItem->longFileName;
			delete (char *) pItem->longSourceFilePath;
		}

		pItem = pNextItem;
	}
}


// This function searches for a specified path and recursively adds
// all files and directories that are found.

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

				StoreFileName (pNewItem->fileName, pNewItem->longFileName, ff.GetName ());

				// If we the user wants recursive search, only then do we
				// actually recurse at deeper levels otherwise ignore directories
				// alltogether.
				// 
				if (params.GetRecursive ())
				{
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

			StoreFileName (pNewItem->sourceFilePath, (char *) pNewItem->longSourceFilePath, sNewPath.c_str ());
			
			pNewItem->isDirectory = FALSE;
			time_t t = ff.GetCreateTime ();
			pNewItem->entryTime = *localtime (&t);

			StoreFileName (pNewItem->fileName, pNewItem->longFileName, ff.GetName ());
			
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

void CBurnContext::StoreFileName (char (& shortFilename) [252], char * psLongFilename, LPCSTR psFilename)
{
	// If filename can fit in the old field, store it there
	// to prevent unnecessary allocation. If not, allocate
	// a sufficient buffer to hold the string.
	// 
	int iLen = strlen (psFilename);

	if (iLen < sizeof (shortFilename))
	{
		strcpy (shortFilename, psFilename);
	}
	else
	{
		psLongFilename = new char [iLen + 1];
		if (psLongFilename != NULL)
		{
			strcpy (psLongFilename, psFilename);
		}
	}
}
