#include "Zipper.h"

#include <zlib/zlib.h>
#include <zlib/zconf.h>


//////////////////////////////////////////////////////////////////////////
/// crypt.h

#define CRC32(c, b) ((*(pcrc_32_tab+(((int)(c) ^ (b)) & 0xff))) ^ ((c) >> 8))

static int decrypt_byte( unsigned long * pkeys, const z_crc_t * pcrc_32_tab )
{
    unsigned temp;  /* POTENTIAL BUG:  temp*(temp^1) may overflow in an
                     * unpredictable manner on 16-bit systems; not a problem
                     * with any known compiler so far, though */

    temp = ( ( unsigned )( *( pkeys + 2 ) ) & 0xffff ) | 2;
    return ( int )( ( ( temp * ( temp ^ 1 ) ) >> 8 ) & 0xff );
}

static int update_keys( unsigned long * pkeys, const z_crc_t * pcrc_32_tab, int c )
{
    ( *( pkeys + 0 ) ) = CRC32( ( *( pkeys + 0 ) ), c );
    ( *( pkeys + 1 ) ) += ( *( pkeys + 0 ) ) & 0xff;
    ( *( pkeys + 1 ) ) = ( *( pkeys + 1 ) ) * 134775813L + 1;
    {
        int keyshift = ( int )( ( *( pkeys + 1 ) ) >> 24 );
        ( *( pkeys + 2 ) ) = CRC32( ( *( pkeys + 2 ) ), keyshift );
    }
    return c;
}

static void init_keys( const char * passwd, unsigned long * pkeys, const z_crc_t * pcrc_32_tab )
{
    *( pkeys + 0 ) = 305419896L;
    *( pkeys + 1 ) = 591751049L;
    *( pkeys + 2 ) = 878082192L;
    while( *passwd != '\0' )
    {
        update_keys( pkeys, pcrc_32_tab, ( int )*passwd );
        passwd++;
    }
}

#define zdecode(pkeys,pcrc_32_tab,c) \
    (update_keys(pkeys,pcrc_32_tab,c ^= decrypt_byte(pkeys,pcrc_32_tab)))

#define zencode(pkeys,pcrc_32_tab,c,t) \
    (t=decrypt_byte(pkeys,pcrc_32_tab), update_keys(pkeys,pcrc_32_tab,c), t^(c))

#define RAND_HEAD_LEN  12
/* "last resort" source for second part of crypt seed pattern */
#  ifndef ZCR_SEED2
#    define ZCR_SEED2 3141592654UL     /* use PI as default pattern */
#  endif

static int crypthead( const char * passwd,      /* password string */
                      unsigned char * buf,      /* where to write header */
                      int bufSize,
                      unsigned long * pkeys,
                      const z_crc_t * pcrc_32_tab,
                      unsigned long crcForCrypting )
{
    int n;                       /* index in random header */
    int t;                       /* temporary */
    int c;                       /* random byte */
    unsigned char header[RAND_HEAD_LEN - 2]; /* random header */
    static unsigned calls = 0;   /* ensure different random header each time */

    if( bufSize < RAND_HEAD_LEN )
        return 0;

    /* First generate RAND_HEAD_LEN-2 random bytes. We encrypt the
     * output of rand() to get less predictability, since rand() is
     * often poorly implemented.
     */
    if( ++calls == 1 )
    {
        srand( ( unsigned )( time( nullptr ) ^ ZCR_SEED2 ) );
    }
    init_keys( passwd, pkeys, pcrc_32_tab );
    for( n = 0; n < RAND_HEAD_LEN - 2; n++ )
    {
        c = ( rand() >> 7 ) & 0xff;
        header[n] = ( unsigned char )zencode( pkeys, pcrc_32_tab, c, t );
    }
    /* Encrypt random header (last two bytes is high word of crc) */
    init_keys( passwd, pkeys, pcrc_32_tab );
    for( n = 0; n < RAND_HEAD_LEN - 2; n++ )
    {
        buf[n] = ( unsigned char )zencode( pkeys, pcrc_32_tab, header[n], t );
    }
    buf[n++] = ( unsigned char )zencode( pkeys, pcrc_32_tab, ( int )( crcForCrypting >> 16 ) & 0xff, t );
    buf[n++] = ( unsigned char )zencode( pkeys, pcrc_32_tab, ( int )( crcForCrypting >> 24 ) & 0xff, t );
    return n;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// ioapi.h

#if (!defined(_WIN32)) && (!defined(WIN32)) && (!defined(__APPLE__))

// Linux needs this to support file operation on files larger then 4+GB
// But might need better if/def to select just the platforms that needs them.

#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifndef _FILE_OFFSET_BIT
#define _FILE_OFFSET_BIT 64
#endif

#endif

#include <stdio.h>
#include <stdlib.h>

#if defined(USE_FILE32API)
#define fopen64 fopen
#define ftello64 ftell
#define fseeko64 fseek
#else
#ifdef __FreeBSD__
#define fopen64 fopen
#define ftello64 ftello
#define fseeko64 fseeko
#endif
#ifdef _MSC_VER
#define fopen64 fopen
#if (_MSC_VER >= 1400) && (!(defined(NO_MSCVER_FILE64_FUNC)))
#define ftello64 _ftelli64
#define fseeko64 _fseeki64
#else // old MSC
#define ftello64 ftell
#define fseeko64 fseek
#endif
#endif
#endif

/*
#ifndef ZPOS64_T
#ifdef _WIN32
            #define ZPOS64_T fpos_t
#else
#include <stdint.h>
#define ZPOS64_T uint64_t
#endif
#endif
*/

#ifdef HAVE_MINIZIP64_CONF_H
#include "mz64conf.h"
#endif

#ifdef HAVE_64BIT_INT_CUSTOM
typedef  64BIT_INT_CUSTOM_TYPE ZPOS64_T;
#else
#ifdef HAS_STDINT_H
#include "stdint.h"
typedef uint64_t ZPOS64_T;
#else

/* Maximum unsigned 32-bit value used as placeholder for zip64 */
#define MAXU32 0xffffffff

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 ZPOS64_T;
#else
typedef unsigned long long int ZPOS64_T;
#endif
#endif
#endif

#define ZLIB_FILEFUNC_SEEK_CUR (1)
#define ZLIB_FILEFUNC_SEEK_END (2)
#define ZLIB_FILEFUNC_SEEK_SET (0)

#define ZLIB_FILEFUNC_MODE_READ      (1)
#define ZLIB_FILEFUNC_MODE_WRITE     (2)
#define ZLIB_FILEFUNC_MODE_READWRITEFILTER (3)

#define ZLIB_FILEFUNC_MODE_EXISTING (4)
#define ZLIB_FILEFUNC_MODE_CREATE   (8)


#ifndef ZCALLBACK
#if (defined(WIN32) || defined(_WIN32) || defined (WINDOWS) || defined (_WINDOWS)) && defined(CALLBACK) && defined (USEWINDOWS_CALLBACK)
#define CALLBACK
#else
#define ZCALLBACK
#endif
#endif

typedef voidpf( * open_file_func )      OF( ( voidpf opaque, const char * filename, int mode ) );
typedef uLong( * read_file_func )      OF( ( voidpf opaque, voidpf stream, void * buf, uLong size ) );
typedef uLong( * write_file_func )     OF( ( voidpf opaque, voidpf stream, const void * buf, uLong size ) );
typedef int( * close_file_func )     OF( ( voidpf opaque, voidpf stream ) );
typedef int( * testerror_file_func ) OF( ( voidpf opaque, voidpf stream ) );

typedef long( * tell_file_func )      OF( ( voidpf opaque, voidpf stream ) );
typedef long( * seek_file_func )      OF( ( voidpf opaque, voidpf stream, uLong offset, int origin ) );

typedef struct zlib_filefunc_def_s
{
    open_file_func      zopen_file;
    read_file_func      zread_file;
    write_file_func     zwrite_file;
    tell_file_func      ztell_file;
    seek_file_func      zseek_file;
    close_file_func     zclose_file;
    testerror_file_func zerror_file;
    voidpf              opaque;
} zlib_filefunc_def;

typedef ZPOS64_T( * tell64_file_func )    OF( ( voidpf opaque, voidpf stream ) );
typedef long( * seek64_file_func )    OF( ( voidpf opaque, voidpf stream, ZPOS64_T offset, int origin ) );
typedef voidpf( * open64_file_func )    OF( ( voidpf opaque, const void * filename, int mode ) );

typedef struct zlib_filefunc64_def_s
{
    open64_file_func    zopen64_file;
    read_file_func      zread_file;
    write_file_func     zwrite_file;
    tell64_file_func    ztell64_file;
    seek64_file_func    zseek64_file;
    close_file_func     zclose_file;
    testerror_file_func zerror_file;
    voidpf              opaque;
} zlib_filefunc64_def;

void fill_fopen64_filefunc OF( ( zlib_filefunc64_def * pzlib_filefunc_def ) );
void fill_fopen_filefunc OF( ( zlib_filefunc_def * pzlib_filefunc_def ) );

typedef struct zlib_filefunc64_32_def_s
{
    zlib_filefunc64_def zfile_func64;
    open_file_func      zopen32_file;
    tell_file_func      ztell32_file;
    seek_file_func      zseek32_file;
} zlib_filefunc64_32_def;


#define ZREAD64(filefunc,filestream,buf,size)     ((*((filefunc).zfile_func64.zread_file))   ((filefunc).zfile_func64.opaque,filestream,buf,size))
#define ZWRITE64(filefunc,filestream,buf,size)    ((*((filefunc).zfile_func64.zwrite_file))  ((filefunc).zfile_func64.opaque,filestream,buf,size))

#define ZCLOSE64(filefunc,filestream)             ((*((filefunc).zfile_func64.zclose_file))  ((filefunc).zfile_func64.opaque,filestream))
#define ZERROR64(filefunc,filestream)             ((*((filefunc).zfile_func64.zerror_file))  ((filefunc).zfile_func64.opaque,filestream))

voidpf call_zopen64 OF( ( const zlib_filefunc64_32_def * pfilefunc, const void * filename, int mode ) );
long    call_zseek64 OF( ( const zlib_filefunc64_32_def * pfilefunc, voidpf filestream, ZPOS64_T offset, int origin ) );
ZPOS64_T call_ztell64 OF( ( const zlib_filefunc64_32_def * pfilefunc, voidpf filestream ) );

void    fill_zlib_filefunc64_32_def_from_filefunc32( zlib_filefunc64_32_def * p_filefunc64_32, const zlib_filefunc_def * p_filefunc32 );

#define ZOPEN64(filefunc,filename,mode)         (call_zopen64((&(filefunc)),(filename),(mode)))
#define ZTELL64(filefunc,filestream)            (call_ztell64((&(filefunc)),(filestream)))
#define ZSEEK64(filefunc,filestream,pos,mode)   (call_zseek64((&(filefunc)),(filestream),(pos),(mode)))

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// ioapi.c
#if defined(_WIN32) && (!(defined(_CRT_SECURE_NO_WARNINGS)))
#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(__APPLE__) || defined(IOAPI_NO_64)
// In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

voidpf call_zopen64( const zlib_filefunc64_32_def * pfilefunc, const void * filename, int mode )
{
	if( pfilefunc->zfile_func64.zopen64_file != nullptr )
		return ( *( pfilefunc->zfile_func64.zopen64_file ) ) ( pfilefunc->zfile_func64.opaque, filename, mode );
	else
	{
		return ( *( pfilefunc->zopen32_file ) )( pfilefunc->zfile_func64.opaque, ( const char * )filename, mode );
	}
}

long call_zseek64( const zlib_filefunc64_32_def * pfilefunc, voidpf filestream, ZPOS64_T offset, int origin )
{
	if( pfilefunc->zfile_func64.zseek64_file != nullptr )
		return ( *( pfilefunc->zfile_func64.zseek64_file ) ) ( pfilefunc->zfile_func64.opaque, filestream, offset, origin );
	else
	{
		uLong offsetTruncated = ( uLong )offset;
		if( offsetTruncated != offset )
			return -1;
		else
			return ( *( pfilefunc->zseek32_file ) )( pfilefunc->zfile_func64.opaque, filestream, offsetTruncated, origin );
	}
}

ZPOS64_T call_ztell64( const zlib_filefunc64_32_def * pfilefunc, voidpf filestream )
{
	if( pfilefunc->zfile_func64.zseek64_file != nullptr )
		return ( *( pfilefunc->zfile_func64.ztell64_file ) ) ( pfilefunc->zfile_func64.opaque, filestream );
	else
	{
		uLong tell_uLong = ( *( pfilefunc->ztell32_file ) )( pfilefunc->zfile_func64.opaque, filestream );
		if( ( tell_uLong ) == MAXU32 )
			return ( ZPOS64_T )-1;
		else
			return tell_uLong;
	}
}

void fill_zlib_filefunc64_32_def_from_filefunc32( zlib_filefunc64_32_def * p_filefunc64_32, const zlib_filefunc_def * p_filefunc32 )
{
	p_filefunc64_32->zfile_func64.zopen64_file = nullptr;
	p_filefunc64_32->zopen32_file = p_filefunc32->zopen_file;
	p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
	p_filefunc64_32->zfile_func64.zread_file = p_filefunc32->zread_file;
	p_filefunc64_32->zfile_func64.zwrite_file = p_filefunc32->zwrite_file;
	p_filefunc64_32->zfile_func64.ztell64_file = nullptr;
	p_filefunc64_32->zfile_func64.zseek64_file = nullptr;
	p_filefunc64_32->zfile_func64.zclose_file = p_filefunc32->zclose_file;
	p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
	p_filefunc64_32->zfile_func64.opaque = p_filefunc32->opaque;
	p_filefunc64_32->zseek32_file = p_filefunc32->zseek_file;
	p_filefunc64_32->ztell32_file = p_filefunc32->ztell_file;
}

static voidpf  fopen_file_func OF( ( voidpf opaque, const char * filename, int mode ) );
static uLong   fread_file_func OF( ( voidpf opaque, voidpf stream, void * buf, uLong size ) );
static uLong   fwrite_file_func OF( ( voidpf opaque, voidpf stream, const void * buf, uLong size ) );
static ZPOS64_T ftell64_file_func OF( ( voidpf opaque, voidpf stream ) );
static long    fseek64_file_func OF( ( voidpf opaque, voidpf stream, ZPOS64_T offset, int origin ) );
static int     fclose_file_func OF( ( voidpf opaque, voidpf stream ) );
static int     ferror_file_func OF( ( voidpf opaque, voidpf stream ) );

static voidpf fopen_file_func( voidpf opaque, const char * filename, int mode )
{
	FILE * file = nullptr;
	const char * mode_fopen = nullptr;
	if( ( mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER ) == ZLIB_FILEFUNC_MODE_READ )
		mode_fopen = "rb";
	else
		if( mode & ZLIB_FILEFUNC_MODE_EXISTING )
			mode_fopen = "r+b";
		else
			if( mode & ZLIB_FILEFUNC_MODE_CREATE )
				mode_fopen = "wb";

	if( ( filename != nullptr ) && ( mode_fopen != nullptr ) )
		file = fopen( filename, mode_fopen );
	return file;
}

static voidpf fopen64_file_func( voidpf opaque, const void * filename, int mode )
{
	FILE * file = nullptr;
	const char * mode_fopen = nullptr;
	if( ( mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER ) == ZLIB_FILEFUNC_MODE_READ )
		mode_fopen = "rb";
	else
		if( mode & ZLIB_FILEFUNC_MODE_EXISTING )
			mode_fopen = "r+b";
		else
			if( mode & ZLIB_FILEFUNC_MODE_CREATE )
				mode_fopen = "wb";

	if( ( filename != nullptr ) && ( mode_fopen != nullptr ) )
		file = FOPEN_FUNC( ( const char * )filename, mode_fopen );
	return file;
}

static uLong fread_file_func( voidpf opaque, voidpf stream, void * buf, uLong size )
{
	uLong ret;
	ret = ( uLong )fread( buf, 1, ( size_t )size, ( FILE * )stream );
	return ret;
}

static uLong fwrite_file_func( voidpf opaque, voidpf stream, const void * buf, uLong size )
{
	uLong ret;
	ret = ( uLong )fwrite( buf, 1, ( size_t )size, ( FILE * )stream );
	return ret;
}

static long ftell_file_func( voidpf opaque, voidpf stream )
{
	long ret;
	ret = ftell( ( FILE * )stream );
	return ret;
}

static ZPOS64_T ftell64_file_func( voidpf opaque, voidpf stream )
{
	ZPOS64_T ret;
	ret = FTELLO_FUNC( ( FILE * )stream );
	return ret;
}

static long fseek_file_func( voidpf  opaque, voidpf stream, uLong offset, int origin )
{
	int fseek_origin = 0;
	long ret;
	switch( origin )
	{
	case ZLIB_FILEFUNC_SEEK_CUR:
		fseek_origin = SEEK_CUR;
		break;
	case ZLIB_FILEFUNC_SEEK_END:
		fseek_origin = SEEK_END;
		break;
	case ZLIB_FILEFUNC_SEEK_SET:
		fseek_origin = SEEK_SET;
		break;
	default: return -1;
	}
	ret = 0;
	if( fseek( ( FILE * )stream, offset, fseek_origin ) != 0 )
		ret = -1;
	return ret;
}

static long fseek64_file_func( voidpf  opaque, voidpf stream, ZPOS64_T offset, int origin )
{
	int fseek_origin = 0;
	long ret;
	switch( origin )
	{
	case ZLIB_FILEFUNC_SEEK_CUR:
		fseek_origin = SEEK_CUR;
		break;
	case ZLIB_FILEFUNC_SEEK_END:
		fseek_origin = SEEK_END;
		break;
	case ZLIB_FILEFUNC_SEEK_SET:
		fseek_origin = SEEK_SET;
		break;
	default: return -1;
	}
	ret = 0;

	if( FSEEKO_FUNC( ( FILE * )stream, offset, fseek_origin ) != 0 )
		ret = -1;

	return ret;
}

static int fclose_file_func( voidpf opaque, voidpf stream )
{
	int ret;
	ret = fclose( ( FILE * )stream );
	return ret;
}

static int ferror_file_func( voidpf opaque, voidpf stream )
{
	int ret;
	ret = ferror( ( FILE * )stream );
	return ret;
}

void fill_fopen_filefunc( zlib_filefunc_def * pzlib_filefunc_def )
{
	pzlib_filefunc_def->zopen_file = fopen_file_func;
	pzlib_filefunc_def->zread_file = fread_file_func;
	pzlib_filefunc_def->zwrite_file = fwrite_file_func;
	pzlib_filefunc_def->ztell_file = ftell_file_func;
	pzlib_filefunc_def->zseek_file = fseek_file_func;
	pzlib_filefunc_def->zclose_file = fclose_file_func;
	pzlib_filefunc_def->zerror_file = ferror_file_func;
	pzlib_filefunc_def->opaque = nullptr;
}

void fill_fopen64_filefunc( zlib_filefunc64_def * pzlib_filefunc_def )
{
	pzlib_filefunc_def->zopen64_file = fopen64_file_func;
	pzlib_filefunc_def->zread_file = fread_file_func;
	pzlib_filefunc_def->zwrite_file = fwrite_file_func;
	pzlib_filefunc_def->ztell64_file = ftell64_file_func;
	pzlib_filefunc_def->zseek64_file = fseek64_file_func;
	pzlib_filefunc_def->zclose_file = fclose_file_func;
	pzlib_filefunc_def->zerror_file = ferror_file_func;
	pzlib_filefunc_def->opaque = nullptr;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// zip.h
#define Z_BZIP2ED 12

#if defined(STRICTZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
    from (void*) without cast */
typedef struct TagzipFile__ { int unused; } zipFile__;
typedef zipFile__ * zipFile;
#else
typedef voidp zipFile;
#endif

#define ZIP_OK                          (0)
#define ZIP_EOF                         (0)
#define ZIP_ERRNO                       (Z_ERRNO)
#define ZIP_PARAMERROR                  (-102)
#define ZIP_BADZIPFILE                  (-103)
#define ZIP_INTERNALERROR               (-104)

#ifndef DEF_MEM_LEVEL
#  if MAX_MEM_LEVEL >= 8
#    define DEF_MEM_LEVEL 8
#  else
#    define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#  endif
#endif

typedef struct tm_zip_s
{
    uInt tm_sec;            /* seconds after the minute - [0,59] */
    uInt tm_min;            /* minutes after the hour - [0,59] */
    uInt tm_hour;           /* hours since midnight - [0,23] */
    uInt tm_mday;           /* day of the month - [1,31] */
    uInt tm_mon;            /* months since January - [0,11] */
    uInt tm_year;           /* years - [1980..2044] */
} tm_zip;

typedef struct
{
    tm_zip      tmz_date;       /* date in understandable format           */
    uLong       dosDate;       /* if dos_date == 0, tmu_date is used      */
/*    uLong       flag;        */   /* general purpose bit flag        2 bytes */

    uLong       internal_fa;    /* internal file attributes        2 bytes */
    uLong       external_fa;    /* external file attributes        4 bytes */
} zip_fileinfo;

typedef const char * zipcharpc;


#define APPEND_STATUS_CREATE        (0)
#define APPEND_STATUS_CREATEAFTER   (1)
#define APPEND_STATUS_ADDINZIP      (2)

zipFile zipOpen OF( ( const char * pathname, int append ) );
zipFile zipOpen64 OF( ( const void * pathname, int append ) );

zipFile zipOpen2 OF( ( const char * pathname,
                                      int append,
                                      zipcharpc * globalcomment,
                                      zlib_filefunc_def * pzlib_filefunc_def ) );

zipFile zipOpen2_64 OF( ( const void * pathname,
                                         int append,
                                         zipcharpc * globalcomment,
                                         zlib_filefunc64_def * pzlib_filefunc_def ) );

int zipOpenNewFileInZip OF( ( zipFile file,
                                             const char * filename,
                                             const zip_fileinfo * zipfi,
                                             const void * extrafield_local,
                                             uInt size_extrafield_local,
                                             const void * extrafield_global,
                                             uInt size_extrafield_global,
                                             const char * comment,
                                             int method,
                                             int level ) );

int zipOpenNewFileInZip64 OF( ( zipFile file,
                                               const char * filename,
                                               const zip_fileinfo * zipfi,
                                               const void * extrafield_local,
                                               uInt size_extrafield_local,
                                               const void * extrafield_global,
                                               uInt size_extrafield_global,
                                               const char * comment,
                                               int method,
                                               int level,
                                               int zip64 ) );


int zipOpenNewFileInZip2 OF( ( zipFile file,
                                              const char * filename,
                                              const zip_fileinfo * zipfi,
                                              const void * extrafield_local,
                                              uInt size_extrafield_local,
                                              const void * extrafield_global,
                                              uInt size_extrafield_global,
                                              const char * comment,
                                              int method,
                                              int level,
                                              int raw ) );


int zipOpenNewFileInZip2_64 OF( ( zipFile file,
                                                 const char * filename,
                                                 const zip_fileinfo * zipfi,
                                                 const void * extrafield_local,
                                                 uInt size_extrafield_local,
                                                 const void * extrafield_global,
                                                 uInt size_extrafield_global,
                                                 const char * comment,
                                                 int method,
                                                 int level,
                                                 int raw,
                                                 int zip64 ) );

int zipOpenNewFileInZip3 OF( ( zipFile file,
                                              const char * filename,
                                              const zip_fileinfo * zipfi,
                                              const void * extrafield_local,
                                              uInt size_extrafield_local,
                                              const void * extrafield_global,
                                              uInt size_extrafield_global,
                                              const char * comment,
                                              int method,
                                              int level,
                                              int raw,
                                              int windowBits,
                                              int memLevel,
                                              int strategy,
                                              const char * password,
                                              uLong crcForCrypting ) );

int zipOpenNewFileInZip3_64 OF( ( zipFile file,
                                                 const char * filename,
                                                 const zip_fileinfo * zipfi,
                                                 const void * extrafield_local,
                                                 uInt size_extrafield_local,
                                                 const void * extrafield_global,
                                                 uInt size_extrafield_global,
                                                 const char * comment,
                                                 int method,
                                                 int level,
                                                 int raw,
                                                 int windowBits,
                                                 int memLevel,
                                                 int strategy,
                                                 const char * password,
                                                 uLong crcForCrypting,
                                                 int zip64
                                                 ) );

int zipOpenNewFileInZip4 OF( ( zipFile file,
                                              const char * filename,
                                              const zip_fileinfo * zipfi,
                                              const void * extrafield_local,
                                              uInt size_extrafield_local,
                                              const void * extrafield_global,
                                              uInt size_extrafield_global,
                                              const char * comment,
                                              int method,
                                              int level,
                                              int raw,
                                              int windowBits,
                                              int memLevel,
                                              int strategy,
                                              const char * password,
                                              uLong crcForCrypting,
                                              uLong versionMadeBy,
                                              uLong flagBase
                                              ) );


int zipOpenNewFileInZip4_64 OF( ( zipFile file,
                                                 const char * filename,
                                                 const zip_fileinfo * zipfi,
                                                 const void * extrafield_local,
                                                 uInt size_extrafield_local,
                                                 const void * extrafield_global,
                                                 uInt size_extrafield_global,
                                                 const char * comment,
                                                 int method,
                                                 int level,
                                                 int raw,
                                                 int windowBits,
                                                 int memLevel,
                                                 int strategy,
                                                 const char * password,
                                                 uLong crcForCrypting,
                                                 uLong versionMadeBy,
                                                 uLong flagBase,
                                                 int zip64
                                                 ) );

int zipWriteInFileInZip OF( ( zipFile file, const void * buf, unsigned len ) );

int zipCloseFileInZip OF( ( zipFile file ) );

int zipCloseFileInZipRaw OF( ( zipFile file, uLong uncompressed_size, uLong crc32 ) );

int zipCloseFileInZipRaw64 OF( ( zipFile file, ZPOS64_T uncompressed_size, uLong crc32 ) );

int zipClose OF( ( zipFile file, const char * global_comment ) );


int zipRemoveExtraInfoBlock OF( ( char * pData, int * dataLen, short sHeader ) );

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// zip.c

#ifndef VERSIONMADEBY
# define VERSIONMADEBY   (0x0) /* platform depedent */
#endif

#ifndef Z_BUFSIZE
#define Z_BUFSIZE (64*1024) //(16384)
#endif

#ifndef Z_MAXFILENAMEINZIP
#define Z_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif
#ifndef TRYFREE
# define TRYFREE(p) {if (p) free(p);}
#endif

/*
#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)
*/

/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined.... */


// NOT sure that this work on ALL platform
#define MAKEULONG64(a, b) ((ZPOS64_T)(((unsigned long)(a)) | ((ZPOS64_T)((unsigned long)(b))) << 32))

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

#ifndef DEF_MEM_LEVEL
#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif
#endif
const char zip_copyright[] = " zip 1.01 Copyright 1998-2004 Gilles Vollant - http://www.winimage.com/zLibDll";


#define SIZEDATA_INDATABLOCK (4096-(4*4))

#define LOCALHEADERMAGIC    (0x04034b50)
#define CENTRALHEADERMAGIC  (0x02014b50)
#define ENDHEADERMAGIC      (0x06054b50)
#define ZIP64ENDHEADERMAGIC      (0x6064b50)
#define ZIP64ENDLOCHEADERMAGIC   (0x7064b50)

#define FLAG_LOCALHEADER_OFFSET (0x06)
#define CRC_LOCALHEADER_OFFSET  (0x0e)

#define SIZECENTRALHEADER (0x2e) /* 46 */

typedef struct linkedlist_datablock_internal_s
{
    struct linkedlist_datablock_internal_s * next_datablock;
    uLong  avail_in_this_block;
    uLong  filled_in_this_block;
    uLong  unused; /* for future use and alignment */
    unsigned char data[SIZEDATA_INDATABLOCK];
} linkedlist_datablock_internal;

typedef struct linkedlist_data_s
{
    linkedlist_datablock_internal * first_block;
    linkedlist_datablock_internal * last_block;
} linkedlist_data;


typedef struct
{
    z_stream stream;            /* zLib stream structure for inflate */
#ifdef HAVE_BZIP2
    bz_stream bstream;          /* bzLib stream structure for bziped */
#endif

    int  stream_initialised;    /* 1 is stream is initialised */
    uInt pos_in_buffered_data;  /* last written byte in buffered_data */

    ZPOS64_T pos_local_header;     /* offset of the static header of the file
                                     currenty writing */
    char * central_header;       /* central header data for the current file */
    uLong size_centralExtra;
    uLong size_centralheader;   /* size of the central header for cur file */
    uLong size_centralExtraFree; /* Extra bytes allocated to the centralheader but that are not used */
    uLong flag;                 /* flag of the file currently writing */

    int  method;                /* compression method of file currenty wr.*/
    int  raw;                   /* 1 for directly writing raw data */
    Byte buffered_data[Z_BUFSIZE];/* buffer contain compressed data to be writ*/
    uLong dosDate;
    uLong crc32;
    int  encrypt;
    int  zip64;               /* Add ZIP64 extened information in the extra field */
    ZPOS64_T pos_zip64extrainfo;
    ZPOS64_T totalCompressedData;
    ZPOS64_T totalUncompressedData;
#ifndef NOCRYPT
    unsigned long keys[3];     /* keys defining the pseudo-random sequence */
    const z_crc_t * pcrc_32_tab;
    int crypt_header_size;
#endif
} curfile64_info;

typedef struct
{
    zlib_filefunc64_32_def z_filefunc;
    voidpf filestream;        /* io structore of the zipfile */
    linkedlist_data central_dir;/* datablock with central dir in construction*/
    int  in_opened_file_inzip;  /* 1 if a file in the zip is currently writ.*/
    curfile64_info ci;            /* info on the file curretly writing */

    ZPOS64_T begin_pos;            /* position of the beginning of the zipfile */
    ZPOS64_T add_position_when_writing_offset;
    ZPOS64_T number_entry;

#ifndef NO_ADDFILEINEXISTINGZIP
    char * globalcomment;
#endif

} zip64_internal;

static linkedlist_datablock_internal * allocate_new_datablock()
{
    linkedlist_datablock_internal * ldi;
    ldi = ( linkedlist_datablock_internal * )
        ALLOC( sizeof( linkedlist_datablock_internal ) );
    if( ldi != NULL )
    {
        ldi->next_datablock = NULL;
        ldi->filled_in_this_block = 0;
        ldi->avail_in_this_block = SIZEDATA_INDATABLOCK;
    }
    return ldi;
}

static void free_datablock( linkedlist_datablock_internal * ldi )
{
    while( ldi != NULL )
    {
        linkedlist_datablock_internal * ldinext = ldi->next_datablock;
        TRYFREE( ldi );
        ldi = ldinext;
    }
}

static void init_linkedlist( linkedlist_data * ll )
{
    ll->first_block = ll->last_block = NULL;
}

static void free_linkedlist( linkedlist_data * ll )
{
    free_datablock( ll->first_block );
    ll->first_block = ll->last_block = NULL;
}


static int add_data_in_datablock( linkedlist_data * ll, const void * buf, uLong len )
{
    linkedlist_datablock_internal * ldi;
    const unsigned char * from_copy;

    if( ll == NULL )
        return ZIP_INTERNALERROR;

    if( ll->last_block == NULL )
    {
        ll->first_block = ll->last_block = allocate_new_datablock();
        if( ll->first_block == NULL )
            return ZIP_INTERNALERROR;
    }

    ldi = ll->last_block;
    from_copy = ( unsigned char * )buf;

    while( len > 0 )
    {
        uInt copy_this;
        uInt i;
        unsigned char * to_copy;

        if( ldi->avail_in_this_block == 0 )
        {
            ldi->next_datablock = allocate_new_datablock();
            if( ldi->next_datablock == NULL )
                return ZIP_INTERNALERROR;
            ldi = ldi->next_datablock;
            ll->last_block = ldi;
        }

        if( ldi->avail_in_this_block < len )
            copy_this = ( uInt )ldi->avail_in_this_block;
        else
            copy_this = ( uInt )len;

        to_copy = &( ldi->data[ldi->filled_in_this_block] );

        for( i = 0; i < copy_this; i++ )
            *( to_copy + i ) = *( from_copy + i );

        ldi->filled_in_this_block += copy_this;
        ldi->avail_in_this_block -= copy_this;
        from_copy += copy_this;
        len -= copy_this;
    }
    return ZIP_OK;
}



/****************************************************************************/

#ifndef NO_ADDFILEINEXISTINGZIP
/* ===========================================================================
   Inputs a long in LSB order to the given file
   nbByte == 1, 2 ,4 or 8 (byte, short or long, ZPOS64_T)
*/

static int zip64local_putValue OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, ZPOS64_T x, int nbByte ) );
static int zip64local_putValue( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, ZPOS64_T x, int nbByte )
{
    unsigned char buf[8];
    int n;
    for( n = 0; n < nbByte; n++ )
    {
        buf[n] = ( unsigned char )( x & 0xff );
        x >>= 8;
    }
    if( x != 0 )
    {     /* data overflow - hack for ZIP64 (X Roche) */
        for( n = 0; n < nbByte; n++ )
        {
            buf[n] = 0xff;
        }
    }

    if( ZWRITE64( *pzlib_filefunc_def, filestream, buf, nbByte ) != ( uLong )nbByte )
        return ZIP_ERRNO;
    else
        return ZIP_OK;
}

