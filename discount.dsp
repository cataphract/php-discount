# Microsoft Developer Studio Project File - Name="discount" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=discount - Win32 Debug_TS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "discount.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "discount.mak" CFG="discount - Win32 Debug_TS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "discount - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
RE2C=re2c.exe

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\Debug_TS"
# PROP BASE Intermediate_Dir "..\..\Debug_TS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug_TS"
# PROP Intermediate_Dir "..\..\Debug_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /D WIN32 /D _MBCS /W3 /wd4996 /D _USE_32BIT_TIME_T=1 /RTC1 /MP /LDd /MDd /W3 /Gm /Od /D _DEBUG /ZI /I"C:\Users\Cataphract_\Documents\php-src\no\include" /c
# ADD CPP /nologo /FD /I ".." /I "..\..\main" /I "..\..\Zend" /I "..\..\TSRM" /I "..\..\ext" /I "..\..\..\bindlib_w32" /D _WINDOWS /D ZEND_WIN32=1 /D PHP_WIN32=1 /D WIN32 /D _MBCS /W3 /wd4996 /D_USE_32BIT_TIME_T=1 /RTC1 /MP /LDd /MDd /W3 /Gm /Od /D _DEBUG /D ZEND_DEBUG=1 /ZI /D ZTS=1 /I "C:\Users\Cataphract_\Documents\php-src\no\include" /D FD_SETSIZE=256 /D COMPILE_DL_DISCOUNT /D DISCOUNT_EXPORTS=1 /D_WSTDIO_DEFINED /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo kernel32.lib ole32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib Dnsapi.lib
# ADD LINK32 /nologo kernel32.lib ole32.lib user32.lib advapi32.lib shell32.lib ws2_32.lib Dnsapi.lib php5ts_debug.lib  /version:5.3.99 /debug /dll  /nodefaultlib:"msvcrt"  /out:"..\..\Debug_TS\discount.dll" /libpath:"..\..\Debug_TS" /libpath:"..\..\..\bindlib_w32\Debug"

# Begin Target
# Name "discount - Win32 Debug_TS"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File
SOURCE=Csio.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount"
# End Source File

# Begin Source File
SOURCE=./lib\css.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\docheader.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\dumptree.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\emmatch.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\flags.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\generate.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\html5.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\markdown.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\mkdio.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\resource.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\tags.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\toc.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\version.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\xml.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\xmlpage.c
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./discount
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount"
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File
SOURCE=./php_discount.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount"
# End Source File

# Begin Source File
SOURCE=./lib\amalloc.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\config.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\config.win32.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\cstring.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\markdown.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\mkdio.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File

# Begin Source File
SOURCE=./lib\tags.h
# PROP Intermediate_Dir "..\..\Debug_TS\ext\discount\lib"
# End Source File


# End Group

# Begin Group "Text Files"
# PROP Default_Filter ""

# End Group


# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group
# End Target
# End Project
