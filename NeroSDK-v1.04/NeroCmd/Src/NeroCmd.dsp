# Microsoft Developer Studio Project File - Name="NeroCmd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=NeroCmd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NeroCmd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NeroCmd.mak" CFG="NeroCmd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NeroCmd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "NeroCmd - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NeroCmd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\NeroAPI\Include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX"Stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 NeroAPIGlue.lib /nologo /subsystem:console /machine:I386 /libpath:"..\..\NeroAPI\Lib"

!ELSEIF  "$(CFG)" == "NeroCmd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\NeroAPI\Include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX"Stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 NeroAPIGlue.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"msvcrtd.lib" /pdbtype:sept /libpath:"..\..\NeroAPI\Lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "NeroCmd - Win32 Release"
# Name "NeroCmd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbortedCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\AddLogLineCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\BurnContext.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandCDInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandDriveInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandEject.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandErase.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandGetSpeeds.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandImageInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandListDrives.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandListFormats.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandRead.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DisableAbortCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=.\ExitCode.cpp
# End Source File
# Begin Source File

SOURCE=.\ExitCodeTranslator.cpp
# End Source File
# Begin Source File

SOURCE=.\FindFile.cpp
# End Source File
# Begin Source File

SOURCE=.\getopt.cpp
# End Source File
# Begin Source File

SOURCE=.\IdleCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCallbacks.cpp
# End Source File
# Begin Source File

SOURCE=.\IsoTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\NeroCMD.cpp
# End Source File
# Begin Source File

SOURCE=.\parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\Response.cpp
# End Source File
# Begin Source File

SOURCE=.\SetMajorPhaseCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPhaseCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"Stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UserDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\version.rc
# End Source File
# Begin Source File

SOURCE=.\WriteFreestyle.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteImage.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteIsoAudio.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteNeroErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteVideoCD.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BurnContext.h
# End Source File
# Begin Source File

SOURCE=.\ErrorLog.h
# End Source File
# Begin Source File

SOURCE=.\ExitCode.h
# End Source File
# Begin Source File

SOURCE=.\FindFile.h
# End Source File
# Begin Source File

SOURCE=.\getopt.h
# End Source File
# Begin Source File

SOURCE=.\NeroProgress.h
# End Source File
# Begin Source File

SOURCE=.\parameters.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Response.h
# End Source File
# Begin Source File

SOURCE=.\SimpleStringArray.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
