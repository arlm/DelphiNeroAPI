/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / Samples
|*
|* PROGRAM: NeroISODemo.cpp
|*
|* PURPOSE: This demo implementation supports storing of files
|*			or complete directory trees in the root directory
|*			of an ISO track. Each subdirectory is scanned while
|*			the Nero API builds its internal tree, so we don't
|*			have to build a tree ourselves.
|*
|*			However, the implementation of CNeroIsoHandle becomes
|*			very inefficient this way because each handle contains
|*			the full path. It would be better for trees with many
|*			files to use a tree and construct the full filename
|*			from going back in the tree to the root.
******************************************************************************/


#include "NeroIsoTrack.h"
#include <string>
#include <list>
#include <errno.h>
using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

extern void Exit (int ret);

//
// This demo implementation supports storing of files
// or complete directory trees in the root directory
// of an ISO track. Each subdirectory is scanned while
// the Nero API builds its internal tree, so we don't
// have to build a tree ourselves.
//
// However, the implementation of CNeroIsoHandle becomes
// very inefficient this way because each handle contains
// the full path. It would be better for trees with many
// files to use a tree and construct the full filename
// from going back in the tree to the root.
//

//
// Reading is done with ordinary FILEs.
//
class CDemoReadCallback : public CNeroDataCallback
{
	FILE *m_pFile;
public:
	CDemoReadCallback (string sFullName)	// open file
	{
		m_pFile = fopen (sFullName.c_str (), "rb");
	}
	~CDemoReadCallback ()					// delete file
	{
		if (m_pFile) {
			fclose (m_pFile);
		}
	}
	virtual DWORD IOCallback (BYTE *pBuffer, DWORD dwLen)	// read from file
	{
		int read = 0;
	   
		if (m_pFile) {
			read = fread (pBuffer, 1, dwLen, m_pFile);
			if (read < 0) {
				perror ("fread");
			}
		}
		return read;
	}
	virtual BOOL EOFCallback ()		{ return m_pFile && feof (m_pFile); }		// calls map to standard functions directly
	virtual BOOL ErrorCallback ()	{
	   /* FIXME: no implementation for ferror() in crtdll.
	    * so no errors occur here :-) */
	   /*return m_pFile && ferror (m_pFile);*/
	   return 0;		
	}

	BOOL Okay () { return m_pFile != NULL; }									// initialized okay?
};

//
// This callback is created by this handle from the full name
// store in it:
//
class CDemoIsoHandle : public CNeroIsoHandle
{
	string m_sFullName;
public:
	CDemoIsoHandle (string sFullName) : m_sFullName (sFullName) { }
	virtual CNeroIsoHandle *Clone ()	{ return new CDemoIsoHandle (m_sFullName); }

	virtual int GetFileName (char *strBuffer, UINT nBufferSize)
	{
		// you can choose if files are read by Nero API or via callback
		#if 1

		// directly by API: give the name to the API
		if (nBufferSize) {
			strncpy (strBuffer, m_sFullName.c_str (), nBufferSize);
			strBuffer[nBufferSize - 1] = 0;
		}
		return m_sFullName.length ();

		#else

		// via callback: refuse to give away the name
		return 0;

		#endif
	}

	
	CNeroDataCallback *Open ()
	{
		CDemoReadCallback *pCallback = new CDemoReadCallback (m_sFullName);
		// opening it may have failed
		if (pCallback && !pCallback->Okay ()) {
			delete pCallback;
			pCallback = NULL;
		}
		return pCallback;
	}
};

//
// reads the file/directory infos and gives them to the API
//
class CDemoIsoEntry : public CNeroIsoEntry
{
	string	m_sFullName;		// name including full path
	string	m_sFileName;		// the name within the current directory
	__int64	m_i64Size;			// < 0 for directory, otherwise size of file 
	time_t	fileTime;

public:
	CDemoIsoEntry () { m_i64Size = -1; }
	CDemoIsoEntry (const char *strFullName) { this->SetName (strFullName); }
	
	void SetName (const char *strFullName)		// read infos and remember everything
	{
		struct _stati64 buf;
	   
		if (_stati64 (strFullName, 
			  &buf)) {
			perror (strFullName);
			Exit (10);
		}
		m_sFullName = strFullName;

		// find last occurance of either "/" or "\"
		const char *name = strrchr (strFullName, '/');
		const char *tmp = strrchr (strFullName, '\\');
		if (!name) {
			name = tmp;
		} else if (tmp) {
			if (tmp > name) {
				name = tmp;
			}
		}
		if (!name || !*name) {
			name = strFullName;
		} else {
			name++;
		}
		m_sFileName = name;
		m_i64Size = (buf.st_mode & _S_IFDIR) ? -1 : buf.st_size;

		fileTime=buf.st_mtime;
	}

	virtual CNeroIsoIterator * CreateDirectoryIterator();	// implemented below because we have to define CDemoIsoIterator first
	
	virtual const char *       GetName ()					{ return m_sFileName.c_str (); }
	virtual __int64            GetLength ()					{ return m_i64Size; }
	virtual BOOL GetEntryTime(tm *tm)
	{
		struct tm *time=localtime(&fileTime);
		if (time==NULL) 
			return FALSE;
		else
		{
			*tm=*time;
			return TRUE;
		}
	}
	virtual CNeroIsoHandle *   CreateHandle ()				{ return new CDemoIsoHandle (m_sFullName); }
};

