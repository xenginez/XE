#include "FileSystem.h"
#include <physfs/physfs.h>

struct XE::FileSystem::File
{

};

void XE::FileSystem::Init()
{
	PHYSFS_init( nullptr );
}

void XE::FileSystem::Deinit()
{
	PHYSFS_deinit();
}

XE::FileSystem::Version XE::FileSystem::GetVersion()
{
	XE::FileSystem::Version ret;

	PHYSFS_Version ver;

	PHYSFS_getLinkedVersion( &ver );

	ret.major = ver.major;
	ret.minor = ver.minor;
	ret.patch = ver.patch;

	return ret;
}

std::vector<XE::FileSystem::ArchiveInfo> XE::FileSystem::SupportedArchiveTypes()
{
	std::vector<XE::FileSystem::ArchiveInfo> ret;

	auto types = PHYSFS_supportedArchiveTypes();

	for (; *types != nullptr; ++types)
	{
		XE::FileSystem::ArchiveInfo info;

		info.author = ( *types )->author;
		info.description = ( *types )->description;
		info.extension = ( *types )->extension;
		info.supportsSymlinks = ( *types )->supportsSymlinks;
		info.url = ( *types )->url;

		ret.push_back( info );
	}

	return ret;
}

std::string XE::FileSystem::DirSeparator()
{
	return PHYSFS_getDirSeparator();
}

void XE::FileSystem::PermitSymbolicLinks( bool allow )
{
	PHYSFS_permitSymbolicLinks( allow );
}

std::string XE::FileSystem::GetBaseDir()
{
	return PHYSFS_getBaseDir();
}

std::string XE::FileSystem::GetUserDir()
{
	return PHYSFS_getUserDir();
}

std::string XE::FileSystem::GetWriteDir()
{
	return PHYSFS_getWriteDir();
}

std::vector<std::string> XE::FileSystem::GetCDRomDirs()
{
	std::vector<std::string> dirs;
	auto dirBegin = PHYSFS_getCdRomDirs();

	for( char ** dir = dirBegin; *dirBegin != nullptr; dirBegin++ )
	{
		dirs.push_back( *dirBegin );
	}

	PHYSFS_freeList( dirBegin );
	
	return dirs;
}

void XE::FileSystem::RemoveFromSearchPath( const std::string & oldDir )
{
	PHYSFS_removeFromSearchPath( oldDir.c_str() );
}

std::vector<std::string> XE::FileSystem::GetSearchPath()
{
	std::vector<std::string> dirs;
	auto dirBegin = PHYSFS_getSearchPath();

	for( char ** dir = dirBegin; *dirBegin != nullptr; dirBegin++ )
	{
		dirs.push_back( *dirBegin );
	}

	PHYSFS_freeList( dirBegin );

	return dirs;
}

void XE::FileSystem::MkDir( const std::string & dirName )
{
	PHYSFS_mkdir( dirName.c_str() );
}

void XE::FileSystem::DeleteFile( const std::string & filename )
{
	PHYSFS_delete( filename.c_str() );
}

std::string XE::FileSystem::GetRealDir( const std::string & filename )
{
	return PHYSFS_getRealDir( filename.c_str() );
}

std::vector<std::string> XE::FileSystem::EnumerateFiles( const std::string & directory )
{
	std::vector<std::string> dirs;
	auto dirBegin = PHYSFS_enumerateFiles( directory.c_str() );

	for( char ** dir = dirBegin; *dirBegin != nullptr; dirBegin++ )
	{
		dirs.push_back( *dirBegin );
	}

	PHYSFS_freeList( dirBegin );

	return dirs;
}

bool XE::FileSystem::Exists( const std::string & filename )
{
	return PHYSFS_exists( filename.c_str() );
}

bool XE::FileSystem::IsDirectory( const std::string & filename )
{
	return PHYSFS_isDirectory( filename.c_str() );
}

bool XE::FileSystem::IsSymbolicLink( const std::string & filename )
{
	return PHYSFS_isSymbolicLink( filename.c_str() );
}

XE::int64 XE::FileSystem::GetLastModTime( const std::string & filename )
{
	return PHYSFS_getLastModTime( filename.c_str() );
}

bool XE::FileSystem::IsInit()
{
	return PHYSFS_isInit();
}

bool XE::FileSystem::SymbolicLinksPermitted()
{
	return PHYSFS_symbolicLinksPermitted();
}

void XE::FileSystem::Mount( const std::string & newDir, const std::string & mountPoint, bool appendToPath )
{
	PHYSFS_mount( newDir.c_str(), mountPoint.c_str(), appendToPath );
}

std::string XE::FileSystem::GetMountPoint( const std::string & dir )
{
	return PHYSFS_getMountPoint( dir.c_str() );
}

void XE::FileSystem::SetWriteDir( const std::string & newDir )
{
	PHYSFS_setWriteDir( newDir.c_str() );
}

void XE::FileSystem::SetSaneConfig( const std::string & orgName, const std::string & appName, const std::string & archiveExt, bool includeCdRoms, bool archivesFirst )
{
	PHYSFS_setSaneConfig( orgName.c_str(), appName.c_str(), archiveExt.c_str(), includeCdRoms, archivesFirst );
}
