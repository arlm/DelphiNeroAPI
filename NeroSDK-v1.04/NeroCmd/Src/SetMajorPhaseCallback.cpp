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
|* PROGRAM: SetMajorPhaseCallback.cpp
|*
|* PURPOSE: Callback for reporting major phase changes
******************************************************************************/


#include "stdafx.h"
#include "BurnContext.h"

struct PHASE_MAPPING
{
	NERO_MAJOR_PHASE m_phase;
	LPCSTR m_psDescription;
};

static PHASE_MAPPING s_PhaseMapping[] = {
{NERO_PHASE_UNSPECIFIED					, "Unspecified"},
{NERO_PHASE_START_CACHE					, "Start cache"},
{NERO_PHASE_DONE_CACHE					, "Done cache"},
{NERO_PHASE_FAIL_CACHE					, "Fail cache"},
{NERO_PHASE_ABORT_CACHE					, "Abort cache"},
{NERO_PHASE_START_TEST					, "Start test"},
{NERO_PHASE_DONE_TEST					, "Done test"},
{NERO_PHASE_FAIL_TEST					, "Fail test"},
{NERO_PHASE_ABORT_TEST					, "Abort test"},
{NERO_PHASE_START_SIMULATE				, "Start simulate"},
{NERO_PHASE_DONE_SIMULATE				, "Done simulate"},
{NERO_PHASE_FAIL_SIMULATE				, "Fail simulate"},
{NERO_PHASE_ABORT_SIMULATE				, "Abort simulate"},
{NERO_PHASE_START_WRITE					, "Start write"},
{NERO_PHASE_DONE_WRITE					, "Done write"},
{NERO_PHASE_FAIL_WRITE					, "Fail write"},
{NERO_PHASE_ABORT_WRITE					, "Abort write"},
{NERO_PHASE_START_SIMULATE_NOSPD		, "Start simulate nospd"},
{NERO_PHASE_DONE_SIMULATE_NOSPD			, "Done simulate nospd"},
{NERO_PHASE_FAIL_SIMULATE_NOSPD			, "Fail simulate nospd"},
{NERO_PHASE_ABORT_SIMULATE_NOSPD		, "Abort simulate nospd"},
{NERO_PHASE_START_WRITE_NOSPD			, "Start write nospd"},
{NERO_PHASE_DONE_WRITE_NOSPD			, "Done write nospd"},
{NERO_PHASE_FAIL_WRITE_NOSPD			, "Fail write nospd"},
{NERO_PHASE_ABORT_WRITE_NOSPD			, "Abort write nospd"},
{NERO_PHASE_PREPARE_ITEMS				, "Prepare items"},
{NERO_PHASE_VERIFY_COMPILATION			, "Verify compilation"},
{NERO_PHASE_VERIFY_ABORTED				, "Verify aborted"},
{NERO_PHASE_VERIFY_END_OK				, "Verify end ok"},
{NERO_PHASE_VERIFY_END_FAIL				, "Verify end fail"},
{NERO_PHASE_ENCODE_VIDEO				, "Encode video"},
{NERO_PHASE_SEAMLESSLINK_ACTIVATED      , "Seamlesslink activated"},
{NERO_PHASE_BUP_ACTIVATED				, "BUP activated"},
{NERO_PHASE_START_FORMATTING			, "Start formatting"},
{NERO_PHASE_CONTINUE_FORMATTING			, "Continue formatting"},
{NERO_PHASE_FORMATTING_SUCCESSFUL		, "Formatting successful"},
{NERO_PHASE_FORMATTING_FAILED			, "Formatting failed"},
{NERO_PHASE_PREPARE_CD					, "Prepare CD"},
{NERO_PHASE_DONE_PREPARE_CD				, "Done prepare CD"},
{NERO_PHASE_FAIL_PREPARE_CD				, "Fail prepare CD"},
{NERO_PHASE_ABORT_PREPARE_CD			, "Abort prepare CD"},
{NERO_PHASE_DVDVIDEO_DETECTED			, "Dvdvideo detected"},
{NERO_PHASE_DVDVIDEO_REALLOC_STARTED	, "Dvdvideo realloc started"},
{NERO_PHASE_DVDVIDEO_REALLOC_COMPLETED	, "Dvdvideo realloc completed"},
{NERO_PHASE_DVDVIDEO_REALLOC_NOTNEEDED	, "Dvdvideo realloc not needed"},
{NERO_PHASE_DVDVIDEO_REALLOC_FAILED		, "Dvdvideo realloc failed"},
};


// This is a Nero callback that prints the change of major phase.

void NERO_CALLBACK_ATTR CBurnContext::SetMajorPhaseCallback (void *pUserData, NERO_MAJOR_PHASE phase, void * reserved)
{
	// Declare the buffer variable and set it to a default message.
	//
	char sBuffer[100] = "PHASE: unknown";

	// Search for the appropriate phase mapping description string.
	//
	for (int i = 0; i < sizeof (s_PhaseMapping)/sizeof (s_PhaseMapping[0]); i ++)
	{
		if (phase == s_PhaseMapping[i].m_phase)
		{
			// If the phase was found in the phase mapping table then
			// use it and break the for loop. We don't need to check
			// for buffer overflow as we "know" all our messages are short
			// enough to fit in the buffer.
			//
			sprintf (sBuffer, "PHASE: %s", s_PhaseMapping[i].m_psDescription);
			break;
		}
	}

	printf ("    %-76s\n", sBuffer);
}
