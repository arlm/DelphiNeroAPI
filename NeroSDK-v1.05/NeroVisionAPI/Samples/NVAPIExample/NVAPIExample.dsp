# Microsoft Developer Studio Project File - Name="NVAPIExample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NVAPIExample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NVAPIExample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NVAPIExample.mak" CFG="NVAPIExample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NVAPIExample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NVAPIExample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NVAPIExample - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\..\..\NeroAPI\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x81a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x81a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 NeroAPIGlue.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\..\NeroAPI\Lib"

!ELSEIF  "$(CFG)" == "NVAPIExample - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\NeroAPI\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x81a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x81a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 NeroAPIGlue.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"msvcrtd.lib" /pdbtype:sept /libpath:"..\..\..\NeroAPI\Lib"

!ENDIF 

# Begin Target

# Name "NVAPIExample - Win32 Release"
# Name "NVAPIExample - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\EstimateDoneDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EstimatingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NVAPIExample.cpp
# End Source File
# Begin Source File

SOURCE=.\NVAPIExample.rc
# End Source File
# Begin Source File

SOURCE=.\NVAPIExampleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PageFirst.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSecond.cpp
# End Source File
# Begin Source File

SOURCE=.\PageThird.cpp
# End Source File
# Begin Source File

SOURCE=.\RecorderComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeedComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EstimateDoneDlg.h
# End Source File
# Begin Source File

SOURCE=.\EstimatingDlg.h
# End Source File
# Begin Source File

SOURCE=.\NVAPIExample.h
# End Source File
# Begin Source File

SOURCE=.\NVAPIExampleDlg.h
# End Source File
# Begin Source File

SOURCE=.\Page.h
# End Source File
# Begin Source File

SOURCE=.\PageData.h
# End Source File
# Begin Source File

SOURCE=.\PageFirst.h
# End Source File
# Begin Source File

SOURCE=.\PageSecond.h
# End Source File
# Begin Source File

SOURCE=.\PageThird.h
# End Source File
# Begin Source File

SOURCE=.\RecorderComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Sheet.h
# End Source File
# Begin Source File

SOURCE=.\SpeedComboBox.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\main.ico
# End Source File
# Begin Source File

SOURCE=.\res\NVAPIExample.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
