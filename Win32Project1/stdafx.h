// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment ( lib, "user32.lib" ) 
#pragma comment ( lib, "comctl32.lib" ) 
#pragma comment ( lib, "winmm.lib")//to play audio
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "targetver.h"
//#include <WinSDKVer.h>
//MFC STUFF
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
//#endif
/*
#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <Winuser.h>
#include <vector>
#include <Prsht.h>
#include "iostream"
#include "string.h"
#include <math.h>
#include <ctime>//more time related stuff
#include <fstream>//for file io
#include <thread>//for threads
//#include <chrono> //for time related stuff
#include <Mmsystem.h>//to play audio
#include <commctrl.h>
#include <atlstr.h>//for some type of string
#include <io.h>
#include <fcntl.h> 
#include <commctrl.h>  //For button sytles, maybe other styles
#include <memory>//for smart pointers

// TODO: reference additional headers your program requires here
