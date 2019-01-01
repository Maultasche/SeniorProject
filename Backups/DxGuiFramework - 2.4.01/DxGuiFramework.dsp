# Microsoft Developer Studio Project File - Name="DxGuiFramework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

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
!MESSAGE "DxGuiFramework - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DxGuiFramework - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
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
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

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
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib dxguid.lib ddraw.lib /nologo /subsystem:windows /profile /debug /machine:I386

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

SOURCE=.\DGSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\DGWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\DxGuiFramework.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
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
# Begin Group "Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\Programming\DXSdk\lib\dxguid.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\DXSdk\lib\ddraw.lib
# End Source File
# End Group
# End Target
# End Project
