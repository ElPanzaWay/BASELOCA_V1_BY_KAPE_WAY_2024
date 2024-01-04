//-----------------------------------------------------------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
//
//-----------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------------------------------------------------------------------------------

class QAngle;
class NewVector;

//-----------------------------------------------------------------------------------------------------------------------------------------------------

typedef float vec_t;

//-----------------------------------------------------------------------------------------------------------------------------------------------------

class NewVector2D
{
public:
	inline NewVector2D(void) { }
	inline NewVector2D(float X, float Y) { x = X; y = Y; }
	inline NewVector2D operator+(const NewVector2D& v)	const { return NewVector2D(x + v.x, y + v.y); }
	inline NewVector2D operator-(const NewVector2D& v)	const { return NewVector2D(x - v.x, y - v.y); }
	inline NewVector2D operator*(float fl)				const { return NewVector2D(x*fl, y*fl); }
	inline NewVector2D operator/(float fl)				const { return NewVector2D(x / fl, y / fl); }

	inline float Length(void)						const { return (float)sqrt(x*x + y * y); }

	inline NewVector2D Normalize(void) const
	{
		NewVector2D vec2;

		float flLen = Length();
		if (flLen == 0)
		{
			return NewVector2D((float)0, (float)0);
		}
		else
		{
			flLen = 1 / flLen;
			return NewVector2D(x * flLen, y * flLen);
		}
	}

	inline float DotProduct(const NewVector2D a, const NewVector2D b) { return(a.x * b.x + a.y * b.y); }

	vec_t	x, y;
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------

class NewVector
{
	public:

		NewVector::NewVector ( void ) : x ( 0.0f ), y ( 0.0f ), z ( 0.0f )
		{

		}

		NewVector::NewVector ( float X, float Y, float Z )
		: x ( X ), y ( Y ), z ( Z )
		{

		}

		NewVector::NewVector ( float* p )
		{
			*this = p;
		};

		NewVector::NewVector ( const NewVector& in )
		{
			x = in.x;
			y = in.y;
			z = in.z;
		};

		NewVector::~NewVector ()
		{

		}

		inline NewVector& operator= ( const NewVector& in );
		inline NewVector& operator= ( float* p );
		inline NewVector& operator= ( float f );
		
		inline float& operator[] ( int i ) const;
		
		inline bool operator! ( void ) const;
		
		inline bool operator== ( const NewVector& other ) const;

		inline bool operator!= ( const NewVector& other ) const;

		inline NewVector& operator+= ( const NewVector& other );
		inline NewVector& operator+= ( float* p );
		inline NewVector& operator+= ( float f );

		inline NewVector& operator-= ( const NewVector& other );
		inline NewVector& operator-= ( float* p );
		inline NewVector& operator-= ( float f );
		
		inline NewVector& operator*= ( const NewVector& other );
		inline NewVector& operator*= ( float *p );
		inline NewVector& operator*= ( float f );
		
		inline NewVector& operator/= ( const NewVector& other );
		inline NewVector& operator/= ( float* p );
		inline NewVector& operator/= ( float f );
		
		inline NewVector operator+ ( const NewVector& other ) const;
		inline NewVector operator+ ( float* p ) const;
		inline NewVector operator+ ( float f ) const;
		
		inline NewVector operator- ( const NewVector& other ) const;
		inline NewVector operator- ( float* p ) const;
		inline NewVector operator- ( float f ) const;
		inline NewVector operator- ( void ) const;
		
		inline NewVector operator* ( const NewVector& other ) const;
		inline NewVector operator* ( float* p ) const;
		inline NewVector operator* ( float f ) const;
		
		inline NewVector operator/ ( const NewVector& other ) const;
		inline NewVector operator/ ( float* p ) const;
		inline NewVector operator/ ( float f ) const;

		operator float *()								{ return &x; }
		operator const float *() const					{ return &x; }
		
		inline bool NewVector::IsZero ( void ) const
		{
			return x == 0.0f && y == 0.0f && z == 0.0f;
		}

		inline bool NewVector::IsZero2D ( void )
		{
			return x == 0.0f && y == 0.0f;
		}

		inline NewVector& Clear ( void )
		{
			x = y = z = 0;
						
			return *this;
		}
		
		inline NewVector& Init ( float X, float Y, float Z )
		{
			x = X;
			y = Y;
			z = Z;

			return *this;
		}

		inline NewVector& Init ( float* p )
		{
			*this = p;

			return *this;
		}

		inline NewVector& Negate ( void )
		{
			x = -x;
			y = -y;
			z = -z;

			return *this;
		}

		inline float Dot ( const NewVector& other )
		{
			return x*other.x + y*other.y + z*other.z;
		}

		inline float Dot2D ( const NewVector& other )
		{
			return x*other.x + y*other.y;
		}

		inline float Length ( void )
		{
			float Length = 0;

			Length = sqrt ( LengthSqr() );
	
			return Length;
		}

		inline float Length2D ( void )
		{
			float Length = 0;

			Length = sqrt ( LengthSqr2D() );
	
			return Length;
		}

		inline float LengthSqr ( void )
		{
			return x*x + y*y + z*z;
		}

		inline float LengthSqr2D ( void )
		{
			return x*x + y*y;
		}

		inline float Distance ( NewVector& ToVector )
		{
			return ( ToVector - *this ).Length();
		}

		inline float Distance2D ( NewVector& ToVector )
		{
			return ( ToVector - *this ).Length2D();
		}

		inline float Normalize ( void )
		{
			float RecipLength, VectorLength;

			VectorLength = Length();

			if ( VectorLength != 0 )
			{
				RecipLength = 1 / VectorLength;

				x *= RecipLength;
				y *= RecipLength;
				z *= RecipLength;
			}

			return VectorLength;
		}

