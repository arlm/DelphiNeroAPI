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
|* PROGRAM: getopt.cpp
|*
|* PURPOSE: Constructors for PARAMETERS class
|*          Decoding of argument list
|*          Help function
|*          Parsing of parameter file
******************************************************************************/


#include "stdafx.h"
#include "getopt.h"
#include "parameters.h"

#if defined(__BORLANDC__)
#include <algorithm.h>
#endif


// Forward declarations. These are the functions used before they are
// defined.
// 
static void Usage (void);
static bool ReadParameterFile (PARAMETERS & params, LPCSTR psFilename);


// These are error strings that correspond to the CLE_xxx error codes.

static LPCSTR s_cle[CLE_MAX] = {
	"Everything fine.",
	"Multiple commands were specified from the following set: listdrives, cdinfo, read, write, erase, eject, load. Only one command is allowed at one time.",
	"Missing drive name parameter after --drivename.",
	"Missing artist parameter after --artist.",
	"Missing title parameter after --title.",
	"Missing speed parameter after --speed.",
	"Supplied speed parameter is invalid.",
	"Missing volume name parameter after --iso.",
	"Invalid -- parameter.",
	"Multiple burn types were specified from the following set: iso/audio, videocd, svideocd, image. Only one burn type is allowed at one time.",
	"Missing file name after --XX parameter.",
	"Maximum number of 99 tracks has been reached.",
	"Parameter file was already processed. It cannot be done recursively!",
	"Missing image filename parameter after --image.",
	"Missing error log filename parameter after --error_log.",
	"Missing import session parameter after --import.",
	"Supplied import session parameter is invalid.",
	"Iso/Audio and (S)VideoCD need at least one track!",
	"Burn type was not specified! Use a proper combination of --audio, --videocd, --svideocd and --iso.",
	"No command was specified!",
	"Missing temporary path parameter after --temp_path.",
	"Missing media type parameter after --media_type.",
	"Missing output image filename parameter after --output_image.",
	"Missing image info filename parameter after --imageinfo.",
	"Missing system identifier parameter after --system_identifier.",
	"Missing volume set parameter after --volume_set.",
	"Missing publisher parameter after --publisher.",
	"Missing data preparer parameter after --data_preparer.",
	"Missing application parameter after --application.",
	"Missing copyright parameter after --copyright.",
	"Missing abstract parameter after --abstract.",
	"Missing bibliographic parameter after --bibliographic.",
	"Missing resolution parameter after --video_resolution.",
	"Bad resolution parameter after --video_resolution. Only PAL and NTSC are allowed.",
};


// This function decodes the argument list.

