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

/*
void HookEngineMessages()
{
	pEngineMsgBase = (PEngineMsg)offset.FindSVCMessages();

	char svc_sound_msg[] = { 's','v','c','_','s','o','u','n','d',0 };
	char svc_spawnstatic_sound_msg[] = { 's','v','c','_','s','p','a','w','n','s','t','a','t','i','c','s','o','u','n','d',0 };

	pSVC_sound = HookEngineMsg( svc_sound_msg , SVC_Sound );
	pSVC_SpawnStaticSound = HookEngineMsg( svc_spawnstatic_sound_msg , SVC_SpawnStaticSound );
}*/

//-------------------------------------------------------------------//

/*
#define MAX_CMD_LINE 1024

int* MSG_ReadCount = 0;
int* MSG_CurrentSize = 0;
int* MSG_BadRead = 0;
void* MSG_Base = 0;
int MSG_SavedReadCount = 0;

char com_token[1024];

HL_MSG_ReadByte MSG_ReadByte;
HL_MSG_ReadShort MSG_ReadShort;
HL_MSG_ReadLong MSG_ReadLong;
HL_MSG_ReadString MSG_ReadString;

HL_MSG_CBuf_AddText CBuf_AddText_Orign;

TEmptyCallback SVC_StuffText_Orign;
TEmptyCallback SVC_SendCvarValue_Orign;
TEmptyCallback SVC_SendCvarValue2_Orign;

const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

TEmptyCallback HookServerMsg(const unsigned Index, void* CallBack,AutoOffset* Offset)
{
	TEmptyCallback Call = (TEmptyCallback)Offset->SVCBase[Index]->Callback;
	Offset->SVCBase[Index]->Callback = (DWORD)CallBack;
	return Call;
}

void MSG_SaveReadCount()
{
	MSG_SavedReadCount = *MSG_ReadCount;
}

void MSG_RestoreReadCount()
{
	*MSG_ReadCount = MSG_SavedReadCount;
}

void CBuf_AddText(char* text)
{
	char str[1024];
	strncpy(str, text, sizeof(str));
	str[sizeof(str) - 1] = 0;

	if (SanitizeCommands(str,"CBuf_AddText"))
		return;

	CBuf_AddText_Orign(text);
}

void SVC_StuffText() // server send cmd
{
	MSG_SaveReadCount();
	char* commands = MSG_ReadString();

	char str[1024];
	strncpy(str, commands, sizeof(str));
	str[sizeof(str) - 1] = 0;

	if (SanitizeCommands(str, "SVC_StuffText"))
		return;

	MSG_RestoreReadCount();
	SVC_StuffText_Orign();
}

void SVC_SendCvarValue()
{
	MSG_SaveReadCount();
	char* cvar = MSG_ReadString();
	
	bool isGood = IsCvarGood(cvar);
	if (!isGood)
	{
		g_Engine.Con_Printf("\t[SVC_SendCvarValue] Server tried to request blocked cvar: %s\n", cvar);
		add_log("%s [SVC_SendCvarValue] Server tried to request blocked cvar: %s", currentDateTime().c_str(), cvar);
		return;
	}
	else
	{
		g_Engine.Con_Printf("\t[SendCvarValue] Server tried to request not blocked cvar: %s\n", cvar);
		add_log("%s [SendCvarValue] Server tried to request not blocked cvar: %s", currentDateTime().c_str(), cvar);
	}

	MSG_RestoreReadCount();	
	SVC_SendCvarValue_Orign();
}

void SVC_SendCvarValue2()
{
	MSG_SaveReadCount();
	char* cvar = MSG_ReadString();

	bool isGood = IsCvarGood(cvar);
	if (!isGood)
	{
		g_Engine.Con_Printf("\t[SendCvarValue2] Server tried to request blocked cvar: %s\n", cvar);
		add_log("%s [SendCvarValue2] Server tried to request blocked cvar: %s", currentDateTime().c_str(), cvar);
		return;
	}
	else
	{
		g_Engine.Con_Printf("\t[SendCvarValue2] Server tried to request not blocked cvar: %s\n", cvar);
		add_log("%s [SendCvarValue2] Server tried to request not blocked cvar: %s", currentDateTime().c_str(), cvar);
	}

	MSG_RestoreReadCount();	
	SVC_SendCvarValue2_Orign();
}

char ToUpper(char ch)
{
    return (char)(ch+32);
}

bool ParseListCvar(const char* str)
{
	DWORD temp = 0;
	DWORD len = strlen(str)-1;
	for(DWORD i = 0;i < _countof(blockListCvar);i++)
	{
		for(DWORD x = 0;x < len;x++)
		{
			if ( blockListCvar[i][x] == str[x] || blockListCvar[i][x] == ToUpper(str[x]) )
			{
				temp++;
				if ( temp == len )
					return true;
			}
			else temp = 0;
		}
	}
	return false;
}

bool ParseList(const char* str)
{
	DWORD temp = 0;
	DWORD len = strlen(str)-1;
	for(DWORD i = 0;i < _countof(blockList);i++)
	{
		for(DWORD x = 0;x < len;x++)
		{
			if ( blockList[i][x] == str[x] || blockList[i][x] == ToUpper(str[x]) )
			{
				temp++;
				if ( temp == len )
					return true;
			}
			else temp = 0;
		}
	}
	return false;
}

bool IsCvarGood(const char *str)
{
	if (str[0] == 0)
		return true;

	if (ParseListCvar(str))
		return false;

	return true;
}

bool IsCommandGood(const char *str)
{
	char *ret = g_Engine.COM_ParseFile((char *)str, com_token);
	if (ret == NULL || com_token[0] == 0)
		return true;
	if ((ParseList(com_token)))
		return false;
	return true;
}

bool SanitizeCommands(char *str,char* name)
{
	bool changed = false;
	char *text = str;
	char command[MAX_CMD_LINE];
	int i, quotes;
	int len = strlen(str);

	while (text[0] != 0)
	{
		quotes = 0;
		for (i = 0; i < len; i++)
		{
			if (text[i] == '\"') quotes++;
			if (!(quotes & 1) && text[i] == ';')
				break;
			if (text[i] == '\n')
				break;
			if (text[i] == 0x00)
				break;
		}
		if (i >= MAX_CMD_LINE)
			i = MAX_CMD_LINE;

		strncpy(command, text, i);
		command[i] = 0;

		bool isGood = IsCommandGood(command);

		int log = 1;
		if (log > 0)
		{
			char *c = command;
			char *a = isGood ? 	"\t[HLR] Server execute command: %s\n": "\t[HLR] Server blocked command: %s\n";
			if (isGood)
			{
				add_log("%s [%s] Server execute command: %s", currentDateTime().c_str(), name, c);
			}
			else
			{
				add_log("%s [%s] Server blocked command: %s", currentDateTime().c_str(), name, c);
			}
			g_Engine.Con_Printf(a,c);
		}
		len -= i;
		if (!isGood)
		{
			strncpy(text, text + i, len);
			text[len] = 0;
			text++;
			changed = true;
		}
		else
		{
			text += i + 1;
		}
	}
	return changed;
}*/