		inline NewVector Normalized(void)
		{
			float flLen = Length();
			if (flLen == 0) return NewVector(0, 0, 1);
			flLen = 1 / flLen;
			return NewVector(x * flLen, y * flLen, z * flLen);
		}

		inline float Normalize2D ( void )
		{
			float Length = LengthSqr2D();
			float RecipLength;

			if ( Length != 0 )
			{
				RecipLength = 1 / Length;

				x *= RecipLength;
				y *= RecipLength;
			}

			return Length;
		}

		inline float AngleBetween ( NewVector& other )
		{
			other.Normalize();
			Normalize();

			return acos ( Dot ( other ) ) * static_cast<float>(180.0 / M_PI);
		}

		NewVector &CrossProduct ( const NewVector& a, const NewVector& b )
		{
			x = ( a.y * b.z ) - ( a.z * b.y );
			y = ( a.z * b.x ) - ( a.x * b.z );
			z = ( a.x * b.y ) - ( a.y * b.x );

			return *this;
		}
		QAngle ToEulerAngles();
		QAngle ToEulerAngles ( NewVector* PseudoUp );
		void AngleMatrix ( QAngle& Rotation, float ( *matrix )[3] );
		void VectorRotate ( NewVector& In, QAngle& Rotation );

		void VectorVectors ( NewVector& Right, NewVector& Up )
		{
			NewVector tmp;

			if ( x == 0 && y == 0)
			{
				Right[0] = 1;	
				Right[1] = 0; 
				Right[2] = 0;
				Up[0] = -z; 
				Up[1] = 0; 
				Up[2] = 0;
				return;
			}

			tmp[0] = 0; tmp[1] = 0; tmp[2] = 1.0;
			CrossProduct( tmp, Right );
			Right.Normalize();
			Right.CrossProduct( *this, Up );
			Up.Normalize();
		}

		inline bool IsValid()
		{
		//	return isfinite ( x ) && isfinite( y ) && isfinite( z );
			return _finite( x ) && _finite( y ) && _finite( z );
		}

	public:

		float x, y, z;
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator= ( const NewVector& in )
{
	x = in.x;
	y = in.y;
	z = in.z;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator= ( float* p )
{
	if ( p )
	{
		x = p[0]; y = p[1]; z = p[2];
	}
	else
	{
		x = y = z = 0;
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator= ( float f )
{
	x = y = z = f;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline float &NewVector::operator[] ( int i ) const
{
	if ( i >= 0 && i < 3 )
	{
		return ( ( float* )this )[i];
	}

	return ( ( float* )this )[0];
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline bool NewVector::operator! ( void ) const
{
	return IsZero();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline bool NewVector::operator== ( const NewVector& other ) const
{
	return x == other.x && y == other.y && z == other.z;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline bool NewVector::operator!= ( const NewVector& other ) const
{
	return x != other.x || y != other.y || z != other.z;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator+= ( const NewVector& other )
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator+= ( float* p )
{
	x += p[0];
	y += p[1];
	z += p[2];

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator+= ( float f )
{
	x += f;
	y += f;
	z += f;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator-= ( const NewVector& other )
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator-= ( float* p )
{
	x -= p[0];
	y -= p[1];
	z -= p[2];

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator-= ( float f )
{
	x -= f;
	y -= f;
	z -= f;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator*= ( const NewVector& other )
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator*= ( float *p )
{
	x *= p[0];
	y *= p[1];
	z *= p[2];

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator*= ( float f )
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator/= ( const NewVector& other )
{
	if ( other.x != 0 && other.y != 0 && other.z != 0 )
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator/= ( float* p )
{
	if ( p[0] != 0 && p[1] != 0 && p[2] != 0 )
	{
		x /= p[0];
		y /= p[1];
		z /= p[2];
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector& NewVector::operator/= ( float f )
{
	if ( f != 0 )
	{
		x /= f;
		y /= f;
		z /= f;
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator+ ( const NewVector& other ) const
{
	return NewVector ( x + other.x, y + other.y, z + other.z );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator+ ( float* p ) const
{
	return NewVector ( x + p[0], y + p[1], z + p[2] );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator+ ( float f ) const
{
	return NewVector ( x + f, y + f, z + f );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector  NewVector::operator- ( const NewVector& other ) const
{
	return NewVector ( x - other.x, y - other.y, z - other.z );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector  NewVector::operator- ( float* p ) const
{
	return NewVector ( x - p[0], y - p[1], z - p[2] );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector  NewVector::operator- ( float f ) const
{
	return NewVector ( x - f, y - f, z - f );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator- ( void ) const
{
	return NewVector ( -x, -y, -z );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator* ( const NewVector& other ) const
{
	return NewVector ( x * other.x, y * other.y, z * other.z );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator* ( float* p ) const
{
	return NewVector ( x * p[0], y * p[1], z * p[2] );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator* ( float f ) const
{
	return NewVector ( x * f, y * f, z * f );
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator/ ( const NewVector& other ) const
{
	if ( other.x != 0 && other.y != 0 && other.z != 0 )
	{
		return NewVector ( x / other.x, y / other.y, z / other.z );
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator/ ( float* p ) const
{
	if ( p[0] != 0 && p[1] != 0 && p[2] != 0 )
	{
		return NewVector ( x / p[0], y / p[1], z / p[2] );
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector NewVector::operator/ ( float f ) const
{
	if ( f != 0 )
	{
		return NewVector ( x / f, y / f, z / f );
	}

	return *this;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

inline NewVector operator*(float fl, const NewVector& v)	{ return v * fl; };

//-----------------------------------------------------------------------------------------------------------------------------------------------------

//#define vec3_t NewVector

//-----------------------------------------------------------------------------------------------------------------------------------------------------