static void zip64local_putValue_inmemory OF( ( void * dest, ZPOS64_T x, int nbByte ) );
static void zip64local_putValue_inmemory( void * dest, ZPOS64_T x, int nbByte )
{
    unsigned char * buf = ( unsigned char * )dest;
    int n;
    for( n = 0; n < nbByte; n++ )
    {
        buf[n] = ( unsigned char )( x & 0xff );
        x >>= 8;
    }

    if( x != 0 )
    {     /* data overflow - hack for ZIP64 */
        for( n = 0; n < nbByte; n++ )
        {
            buf[n] = 0xff;
        }
    }
}

/****************************************************************************/


static uLong zip64local_TmzDateToDosDate( const tm_zip * ptm )
{
    uLong year = ( uLong )ptm->tm_year;
    if( year >= 1980 )
        year -= 1980;
    else if( year >= 80 )
        year -= 80;
    return
        ( uLong )( ( ( ptm->tm_mday ) + ( 32 * ( ptm->tm_mon + 1 ) ) + ( 512 * year ) ) << 16 ) |
        ( ( ptm->tm_sec / 2 ) + ( 32 * ptm->tm_min ) + ( 2048 * ( uLong )ptm->tm_hour ) );
}


/****************************************************************************/

static int zip64local_getByte OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, int * pi ) );

static int zip64local_getByte( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, int * pi )
{
    unsigned char c;
    int err = ( int )ZREAD64( *pzlib_filefunc_def, filestream, &c, 1 );
    if( err == 1 )
    {
        *pi = ( int )c;
        return ZIP_OK;
    }
    else
    {
        if( ZERROR64( *pzlib_filefunc_def, filestream ) )
            return ZIP_ERRNO;
        else
            return ZIP_EOF;
    }
}


/* ===========================================================================
   Reads a long in LSB order from the given gz_stream. Sets
*/
static int zip64local_getShort OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, uLong * pX ) );

static int zip64local_getShort( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, uLong * pX )
{
    uLong x;
    int i = 0;
    int err;

    err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( uLong )i;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( uLong )i ) << 8;

    if( err == ZIP_OK )
        *pX = x;
    else
        *pX = 0;
    return err;
}

static int zip64local_getLong OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, uLong * pX ) );

static int zip64local_getLong( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, uLong * pX )
{
    uLong x;
    int i = 0;
    int err;

    err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( uLong )i;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( uLong )i ) << 8;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( uLong )i ) << 16;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( uLong )i ) << 24;

    if( err == ZIP_OK )
        *pX = x;
    else
        *pX = 0;
    return err;
}

static int zip64local_getLong64 OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, ZPOS64_T * pX ) );


static int zip64local_getLong64( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, ZPOS64_T * pX )
{
    ZPOS64_T x;
    int i = 0;
    int err;

    err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( ZPOS64_T )i;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 8;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 16;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 24;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 32;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 40;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 48;

    if( err == ZIP_OK )
        err = zip64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( ZPOS64_T )i ) << 56;

    if( err == ZIP_OK )
        *pX = x;
    else
        *pX = 0;

    return err;
}

#ifndef BUFREADCOMMENT
#define BUFREADCOMMENT (0x400)
#endif
/*
  Locate the Central directory of a zipfile (at the end, just before
    the global comment)
*/
static ZPOS64_T zip64local_SearchCentralDir OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream ) );

static ZPOS64_T zip64local_SearchCentralDir( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream )
{
    unsigned char * buf;
    ZPOS64_T uSizeFile;
    ZPOS64_T uBackRead;
    ZPOS64_T uMaxBack = 0xffff; /* maximum size of global comment */
    ZPOS64_T uPosFound = 0;

    if( ZSEEK64( *pzlib_filefunc_def, filestream, 0, ZLIB_FILEFUNC_SEEK_END ) != 0 )
        return 0;


    uSizeFile = ZTELL64( *pzlib_filefunc_def, filestream );

    if( uMaxBack > uSizeFile )
        uMaxBack = uSizeFile;

    buf = ( unsigned char * )ALLOC( BUFREADCOMMENT + 4 );
    if( buf == NULL )
        return 0;

    uBackRead = 4;
    while( uBackRead < uMaxBack )
    {
        uLong uReadSize;
        ZPOS64_T uReadPos;
        int i;
        if( uBackRead + BUFREADCOMMENT > uMaxBack )
            uBackRead = uMaxBack;
        else
            uBackRead += BUFREADCOMMENT;
        uReadPos = uSizeFile - uBackRead;

        uReadSize = ( ( BUFREADCOMMENT + 4 ) < ( uSizeFile - uReadPos ) ) ?
            ( BUFREADCOMMENT + 4 ) : ( uLong )( uSizeFile - uReadPos );
        if( ZSEEK64( *pzlib_filefunc_def, filestream, uReadPos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            break;

        if( ZREAD64( *pzlib_filefunc_def, filestream, buf, uReadSize ) != uReadSize )
            break;

        for( i = ( int )uReadSize - 3; ( i-- ) > 0;)
            if( ( ( *( buf + i ) ) == 0x50 ) && ( ( *( buf + i + 1 ) ) == 0x4b ) &&
                ( ( *( buf + i + 2 ) ) == 0x05 ) && ( ( *( buf + i + 3 ) ) == 0x06 ) )
            {
                uPosFound = uReadPos + i;
                break;
            }

        if( uPosFound != 0 )
            break;
    }
    TRYFREE( buf );
    return uPosFound;
}

/*
Locate the End of Zip64 Central directory locator and from there find the CD of a zipfile (at the end, just before
the global comment)
*/
static ZPOS64_T zip64local_SearchCentralDir64 OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream ) );