//
// Our iterator implements both interfaces and thus returns a pointer
// to itself when asked for the current entry (but only while it really
// has information about a file).
//
class CDemoIsoIterator : public CNeroIsoIterator, public CDemoIsoEntry
{
	long m_lHandle;				// for searching with findfirst/next/close()
	_finddata_t m_FindData;		// the result of last call to findfirst/next()
	string m_sPath;				// the directory we are searching in
	BOOL m_bValid;				// we currently have valid information


	// The information about the current entry are stored in the base
	// class CDemoIsoEntry. FindData2Entry() sets them there:
	void FindData2Entry ()
	{
		// skip current and parent directory entries
		while (!strcmp (m_FindData.name, ".") || !strcmp (m_FindData.name, "..")) {
			this->Next ();
			if (!m_bValid) {
				// found end of directory, give up
				return;
			}
		}

		// build name
		string sFullName = m_sPath;
		sFullName += "\\";
		sFullName += m_FindData.name;

		// ask base class to analyze this name
		this->SetName (sFullName.c_str ());

		// base class would have quit if there was a problem,
		// so now we are fine
		m_bValid = TRUE;
	}

public:
	CDemoIsoIterator (const char *strPath) : m_sPath (strPath), m_bValid (FALSE)
	{
		// start searching this directory for any file
		string pattern = strPath;
		pattern += "\\*";
		m_lHandle = _findfirst (pattern.c_str (), &m_FindData);
		if (m_lHandle == -1) {
			perror (strPath);
			Exit (10);
		}

		// copy informations for first entry
		this->FindData2Entry ();
	}
	~CDemoIsoIterator () { _findclose (m_lHandle); }

	virtual CNeroIsoEntry *GetCurrentEntry () { return m_bValid ? this : NULL; }	// our base class _is_ the current entry if m_bValid is TRUE
	virtual void Next ()
	{
		// invalidate ourself
		m_bValid = FALSE;
		if (_findnext (m_lHandle, &m_FindData) == -1) {
			// quit unless the error indicates the end of the directory
			if (errno != ENOENT) {
				perror ("findnext");
				Exit (10);
			}
		} else {
			// copy new infos
			this->FindData2Entry ();
		}
	}
};

// now that CDemoIsoIterator is defined we can implement this function
CNeroIsoIterator * CDemoIsoEntry::CreateDirectoryIterator()
{
	return new CDemoIsoIterator (m_sFullName.c_str ());
};

//
// The root directory is implemented by a seperate class
// which has a list of entries that are traversed by
// a special iterator and also provides the other
// ISO track options.
//
class CDemoIsoTrack : public CNeroIsoTrack
{
	string m_sVolumeName;						// ISO volume name
	typedef list <CDemoIsoEntry> DemoList_t;	// type definition for storing them and
	DemoList_t m_Entries;						// all entries in the root directory themselves

	BOOL m_bUseJoliet;
	BOOL m_bUseMode2;
	BOOL m_bBurnISO;
	BOOL m_bBurnUDF;
	BOOL m_bReallocDVDVideoFiles;

	class CDemoRootIterator : public CNeroIsoIterator	// traverses any STL collection of CDemoIsoEntries
	{
		DemoList_t::iterator m_End;						// STL end marker
		DemoList_t::iterator m_Current;					// STL iterator

	public:
		CDemoRootIterator (DemoList_t &List) : m_End (List.end ()), m_Current (List.begin ()) { }
		virtual CNeroIsoEntry *GetCurrentEntry ()	{ return m_Current != m_End ? &(*m_Current) : NULL; }
		virtual void Next ()						{ m_Current++; }
	};

public:
	CDemoIsoTrack ()
	{
		m_bUseJoliet = TRUE;
		m_bUseMode2 = FALSE;
		m_bBurnISO = TRUE;
		m_bBurnUDF = FALSE;
		m_bReallocDVDVideoFiles = FALSE;
	}

	// modify settings for ISO track
	void SetVolumeName (const char *strVolumeName)	{ m_sVolumeName = strVolumeName; }
	void SetJoliet (BOOL bUseJoliet)				{ m_bUseJoliet = bUseJoliet; }
	void SetMode2 (BOOL bUseMode2)					{ m_bUseMode2 = bUseMode2; }
	void SetISO(BOOL b)								{ m_bBurnISO = b;}
	void SetUDF(BOOL b)								{ m_bBurnUDF = b;}
	void SetReallocDVDVideoFiles(BOOL b)			{ m_bReallocDVDVideoFiles = b;}

	// return settings
	virtual const char *       GetName ()					{ return m_sVolumeName.c_str (); }

	// add a file/directory - the base name is kept in the ISO track,
	// but the path is discarded, i.e. "C:\Dir1\Dir2" will be stored
	// as ":\Dir2" on the disc.
	void AddEntry (const char *strEntryName)		{ m_Entries.insert (m_Entries.end(), CDemoIsoEntry (strEntryName)); }

	// return new iterator
	virtual CNeroIsoIterator * CreateDirectoryIterator ()	{ return new CDemoRootIterator (m_Entries); }

    virtual DWORD              BurnOptions() 
	{
		return (m_bUseJoliet ? NCITEF_USE_JOLIET : 0)
			  |(m_bUseMode2 ? NCITEF_USE_MODE2 : 0)
			  |(m_bBurnISO ? NCITEF_CREATE_ISO_FS : 0)
			  |(m_bBurnUDF ? NCITEF_CREATE_UDF_FS : 0)
			  |(m_bReallocDVDVideoFiles ? NCITEF_DVDVIDEO_REALLOC : 0);
	}
};
