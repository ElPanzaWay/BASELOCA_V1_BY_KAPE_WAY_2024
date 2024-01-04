# Microsoft Developer Studio Project File - Name="ASD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ASD - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ASD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ASD.mak" CFG="ASD - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ASD - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ASD_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ASD_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x540a /d "NDEBUG"
# ADD RSC /l 0x540a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Target

# Name "ASD - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "x"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\defs.h
# End Source File
# Begin Source File

SOURCE=.\KEYDEFS.H
# End Source File
# Begin Source File

SOURCE=.\PARSEMSG.CPP
# End Source File
# Begin Source File

SOURCE=.\PARSEMSG.H
# End Source File
# Begin Source File

SOURCE=.\peb.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# Begin Source File

SOURCE=.\xorstr.h
# End Source File
# End Group
# Begin Group "math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Math\matrix3x4.h
# End Source File
# Begin Source File

SOURCE=.\Math\qangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\qangle.h
# End Source File
# Begin Source File

SOURCE=.\Math\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\vector.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\aim.cpp
# End Source File
# Begin Source File

SOURCE=.\aimutils.cpp
# End Source File
# Begin Source File

SOURCE=.\antiaim.cpp
# End Source File
# Begin Source File

SOURCE=.\asd.cpp
# End Source File
# Begin Source File

SOURCE=.\attackutils.cpp
# End Source File
# Begin Source File

SOURCE=.\autooffsets.cpp
# End Source File
# Begin Source File

SOURCE=.\client.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\CVARS.CPP
# End Source File
# Begin Source File

SOURCE=.\draw.cpp
# End Source File
# Begin Source File

SOURCE=.\drawtext.cpp
# End Source File
# Begin Source File

SOURCE=.\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\enginemsg.cpp
# End Source File
# Begin Source File

SOURCE=.\enginestudio.cpp
# End Source File
# Begin Source File

SOURCE=.\enginestudiodraw.cpp
# End Source File
# Begin Source File

SOURCE=.\ENTS.CPP
# End Source File
# Begin Source File

SOURCE=.\fireevents.cpp
# End Source File
# Begin Source File

SOURCE=.\functions.cpp
# End Source File
# Begin Source File

SOURCE=.\GUNS.CPP
# End Source File
# Begin Source File

SOURCE=.\HOOK.CPP
# End Source File
# Begin Source File

SOURCE=.\keyhandling.cpp
# End Source File
# Begin Source File

SOURCE=.\menu_nk.cpp
# End Source File
# Begin Source File

SOURCE=.\player.cpp
# End Source File
# Begin Source File

SOURCE=.\recoil.cpp
# End Source File
# Begin Source File

SOURCE=.\soundhack.cpp
# End Source File
# Begin Source File

SOURCE=.\spread.cpp
# End Source File
# Begin Source File

SOURCE=.\steamid.cpp
# End Source File
# Begin Source File

SOURCE=.\usermsg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aim.h
# End Source File
# Begin Source File

SOURCE=.\aimutils.h
# End Source File
# Begin Source File

SOURCE=.\antiaim.h
# End Source File
# Begin Source File

SOURCE=.\attackutils.h
# End Source File
# Begin Source File

SOURCE=.\autooffsets.h
# End Source File
# Begin Source File

SOURCE=.\client.h
# End Source File
# Begin Source File

SOURCE=.\client_headers.h
# End Source File
# Begin Source File

SOURCE=.\commands.h
# End Source File
# Begin Source File

SOURCE=.\CVARS.H
# End Source File
# Begin Source File

SOURCE=.\draw.h
# End Source File
# Begin Source File

SOURCE=.\drawtext.h
# End Source File
# Begin Source File

SOURCE=.\engine.h
# End Source File
# Begin Source File

SOURCE=.\enginemsg.h
# End Source File
# Begin Source File

SOURCE=.\enginestudio.h
# End Source File
# Begin Source File

SOURCE=.\enginestudiodraw.h
# End Source File
# Begin Source File

SOURCE=.\ENTS.H
# End Source File
# Begin Source File

SOURCE=.\fireevents.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\GUNS.H
# End Source File
# Begin Source File

SOURCE=.\HOOK.H
# End Source File
# Begin Source File

SOURCE=.\keyhandling.h
# End Source File
# Begin Source File

SOURCE=.\menu_nk.h
# End Source File
# Begin Source File

SOURCE=.\player.h
# End Source File
# Begin Source File

SOURCE=.\recoil.h
# End Source File
# Begin Source File

SOURCE=.\soundhack.h
# End Source File
# Begin Source File

SOURCE=.\spread.h
# End Source File
# Begin Source File

SOURCE=.\steamid.h
# End Source File
# Begin Source File

SOURCE=.\usermsg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# End Target
# End Project
