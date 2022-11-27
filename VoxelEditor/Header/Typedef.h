#pragma

#ifdef UNICODE
typedef wchar_t				tchar;
#else
typedef char				tchar;
#endif

typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef unsigned short		word;
typedef unsigned long		dword;

typedef D3DXVECTOR2			vec2;
typedef D3DXVECTOR3			vec3;
typedef D3DXVECTOR4			vec4;
typedef D3DXMATRIX			matrix;