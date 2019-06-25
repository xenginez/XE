/*!
 * \file   Config.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CONFIG_H__851B77A2_E78D_4E14_91A6_D6317250A486
#define __CONFIG_H__851B77A2_E78D_4E14_91A6_D6317250A486

/////////////////////////////////////////////////////////////////////////////////////////
/// CPU
#define CPU_ARM 1
#define CPU_PPC 2
#define CPU_X86 3
#define CPU_RISC 4
#define CPU_MIPSV 5
#define CPU_JIT 6

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#define CPU CPU_ARM
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#define CPU CPU_PPC
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
#define CPU CPU_X86
#elif defined(__MIPSEL__) || defined(__mips_isa_rev) || defined(__mips64)
#define CPU CPU_MIPS
#elif defined(__riscv) || defined(__riscv__) || defined(RISCVEL)
#define CPU CPU_RISCV
#else
#define CPU CPU_JIT
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// ENDIAN
#define ENDIAN_BIG    1
#define ENDIAN_LITTLE 2

#if CPU == CPU_PPC
#if _LITTLE_ENDIAN
#define ENDIAN ENDIAN_LITTLE
#else
#define ENDIAN ENDIAN_BIG
#endif
#else
#define ENDIAN ENDIAN_LITTLE
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// PLATFORM OS

#define OS_PS4 1
#define OS_MAC 2
#define OS_IOS 3
#define OS_LINUX 4
#define OS_ANDROID 5
#define OS_XBOXONE 6
#define OS_WINDOWS 7

#if defined(__ORBIS__)
#define PLATFORM_OS OS_PS4
#elif defined(_IOS)
#define PLATFORM_OS OS_IOS
#elif defined(__APPLE__)
#define PLATFORM_OS OS_MAC
#elif defined(__ANDROID__)
#define PLATFORM_OS OS_ANDROID
#elif defined(_LINUX)
#define PLATFORM_OS OS_LINUX
#elif defined(_XBOX_ONE)
#define PLATFORM_OS OS_XBOXONE
#elif defined(_WIN32)
#define PLATFORM_OS OS_WINDOWS
#else
#   error "unknown platform os !"
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// COMPILER

#define COMPILER_CLANG 1
#define COMPILER_GNUC 2
#define COMPILER_MSVC 3

#if defined( __clang__ )
#   define COMPILER COMPILER_CLANG
#elif defined( __GNUC__ )
#   define COMPILER COMPILER_GNUC
#elif defined( _MSC_VER )
#   define COMPILER COMPILER_MSVC
#else
#   error "unknown compiler !"
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// CPU ARCH

#define ARCH_32 1
#define ARCH_64 2

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__64BIT__) || defined(__mips64) || defined(__powerpc64__) || defined(__ppc64__) || defined(__LP64__)
#   define ARCH_TYPE ARCH_64
#else
#   define ARCH_TYPE ARCH_32
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// SIMD 
#define SIMD_SSE 1
#define SIMD_NEON 2

#if (defined (_M_IX86) || defined (_M_X64)) && !defined(_CHPE_ONLY_)
#define SIMD_TYPE SIMD_SSE
#elif defined (_M_ARM) || defined (_M_ARM64) || defined(_M_HYBRID_X86_ARM64)
#define SIMD_TYPE SIMD_NEON
#else
#define SIMD_TYPE SIMD_SSE
//#   error "unknown SIMD !"
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// INLINE

#if COMPILER == COMPILER_MSVC
#	define XE_INLINE __forceinline
#elif COMPILER == COMPILER_GNUC || COMPILER == COMPILER_CLANG
#	define XE_INLINE __inline__
#else
#	define XE_INLINE inline
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// DLL EXPORT

#if COMPILER == COMPILER_MSVC
#   define DLL_IMPORT __declspec( dllimport )
#   define DLL_EXPORT __declspec( dllexport )
#   define DLL_VAR_WEAK __declspec( selectany )
#elif COMPILER == COMPILER_GNUC || COMPILER == COMPILER_CLANG
#   define DLL_IMPORT __attribute__ ((visibility ("default")))
#   define DLL_EXPORT __attribute__ ((visibility ("default")))
#   define DLL_VAR_WEAK __attribute__((weak))
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// ALIGNED

#define ALIGNED(VALUE, ALIGN) (((XE::uint64)(VALUE) + ((ALIGN) - 1)) & ~((ALIGN) - 1))

#define ALIGNED4(VALUE) (((XE::uint64)(VALUE) + 3) & ~3)
#define ALIGNED8(VALUE) (((XE::uint64)(VALUE) + 7) & ~7)
#define ALIGNED16(VALUE) (((XE::uint64)(VALUE) + 15) & ~15)
#define ALIGNED32(VALUE) (((XE::uint64)(VALUE) + 31) & ~31)
#define ALIGNED64(VALUE) (((XE::uint64)(VALUE) + 63) & ~63)
#define ALIGNED128(VALUE) (((XE::uint64)(VALUE) + 127) & ~127)
#define ALIGNED256(VALUE) (((XE::uint64)(VALUE) + 255) & ~255)
#define IS_ALIGNED4(VALUE) (((XE::uint64)(VALUE) & 3) == 0)
#define IS_ALIGNED8(VALUE) (((XE::uint64)(VALUE) & 7) == 0)
#define IS_ALIGNED16(VALUE) (((XE::uint64)(VALUE) & 15) == 0)
#define IS_ALIGNED32(VALUE) (((XE::uint64)(VALUE) & 31) == 0)
#define IS_ALIGNED64(VALUE) (((XE::uint64)(VALUE) & 63) == 0)
#define IS_ALIGNED128(VALUE) (((XE::uint64)(VALUE) & 127) == 0)
#define IS_ALIGNED256(VALUE) (((XE::uint64)(VALUE) & 255) == 0)

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// DEBUG

#if defined(DEBUG) || defined(_DEBUG)
#undef DEBUG
#define DEBUG
#endif // DEBUG

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// ASSERT

#ifndef DEBUG
#define XE_ASSERT(x) { (void)0; }
#else
#if PLATFORM_OS == OS_WINDOWS
#define XE_ASSERT(x) { if(!(x)) __debugbreak(); }
#else
#define XE_ASSERT(x) { if(!(x)) raise(SIGTRAP); }
#endif
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// MEMORY SIZE

#define ONE_BYTE (1)
#define ONE_KBYTE (ONE_BYTE * 1024)
#define ONE_MBYTE (ONE_KBYTE * 1024)
#define ONE_GBYTE (ONE_MBYTE * 1024)

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// MACRO ARGS COUNT

#define MACRO_CAT(x, y)     x##y
#define MACRO_GLUE(x, y)    MACRO_CAT(x, y)

#define MACRO_EXP_(exp) exp
#define MACRO_ARGS_FILTER(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_N, ...) _N
#define MACRO_ARGS_CONTER(...)  MACRO_EXP_(MACRO_ARGS_FILTER(0, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// NAMESPACE

#define BEG_XE_NAMESPACE namespace XE {
#define END_XE_NAMESPACE };
#define USING_XE using namespace XE;

/////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////
/// IGNORED WARNING

#if COMPILER == COMPILER_MSVC
#pragma warning(disable : 4251)
#pragma warning(disable : 4996)
#pragma warning(disable : 4091)
#elif COMPILER == COMPILER_CLANG
#pragma clang diagnostic ignored"-Winconsistent-missing-override"
#else
#endif

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/// VERSION

#define MAJOR_VERSION 0
#define MINOR_VERSION 0
#define PATCH_VERSION 0

#define VERSION_INTEGER ( int( ( MAJOR_VERSION << 20 ) | ( MINOR_VERSION << 10 ) | ( PATCH_VERSION ) ) )

#define _VERSION_TO_STRING_(x) #x
#define _VERSION_TO_STRING(x) _VERSION_TO_STRING_(x)
#define VERSION_STRING _VERSION_TO_STRING(MAJOR_VERSION)"."_VERSION_TO_STRING(MINOR_VERSION)"."_VERSION_TO_STRING(PATCH_VERSION) 

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __CONFIG_H__851B77A2_E78D_4E14_91A6_D6317250A486
