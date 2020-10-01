#ifndef FILESYSTEM_H__373D1606_6495_43EC_8013_03DDF9BABFA0
#define FILESYSTEM_H__373D1606_6495_43EC_8013_03DDF9BABFA0

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API FileSystem
{
public:
	enum class Mode
	{
		READ,
		WIRTE,
		APPEND,
	};

public:
	struct Version
	{
		XE::uint8 major; /**< major revision */
		XE::uint8 minor; /**< minor revision */
		XE::uint8 patch; /**< patchlevel */
	};

	struct ArchiveInfo
	{
		const char * extension = nullptr;   /**< Archive file extension: "ZIP", for example. */
		const char * description = nullptr; /**< Human-readable archive description. */
		const char * author = nullptr;      /**< Person who did support for this archive. */
		const char * url = nullptr;         /**< URL related to this archive */
		int supportsSymlinks = 0;    /**< non-zero if archive offers symbolic links. */
	};

public:
	static void Init();

	static void Deinit();

	static Version GetVersion();

	static std::vector<ArchiveInfo> SupportedArchiveTypes();

	static std::string DirSeparator();

	static void PermitSymbolicLinks( bool allow );

	static std::string GetBaseDir();

	static std::string GetUserDir();

	static std::string GetWriteDir();

	static std::vector<std::string> GetCDRomDirs();

	static void RemoveFromSearchPath( const std::string & oldDir );

	static std::vector<std::string> GetSearchPath();

	static void MkDir( const std::string & dirName );

	static void DeleteFile( const std::string & filename );

	static std::string GetRealDir( const std::string & filename );

	static std::vector<std::string> EnumerateFiles( const std::string & directory );

	static bool Exists( const std::string & filename );

	static bool IsDirectory( const std::string & filename );

	static bool IsSymbolicLink( const std::string & filename );

	static XE::int64 GetLastModTime( const std::string & filename );

	static bool IsInit();

	static bool SymbolicLinksPermitted();

	static void Mount( const std::string & newDir, const std::string & mountPoint, bool appendToPath );

	static std::string GetMountPoint( const std::string & dir );

public:
	static void SetWriteDir( const std::string & newDir );

	static void SetSaneConfig( const std::string & orgName, const std::string & appName, const std::string & archiveExt, bool includeCdRoms, bool archivesFirst );

};

END_XE_NAMESPACE

#endif // FILESYSTEM_H__373D1606_6495_43EC_8013_03DDF9BABFA0