bool getopt (PARAMETERS & params, int argc, char ** argv)
{
	if ((0 == argc) && !params.GetProcessedParameterFile())
	{
		Usage ();

		return false;
	}

	COMMAND_LINE_ERRORS ecl = CLE_NO_ERROR;

	try
	{
		for (; argc>0; argc--, argv++)
		{
			if (CLE_NO_ERROR != ecl)
			{
				throw ecl;
			}
			else if (stricmp (*argv, "--listdrives") == 0)
			{
				ecl = params.SetCommand(COMMAND_LISTDRIVES);
			}
			else if (stricmp (*argv, "--version") == 0)
			{
				ecl = params.SetCommand(COMMAND_VERSION);
			}
			else if (stricmp (*argv, "--cdinfo") == 0)
			{
				ecl = params.SetCommand(COMMAND_CDINFO);
			}
			else if (stricmp (*argv, "--read") == 0)
			{
				ecl = params.SetCommand(COMMAND_READ);
			}
			else if (stricmp (*argv, "--write") == 0)
			{
				ecl = params.SetCommand(COMMAND_WRITE);
			}
			else if (stricmp (*argv, "--erase") == 0)
			{
				ecl = params.SetCommand(COMMAND_ERASE);
			}
			else if (stricmp (*argv, "--eject") == 0)
			{
				ecl = params.SetCommand(COMMAND_EJECT);
			}
			else if (stricmp (*argv, "--load") == 0)
			{
				ecl = params.SetCommand(COMMAND_LOAD);
			}
			else if (stricmp (*argv, "--driveinfo") == 0)
			{
				ecl = params.SetCommand(COMMAND_DRIVE_INFO);
			}
			else if (stricmp (*argv, "--listformats") == 0)
			{
				ecl = params.SetCommand(COMMAND_LISTFORMATS);
			}
			else if (stricmp (*argv, "--get_speeds") == 0)
			{
				ecl = params.SetCommand(COMMAND_GET_SPEEDS);
			}
			else if (stricmp (*argv, "--estimate") == 0)
			{
				ecl = params.SetCommand(COMMAND_ESTIMATE);
			}
			else if (stricmp (*argv, "--internal") == 0)
			{
				ecl = params.SetCommand(COMMAND_INTERNAL);
			}
			else if (stricmp (*argv, "--drivename") == 0)
			{
				ecl = params.SetDriveName(argc, argv);
			}
			else if (stricmp (*argv, "--no_user_interaction") == 0)
			{
				ecl = params.SetNoUserInteraction ();
			}
			else if (stricmp (*argv, "--real") == 0)
			{
				ecl = params.SetUseReal();
			}
			else if (stricmp (*argv, "--tao") == 0)
			{
				ecl = params.SetUseTAO();
			}
			else if (stricmp (*argv, "--underrun_prot") == 0)
			{
				ecl = params.SetUseUnderRunProt();
			}
			else if (stricmp (*argv, "--no_error_log") == 0)
			{
				ecl = params.SetWriteErrorLog();
			}
			else if (stricmp (*argv, "--speedtest") == 0)
			{
				ecl = params.SetSpeedTest();
			}
			else if (stricmp (*argv, "--enable_abort") == 0)
			{
				ecl = params.SetEnableAbort();
			}
			else if (stricmp (*argv, "--close_session") == 0)
			{
				ecl = params.SetCloseSession();
			}
			else if (stricmp (*argv, "--detect_non_empty_cdrw") == 0)
			{
				ecl = params.SetDetectNonEmptyCDRW();
			}
			else if (stricmp (*argv, "--cd_text") == 0)
			{
				ecl = params.SetUseCDText();
			}
			else if (stricmp (*argv, "--japanese_cd_text") == 0)
			{
				ecl = params.SetJapaneseCDText();
			}
			else if (stricmp (*argv, "--booktype_dvdrom") == 0)
			{
				ecl = params.SetBooktypeDVDROM();
			}
			else if (stricmp (*argv, "--no_booktype_change") == 0)
			{
				ecl = params.SetNoBooktypeChange();
			}
			else if (stricmp (*argv, "--use_rockridge") == 0)
			{
				ecl = params.SetUseRockridge();
			}
			else if (stricmp (*argv, "--create_iso_fs") == 0)
			{
				ecl = params.SetCreateIsoFs();
			}
			else if (stricmp (*argv, "--create_udf_fs") == 0)
			{
				ecl = params.SetCreateUdfFs();
			}
			else if (stricmp (*argv, "--dvdvideo_realloc") == 0)
			{
				ecl = params.SetDVDVideoRealloc();
			}
			else if (stricmp (*argv, "--dvdvideo_cmpt") == 0)
			{
				ecl = params.SetDVDVideoCmpt();
			}
			else if (stricmp (*argv, "--use_allspace") == 0)
			{
				params.SetUseAllSpace();
			}
			else if (stricmp (*argv, "--relax_joliet") == 0)
			{
				params.SetRelaxJoliet();
			}
			else if (stricmp (*argv, "--import_rockridge") == 0)
			{
				// NIITEF_IMPORT_ROCKRIDGE flag is obsolete so we commented the
				// code below but keep the command line option for
				// compatibility.
				//
//				ecl = params.SetImportRockridge();
			}
			else if (stricmp (*argv, "--import_udf") == 0)
			{
				ecl = params.SetImportUDF();
			}
			else if (stricmp (*argv, "--import_vms_session") == 0)
			{
				ecl = params.SetImportVMSSession();
			}
			else if (stricmp (*argv, "--import_iso_only") == 0)
			{
				// if this flag is given, do as if --import is given
				ecl = params.SetSessionToImport(argc, argv);
			}
			else if (stricmp (*argv, "--prefer_rockridge") == 0)
			{
//				ecl = params.SetPreferRockridge();
			}
			else if (stricmp (*argv, "--disable_eject") == 0)
			{
				ecl = params.SetDisableEject();
			}
			else if (stricmp (*argv, "--verify") == 0)
			{
				ecl = params.SetVerify();
			}
			else if (stricmp (*argv, "--error_log") == 0)
			{
				ecl = params.SetErrorLogName(argc, argv);
			}
			else if (stricmp (*argv, "--artist") == 0)
			{
				ecl = params.SetArtist(argc, argv);
			}
			else if (stricmp (*argv, "--title") == 0)
			{
				ecl = params.SetTitle(argc, argv);
			}
			else if (stricmp (*argv, "--read_speed") == 0)
			{
				ecl = params.SetReadSpeed(argc, argv);
			}
			else if (stricmp (*argv, "--speed") == 0)
			{
				ecl = params.SetSpeed(argc, argv);
			}
			else if (stricmp (*argv, "--speed_in_kbps") == 0)
			{
				ecl = params.SetSpeedInKbps(argc, argv);
			}
			else if (stricmp (*argv, "--import") == 0)
			{
				ecl = params.SetSessionToImport(argc, argv);
			}
			else if (stricmp (*argv, "--cdextra") == 0)
			{
				params.SetCDExtra();
			}
			else if (stricmp (*argv, "--iso") == 0)
			{
				ecl = params.SetISOSelected(argc, argv);
			}
			else if (stricmp (*argv, "--iso-no-joliet") == 0)
			{
				params.SetDontUseJoliet();
			}
			else if (stricmp (*argv, "--iso-mode2") == 0)
			{
				params.SetUseMode2();
			}
			else if (stricmp (*argv, "--audio") == 0)
			{
				ecl = params.SetAudioSelected();
			}
			else if (stricmp (*argv, "--videocd") == 0)
			{
				ecl = params.SetBurnType(BURNTYPE_VIDEOCD);
			}
			else if (stricmp (*argv, "--svideocd") == 0)
			{
				ecl = params.SetBurnType(BURNTYPE_SVIDEOCD);
			}
			else if (stricmp (*argv, "--image") == 0)
			{
				params.SetImageBurnType(argc, argv);
			}
			else if (stricmp (*argv, "--freestyle_mode1") == 0 ||
					stricmp (*argv, "--freestyle_mode2") == 0 ||
					stricmp (*argv, "--freestyle_audio") == 0)
			{
				params.SetFreestyleBurnType(argc, argv);
			}
			else if (stricmp (*argv, "--entire") == 0)
			{
				ecl = params.SetEraseMode(NEROAPI_ERASE_ENTIRE);
			}
			else if (stricmp (*argv, "--dvd") == 0)
			{
				ecl = params.SetUseDVD();
			}
			else if (stricmp (*argv, "--dvd_high_compatibility") == 0)
			{
				ecl = params.SetUseDVDHighCompatibility();
			}
			else if (stricmp (*argv, "--recursive") == 0)
			{
				ecl = params.SetRecursive();
			}
			else if (stricmp (*argv, "--nero_log_timestamp") == 0)
			{
				ecl = params.SetNeroLogTimestamp();
			}
			else if (stricmp (*argv, "--force_erase_cdrw") == 0)
			{
				ecl = params.SetForceEraseCDRW();
			}
			else if (stricmp (*argv, "--temp_path") == 0)
			{
				ecl = params.SetTempPath(argc, argv);
			}
			else if (stricmp (*argv, "--media_type") == 0)
			{
				ecl = params.SetMediaType(argc, argv);
			}
			else if (stricmp (*argv, "--disable_eject_after_erase") == 0)
			{
				params.SetDisableEjectAfterErase();
			}
			else if (stricmp (*argv, "--force_eject_after_erase") == 0)
			{
				params.SetForceEjectAfterErase();
			}
			else if (stricmp (*argv, "--output_image") == 0)
			{
				ecl = params.SetOutputImageFileName(argc, argv);
			}
			else if (stricmp (*argv, "--imageinfo") == 0)
			{
				ecl = params.SetCommand(COMMAND_IMAGE_INFO);
				if (ecl == CLE_NO_ERROR)
				{
					ecl = params.SetImageInfoFileName(argc, argv);
				}
			}
			else if (stricmp (*argv, "--system_identifier") == 0)
			{
				ecl = params.SetSystemIdentifier(argc, argv);
			}
			else if (stricmp (*argv, "--volume_set") == 0)
			{
				ecl = params.SetVolumeSet(argc, argv);
			}
			else if (stricmp (*argv, "--publisher") == 0)
			{
				ecl = params.SetPublisher(argc, argv);
			}
			else if (stricmp (*argv, "--data_preparer") == 0)
			{
				ecl = params.SetDataPreparer(argc, argv);
			}
			else if (stricmp (*argv, "--application") == 0)
			{
				ecl = params.SetApplication(argc, argv);
			}
			else if (stricmp (*argv, "--copyright") == 0)
			{
				ecl = params.SetCopyright(argc, argv);
			}
			else if (stricmp (*argv, "--abstract") == 0)
			{
				ecl = params.SetAbstract(argc, argv);
			}
			else if (stricmp (*argv, "--bibliographic") == 0)
			{
				ecl = params.SetBibliographic(argc, argv);
			}
			else if (stricmp (*argv, "--backup") == 0)
			{
				ecl = params.SetBackup ();
			}
			else if (stricmp (*argv, "--video_resolution") == 0)
			{
				ecl = params.SetVideoResolution(argc, argv);
			}
			else if (stricmp (*argv, "--estimate_no_fs_overhead") == 0)
			{
				ecl = params.SetEstimateNoFSOverhead ();
			}
			else if (stricmp (*argv, "--estimate_no_data") == 0)
			{
				ecl = params.SetEstimateNoData ();
			}
			else if (stricmp (*argv, "--estimate_no_exact_size") == 0)
			{
				ecl = params.SetEstimateNoExactSize ();
			}
			else if ((*argv)[0] == '@')
			{
				if (params.GetProcessedParameterFile())
				{
					throw CLE_PARAMETER_FILE_ALREADY_PROCESSED;
				}

				ecl = params.SetProcessedParameterFile();
				if (CLE_NO_ERROR != ecl)
				{
					throw ecl;
				}

				if (!ReadParameterFile (params, &(*argv)[1]))
				{
					return false;
				}
			}
			else if (!strncmp (*argv, "--", 2))
			{
				ecl = params.AddAudioReadTrack(argc, argv);
			}
			else
			{
				ecl = params.AddAudioIsoFreestyleWriteTrack(argc, argv);
			}
		}

		// Make sure we had no error during
		// the last loop execution.

		if (CLE_NO_ERROR != ecl)
		{
			throw ecl;
		}

		if (params.GetCommand() == COMMAND_WRITE && params.GetBurnType() == BURNTYPE_UNKNOWN)
		{
			throw CLE_BURN_TYPE_NOT_SPECIFIED;
		}

		if ((params.GetBurnType() == BURNTYPE_ISOAUDIO ||
			params.GetBurnType() == BURNTYPE_SVIDEOCD ||
			params.GetBurnType() == BURNTYPE_VIDEOCD) &&
			params.GetNumberOfTracks() <= 0 && params.GetFileListSize() == 0)
		{
			throw CLE_NEED_TRACKS;
		}

		if (params.GetCommand () == COMMAND_UNKNOWN)
		{
			throw CLE_NO_COMMAND_SPECIFIED;
		}
	}
	catch (COMMAND_LINE_ERRORS e)
	{
		printf ("%s\n", s_cle[e]);
		Usage ();

		return false;
	}

	return true;
}