static ZPOS64_T zip64local_SearchCentralDir64( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream )
{
    unsigned char * buf;
    ZPOS64_T uSizeFile;
    ZPOS64_T uBackRead;
    ZPOS64_T uMaxBack = 0xffff; /* maximum size of global comment */
    ZPOS64_T uPosFound = 0;
    uLong uL;
    ZPOS64_T relativeOffset;

    if( ZSEEK64( *pzlib_filefunc_def, filestream, 0, ZLIB_FILEFUNC_SEEK_END ) != 0 )
        return 0;

    uSizeFile = ZTELL64( *pzlib_filefunc_def, filestream );

    if( uMaxBack > uSizeFile )
        uMaxBack = uSizeFile;

    buf = ( unsigned char * )ALLOC( BUFREADCOMMENT + 4 );
    if( buf == NULL )
        return 0;

    uBackRead = 4;
    while( uBackRead < uMaxBack )
    {
        uLong uReadSize;
        ZPOS64_T uReadPos;
        int i;
        if( uBackRead + BUFREADCOMMENT > uMaxBack )
            uBackRead = uMaxBack;
        else
            uBackRead += BUFREADCOMMENT;
        uReadPos = uSizeFile - uBackRead;

        uReadSize = ( ( BUFREADCOMMENT + 4 ) < ( uSizeFile - uReadPos ) ) ?
            ( BUFREADCOMMENT + 4 ) : ( uLong )( uSizeFile - uReadPos );
        if( ZSEEK64( *pzlib_filefunc_def, filestream, uReadPos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            break;

        if( ZREAD64( *pzlib_filefunc_def, filestream, buf, uReadSize ) != uReadSize )
            break;

        for( i = ( int )uReadSize - 3; ( i-- ) > 0;)
        {
            // Signature "0x07064b50" Zip64 end of central directory locater
            if( ( ( *( buf + i ) ) == 0x50 ) && ( ( *( buf + i + 1 ) ) == 0x4b ) && ( ( *( buf + i + 2 ) ) == 0x06 ) && ( ( *( buf + i + 3 ) ) == 0x07 ) )
            {
                uPosFound = uReadPos + i;
                break;
            }
        }

        if( uPosFound != 0 )
            break;
    }

    TRYFREE( buf );
    if( uPosFound == 0 )
        return 0;

    /* Zip64 end of central directory locator */
    if( ZSEEK64( *pzlib_filefunc_def, filestream, uPosFound, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return 0;

    /* the signature, already checked */
    if( zip64local_getLong( pzlib_filefunc_def, filestream, &uL ) != ZIP_OK )
        return 0;

    /* number of the disk with the start of the zip64 end of  central directory */
    if( zip64local_getLong( pzlib_filefunc_def, filestream, &uL ) != ZIP_OK )
        return 0;
    if( uL != 0 )
        return 0;

    /* relative offset of the zip64 end of central directory record */
    if( zip64local_getLong64( pzlib_filefunc_def, filestream, &relativeOffset ) != ZIP_OK )
        return 0;

    /* total number of disks */
    if( zip64local_getLong( pzlib_filefunc_def, filestream, &uL ) != ZIP_OK )
        return 0;
    if( uL != 1 )
        return 0;

    /* Goto Zip64 end of central directory record */
    if( ZSEEK64( *pzlib_filefunc_def, filestream, relativeOffset, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return 0;

    /* the signature */
    if( zip64local_getLong( pzlib_filefunc_def, filestream, &uL ) != ZIP_OK )
        return 0;

    if( uL != 0x06064b50 ) // signature of 'Zip64 end of central directory'
        return 0;

    return relativeOffset;
}

int LoadCentralDirectoryRecord( zip64_internal * pziinit )
{
    int err = ZIP_OK;
    ZPOS64_T byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/

    ZPOS64_T size_central_dir;     /* size of the central directory  */
    ZPOS64_T offset_central_dir;   /* offset of start of central directory */
    ZPOS64_T central_pos;
    uLong uL;

    uLong number_disk;          /* number of the current dist, used for
                                spaning ZIP, unsupported, always 0*/
    uLong number_disk_with_CD;  /* number the the disk with central dir, used
                                for spaning ZIP, unsupported, always 0*/
    ZPOS64_T number_entry;
    ZPOS64_T number_entry_CD;      /* total number of entries in
                                  the central dir
                                  (same than number_entry on nospan) */
    uLong VersionMadeBy;
    uLong VersionNeeded;
    uLong size_comment;

    int hasZIP64Record = 0;

    // check first if we find a ZIP64 record
    central_pos = zip64local_SearchCentralDir64( &pziinit->z_filefunc, pziinit->filestream );
    if( central_pos > 0 )
    {
        hasZIP64Record = 1;
    }
    else if( central_pos == 0 )
    {
        central_pos = zip64local_SearchCentralDir( &pziinit->z_filefunc, pziinit->filestream );
    }

    /* disable to allow appending to empty ZIP archive
            if (central_pos==0)
                err=ZIP_ERRNO;
    */

    if( hasZIP64Record )
    {
        ZPOS64_T sizeEndOfCentralDirectory;
        if( ZSEEK64( pziinit->z_filefunc, pziinit->filestream, central_pos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = ZIP_ERRNO;

        /* the signature, already checked */
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* size of zip64 end of central directory record */
        if( zip64local_getLong64( &pziinit->z_filefunc, pziinit->filestream, &sizeEndOfCentralDirectory ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* version made by */
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &VersionMadeBy ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* version needed to extract */
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &VersionNeeded ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* number of this disk */
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &number_disk ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* number of the disk with the start of the central directory */
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &number_disk_with_CD ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* total number of entries in the central directory on this disk */
        if( zip64local_getLong64( &pziinit->z_filefunc, pziinit->filestream, &number_entry ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* total number of entries in the central directory */
        if( zip64local_getLong64( &pziinit->z_filefunc, pziinit->filestream, &number_entry_CD ) != ZIP_OK )
            err = ZIP_ERRNO;

        if( ( number_entry_CD != number_entry ) || ( number_disk_with_CD != 0 ) || ( number_disk != 0 ) )
            err = ZIP_BADZIPFILE;

        /* size of the central directory */
        if( zip64local_getLong64( &pziinit->z_filefunc, pziinit->filestream, &size_central_dir ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* offset of start of central directory with respect to the
        starting disk number */
        if( zip64local_getLong64( &pziinit->z_filefunc, pziinit->filestream, &offset_central_dir ) != ZIP_OK )
            err = ZIP_ERRNO;

        // TODO..
        // read the comment from the standard central header.
        size_comment = 0;
    }
    else
    {
        // Read End of central Directory info
        if( ZSEEK64( pziinit->z_filefunc, pziinit->filestream, central_pos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = ZIP_ERRNO;

        /* the signature, already checked */
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* number of this disk */
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &number_disk ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* number of the disk with the start of the central directory */
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &number_disk_with_CD ) != ZIP_OK )
            err = ZIP_ERRNO;

        /* total number of entries in the central dir on this disk */
        number_entry = 0;
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;
        else
            number_entry = uL;

        /* total number of entries in the central dir */
        number_entry_CD = 0;
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;
        else
            number_entry_CD = uL;

        if( ( number_entry_CD != number_entry ) || ( number_disk_with_CD != 0 ) || ( number_disk != 0 ) )
            err = ZIP_BADZIPFILE;

        /* size of the central directory */
        size_central_dir = 0;
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;
        else
            size_central_dir = uL;

        /* offset of start of central directory with respect to the starting disk number */
        offset_central_dir = 0;
        if( zip64local_getLong( &pziinit->z_filefunc, pziinit->filestream, &uL ) != ZIP_OK )
            err = ZIP_ERRNO;
        else
            offset_central_dir = uL;


        /* zipfile global comment length */
        if( zip64local_getShort( &pziinit->z_filefunc, pziinit->filestream, &size_comment ) != ZIP_OK )
            err = ZIP_ERRNO;
    }

    if( ( central_pos < offset_central_dir + size_central_dir ) &&
        ( err == ZIP_OK ) )
        err = ZIP_BADZIPFILE;

    if( err != ZIP_OK )
    {
        ZCLOSE64( pziinit->z_filefunc, pziinit->filestream );
        return ZIP_ERRNO;
    }

    if( size_comment > 0 )
    {
        pziinit->globalcomment = ( char * )ALLOC( size_comment + 1 );
        if( pziinit->globalcomment )
        {
            size_comment = ZREAD64( pziinit->z_filefunc, pziinit->filestream, pziinit->globalcomment, size_comment );
            pziinit->globalcomment[size_comment] = 0;
        }
    }

    byte_before_the_zipfile = central_pos - ( offset_central_dir + size_central_dir );
    pziinit->add_position_when_writing_offset = byte_before_the_zipfile;

    {
        ZPOS64_T size_central_dir_to_read = size_central_dir;
        size_t buf_size = SIZEDATA_INDATABLOCK;
        void * buf_read = ( void * )ALLOC( buf_size );
        if( ZSEEK64( pziinit->z_filefunc, pziinit->filestream, offset_central_dir + byte_before_the_zipfile, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = ZIP_ERRNO;

        while( ( size_central_dir_to_read > 0 ) && ( err == ZIP_OK ) )
        {
            ZPOS64_T read_this = SIZEDATA_INDATABLOCK;
            if( read_this > size_central_dir_to_read )
                read_this = size_central_dir_to_read;

            if( ZREAD64( pziinit->z_filefunc, pziinit->filestream, buf_read, ( uLong )read_this ) != read_this )
                err = ZIP_ERRNO;

            if( err == ZIP_OK )
                err = add_data_in_datablock( &pziinit->central_dir, buf_read, ( uLong )read_this );

            size_central_dir_to_read -= read_this;
        }
        TRYFREE( buf_read );
    }
    pziinit->begin_pos = byte_before_the_zipfile;
    pziinit->number_entry = number_entry_CD;

    if( ZSEEK64( pziinit->z_filefunc, pziinit->filestream, offset_central_dir + byte_before_the_zipfile, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        err = ZIP_ERRNO;

    return err;
}


#endif /* !NO_ADDFILEINEXISTINGZIP*/


/************************************************************/
extern zipFile zipOpen3( const void * pathname, int append, zipcharpc * globalcomment, zlib_filefunc64_32_def * pzlib_filefunc64_32_def )
{
    zip64_internal ziinit;
    zip64_internal * zi;
    int err = ZIP_OK;

    ziinit.z_filefunc.zseek32_file = NULL;
    ziinit.z_filefunc.ztell32_file = NULL;
    if( pzlib_filefunc64_32_def == NULL )
        fill_fopen64_filefunc( &ziinit.z_filefunc.zfile_func64 );
    else
        ziinit.z_filefunc = *pzlib_filefunc64_32_def;

    ziinit.filestream = ZOPEN64( ziinit.z_filefunc,
                                 pathname,
                                 ( append == APPEND_STATUS_CREATE ) ?
                                 ( ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_CREATE ) :
                                 ( ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_EXISTING ) );

    if( ziinit.filestream == NULL )
        return NULL;

    if( append == APPEND_STATUS_CREATEAFTER )
        ZSEEK64( ziinit.z_filefunc, ziinit.filestream, 0, SEEK_END );

    ziinit.begin_pos = ZTELL64( ziinit.z_filefunc, ziinit.filestream );
    ziinit.in_opened_file_inzip = 0;
    ziinit.ci.stream_initialised = 0;
    ziinit.number_entry = 0;
    ziinit.add_position_when_writing_offset = 0;
    init_linkedlist( &( ziinit.central_dir ) );



    zi = ( zip64_internal * )ALLOC( sizeof( zip64_internal ) );
    if( zi == NULL )
    {
        ZCLOSE64( ziinit.z_filefunc, ziinit.filestream );
        return NULL;
    }

    /* now we add file in a zipfile */
#    ifndef NO_ADDFILEINEXISTINGZIP
    ziinit.globalcomment = NULL;
    if( append == APPEND_STATUS_ADDINZIP )
    {
        // Read and Cache Central Directory Records
        err = LoadCentralDirectoryRecord( &ziinit );
    }

    if( globalcomment )
    {
        *globalcomment = ziinit.globalcomment;
    }
#    endif /* !NO_ADDFILEINEXISTINGZIP*/

    if( err != ZIP_OK )
    {
    #    ifndef NO_ADDFILEINEXISTINGZIP
        TRYFREE( ziinit.globalcomment );
    #    endif /* !NO_ADDFILEINEXISTINGZIP*/
        TRYFREE( zi );
        return NULL;
    }
    else
    {
        *zi = ziinit;
        return ( zipFile )zi;
    }
}

extern zipFile zipOpen2( const char * pathname, int append, zipcharpc * globalcomment, zlib_filefunc_def * pzlib_filefunc32_def )
{
    if( pzlib_filefunc32_def != NULL )
    {
        zlib_filefunc64_32_def zlib_filefunc64_32_def_fill;
        fill_zlib_filefunc64_32_def_from_filefunc32( &zlib_filefunc64_32_def_fill, pzlib_filefunc32_def );
        return zipOpen3( pathname, append, globalcomment, &zlib_filefunc64_32_def_fill );
    }
    else
        return zipOpen3( pathname, append, globalcomment, NULL );
}

extern zipFile zipOpen2_64( const void * pathname, int append, zipcharpc * globalcomment, zlib_filefunc64_def * pzlib_filefunc_def )
{
    if( pzlib_filefunc_def != NULL )
    {
        zlib_filefunc64_32_def zlib_filefunc64_32_def_fill;
        zlib_filefunc64_32_def_fill.zfile_func64 = *pzlib_filefunc_def;
        zlib_filefunc64_32_def_fill.ztell32_file = NULL;
        zlib_filefunc64_32_def_fill.zseek32_file = NULL;
        return zipOpen3( pathname, append, globalcomment, &zlib_filefunc64_32_def_fill );
    }
    else
        return zipOpen3( pathname, append, globalcomment, NULL );
}



extern zipFile zipOpen( const char * pathname, int append )
{
    return zipOpen3( ( const void * )pathname, append, NULL, NULL );
}

extern zipFile zipOpen64( const void * pathname, int append )
{
    return zipOpen3( pathname, append, NULL, NULL );
}

int Write_LocalFileHeader( zip64_internal * zi, const char * filename, uInt size_extrafield_local, const void * extrafield_local )
{
    /* write the static header */
    int err;
    uInt size_filename = ( uInt )strlen( filename );
    uInt size_extrafield = size_extrafield_local;

    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )LOCALHEADERMAGIC, 4 );

    if( err == ZIP_OK )
    {
        if( zi->ci.zip64 )
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )45, 2 );/* version needed to extract */
        else
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )20, 2 );/* version needed to extract */
    }

    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )zi->ci.flag, 2 );

    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )zi->ci.method, 2 );

    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )zi->ci.dosDate, 4 );

    // CRC / Compressed size / Uncompressed size will be filled in later and rewritten later
    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 ); /* crc 32, unknown */
    if( err == ZIP_OK )
    {
        if( zi->ci.zip64 )
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0xFFFFFFFF, 4 ); /* compressed size, unknown */
        else
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 ); /* compressed size, unknown */
    }
    if( err == ZIP_OK )
    {
        if( zi->ci.zip64 )
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0xFFFFFFFF, 4 ); /* uncompressed size, unknown */
        else
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 ); /* uncompressed size, unknown */
    }

    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )size_filename, 2 );

    if( zi->ci.zip64 )
    {
        size_extrafield += 20;
    }

    if( err == ZIP_OK )
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )size_extrafield, 2 );

    if( ( err == ZIP_OK ) && ( size_filename > 0 ) )
    {
        if( ZWRITE64( zi->z_filefunc, zi->filestream, filename, size_filename ) != size_filename )
            err = ZIP_ERRNO;
    }

    if( ( err == ZIP_OK ) && ( size_extrafield_local > 0 ) )
    {
        if( ZWRITE64( zi->z_filefunc, zi->filestream, extrafield_local, size_extrafield_local ) != size_extrafield_local )
            err = ZIP_ERRNO;
    }


    if( ( err == ZIP_OK ) && ( zi->ci.zip64 ) )
    {
        // write the Zip64 extended info
        short HeaderID = 1;
        short DataSize = 16;
        ZPOS64_T CompressedSize = 0;
        ZPOS64_T UncompressedSize = 0;

        // Remember position of Zip64 extended info for the static file header. (needed when we update size after done with file)
        zi->ci.pos_zip64extrainfo = ZTELL64( zi->z_filefunc, zi->filestream );

        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( short )HeaderID, 2 );
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( short )DataSize, 2 );

        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( ZPOS64_T )UncompressedSize, 8 );
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( ZPOS64_T )CompressedSize, 8 );
    }

    return err;
}

/*
 NOTE.
 When writing RAW the ZIP64 extended information in extrafield_local and extrafield_global needs to be stripped
 before calling this function it can be done with zipRemoveExtraInfoBlock

 It is not done here because then we need to realloc a new buffer since parameters are 'const' and I want to minimize
 unnecessary allocations.
 */
extern int zipOpenNewFileInZip4_64( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                            const void * extrafield_local, uInt size_extrafield_local,
                                            const void * extrafield_global, uInt size_extrafield_global,
                                            const char * comment, int method, int level, int raw,
                                            int windowBits, int memLevel, int strategy,
                                            const char * password, uLong crcForCrypting,
                                            uLong versionMadeBy, uLong flagBase, int zip64 )
{
    zip64_internal * zi;
    uInt size_filename;
    uInt size_comment;
    uInt i;
    int err = ZIP_OK;

#    ifdef NOCRYPT
    ( crcForCrypting );
    if( password != NULL )
        return ZIP_PARAMERROR;
#    endif

    if( file == NULL )
        return ZIP_PARAMERROR;

#ifdef HAVE_BZIP2
    if( ( method != 0 ) && ( method != Z_DEFLATED ) && ( method != Z_BZIP2ED ) )
        return ZIP_PARAMERROR;
#else
    if( ( method != 0 ) && ( method != Z_DEFLATED ) )
        return ZIP_PARAMERROR;
#endif

    zi = ( zip64_internal * )file;

    if( zi->in_opened_file_inzip == 1 )
    {
        err = zipCloseFileInZip( file );
        if( err != ZIP_OK )
            return err;
    }

    if( filename == NULL )
        filename = "-";

    if( comment == NULL )
        size_comment = 0;
    else
        size_comment = ( uInt )strlen( comment );

    size_filename = ( uInt )strlen( filename );

    if( zipfi == NULL )
        zi->ci.dosDate = 0;
    else
    {
        if( zipfi->dosDate != 0 )
            zi->ci.dosDate = zipfi->dosDate;
        else
            zi->ci.dosDate = zip64local_TmzDateToDosDate( &zipfi->tmz_date );
    }

    zi->ci.flag = flagBase;
    if( ( level == 8 ) || ( level == 9 ) )
        zi->ci.flag |= 2;
    if( level == 2 )
        zi->ci.flag |= 4;
    if( level == 1 )
        zi->ci.flag |= 6;
    if( password != NULL )
        zi->ci.flag |= 1;

    zi->ci.crc32 = 0;
    zi->ci.method = method;
    zi->ci.encrypt = 0;
    zi->ci.stream_initialised = 0;
    zi->ci.pos_in_buffered_data = 0;
    zi->ci.raw = raw;
    zi->ci.pos_local_header = ZTELL64( zi->z_filefunc, zi->filestream );

    zi->ci.size_centralheader = SIZECENTRALHEADER + size_filename + size_extrafield_global + size_comment;
    zi->ci.size_centralExtraFree = 32; // Extra space we have reserved in case we need to add ZIP64 extra info data

    zi->ci.central_header = ( char * )ALLOC( ( uInt )zi->ci.size_centralheader + zi->ci.size_centralExtraFree );

    zi->ci.size_centralExtra = size_extrafield_global;
    zip64local_putValue_inmemory( zi->ci.central_header, ( uLong )CENTRALHEADERMAGIC, 4 );
    /* version info */
    zip64local_putValue_inmemory( zi->ci.central_header + 4, ( uLong )versionMadeBy, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 6, ( uLong )20, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 8, ( uLong )zi->ci.flag, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 10, ( uLong )zi->ci.method, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 12, ( uLong )zi->ci.dosDate, 4 );
    zip64local_putValue_inmemory( zi->ci.central_header + 16, ( uLong )0, 4 ); /*crc*/
    zip64local_putValue_inmemory( zi->ci.central_header + 20, ( uLong )0, 4 ); /*compr size*/
    zip64local_putValue_inmemory( zi->ci.central_header + 24, ( uLong )0, 4 ); /*uncompr size*/
    zip64local_putValue_inmemory( zi->ci.central_header + 28, ( uLong )size_filename, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 30, ( uLong )size_extrafield_global, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 32, ( uLong )size_comment, 2 );
    zip64local_putValue_inmemory( zi->ci.central_header + 34, ( uLong )0, 2 ); /*disk nm start*/

    if( zipfi == NULL )
        zip64local_putValue_inmemory( zi->ci.central_header + 36, ( uLong )0, 2 );
    else
        zip64local_putValue_inmemory( zi->ci.central_header + 36, ( uLong )zipfi->internal_fa, 2 );

    if( zipfi == NULL )
        zip64local_putValue_inmemory( zi->ci.central_header + 38, ( uLong )0, 4 );
    else
        zip64local_putValue_inmemory( zi->ci.central_header + 38, ( uLong )zipfi->external_fa, 4 );

    if( zi->ci.pos_local_header >= 0xffffffff )
        zip64local_putValue_inmemory( zi->ci.central_header + 42, ( uLong )0xffffffff, 4 );
    else
        zip64local_putValue_inmemory( zi->ci.central_header + 42, ( uLong )zi->ci.pos_local_header - zi->add_position_when_writing_offset, 4 );

    for( i = 0; i < size_filename; i++ )
        *( zi->ci.central_header + SIZECENTRALHEADER + i ) = *( filename + i );

    for( i = 0; i < size_extrafield_global; i++ )
        *( zi->ci.central_header + SIZECENTRALHEADER + size_filename + i ) =
        *( ( ( const char * )extrafield_global ) + i );

    for( i = 0; i < size_comment; i++ )
        *( zi->ci.central_header + SIZECENTRALHEADER + size_filename +
           size_extrafield_global + i ) = *( comment + i );
    if( zi->ci.central_header == NULL )
        return ZIP_INTERNALERROR;

    zi->ci.zip64 = zip64;
    zi->ci.totalCompressedData = 0;
    zi->ci.totalUncompressedData = 0;
    zi->ci.pos_zip64extrainfo = 0;

    err = Write_LocalFileHeader( zi, filename, size_extrafield_local, extrafield_local );

#ifdef HAVE_BZIP2
    zi->ci.bstream.avail_in = ( uInt )0;
    zi->ci.bstream.avail_out = ( uInt )Z_BUFSIZE;
    zi->ci.bstream.next_out = ( char * )zi->ci.buffered_data;
    zi->ci.bstream.total_in_hi32 = 0;
    zi->ci.bstream.total_in_lo32 = 0;
    zi->ci.bstream.total_out_hi32 = 0;
    zi->ci.bstream.total_out_lo32 = 0;
#endif

    zi->ci.stream.avail_in = ( uInt )0;
    zi->ci.stream.avail_out = ( uInt )Z_BUFSIZE;
    zi->ci.stream.next_out = zi->ci.buffered_data;
    zi->ci.stream.total_in = 0;
    zi->ci.stream.total_out = 0;
    zi->ci.stream.data_type = Z_BINARY;

#ifdef HAVE_BZIP2
    if( ( err == ZIP_OK ) && ( zi->ci.method == Z_DEFLATED || zi->ci.method == Z_BZIP2ED ) && ( !zi->ci.raw ) )
    #else
    if( ( err == ZIP_OK ) && ( zi->ci.method == Z_DEFLATED ) && ( !zi->ci.raw ) )
    #endif
    {
        if( zi->ci.method == Z_DEFLATED )
        {
            zi->ci.stream.zalloc = ( alloc_func )0;
            zi->ci.stream.zfree = ( free_func )0;
            zi->ci.stream.opaque = ( voidpf )0;

            if( windowBits > 0 )
                windowBits = -windowBits;

            err = deflateInit2( &zi->ci.stream, level, Z_DEFLATED, windowBits, memLevel, strategy );

            if( err == Z_OK )
                zi->ci.stream_initialised = Z_DEFLATED;
        }
        else if( zi->ci.method == Z_BZIP2ED )
        {
        #ifdef HAVE_BZIP2
            // Init BZip stuff here
            zi->ci.bstream.bzalloc = 0;
            zi->ci.bstream.bzfree = 0;
            zi->ci.bstream.opaque = ( voidpf )0;

            err = BZ2_bzCompressInit( &zi->ci.bstream, level, 0, 35 );
            if( err == BZ_OK )
                zi->ci.stream_initialised = Z_BZIP2ED;
        #endif
        }

    }

#    ifndef NOCRYPT
    zi->ci.crypt_header_size = 0;
    if( ( err == Z_OK ) && ( password != NULL ) )
    {
        unsigned char bufHead[RAND_HEAD_LEN];
        unsigned int sizeHead;
        zi->ci.encrypt = 1;
        zi->ci.pcrc_32_tab = get_crc_table();
        /*init_keys(password,zi->ci.keys,zi->ci.pcrc_32_tab);*/

        sizeHead = crypthead( password, bufHead, RAND_HEAD_LEN, zi->ci.keys, zi->ci.pcrc_32_tab, crcForCrypting );
        zi->ci.crypt_header_size = sizeHead;

        if( ZWRITE64( zi->z_filefunc, zi->filestream, bufHead, sizeHead ) != sizeHead )
            err = ZIP_ERRNO;
    }
#    endif

    if( err == Z_OK )
        zi->in_opened_file_inzip = 1;
    return err;
}

