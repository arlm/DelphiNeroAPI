/******************************************************************************
|* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
|* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
|* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
|* PARTICULAR PURPOSE.
|* 
|* Copyright 1995-2003 Ahead Software AG. All Rights Reserved.
|*-----------------------------------------------------------------------------
|* NeroSDK / NeroAPI
|*
|* PROGRAM: FileSystemBlockAccessExtensions.h
|*
|* PURPOSE: All block device access extensions are derived from this one.
|*
******************************************************************************/
#ifndef FILESYSTEMBLOCKACCESSEXTENSIONS_H
#define FILESYSTEMBLOCKACCESSEXTENSIONS_H

/* 
 * Type of an extension.
 * Currently no extension is provided within the NeroSDK
 */
enum NeroFSBlockAccessExtensionsType
{
	etMRWReadDefectiveManagementInfo,
	etDVDPRWFormatExtension,
	etSectorMappingControlExtension,
	etBlankAreaControlExtension,
	etIllegalBlockAccessExtension,
	etHDPartitionInfo,
	etHDUsedBlockAccessExtention,
	etSectorPatchControlExtension
};

class INeroFileSystemBlockAccessExtension
{
public:
	virtual NeroFSBlockAccessExtensionsType GetExtensionType() const = 0;

	virtual ~INeroFileSystemBlockAccessExtension() {}; 
};

#endif // FILESYSTEMBLOCKACCESSEXTENSIONS_H
