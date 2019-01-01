# Microsoft Developer Studio Project File - Name="DxGuiFramework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DxGuiFramework - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DxGuiFramework.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DxGuiFramework.mak" CFG="DxGuiFramework - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DxGuiFramework - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DxGuiFramework - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DxGuiFramework - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DxGuiFramework - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "DxGuiFramework - Win32 Release"
# Name "DxGuiFramework - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DGApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\DGBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\DGBitmapList.cpp
# End Source File
# Begin Source File

SOURCE=.\DGColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DGDebugLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DGDisplayModeList.cpp
# End Source File
# Begin Source File

SOURCE=.\DGFont.cpp
# End Source File
# Begin Source File

SOURCE=.\DGGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\DGGui.cpp
# End Source File
# Begin Source File

SOURCE=.\DGInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DGMainWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\DGMessageLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DGSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\DGWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\DxGuiFramework.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DGApplication.h
# End Source File
# Begin Source File

SOURCE=.\DGBitmap.h
# End Source File
# Begin Source File

SOURCE=.\DGBitmapList.h
# End Source File
# Begin Source File

SOURCE=.\DGColor.h
# End Source File
# Begin Source File

SOURCE=.\DGDebugLog.h
# End Source File
# Begin Source File

SOURCE=.\DGDisplayModeList.h
# End Source File
# Begin Source File

SOURCE=.\DGException.h
# End Source File
# Begin Source File

SOURCE=.\DGFont.h
# End Source File
# Begin Source File

SOURCE=.\DGGraphics.h
# End Source File
# Begin Source File

SOURCE=.\DGGui.h
# End Source File
# Begin Source File

SOURCE=.\DGInput.h
# End Source File
# Begin Source File

SOURCE=.\DGLinkedList.h
# End Source File
# Begin Source File

SOURCE=.\DGMainWindow.h
# End Source File
# Begin Source File

SOURCE=.\DGMessage.h
# End Source File
# Begin Source File

SOURCE=.\DGMessageLog.h
# End Source File
# Begin Source File

SOURCE=.\DGQueue.h
# End Source File
# Begin Source File

SOURCE=.\DGSimpleClasses.h
# End Source File
# Begin Source File

SOURCE=.\DGSurface.h
# End Source File
# Begin Source File

SOURCE=.\DGWindow.h
# End Source File
# Begin Source File

SOURCE=.\DxGuiFramework.h
# End Source File
# Begin Source File

SOURCE=.\DxGuiGlobals.h
# End Source File
# End Group
# End Target
# End Project
