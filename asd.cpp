///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BASELOCA V1 By WAY TEAM
//
// By Kape Way , (2024)
//
// Credits: Russian bases, OGC and Kyros Base code and ideas, gamedeception guys, unknowncheats.me, and VALVE!
//
// Tested on latest Steam CS version (Jan2024), beta versions, non-steam v43, maybe others
// https://way-team-cs.blogspot.com/
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "client_headers.h"

//-------------------------------------------------------------------//

#define MAX_PATH_ARRAY_SIZE 400

char ogcdir[400] = "\0";
char hldir[400] = "\0";

//-------------------------------------------------------------------//

bool FileExists(const char* filename)
{
	WIN32_FIND_DATA finddata;
	HANDLE handle = FindFirstFile(filename,&finddata);
	return (handle!=INVALID_HANDLE_VALUE);
}

//-------------------------------------------------------------------//

static void removeFileName(char* path)
{
	char* pos = path+strlen(path); while(pos>=path && *pos!='\\') --pos; pos[1]=0; 
}

//-------------------------------------------------------------------//

const char* getOgcDirFile(const char* basename)
{
	if(strstr(basename, (const char*)/*..\0*/XorStr<0x14,4,0xEE011F42>("\x3A\x3B\x16"+0xEE011F42).s))
	{ 
		return ":*?\\/<>\"\0"; 
	}

	static char ret[400] = "\0";
	ret[0] = 0;
	memset(ret,0,sizeof(ret));
	strcpy(ret,ogcdir);
	
	return strcat(ret,basename);
}

//-------------------------------------------------------------------//

void logme1(const char *fmt, ... )
{ 	
	va_list va_alist;
	char buf[256]="\0";

	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);

	ofstream fout; 

	char filepath1[MAX_PATH_ARRAY_SIZE] = "\0";

	strcpy(filepath1, getOgcDirFile("offsets.txt\0"));

	fout.open(filepath1, ios::app); 
	fout << buf << endl; 
	fout.close(); // save & close file		
}

//-------------------------------------------------------------------//

#pragma comment(lib,"winmm.lib")
#include <lm.h>
#pragma comment(lib, "netapi32.lib")

//#include <strsafe.h>
#include <wininet.h>
#include <Urlmon.h>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "Urlmon.lib")
//#pragma comment(lib, "user32.lib")
//#pragma link "$(BCB)\\lib\\PSDK\\Urlmon.lib"
//#pragma link "$(BCB)\\lib\\PSDK\\Wininet.lib"

#include <WinInet.h>
SYSTEMTIME GetServerTime()
{
 	// Clear output buffer
 	SYSTEMTIME sysTime;
 	ZeroMemory(&sysTime, sizeof(SYSTEMTIME));

 	// Open connection
 	HINTERNET hInternetSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
 	if (!hInternetSession) 
 		return sysTime;

 	HINTERNET hInternetFile = InternetOpenUrl(hInternetSession, 
		
		/*https://www.google.com/\0*/XorStr<0xB9,25,0xE26D9FC0>("\xD1\xCE\xCF\xCC\xCE\x84\x90\xEF\xB6\xB5\xB4\xEA\xA2\xA9\xA8\xAF\xA5\xAF\xE5\xAF\xA2\xA3\xE0\xD0"+0xE26D9FC0).s
		
		, 0, 0,INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);

	if (!hInternetFile)
  	{
		InternetCloseHandle(hInternetSession);
   		return sysTime;
 	}

 	// Query date time in format systemtime
 	DWORD dwSize = sizeof(SYSTEMTIME);
 	if (!HttpQueryInfo(hInternetFile, HTTP_QUERY_DATE | 
 	HTTP_QUERY_FLAG_SYSTEMTIME, &sysTime, &dwSize, NULL))
	{
 		InternetCloseHandle(hInternetSession);
 		InternetCloseHandle(hInternetFile);
 		return sysTime;
	}

	// Clean up ...
 	InternetCloseHandle(hInternetFile);
 	InternetCloseHandle(hInternetSession);
	return sysTime;
}

//-------------------------------------------------------------------//

DWORD WINAPI StartThread(LPVOID lpParam)
{
	while(!GetModuleHandleA(/*vgui2.dll\0*/XorStr<0xE7,11,0xEF566BBA>("\x91\x8F\x9C\x83\xD9\xC2\x89\x82\x83\xF0"+0xEF566BBA).s)) 
		
		Sleep(1000);

	SYSTEMTIME theTime2 = GetServerTime();
	if(theTime2.wYear==2024)
	{
		if(theTime2.wMonth==1)
		{
	LoadHack();
		}
	}

	return 0;
}

//-------------------------------------------------------------------//


bool WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason==DLL_PROCESS_ATTACH) 
	{

//	MessageBox(0,0,0,0);

		GetModuleFileName(hinstDLL, ogcdir, MAX_PATH_ARRAY_SIZE);
		char* pos = ogcdir+strlen(ogcdir);
		while(pos>=ogcdir && *pos!='\\') --pos;
		pos[1]=0;

		GetModuleFileName(NULL, hldir, MAX_PATH_ARRAY_SIZE);
		char* pos1 = hldir+strlen(hldir);
		while(pos1>=hldir && *pos1!='\\') --pos1;
		pos1[1]=0;

		SYSTEMTIME theTime;
		GetLocalTime(&theTime);
		if(theTime.wYear==2024)
		{

			if(theTime.wMonth==1)
			{

			//	SYSTEMTIME theTime2 = GetServerTime();
			//	if(theTime2.wYear==2024)
				{
			//		if(theTime2.wMonth==1)
					{

		CloseHandle(CreateRemoteThread( GetCurrentProcess(), NULL, NULL, 
			(LPTHREAD_START_ROUTINE)StartThread, NULL, NULL, NULL ));

					}

				}
			}
		}

	}
	else if(fdwReason == DLL_PROCESS_DETACH)
	{
	}
	else if(fdwReason == DLL_THREAD_ATTACH||fdwReason == DLL_THREAD_DETACH)
	{
	}

	return (true);
}

//-------------------------------------------------------------------//







