extern int zipOpenNewFileInZip4( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                         const void * extrafield_local, uInt size_extrafield_local,
                                         const void * extrafield_global, uInt size_extrafield_global,
                                         const char * comment, int method, int level, int raw,
                                         int windowBits, int memLevel, int strategy,
                                         const char * password, uLong crcForCrypting,
                                         uLong versionMadeBy, uLong flagBase )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, raw,
                                    windowBits, memLevel, strategy,
                                    password, crcForCrypting, versionMadeBy, flagBase, 0 );
}

extern int zipOpenNewFileInZip3( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                         const void * extrafield_local, uInt size_extrafield_local,
                                         const void * extrafield_global, uInt size_extrafield_global,
                                         const char * comment, int method, int level, int raw,
                                         int windowBits, int memLevel, int strategy,
                                         const char * password, uLong crcForCrypting )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, raw,
                                    windowBits, memLevel, strategy,
                                    password, crcForCrypting, VERSIONMADEBY, 0, 0 );
}

extern int zipOpenNewFileInZip3_64( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                            const void * extrafield_local, uInt size_extrafield_local,
                                            const void * extrafield_global, uInt size_extrafield_global,
                                            const char * comment, int method, int level, int raw,
                                            int windowBits, int memLevel, int strategy,
                                            const char * password, uLong crcForCrypting, int zip64 )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, raw,
                                    windowBits, memLevel, strategy,
                                    password, crcForCrypting, VERSIONMADEBY, 0, zip64 );
}

extern int zipOpenNewFileInZip2( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                         const void * extrafield_local, uInt size_extrafield_local,
                                         const void * extrafield_global, uInt size_extrafield_global,
                                         const char * comment, int method, int level, int raw )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, raw,
                                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                    NULL, 0, VERSIONMADEBY, 0, 0 );
}

extern int zipOpenNewFileInZip2_64( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                            const void * extrafield_local, uInt size_extrafield_local,
                                            const void * extrafield_global, uInt size_extrafield_global,
                                            const char * comment, int method, int level, int raw, int zip64 )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, raw,
                                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                    NULL, 0, VERSIONMADEBY, 0, zip64 );
}

extern int zipOpenNewFileInZip64( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                          const void * extrafield_local, uInt size_extrafield_local,
                                          const void * extrafield_global, uInt size_extrafield_global,
                                          const char * comment, int method, int level, int zip64 )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, 0,
                                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                    NULL, 0, VERSIONMADEBY, 0, zip64 );
}

extern int zipOpenNewFileInZip( zipFile file, const char * filename, const zip_fileinfo * zipfi,
                                        const void * extrafield_local, uInt size_extrafield_local,
                                        const void * extrafield_global, uInt size_extrafield_global,
                                        const char * comment, int method, int level )
{
    return zipOpenNewFileInZip4_64( file, filename, zipfi,
                                    extrafield_local, size_extrafield_local,
                                    extrafield_global, size_extrafield_global,
                                    comment, method, level, 0,
                                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                    NULL, 0, VERSIONMADEBY, 0, 0 );
}

static int zip64FlushWriteBuffer( zip64_internal * zi )
{
    int err = ZIP_OK;

    if( zi->ci.encrypt != 0 )
    {
    #ifndef NOCRYPT
        uInt i;
        int t;
        for( i = 0; i < zi->ci.pos_in_buffered_data; i++ )
            zi->ci.buffered_data[i] = zencode( zi->ci.keys, zi->ci.pcrc_32_tab, zi->ci.buffered_data[i], t );
    #endif
    }

    if( ZWRITE64( zi->z_filefunc, zi->filestream, zi->ci.buffered_data, zi->ci.pos_in_buffered_data ) != zi->ci.pos_in_buffered_data )
        err = ZIP_ERRNO;

    zi->ci.totalCompressedData += zi->ci.pos_in_buffered_data;

#ifdef HAVE_BZIP2
    if( zi->ci.method == Z_BZIP2ED )
    {
        zi->ci.totalUncompressedData += zi->ci.bstream.total_in_lo32;
        zi->ci.bstream.total_in_lo32 = 0;
        zi->ci.bstream.total_in_hi32 = 0;
    }
    else
    #endif
    {
        zi->ci.totalUncompressedData += zi->ci.stream.total_in;
        zi->ci.stream.total_in = 0;
    }


    zi->ci.pos_in_buffered_data = 0;

    return err;
}

extern int zipWriteInFileInZip( zipFile file, const void * buf, unsigned int len )
{
    zip64_internal * zi;
    int err = ZIP_OK;

    if( file == NULL )
        return ZIP_PARAMERROR;
    zi = ( zip64_internal * )file;

    if( zi->in_opened_file_inzip == 0 )
        return ZIP_PARAMERROR;

    zi->ci.crc32 = crc32( zi->ci.crc32, ( const Bytef * )buf, ( uInt )len );

    {
        zi->ci.stream.next_in = ( Bytef * )buf;
        zi->ci.stream.avail_in = len;

        while( ( err == ZIP_OK ) && ( zi->ci.stream.avail_in > 0 ) )
        {
            if( zi->ci.stream.avail_out == 0 )
            {
                if( zip64FlushWriteBuffer( zi ) == ZIP_ERRNO )
                    err = ZIP_ERRNO;
                zi->ci.stream.avail_out = ( uInt )Z_BUFSIZE;
                zi->ci.stream.next_out = zi->ci.buffered_data;
            }


            if( err != ZIP_OK )
                break;

            if( ( zi->ci.method == Z_DEFLATED ) && ( !zi->ci.raw ) )
            {
                uLong uTotalOutBefore = zi->ci.stream.total_out;
                err = deflate( &zi->ci.stream, Z_NO_FLUSH );
                if( uTotalOutBefore > zi->ci.stream.total_out )
                {
                    int bBreak = 0;
                    bBreak++;
                }

                zi->ci.pos_in_buffered_data += ( uInt )( zi->ci.stream.total_out - uTotalOutBefore );
            }
            else
            {
                uInt copy_this, i;
                if( zi->ci.stream.avail_in < zi->ci.stream.avail_out )
                    copy_this = zi->ci.stream.avail_in;
                else
                    copy_this = zi->ci.stream.avail_out;

                for( i = 0; i < copy_this; i++ )
                    *( ( ( char * )zi->ci.stream.next_out ) + i ) =
                    *( ( ( const char * )zi->ci.stream.next_in ) + i );
                {
                    zi->ci.stream.avail_in -= copy_this;
                    zi->ci.stream.avail_out -= copy_this;
                    zi->ci.stream.next_in += copy_this;
                    zi->ci.stream.next_out += copy_this;
                    zi->ci.stream.total_in += copy_this;
                    zi->ci.stream.total_out += copy_this;
                    zi->ci.pos_in_buffered_data += copy_this;
                }
            }
        }// while(...)
    }

    return err;
}

extern int zipCloseFileInZipRaw( zipFile file, uLong uncompressed_size, uLong crc32 )
{
    return zipCloseFileInZipRaw64( file, uncompressed_size, crc32 );
}

extern int zipCloseFileInZipRaw64( zipFile file, ZPOS64_T uncompressed_size, uLong crc32 )
{
    zip64_internal * zi;
    ZPOS64_T compressed_size;
    uLong invalidValue = 0xffffffff;
    short datasize = 0;
    int err = ZIP_OK;

    if( file == NULL )
        return ZIP_PARAMERROR;
    zi = ( zip64_internal * )file;

    if( zi->in_opened_file_inzip == 0 )
        return ZIP_PARAMERROR;
    zi->ci.stream.avail_in = 0;

    if( ( zi->ci.method == Z_DEFLATED ) && ( !zi->ci.raw ) )
    {
        while( err == ZIP_OK )
        {
            uLong uTotalOutBefore;
            if( zi->ci.stream.avail_out == 0 )
            {
                if( zip64FlushWriteBuffer( zi ) == ZIP_ERRNO )
                    err = ZIP_ERRNO;
                zi->ci.stream.avail_out = ( uInt )Z_BUFSIZE;
                zi->ci.stream.next_out = zi->ci.buffered_data;
            }
            uTotalOutBefore = zi->ci.stream.total_out;
            err = deflate( &zi->ci.stream, Z_FINISH );
            zi->ci.pos_in_buffered_data += ( uInt )( zi->ci.stream.total_out - uTotalOutBefore );
        }
    }
    else if( ( zi->ci.method == Z_BZIP2ED ) && ( !zi->ci.raw ) )
    {
    #ifdef HAVE_BZIP2
        err = BZ_FINISH_OK;
        while( err == BZ_FINISH_OK )
        {
            uLong uTotalOutBefore;
            if( zi->ci.bstream.avail_out == 0 )
            {
                if( zip64FlushWriteBuffer( zi ) == ZIP_ERRNO )
                    err = ZIP_ERRNO;
                zi->ci.bstream.avail_out = ( uInt )Z_BUFSIZE;
                zi->ci.bstream.next_out = ( char * )zi->ci.buffered_data;
            }
            uTotalOutBefore = zi->ci.bstream.total_out_lo32;
            err = BZ2_bzCompress( &zi->ci.bstream, BZ_FINISH );
            if( err == BZ_STREAM_END )
                err = Z_STREAM_END;

            zi->ci.pos_in_buffered_data += ( uInt )( zi->ci.bstream.total_out_lo32 - uTotalOutBefore );
        }

        if( err == BZ_FINISH_OK )
            err = ZIP_OK;
    #endif
    }

    if( err == Z_STREAM_END )
        err = ZIP_OK; /* this is normal */

    if( ( zi->ci.pos_in_buffered_data > 0 ) && ( err == ZIP_OK ) )
    {
        if( zip64FlushWriteBuffer( zi ) == ZIP_ERRNO )
            err = ZIP_ERRNO;
    }

    if( ( zi->ci.method == Z_DEFLATED ) && ( !zi->ci.raw ) )
    {
        int tmp_err = deflateEnd( &zi->ci.stream );
        if( err == ZIP_OK )
            err = tmp_err;
        zi->ci.stream_initialised = 0;
    }
#ifdef HAVE_BZIP2
    else if( ( zi->ci.method == Z_BZIP2ED ) && ( !zi->ci.raw ) )
    {
        int tmperr = BZ2_bzCompressEnd( &zi->ci.bstream );
        if( err == ZIP_OK )
            err = tmperr;
        zi->ci.stream_initialised = 0;
    }
#endif

    if( !zi->ci.raw )
    {
        crc32 = ( uLong )zi->ci.crc32;
        uncompressed_size = zi->ci.totalUncompressedData;
    }
    compressed_size = zi->ci.totalCompressedData;

#    ifndef NOCRYPT
    compressed_size += zi->ci.crypt_header_size;
#    endif

    // update Current Item crc and sizes,
    if( compressed_size >= 0xffffffff || uncompressed_size >= 0xffffffff || zi->ci.pos_local_header >= 0xffffffff )
    {
        /*version Made by*/
        zip64local_putValue_inmemory( zi->ci.central_header + 4, ( uLong )45, 2 );
        /*version needed*/
        zip64local_putValue_inmemory( zi->ci.central_header + 6, ( uLong )45, 2 );

    }

    zip64local_putValue_inmemory( zi->ci.central_header + 16, crc32, 4 ); /*crc*/


    if( compressed_size >= 0xffffffff )
        zip64local_putValue_inmemory( zi->ci.central_header + 20, invalidValue, 4 ); /*compr size*/
    else
        zip64local_putValue_inmemory( zi->ci.central_header + 20, compressed_size, 4 ); /*compr size*/

      /// set internal file attributes field
    if( zi->ci.stream.data_type == Z_ASCII )
        zip64local_putValue_inmemory( zi->ci.central_header + 36, ( uLong )Z_ASCII, 2 );

    if( uncompressed_size >= 0xffffffff )
        zip64local_putValue_inmemory( zi->ci.central_header + 24, invalidValue, 4 ); /*uncompr size*/
    else
        zip64local_putValue_inmemory( zi->ci.central_header + 24, uncompressed_size, 4 ); /*uncompr size*/

      // Add ZIP64 extra info field for uncompressed size
    if( uncompressed_size >= 0xffffffff )
        datasize += 8;

    // Add ZIP64 extra info field for compressed size
    if( compressed_size >= 0xffffffff )
        datasize += 8;

    // Add ZIP64 extra info field for relative offset to static file header of current file
    if( zi->ci.pos_local_header >= 0xffffffff )
        datasize += 8;

    if( datasize > 0 )
    {
        char * p = NULL;

        if( ( uLong )( datasize + 4 ) > zi->ci.size_centralExtraFree )
        {
            // we can not write more data to the buffer that we have room for.
            return ZIP_BADZIPFILE;
        }

        p = zi->ci.central_header + zi->ci.size_centralheader;

        // Add Extra Information Header for 'ZIP64 information'
        zip64local_putValue_inmemory( p, 0x0001, 2 ); // HeaderID
        p += 2;
        zip64local_putValue_inmemory( p, datasize, 2 ); // DataSize
        p += 2;

        if( uncompressed_size >= 0xffffffff )
        {
            zip64local_putValue_inmemory( p, uncompressed_size, 8 );
            p += 8;
        }

        if( compressed_size >= 0xffffffff )
        {
            zip64local_putValue_inmemory( p, compressed_size, 8 );
            p += 8;
        }

        if( zi->ci.pos_local_header >= 0xffffffff )
        {
            zip64local_putValue_inmemory( p, zi->ci.pos_local_header, 8 );
            p += 8;
        }

        // Update how much extra free space we got in the memory buffer
        // and increase the centralheader size so the new ZIP64 fields are included
        // ( 4 below is the size of HeaderID and DataSize field )
        zi->ci.size_centralExtraFree -= datasize + 4;
        zi->ci.size_centralheader += datasize + 4;

        // Update the extra info size field
        zi->ci.size_centralExtra += datasize + 4;
        zip64local_putValue_inmemory( zi->ci.central_header + 30, ( uLong )zi->ci.size_centralExtra, 2 );
    }

    if( err == ZIP_OK )
        err = add_data_in_datablock( &zi->central_dir, zi->ci.central_header, ( uLong )zi->ci.size_centralheader );

    free( zi->ci.central_header );

    if( err == ZIP_OK )
    {
        // Update the LocalFileHeader with the new values.

        ZPOS64_T cur_pos_inzip = ZTELL64( zi->z_filefunc, zi->filestream );

        if( ZSEEK64( zi->z_filefunc, zi->filestream, zi->ci.pos_local_header + 14, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = ZIP_ERRNO;

        if( err == ZIP_OK )
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, crc32, 4 ); /* crc 32, unknown */

        if( uncompressed_size >= 0xffffffff || compressed_size >= 0xffffffff )
        {
            if( zi->ci.pos_zip64extrainfo > 0 )
            {
                // Update the size in the ZIP64 extended field.
                if( ZSEEK64( zi->z_filefunc, zi->filestream, zi->ci.pos_zip64extrainfo + 4, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
                    err = ZIP_ERRNO;

                if( err == ZIP_OK ) /* compressed size, unknown */
                    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, uncompressed_size, 8 );

                if( err == ZIP_OK ) /* uncompressed size, unknown */
                    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, compressed_size, 8 );
            }
            else
                err = ZIP_BADZIPFILE; // Caller passed zip64 = 0, so no room for zip64 info -> fatal
        }
        else
        {
            if( err == ZIP_OK ) /* compressed size, unknown */
                err = zip64local_putValue( &zi->z_filefunc, zi->filestream, compressed_size, 4 );

            if( err == ZIP_OK ) /* uncompressed size, unknown */
                err = zip64local_putValue( &zi->z_filefunc, zi->filestream, uncompressed_size, 4 );
        }

        if( ZSEEK64( zi->z_filefunc, zi->filestream, cur_pos_inzip, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = ZIP_ERRNO;
    }

    zi->number_entry++;
    zi->in_opened_file_inzip = 0;

    return err;
}

extern int zipCloseFileInZip( zipFile file )
{
    return zipCloseFileInZipRaw( file, 0, 0 );
}

int Write_Zip64EndOfCentralDirectoryLocator( zip64_internal * zi, ZPOS64_T zip64eocd_pos_inzip )
{
    int err = ZIP_OK;
    ZPOS64_T pos = zip64eocd_pos_inzip - zi->add_position_when_writing_offset;

    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )ZIP64ENDLOCHEADERMAGIC, 4 );

    /*num disks*/
    if( err == ZIP_OK ) /* number of the disk with the start of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 );

    /*relative offset*/
    if( err == ZIP_OK ) /* Relative offset to the Zip64EndOfCentralDirectory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, pos, 8 );

    /*total disks*/ /* Do not support spawning of disk so always say 1 here*/
    if( err == ZIP_OK ) /* number of the disk with the start of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )1, 4 );

    return err;
}

int Write_Zip64EndOfCentralDirectoryRecord( zip64_internal * zi, uLong size_centraldir, ZPOS64_T centraldir_pos_inzip )
{
    int err = ZIP_OK;

    uLong Zip64DataSize = 44;

    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )ZIP64ENDHEADERMAGIC, 4 );

    if( err == ZIP_OK ) /* size of this 'zip64 end of central directory' */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( ZPOS64_T )Zip64DataSize, 8 ); // why ZPOS64_T of this ?

    if( err == ZIP_OK ) /* version made by */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )45, 2 );

    if( err == ZIP_OK ) /* version needed */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )45, 2 );

    if( err == ZIP_OK ) /* number of this disk */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 );

    if( err == ZIP_OK ) /* number of the disk with the start of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 4 );

    if( err == ZIP_OK ) /* total number of entries in the central dir on this disk */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, zi->number_entry, 8 );

    if( err == ZIP_OK ) /* total number of entries in the central dir */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, zi->number_entry, 8 );

    if( err == ZIP_OK ) /* size of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( ZPOS64_T )size_centraldir, 8 );

    if( err == ZIP_OK ) /* offset of start of central directory with respect to the starting disk number */
    {
        ZPOS64_T pos = centraldir_pos_inzip - zi->add_position_when_writing_offset;
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( ZPOS64_T )pos, 8 );
    }
    return err;
}
int Write_EndOfCentralDirectoryRecord( zip64_internal * zi, uLong size_centraldir, ZPOS64_T centraldir_pos_inzip )
{
    int err = ZIP_OK;

    /*signature*/
    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )ENDHEADERMAGIC, 4 );

    if( err == ZIP_OK ) /* number of this disk */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 2 );

    if( err == ZIP_OK ) /* number of the disk with the start of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0, 2 );

    if( err == ZIP_OK ) /* total number of entries in the central dir on this disk */
    {
        {
            if( zi->number_entry >= 0xFFFF )
                err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0xffff, 2 ); // use value in ZIP64 record
            else
                err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )zi->number_entry, 2 );
        }
    }

    if( err == ZIP_OK ) /* total number of entries in the central dir */
    {
        if( zi->number_entry >= 0xFFFF )
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0xffff, 2 ); // use value in ZIP64 record
        else
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )zi->number_entry, 2 );
    }

    if( err == ZIP_OK ) /* size of the central directory */
        err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )size_centraldir, 4 );

    if( err == ZIP_OK ) /* offset of start of central directory with respect to the starting disk number */
    {
        ZPOS64_T pos = centraldir_pos_inzip - zi->add_position_when_writing_offset;
        if( pos >= 0xffffffff )
        {
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )0xffffffff, 4 );
        }
        else
            err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )( centraldir_pos_inzip - zi->add_position_when_writing_offset ), 4 );
    }

    return err;
}

