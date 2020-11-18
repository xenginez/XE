/*!
 * \file   FileSystem.h
 *
 * \author ZhengYuanQing
 * \date   2020/10/02
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef FILESYSTEM_H__9E3E6B04_2D43_49AE_9FD4_08CEED267D20
#define FILESYSTEM_H__9E3E6B04_2D43_49AE_9FD4_08CEED267D20

#include "Type.h"

#if PLATFORM_OS == OS_MAC || PLATFORM_OS == OS_PS4 || PLATFORM_OS == OS_UNIX || PLATFORM_OS == OS_LINUX || PLATFORM_OS == OS_XBOXONE || PLATFORM_OS == OS_WINDOWS
#include <filesystem>
#endif

BEG_XE_NAMESPACE

namespace FileSystem
{
#if PLATFORM_OS == OS_MAC || PLATFORM_OS == OS_PS4 || PLATFORM_OS == OS_UNIX || PLATFORM_OS == OS_LINUX || PLATFORM_OS == OS_XBOXONE || PLATFORM_OS == OS_WINDOWS

	using namespace std::filesystem;

	using Path = std::filesystem::path;
	using DirectoryEntry = std::filesystem::directory_entry;
	using DirectoryIterator = std::filesystem::directory_iterator;
	using RecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;
	using DirectoryOptions = std::filesystem::directory_options;
	using FileStatus = std::filesystem::file_status;
	using FileType = std::filesystem::file_type;
	using FileSystemError = std::filesystem::filesystem_error;
	using PermOptions = std::filesystem::perm_options;
	using Perms = std::filesystem::perms;
	using CopyOptions = std::filesystem::copy_options;
	using FileTimeType = std::filesystem::file_time_type;
	using SpaceInfo = std::filesystem::space_info;

#else

	class Path;
	class DirectoryIterator;
	class RecursiveDirectoryIterator;

	class Path
	{
		friend void current_path( const Path & _To );
		friend void current_path( const Path & _To, std::error_code & _Ec ) noexcept;

	public:
		using value_type = char;
		using string_type = std::string;

		static constexpr char preferred_separator = '/';

		enum format
		{
			auto_format, native_format, generic_format
		};

		Path() = default;
		Path( const Path & ) = default;
		Path( Path && ) = default;
		~Path() = default;
		Path & operator=( const Path & ) = default;
		Path & operator=( Path && ) noexcept = default;

		Path( string_type && _Source );

		Path( string_type && _Source, format );

		template <class _InIt>
		Path( _InIt _First, _InIt _Last, format = auto_format );

		Path & operator=( string_type && _Source );

		Path & assign( string_type && _Source );

		template <class _InIt>
		Path & assign( _InIt _First, _InIt _Last );

		Path & operator/=( const Path & _Other );

		Path & operator/=( const string_type & _Source );

		Path & append( const string_type & _Source );

		template <class _InIt>
		Path & append( _InIt _First, _InIt _Last );

		Path & operator+=( const Path & _Added );

		Path & operator+=( const string_type & _Added );

		Path & operator+=( const value_type * const _Added );

		Path & operator+=( const value_type _Added );

		Path & concat( const string_type & _Added );

		template <class _InIt>
		Path & concat( _InIt _First, _InIt _Last );

		void clear();

		Path & make_preferred();

		Path & remove_filename();

		Path & replace_filename( const Path & _Replacement );

		Path & replace_extension(/* const path& _Replacement = path() */ );

		Path & replace_extension( const Path & _Replacement );

		void swap( Path & _Rhs );

		const string_type & native() const;

		const value_type * c_str() const;

		operator string_type() const;

		std::string string() const;

		std::wstring wstring() const;

		std::string u8string() const;

		std::string generic_string() const;

		std::string generic_u8string() const;

		int compare( const Path & _Other ) const;

		int compare( const string_type & _Other ) const;

		int compare( const std::basic_string_view<value_type> _Other ) const;

		int compare( const value_type * const _Other ) const;

		Path root_name() const;

		Path root_directory() const;

		Path root_path() const;

		Path relative_path() const;

		Path parent_path() const;

		Path filename() const;

		Path stem() const;

		Path extension() const;

		bool empty() const;

		bool has_root_name() const;

		bool has_root_directory() const;

		bool has_root_path() const;

		bool has_relative_path() const;

		bool has_parent_path() const;

		bool has_filename() const;

		bool has_stem() const;

		bool has_extension() const;

		bool is_absolute() const;

		bool is_relative() const;

		Path lexically_normal() const;

		Path lexically_relative( const Path & _Base ) const;

		Path lexically_proximate( const Path & _Base ) const;

		using iterator = string_type::const_iterator;
		using const_iterator = iterator;

		iterator begin() const;
		iterator end() const noexcept;

		template <class _Elem, class _Traits>
		friend std::basic_ostream<_Elem, _Traits> & operator<<( std::basic_ostream<_Elem, _Traits> & _Ostr, const Path & _Path );

		template <class _Elem, class _Traits>
		friend std::basic_istream<_Elem, _Traits> & operator>>( std::basic_istream<_Elem, _Traits> & _Istr, Path & _Path );

		friend bool operator==( const Path & _Left, const Path & _Right );

		friend bool operator!=( const Path & _Left, const Path & _Right );

		friend bool operator<( const Path & _Left, const Path & _Right );

		friend bool operator>( const Path & _Left, const Path & _Right );

		friend bool operator<=( const Path & _Left, const Path & _Right );

		friend bool operator>=( const Path & _Left, const Path & _Right );

		friend Path operator/( const Path & _Left, const Path & _Right );

	private:
		string_type _Text;
	};

	Path u8path( const std::string & _Source );

	template <class _InIt>
	Path u8path( _InIt _First, _InIt _Last );

	void swap( Path & _Left, Path & _Right );

	size_t hash_value( const Path & _Path );

	class FileSystemError : public std::system_error
	{
	public:
		FileSystemError( const std::string & _Message, const std::error_code _Errcode );

		FileSystemError( const std::string & _Message, const Path & _Path1_arg, const std::error_code _Errcode );

		FileSystemError( const std::string & _Message, const Path & _Path1_arg, const Path & _Path2_arg, const std::error_code _Errcode );

		const Path & path1() const;

		const Path & path2() const;

		virtual const char * what() const;

	};

	enum class FileType
	{
		none,
		not_found,
		regular,
		directory,
		symlink,

		block,
		character,

		fifo,
		socket,
		unknown,

		junction
	};

	enum class Perms
	{
		none = 0,

		owner_read = 0400,
		owner_write = 0200,
		owner_exec = 0100,
		owner_all = 0700,

		group_read = 0040,
		group_write = 0020,
		group_exec = 0010,
		group_all = 0070,

		others_read = 0004,
		others_write = 0002,
		others_exec = 0001,
		others_all = 0007,

		all = 0777,
		set_uid = 04000,
		set_gid = 02000,
		sticky_bit = 01000,
		mask = 07777,
		unknown = 0xFFFF,
	};

	enum class CopyOptions
	{
		none = 0,

		skip_existing = 0x1,
		overwrite_existing = 0x2,
		update_existing = 0x4,

		recursive = 0x10,

		_Symlinks_mask = 0xF00,
		copy_symlinks = 0x100,
		skip_symlinks = 0x200,

		_Copy_form_mask = 0xF000,
		directories_only = 0x1000,
		create_symlinks = 0x2000,
		create_hard_links = 0x4000,
	};

	class FileStatus
	{
	public:
		FileStatus() noexcept = default;
		explicit FileStatus( FileType _Ft, Perms _Perms = Perms::unknown ) noexcept;
		FileStatus( const FileStatus & ) noexcept = default;
		FileStatus( FileStatus && ) noexcept = default;
		~FileStatus() noexcept = default;

		FileStatus & operator=( const FileStatus & ) noexcept = default;
		FileStatus & operator=( FileStatus && ) noexcept = default;

		void type( FileType _Ft ) noexcept;

		void permissions( Perms _Perms ) noexcept;

		FileType type() const noexcept;

		Perms permissions() const noexcept;
	};

	bool exists( const FileStatus _Status );

	bool is_block_file( const FileStatus _Status );

	bool is_character_file( const FileStatus _Status );

	bool is_directory( const FileStatus _Status );

	bool is_fifo( const FileStatus _Status );

	bool is_other( const FileStatus _Status );

	bool is_regular_file( const FileStatus _Status );

	bool is_socket( const FileStatus _Status );

	bool is_symlink( const FileStatus _Status );

	using FileTimeType = std::chrono::system_clock::time_point;

	class DirectoryEntry
	{
	public:
		DirectoryEntry() noexcept;

		DirectoryEntry( const DirectoryEntry & ) = default;
		DirectoryEntry( DirectoryEntry && ) noexcept = default;
		explicit DirectoryEntry( const XE::FileSystem::Path & _Path_arg );

		DirectoryEntry( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec );

		~DirectoryEntry() = default;

		DirectoryEntry & operator=( const DirectoryEntry & ) = default;
		DirectoryEntry & operator=( DirectoryEntry && ) noexcept = default;

		void assign( const XE::FileSystem::Path & _Path_arg );

		void assign( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec );

		void replace_filename( const XE::FileSystem::Path & _Path_arg );

		void replace_filename( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec );

		void refresh();

		void refresh( std::error_code & _Ec );

		void clear_cache();

	public:
		const XE::FileSystem::Path & path() const;

		operator const FileSystem::Path & ( ) const;

		bool exists() const;

		bool exists( std::error_code & _Ec ) const;

		bool is_block_file() const;

		bool is_block_file( std::error_code & _Ec ) const;

		bool is_character_file() const;

		bool is_character_file( std::error_code & _Ec ) const;

		bool is_directory() const;

		bool is_directory( std::error_code & _Ec ) const;

		bool is_fifo() const;

		bool is_fifo( std::error_code & _Ec ) const;

		bool is_other() const;

		bool is_other( std::error_code & _Ec ) const;

		bool is_regular_file() const;

		bool is_regular_file( std::error_code & _Ec ) const;

		bool is_socket() const;

		bool is_socket( std::error_code & _Ec ) const;

		bool is_symlink() const;

		bool is_symlink( std::error_code & _Ec ) const;

	public:
		XE::uint64 file_size() const;

		XE::uint64 file_size( std::error_code & _Ec ) const;

	public:
		XE::uint64 hard_link_count() const;

		XE::uint64 hard_link_count( std::error_code & _Ec ) const;

	public:
		FileTimeType last_write_time() const;

		FileTimeType last_write_time( std::error_code & _Ec ) const;

	public:
		FileStatus status() const;

		FileStatus status( std::error_code & _Ec ) const;

		FileStatus symlink_status() const;

		FileStatus symlink_status( std::error_code & _Ec ) const;

		bool operator<( const DirectoryEntry & _Rhs ) const;

		bool operator==( const DirectoryEntry & _Rhs ) const;

		bool operator!=( const DirectoryEntry & _Rhs ) const;

		bool operator<=( const DirectoryEntry & _Rhs ) const;

		bool operator>( const DirectoryEntry & _Rhs ) const;

		bool operator>=( const DirectoryEntry & _Rhs ) const;

	private:
		FileSystem::Path _Path;
	};

	enum class DirectoryOptions
	{
		none = 0, follow_directory_symlink = 1, skip_permission_denied = 2
	};

	class DirectoryIterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = DirectoryEntry;
		using difference_type = std::ptrdiff_t;
		using pointer = const DirectoryEntry *;
		using reference = const DirectoryEntry &;

		DirectoryIterator() noexcept = default;
		explicit DirectoryIterator( const Path & _Path );

		DirectoryIterator( const Path & _Path, const DirectoryOptions _Options );

		DirectoryIterator( const Path & _Path, std::error_code & _Ec );

		DirectoryIterator( const Path & _Path, const DirectoryOptions _Options, std::error_code & _Ec );

		DirectoryIterator( const DirectoryIterator & ) noexcept = default;
		DirectoryIterator( DirectoryIterator && ) noexcept = default;
		~DirectoryIterator() noexcept = default;

		DirectoryIterator & operator=( const DirectoryIterator & ) noexcept = default;
		DirectoryIterator & operator=( DirectoryIterator && ) noexcept = default;

		const DirectoryEntry & operator*() const;

		const DirectoryEntry * operator->() const;

		DirectoryIterator & operator++();

		DirectoryIterator & increment( std::error_code & _Ec );
		
		bool operator==( const DirectoryIterator & _Rhs ) const;

		bool operator!=( const DirectoryIterator & _Rhs ) const;

	};
	
	DirectoryIterator begin( DirectoryIterator _Iter );

	DirectoryIterator end( DirectoryIterator );

	class RecursiveDirectoryIterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = DirectoryEntry;
		using difference_type = std::ptrdiff_t;
		using pointer = const DirectoryEntry *;
		using reference = const DirectoryEntry &;


		RecursiveDirectoryIterator() noexcept = default;
		explicit RecursiveDirectoryIterator( const Path & _Path );

		RecursiveDirectoryIterator( const Path & _Path, const DirectoryOptions _Options );

		RecursiveDirectoryIterator( const Path & _Path, const DirectoryOptions _Options, std::error_code & _Ec );

		RecursiveDirectoryIterator( const Path & _Path, std::error_code & _Ec );

		RecursiveDirectoryIterator( const RecursiveDirectoryIterator & ) noexcept = default;
		RecursiveDirectoryIterator( RecursiveDirectoryIterator && ) noexcept = default;
		~RecursiveDirectoryIterator() noexcept = default;

		DirectoryOptions options() const;
		int depth() const;
		bool recursion_pending() const;

		const DirectoryEntry & operator*() const;

		const DirectoryEntry * operator->() const;

		RecursiveDirectoryIterator & operator=( RecursiveDirectoryIterator && ) noexcept = default;
		RecursiveDirectoryIterator & operator=( const RecursiveDirectoryIterator & ) noexcept = default;

		RecursiveDirectoryIterator & operator++();

		RecursiveDirectoryIterator & increment( std::error_code & _Ec );

		void pop();

		void pop( std::error_code & _Ec );

		void disable_recursion_pending();

		bool operator==( const RecursiveDirectoryIterator & _Rhs ) const;

		bool operator!=( const RecursiveDirectoryIterator & _Rhs ) const;

	};

	RecursiveDirectoryIterator begin( RecursiveDirectoryIterator _Iter );

	RecursiveDirectoryIterator end( RecursiveDirectoryIterator );

	Path absolute( const Path & _Input );

	Path absolute( const Path & _Input, std::error_code & _Ec );

	Path canonical( const Path & _Input );

	Path canonical( const Path & _Input, std::error_code & _Ec );

	void create_directory_symlink( const Path & _To, const Path & _New_symlink );

	void create_directory_symlink( const Path & _To, const Path & _New_symlink, std::error_code & _Ec );

	void create_hard_link( const Path & _To, const Path & _New_hard_link );

	void create_hard_link( const Path & _To, const Path & _New_hard_link, std::error_code & _Ec );

	void create_symlink( const Path & _To, const Path & _New_symlink );

	void create_symlink( const Path & _To, const Path & _New_symlink, std::error_code & _Ec );

	Path read_symlink( const Path & _Symlink_path, std::error_code & _Ec );

	Path read_symlink( const Path & _Symlink_path );

	void copy_symlink( const Path & _Symlink, const Path & _New_symlink, std::error_code & _Ec );

	void copy_symlink( const Path & _Symlink, const Path & _New_symlink );

	bool copy_file( const Path & _From, const Path & _To, const CopyOptions _Options, std::error_code & _Ec );

	bool copy_file( const Path & _From, const Path & _To, const CopyOptions _Options );

	bool copy_file( const Path & _From, const Path & _To, std::error_code & _Ec );

	bool copy_file( const Path & _From, const Path & _To );

	bool equivalent( const Path & _Lhs, const Path & _Rhs );

	bool equivalent( const Path & _Lhs, const Path & _Rhs, std::error_code & _Ec );

	FileStatus status( const Path & _Path );
	FileStatus status( const Path & _Path, std::error_code & _Ec ) noexcept;
	FileStatus symlink_status( const Path & _Path );
	FileStatus symlink_status( const Path & _Path, std::error_code & _Ec ) noexcept;

	bool exists( const Path & _Target, std::error_code & _Ec );

	bool exists( const Path & _Target );

	XE::uint64 file_size( const Path & _Path );

	XE::uint64 file_size( const Path & _Path, std::error_code & _Ec );

	XE::uint64 hard_link_count( const Path & _Target );

	XE::uint64 hard_link_count( const Path & _Target, std::error_code & _Ec );

	bool is_block_file( const Path & );

	bool is_block_file( const Path & _Path, std::error_code & _Ec );

	bool is_character_file( const Path & );

	bool is_character_file( const Path & _Path, std::error_code & _Ec );

	bool is_directory( const Path & _Path );

	bool is_directory( const Path & _Path, std::error_code & _Ec );

	bool is_empty( const Path & _Path, std::error_code & _Ec );

	bool is_empty( const Path & _Path );

	bool is_fifo( const Path & );

	bool is_fifo( const Path & _Path, std::error_code & _Ec );

	bool is_other( const Path & _Path );

	bool is_other( const Path & _Path, std::error_code & _Ec );

	bool is_regular_file( const Path & _Path );

	bool is_regular_file( const Path & _Path, std::error_code & _Ec );

	bool is_socket( const Path & );

	bool is_socket( const Path & _Path, std::error_code & _Ec );

	bool is_symlink( const Path & _Path );

	bool is_symlink( const Path & _Path, std::error_code & _Ec );

	bool remove( const Path & _Target );

	bool remove( const Path & _Target, std::error_code & _Ec );

	void rename( const Path & _Old_p, const Path & _New_p );

	void rename( const Path & _Old_p, const Path & _New_p, std::error_code & _Ec );

	void resize_file( const Path & _Target, const XE::uint64 _New_size );

	void resize_file( const Path & _Target, const XE::uint64 _New_size, std::error_code & _Ec );

	struct SpaceInfo
	{
		XE::uint64 capacity;
		XE::uint64 free;
		XE::uint64 available;
	};

	SpaceInfo space( const Path & _Target );

	SpaceInfo space( const Path & _Target, std::error_code & _Ec );

	bool status_known( const FileStatus _Status );

	FileStatus status( const Path & _Path, std::error_code & _Ec );

	FileStatus status( const Path & _Path );

	FileStatus symlink_status( const Path & _Path, std::error_code & _Ec );

	FileStatus symlink_status( const Path & _Path );

	bool create_directory( const Path & _Path );

	bool create_directory( const Path & _Path, std::error_code & _Ec );

	bool create_directory( const Path & _Path, const Path & _Existing_p );

	bool create_directory( const Path & _Path, const Path &, std::error_code & _Ec );

	bool create_directories( const Path & _Path, std::error_code & _Ec );

	bool create_directories( const Path & _Path );

	XE::uint64 remove_all( const Path & _Path, std::error_code & _Ec );

	XE::uint64 remove_all( const Path & _Path );

	FileTimeType last_write_time( const Path & _Path );

	FileTimeType last_write_time( const Path & _Path, std::error_code & _Ec );

	void last_write_time( const Path & _Target, const FileTimeType _New_time );

	void last_write_time( const Path & _Target, const FileTimeType _New_time, std::error_code & _Ec );

	enum class PermOptions
	{
		replace = 0x1, add = 0x2, remove = 0x4, nofollow = 0x8
	};

	void permissions( const Path & _Target, const Perms _Perms, const PermOptions _Options = PermOptions::replace );

	void permissions( const Path & _Target, const Perms _Perms, const PermOptions _Options, std::error_code & _Ec );

	void permissions( const Path & _Target, const Perms _Perms, std::error_code & _Ec );

	Path temp_directory_path( std::error_code & _Ec );

	Path temp_directory_path();

	Path current_path( std::error_code & _Ec );

	Path current_path();

	void current_path( const Path & _To, std::error_code & _Ec );

	void current_path( const Path & _To );

	Path weakly_canonical( const Path & _Input, std::error_code & _Ec );

	Path weakly_canonical( const Path & _Input );

	Path proximate( const Path & _Path, const Path & _Base = FileSystem::current_path() );

	Path proximate( const Path & _Path, const Path & _Base, std::error_code & _Ec );

	Path proximate( const Path & _Path, std::error_code & _Ec );

	Path relative( const Path & _Path, const Path & _Base = FileSystem::current_path() );

	Path relative( const Path & _Path, const Path & _Base, std::error_code & _Ec );

	Path relative( const Path & _Path, std::error_code & _Ec );

	void copy( const Path & _From, const Path & _To, const CopyOptions _Options, std::error_code & _Ec );

	void copy( const Path & _From, const Path & _To, const CopyOptions _Options );

	void copy( const Path & _From, const Path & _To, std::error_code & _Ec );

	void copy( const Path & _From, const Path & _To );

#endif

};

XE_INLINE std::string ToString( const XE::FileSystem::Path & _Val )
{
	return _Val.u8string();
}

XE_INLINE bool FromString( const std::string & _Str, XE::FileSystem::Path & _Val )
{
	_Val = _Str;
}

END_XE_NAMESPACE

#endif // FILESYSTEM_H__9E3E6B04_2D43_49AE_9FD4_08CEED267D20