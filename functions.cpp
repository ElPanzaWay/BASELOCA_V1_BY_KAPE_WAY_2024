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

#define M_PI 3.14159265358979323846

#define INT_DIGITS 19

char native_itoa_buffer[INT_DIGITS + 2];

int native_strlen( char *pStr );
int native_strncmp( char const* _Str1 , char const* _Str2 , size_t MaxCount );

//-------------------------------------------------------------------//

char* native_strcpy( char *dest , const char *src )
{
	return lstrcpyA( dest , src );
}

char* native_strncpy( char *dest , const char *src , int n )
{
	return lstrcpynA( dest , src , n );
}

char* native_strcat( char *dest , const char *src )
{
	return lstrcatA( dest , src );
}

char* native_strstr( char *in , char *str )
{
	char c = 0;
	size_t len = 0;
	c = *str++;
	if ( !c )
		return (char *)in;
	len = native_strlen( str );
	do
	{
		char sc;

		do
		{
			sc = *in++;
			if ( !sc )
				return (char *)0;
		} while ( sc != c );
	} while ( native_strncmp( in , str , len ) != 0 );
	return (char *)( in - 1 );
}

int native_strcmp( char *pStr1 , char *pStr2 )
{
	return lstrcmpA( pStr1 , pStr2 );
}

int native_strlen( char *pStr )
{
	return lstrlenA( pStr );
}

int native_strncmp( char const* _Str1 , char const* _Str2 , size_t MaxCount )
{
	if ( !MaxCount ) return 0;
	while ( --MaxCount && *_Str1 && *_Str1 == *_Str2 )
	{
		_Str1++;
		_Str2++;
	}
	return *(unsigned char *)_Str1 - *(unsigned char *)_Str2;
}

void native_memcpy( void * dst , const void * src , size_t count )
{
	_asm
	{
		mov	edi , [dst]
		mov	esi , [src]
		mov	ecx , [count]
		rep	movsb
	}
}

void* native_memcpy2( void * dst , const void * src , size_t count )
{
	void * ret = dst;
	while ( count-- )
	{
		*(char *)dst = *(char *)src;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}
	return( ret );
}

void native_memset( void *szBuffer , DWORD dwLen , DWORD dwSym )
{
	_asm
	{
		pushad
		mov edi , [szBuffer]
		mov ecx , [dwLen]
		mov eax , [dwSym]
		rep stosb
		popad
	}
}

PCHAR native_itoa( int i )
{
	char *p = native_itoa_buffer + INT_DIGITS + 1;
	if ( i >= 0 )
	{
		do
		{
			*--p = '0' + ( i % 10 );
			i /= 10;
		} while ( i != 0 );
		return p;
	}
	else
	{
		do
		{
			*--p = '0' - ( i % 10 );
			i /= 10;
		} while ( i != 0 );
		*--p = '-';
	}
	return p;
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

float mysqrt( float x )
{
	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f375a86 - ( i >> 1 );
	x = *(float*)&i;
	x = x*( 1.5f - xhalf*x*x );
	x = x*( 1.5f - xhalf*x*x );
	x = x*( 1.5f - xhalf*x*x );
	x = 1 / x;
	return x;
}

double myatan( double x , int n )
{
	double a = 0.0;// 1st term
	double sum = 0.0;
	if ( x == 1.0 ) return M_PI / 4.0;
	if ( x == -1.0 ) return -M_PI / 4.0;
	if ( n > 0 )
	{
		if ( ( x < -1.0 ) || ( x > 1.0 ) )
		{
			if ( x > 1.0 )
				sum = M_PI / 2.0;
			else
				sum = -M_PI / 2.0;
			a = -1.0 / x;
			for ( int j = 1; j <= n; j++ )
			{
				sum += a;
				a *= -1.0*( 2.0*j - 1 ) / ( ( 2.0*j + 1 )*x*x );
			}
		}
		else
		{
			sum = 0.0;
			a = x;
			for ( int j = 1; j <= n; j++ )
			{
				sum += a;
				a *= -1.0*( 2.0*j - 1 )*x*x / ( 2.0*j + 1 );
			}
		}
	}
	return sum;
}

double myatan2( double y , double x )
{
	double u = myatan( y / x , 10 );
	if ( x < 0.0 )
	{
		if ( u > 0.0 )
			u -= M_PI;
		else
			u += M_PI;
	}
	return u;
}

double mypow( double a , double b )
{
	double c = 1;
	for ( int i = 0; i<b; i++ )
		c *= a;
	return c;
}

double myfact( double x )
{
	double ret = 1;
	for ( int i = 1; i <= x; i++ )
		ret *= i;
	return ret;
}

double mysin( double x )
{
	double y = x;
	double s = -1;
	for ( int i = 3; i <= 100; i += 2 )
	{
		y += s*( mypow( x , i ) / myfact( i ) );
		s *= -1;
	}
	return y;
}

double mycos( double x )
{
	double y = 1;
	double s = -1;
	for ( int i = 2; i <= 100; i += 2 )
	{
		y += s*( mypow( x , i ) / myfact( i ) );
		s *= -1;
	}
	return y;
}

float myfabs( float x )
{
	if ( x < 0.f )
		return -x;
	else
		return x;
}

//-------------------------------------------------------------------//