int Write_GlobalComment( zip64_internal * zi, const char * global_comment )
{
    int err = ZIP_OK;
    uInt size_global_comment = 0;

    if( global_comment != NULL )
        size_global_comment = ( uInt )strlen( global_comment );

    err = zip64local_putValue( &zi->z_filefunc, zi->filestream, ( uLong )size_global_comment, 2 );

    if( err == ZIP_OK && size_global_comment > 0 )
    {
        if( ZWRITE64( zi->z_filefunc, zi->filestream, global_comment, size_global_comment ) != size_global_comment )
            err = ZIP_ERRNO;
    }
    return err;
}

extern int zipClose( zipFile file, const char * global_comment )
{
    zip64_internal * zi;
    int err = 0;
    uLong size_centraldir = 0;
    ZPOS64_T centraldir_pos_inzip;
    ZPOS64_T pos;

    if( file == NULL )
        return ZIP_PARAMERROR;

    zi = ( zip64_internal * )file;

    if( zi->in_opened_file_inzip == 1 )
    {
        err = zipCloseFileInZip( file );
    }

#ifndef NO_ADDFILEINEXISTINGZIP
    if( global_comment == NULL )
        global_comment = zi->globalcomment;
#endif

    centraldir_pos_inzip = ZTELL64( zi->z_filefunc, zi->filestream );

    if( err == ZIP_OK )
    {
        linkedlist_datablock_internal * ldi = zi->central_dir.first_block;
        while( ldi != NULL )
        {
            if( ( err == ZIP_OK ) && ( ldi->filled_in_this_block > 0 ) )
            {
                if( ZWRITE64( zi->z_filefunc, zi->filestream, ldi->data, ldi->filled_in_this_block ) != ldi->filled_in_this_block )
                    err = ZIP_ERRNO;
            }

            size_centraldir += ldi->filled_in_this_block;
            ldi = ldi->next_datablock;
        }
    }
    free_linkedlist( &( zi->central_dir ) );

    pos = centraldir_pos_inzip - zi->add_position_when_writing_offset;
    if( pos >= 0xffffffff || zi->number_entry > 0xFFFF )
    {
        ZPOS64_T Zip64EOCDpos = ZTELL64( zi->z_filefunc, zi->filestream );
        Write_Zip64EndOfCentralDirectoryRecord( zi, size_centraldir, centraldir_pos_inzip );

        Write_Zip64EndOfCentralDirectoryLocator( zi, Zip64EOCDpos );
    }

    if( err == ZIP_OK )
        err = Write_EndOfCentralDirectoryRecord( zi, size_centraldir, centraldir_pos_inzip );

    if( err == ZIP_OK )
        err = Write_GlobalComment( zi, global_comment );

    if( ZCLOSE64( zi->z_filefunc, zi->filestream ) != 0 )
        if( err == ZIP_OK )
            err = ZIP_ERRNO;

#ifndef NO_ADDFILEINEXISTINGZIP
    TRYFREE( zi->globalcomment );
#endif
    TRYFREE( zi );

    return err;
}

extern int zipRemoveExtraInfoBlock( char * pData, int * dataLen, short sHeader )
{
    char * p = pData;
    int size = 0;
    char * pNewHeader;
    char * pTmp;
    short header;
    short dataSize;

    int retVal = ZIP_OK;

    if( pData == NULL || *dataLen < 4 )
        return ZIP_PARAMERROR;

    pNewHeader = ( char * )ALLOC( *dataLen );
    pTmp = pNewHeader;

    while( p < ( pData + *dataLen ) )
    {
        header = *( short * )p;
        dataSize = *( ( ( short * )p ) + 1 );

        if( header == sHeader ) // Header found.
        {
            p += dataSize + 4; // skip it. do not copy to temp buffer
        }
        else
        {
            // Extra Info block should not be removed, So copy it to the temp buffer.
            memcpy( pTmp, p, dataSize + 4 );
            p += dataSize + 4;
            size += dataSize + 4;
        }

    }

    if( size < *dataLen )
    {
        // clean old extra info block.
        memset( pData, 0, *dataLen );

        // copy the new extra info block over the old
        if( size > 0 )
            memcpy( pData, pNewHeader, size );

        // set the new extra info size
        *dataLen = size;

        retVal = ZIP_OK;
    }
    else
        retVal = ZIP_ERRNO;

    TRYFREE( pNewHeader );

    return retVal;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// unzip.h

#define Z_BZIP2ED 12

#if defined(STRICTUNZIP) || defined(STRICTZIPUNZIP)
typedef struct TagunzFile__ { int unused; } unzFile__;
typedef unzFile__ * unzFile;
#else
typedef voidp unzFile;
#endif


#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define UNZ_ERRNO                       (Z_ERRNO)
#define UNZ_EOF                         (0)
#define UNZ_PARAMERROR                  (-102)
#define UNZ_BADZIPFILE                  (-103)
#define UNZ_INTERNALERROR               (-104)
#define UNZ_CRCERROR                    (-105)

typedef struct tm_unz_s
{
    uInt tm_sec;            /* seconds after the minute - [0,59] */
    uInt tm_min;            /* minutes after the hour - [0,59] */
    uInt tm_hour;           /* hours since midnight - [0,23] */
    uInt tm_mday;           /* day of the month - [1,31] */
    uInt tm_mon;            /* months since January - [0,11] */
    uInt tm_year;           /* years - [1980..2044] */
} tm_unz;

typedef struct unz_global_info64_s
{
    ZPOS64_T number_entry;         /* total number of entries in
                                     the central dir on this disk */
    uLong size_comment;         /* size of the global comment of the zipfile */
} unz_global_info64;

typedef struct unz_global_info_s
{
    uLong number_entry;         /* total number of entries in
                                     the central dir on this disk */
    uLong size_comment;         /* size of the global comment of the zipfile */
} unz_global_info;

typedef struct unz_file_info64_s
{
    uLong version;              /* version made by                 2 bytes */
    uLong version_needed;       /* version needed to extract       2 bytes */
    uLong flag;                 /* general purpose bit flag        2 bytes */
    uLong compression_method;   /* compression method              2 bytes */
    uLong dosDate;              /* last mod file date in Dos fmt   4 bytes */
    uLong crc;                  /* crc-32                          4 bytes */
    ZPOS64_T compressed_size;   /* compressed size                 8 bytes */
    ZPOS64_T uncompressed_size; /* uncompressed size               8 bytes */
    uLong size_filename;        /* filename length                 2 bytes */
    uLong size_file_extra;      /* extra field length              2 bytes */
    uLong size_file_comment;    /* file comment length             2 bytes */

    uLong disk_num_start;       /* disk number start               2 bytes */
    uLong internal_fa;          /* internal file attributes        2 bytes */
    uLong external_fa;          /* external file attributes        4 bytes */

    tm_unz tmu_date;
} unz_file_info64;

typedef struct unz_file_info_s
{
    uLong version;              /* version made by                 2 bytes */
    uLong version_needed;       /* version needed to extract       2 bytes */
    uLong flag;                 /* general purpose bit flag        2 bytes */
    uLong compression_method;   /* compression method              2 bytes */
    uLong dosDate;              /* last mod file date in Dos fmt   4 bytes */
    uLong crc;                  /* crc-32                          4 bytes */
    uLong compressed_size;      /* compressed size                 4 bytes */
    uLong uncompressed_size;    /* uncompressed size               4 bytes */
    uLong size_filename;        /* filename length                 2 bytes */
    uLong size_file_extra;      /* extra field length              2 bytes */
    uLong size_file_comment;    /* file comment length             2 bytes */

    uLong disk_num_start;       /* disk number start               2 bytes */
    uLong internal_fa;          /* internal file attributes        2 bytes */
    uLong external_fa;          /* external file attributes        4 bytes */

    tm_unz tmu_date;
} unz_file_info;

int unzStringFileNameCompare OF( ( const char * fileName1, const char * fileName2, int iCaseSensitivity ) );

unzFile unzOpen OF( ( const char * Path ) );
unzFile unzOpen64 OF( ( const void * Path ) );

unzFile unzOpen2 OF( ( const char * Path, zlib_filefunc_def * pzlib_filefunc_def ) );

unzFile unzOpen2_64 OF( ( const void * Path, zlib_filefunc64_def * pzlib_filefunc_def ) );

int unzClose OF( ( unzFile file ) );

int unzGetGlobalInfo OF( ( unzFile file, unz_global_info * pglobal_info ) );

int unzGetGlobalInfo64 OF( ( unzFile file, unz_global_info64 * pglobal_info ) );

int unzGetGlobalComment OF( ( unzFile file, char * szComment, uLong uSizeBuf ) );

int unzGoToFirstFile OF( ( unzFile file ) );

int unzGoToNextFile OF( ( unzFile file ) );

int unzLocateFile OF( ( unzFile file, const char * szFileName, int iCaseSensitivity ) );

typedef struct unz_file_pos_s
{
    uLong pos_in_zip_directory;   /* offset in zip file directory */
    uLong num_of_file;            /* # of file */
} unz_file_pos;

int unzGetFilePos( unzFile file, unz_file_pos * file_pos );

int unzGoToFilePos( unzFile file, unz_file_pos * file_pos );

typedef struct unz64_file_pos_s
{
    ZPOS64_T pos_in_zip_directory;   /* offset in zip file directory */
    ZPOS64_T num_of_file;            /* # of file */
} unz64_file_pos;

int unzGetFilePos64( unzFile file, unz64_file_pos * file_pos );

int unzGoToFilePos64( unzFile file, const unz64_file_pos * file_pos );

int unzGetCurrentFileInfo64 OF( ( unzFile file,
                                                 unz_file_info64 * pfile_info,
                                                 char * szFileName,
                                                 uLong fileNameBufferSize,
                                                 void * extraField,
                                                 uLong extraFieldBufferSize,
                                                 char * szComment,
                                                 uLong commentBufferSize ) );

int unzGetCurrentFileInfo OF( ( unzFile file,
                                               unz_file_info * pfile_info,
                                               char * szFileName,
                                               uLong fileNameBufferSize,
                                               void * extraField,
                                               uLong extraFieldBufferSize,
                                               char * szComment,
                                               uLong commentBufferSize ) );

ZPOS64_T unzGetCurrentFileZStreamPos64 OF( ( unzFile file ) );

int unzOpenCurrentFile OF( ( unzFile file ) );

int unzOpenCurrentFilePassword OF( ( unzFile file, const char * password ) );

int unzOpenCurrentFile2 OF( ( unzFile file, int * method, int * level, int raw ) );

int unzOpenCurrentFile3 OF( ( unzFile file, int * method, int * level, int raw, const char * password ) );

int unzCloseCurrentFile OF( ( unzFile file ) );

int unzReadCurrentFile OF( ( unzFile file, voidp buf, unsigned len ) );

z_off_t unztell OF( ( unzFile file ) );

ZPOS64_T unztell64 OF( ( unzFile file ) );

int unzeof OF( ( unzFile file ) );

int unzGetLocalExtrafield OF( ( unzFile file, voidp buf, unsigned len ) );

ZPOS64_T unzGetOffset64( unzFile file );
uLong unzGetOffset( unzFile file );

int unzSetOffset64( unzFile file, ZPOS64_T pos );
int unzSetOffset( unzFile file, uLong pos );

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// unzip.c

#ifndef CASESENSITIVITYDEFAULT_NO
#  if !defined(unix) && !defined(CASESENSITIVITYDEFAULT_YES)
#    define CASESENSITIVITYDEFAULT_NO
#  endif
#endif

#ifndef UNZ_BUFSIZE
#define UNZ_BUFSIZE (16384)
#endif

#ifndef UNZ_MAXFILENAMEINZIP
#define UNZ_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif

#ifndef TRYFREE
# define TRYFREE(p) {if (p) free(p);}
#endif

#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)

const char unz_copyright[] = " unzip 1.01 Copyright 1998-2004 Gilles Vollant - http://www.winimage.com/zLibDll";

typedef struct unz_file_info64_internal_s
{
    ZPOS64_T offset_curfile;/* relative offset of static header 8 bytes */
} unz_file_info64_internal;

typedef struct
{
    char * read_buffer;         /* internal buffer for compressed data */
    z_stream stream;            /* zLib stream structure for inflate */

#ifdef HAVE_BZIP2
    bz_stream bstream;          /* bzLib stream structure for bziped */
#endif

    ZPOS64_T pos_in_zipfile;       /* position in byte on the zipfile, for fseek*/
    uLong stream_initialised;   /* flag set if stream structure is initialised*/

    ZPOS64_T offset_local_extrafield;/* offset of the static extra field */
    uInt  size_local_extrafield;/* size of the static extra field */
    ZPOS64_T pos_local_extrafield;   /* position in the static extra field in read*/
    ZPOS64_T total_out_64;

    uLong crc32;                /* crc32 of all data uncompressed */
    uLong crc32_wait;           /* crc32 we must obtain after decompress all */
    ZPOS64_T rest_read_compressed; /* number of byte to be decompressed */
    ZPOS64_T rest_read_uncompressed;/*number of byte to be obtained after decomp*/
    zlib_filefunc64_32_def z_filefunc;
    voidpf filestream;        /* io structore of the zipfile */
    uLong compression_method;   /* compression method (0==store) */
    ZPOS64_T byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
    int   raw;
} file_in_zip64_read_info_s;

typedef struct
{
    zlib_filefunc64_32_def z_filefunc;
    int is64bitOpenFunction;
    voidpf filestream;        /* io structore of the zipfile */
    unz_global_info64 gi;       /* public global information */
    ZPOS64_T byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
    ZPOS64_T num_file;             /* number of the current file in the zipfile*/
    ZPOS64_T pos_in_central_dir;   /* pos of the current file in the central dir*/
    ZPOS64_T current_file_ok;      /* flag about the usability of the current file*/
    ZPOS64_T central_pos;          /* position of the beginning of the central dir*/

    ZPOS64_T size_central_dir;     /* size of the central directory  */
    ZPOS64_T offset_central_dir;   /* offset of start of central directory with
                                   respect to the starting disk number */

    unz_file_info64 cur_file_info; /* public info about the current file in zip*/
    unz_file_info64_internal cur_file_info_internal; /* private info about it*/
    file_in_zip64_read_info_s * pfile_in_zip_read; /* structure about the current
                                        file if we are decompressing it */
    int encrypted;

    int isZip64;

#    ifndef NOUNCRYPT
    unsigned long keys[3];     /* keys defining the pseudo-random sequence */
    const z_crc_t * pcrc_32_tab;
#    endif
} unz64_s;

static int unz64local_getByte OF( (
    const zlib_filefunc64_32_def * pzlib_filefunc_def,
    voidpf filestream,
    int * pi ) );

static int unz64local_getByte( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream, int * pi )
{
    unsigned char c;
    int err = ( int )ZREAD64( *pzlib_filefunc_def, filestream, &c, 1 );
    if( err == 1 )
    {
        *pi = ( int )c;
        return UNZ_OK;
    }
    else
    {
        if( ZERROR64( *pzlib_filefunc_def, filestream ) )
            return UNZ_ERRNO;
        else
            return UNZ_EOF;
    }
}

static int unz64local_getShort OF( (
    const zlib_filefunc64_32_def * pzlib_filefunc_def,
    voidpf filestream,
    uLong * pX ) );

static int unz64local_getShort( const zlib_filefunc64_32_def * pzlib_filefunc_def,
                               voidpf filestream,
                               uLong * pX )
{
    uLong x;
    int i = 0;
    int err;

    err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( uLong )i;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( uLong )i ) << 8;

    if( err == UNZ_OK )
        *pX = x;
    else
        *pX = 0;
    return err;
}

static int unz64local_getLong OF( (
    const zlib_filefunc64_32_def * pzlib_filefunc_def,
    voidpf filestream,
    uLong * pX ) );

static int unz64local_getLong( const zlib_filefunc64_32_def * pzlib_filefunc_def,
                              voidpf filestream,
                              uLong * pX )
{
    uLong x;
    int i = 0;
    int err;

    err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( uLong )i;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( uLong )i ) << 8;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( uLong )i ) << 16;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x += ( ( uLong )i ) << 24;

    if( err == UNZ_OK )
        *pX = x;
    else
        *pX = 0;
    return err;
}

static int unz64local_getLong64 OF( (
    const zlib_filefunc64_32_def * pzlib_filefunc_def,
    voidpf filestream,
    ZPOS64_T * pX ) );

static int unz64local_getLong64( const zlib_filefunc64_32_def * pzlib_filefunc_def,
                                voidpf filestream,
                                ZPOS64_T * pX )
{
    ZPOS64_T x;
    int i = 0;
    int err;

    err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x = ( ZPOS64_T )i;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 8;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 16;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 24;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 32;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 40;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 48;

    if( err == UNZ_OK )
        err = unz64local_getByte( pzlib_filefunc_def, filestream, &i );
    x |= ( ( ZPOS64_T )i ) << 56;

    if( err == UNZ_OK )
        *pX = x;
    else
        *pX = 0;
    return err;
}

static int strcmpcasenosensitive_internal( const char * fileName1, const char * fileName2 )
{
    for( ;;)
    {
        char c1 = *( fileName1++ );
        char c2 = *( fileName2++ );
        if( ( c1 >= 'a' ) && ( c1 <= 'z' ) )
            c1 -= 0x20;
        if( ( c2 >= 'a' ) && ( c2 <= 'z' ) )
            c2 -= 0x20;
        if( c1 == '\0' )
            return ( ( c2 == '\0' ) ? 0 : -1 );
        if( c2 == '\0' )
            return 1;
        if( c1 < c2 )
            return -1;
        if( c1 > c2 )
            return 1;
    }
}

#ifdef  CASESENSITIVITYDEFAULT_NO
#define CASESENSITIVITYDEFAULTVALUE 2
#else
#define CASESENSITIVITYDEFAULTVALUE 1
#endif

#ifndef STRCMPCASENOSENTIVEFUNCTION
#define STRCMPCASENOSENTIVEFUNCTION strcmpcasenosensitive_internal
#endif

int unzStringFileNameCompare( const char * fileName1,
                                             const char * fileName2,
                                             int iCaseSensitivity )

{
    if( iCaseSensitivity == 0 )
        iCaseSensitivity = CASESENSITIVITYDEFAULTVALUE;

    if( iCaseSensitivity == 1 )
        return strcmp( fileName1, fileName2 );

    return STRCMPCASENOSENTIVEFUNCTION( fileName1, fileName2 );
}

#ifndef BUFREADCOMMENT
#define BUFREADCOMMENT (0x400)
#endif

