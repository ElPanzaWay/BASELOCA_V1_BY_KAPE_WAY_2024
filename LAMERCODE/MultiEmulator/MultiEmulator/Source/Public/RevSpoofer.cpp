///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "RevSpoofer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define astrlen(x) _countof(x) - 1

static char s_szDictionary[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

static int iInputLen;
static unsigned int uTreasure;

bool ScanLast3(char *pszInput, unsigned int uPrevHash)
{
	unsigned int h1, h2, h3, hh;
	for (unsigned int i1 = 0; i1 < /*astrlen*/strlen(s_szDictionary)-1; i1++)
	{
		h1 = uPrevHash ^ ((uPrevHash >> 2) + (uPrevHash << 5) + s_szDictionary[i1]);
		hh = h1 ^ ((h1 >> 2) + (h1 << 5));
		hh = hh ^ ((hh >> 2) + (hh << 5));

		if ((hh ^ uTreasure) >> (8 + 5 + 3))
			continue;

		for (unsigned int i2 = 0; i2 < /*astrlen*/strlen(s_szDictionary)-1; i2++)
		{
			h2 = h1 ^ ((h1 >> 2) + (h1 << 5) + s_szDictionary[i2]);
			hh = h2 ^ ((h2 >> 2) + (h2 << 5));
			if ((hh ^ uTreasure) >> (8 + 3))
				continue;

			for (unsigned int i3 = 0; i3 < /*astrlen*/strlen(s_szDictionary)-1; i3++)
			{
				h3 = h2 ^ ((h2 >> 2) + (h2 << 5) + s_szDictionary[i3]);
				if (h3 == uTreasure)
				{
					pszInput[iInputLen - 3] = s_szDictionary[i1];
					pszInput[iInputLen - 2] = s_szDictionary[i2];
					pszInput[iInputLen - 1] = s_szDictionary[i3];
					return true;
				}
			}
		}
	}
	return false;
}

bool ScanNext(char* pszInput, int uIndex, unsigned int uPrevHash)
{
	bool res;

	for (unsigned int i = 0; i < /*astrlen*/strlen(s_szDictionary)-1; i++)
	{
		auto h = uPrevHash ^ ((uPrevHash >> 2) + (uPrevHash << 5) + s_szDictionary[i]);

		if (uIndex + 1 < iInputLen - 3)
			res = ScanNext(pszInput, uIndex + 1, h);
		else
			res = ScanLast3(pszInput, h);

		if (res)
		{
			pszInput[uIndex] = s_szDictionary[i];
			return true;
		}
	}
	return false;
}

namespace RevSpoofer
{
	bool Spoof(char *pszDest, int uSID)
	{
		uTreasure = uSID;
		iInputLen = strlen(pszDest);

		auto i = iInputLen - 7;
		i = (i < 0) ? 0 : i;
		pszDest[i] = '\0';
		auto h = Hash(pszDest);
		return ScanNext(pszDest, i, h);
	}

	unsigned int Hash(char *pszString)
	{
		int i = 0;
		unsigned int nHash = 0x4E67C6A7;
		int c = pszString[i++];

		while (c)
		{
			nHash = nHash ^ ((nHash >> 2) + (nHash << 5) + c);
			c = pszString[i++];
		}

		return nHash;
	}
}