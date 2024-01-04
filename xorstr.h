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

#pragma once

//=================================================================================================================//

#undef KEY
#undef BUFLEN

//=================================================================================================================//

template <int XORSTART, int BUFLEN, int XREFKILLER>

//=================================================================================================================//

class XorStr
{
	private: 
		 XorStr();
	public: 
		char s[BUFLEN];

		 XorStr(const char* xs);
#ifndef DEBUG_OPTION
		 ~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;} // clear string from stack
#endif
};

//=================================================================================================================//

template <int XORSTART, int BUFLEN, int XREFKILLER>

//=================================================================================================================//

XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for(;i<(BUFLEN-1);i++) {
		s[i] = xs[i-XREFKILLER]^xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN-1] = 0;
}

//=================================================================================================================//