static ZPOS64_T unz64local_SearchCentralDir OF( ( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream ) );
static ZPOS64_T unz64local_SearchCentralDir( const zlib_filefunc64_32_def * pzlib_filefunc_def, voidpf filestream )
{
    unsigned char * buf;
    ZPOS64_T uSizeFile;
    ZPOS64_T uBackRead;
    ZPOS64_T uMaxBack = 0xffff; /* maximum size of global comment */
    ZPOS64_T uPosFound = 0;

    if( ZSEEK64( *pzlib_filefunc_def, filestream, 0, ZLIB_FILEFUNC_SEEK_END ) != 0 )
        return 0;


    uSizeFile = ZTELL64( *pzlib_filefunc_def, filestream );

    if( uMaxBack > uSizeFile )
        uMaxBack = uSizeFile;

    buf = ( unsigned char * )ALLOC( BUFREADCOMMENT + 4 );
    if( buf == nullptr )
        return 0;

    uBackRead = 4;
    while( uBackRead < uMaxBack )
    {
        uLong uReadSize;
        ZPOS64_T uReadPos;
        int i;
        if( uBackRead + BUFREADCOMMENT > uMaxBack )
            uBackRead = uMaxBack;
        else
            uBackRead += BUFREADCOMMENT;
        uReadPos = uSizeFile - uBackRead;

        uReadSize = ( ( BUFREADCOMMENT + 4 ) < ( uSizeFile - uReadPos ) ) ?
            ( BUFREADCOMMENT + 4 ) : ( uLong )( uSizeFile - uReadPos );
        if( ZSEEK64( *pzlib_filefunc_def, filestream, uReadPos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            break;

        if( ZREAD64( *pzlib_filefunc_def, filestream, buf, uReadSize ) != uReadSize )
            break;

        for( i = ( int )uReadSize - 3; ( i-- ) > 0;)
            if( ( ( *( buf + i ) ) == 0x50 ) && ( ( *( buf + i + 1 ) ) == 0x4b ) &&
                ( ( *( buf + i + 2 ) ) == 0x05 ) && ( ( *( buf + i + 3 ) ) == 0x06 ) )
            {
                uPosFound = uReadPos + i;
                break;
            }

        if( uPosFound != 0 )
            break;
    }
    TRYFREE( buf );
    return uPosFound;
}

static ZPOS64_T unz64local_SearchCentralDir64 OF( (
    const zlib_filefunc64_32_def * pzlib_filefunc_def,
    voidpf filestream ) );

static ZPOS64_T unz64local_SearchCentralDir64( const zlib_filefunc64_32_def * pzlib_filefunc_def,
                                              voidpf filestream )
{
    unsigned char * buf;
    ZPOS64_T uSizeFile;
    ZPOS64_T uBackRead;
    ZPOS64_T uMaxBack = 0xffff; /* maximum size of global comment */
    ZPOS64_T uPosFound = 0;
    uLong uL;
    ZPOS64_T relativeOffset;

    if( ZSEEK64( *pzlib_filefunc_def, filestream, 0, ZLIB_FILEFUNC_SEEK_END ) != 0 )
        return 0;


    uSizeFile = ZTELL64( *pzlib_filefunc_def, filestream );

    if( uMaxBack > uSizeFile )
        uMaxBack = uSizeFile;

    buf = ( unsigned char * )ALLOC( BUFREADCOMMENT + 4 );
    if( buf == nullptr )
        return 0;

    uBackRead = 4;
    while( uBackRead < uMaxBack )
    {
        uLong uReadSize;
        ZPOS64_T uReadPos;
        int i;
        if( uBackRead + BUFREADCOMMENT > uMaxBack )
            uBackRead = uMaxBack;
        else
            uBackRead += BUFREADCOMMENT;
        uReadPos = uSizeFile - uBackRead;

        uReadSize = ( ( BUFREADCOMMENT + 4 ) < ( uSizeFile - uReadPos ) ) ?
            ( BUFREADCOMMENT + 4 ) : ( uLong )( uSizeFile - uReadPos );
        if( ZSEEK64( *pzlib_filefunc_def, filestream, uReadPos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            break;

        if( ZREAD64( *pzlib_filefunc_def, filestream, buf, uReadSize ) != uReadSize )
            break;

        for( i = ( int )uReadSize - 3; ( i-- ) > 0;)
            if( ( ( *( buf + i ) ) == 0x50 ) && ( ( *( buf + i + 1 ) ) == 0x4b ) &&
                ( ( *( buf + i + 2 ) ) == 0x06 ) && ( ( *( buf + i + 3 ) ) == 0x07 ) )
            {
                uPosFound = uReadPos + i;
                break;
            }

        if( uPosFound != 0 )
            break;
    }
    TRYFREE( buf );
    if( uPosFound == 0 )
        return 0;

    /* Zip64 end of central directory locator */
    if( ZSEEK64( *pzlib_filefunc_def, filestream, uPosFound, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return 0;

    /* the signature, already checked */
    if( unz64local_getLong( pzlib_filefunc_def, filestream, &uL ) != UNZ_OK )
        return 0;

    /* number of the disk with the start of the zip64 end of  central directory */
    if( unz64local_getLong( pzlib_filefunc_def, filestream, &uL ) != UNZ_OK )
        return 0;
    if( uL != 0 )
        return 0;

    /* relative offset of the zip64 end of central directory record */
    if( unz64local_getLong64( pzlib_filefunc_def, filestream, &relativeOffset ) != UNZ_OK )
        return 0;

    /* total number of disks */
    if( unz64local_getLong( pzlib_filefunc_def, filestream, &uL ) != UNZ_OK )
        return 0;
    if( uL != 1 )
        return 0;

    /* Goto end of central directory record */
    if( ZSEEK64( *pzlib_filefunc_def, filestream, relativeOffset, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return 0;

    /* the signature */
    if( unz64local_getLong( pzlib_filefunc_def, filestream, &uL ) != UNZ_OK )
        return 0;

    if( uL != 0x06064b50 )
        return 0;

    return relativeOffset;
}

static unzFile unzOpenInternal( const void * path,
                               zlib_filefunc64_32_def * pzlib_filefunc64_32_def,
                               int is64bitOpenFunction )
{
    unz64_s us;
    unz64_s * s;
    ZPOS64_T central_pos;
    uLong   uL;

    uLong number_disk;          /* number of the current dist, used for
                                   spaning ZIP, unsupported, always 0*/
    uLong number_disk_with_CD;  /* number the the disk with central dir, used
                                   for spaning ZIP, unsupported, always 0*/
    ZPOS64_T number_entry_CD;      /* total number of entries in
                                   the central dir
                                   (same than number_entry on nospan) */

    int err = UNZ_OK;

    if( unz_copyright[0] != ' ' )
        return nullptr;

    us.z_filefunc.zseek32_file = nullptr;
    us.z_filefunc.ztell32_file = nullptr;
    if( pzlib_filefunc64_32_def == nullptr )
        fill_fopen64_filefunc( &us.z_filefunc.zfile_func64 );
    else
        us.z_filefunc = *pzlib_filefunc64_32_def;
    us.is64bitOpenFunction = is64bitOpenFunction;



    us.filestream = ZOPEN64( us.z_filefunc,
                             path,
                             ZLIB_FILEFUNC_MODE_READ |
                             ZLIB_FILEFUNC_MODE_EXISTING );
    if( us.filestream == nullptr )
        return nullptr;

    central_pos = unz64local_SearchCentralDir64( &us.z_filefunc, us.filestream );
    if( central_pos )
    {
        uLong uS;
        ZPOS64_T uL64;

        us.isZip64 = 1;

        if( ZSEEK64( us.z_filefunc, us.filestream,
                     central_pos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = UNZ_ERRNO;

        /* the signature, already checked */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* size of zip64 end of central directory record */
        if( unz64local_getLong64( &us.z_filefunc, us.filestream, &uL64 ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* version made by */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &uS ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* version needed to extract */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &uS ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* number of this disk */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &number_disk ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* number of the disk with the start of the central directory */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &number_disk_with_CD ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* total number of entries in the central directory on this disk */
        if( unz64local_getLong64( &us.z_filefunc, us.filestream, &us.gi.number_entry ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* total number of entries in the central directory */
        if( unz64local_getLong64( &us.z_filefunc, us.filestream, &number_entry_CD ) != UNZ_OK )
            err = UNZ_ERRNO;

        if( ( number_entry_CD != us.gi.number_entry ) ||
            ( number_disk_with_CD != 0 ) ||
            ( number_disk != 0 ) )
            err = UNZ_BADZIPFILE;

        /* size of the central directory */
        if( unz64local_getLong64( &us.z_filefunc, us.filestream, &us.size_central_dir ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* offset of start of central directory with respect to the
          starting disk number */
        if( unz64local_getLong64( &us.z_filefunc, us.filestream, &us.offset_central_dir ) != UNZ_OK )
            err = UNZ_ERRNO;

        us.gi.size_comment = 0;
    }
    else
    {
        central_pos = unz64local_SearchCentralDir( &us.z_filefunc, us.filestream );
        if( central_pos == 0 )
            err = UNZ_ERRNO;

        us.isZip64 = 0;

        if( ZSEEK64( us.z_filefunc, us.filestream,
                     central_pos, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
            err = UNZ_ERRNO;

        /* the signature, already checked */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* number of this disk */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &number_disk ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* number of the disk with the start of the central directory */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &number_disk_with_CD ) != UNZ_OK )
            err = UNZ_ERRNO;

        /* total number of entries in the central dir on this disk */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;
        us.gi.number_entry = uL;

        /* total number of entries in the central dir */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;
        number_entry_CD = uL;

        if( ( number_entry_CD != us.gi.number_entry ) ||
            ( number_disk_with_CD != 0 ) ||
            ( number_disk != 0 ) )
            err = UNZ_BADZIPFILE;

        /* size of the central directory */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;
        us.size_central_dir = uL;

        /* offset of start of central directory with respect to the
            starting disk number */
        if( unz64local_getLong( &us.z_filefunc, us.filestream, &uL ) != UNZ_OK )
            err = UNZ_ERRNO;
        us.offset_central_dir = uL;

        /* zipfile comment length */
        if( unz64local_getShort( &us.z_filefunc, us.filestream, &us.gi.size_comment ) != UNZ_OK )
            err = UNZ_ERRNO;
    }

    if( ( central_pos < us.offset_central_dir + us.size_central_dir ) &&
        ( err == UNZ_OK ) )
        err = UNZ_BADZIPFILE;

    if( err != UNZ_OK )
    {
        ZCLOSE64( us.z_filefunc, us.filestream );
        return nullptr;
    }

    us.byte_before_the_zipfile = central_pos -
        ( us.offset_central_dir + us.size_central_dir );
    us.central_pos = central_pos;
    us.pfile_in_zip_read = nullptr;
    us.encrypted = 0;


    s = ( unz64_s * )ALLOC( sizeof( unz64_s ) );
    if( s != nullptr )
    {
        *s = us;
        unzGoToFirstFile( ( unzFile )s );
    }
    return ( unzFile )s;
}

unzFile unzOpen2( const char * path,
                                 zlib_filefunc_def * pzlib_filefunc32_def )
{
    if( pzlib_filefunc32_def != nullptr )
    {
        zlib_filefunc64_32_def zlib_filefunc64_32_def_fill;
        fill_zlib_filefunc64_32_def_from_filefunc32( &zlib_filefunc64_32_def_fill, pzlib_filefunc32_def );
        return unzOpenInternal( path, &zlib_filefunc64_32_def_fill, 0 );
    }
    else
        return unzOpenInternal( path, nullptr, 0 );
}

unzFile unzOpen2_64( const void * path,
                                    zlib_filefunc64_def * pzlib_filefunc_def )
{
    if( pzlib_filefunc_def != nullptr )
    {
        zlib_filefunc64_32_def zlib_filefunc64_32_def_fill;
        zlib_filefunc64_32_def_fill.zfile_func64 = *pzlib_filefunc_def;
        zlib_filefunc64_32_def_fill.ztell32_file = nullptr;
        zlib_filefunc64_32_def_fill.zseek32_file = nullptr;
        return unzOpenInternal( path, &zlib_filefunc64_32_def_fill, 1 );
    }
    else
        return unzOpenInternal( path, nullptr, 1 );
}

unzFile unzOpen( const char * path )
{
    return unzOpenInternal( path, nullptr, 0 );
}

unzFile unzOpen64( const void * path )
{
    return unzOpenInternal( path, nullptr, 1 );
}

int unzClose( unzFile file )
{
    unz64_s * s;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;

    if( s->pfile_in_zip_read != nullptr )
        unzCloseCurrentFile( file );

    ZCLOSE64( s->z_filefunc, s->filestream );
    TRYFREE( s );
    return UNZ_OK;
}

int unzGetGlobalInfo64( unzFile file, unz_global_info64 * pglobal_info )
{
    unz64_s * s;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    *pglobal_info = s->gi;
    return UNZ_OK;
}

int unzGetGlobalInfo( unzFile file, unz_global_info * pglobal_info32 )
{
    unz64_s * s;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    /* to do : check if number_entry is not truncated */
    pglobal_info32->number_entry = ( uLong )s->gi.number_entry;
    pglobal_info32->size_comment = s->gi.size_comment;
    return UNZ_OK;
}

static void unz64local_DosDateToTmuDate( ZPOS64_T ulDosDate, tm_unz * ptm )
{
    ZPOS64_T uDate;
    uDate = ( ZPOS64_T )( ulDosDate >> 16 );
    ptm->tm_mday = ( uInt )( uDate & 0x1f );
    ptm->tm_mon = ( uInt )( ( ( ( uDate ) & 0x1E0 ) / 0x20 ) - 1 );
    ptm->tm_year = ( uInt )( ( ( uDate & 0x0FE00 ) / 0x0200 ) + 1980 );

    ptm->tm_hour = ( uInt )( ( ulDosDate & 0xF800 ) / 0x800 );
    ptm->tm_min = ( uInt )( ( ulDosDate & 0x7E0 ) / 0x20 );
    ptm->tm_sec = ( uInt )( 2 * ( ulDosDate & 0x1f ) );
}

static int unz64local_GetCurrentFileInfoInternal OF( ( unzFile file,
                                                      unz_file_info64 * pfile_info,
                                                      unz_file_info64_internal
                                                      * pfile_info_internal,
                                                      char * szFileName,
                                                      uLong fileNameBufferSize,
                                                      void * extraField,
                                                      uLong extraFieldBufferSize,
                                                      char * szComment,
                                                      uLong commentBufferSize ) );

static int unz64local_GetCurrentFileInfoInternal( unzFile file,
                                                 unz_file_info64 * pfile_info,
                                                 unz_file_info64_internal
                                                 * pfile_info_internal,
                                                 char * szFileName,
                                                 uLong fileNameBufferSize,
                                                 void * extraField,
                                                 uLong extraFieldBufferSize,
                                                 char * szComment,
                                                 uLong commentBufferSize )
{
    unz64_s * s;
    unz_file_info64 file_info;
    unz_file_info64_internal file_info_internal;
    int err = UNZ_OK;
    uLong uMagic;
    long lSeek = 0;
    uLong uL;

    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    if( ZSEEK64( s->z_filefunc, s->filestream,
                 s->pos_in_central_dir + s->byte_before_the_zipfile,
                 ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        err = UNZ_ERRNO;


    /* we check the magic */
    if( err == UNZ_OK )
    {
        if( unz64local_getLong( &s->z_filefunc, s->filestream, &uMagic ) != UNZ_OK )
            err = UNZ_ERRNO;
        else if( uMagic != 0x02014b50 )
            err = UNZ_BADZIPFILE;
    }

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.version ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.version_needed ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.flag ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.compression_method ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &file_info.dosDate ) != UNZ_OK )
        err = UNZ_ERRNO;

    unz64local_DosDateToTmuDate( file_info.dosDate, &file_info.tmu_date );

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &file_info.crc ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uL ) != UNZ_OK )
        err = UNZ_ERRNO;
    file_info.compressed_size = uL;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uL ) != UNZ_OK )
        err = UNZ_ERRNO;
    file_info.uncompressed_size = uL;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.size_filename ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.size_file_extra ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.size_file_comment ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.disk_num_start ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &file_info.internal_fa ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &file_info.external_fa ) != UNZ_OK )
        err = UNZ_ERRNO;

    // relative offset of static header
    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uL ) != UNZ_OK )
        err = UNZ_ERRNO;
    file_info_internal.offset_curfile = uL;

    lSeek += file_info.size_filename;
    if( ( err == UNZ_OK ) && ( szFileName != nullptr ) )
    {
        uLong uSizeRead;
        if( file_info.size_filename < fileNameBufferSize )
        {
            *( szFileName + file_info.size_filename ) = '\0';
            uSizeRead = file_info.size_filename;
        }
        else
            uSizeRead = fileNameBufferSize;

        if( ( file_info.size_filename > 0 ) && ( fileNameBufferSize > 0 ) )
            if( ZREAD64( s->z_filefunc, s->filestream, szFileName, uSizeRead ) != uSizeRead )
                err = UNZ_ERRNO;
        lSeek -= uSizeRead;
    }

    // Read extrafield
    if( ( err == UNZ_OK ) && ( extraField != nullptr ) )
    {
        ZPOS64_T uSizeRead;
        if( file_info.size_file_extra < extraFieldBufferSize )
            uSizeRead = file_info.size_file_extra;
        else
            uSizeRead = extraFieldBufferSize;

        if( lSeek != 0 )
        {
            if( ZSEEK64( s->z_filefunc, s->filestream, lSeek, ZLIB_FILEFUNC_SEEK_CUR ) == 0 )
                lSeek = 0;
            else
                err = UNZ_ERRNO;
        }

        if( ( file_info.size_file_extra > 0 ) && ( extraFieldBufferSize > 0 ) )
            if( ZREAD64( s->z_filefunc, s->filestream, extraField, ( uLong )uSizeRead ) != uSizeRead )
                err = UNZ_ERRNO;

        lSeek += file_info.size_file_extra - ( uLong )uSizeRead;
    }
    else
        lSeek += file_info.size_file_extra;


    if( ( err == UNZ_OK ) && ( file_info.size_file_extra != 0 ) )
    {
        uLong acc = 0;

        // since lSeek now points to after the extra field we need to move back
        lSeek -= file_info.size_file_extra;

        if( lSeek != 0 )
        {
            if( ZSEEK64( s->z_filefunc, s->filestream, lSeek, ZLIB_FILEFUNC_SEEK_CUR ) == 0 )
                lSeek = 0;
            else
                err = UNZ_ERRNO;
        }

        while( acc < file_info.size_file_extra )
        {
            uLong headerId;
            uLong dataSize;

            if( unz64local_getShort( &s->z_filefunc, s->filestream, &headerId ) != UNZ_OK )
                err = UNZ_ERRNO;

            if( unz64local_getShort( &s->z_filefunc, s->filestream, &dataSize ) != UNZ_OK )
                err = UNZ_ERRNO;

            /* ZIP64 extra fields */
            if( headerId == 0x0001 )
            {
                uLong uL;

                if( file_info.uncompressed_size == MAXU32 )
                {
                    if( unz64local_getLong64( &s->z_filefunc, s->filestream, &file_info.uncompressed_size ) != UNZ_OK )
                        err = UNZ_ERRNO;
                }

                if( file_info.compressed_size == MAXU32 )
                {
                    if( unz64local_getLong64( &s->z_filefunc, s->filestream, &file_info.compressed_size ) != UNZ_OK )
                        err = UNZ_ERRNO;
                }

                if( file_info_internal.offset_curfile == MAXU32 )
                {
                    /* Relative Header offset */
                    if( unz64local_getLong64( &s->z_filefunc, s->filestream, &file_info_internal.offset_curfile ) != UNZ_OK )
                        err = UNZ_ERRNO;
                }

                if( file_info.disk_num_start == MAXU32 )
                {
                    /* Disk Start Number */
                    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uL ) != UNZ_OK )
                        err = UNZ_ERRNO;
                }

            }
            else
            {
                if( ZSEEK64( s->z_filefunc, s->filestream, dataSize, ZLIB_FILEFUNC_SEEK_CUR ) != 0 )
                    err = UNZ_ERRNO;
            }

            acc += 2 + 2 + dataSize;
        }
    }

    if( ( err == UNZ_OK ) && ( szComment != nullptr ) )
    {
        uLong uSizeRead;
        if( file_info.size_file_comment < commentBufferSize )
        {
            *( szComment + file_info.size_file_comment ) = '\0';
            uSizeRead = file_info.size_file_comment;
        }
        else
            uSizeRead = commentBufferSize;

        if( lSeek != 0 )
        {
            if( ZSEEK64( s->z_filefunc, s->filestream, lSeek, ZLIB_FILEFUNC_SEEK_CUR ) == 0 )
                lSeek = 0;
            else
                err = UNZ_ERRNO;
        }

        if( ( file_info.size_file_comment > 0 ) && ( commentBufferSize > 0 ) )
            if( ZREAD64( s->z_filefunc, s->filestream, szComment, uSizeRead ) != uSizeRead )
                err = UNZ_ERRNO;
        lSeek += file_info.size_file_comment - uSizeRead;
    }
    else
        lSeek += file_info.size_file_comment;


    if( ( err == UNZ_OK ) && ( pfile_info != nullptr ) )
        *pfile_info = file_info;

    if( ( err == UNZ_OK ) && ( pfile_info_internal != nullptr ) )
        *pfile_info_internal = file_info_internal;

    return err;
}

int unzGetCurrentFileInfo64( unzFile file,
                                            unz_file_info64 * pfile_info,
                                            char * szFileName, uLong fileNameBufferSize,
                                            void * extraField, uLong extraFieldBufferSize,
                                            char * szComment, uLong commentBufferSize )
{
    return unz64local_GetCurrentFileInfoInternal( file, pfile_info, nullptr,
                                                  szFileName, fileNameBufferSize,
                                                  extraField, extraFieldBufferSize,
                                                  szComment, commentBufferSize );
}

int unzGetCurrentFileInfo( unzFile file,
                                          unz_file_info * pfile_info,
                                          char * szFileName, uLong fileNameBufferSize,
                                          void * extraField, uLong extraFieldBufferSize,
                                          char * szComment, uLong commentBufferSize )
{
    int err;
    unz_file_info64 file_info64;
    err = unz64local_GetCurrentFileInfoInternal( file, &file_info64, nullptr,
                                                 szFileName, fileNameBufferSize,
                                                 extraField, extraFieldBufferSize,
                                                 szComment, commentBufferSize );
    if( ( err == UNZ_OK ) && ( pfile_info != nullptr ) )
    {
        pfile_info->version = file_info64.version;
        pfile_info->version_needed = file_info64.version_needed;
        pfile_info->flag = file_info64.flag;
        pfile_info->compression_method = file_info64.compression_method;
        pfile_info->dosDate = file_info64.dosDate;
        pfile_info->crc = file_info64.crc;

        pfile_info->size_filename = file_info64.size_filename;
        pfile_info->size_file_extra = file_info64.size_file_extra;
        pfile_info->size_file_comment = file_info64.size_file_comment;

        pfile_info->disk_num_start = file_info64.disk_num_start;
        pfile_info->internal_fa = file_info64.internal_fa;
        pfile_info->external_fa = file_info64.external_fa;

        pfile_info->tmu_date = file_info64.tmu_date,


            pfile_info->compressed_size = ( uLong )file_info64.compressed_size;
        pfile_info->uncompressed_size = ( uLong )file_info64.uncompressed_size;

    }
    return err;
}

int unzGoToFirstFile( unzFile file )
{
    int err = UNZ_OK;
    unz64_s * s;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    s->pos_in_central_dir = s->offset_central_dir;
    s->num_file = 0;
    err = unz64local_GetCurrentFileInfoInternal( file, &s->cur_file_info,
                                                 &s->cur_file_info_internal,
                                                 nullptr, 0, nullptr, 0, nullptr, 0 );
    s->current_file_ok = ( err == UNZ_OK );
    return err;
}

int unzGoToNextFile( unzFile  file )
{
    unz64_s * s;
    int err;

    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    if( !s->current_file_ok )
        return UNZ_END_OF_LIST_OF_FILE;
    if( s->gi.number_entry != 0xffff )    /* 2^16 files overflow hack */
        if( s->num_file + 1 == s->gi.number_entry )
            return UNZ_END_OF_LIST_OF_FILE;

    s->pos_in_central_dir += SIZECENTRALDIRITEM + s->cur_file_info.size_filename +
        s->cur_file_info.size_file_extra + s->cur_file_info.size_file_comment;
    s->num_file++;
    err = unz64local_GetCurrentFileInfoInternal( file, &s->cur_file_info,
                                                 &s->cur_file_info_internal,
                                                 nullptr, 0, nullptr, 0, nullptr, 0 );
    s->current_file_ok = ( err == UNZ_OK );
    return err;
}

int unzLocateFile( unzFile file, const char * szFileName, int iCaseSensitivity )
{
    unz64_s * s;
    int err;

    /* We remember the 'current' position in the file so that we can jump
     * back there if we fail.
     */
    unz_file_info64 cur_file_infoSaved;
    unz_file_info64_internal cur_file_info_internalSaved;
    ZPOS64_T num_fileSaved;
    ZPOS64_T pos_in_central_dirSaved;


    if( file == nullptr )
        return UNZ_PARAMERROR;

    if( strlen( szFileName ) >= UNZ_MAXFILENAMEINZIP )
        return UNZ_PARAMERROR;

    s = ( unz64_s * )file;
    if( !s->current_file_ok )
        return UNZ_END_OF_LIST_OF_FILE;

    /* Save the current state */
    num_fileSaved = s->num_file;
    pos_in_central_dirSaved = s->pos_in_central_dir;
    cur_file_infoSaved = s->cur_file_info;
    cur_file_info_internalSaved = s->cur_file_info_internal;

    err = unzGoToFirstFile( file );

    while( err == UNZ_OK )
    {
        char szCurrentFileName[UNZ_MAXFILENAMEINZIP + 1];
        err = unzGetCurrentFileInfo64( file, nullptr,
                                       szCurrentFileName, sizeof( szCurrentFileName ) - 1,
                                       nullptr, 0, nullptr, 0 );
        if( err == UNZ_OK )
        {
            if( unzStringFileNameCompare( szCurrentFileName,
                                          szFileName, iCaseSensitivity ) == 0 )
                return UNZ_OK;
            err = unzGoToNextFile( file );
        }
    }

    /* We failed, so restore the state of the 'current file' to where we
     * were.
     */
    s->num_file = num_fileSaved;
    s->pos_in_central_dir = pos_in_central_dirSaved;
    s->cur_file_info = cur_file_infoSaved;
    s->cur_file_info_internal = cur_file_info_internalSaved;
    return err;
}

int unzGetFilePos64( unzFile file, unz64_file_pos * file_pos )
{
    unz64_s * s;

    if( file == nullptr || file_pos == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    if( !s->current_file_ok )
        return UNZ_END_OF_LIST_OF_FILE;

    file_pos->pos_in_zip_directory = s->pos_in_central_dir;
    file_pos->num_of_file = s->num_file;

    return UNZ_OK;
}

int unzGetFilePos(
    unzFile file,
    unz_file_pos * file_pos )
{
    unz64_file_pos file_pos64;
    int err = unzGetFilePos64( file, &file_pos64 );
    if( err == UNZ_OK )
    {
        file_pos->pos_in_zip_directory = ( uLong )file_pos64.pos_in_zip_directory;
        file_pos->num_of_file = ( uLong )file_pos64.num_of_file;
    }
    return err;
}

int unzGoToFilePos64( unzFile file, const unz64_file_pos * file_pos )
{
    unz64_s * s;
    int err;

    if( file == nullptr || file_pos == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;

    /* jump to the right spot */
    s->pos_in_central_dir = file_pos->pos_in_zip_directory;
    s->num_file = file_pos->num_of_file;

    /* set the current file */
    err = unz64local_GetCurrentFileInfoInternal( file, &s->cur_file_info,
                                                 &s->cur_file_info_internal,
                                                 nullptr, 0, nullptr, 0, nullptr, 0 );
    /* return results */
    s->current_file_ok = ( err == UNZ_OK );
    return err;
}

int unzGoToFilePos(
    unzFile file,
    unz_file_pos * file_pos )
{
    unz64_file_pos file_pos64;
    if( file_pos == nullptr )
        return UNZ_PARAMERROR;

    file_pos64.pos_in_zip_directory = file_pos->pos_in_zip_directory;
    file_pos64.num_of_file = file_pos->num_of_file;
    return unzGoToFilePos64( file, &file_pos64 );
}

static int unz64local_CheckCurrentFileCoherencyHeader( unz64_s * s, uInt * piSizeVar,
                                                      ZPOS64_T * poffset_local_extrafield,
                                                      uInt * psize_local_extrafield )
{
    uLong uMagic, uData, uFlags;
    uLong size_filename;
    uLong size_extra_field;
    int err = UNZ_OK;

    *piSizeVar = 0;
    *poffset_local_extrafield = 0;
    *psize_local_extrafield = 0;

    if( ZSEEK64( s->z_filefunc, s->filestream, s->cur_file_info_internal.offset_curfile +
                 s->byte_before_the_zipfile, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return UNZ_ERRNO;


    if( err == UNZ_OK )
    {
        if( unz64local_getLong( &s->z_filefunc, s->filestream, &uMagic ) != UNZ_OK )
            err = UNZ_ERRNO;
        else if( uMagic != 0x04034b50 )
            err = UNZ_BADZIPFILE;
    }

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK )
        err = UNZ_ERRNO;
    /*
        else if ((err==UNZ_OK) && (uData!=s->cur_file_info.wVersion))
            err=UNZ_BADZIPFILE;
    */
    if( unz64local_getShort( &s->z_filefunc, s->filestream, &uFlags ) != UNZ_OK )
        err = UNZ_ERRNO;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK )
        err = UNZ_ERRNO;
    else if( ( err == UNZ_OK ) && ( uData != s->cur_file_info.compression_method ) )
        err = UNZ_BADZIPFILE;

    if( ( err == UNZ_OK ) && ( s->cur_file_info.compression_method != 0 ) &&
        /* #ifdef HAVE_BZIP2 */
        ( s->cur_file_info.compression_method != Z_BZIP2ED ) &&
        /* #endif */
        ( s->cur_file_info.compression_method != Z_DEFLATED ) )
        err = UNZ_BADZIPFILE;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK ) /* date/time */
        err = UNZ_ERRNO;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK ) /* crc */
        err = UNZ_ERRNO;
    else if( ( err == UNZ_OK ) && ( uData != s->cur_file_info.crc ) && ( ( uFlags & 8 ) == 0 ) )
        err = UNZ_BADZIPFILE;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK ) /* size compr */
        err = UNZ_ERRNO;
    else if( uData != 0xFFFFFFFF && ( err == UNZ_OK ) && ( uData != s->cur_file_info.compressed_size ) && ( ( uFlags & 8 ) == 0 ) )
        err = UNZ_BADZIPFILE;

    if( unz64local_getLong( &s->z_filefunc, s->filestream, &uData ) != UNZ_OK ) /* size uncompr */
        err = UNZ_ERRNO;
    else if( uData != 0xFFFFFFFF && ( err == UNZ_OK ) && ( uData != s->cur_file_info.uncompressed_size ) && ( ( uFlags & 8 ) == 0 ) )
        err = UNZ_BADZIPFILE;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &size_filename ) != UNZ_OK )
        err = UNZ_ERRNO;
    else if( ( err == UNZ_OK ) && ( size_filename != s->cur_file_info.size_filename ) )
        err = UNZ_BADZIPFILE;

    *piSizeVar += ( uInt )size_filename;

    if( unz64local_getShort( &s->z_filefunc, s->filestream, &size_extra_field ) != UNZ_OK )
        err = UNZ_ERRNO;
    *poffset_local_extrafield = s->cur_file_info_internal.offset_curfile +
        SIZEZIPLOCALHEADER + size_filename;
    *psize_local_extrafield = ( uInt )size_extra_field;

    *piSizeVar += ( uInt )size_extra_field;

    return err;
}

int unzOpenCurrentFile3( unzFile file, int * method,
                                        int * level, int raw, const char * password )
{
    int err = UNZ_OK;
    uInt iSizeVar;
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    ZPOS64_T offset_local_extrafield;  /* offset of the static extra field */
    uInt  size_local_extrafield;    /* size of the static extra field */
#    ifndef NOUNCRYPT
    char source[12];
#    else
    if( password != nullptr )
        return UNZ_PARAMERROR;
#    endif

    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    if( !s->current_file_ok )
        return UNZ_PARAMERROR;

    if( s->pfile_in_zip_read != nullptr )
        unzCloseCurrentFile( file );

    if( unz64local_CheckCurrentFileCoherencyHeader( s, &iSizeVar, &offset_local_extrafield, &size_local_extrafield ) != UNZ_OK )
        return UNZ_BADZIPFILE;

    pfile_in_zip_read_info = ( file_in_zip64_read_info_s * )ALLOC( sizeof( file_in_zip64_read_info_s ) );
    if( pfile_in_zip_read_info == nullptr )
        return UNZ_INTERNALERROR;

    pfile_in_zip_read_info->read_buffer = ( char * )ALLOC( UNZ_BUFSIZE );
    pfile_in_zip_read_info->offset_local_extrafield = offset_local_extrafield;
    pfile_in_zip_read_info->size_local_extrafield = size_local_extrafield;
    pfile_in_zip_read_info->pos_local_extrafield = 0;
    pfile_in_zip_read_info->raw = raw;

    if( pfile_in_zip_read_info->read_buffer == nullptr )
    {
        TRYFREE( pfile_in_zip_read_info );
        return UNZ_INTERNALERROR;
    }

    pfile_in_zip_read_info->stream_initialised = 0;

    if( method != nullptr )
        *method = ( int )s->cur_file_info.compression_method;

    if( level != nullptr )
    {
        *level = 6;
        switch( s->cur_file_info.flag & 0x06 )
        {
        case 6: *level = 1; break;
        case 4: *level = 2; break;
        case 2: *level = 9; break;
        }
    }

    if( ( s->cur_file_info.compression_method != 0 ) &&
        /* #ifdef HAVE_BZIP2 */
        ( s->cur_file_info.compression_method != Z_BZIP2ED ) &&
        /* #endif */
        ( s->cur_file_info.compression_method != Z_DEFLATED ) )

        err = UNZ_BADZIPFILE;

    pfile_in_zip_read_info->crc32_wait = s->cur_file_info.crc;
    pfile_in_zip_read_info->crc32 = 0;
    pfile_in_zip_read_info->total_out_64 = 0;
    pfile_in_zip_read_info->compression_method = s->cur_file_info.compression_method;
    pfile_in_zip_read_info->filestream = s->filestream;
    pfile_in_zip_read_info->z_filefunc = s->z_filefunc;
    pfile_in_zip_read_info->byte_before_the_zipfile = s->byte_before_the_zipfile;

    pfile_in_zip_read_info->stream.total_out = 0;

    if( ( s->cur_file_info.compression_method == Z_BZIP2ED ) && ( !raw ) )
    {
    #ifdef HAVE_BZIP2
        pfile_in_zip_read_info->bstream.bzalloc = ( void * ( * ) ( void *, int, int ) )0;
        pfile_in_zip_read_info->bstream.bzfree = ( free_func )0;
        pfile_in_zip_read_info->bstream.opaque = ( voidpf )0;
        pfile_in_zip_read_info->bstream.state = ( voidpf )0;

        pfile_in_zip_read_info->stream.zalloc = ( alloc_func )0;
        pfile_in_zip_read_info->stream.zfree = ( free_func )0;
        pfile_in_zip_read_info->stream.opaque = ( voidpf )0;
        pfile_in_zip_read_info->stream.next_in = ( voidpf )0;
        pfile_in_zip_read_info->stream.avail_in = 0;

        err = BZ2_bzDecompressInit( &pfile_in_zip_read_info->bstream, 0, 0 );
        if( err == Z_OK )
            pfile_in_zip_read_info->stream_initialised = Z_BZIP2ED;
        else
        {
            TRYFREE( pfile_in_zip_read_info );
            return err;
        }
    #else
        pfile_in_zip_read_info->raw = 1;
    #endif
    }
    else if( ( s->cur_file_info.compression_method == Z_DEFLATED ) && ( !raw ) )
    {
        pfile_in_zip_read_info->stream.zalloc = ( alloc_func )0;
        pfile_in_zip_read_info->stream.zfree = ( free_func )0;
        pfile_in_zip_read_info->stream.opaque = ( voidpf )0;
        pfile_in_zip_read_info->stream.next_in = 0;
        pfile_in_zip_read_info->stream.avail_in = 0;

        err = inflateInit2( &pfile_in_zip_read_info->stream, -MAX_WBITS );
        if( err == Z_OK )
            pfile_in_zip_read_info->stream_initialised = Z_DEFLATED;
        else
        {
            TRYFREE( pfile_in_zip_read_info );
            return err;
        }
        /* windowBits is passed < 0 to tell that there is no zlib header.
         * Note that in this case inflate *requires* an extra "dummy" byte
         * after the compressed stream in order to complete decompression and
         * return Z_STREAM_END.
         * In unzip, i don't wait absolutely Z_STREAM_END because I known the
         * size of both compressed and uncompressed data
         */
    }
    pfile_in_zip_read_info->rest_read_compressed =
        s->cur_file_info.compressed_size;
    pfile_in_zip_read_info->rest_read_uncompressed =
        s->cur_file_info.uncompressed_size;


    pfile_in_zip_read_info->pos_in_zipfile =
        s->cur_file_info_internal.offset_curfile + SIZEZIPLOCALHEADER +
        iSizeVar;

    pfile_in_zip_read_info->stream.avail_in = ( uInt )0;

    s->pfile_in_zip_read = pfile_in_zip_read_info;
    s->encrypted = 0;

#    ifndef NOUNCRYPT
    if( password != nullptr )
    {
        int i;
        s->pcrc_32_tab = get_crc_table();
        init_keys( password, s->keys, s->pcrc_32_tab );
        if( ZSEEK64( s->z_filefunc, s->filestream,
                     s->pfile_in_zip_read->pos_in_zipfile +
                     s->pfile_in_zip_read->byte_before_the_zipfile,
                     SEEK_SET ) != 0 )
            return UNZ_INTERNALERROR;
        if( ZREAD64( s->z_filefunc, s->filestream, source, 12 ) < 12 )
            return UNZ_INTERNALERROR;

        for( i = 0; i < 12; i++ )
            zdecode( s->keys, s->pcrc_32_tab, source[i] );

        s->pfile_in_zip_read->pos_in_zipfile += 12;
        s->encrypted = 1;
    }
#    endif


    return UNZ_OK;
}

int unzOpenCurrentFile( unzFile file )
{
    return unzOpenCurrentFile3( file, nullptr, nullptr, 0, nullptr );
}

int unzOpenCurrentFilePassword( unzFile file, const char * password )
{
    return unzOpenCurrentFile3( file, nullptr, nullptr, 0, password );
}

int unzOpenCurrentFile2( unzFile file, int * method, int * level, int raw )
{
    return unzOpenCurrentFile3( file, method, level, raw, nullptr );
}

ZPOS64_T unzGetCurrentFileZStreamPos64( unzFile file )
{
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    s = ( unz64_s * )file;
    if( file == nullptr )
        return 0; //UNZ_PARAMERROR;
    pfile_in_zip_read_info = s->pfile_in_zip_read;
    if( pfile_in_zip_read_info == nullptr )
        return 0; //UNZ_PARAMERROR;
    return pfile_in_zip_read_info->pos_in_zipfile +
        pfile_in_zip_read_info->byte_before_the_zipfile;
}

int unzReadCurrentFile( unzFile file, voidp buf, unsigned len )
{
    int err = UNZ_OK;
    uInt iRead = 0;
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return UNZ_PARAMERROR;


    if( pfile_in_zip_read_info->read_buffer == nullptr )
        return UNZ_END_OF_LIST_OF_FILE;
    if( len == 0 )
        return 0;

    pfile_in_zip_read_info->stream.next_out = ( Bytef * )buf;

    pfile_in_zip_read_info->stream.avail_out = ( uInt )len;

    if( ( len > pfile_in_zip_read_info->rest_read_uncompressed ) &&
        ( !( pfile_in_zip_read_info->raw ) ) )
        pfile_in_zip_read_info->stream.avail_out =
        ( uInt )pfile_in_zip_read_info->rest_read_uncompressed;

    if( ( len > pfile_in_zip_read_info->rest_read_compressed +
          pfile_in_zip_read_info->stream.avail_in ) &&
        ( pfile_in_zip_read_info->raw ) )
        pfile_in_zip_read_info->stream.avail_out =
        ( uInt )pfile_in_zip_read_info->rest_read_compressed +
        pfile_in_zip_read_info->stream.avail_in;

    while( pfile_in_zip_read_info->stream.avail_out > 0 )
    {
        if( ( pfile_in_zip_read_info->stream.avail_in == 0 ) &&
            ( pfile_in_zip_read_info->rest_read_compressed > 0 ) )
        {
            uInt uReadThis = UNZ_BUFSIZE;
            if( pfile_in_zip_read_info->rest_read_compressed < uReadThis )
                uReadThis = ( uInt )pfile_in_zip_read_info->rest_read_compressed;
            if( uReadThis == 0 )
                return UNZ_EOF;
            if( ZSEEK64( pfile_in_zip_read_info->z_filefunc,
                         pfile_in_zip_read_info->filestream,
                         pfile_in_zip_read_info->pos_in_zipfile +
                         pfile_in_zip_read_info->byte_before_the_zipfile,
                         ZLIB_FILEFUNC_SEEK_SET ) != 0 )
                return UNZ_ERRNO;
            if( ZREAD64( pfile_in_zip_read_info->z_filefunc,
                         pfile_in_zip_read_info->filestream,
                         pfile_in_zip_read_info->read_buffer,
                         uReadThis ) != uReadThis )
                return UNZ_ERRNO;


        #            ifndef NOUNCRYPT
            if( s->encrypted )
            {
                uInt i;
                for( i = 0; i < uReadThis; i++ )
                    pfile_in_zip_read_info->read_buffer[i] =
                    zdecode( s->keys, s->pcrc_32_tab,
                             pfile_in_zip_read_info->read_buffer[i] );
            }
        #            endif


            pfile_in_zip_read_info->pos_in_zipfile += uReadThis;

            pfile_in_zip_read_info->rest_read_compressed -= uReadThis;

            pfile_in_zip_read_info->stream.next_in =
                ( Bytef * )pfile_in_zip_read_info->read_buffer;
            pfile_in_zip_read_info->stream.avail_in = ( uInt )uReadThis;
        }

        if( ( pfile_in_zip_read_info->compression_method == 0 ) || ( pfile_in_zip_read_info->raw ) )
        {
            uInt uDoCopy, i;

            if( ( pfile_in_zip_read_info->stream.avail_in == 0 ) &&
                ( pfile_in_zip_read_info->rest_read_compressed == 0 ) )
                return ( iRead == 0 ) ? UNZ_EOF : iRead;

            if( pfile_in_zip_read_info->stream.avail_out <
                pfile_in_zip_read_info->stream.avail_in )
                uDoCopy = pfile_in_zip_read_info->stream.avail_out;
            else
                uDoCopy = pfile_in_zip_read_info->stream.avail_in;

            for( i = 0; i < uDoCopy; i++ )
                *( pfile_in_zip_read_info->stream.next_out + i ) =
                *( pfile_in_zip_read_info->stream.next_in + i );

            pfile_in_zip_read_info->total_out_64 = pfile_in_zip_read_info->total_out_64 + uDoCopy;

            pfile_in_zip_read_info->crc32 = crc32( pfile_in_zip_read_info->crc32,
                                                   pfile_in_zip_read_info->stream.next_out,
                                                   uDoCopy );
            pfile_in_zip_read_info->rest_read_uncompressed -= uDoCopy;
            pfile_in_zip_read_info->stream.avail_in -= uDoCopy;
            pfile_in_zip_read_info->stream.avail_out -= uDoCopy;
            pfile_in_zip_read_info->stream.next_out += uDoCopy;
            pfile_in_zip_read_info->stream.next_in += uDoCopy;
            pfile_in_zip_read_info->stream.total_out += uDoCopy;
            iRead += uDoCopy;
        }
        else if( pfile_in_zip_read_info->compression_method == Z_BZIP2ED )
        {
        #ifdef HAVE_BZIP2
            uLong uTotalOutBefore, uTotalOutAfter;
            const Bytef * bufBefore;
            uLong uOutThis;

            pfile_in_zip_read_info->bstream.next_in = ( char * )pfile_in_zip_read_info->stream.next_in;
            pfile_in_zip_read_info->bstream.avail_in = pfile_in_zip_read_info->stream.avail_in;
            pfile_in_zip_read_info->bstream.total_in_lo32 = pfile_in_zip_read_info->stream.total_in;
            pfile_in_zip_read_info->bstream.total_in_hi32 = 0;
            pfile_in_zip_read_info->bstream.next_out = ( char * )pfile_in_zip_read_info->stream.next_out;
            pfile_in_zip_read_info->bstream.avail_out = pfile_in_zip_read_info->stream.avail_out;
            pfile_in_zip_read_info->bstream.total_out_lo32 = pfile_in_zip_read_info->stream.total_out;
            pfile_in_zip_read_info->bstream.total_out_hi32 = 0;

            uTotalOutBefore = pfile_in_zip_read_info->bstream.total_out_lo32;
            bufBefore = ( const Bytef * )pfile_in_zip_read_info->bstream.next_out;

            err = BZ2_bzDecompress( &pfile_in_zip_read_info->bstream );

            uTotalOutAfter = pfile_in_zip_read_info->bstream.total_out_lo32;
            uOutThis = uTotalOutAfter - uTotalOutBefore;

            pfile_in_zip_read_info->total_out_64 = pfile_in_zip_read_info->total_out_64 + uOutThis;

            pfile_in_zip_read_info->crc32 = crc32( pfile_in_zip_read_info->crc32, bufBefore, ( uInt )( uOutThis ) );
            pfile_in_zip_read_info->rest_read_uncompressed -= uOutThis;
            iRead += ( uInt )( uTotalOutAfter - uTotalOutBefore );

            pfile_in_zip_read_info->stream.next_in = ( Bytef * )pfile_in_zip_read_info->bstream.next_in;
            pfile_in_zip_read_info->stream.avail_in = pfile_in_zip_read_info->bstream.avail_in;
            pfile_in_zip_read_info->stream.total_in = pfile_in_zip_read_info->bstream.total_in_lo32;
            pfile_in_zip_read_info->stream.next_out = ( Bytef * )pfile_in_zip_read_info->bstream.next_out;
            pfile_in_zip_read_info->stream.avail_out = pfile_in_zip_read_info->bstream.avail_out;
            pfile_in_zip_read_info->stream.total_out = pfile_in_zip_read_info->bstream.total_out_lo32;

            if( err == BZ_STREAM_END )
                return ( iRead == 0 ) ? UNZ_EOF : iRead;
            if( err != BZ_OK )
                break;
        #endif
        } // end Z_BZIP2ED
        else
        {
            ZPOS64_T uTotalOutBefore, uTotalOutAfter;
            const Bytef * bufBefore;
            ZPOS64_T uOutThis;
            int flush = Z_SYNC_FLUSH;

            uTotalOutBefore = pfile_in_zip_read_info->stream.total_out;
            bufBefore = pfile_in_zip_read_info->stream.next_out;

            /*
            if ((pfile_in_zip_read_info->rest_read_uncompressed ==
                     pfile_in_zip_read_info->stream.avail_out) &&
                (pfile_in_zip_read_info->rest_read_compressed == 0))
                flush = Z_FINISH;
            */
            err = inflate( &pfile_in_zip_read_info->stream, flush );

            if( ( err >= 0 ) && ( pfile_in_zip_read_info->stream.msg != nullptr ) )
                err = Z_DATA_ERROR;

            uTotalOutAfter = pfile_in_zip_read_info->stream.total_out;
            uOutThis = uTotalOutAfter - uTotalOutBefore;

            pfile_in_zip_read_info->total_out_64 = pfile_in_zip_read_info->total_out_64 + uOutThis;

            pfile_in_zip_read_info->crc32 =
                crc32( pfile_in_zip_read_info->crc32, bufBefore,
                       ( uInt )( uOutThis ) );

            pfile_in_zip_read_info->rest_read_uncompressed -=
                uOutThis;

            iRead += ( uInt )( uTotalOutAfter - uTotalOutBefore );

            if( err == Z_STREAM_END )
                return ( iRead == 0 ) ? UNZ_EOF : iRead;
            if( err != Z_OK )
                break;
        }
    }

    if( err == Z_OK )
        return iRead;
    return err;
}

z_off_t unztell( unzFile file )
{
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return UNZ_PARAMERROR;

    return ( z_off_t )pfile_in_zip_read_info->stream.total_out;
}

ZPOS64_T unztell64( unzFile file )
{

    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    if( file == nullptr )
        return ( ZPOS64_T )-1;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return ( ZPOS64_T )-1;

    return pfile_in_zip_read_info->total_out_64;
}

int unzeof( unzFile file )
{
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return UNZ_PARAMERROR;

    if( pfile_in_zip_read_info->rest_read_uncompressed == 0 )
        return 1;
    else
        return 0;
}

int unzGetLocalExtrafield( unzFile file, voidp buf, unsigned len )
{
    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    uInt read_now;
    ZPOS64_T size_to_read;

    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return UNZ_PARAMERROR;

    size_to_read = ( pfile_in_zip_read_info->size_local_extrafield -
                     pfile_in_zip_read_info->pos_local_extrafield );

    if( buf == nullptr )
        return ( int )size_to_read;

    if( len > size_to_read )
        read_now = ( uInt )size_to_read;
    else
        read_now = ( uInt )len;

    if( read_now == 0 )
        return 0;

    if( ZSEEK64( pfile_in_zip_read_info->z_filefunc,
                 pfile_in_zip_read_info->filestream,
                 pfile_in_zip_read_info->offset_local_extrafield +
                 pfile_in_zip_read_info->pos_local_extrafield,
                 ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return UNZ_ERRNO;

    if( ZREAD64( pfile_in_zip_read_info->z_filefunc,
                 pfile_in_zip_read_info->filestream,
                 buf, read_now ) != read_now )
        return UNZ_ERRNO;

    return ( int )read_now;
}

int unzCloseCurrentFile( unzFile file )
{
    int err = UNZ_OK;

    unz64_s * s;
    file_in_zip64_read_info_s * pfile_in_zip_read_info;
    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    pfile_in_zip_read_info = s->pfile_in_zip_read;

    if( pfile_in_zip_read_info == nullptr )
        return UNZ_PARAMERROR;


    if( ( pfile_in_zip_read_info->rest_read_uncompressed == 0 ) &&
        ( !pfile_in_zip_read_info->raw ) )
    {
        if( pfile_in_zip_read_info->crc32 != pfile_in_zip_read_info->crc32_wait )
            err = UNZ_CRCERROR;
    }


    TRYFREE( pfile_in_zip_read_info->read_buffer );
    pfile_in_zip_read_info->read_buffer = nullptr;
    if( pfile_in_zip_read_info->stream_initialised == Z_DEFLATED )
        inflateEnd( &pfile_in_zip_read_info->stream );
#ifdef HAVE_BZIP2
    else if( pfile_in_zip_read_info->stream_initialised == Z_BZIP2ED )
        BZ2_bzDecompressEnd( &pfile_in_zip_read_info->bstream );
#endif


    pfile_in_zip_read_info->stream_initialised = 0;
    TRYFREE( pfile_in_zip_read_info );

    s->pfile_in_zip_read = nullptr;

    return err;
}

int unzGetGlobalComment( unzFile file, char * szComment, uLong uSizeBuf )
{
    unz64_s * s;
    uLong uReadThis;
    if( file == nullptr )
        return ( int )UNZ_PARAMERROR;
    s = ( unz64_s * )file;

    uReadThis = uSizeBuf;
    if( uReadThis > s->gi.size_comment )
        uReadThis = s->gi.size_comment;

    if( ZSEEK64( s->z_filefunc, s->filestream, s->central_pos + 22, ZLIB_FILEFUNC_SEEK_SET ) != 0 )
        return UNZ_ERRNO;

    if( uReadThis > 0 )
    {
        *szComment = '\0';
        if( ZREAD64( s->z_filefunc, s->filestream, szComment, uReadThis ) != uReadThis )
            return UNZ_ERRNO;
    }

    if( ( szComment != nullptr ) && ( uSizeBuf > s->gi.size_comment ) )
        *( szComment + s->gi.size_comment ) = '\0';
    return ( int )uReadThis;
}

ZPOS64_T unzGetOffset64( unzFile file )
{
    unz64_s * s;

    if( file == nullptr )
        return 0; //UNZ_PARAMERROR;
    s = ( unz64_s * )file;
    if( !s->current_file_ok )
        return 0;
    if( s->gi.number_entry != 0 && s->gi.number_entry != 0xffff )
        if( s->num_file == s->gi.number_entry )
            return 0;
    return s->pos_in_central_dir;
}

uLong unzGetOffset( unzFile file )
{
    ZPOS64_T offset64;

    if( file == nullptr )
        return 0; //UNZ_PARAMERROR;
    offset64 = unzGetOffset64( file );
    return ( uLong )offset64;
}

int unzSetOffset64( unzFile file, ZPOS64_T pos )
{
    unz64_s * s;
    int err;

    if( file == nullptr )
        return UNZ_PARAMERROR;
    s = ( unz64_s * )file;

    s->pos_in_central_dir = pos;
    s->num_file = s->gi.number_entry;      /* hack */
    err = unz64local_GetCurrentFileInfoInternal( file, &s->cur_file_info,
                                                 &s->cur_file_info_internal,
                                                 nullptr, 0, nullptr, 0, nullptr, 0 );
    s->current_file_ok = ( err == UNZ_OK );
    return err;
}

int unzSetOffset( unzFile file, uLong pos )
{
    return unzSetOffset64( file, pos );
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// tool

bool isLargeFile( std::istream & input_stream )
{
	ZPOS64_T pos = 0;
	input_stream.seekg( 0, std::ios::end );
	pos = input_stream.tellg();
	input_stream.seekg( 0 );

	return pos >= 0xffffffff;
}

void getFileCrc( std::istream & input_stream, std::vector<char> & buff, unsigned long & result_crc )
{
	unsigned long calculate_crc = 0;
	unsigned long size_read = 0;
	unsigned long total_read = 0;

	do
	{
		input_stream.read( buff.data(), buff.size() );
		size_read = ( unsigned long )input_stream.gcount();

		if( size_read > 0 )
			calculate_crc = crc32( calculate_crc, ( const unsigned char * )buff.data(), size_read );

		total_read += size_read;

	} while( size_read > 0 );

	input_stream.clear();
	input_stream.seekg( 0, std::ios_base::beg );
	result_crc = calculate_crc;
}

//////////////////////////////////////////////////////////////////////////



struct XE::Zipper::Private
{
    bool _IsOpen = false;
    zipFile _Zip = nullptr;
};

XE::Zipper::Zipper()
    :_p( new Private )
{

}

XE::Zipper::Zipper( const std::string & zipname, const std::string & password /*= "" */ )
	: _p( new Private )
{
    Open( zipname, password );
}

XE::Zipper::~Zipper()
{
    delete _p;
}

bool XE::Zipper::Add( std::istream & source, const std::string & name, const std::string & password /*= "" */ )
{
    if( !_p->_Zip )
    {
        return false;
    }

	int compressLevel = 9;
	int zip64 = 0;
	int size_buf = 8192;
	int err = ZIP_OK;
	unsigned long crcFile = 0;

	zip_fileinfo zi = { 0 };

    std::tm timestamp = {};

	zi.tmz_date.tm_sec = timestamp.tm_sec;
	zi.tmz_date.tm_min = timestamp.tm_min;
	zi.tmz_date.tm_hour = timestamp.tm_hour;
	zi.tmz_date.tm_mday = timestamp.tm_mday;
	zi.tmz_date.tm_mon = timestamp.tm_mon;
	zi.tmz_date.tm_year = timestamp.tm_year;

	size_t size_read;

	std::vector<char> buff;
	buff.resize( size_buf );

    if( name.empty() )
    {
        return false;
    }

	zip64 = ( int )isLargeFile( source );
	if( password.empty() )
		err = zipOpenNewFileInZip64( _p->_Zip,
									 name.c_str(),
									 &zi,
									 nullptr,
									 0,
									 nullptr,
									 0,
									 nullptr,
									 ( compressLevel != 0 ) ? Z_DEFLATED : 0,
									 compressLevel,
									 zip64 );
	else
	{
		getFileCrc( source, buff, crcFile );
		err = zipOpenNewFileInZip3_64( _p->_Zip,
									   name.c_str(),
									   &zi,
									   nullptr,
									   0,
									   nullptr,
									   0,
									   nullptr,
									   ( compressLevel != 0 ) ? Z_DEFLATED : 0,
									   compressLevel,
									   0,
									   -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
									   password.c_str(),
									   crcFile,
									   zip64 );
	}

	if( ZIP_OK == err )
	{
		do
		{
			err = ZIP_OK;
			source.read( buff.data(), buff.size() );
			size_read = ( size_t )source.gcount();
            if( size_read < buff.size() && !source.eof() && !source.good() )
            {
                err = ZIP_ERRNO;
            }

            if( size_read > 0 )
            {
                err = zipWriteInFileInZip( _p->_Zip, buff.data(), ( unsigned int )size_read );
            }

		} while( ( err == ZIP_OK ) && ( size_read > 0 ) );
	}
    else
    {
        return false;
    }

    if( ZIP_OK == err )
    {
        err = zipCloseFileInZip( _p->_Zip );
    }

	return ZIP_OK == err;
}

bool XE::Zipper::Open( const std::string & zipname, const std::string & password /*= "" */ )
{
    if( _p->_Zip = zipOpen64( zipname.c_str(), APPEND_STATUS_ADDINZIP ) )
    {
        _p->_IsOpen = true;
    }

    return _p->_Zip != nullptr;
}

bool XE::Zipper::IsOpen() const
{
    return _p->_IsOpen;
}

void XE::Zipper::Close()
{
	if( _p->_Zip != nullptr )
	{
		zipClose( _p->_Zip, nullptr );
		_p->_Zip = nullptr;
	}

	_p->_IsOpen = false;
}



struct XE::Unzipper::Private
{
    bool _IsOpen = false;
    zipFile _Zip = nullptr;
};

XE::Unzipper::Unzipper()
    :_p( new Private )
{

}

XE::Unzipper::Unzipper( const std::string & zipname, const std::string & password /*= "" */ )
	: _p( new Private )
{
    Open( zipname, password );
}

XE::Unzipper::~Unzipper()
{
    delete _p;
}

bool XE::Unzipper::GetEntries( XE::Array< Entry > & entries ) const
{
	int err = unzGoToFirstFile( _p->_Zip );
	if( UNZ_OK == err )
	{
		unz_file_info64 file_info = { 0 };
		char filename_inzip[256] = { 0 };

		do
		{
			int err = unzGetCurrentFileInfo64( _p->_Zip, &file_info, filename_inzip, sizeof( filename_inzip ), NULL, 0, NULL, 0 );
            if( UNZ_OK != err )
            {
                return false;
            }

            Entry entryinfo;

            entryinfo.name = filename_inzip;
            entryinfo.compressed_size = file_info.compressed_size;
            entryinfo.uncompressed_size = file_info.uncompressed_size;

			entries.push_back( entryinfo );

			err = unzGoToNextFile( _p->_Zip );

		} while( UNZ_OK == err );

        if( UNZ_END_OF_LIST_OF_FILE != err && UNZ_OK != err )
        {
            return false;
        }
	}

    return true;
}

bool XE::Unzipper::ExtractEntiy( const std::string & name )
{
    return unzLocateFile( _p->_Zip, name.c_str(), 0 ) == UNZ_OK;
}

bool XE::Unzipper::GetEntryData( const std::string & name, std::ostream & stream, const std::string & password /*= "" */ )
{
    if( ExtractEntiy( name ) )
	{
		size_t err = unzOpenCurrentFilePassword( _p->_Zip, password.c_str() );
		if( UNZ_OK != err )
		{
			return false;
		}

		XE::Array<char> buffer( XE::MemoryResource::GetStackMemoryResource() );
		buffer.resize( 8192 );

		do
		{
			err = unzReadCurrentFile( _p->_Zip, buffer.data(), ( unsigned int )buffer.size() );
			if( err < 0 || err == 0 )
				break;

			stream.write( buffer.data(), err );
			if( !stream.good() )
			{
				err = UNZ_ERRNO;
				break;
			}

		} while( err > UNZ_OK );

		stream.flush();

		return true;
    }

    return false;
}

bool XE::Unzipper::Open( const std::string & zipname, const std::string & password /*= "" */ )
{
	if( _p->_Zip = unzOpen64( zipname.c_str() ) )
	{
		_p->_IsOpen = true;
	}

	return _p->_Zip != nullptr;
}

bool XE::Unzipper::IsOpen() const
{
    return _p->_IsOpen;
}

void XE::Unzipper::Close()
{
	if( _p->_Zip != nullptr )
	{
		zipClose( _p->_Zip, nullptr );
		_p->_Zip = nullptr;
	}

	_p->_IsOpen = false;
}