// This function displays usage information after the user enters incorrect parameters.
// It always displays only as many lines of text as there are visible lines.

static void Usage (void)
{
	LPCSTR psMessage = 
						"\nUsage:\n"
						"  _______________\n"
						" | List available| --listdrives\n"
						" | drives        |\n"
						" |_______________|\n"
						" | Obtain drive  | --driveinfo --drivename <name>\n"
						" | info          |\n"
						" |_______________|\n"
						" | Obtain disc   | --cdinfo --drivename <name>\n"
						" | info          |\n"
						" |_______________|\n"
						" | Write         | --write --drivename <name> [--real] [--tao]\n"
						" | ISO/Audio CD  | [--artist <artist>] [--title <title>] [--speed <speed>]\n"
						" |               | [--audio] <audio files> [--cdextra] [--iso <volumename>]\n"
						" |               | [--iso-no-joliet] [--iso-mode2] [--speedtest]\n"
						" |               | [--enable_abort] [--close_session] [--detect_non_empty_cdrw]\n"
						" |               | [--cd_text] [--underrun_prot]\n"
						" |               | [--import_udf] [--import_vms_session]\n"
						" |               | [--use_rockridge] [--create_iso_fs] [--create_udf_fs]\n"
						" |               | [--disable_eject] [--verify] [--dvd] [--use_allspace]\n"
						" |               | <disk file> ...\n"
						" |               | [--force_erase_cdrw] [--nero_log_timestamp]\n"
						" |               | [--output_image <filename>]\n"
						" |               |\n"
						" |               | NOTE: At least one audio file or one disk file needs to be\n"
						" |               | specified!\n"
						" |_______________|\n"
						" | Write         | --write --drivename <name> [--real] [--tao]\n"
						" | Video CD      | --videocd [--speed <speed>] [--speedtest] [--enable_abort]\n"
						" |               | [--close_session] <video files> [--iso <volumename>]\n"
						" |               | [--iso-no-joliet] [--iso-mode2] [--speedtest]\n"
						" |               | [--enable_abort] [--close_session] [--detect_non_empty_cdrw]\n"
						" |               | [--underrun_prot] [--disable_eject] <disk file>...\n"
						" |               | [--force_erase_cdrw] [--nero_log_timestamp]\n"
						" |               | [--temp_path <path>] [--output_image <filename>]\n"
						" |_______________|\n"
						" | Write Super   | --write --drivename <name> [--real] [--tao]\n"
						" | Video CD      | --svideocd [--speed <speed>] [--speedtest] [--enable_abort]\n"
						" |               | [--close_session] <video files> [--iso <volumename>]\n"
						" |               | [--iso-no-joliet] [--iso-mode2] [--speedtest]\n"
						" |               | [--enable_abort] [--close_session] [--detect_non_empty_cdrw]\n"
						" |               | [--underrun_prot] [--disable_eject] <disk file>...\n"
						" |               | [--force_erase_cdrw] [--nero_log_timestamp]\n"
						" |               | [--temp_path <path>] [--output_image <filename>]\n"
						" |_______________|\n"
						" | Write image   | --write --drivename <name> [--real] [--tao] [--dvd]\n"
						" |               | --image <image filename> [--speed <speed>] [--speedtest]\n"
						" |               | [--enable_abort] [--close_session] [--detect_non_empty_cdrw]\n"
						" |               | [--underrun_prot] [--disable_eject]\n"
						" |               | [--force_erase_cdrw] [--nero_log_timestamp]\n"
						" |               | [--output_image <filename>]\n"
						" |_______________|\n"
						" | Write         | --write --drivename <name> [--real] [--tao]\n"
						" | freestyle CD  | [--artist <artist>] [--title <title>] [--speed <speed>]\n"
						" |               | [--cdextra] [--iso <volumename>]\n"
						" |               | [--freestyle_mode1 <filename>]\n"
						" |               | [--freestyle_mode2 <filename>]\n"
						" |               | [--freestyle_audio <filename>]\n"
						" |               | [--iso-no-joliet] [--iso-mode2] [--speedtest]\n"
						" |               | [--enable_abort] [--close_session] [--detect_non_empty_cdrw]\n"
						" |               | [--cd_text] [--underrun_prot]\n"
						" |               | [--import_udf] [--import_vms_session]\n"
						" |               | [--use_rockridge] [--create_iso_fs] [--create_udf_fs]\n"
						" |               | [--disable_eject] [--verify] [--use_allspace] <disk file>...\n"
						" |               | [--force_erase_cdrw] [--nero_log_timestamp]\n"
						" |               | [--output_image <filename>]\n"
						" |               |\n"
						" |               | NOTE: Any number of freestyle tracks can be specified up to\n"
						" |               | a maximum of 99 tracks.!\n"
						" |_______________|\n"
						" | Estimate      | --estimate --drivename <name> [--tao]\n"
						" | track size    | [--iso <volumename>] [--iso-no-joliet] [--iso-mode2]\n"
						" |               | [--close_session] [--import_udf] [--import_vms_session]\n"
						" |               | [--use_rockridge] [--create_iso_fs] [--create_udf_fs]\n"
						" |               | [--disable_eject] [--dvd] [--use_allspace]\n"
						" |               | [--estimate_no_fs_overhead] [--estimate_no_data]\n"
						" |               | [--estimate_no_exact_size] <disk file> ...\n"
						" |_______________|\n"
						" | Read audio    | --read --drivename <name> [--read_speed <speed>]\n"
						" | track(s)      | --XY <filename> [-XY <filename> ...]\n"
						" |_______________|\n"
						" | List audio    | --listformats\n"
						" | formats       |\n"
						" |_______________|\n"
						" | Erase disc    | --erase [--entire] --drivename <name>\n"
						" |_______________|\n"
						" | Eject disc    | --eject --drivename <name>\n"
						" |_______________|\n"
						" | Load disc     | --load --drivename <name>\n"
						" |_______________|\n"
						" | Obtain image  | --imageinfo <filename>\n"
						" | file disc info|\n"
						" |_______________|\n"
						" | Version info  | --version\n"
						" |_______________|\n"
						"\n"
						" Each command supports the following switches: [--no_error_log],\n"
						" [--error_log <log filename>], [--no_user_interaction] and [@parameter_file]\n"
						"\n"
						"  _______________\n"
						" | --write       | Burn disc.\n"
						" |_______________|\n"
						" | --drivename   | <name> is either the \"full name\" of the drive or the\n"
						" | <name>        | drive letter.\n"
						" |_______________|\n"
						" | --real        | Forces the disc to be actually burned. If --real is not\n"
						" |               | specified the process is only simulated.\n"
						" |_______________|\n"
						" | --tao         | Disc is burned in TAO mode (DAO is default).\n"
						" |_______________|\n"
						" | --burnproof   | Obsolete option, use --underrun_prot instead.\n"
						" |_______________|\n"
						" | --artist      | <artist> is the artist name as to be written on CD.\n"
						" | <artist>      |\n"
						" |_______________|\n"
						" | --title       | <title> is the title to be written on CD.\n"
						" | <title>       |\n"
						" |_______________|\n"
						" | --read_speed  | <speed> is the speed at which the audio tracks will be read\n"
						" | <speed>       | (in x150KB/s).\n"
						" |_______________|\n"
						" | --speed       | <speed> is the speed at which the disc will be burned\n"
						" | <speed>       | (for CD in x150 KB/s and for DVD in x1,385 KB/s).\n"
						" |_______________|\n"
						" | --speed_in_   | <speed> is the speed at which the disc will be burned\n"
						" |  kbps <speed> | (in KB/s).\n"
						" |_______________|\n"
						" | --audio       | The disc is burned with audio information.\n"
						" |_______________|\n"
						" | <audio files> | <audio files> is a list of audio files (wav, mp3, wma, pcm).\n"
						" |_______________|\n"
						" | --cdextra     | Use the CDExtra feature.\n"
						" |_______________|\n"
						" | --iso         | <volume name> is the volume name to be stored on the disc.\n"
						" | <volume name> |\n"
						" |_______________|\n"
						" |--iso-no-joliet| Do not use Joliet format.\n"
						" |_______________|\n"
						" | --iso-mode2   | Burn the CD using mode 2.\n"
						" |_______________|\n"
						" | --speedtest   | Perform speed test before burning.\n"
						" |_______________|\n"
						" | --enable_abort| Notify which operations can and which cannot be aborted.\n"
						" |_______________|\n"
						" |--close_session| Close the session, not the whole disc.\n"
						" |_______________|\n"
						" |--detect_non_  | Detect if the disc for burning is a non empty\n"
						" | empty_cdrw    | RW media and offer to take certain actions.\n"
						" |_______________|\n"
						" | --cd_text     | Write CD text (if supported by device).\n"
						" |_______________|\n"
						" | --videocd     | Burn a Video CD.\n"
						" |_______________|\n"
						" | --svideocd    | Burn a Super Video CD.\n"
						" |_______________|\n"
						" | <video files> | <video files> represents a list of video files (mpeg, jpeg).\n"
						" |_______________|\n"
						" | --image       | <filename> is the filename to the image file.\n"
						" | <filename>    |\n"
						" |_______________|\n"
						" | --read        | Read audio track(s).\n"
						" |_______________|\n"
						" | --XY          | XY is the number of the audio track that is to be saved to\n"
						" | <filename>    | <filename>.\n"
						" |_______________|\n"
						" | --erase       | Erase an RW media.\n"
						" |_______________|\n"
						" | --entire      | Erase the entire disc (the default is quick erase).\n"
						" |_______________|\n"
						" | --eject       | Eject disc.\n"
						" |_______________|\n"
						" | --load        | Load disc.\n"
						" |_______________|\n"
						" | --version     | Print NeroAPI version information.\n"
						" |_______________|\n"
						" | --underrun_   | Protect from underrun condition.\n"
						" |   prot        |\n"
						" |_______________|\n"
						" | --use_        | Use rockridge format.\n"
						" |   rockridge   |\n"
						" |_______________|\n"
						" | --create      | Create ISO filesystem.\n"
						" |   _iso_fs     |\n"
						" |_______________|\n"
						" | --create      | Create UDF filesystem.\n"
						" |   _udf_fs     |\n"
						" |_______________|\n"
						" | --dvdvideo    | Perform reallocation of files in VIDEO_TS\n"
						" |   _realloc    | directory.\n"
						" |_______________|\n"
						" | --dvdvideo    | Create DVD-Video compatible disc.\n"
						" |   _cmpt       | --create_iso_fs --create_udf_fs and \n"
						" |               | --iso_no_joliet also need to be specified.\n"
						" |_______________|\n"
						" | --import      | Obsolete option; will be ignored.\n"
						" |   rockridge   |\n"
						" |_______________|\n"
						" | --import_udf  | Import UDF format.\n"
						" |_______________|\n"
						" | --import_vms  | Import Virtual Multisession (VMS) session\n"
						" |   _session    | (session number treated as VMS session).\n"
						" |_______________|\n"
						" | --import      | Obsolete option; will be ignored.\n"
						" |   _iso_only   |\n"
						" |_______________|\n"
						" | --import      | Import session number (if omitted, the last\n"
						" |  <session #>  | session is imported).\n"
						" |_______________|\n"
						" | --prefer      | Obsolete option; will be ignored.\n"
						" |   _rockridge  |\n"
						" |_______________|\n"
						" | --freestyle_  | Burn the file in mode 1.\n"
						" |  mode1        |\n"
						" |_______________|\n"
						" | --freestyle_  | Burn the file in mode 2.\n"
						" |  mode2        |\n"
						" |_______________|\n"
						" | --freestyle_  | Burn the file in audio mode.\n"
						" |  audio        |\n"
						" |_______________|\n"
						" | --disable_    | Disables disc ejection after burn completion.\n"
						" |   eject       |\n"
						" |_______________|\n"
						" | --verify      | Verify ISO filesystem after writing.\n"
						" |_______________|\n"
						" | --dvd_high_   | Used for better compatibility of burned DVDs.\n"
						" |  compatibility| At least 1GB will be written.\n"
						" |_______________|\n"
						" | --dvd         | Select DVD as media type.\n"
						" |_______________|\n"
						" | --recursive   | Do a recursive file search.\n"
						" |_______________|\n"
						" | --force_erase_| Delete disc without user interaction\n"
						" |   cdrw        | (requires --detect_non_empty_cdrw).\n"
						" |_______________|\n"
						" | --nero_log_   | Add a timestamp to the log's file name.\n"
						" |   timestamp   |\n"
						" |_______________|\n"
						" | --temp_path   | Specify a temporary path for Video CD files.\n"
						" |_______________|\n"
						" | --media_type  | Specify a media type (combine with +) \n"
						" |   <type>      |  media_cd, media_ddcd, media_dvd_m, media_dvd_p,\n"
						" |               |  media_dvd_any, media_dvd_ram, media_ml, media_mrw,\n"
						" |               |  media_no_cdr, media_no_cdrw, media_cdrw, media_cdr\n"
						" |               |  media_dvd_rom, media_cdrom, media_no_dvd_m_rw,\n"
						" |               |  media_no_dvd_m_r, media_no_dvd_p_rw,\n"
						" |               |  media_no_dvd_p_r, media_dvd_m_r, media_dvd_m_rw,\n"
						" |               |  media_dvd_p_r, media_dvd_p_rw, media_fpacket,\n"
						" |               |  media_vpacket, media_packetw or media_hdb).\n"
						" |_______________|\n"
						" | --no_user_    | Allow the whole process to take place with no user\n"
						" |  interaction  | interaction (no questions asked).\n"
						" |_______________|\n"
						" | --output_image| Specify output image file name if image recorder is used\n"
						" |               | to avoid prompting for filename.\n"
						" |_______________|\n"
						" | --use_allspace| Use all space on the media.\n"
						" |_______________|\n"
						" | --relax_joliet| Relax Joliet file name length limitations.\n"
						" |_______________|\n"
						" | --japanese_   | CD Text is treated as Japanese CD Text (must include\n"
						" |  cd_text      | --cd_text as well).\n"
						" |_______________|\n"
						" |--disable_eject| Do not eject the RW media after erasing it.\n"
						" | _after_erase  |\n"
						" |_______________|\n"
						" | --force_eject | Force disc ejection after erasing the RW media.\n"
						" |  _after_erase |\n"
						" |_______________|\n"
						" | --system_     | <text> is the \"system identifier\" of an ISO track.\n"
						" |  identifier   |\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --volume_set  | <text> is the \"volume set\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --publisher   | <text> is the \"publisher\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --data_       | <text> is the \"data preparer\" of an ISO track.\n"
						" |preparer <text>|\n"
						" |_______________|\n"
						" | --application | <text> is the \"application\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --copyright   | <text> is the \"copyright\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --abstract    | <text> is the \"abstract\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" |--bibliographic| <text> is the \"bibliographic\" of an ISO track.\n"
						" |  <text>       |\n"
						" |_______________|\n"
						" | --backup      | Replace imported files only if newer are found.\n"
						" |_______________|\n"
						" | --booktype    | The book type of a burned DVD will be set to\n"
						" |   _dvdrom     | DVD-ROM.\n"
						" |_______________|\n"
						" | --no_booktype | Do not change the book type of a DVD even if the default\n"
						" |   _change     | setting is to change the book type to DVD-ROM.\n"
						" |_______________|\n"
						" | --estimate_no | Do not include the file system overhead in calculation.\n"
						" |   fs_overhead |\n"
						" |_______________|\n"
						" | --estimate_no | Do not include data in calculation.\n"
						" |   data        |\n"
						" |_______________|\n"
						" | --estimate_no | Do not calculate the exact size (quicker).\n"
						" |   exact_size  |\n"
						" |_______________|\n"
						" | @param_file   | param_file contains the command line arguments.\n"
						" |_______________|\n";

	// The following piece of code prints the usage screen by screen.

	int iLine;
	int iLen = strlen (psMessage);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole;

	hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo (hConsole, &csbi);
	iLine = csbi.dwCursorPosition.Y;

	while (*psMessage)
	{
		char buffer[81];
		int iToCopy;
		LPCSTR p;

		p = strchr (psMessage, '\n');
		iToCopy = (p)? p - psMessage + 1: iLen;
		iToCopy = min (sizeof (buffer) - 1, iToCopy);
		strncpy (buffer, psMessage, iToCopy);
		buffer[iToCopy] = 0;
		iLen -= iToCopy;
		psMessage += iToCopy;

		printf ("%s", buffer);

		if (++iLine == csbi.srWindow.Bottom - csbi.srWindow.Top)
		{
			printf ("-- PRESS ANY KEY TO CONTINUE LISTING OR ESCAPE TO QUIT! --");
			char ch = getch ();
			printf ("\r                                                          \r");
			if (ch == 27)
			{
				break;
			}
			iLine = 0;
		}
	}
}


// ReadParameterFile is responsible for reading and parsing the parameter list from a
// disk file. Once the parameters are parsed, they are passed on to the getopt
// function for decoding.

static bool ReadParameterFile (PARAMETERS & params, LPCSTR psFilename)
{

	FILE * fh;
	char ch;
	int iStart = -1;
	bool bStartWasQuote;
	bool bStartWasSemicolon;
	bool bLastWasBackslash = false;
	static CSimpleStringArray args;

	// Open the file in binary mode. Text mode retrieves a DOS newline
	// as 0x0A, though it really is 0x0D+0x0A, thus compromising
	// the command length calculation.

	fh = fopen (psFilename, "rb");
	if (NULL == fh)
	{
		printf ("Could not open parameter file '%s'\n", psFilename);
		return false;
	}

	// The following code parses the file into argc/argv type of arguments.

	do
	{
		ch = getc (fh);

		// Handle the start of a command or parameter string

		if (!isspace (ch) && ch != EOF && iStart == -1)
		{
			// ftell returns the current position of the file pointer
			// Here we are at start of the string.

			iStart = ftell (fh);

			// Check if a quote character was read and remember it.
			// This facilitates usage of blanks in file names.

			bStartWasQuote = ch == '"';

			// Check and remember that a comment was started
			// Comments are discarded later.

			bStartWasSemicolon = ch == ';';

			// If the string started with a quote, we don't want that,
			// so we leave the file pointer on the current position.

			if (!bStartWasQuote)
			{
				// We did not start with a quote, so lets set the 
				// start value, which is one less than the current
				// position

				iStart--;
			}
		}

		// Handle the end of comments

		else if (iStart != -1 && bStartWasSemicolon && 
						(isspace(ch) || ch == EOF))
		{
			// Comments are discarded

			if (ch == '\n')
			{
				iStart = -1;
			}

		}

		// Handle the end of a command or parameter string

		else if (iStart != -1 && ((isspace (ch) && !bStartWasQuote) ||
								(ch == '"' && bStartWasQuote) ||
								 ch == ';' || ch == EOF))
		{
			// Get the current file pointer position
			// and calculate the command string length

			int iCurPos = ftell (fh);
			int iLen = iCurPos - iStart;

			// Set the file pointer to the start of the command
			// by moving it back by iLen bytes.

			fseek (fh, -iLen, SEEK_CUR);

			// Normally getc reads a character and then moves the file
			// pointer to the next character. At the end of the input stream,
			// the file pointer cannot go beyond EOF,
			// thus we must not decrement the length in that case because we
			// would delete parts of a command string.

			if (ch != EOF)
			{
				iLen--;
			}

				// Allocate enough space for the command string and the 
				// termination character

			LPSTR p = new char [iLen + 1];
			if (!p)
			{
				printf ("Out of memory while parsing parameter file '%s'\n", psFilename);
				fclose (fh);
				return false;
			}

				// Copy the command string

			fread (p, 1, iLen, fh);
			p[iLen] = 0;

				// Return to the previous last position
				// by seting the file pointer to an absolute position

			fseek (fh, iCurPos, SEEK_SET);

				// Add the string to the string vector

			args.Add (p);


			// Make sure we discard the end of the line even
      // if there was no blank between the command
      // line parameter and a comment character ";"

      bStartWasSemicolon = ch == ';';

      // If the command was terminated by ";" we 
      // do not start another command yet.

      if (!bStartWasSemicolon)
      {
			  // Set the flag to get the next command

			  iStart = -1;
      }
		}
		else if (bLastWasBackslash && ch != EOF)
		{
			if (ch != '"' && ch != '\\')
			{
				ungetc (ch, fh);
			}

			bLastWasBackslash = false;
		}
	} while (ch != EOF);

	fclose (fh);

	char ** argv = new char*[args.vect.size ()];
	if (!argv)
	{
		printf ("Out of memory while parsing parameter file '%s'\n", psFilename);
		return false;
	}

	for (int i = 0; i < (int)(args.vect.size()); i ++)
	{
		argv[i] = args.vect[i];
	}

	bool bRet = getopt (params, args.vect.size (), argv);
	delete [] argv;

	return bRet;
}
