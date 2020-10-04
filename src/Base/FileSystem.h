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

#if PLATFORM_OS == OS_MAC || PLATFORM_OS == OS_PS4 || PLATFORM_OS == OS_UNIX || PLATFORM_OS == OS_LINUX || PLATFORM_OS == OS_XBOXONE || PLATFORM_OS == OS_WINDOWS

namespace FileSystem
{
	using namespace std::filesystem;

	using Path = std::filesystem::path;
	using DirectoryEntry = std::filesystem::directory_entry;
	using DirectoryIterator = std::filesystem::directory_iterator;
	using RecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;
	using DirectoryOptions = std::filesystem::directory_options;
	using FileStatus = std::filesystem::file_status;
	using FileType = std::filesystem::file_type;
	using FilesystemError = std::filesystem::filesystem_error;
	using PermOptions = std::filesystem::perm_options;
	using Perms = std::filesystem::perms;
}

#else

#define XE_BITMASK_OPS(_BITMASK)                                                                                      \
    static constexpr _BITMASK operator&(_BITMASK _Left, _BITMASK _Right) noexcept { /* return _Left & _Right */ \
        using _IntTy = _STD underlying_type_t<_BITMASK>;                                                            \
        return static_cast<_BITMASK>(static_cast<_IntTy>(_Left) & static_cast<_IntTy>(_Right));                     \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK operator|(_BITMASK _Left, _BITMASK _Right) noexcept { /* return _Left | _Right */ \
        using _IntTy = _STD underlying_type_t<_BITMASK>;                                                            \
        return static_cast<_BITMASK>(static_cast<_IntTy>(_Left) | static_cast<_IntTy>(_Right));                     \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK operator^(_BITMASK _Left, _BITMASK _Right) noexcept { /* return _Left ^ _Right */ \
        using _IntTy = _STD underlying_type_t<_BITMASK>;                                                            \
        return static_cast<_BITMASK>(static_cast<_IntTy>(_Left) ^ static_cast<_IntTy>(_Right));                     \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK& operator&=(_BITMASK& _Left, _BITMASK _Right) noexcept { /* return _Left &= _Right */        \
        return _Left = _Left & _Right;                                                                              \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK& operator|=(_BITMASK& _Left, _BITMASK _Right) noexcept { /* return _Left |= _Right */        \
        return _Left = _Left | _Right;                                                                              \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK& operator^=(_BITMASK& _Left, _BITMASK _Right) noexcept { /* return _Left ^= _Right */        \
        return _Left = _Left ^ _Right;                                                                              \
    }                                                                                                               \
                                                                                                                    \
    static constexpr _BITMASK operator~(_BITMASK _Left) noexcept { /* return ~_Left */                          \
        using _IntTy = _STD underlying_type_t<_BITMASK>;                                                            \
        return static_cast<_BITMASK>(~static_cast<_IntTy>(_Left));                                                  \
    }                                                                                                               \
                                                                                                                    \
    static constexpr bool _Bitmask_includes(                                                                    \
        _BITMASK _Left, _BITMASK _Elements) noexcept { /* return (_Left & _Elements) != _BITMASK{} */               \
        return (_Left & _Elements) != _BITMASK{};                                                                   \
    }                                                                                                               \
                                                                                                                    \
    static constexpr bool _Bitmask_includes_all(                                                                \
        _BITMASK _Left, _BITMASK _Elements) noexcept { /* return (_Left & _Elements) == _Elements */                \
        return (_Left & _Elements) == _Elements;                                                                    \
    }

namespace FileSystem
{
	static constexpr size_t __std_fs_max_path = 260; 
	static constexpr size_t __std_fs_temp_path_max = __std_fs_max_path + 1;
	static constexpr long long __std_fs_file_time_epoch_adjustment = 0x19DB1DED53E8000LL; 

	enum class __std_win_error : unsigned long
	{
		_Success = 0, 
		_Invalid_function = 1, 
		_File_not_found = 2, 
		_Path_not_found = 3, 
		_Access_denied = 5, 
		_Not_enough_memory = 8, 
		_No_more_files = 18, 
		_Sharing_violation = 32, 
		_Not_supported = 50, 
		_File_exists = 80, 
		_Invalid_parameter = 87, 
		_Insufficient_buffer = 122, 
		_Invalid_name = 123, 
		_Directory_not_empty = 145, 
		_Already_exists = 183, 
		_Filename_exceeds_range = 206, 
		_Directory_name_is_invalid = 267, 
		_Max = ~0UL 
	};

	enum class __std_fs_dir_handle : intptr_t
	{
		_Invalid = -1
	};

	enum class __std_fs_file_attr : unsigned long
	{
		_Readonly = 0x00000001, 
		_Hidden = 0x00000002, 
		_System = 0x00000004, 
		_Directory = 0x00000010, 
		_Archive = 0x00000020, 
		_Device = 0x00000040, 
		_Normal = 0x00000080, 
		_Temporary = 0x00000100, 
		_Sparse_file = 0x00000200, 
		_Reparse_point = 0x00000400, 

		_Invalid = 0xFFFFFFFF, 
	};
	XE_BITMASK_OPS( __std_fs_file_attr )

	enum class __std_fs_reparse_tag : unsigned long
	{
		_None = 0,
		_Mount_point = ( 0xA0000003L ), 
		_Symlink = ( 0xA000000CL ), 
	};

	struct __std_fs_filetime
	{ 
		unsigned long _Low; 
		unsigned long _High; 
	}; 

	struct __std_fs_find_data
	{ 
		__std_fs_file_attr _Attributes; 
		__std_fs_filetime _Creation_time; 
		__std_fs_filetime _Last_access_time; 
		__std_fs_filetime _Last_write_time; 
		unsigned long _File_size_high; 
		unsigned long _File_size_low; 

		
		

		__std_fs_reparse_tag _Reparse_point_tag; 
		unsigned long _Reserved1; 
		wchar_t _File_name[__std_fs_max_path]; 
		wchar_t _Short_file_name[14]; 
	}; 

	enum class __std_fs_stats_flags : unsigned long
	{
		_None = 0,

		_Follow_symlinks = 0x01, 
		_Attributes = 0x02, 
		_Reparse_tag = 0x04, 
		_File_size = 0x08, 
		_Link_count = 0x10, 
		_Last_write_time = 0x20, 

		_All_data = _Attributes | _Reparse_tag | _File_size | _Link_count | _Last_write_time
	};
	XE_BITMASK_OPS( __std_fs_stats_flags )

	struct __std_fs_stats
	{
		long long _Last_write_time;
		unsigned long long _File_size;
		__std_fs_file_attr _Attributes;
		__std_fs_reparse_tag _Reparse_point_tag;
		unsigned long _Link_count;
		__std_fs_stats_flags _Available; 

		__std_fs_file_attr _Symlink_hint_attributes() const noexcept
		{
			if( _Bitmask_includes( _Available, __std_fs_stats_flags::_Attributes ) )
			{
				return _Attributes;
			}

			return __std_fs_file_attr::_Invalid;
		}
	};

	struct __std_fs_reparse_data_buffer
	{ 
		unsigned long _Reparse_tag;
		unsigned short _Reparse_data_length;
		unsigned short _Reserved;
		union
		{
			struct
			{
				unsigned short _Substitute_name_offset;
				unsigned short _Substitute_name_length;
				unsigned short _Print_name_offset;
				unsigned short _Print_name_length;
				unsigned long _Flags;
				wchar_t _Path_buffer[1];
			} _Symbolic_link_reparse_buffer;
			struct
			{
				unsigned short _Substitute_name_offset;
				unsigned short _Substitute_name_length;
				unsigned short _Print_name_offset;
				unsigned short _Print_name_length;
				wchar_t _Path_buffer[1];
			} _Mount_point_reparse_buffer;
			struct
			{
				unsigned char _Data_buffer[1];
			} _Generic_reparse_buffer;
		};
	};

	struct __std_ulong_and_error
	{
		unsigned long _Size;
		__std_win_error _Error;
	};

	enum class __std_fs_volume_name_kind : unsigned long
	{
		_Dos = 0, 
		_Guid = 1, 
		_Nt = 2, 
		_None = 4 
	};

	enum class __std_access_rights : unsigned long
	{
		_Delete = 0x00010000, 
		_File_read_attributes = 0x0080, 
		_File_write_attributes = 0x0100,
		_File_generic_write = 0x00120116,
	};

	XE_BITMASK_OPS( __std_access_rights )

	enum class __std_fs_file_flags : unsigned long
	{
		_None = 0,
		_Backup_semantics = 0x02000000, 
		_Open_reparse_point = 0x00200000, 
	};

	XE_BITMASK_OPS( __std_fs_file_flags )

	enum class __std_fs_file_handle : intptr_t
	{
		_Invalid = -1
	};

	enum class __std_code_page : unsigned int
	{
		_Utf8 = 65001
	};

	struct __std_fs_convert_result
	{
		int _Len;
		__std_win_error _Err;
	};

	struct __std_fs_file_id
	{ 
		unsigned long long _Volume_serial_number; 
		unsigned char _Id[16]; 
	}; 

	enum class __std_fs_copy_options
	{
		_None = 0x0,

		_Existing_mask = 0xF,
		_Skip_existing = 0x1,
		_Overwrite_existing = 0x2,
		_Update_existing = 0x4,
	};

	XE_BITMASK_OPS( __std_fs_copy_options )


	__std_ulong_and_error __std_fs_get_full_path_name( const wchar_t * _Source, unsigned long _Target_size, wchar_t * _Target ) noexcept;

	__std_win_error __std_fs_open_handle( __std_fs_file_handle * _Handle, const wchar_t * _File_name, __std_access_rights _Desired_access, __std_fs_file_flags _Flags ) noexcept;

	void __std_fs_close_handle( __std_fs_file_handle _Handle ) noexcept;

	__std_win_error __std_fs_get_file_attributes_by_handle( __std_fs_file_handle _Handle, unsigned long * _File_attributes ) noexcept;

	__std_ulong_and_error __std_fs_get_final_path_name_by_handle( __std_fs_file_handle _Handle, wchar_t * _Target, unsigned long _Target_size, __std_fs_volume_name_kind _Flags ) noexcept;

	struct __std_fs_copy_file_result
	{
		bool _Copied;
		__std_win_error _Error;
	};

	__std_fs_copy_file_result __std_fs_copy_file( const wchar_t * _Source, const wchar_t * _Target, __std_fs_copy_options _Options ) noexcept;

	__std_win_error __std_fs_directory_iterator_open( const wchar_t * _Path_spec, __std_fs_dir_handle * _Handle, __std_fs_find_data * _Results ) noexcept;

	void __std_fs_directory_iterator_close( __std_fs_dir_handle _Handle ) noexcept;

	__std_win_error __std_fs_get_stats( const wchar_t * _Path, __std_fs_stats * _Stats, __std_fs_stats_flags _Flags, __std_fs_file_attr _Symlink_attribute_hint = __std_fs_file_attr::_Invalid ) noexcept;

	__std_win_error __std_fs_directory_iterator_advance( __std_fs_dir_handle _Handle, __std_fs_find_data * _Results ) noexcept;

	__std_code_page __std_fs_code_page() noexcept;

	__std_fs_convert_result __std_fs_convert_narrow_to_wide( __std_code_page _Code_page, const char * _Input_str, int _Input_len, wchar_t * _Output_str, int _Output_len ) noexcept;

	__std_fs_convert_result __std_fs_convert_wide_to_narrow( __std_code_page _Code_page, const wchar_t * _Input_str, int _Input_len, char * _Output_str, int _Output_len ) noexcept;

	__std_win_error __std_fs_get_file_id( __std_fs_file_id * _Id, const wchar_t * _Path ) noexcept;

	__std_win_error __std_fs_set_last_write_time( long long _Last_write_filetime, const wchar_t * _Path ) noexcept;

	__std_win_error __std_fs_change_permissions( const wchar_t * _Path, bool _Follow_symlinks, bool _Readonly ) noexcept;

	__std_ulong_and_error __std_fs_get_temp_path( wchar_t * _Target ) noexcept;

	__std_ulong_and_error __std_fs_get_current_path( unsigned long _Target_size, wchar_t * _Target ) noexcept;

	__std_win_error __std_fs_set_current_path( const wchar_t * _Target ) noexcept;

	__std_win_error __std_fs_create_directory_symbolic_link( const wchar_t * _Symlink_file_name, const wchar_t * _Target_file_name ) noexcept;

	__std_win_error __std_fs_create_hard_link( const wchar_t * _File_name, const wchar_t * _Existing_file_name ) noexcept;

	__std_win_error __std_fs_create_symbolic_link( const wchar_t * _Symlink_file_name, const wchar_t * _Target_file_name ) noexcept;

	__std_win_error __std_fs_read_reparse_data_buffer( __std_fs_file_handle _Handle, void * _Buffer, unsigned long _Buffer_size ) noexcept;

	__std_win_error __std_fs_read_name_from_reparse_data_buffer( __std_fs_reparse_data_buffer * _Handle, wchar_t ** _Offset, unsigned short * _Length ) noexcept;

	struct __std_fs_create_directory_result
	{
		bool _Created;
		__std_win_error _Error;
	};

	__std_fs_create_directory_result __std_fs_create_directory( const wchar_t * _New_directory ) noexcept;

	struct __std_fs_remove_result
	{
		bool _Removed;
		__std_win_error _Error;
	};

	__std_fs_remove_result __std_fs_remove( const wchar_t * _Target ) noexcept;

	__std_win_error __std_fs_rename( const wchar_t * _Source, const wchar_t * _Target ) noexcept;

	__std_win_error __std_fs_resize_file( const wchar_t * _Target, uintmax_t _New_size ) noexcept;

	__std_win_error __std_fs_space( const wchar_t * _Target, uintmax_t * _Available, uintmax_t * _Total_bytes, uintmax_t * _Free_bytes ) noexcept;

	struct _Fs_file
	{
		__std_fs_file_handle _Raw;

		explicit _Fs_file( void * const _Handle ) : _Raw{ reinterpret_cast< intptr_t >( _Handle ) }
		{
		}

		_Fs_file( const wchar_t * const _File_name, const __std_access_rights _Desired_access,
				  const __std_fs_file_flags _Flags, __std_win_error * const _Err )
		{
			*_Err = __std_fs_open_handle( &_Raw, _File_name, _Desired_access, _Flags );
		}

		_Fs_file( const _Fs_file & ) = delete;
		_Fs_file & operator=( const _Fs_file & ) = delete;

		~_Fs_file()
		{
			__std_fs_close_handle( _Raw );
		}

		void * _Get() const
		{
			return reinterpret_cast< void * >( _Raw );
		}
	};

	struct _Is_slash_oper
	{ 
		constexpr bool operator()(
			const wchar_t _Ch ) const
		{ 
			return _Ch == L'\\' || _Ch == L'/';
		}
	};

	constexpr _Is_slash_oper _Is_slash{};




	std::error_code _Make_ec( __std_win_error _Errno ) noexcept
	{
		return { static_cast< int >( _Errno ), std::system_category() };
	}

	void _Throw_system_error_from_std_win_error( const __std_win_error _Errno )
	{
		throw ( std::system_error{ _Make_ec( _Errno ) } );
	}

	int _Check_convert_result( const __std_fs_convert_result _Result )
	{
		if( _Result._Err != __std_win_error::_Success )
		{
			_Throw_system_error_from_std_win_error( _Result._Err );
		}

		return _Result._Len;
	}

	std::wstring _Convert_narrow_to_wide( const __std_code_page _Code_page, const std::string_view _Input )
	{
		std::wstring _Output;

		if( !_Input.empty() )
		{
			if( _Input.size() > static_cast< size_t >( INT_MAX ) )
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}

			const int _Len = _Check_convert_result( __std_fs_convert_narrow_to_wide(
				_Code_page, _Input.data(), static_cast< int >( _Input.size() ), nullptr, 0 ) );

			_Output.resize( static_cast< size_t >( _Len ) );

			( void ) _Check_convert_result( __std_fs_convert_narrow_to_wide(
				_Code_page, _Input.data(), static_cast< int >( _Input.size() ), _Output.data(), _Len ) );
		}

		return _Output;
	}

	template <class _Traits, class _Alloc>
	std::basic_string<typename _Traits::char_type, _Traits, _Alloc> _Convert_wide_to_narrow(
		const __std_code_page _Code_page, const std::wstring_view _Input, const _Alloc & _Al )
	{
		std::basic_string<typename _Traits::char_type, _Traits, _Alloc> _Output( _Al );

		if( !_Input.empty() )
		{
			if( _Input.size() > static_cast< size_t >( INT_MAX ) )
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}

			const int _Len = _Check_convert_result( __std_fs_convert_wide_to_narrow(
				_Code_page, _Input.data(), static_cast< int >( _Input.size() ), nullptr, 0 ) );

			_Output.resize( static_cast< size_t >( _Len ) );

			const auto _Data_as_char = reinterpret_cast< char * >( _Output.data() );

			( void ) _Check_convert_result( __std_fs_convert_wide_to_narrow(
				_Code_page, _Input.data(), static_cast< int >( _Input.size() ), _Data_as_char, _Len ) );
		}

		return _Output;
	}

	std::wstring _Convert_utf32_to_wide( const std::u32string_view _Input )
	{
		std::wstring _Output;

		_Output.reserve( _Input.size() );

		for( const auto & _Code_point : _Input )
		{
			if( _Code_point <= 0xD7FFU )
			{
				_Output.push_back( static_cast< wchar_t >( _Code_point ) );
			}
			else if( _Code_point <= 0xDFFFU )
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}
			else if( _Code_point <= 0xFFFFU )
			{
				_Output.push_back( static_cast< wchar_t >( _Code_point ) );
			}
			else if( _Code_point <= 0x10FFFFU )
			{
				_Output.push_back( static_cast< wchar_t >( 0xD7C0U + ( _Code_point >> 10 ) ) );
				_Output.push_back( static_cast< wchar_t >( 0xDC00U + ( _Code_point & 0x3FFU ) ) );
			}
			else
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}
		}

		return _Output;
	}

	template <class _Traits, class _Alloc>
	std::basic_string<char32_t, _Traits, _Alloc> _Convert_wide_to_utf32(
		const std::wstring_view _Input, const _Alloc & _Al )
	{
		std::basic_string<char32_t, _Traits, _Alloc> _Output( _Al );

		_Output.reserve( _Input.size() );

		const wchar_t * _First = _Input.data();
		const wchar_t * const _Last = _First + _Input.size();

		for( ; _First != _Last; ++_First )
		{
			if( *_First <= 0xD7FFU )
			{
				_Output.push_back( *_First );
			}
			else if( *_First <= 0xDBFFU )
			{
				const char32_t _Leading = *_First;

				++_First;

				if( _First == _Last )
				{
					std::_Throw_system_error( std::errc::invalid_argument );
				}

				const char32_t _Trailing = *_First;

				if( 0xDC00U <= _Trailing && _Trailing <= 0xDFFFU )
				{
					_Output.push_back( 0xFCA02400U + ( _Leading << 10 ) + _Trailing );
				}
				else
				{
					std::_Throw_system_error( std::errc::invalid_argument );
				}
			}
			else if( *_First <= 0xDFFFU )
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}
			else
			{
				_Output.push_back( *_First );
			}
		}

		return _Output;
	}

	template <class _Traits, class _Alloc, class _EcharT = typename _Traits::char_type>
	std::basic_string<_EcharT, _Traits, _Alloc> _Convert_wide_to( const std::wstring_view _Input, const _Alloc & _Al )
	{
		if constexpr( std::is_same_v<_EcharT, char> )
		{
			return _Convert_wide_to_narrow<_Traits>( __std_fs_code_page(), _Input, _Al );
		}
		else if constexpr( std::is_same_v<_EcharT, char32_t> )
		{
			return _Convert_wide_to_utf32<_Traits>( _Input, _Al );
		}
		else
		{
			return std::basic_string<_EcharT, _Traits, _Alloc>( _Input.data(), _Input.data() + _Input.size(), _Al );
		}
	}

	template <class>
	constexpr bool _Is_EcharT = false;
	template <>
	constexpr bool _Is_EcharT<char> = true;
	template <>
	constexpr bool _Is_EcharT<wchar_t> = true;
	template <>
	constexpr bool _Is_EcharT<char16_t> = true;
	template <>
	constexpr bool _Is_EcharT<char32_t> = true;

	template <class _Ty, class = void>
	constexpr bool _Is_Source2 = false;

	template <class _Ty>
	constexpr bool _Is_Source2<_Ty, std::void_t<std::_Iter_value_t<std::decay_t<_Ty>>>> =
		_Is_EcharT<std::_Iter_value_t<std::decay_t<_Ty>>>;

	template <class _Ty>
	constexpr bool _Is_Source = _Is_Source2<_Ty>;

	class Path;

	template <>
	constexpr bool _Is_Source<Path> = false;

	template <class _Elem, class _Traits, class _Alloc>
	constexpr bool _Is_Source<std::basic_string<_Elem, _Traits, _Alloc>> = _Is_EcharT<_Elem>;

	template <class _Elem, class _Traits>
	constexpr bool _Is_Source<std::basic_string_view<_Elem, _Traits>> = _Is_EcharT<_Elem>;

	struct _Normal_conversion
	{
	};

	struct _Utf8_conversion
	{
	};


	template <class _Conversion>
	std::wstring _Convert_stringoid_to_wide( const std::string_view _Input, _Conversion )
	{
		static_assert( std::_Is_any_of_v<_Conversion, _Normal_conversion, _Utf8_conversion> );

		if constexpr( std::is_same_v<_Conversion, _Normal_conversion> )
		{
			return _Convert_narrow_to_wide( __std_fs_code_page(), _Input );
		}
		else
		{
			return _Convert_narrow_to_wide( __std_code_page::_Utf8, _Input );
		}
	}

	template <class _Conversion>
	std::wstring _Convert_stringoid_to_wide( const std::wstring_view _Input, _Conversion )
	{
		static_assert(
			std::is_same_v<_Conversion, _Normal_conversion>, "invalid value_type, see N4810 D.17 [depr.fs.path.factory]/1" );
		return std::wstring( _Input );
	}

	template <class _Conversion>
	std::wstring _Convert_stringoid_to_wide( const std::u16string_view _Input, _Conversion )
	{
		static_assert(
			std::is_same_v<_Conversion, _Normal_conversion>, "invalid value_type, see N4810 D.17 [depr.fs.path.factory]/1" );
		return std::wstring( _Input.data(), _Input.data() + _Input.size() );
	}

	template <class _Conversion>
	std::wstring _Convert_stringoid_to_wide( const std::u32string_view _Input, _Conversion )
	{
		static_assert(
			std::is_same_v<_Conversion, _Normal_conversion>, "invalid value_type, see N4810 D.17 [depr.fs.path.factory]/1" );
		return _Convert_utf32_to_wide( _Input );
	}

	template <class _EcharT, class _Traits>
	auto _Stringoid_from_Source( const std::basic_string_view<_EcharT, _Traits> & _Source )
	{
		return std::basic_string_view<_EcharT>( _Source.data(), _Source.size() );
	}

	template <class _EcharT, class _Traits, class _Alloc>
	auto _Stringoid_from_Source( const std::basic_string<_EcharT, _Traits, _Alloc> & _Source )
	{
		return std::basic_string_view<_EcharT>( _Source.data(), _Source.size() );
	}

	template <class _Src>
	auto _Stringoid_from_Source( const _Src & _Source )
	{
		using _EcharT = std::_Iter_value_t<std::decay_t<_Src>>;
		if constexpr( std::is_pointer_v<std::_Unwrapped_unverified_t<_Src>> )
		{
			return std::basic_string_view<_EcharT>( std::_Get_unwrapped_unverified( _Source ) );
		}
		else if constexpr( is_pointer_v<_Unwrapped_t<_Src>> )
		{
			const auto _Data = std::_Get_unwrapped( _Source );
			auto _Next = _Source;
			while( *_Next != _EcharT{} )
			{
				++_Next;
			}

			return std::basic_string_view<_EcharT>( _Data, static_cast< size_t >( std::_Get_unwrapped( _Next ) - _Data ) );
		}
		else
		{
			std::basic_string<_EcharT> _Str;
			for( auto _Next = _Source; *_Next != _EcharT{}; ++_Next )
			{
				_Str.push_back( *_Next );
			}

			return _Str;
		}
	}

	template <class _EcharT, size_t _SourceSize>
	std::basic_string_view<_EcharT> _Stringoid_from_Source( const _EcharT( &_Src )[_SourceSize] )
	{
		for( size_t _Idx = 0;; ++_Idx )
		{
			_STL_VERIFY( _Idx < _SourceSize, "path input not null terminated" );
			if( _Src[_Idx] == _EcharT{} )
			{
				return std::basic_string_view<_EcharT>( _Src, _Idx );
			}
		}
	}

	template <class _Src, class _Conversion = _Normal_conversion>
	std::wstring _Convert_Source_to_wide( const _Src & _Source, _Conversion _Tag = {} )
	{
		return _Convert_stringoid_to_wide( _Stringoid_from_Source( _Source ), _Tag );
	}

	template <class _InIt>
	auto _Stringoid_from_range( _InIt _First, _InIt _Last )
	{
		_Adl_verify_range( _First, _Last );
		const auto _UFirst = std::_Get_unwrapped( _First );
		const auto _ULast = std::_Get_unwrapped( _Last );

		if constexpr( is_pointer_v<decltype( _UFirst )> )
		{
			return std::basic_string_view<_Iter_value_t<_InIt>>( _UFirst, static_cast< size_t >( _ULast - _UFirst ) );
		}
		else
		{
			return std::basic_string<_Iter_value_t<_InIt>>( _UFirst, _ULast );
		}
	}

	template <class _InIt, class _Conversion = _Normal_conversion>
	std::wstring _Convert_range_to_wide( _InIt _First, _InIt _Last, _Conversion _Tag = {} )
	{
		return _Convert_stringoid_to_wide( _Stringoid_from_range( _First, _Last ), _Tag );
	}

	std::wstring _Convert_stringoid_with_locale_to_wide( const std::string_view _Input, const std::locale & _Loc )
	{
		const auto & _Facet = std::use_facet<std::codecvt<wchar_t, char, mbstate_t>>( _Loc );

		std::wstring _Output( _Input.size(), L'\0' );

		for( ;;)
		{
			mbstate_t _State{};
			const char * const _From_begin = _Input.data();
			const char * const _From_end = _From_begin + _Input.size();
			const char * _From_next = nullptr;
			wchar_t * const _To_begin = _Output.data();
			wchar_t * const _To_end = _To_begin + _Output.size();
			wchar_t * _To_next = nullptr;

			const auto _Result = _Facet.in( _State, _From_begin, _From_end, _From_next, _To_begin, _To_end, _To_next );

			if( _From_next < _From_begin || _From_next > _From_end || _To_next < _To_begin || _To_next > _To_end )
			{
				std::_Throw_system_error( std::errc::invalid_argument );
			}

			switch( _Result )
			{
			case std::codecvt_base::ok:
				_Output.resize( static_cast< size_t >( _To_next - _To_begin ) );
				return _Output;

			case std::codecvt_base::partial:
				if( ( _From_next == _From_end && _To_next != _To_end ) || _Output.size() > _Output.max_size() / 2 )
				{
					std::_Throw_system_error( std::errc::invalid_argument );
				}

				_Output.resize( _Output.size() * 2 );
				break;

			case std::codecvt_base::error:
			case std::codecvt_base::noconv:
			default:
				std::_Throw_system_error( std::errc::invalid_argument );
			}
		}
	}

	template <class _Ty>
	_Ty _Unaligned_load( const void * _Ptr )
	{
		static_assert( std::is_trivial_v<_Ty>, "Unaligned loads require trivial types" );
		_Ty _Tmp;
		::memcpy( &_Tmp, _Ptr, sizeof( _Tmp ) );
		return _Tmp;
	}

	bool _Is_drive_prefix( const wchar_t * const _First )
	{
		auto _Value = _Unaligned_load<unsigned int>( _First );
		_Value &= 0xFFFF'FFDFu;
		_Value -= ( static_cast< unsigned int >( L':' ) << ( sizeof( wchar_t ) * CHAR_BIT ) ) | L'A';
		return _Value < 26;
	}

	bool _Has_drive_letter_prefix( const wchar_t * const _First, const wchar_t * const _Last )
	{
		return _Last - _First >= 2 && _Is_drive_prefix( _First );
	}

	const wchar_t * _Find_root_name_end( const wchar_t * const _First, const wchar_t * const _Last )
	{
		if( _Last - _First < 2 )
		{
			return _First;
		}

		if( _Has_drive_letter_prefix( _First, _Last ) )
		{
			return _First + 2;
		}

		if( !_Is_slash( _First[0] ) )
		{
			return _First;
		}

		if( _Last - _First >= 4 && _Is_slash( _First[3] ) && ( _Last - _First == 4 || !_Is_slash( _First[4] ) )
			&& ( ( _Is_slash( _First[1] ) && ( _First[2] == L'?' || _First[2] == L'.' ) )
				 || ( _First[1] == L'?' && _First[2] == L'?' ) ) )
		{
			return _First + 3;
		}

		if( _Last - _First >= 3 && _Is_slash( _First[1] ) && !_Is_slash( _First[2] ) )
		{
			return std::find_if( _First + 3, _Last, _Is_slash );
		}

		return _First;
	}

	std::wstring_view _Parse_root_name( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		return std::wstring_view( _First, static_cast< size_t >( _Find_root_name_end( _First, _Last ) - _First ) );
	}

	const wchar_t * _Find_relative_path( const wchar_t * const _First, const wchar_t * const _Last )
	{
		return std::find_if_not( _Find_root_name_end( _First, _Last ), _Last, _Is_slash );
	}

	std::wstring_view _Parse_root_directory( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		const auto _Root_name_end = _Find_root_name_end( _First, _Last );
		const auto _Relative_path = std::find_if_not( _Root_name_end, _Last, _Is_slash );
		return std::wstring_view( _Root_name_end, static_cast< size_t >( _Relative_path - _Root_name_end ) );
	}

	std::wstring_view _Parse_root_path( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		return std::wstring_view( _First, static_cast< size_t >( _Find_relative_path( _First, _Last ) - _First ) );
	}

	std::wstring_view _Parse_relative_path( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		const auto _Relative_path = _Find_relative_path( _First, _Last );
		return std::wstring_view( _Relative_path, static_cast< size_t >( _Last - _Relative_path ) );
	}

	std::wstring_view _Parse_parent_path( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		auto _Last = _First + _Str.size();
		const auto _Relative_path = _Find_relative_path( _First, _Last );
		while( _Relative_path != _Last && !_Is_slash( _Last[-1] ) )
		{
			--_Last;
		}

		while( _Relative_path != _Last && _Is_slash( _Last[-1] ) )
		{
			--_Last;
		}

		return std::wstring_view( _First, static_cast< size_t >( _Last - _First ) );
	}

	const wchar_t * _Find_filename( const wchar_t * const _First, const wchar_t * _Last )
	{
		const auto _Relative_path = _Find_relative_path( _First, _Last );
		while( _Relative_path != _Last && !_Is_slash( _Last[-1] ) )
		{
			--_Last;
		}

		return _Last;
	}

	std::wstring_view _Parse_filename( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		const auto _Filename = _Find_filename( _First, _Last );
		return std::wstring_view( _Filename, static_cast< size_t >( _Last - _Filename ) );
	}

	constexpr const wchar_t * _Find_extension( const wchar_t * const _Filename, const wchar_t * const _Ads )
	{
		auto _Extension = _Ads;
		if( _Filename == _Extension )
		{
			return _Ads;
		}

		--_Extension;
		if( _Filename == _Extension )
		{
			return _Ads;
		}

		if( *_Extension == L'.' )
		{
			if( _Filename == _Extension - 1 && _Extension[-1] == L'.' )
			{
				return _Ads;
			}
			else
			{
				return _Extension;
			}
		}

		while( _Filename != --_Extension )
		{
			if( *_Extension == L'.' )
			{
				return _Extension;
			}
		}

		return _Ads;
	}

	std::wstring_view _Parse_stem( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		const auto _Filename = _Find_filename( _First, _Last );
		const auto _Ads =
			std::find( _Filename, _Last, L':' );
		const auto _Extension = _Find_extension( _Filename, _Ads );
		return std::wstring_view( _Filename, static_cast< size_t >( _Extension - _Filename ) );
	}

	std::wstring_view _Parse_extension( const std::wstring_view _Str )
	{
		const auto _First = _Str.data();
		const auto _Last = _First + _Str.size();
		const auto _Filename = _Find_filename( _First, _Last );
		const auto _Ads =
			std::find( _Filename, _Last, L':' );
		const auto _Extension = _Find_extension( _Filename, _Ads );
		return std::wstring_view( _Extension, static_cast< size_t >( _Ads - _Extension ) );
	}

	int _Range_compare( const wchar_t * const _Lfirst, const wchar_t * const _Llast,
						const wchar_t * const _Rfirst, const wchar_t * const _Rlast )
	{
		return std::_Traits_compare<std::char_traits<wchar_t>>(
			_Lfirst, static_cast< size_t >( _Llast - _Lfirst ), _Rfirst, static_cast< size_t >( _Rlast - _Rfirst ) );
	}

	bool _Is_drive_prefix_with_slash_slash_question( const std::wstring_view _Text )
	{
		using namespace std::string_view_literals;
		return _Text.size() >= 6 && _Text._Starts_with( LR"(\\?\)"sv ) && _Is_drive_prefix( _Text.data() + 4 );
	}

	bool _Is_dot_or_dotdot( const __std_fs_find_data & _Data )
	{
		if( _Data._File_name[0] != L'.' )
		{
			return false;
		}

		const auto _Second_char = _Data._File_name[1];
		if( _Second_char == 0 )
		{
			return true;
		}

		if( _Second_char != L'.' )
		{
			return false;
		}

		return _Data._File_name[2] == 0;
	}

	struct _Find_file_handle
	{
		__std_fs_dir_handle _Handle = __std_fs_dir_handle::_Invalid;

		_Find_file_handle() noexcept = default;
		_Find_file_handle( _Find_file_handle && _Rhs ) noexcept
			: _Handle( std::exchange( _Rhs._Handle, __std_fs_dir_handle::_Invalid ) )
		{
		}

		_Find_file_handle & operator=( _Find_file_handle && _Rhs ) noexcept
		{
			auto _Tmp = std::exchange( _Rhs._Handle, __std_fs_dir_handle::_Invalid );
			_Tmp = std::exchange( _Handle, _Tmp );
			__std_fs_directory_iterator_close( _Tmp );
			return *this;
		}

		__std_win_error _Open( const wchar_t * _Path_spec, __std_fs_find_data * _Results ) noexcept
		{
			return __std_fs_directory_iterator_open( _Path_spec, &_Handle, _Results );
		}

		~_Find_file_handle() noexcept
		{
			__std_fs_directory_iterator_close( _Handle );
		}

		explicit operator bool() const noexcept
		{
			return _Handle != __std_fs_dir_handle::_Invalid;
		}
	};

	template <class _Base_iter>
	class _Path_iterator;

	class Path
	{
		template <class _Base_iter>
		friend class _Path_iterator;
		friend __std_win_error _Absolute( Path & _Result, const std::wstring & _Text );
		friend __std_win_error _Canonical( Path & _Result, const std::wstring & _Text );
		friend Path temp_directory_path( std::error_code & _Ec );
		friend __std_win_error _Current_path( Path & _Result ) noexcept;
		friend void current_path( const Path & _To );
		friend void current_path( const Path & _To, std::error_code & _Ec ) noexcept;
		friend __std_win_error _Read_symlink( const Path & _Symlink_path, Path & _Result ) noexcept;

	public:
		using value_type = wchar_t;
		using string_type = std::wstring;

		static constexpr wchar_t preferred_separator = L'\\';

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

		Path( string_type && _Source ) : _Text( std::move( _Source ) )
		{
		}

		Path( string_type && _Source, format ) : _Text( std::move( _Source ) )
		{
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path( const _Src & _Source, format = auto_format ) : _Text( _Convert_Source_to_wide( _Source ) )
		{
		}

		template <class _InIt>
		Path( _InIt _First, _InIt _Last, format = auto_format ) : _Text( _Convert_range_to_wide( _First, _Last ) )
		{
			static_assert( _Is_EcharT<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3" );
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path( const _Src & _Source, const std::locale & _Loc, format = auto_format )
			: _Text( _Convert_stringoid_with_locale_to_wide( _Stringoid_from_Source( _Source ), _Loc ) )
		{
			using _Stringoid = decltype( _Stringoid_from_Source( _Source ) );
			static_assert( std::is_same_v<typename _Stringoid::value_type, char>,
						   "invalid value_type, see N4810 29.11.7.4.1 [fs.path.construct]/6" );
		}

		template <class _InIt>
		Path( _InIt _First, _InIt _Last, const std::locale & _Loc, format = auto_format )
			: _Text( _Convert_stringoid_with_locale_to_wide( _Stringoid_from_range( _First, _Last ), _Loc ) )
		{
			static_assert( std::is_same_v<_Iter_value_t<_InIt>, char>,
						   "invalid value_type, see N4810 29.11.7.4.1 [fs.path.construct]/6" );
		}

		Path & operator=( string_type && _Source ) noexcept
		{
			_Text = std::move( _Source );
			return *this;
		}

		Path & assign( string_type && _Source ) noexcept
		{
			_Text = std::move( _Source );
			return *this;
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & operator=( const _Src & _Source )
		{
			_Text = _Convert_Source_to_wide( _Source );
			return *this;
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & assign( const _Src & _Source )
		{
			_Text = _Convert_Source_to_wide( _Source );
			return *this;
		}

		template <class _InIt>
		Path & assign( _InIt _First, _InIt _Last )
		{
			static_assert( _Is_EcharT<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3" );
			_Text = _Convert_range_to_wide( _First, _Last );
			return *this;
		}

		Path & operator/=( const Path & _Other )
		{
			if( _Other.is_absolute() )
			{
				return operator=( _Other );
			}

			const auto _My_first = _Text.data();
			const auto _My_last = _My_first + _Text.size();
			const auto _Other_first = _Other._Text.data();
			const auto _Other_last = _Other_first + _Other._Text.size();
			const auto _My_root_name_end = _Find_root_name_end( _My_first, _My_last );
			const auto _Other_root_name_end = _Find_root_name_end( _Other_first, _Other_last );
			if( _Other_first != _Other_root_name_end
				&& _Range_compare( _My_first, _My_root_name_end, _Other_first, _Other_root_name_end ) != 0 )
			{
				return operator=( _Other );
			}

			if( _Other_root_name_end != _Other_last && _Is_slash( *_Other_root_name_end ) )
			{
				_Text.erase( static_cast< size_t >( _My_root_name_end - _My_first ) );
			}
			else
			{
				if( _My_root_name_end == _My_last )
				{
					if( _My_root_name_end - _My_first >= 3 )
					{
						_Text.push_back( preferred_separator );
					}
				}
				else
				{
					if( !_Is_slash( _My_last[-1] ) )
					{
						_Text.push_back( preferred_separator );
					}
				}
			}
			_Text.append( _Other_root_name_end, static_cast< size_t >( _Other_last - _Other_root_name_end ) );
			return *this;
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & operator/=( const _Src & _Source )
		{
			return operator/=( Path( _Source ) );
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & append( const _Src & _Source )
		{
			return operator/=( Path( _Source ) );
		}

		template <class _InIt>
		Path & append( _InIt _First, _InIt _Last )
		{
			static_assert( _Is_EcharT<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3" );
			return operator/=( Path( _First, _Last ) );
		}

		Path & operator+=( const Path & _Added )
		{
			_Text._Orphan_all();
			_Text += _Added._Text;
			return *this;
		}

		Path & operator+=( const string_type & _Added )
		{
			_Text._Orphan_all();
			_Text += _Added;
			return *this;
		}

		Path & operator+=( const std::wstring_view _Added )
		{
			_Text._Orphan_all();
			_Text += _Added;
			return *this;
		}

		Path & operator+=( const value_type * const _Added )
		{
			_Text._Orphan_all();
			_Text += _Added;
			return *this;
		}

		Path & operator+=( const value_type _Added )
		{
			_Text._Orphan_all();
			_Text += _Added;
			return *this;
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & operator+=( const _Src & _Added )
		{
			return operator+=( Path( _Added ) );
		}

		template <class _EcharT, std::enable_if_t<_Is_EcharT<_EcharT>, int> = 0>
		Path & operator+=( const _EcharT _Added )
		{
			return operator+=( Path( &_Added, &_Added + 1 ) );
		}

		template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
		Path & concat( const _Src & _Added )
		{
			return operator+=( Path( _Added ) );
		}

		template <class _InIt>
		Path & concat( _InIt _First, _InIt _Last )
		{
			static_assert( _Is_EcharT<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3" );
			return operator+=( Path( _First, _Last ) );
		}

		void clear() noexcept
		{
			_Text._Orphan_all();
			_Text.clear();
		}

		Path & make_preferred() noexcept
		{
			_Text._Orphan_all();
			std::replace( _Text.begin(), _Text.end(), L'/', L'\\' );
			return *this;
		}

		Path & remove_filename() noexcept
		{
			const auto _First = _Text.data();
			const auto _Last = _First + _Text.size();
			const auto _Filename = _Find_filename( _First, _Last );
			_Text._Orphan_all();
			_Text.erase( static_cast< size_t >( _Filename - _First ) );
			return *this;
		}

		void _Remove_filename_and_separator() noexcept
		{
			const auto _First = _Text.data();
			const auto _Last = _First + _Text.size();
			const auto _Root_name_end = _Find_root_name_end( _First, _Last );
			const auto _Root_dir_end =
				( _Root_name_end != _Last && _Is_slash( *_Root_name_end ) ) ? _Root_name_end + 1 : _Root_name_end;

			using _Reverse_iter = std::reverse_iterator<const wchar_t *>;

			const _Reverse_iter _Rbegin{ _Last };
			const _Reverse_iter _Rend{ _Root_dir_end };

			const auto _Rslash_first = std::find_if( _Rbegin, _Rend, _Is_slash );
			const auto _Rslash_last = std::find_if_not( _Rslash_first, _Rend, _Is_slash );

			const _Reverse_iter _Rlast{ _First };

			_Text._Orphan_all();
			_Text.erase( static_cast< size_t >( _Rlast - _Rslash_last ) );
		}

		Path & replace_filename( const Path & _Replacement )
		{
			remove_filename();
			return operator/=( _Replacement );
		}

		Path & replace_extension(/* const path& _Replacement = path() */ ) noexcept
		{
			const wchar_t * _First = _Text.data();
			const auto _Last = _First + _Text.size();
			const auto _Filename = _Find_filename( _First, _Last );
			const auto _Ads = std::find( _Filename, _Last, L':' );
			const auto _Extension = _Find_extension( _Filename, _Ads );
			_Text._Orphan_all();
			_Text.erase( static_cast< size_t >( _Extension - _First ) );
			return *this;
		}

		Path & replace_extension( const Path & _Replacement )
		{
			replace_extension();
			if( !_Replacement.empty() && _Replacement._Text[0] != L'.' )
			{
				_Text.push_back( L'.' );
			}

			return operator+=( _Replacement );
		}

		void swap( Path & _Rhs ) noexcept
		{
			_Text.swap( _Rhs._Text );
		}

		const string_type & native() const noexcept
		{
			return _Text;
		}

		const value_type * c_str() const noexcept
		{
			return _Text.c_str();
		}

		operator string_type() const
		{
			return _Text;
		}

		template <class _EcharT, class _Traits = std::char_traits<_EcharT>, class _Alloc = std::allocator<_EcharT>,
			std::enable_if_t<_Is_EcharT<_EcharT>, int> = 0>
			std::basic_string<_EcharT, _Traits, _Alloc> string( const _Alloc & _Al = _Alloc() ) const
		{
			return _Convert_wide_to<_Traits>( _Text, _Al );
		}

		std::string string() const
		{
			return string<char>();
		}

		std::wstring wstring() const
		{
			return _Text;
		}

		auto u8string() const
		{
#ifdef __cpp_lib_char8_t
			using _U8Ty = char8_t;
#else 
			using _U8Ty = char;
#endif 
			return _Convert_wide_to_narrow<std::char_traits<_U8Ty>>( __std_code_page::_Utf8, _Text, std::allocator<_U8Ty>{} );
		}

		std::u16string u16string() const
		{
			return string<char16_t>();
		}

		std::u32string u32string() const
		{
			return string<char32_t>();
		}

		template <class _EcharT, class _Traits = std::char_traits<_EcharT>, class _Alloc = std::allocator<_EcharT>,
			std::enable_if_t<_Is_EcharT<_EcharT>, int> = 0>
			std::basic_string<_EcharT, _Traits, _Alloc> generic_string( const _Alloc & _Al = _Alloc() ) const
		{
			using _Alwide = std::_Rebind_alloc_t<_Alloc, wchar_t>;
			_Alwide _Al_wchar( _Al );
			std::basic_string<wchar_t, std::char_traits<wchar_t>, _Alwide> _Generic_str( _Al_wchar );
			_Generic_str.resize( _Text.size() );
			std::replace_copy( _Text.begin(), _Text.end(), _Generic_str.begin(), L'\\', L'/' );
			return _Convert_wide_to<_Traits>( _Generic_str, _Al );
		}

		std::string generic_string() const
		{
			return generic_string<char>();
		}

		std::wstring generic_wstring() const
		{
			std::wstring _Result;
			_Result.resize( _Text.size() );
			std::replace_copy( _Text.begin(), _Text.end(), _Result.begin(), L'\\', L'/' );
			return _Result;
		}

		auto generic_u8string() const
		{
			auto _Result = u8string();
			using _U8Ty = decltype( _Result )::value_type;
			std::replace( _Result.begin(), _Result.end(), _U8Ty{ u8'\\' }, _U8Ty{ u8'/' } );
			return _Result;
		}

		std::u16string generic_u16string() const
		{
			std::u16string _Result = u16string();
			std::replace( _Result.begin(), _Result.end(), u'\\', u'/' );
			return _Result;
		}

		std::u32string generic_u32string() const
		{
			std::u32string _Result = u32string();
			std::replace( _Result.begin(), _Result.end(), U'\\', U'/' );
			return _Result;
		}

		int compare( const Path & _Other ) const noexcept
		{
			return compare( static_cast< std::wstring_view >( _Other._Text ) );
		}

		int compare( const string_type & _Other ) const noexcept
		{
			return compare( static_cast< std::wstring_view >( _Other ) );
		}

		int compare( const std::basic_string_view<value_type> _Other ) const noexcept
		{
			const auto _My_first = _Text.data();
			const auto _My_last = _My_first + _Text.size();
			const auto _My_root_name_end = _Find_root_name_end( _My_first, _My_last );
			const auto _Other_first = _Other.data();
			const auto _Other_last = _Other_first + _Other.size();
			const auto _Other_root_name_end = _Find_root_name_end( _Other_first, _Other_last );

			const int _Root_cmp = _Range_compare( _My_first, _My_root_name_end, _Other_first, _Other_root_name_end );
			if( _Root_cmp != 0 )
			{
				return _Root_cmp;
			}

			auto _My_relative = std::find_if_not( _My_root_name_end, _My_last, _Is_slash );
			auto _Other_relative = std::find_if_not( _Other_root_name_end, _Other_last, _Is_slash );
			const bool _My_has_root_name = _My_root_name_end != _My_relative;
			const bool _Other_has_root_name = _Other_root_name_end != _Other_relative;
			const int _Root_name_cmp = _My_has_root_name - _Other_has_root_name;
			if( _Root_name_cmp != 0 )
			{
				return _Root_name_cmp;
			}

			for( ;;)
			{
				const bool _My_empty = _My_relative == _My_last;
				const bool _Other_empty = _Other_relative == _Other_last;
				const int _Empty_cmp = _Other_empty - _My_empty;
				if( _My_empty || _Empty_cmp != 0 )
				{
					return _Empty_cmp;
				}

				const bool _My_slash = _Is_slash( *_My_relative );
				const bool _Other_slash = _Is_slash( *_Other_relative );
				const int _Slash_cmp = _Other_slash - _My_slash;
				if( _Slash_cmp != 0 )
				{
					return _Slash_cmp;
				}

				if( _My_slash )
				{
					_My_relative = std::find_if_not( _My_relative + 1, _My_last, _Is_slash );
					_Other_relative = std::find_if_not( _Other_relative + 1, _Other_last, _Is_slash );
					continue;
				}

				const int _Cmp = *_My_relative - *_Other_relative;
				if( _Cmp != 0 )
				{
					return _Cmp;
				}

				++_My_relative;
				++_Other_relative;
			}
		}

		int compare( const value_type * const _Other ) const noexcept
		{
			return compare( static_cast< std::wstring_view >( _Other ) );
		}

		Path root_name() const
		{
			return _Parse_root_name( _Text );
		}

		Path root_directory() const
		{
			return _Parse_root_directory( _Text );
		}

		Path root_path() const
		{
			return _Parse_root_path( _Text );
		}

		Path relative_path() const
		{
			return _Parse_relative_path( _Text );
		}

		Path parent_path() const
		{
			return _Parse_parent_path( _Text );
		}

		Path filename() const
		{
			return _Parse_filename( _Text );
		}

		Path stem() const
		{
			return _Parse_stem( _Text );
		}

		Path extension() const
		{
			return _Parse_extension( _Text );
		}

		bool empty() const noexcept
		{
			return _Text.empty();
		}

		bool has_root_name() const noexcept
		{
			return !_Parse_root_name( _Text ).empty();
		}

		bool has_root_directory() const noexcept
		{
			return !_Parse_root_directory( _Text ).empty();
		}

		bool has_root_path() const noexcept
		{
			return !_Parse_root_path( _Text ).empty();
		}

		bool has_relative_path() const noexcept
		{
			return !_Parse_relative_path( _Text ).empty();
		}

		bool has_parent_path() const noexcept
		{
			return !_Parse_parent_path( _Text ).empty();
		}

		bool has_filename() const noexcept
		{
			return !_Parse_filename( _Text ).empty();
		}

		bool has_stem() const noexcept
		{
			return !_Parse_stem( _Text ).empty();
		}

		bool has_extension() const noexcept
		{
			return !_Parse_extension( _Text ).empty();
		}

		bool is_absolute() const noexcept
		{
			const auto _First = _Text.data();
			const auto _Last = _First + _Text.size();
			if( _Has_drive_letter_prefix( _First, _Last ) )
			{
				return _Last - _First >= 3 && _Is_slash( _First[2] );
			}
			return _First != _Find_root_name_end( _First, _Last );
		}

		bool is_relative() const noexcept
		{
			return !is_absolute();
		}

		Path lexically_normal() const
		{
			using namespace std::string_view_literals;

			constexpr std::wstring_view _Dot = L"."sv;
			constexpr std::wstring_view _Dot_dot = L".."sv;
			if( empty() )
			{
				return {};
			}
			const auto _First = _Text.data();
			const auto _Last = _First + _Text.size();
			const auto _Root_name_end = _Find_root_name_end( _First, _Last );
			string_type _Normalized( _First, _Root_name_end );
			std::replace( _Normalized.begin(), _Normalized.end(), L'/', L'\\' );
			std::list<std::wstring_view> _Lst;
			for( auto _Next = _Root_name_end; _Next != _Last;)
			{
				if( _Is_slash( *_Next ) )
				{
					if( _Lst.empty() || !_Lst.back().empty() )
					{
						_Lst.emplace_back();
					}

					++_Next;
				}
				else
				{
					const auto _Filename_end = std::find_if( _Next + 1, _Last, _Is_slash );
					_Lst.emplace_back( _Next, static_cast< size_t >( _Filename_end - _Next ) );
					_Next = _Filename_end;
				}
			}
			for( auto _Next = _Lst.begin(); _Next != _Lst.end();)
			{
				if( *_Next == _Dot )
				{
					_Next = _Lst.erase( _Next );

					if( _Next != _Lst.end() )
					{
						_Next = _Lst.erase( _Next );
					}
				}
				else
				{
					++_Next;
				}
			}
			for( auto _Next = _Lst.begin(); _Next != _Lst.end();)
			{
				auto _Prev = _Next;

				++_Next;

				if( *_Prev == _Dot_dot && _Prev != _Lst.begin() && --_Prev != _Lst.begin() && *--_Prev != _Dot_dot )
				{
					if( _Next != _Lst.end() )
					{
						++_Next;
					}

					_Lst.erase( _Prev, _Next );
				}
			}
			if( !_Lst.empty() && _Lst.front().empty() )
			{
				for( auto _Next = _Lst.begin(); _Next != _Lst.end();)
				{
					if( *_Next == _Dot_dot )
					{
						_Next = _Lst.erase( _Next );

						if( _Next != _Lst.end() )
						{
							_Next = _Lst.erase( _Next );
						}
					}
					else
					{
						++_Next;
					}
				}
			}
			if( _Lst.size() >= 2 && _Lst.back().empty() && *( std::prev( _Lst.end(), 2 ) ) == _Dot_dot )
			{
				_Lst.pop_back();
			}
			for( const auto & _Elem : _Lst )
			{
				if( _Elem.empty() )
				{
					_Normalized += preferred_separator;
				}
				else
				{
					_Normalized += _Elem;
				}
			}
			if( _Normalized.empty() )
			{
				_Normalized = _Dot;
			}
			Path _Result( std::move( _Normalized ) );

			return _Result;
		}

		Path lexically_relative( const Path & _Base ) const;

		Path lexically_proximate( const Path & _Base ) const
		{
			Path _Result = lexically_relative( _Base );

			if( _Result.empty() )
			{
				_Result = *this;
			}

			return _Result;
		}

		using iterator = _Path_iterator<string_type::const_iterator>;
		using const_iterator = iterator;

		iterator begin() const;
		iterator end() const noexcept;

		template <class _Elem, class _Traits>
		friend std::basic_ostream<_Elem, _Traits> & operator<<( std::basic_ostream<_Elem, _Traits> & _Ostr, const Path & _Path )
		{
			return _Ostr << std::quoted( _Path.string<_Elem, _Traits>() );
		}

		template <class _Elem, class _Traits>
		friend std::basic_istream<_Elem, _Traits> & operator>>( std::basic_istream<_Elem, _Traits> & _Istr, Path & _Path )
		{
			std::basic_string<_Elem, _Traits> _Tmp;
			_Istr >> std::quoted( _Tmp );
			_Path = std::move( _Tmp );
			return _Istr;
		}

		friend bool operator==( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) == 0;
		}

		friend bool operator!=( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) != 0;
		}

		friend bool operator<( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) < 0;
		}

		friend bool operator>( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) > 0;
		}

		friend bool operator<=( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) <= 0;
		}

		friend bool operator>=( const Path & _Left, const Path & _Right ) noexcept
		{
			return _Left.compare( _Right ) >= 0;
		}

		friend Path operator/( const Path & _Left, const Path & _Right )
		{
			return Path( _Left ) /= _Right;
		}

	private:
		string_type _Text;
	};

	template <class _Src, std::enable_if_t<_Is_Source<_Src>, int> = 0>
	Path u8path( const _Src & _Source )
	{
		return Path( _Convert_Source_to_wide( _Source, _Utf8_conversion{} ) );
	}

	template <class _InIt>
	Path u8path( _InIt _First, _InIt _Last )
	{
		static_assert( _Is_EcharT<_Iter_value_t<_InIt>>, "invalid value_type, see N4810 29.11.4 [fs.req]/3" );
		return Path( _Convert_range_to_wide( _First, _Last, _Utf8_conversion{} ) );
	}

	template <class _Base_iter>
	class _Path_iterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = Path;
		using difference_type = ptrdiff_t;
		using pointer = const Path *;
		using reference = const Path &;

		_Path_iterator() = default;

		_Path_iterator( const _Base_iter & _Position_, const Path * _Mypath_ ) noexcept
			: _Position( _Position_ ), _Element(), _Mypath( _Mypath_ )
		{
		}

		_Path_iterator( const _Base_iter & _Position_, std::wstring_view _Element_text, const Path * _Mypath_ )
			: _Position( _Position_ ), _Element( _Element_text ), _Mypath( _Mypath_ )
		{
		}

		_Path_iterator( const _Path_iterator & ) = default;
		_Path_iterator( _Path_iterator && ) = default;
		_Path_iterator & operator=( const _Path_iterator & ) = default;
		_Path_iterator & operator=( _Path_iterator && ) = default;

		reference operator*() const noexcept
		{
			return _Element;
		}

		pointer operator->() const noexcept
		{
			return std::addressof( _Element );
		}

		_Path_iterator & operator++()
		{
			const auto & _Text = _Mypath->native();
			const auto _Size = _Element.native().size();
			std::_Adl_verify_range( _Text.begin(), _Position );
			const auto _Begin = _Text.data();
			const auto _End = _Begin + _Text.size();
			std::_Adl_verify_range( _Begin, _Position );
			if( _Begin == std::_Get_unwrapped( _Position ) )
			{
				_Position += static_cast< ptrdiff_t >( _Size );
				const auto _First = _Text.data();
				const auto _Last = _First + _Text.size();
				const auto _Root_name_end = _Find_root_name_end( _First, _Last );
				const auto _Root_directory_end = std::find_if_not( _Root_name_end, _Last, _Is_slash );
				if( _First != _Root_name_end && _Root_name_end != _Root_directory_end )
				{
					_Element._Text.assign( _Root_name_end, _Root_directory_end );
					return *this;
				}
			}
			else if( _Is_slash( *_Position ) )
			{
				if( _Size == 0 )
				{
					++_Position;
					return *this;
				}
				_Position += static_cast< ptrdiff_t >( _Size );
			}
			else
			{
				_Position += static_cast< ptrdiff_t >( _Size );
			}

			if( std::_Get_unwrapped( _Position ) == _End )
			{
				_Element.clear();
				return *this;
			}
			while( _Is_slash( *_Position ) )
			{
				if( std::_Get_unwrapped( ++_Position ) == _End )
				{
					--_Position;
					_Element.clear();
					return *this;
				}
			}

			_Element._Text.assign( std::_Get_unwrapped( _Position ), std::find_if( std::_Get_unwrapped( _Position ), _End, _Is_slash ) );
			return *this;
		}

		_Path_iterator operator++( int )
		{
			_Path_iterator _Tmp = *this;
			++ * this;
			return _Tmp;
		}

		_Path_iterator & operator--()
		{
			const auto & _Text = _Mypath->native();
			_Adl_verify_range( _Text.begin(), _Position );
			const auto _First = _Text.data();
			_Adl_verify_range( _First, _Position );
			const auto _Last = _First + _Text.size();
			const auto _Root_name_end_ptr = _Find_root_name_end( _First, _Last );
			const auto _Root_directory_end_ptr = std::find_if_not( _Root_name_end_ptr, _Last, _Is_slash );

			if( _Root_name_end_ptr != _Root_directory_end_ptr && std::_Get_unwrapped( _Position ) == _Root_directory_end_ptr )
			{
				_Seek_wrapped( _Position, _Root_name_end_ptr );
				_Element._Text.assign(
					_Root_name_end_ptr, static_cast< size_t >( _Root_directory_end_ptr - _Root_name_end_ptr ) );
				return *this;
			}

			if( _First != _Root_name_end_ptr && std::_Get_unwrapped( _Position ) == _Root_name_end_ptr )
			{
				_Seek_wrapped( _Position, _First );
				_Element._Text.assign( _First, static_cast< size_t >( _Root_name_end_ptr - _First ) );
				return *this;
			}
			if( std::_Get_unwrapped( _Position ) == _Last && _Is_slash( _Position[-1] ) )
			{
				--_Position;
				_Element.clear();
				return *this;
			}

			while( _Root_directory_end_ptr != std::_Get_unwrapped( _Position ) && _Is_slash( _Position[-1] ) )
			{
				--_Position;
			}

			const auto _New_end = _Position;
			while( _Root_directory_end_ptr != std::_Get_unwrapped( _Position ) && !_Is_slash( _Position[-1] ) )
			{
				--_Position;
			}

			_Element._Text.assign( _Position, _New_end );
			return *this;
		}

		_Path_iterator operator--( int )
		{
			_Path_iterator _Tmp = *this;
			-- * this;
			return _Tmp;
		}

		friend bool operator==( const _Path_iterator & _Lhs, const _Path_iterator & _Rhs )
		{
			return _Lhs._Position == _Rhs._Position;
		}

		friend bool operator!=( const _Path_iterator & _Lhs, const _Path_iterator & _Rhs )
		{
			return _Lhs._Position != _Rhs._Position;
		}

#if _ITERATOR_DEBUG_LEVEL != 0
		friend void _Verify_range( const _Path_iterator & _Lhs, const _Path_iterator & _Rhs )
		{
			_Verify_range( _Lhs._Position, _Rhs._Position );
		}
#endif 

		using _Prevent_inheriting_unwrap = _Path_iterator;

		template <class _Iter2 = _Base_iter, std::enable_if_t<std::_Unwrappable_v<_Iter2>, int> = 0>
		_Path_iterator<std::_Unwrapped_t<_Base_iter>> _Unwrapped() const
		{
			return { _Position._Unwrapped(), _Element.native(), _Mypath };
		}

		static constexpr bool _Unwrap_when_unverified = std::_Do_unwrap_when_unverified_v<_Base_iter>;

		template <class _Other>
		friend class _Path_iterator;

		template <class _Other, std::enable_if_t<std::_Wrapped_seekable_v<_Base_iter, _Other>, int> = 0>
		constexpr void _Seek_to( const _Path_iterator<_Other> & _It )
		{
			_Position._Seek_to( _It._Position );
			_Element = _It._Element;
		}

	private:
		_Base_iter _Position{};
		Path _Element{};
		const Path * _Mypath{};
	};

	void swap( Path & _Left, Path & _Right ) noexcept
	{
		_Left.swap( _Right );
	}

	size_t hash_value( const Path & _Path ) noexcept
	{
		size_t _Val = std::_FNV_offset_basis;
		const auto & _Text = _Path.native();
		const auto _First = _Text.data();
		const auto _Last = _First + _Text.size();
		auto _Next = _Find_root_name_end( _First, _Last );
		_Val = std::_Fnv1a_append_range( _Val, _First, _Next );
		bool _Slash_inserted = false;
		for( ; _Next != _Last; ++_Next )
		{
			if( _Is_slash( *_Next ) )
			{
				if( !_Slash_inserted )
				{
					_Val = std::_Fnv1a_append_value( _Val, Path::preferred_separator );
					_Slash_inserted = true;
				}
			}
			else
			{
				_Val = std::_Fnv1a_append_value( _Val, *_Next );
				_Slash_inserted = false;
			}
		}

		return _Val;
	}

	Path Path::lexically_relative( const Path & _Base ) const
	{
		using namespace std::string_view_literals;

		constexpr std::wstring_view _Dot = L"."sv;
		constexpr std::wstring_view _Dot_dot = L".."sv;
		Path _Result;

		if( root_name() != _Base.root_name() || is_absolute() != _Base.is_absolute()
			|| ( !has_root_directory() && _Base.has_root_directory() ) )
		{
			return _Result;
		}

		const iterator _This_end = end();
		const iterator _Base_begin = _Base.begin();
		const iterator _Base_end = _Base.end();

		auto _Mismatched = std::mismatch( begin(), _This_end, _Base_begin, _Base_end );
		iterator & _A_iter = _Mismatched.first;
		iterator & _B_iter = _Mismatched.second;

		if( _A_iter == _This_end && _B_iter == _Base_end )
		{
			_Result = _Dot;
			return _Result;
		}

		{
			ptrdiff_t _B_dist = std::distance( _Base_begin, _B_iter );

			const ptrdiff_t _Base_root_dist =
				static_cast< ptrdiff_t >( _Base.has_root_name() ) + static_cast< ptrdiff_t >( _Base.has_root_directory() );

			while( _B_dist < _Base_root_dist )
			{
				++_B_iter;
				++_B_dist;
			}
		}

		ptrdiff_t _Num = 0;

		for( ; _B_iter != _Base_end; ++_B_iter )
		{
			const Path & _Elem = *_B_iter;

			if( _Elem.empty() )
			{
			}
			else if( _Elem == _Dot )
			{
			}
			else if( _Elem == _Dot_dot )
			{
				--_Num;
			}
			else
			{
				++_Num;
			}
		}

		if( _Num < 0 )
		{
			return _Result;
		}

		if( _Num == 0 && ( _A_iter == _This_end || _A_iter->empty() ) )
		{
			_Result = _Dot;
			return _Result;
		}

		for( ; _Num > 0; --_Num )
		{
			_Result /= _Dot_dot;
		}

		for( ; _A_iter != _This_end; ++_A_iter )
		{
			_Result /= *_A_iter;
		}

		return _Result;
	}

	Path::iterator Path::begin() const
	{
		const auto _First = _Text.data();
		const auto _Last = _First + _Text.size();
		const auto _Root_name_end = _Find_root_name_end( _First, _Last );
		const wchar_t * _First_end;
		if( _First == _Root_name_end )
		{
			auto _Root_directory_end = std::find_if_not( _Root_name_end, _Last, _Is_slash );
			if( _First == _Root_directory_end )
			{
				_First_end = std::find_if( _Root_directory_end, _Last, _Is_slash );
			}
			else
			{
				_First_end = _Root_directory_end;
			}
		}
		else
		{
			_First_end = _Root_name_end;
		}

		return iterator( _Text.cbegin(), std::wstring_view( _First, static_cast< size_t >( _First_end - _First ) ), this );
	}

	Path::iterator Path::end() const noexcept
	{
		return iterator( _Text.cend(), this );
	}

	class filesystem_error : public std::system_error
	{
	public:
		filesystem_error( const std::string & _Message, const std::error_code _Errcode )
			: std::system_error( _Errcode, _Message ), _What( runtime_error::what() )
		{
		}

		filesystem_error( const std::string & _Message, const Path & _Path1_arg, const std::error_code _Errcode )
			: std::system_error( _Errcode, _Message ), _Path1( _Path1_arg ), _Path2(),
			_What( _Pretty_message( runtime_error::what(), _Path1_arg ) )
		{
		}

		filesystem_error(
			const std::string & _Message, const Path & _Path1_arg, const Path & _Path2_arg, const std::error_code _Errcode )
			: std::system_error( _Errcode, _Message ), _Path1( _Path1_arg ), _Path2( _Path2_arg ),
			_What( _Pretty_message( runtime_error::what(), _Path1_arg, _Path2_arg ) )
		{
		}

		const Path & path1() const noexcept
		{
			return _Path1;
		}

		const Path & path2() const noexcept
		{
			return _Path2;
		}

		virtual const char * what() const noexcept override
		{
			return _What.c_str();
		}

	private:
		static std::string _Pretty_message( const std::string_view _Op, const Path & _Path1, const Path & _Path2 = {} )
		{
			using namespace std::string_view_literals;
			std::string _Result;
			const std::string _Path1_str = _Path1.string();
			const std::string _Path2_str = _Path2.string();
			_Result.reserve( _Op.size() + ( _Path2_str.empty() ? 4 : 8 ) + _Path1_str.size() + _Path2_str.size() );
			_Result += _Op;
			_Result += R"(: ")"sv;
			_Result += _Path1_str;
			if( !_Path2_str.empty() )
			{
				_Result += R"(", ")"sv;
				_Result += _Path2_str;
			}
			_Result += '"';
			return _Result;
		}

		Path _Path1;
		Path _Path2;
		std::string _What;

#if _HAS_EXCEPTIONS

#else 
	protected:
		virtual void _Doraise() const
		{
			_RAISE( *this );
		}
#endif 
	};

	void _Throw_fs_error( const char * _Op, __std_win_error _Error )
	{
		throw ( filesystem_error( _Op, _Make_ec( _Error ) ) );
	}

	void _Throw_fs_error( const char * _Op, __std_win_error _Error, const Path & _Path1 )
	{
		throw ( filesystem_error( _Op, _Path1, _Make_ec( _Error ) ) );
	}

	void _Throw_fs_error(
		const char * _Op, __std_win_error _Error, const Path & _Path1, const Path & _Path2 )
	{
		throw ( filesystem_error( _Op, _Path1, _Path2, _Make_ec( _Error ) ) );
	}

	void _Throw_fs_error( const char * _Op, const std::error_code & _Error, const Path & _Path1 )
	{
		throw ( filesystem_error( _Op, _Path1, _Error ) );
	}

	void _Throw_fs_error(
		const char * _Op, const std::error_code & _Error, const Path & _Path1, const Path & _Path2 )
	{
		throw ( filesystem_error( _Op, _Path1, _Path2, _Error ) );
	}

	bool _Is_file_not_found( const __std_win_error _Error ) noexcept
	{
		return _Error == __std_win_error::_File_not_found || _Error == __std_win_error::_Path_not_found
			|| _Error == __std_win_error::_Invalid_name;
	}

	enum class file_type
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

	enum class perms
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

		_All_write = owner_write | group_write | others_write,
		_File_attribute_readonly = all & ~_All_write
	};

	XE_BITMASK_OPS( perms )

	enum class copy_options
	{
		none = static_cast< int >( __std_fs_copy_options::_None ),

		_Existing_mask = static_cast< int >( __std_fs_copy_options::_Existing_mask ),
		skip_existing = static_cast< int >( __std_fs_copy_options::_Skip_existing ),
		overwrite_existing = static_cast< int >( __std_fs_copy_options::_Overwrite_existing ),
		update_existing = static_cast< int >( __std_fs_copy_options::_Update_existing ),

		recursive = 0x10,

		_Symlinks_mask = 0xF00,
		copy_symlinks = 0x100,
		skip_symlinks = 0x200,

		_Copy_form_mask = 0xF000,
		directories_only = 0x1000,
		create_symlinks = 0x2000,
		create_hard_links = 0x4000,

		_Unspecified_copy_prevention_tag = 0x10000
	};

	XE_BITMASK_OPS( copy_options )

	class file_status
	{
	public:
		file_status() noexcept = default;
		explicit file_status( file_type _Ft, perms _Perms = perms::unknown ) noexcept : _Myftype( _Ft ), _Myperms( _Perms )
		{
		}
		file_status( const file_status & ) noexcept = default;
		file_status( file_status && ) noexcept = default;
		~file_status() noexcept = default;

		file_status & operator=( const file_status & ) noexcept = default;
		file_status & operator=( file_status && ) noexcept = default;

		void type( file_type _Ft ) noexcept
		{
			_Myftype = _Ft;
		}

		void permissions( perms _Perms ) noexcept
		{
			_Myperms = _Perms;
		}

		file_type type() const noexcept
		{
			return _Myftype;
		}

		perms permissions() const noexcept
		{
			return _Myperms;
		}

		void _Refresh( const __std_win_error _Error, const __std_fs_stats & _Stats ) noexcept
		{
			if( _Error == __std_win_error::_Success )
			{
				const auto _Attrs = _Stats._Attributes;

				if( _Bitmask_includes( _Attrs, __std_fs_file_attr::_Readonly ) )
				{
					this->permissions( perms::_File_attribute_readonly );
				}
				else
				{
					this->permissions( perms::all );
				}

				if( _Bitmask_includes( _Attrs, __std_fs_file_attr::_Reparse_point ) )
				{
					if( _Stats._Reparse_point_tag == __std_fs_reparse_tag::_Symlink )
					{
						this->type( file_type::symlink );
						return;
					}

					if( _Stats._Reparse_point_tag == __std_fs_reparse_tag::_Mount_point )
					{
						this->type( file_type::junction );
						return;
					}

				}

				if( _Bitmask_includes( _Attrs, __std_fs_file_attr::_Directory ) )
				{
					this->type( file_type::directory );
				}
				else
				{
					this->type( file_type::regular );
				}

				return;
			}

			this->permissions( perms::unknown );
			this->type( _Is_file_not_found( _Error ) ? file_type::not_found : file_type::none );
		}

	private:
		file_type _Myftype = file_type::none;
		perms _Myperms = perms::unknown;
	};

	bool exists( const file_status _Status ) noexcept
	{
		switch( _Status.type() )
		{
		case file_type::none:
		case file_type::not_found:
			return false;
		case file_type::regular:
		case file_type::directory:
		case file_type::symlink:
		case file_type::block:
		case file_type::character:
		case file_type::fifo:
		case file_type::socket:
		case file_type::unknown:
		case file_type::junction:
		default:
			return true;
		}
	}

	bool is_block_file( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::block;
	}

	bool is_character_file( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::character;
	}

	bool is_directory( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::directory;
	}

	bool is_fifo( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::fifo;
	}

	bool is_other( const file_status _Status ) noexcept
	{
		switch( _Status.type() )
		{
		case file_type::none:
		case file_type::not_found:
		case file_type::regular:
		case file_type::directory:
		case file_type::symlink:
			return false;
		case file_type::block:
		case file_type::character:
		case file_type::fifo:
		case file_type::socket:
		case file_type::unknown:
		case file_type::junction:
		default:
			return true;
		}
	}

	bool is_regular_file( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::regular;
	}

	bool is_socket( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::socket;
	}

	bool is_symlink( const file_status _Status ) noexcept
	{
		return _Status.type() == file_type::symlink;
	}

	struct _File_status_and_error
	{
		file_status _Status;
		__std_win_error _Error;

		bool _Not_good() const noexcept
		{
			return _Error != __std_win_error::_Success && _Status.type() != file_type::not_found
				&& _Status.type() != file_type::unknown;
		}
	};

	constexpr auto _Status_stats_flags =
		__std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Follow_symlinks;

	constexpr auto _Symlink_status_stats_flags =
		__std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;

	struct _File_time_clock
	{
		using rep = long long;
		using period = std::ratio_multiply<std::ratio<_XTIME_NSECS_PER_TICK, 1>, std::nano>;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<_File_time_clock>;

		static constexpr bool is_steady = false;

		static time_point now() noexcept
		{
			return time_point( duration( _Xtime_get_ticks() + __std_fs_file_time_epoch_adjustment ) );
		}
	};

	using file_time_type = std::chrono::time_point<_File_time_clock>;

	class directory_entry
	{
	public:
		directory_entry() noexcept : _Cached_data{}, _Path() {}

		directory_entry( const directory_entry & ) = default;
		directory_entry( directory_entry && ) noexcept = default;
		explicit directory_entry( const XE::FileSystem::Path & _Path_arg ) : _Cached_data{}, _Path( _Path_arg ) {
			( void ) _Refresh( _Cached_data, _Path );
		}

		directory_entry( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec ) : _Cached_data{}, _Path( _Path_arg ) {
			_Ec.clear();
			( void ) _Refresh( _Cached_data, _Path );
		}

		~directory_entry() = default;

		directory_entry & operator=( const directory_entry & ) = default;
		directory_entry & operator=( directory_entry && ) noexcept = default;

		void assign( const XE::FileSystem::Path & _Path_arg )
		{
			_Path.assign( _Path_arg );
			( void ) _Refresh( _Cached_data, _Path );
		}

		void assign( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec )
		{
			_Ec.clear();
			_Path.assign( _Path_arg );
			( void ) _Refresh( _Cached_data, _Path );
		}

		void replace_filename( const XE::FileSystem::Path & _Path_arg )
		{
			_Path.replace_filename( _Path_arg );
			( void ) _Refresh( _Cached_data, _Path );
		}

		void replace_filename( const XE::FileSystem::Path & _Path_arg, std::error_code & _Ec )
		{
			_Ec.clear();
			_Path.replace_filename( _Path_arg );
			( void ) _Refresh( _Cached_data, _Path );
		}

		void refresh()
		{
			const auto _Error = _Refresh( _Cached_data, _Path );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_entry::refresh", _Error, _Path );
			}
		}

		void refresh( std::error_code & _Ec ) noexcept
		{
			_Ec = _Make_ec( _Refresh( _Cached_data, _Path ) );
		}

#if _HAS_CXX20
		void clear_cache() noexcept
		{
			_Cached_data._Available = __std_fs_stats_flags::_None;
		}
#endif 

	private:
		bool _Has_cached_attribute( const __std_fs_file_attr _Attrs ) const noexcept
		{
			return _Bitmask_includes( _Cached_data._Attributes, _Attrs );
		}

	public:
		const XE::FileSystem::Path & path() const noexcept
		{
			return _Path;
		}

		operator const FileSystem::Path & ( ) const noexcept
		{
			return _Path;
		}

		bool exists() const
		{
			const auto _Type = this->status().type();
			return _Type != file_type::not_found && _Type != file_type::none;
		}

		bool exists( std::error_code & _Ec ) const noexcept
		{
			const auto _Type = this->status( _Ec ).type();
			return _Type != file_type::not_found && _Type != file_type::none;
		}

		bool is_block_file() const
		{
			return false;
		}

		bool is_block_file( std::error_code & _Ec ) const noexcept
		{
			_Ec.clear();
			return false;
		}

		bool is_character_file() const
		{
			return false;
		}

		bool is_character_file( std::error_code & _Ec ) const noexcept
		{
			_Ec.clear();
			return false;
		}

		bool is_directory() const
		{
			return FileSystem::is_directory( this->status() );
		}

		bool is_directory( std::error_code & _Ec ) const noexcept
		{
			return FileSystem::is_directory( this->status( _Ec ) );
		}

		bool is_fifo() const
		{
			return false;
		}

		bool is_fifo( std::error_code & _Ec ) const noexcept
		{
			_Ec.clear();
			return false;
		}

		bool is_other() const
		{
			return FileSystem::is_other( this->status() );
		}

		bool is_other( std::error_code & _Ec ) const noexcept
		{
			return FileSystem::is_other( this->status( _Ec ) );
		}

		bool is_regular_file() const
		{
			return FileSystem::is_regular_file( this->status() );
		}

		bool is_regular_file( std::error_code & _Ec ) const noexcept
		{
			return FileSystem::is_regular_file( this->status( _Ec ) );
		}

		bool is_socket() const
		{
			return false;
		}

		bool is_socket( std::error_code & _Ec ) const noexcept
		{
			_Ec.clear();
			return false;
		}

		bool _Is_symlink_or_junction() const noexcept
		{
			return _Has_cached_attribute( __std_fs_file_attr::_Reparse_point )
				&& ( _Cached_data._Reparse_point_tag == __std_fs_reparse_tag::_Symlink
					 || _Cached_data._Reparse_point_tag == __std_fs_reparse_tag::_Mount_point );
		}

		bool is_symlink() const
		{
			return FileSystem::is_symlink( this->symlink_status() );
		}

		bool is_symlink( std::error_code & _Ec ) const noexcept
		{
			return FileSystem::is_symlink( this->symlink_status( _Ec ) );
		}

		bool _Available( const __std_fs_stats_flags _Flags ) const noexcept
		{
			return _Bitmask_includes( _Cached_data._Available, _Flags );
		}

	private:
		__std_win_error _File_size( uintmax_t & _Result ) const noexcept
		{
			if( _Available( __std_fs_stats_flags::_File_size ) )
			{
				_Result = _Cached_data._File_size;
				return __std_win_error::_Success;
			}

			__std_fs_stats _Stats;
			constexpr auto _Flags = __std_fs_stats_flags::_File_size | __std_fs_stats_flags::_Follow_symlinks;
			const auto _Error =
				__std_fs_get_stats( _Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes() );
			if( _Error == __std_win_error::_Success )
			{
				_Result = _Stats._File_size;
			}
			else
			{
				_Result = static_cast< uintmax_t >( -1 );
			}

			return _Error;
		}

	public:
		uintmax_t file_size() const
		{
			uintmax_t _Result;
			const auto _Error = _File_size( _Result );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_entry::file_size", _Error, _Path );
			}

			return _Result;
		}

		uintmax_t file_size( std::error_code & _Ec ) const noexcept
		{
			uintmax_t _Result;
			_Ec = _Make_ec( _File_size( _Result ) );
			return _Result;
		}

	private:
		__std_win_error _Hard_link_count( uintmax_t & _Result ) const noexcept
		{
			if( _Available( __std_fs_stats_flags::_Link_count ) )
			{
				_Result = _Cached_data._Link_count;
				return __std_win_error::_Success;
			}

			__std_fs_stats _Stats;
			constexpr auto _Flags = __std_fs_stats_flags::_Link_count | __std_fs_stats_flags::_Follow_symlinks;
			const auto _Error =
				__std_fs_get_stats( _Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes() );
			if( _Error == __std_win_error::_Success )
			{
				_Result = _Stats._Link_count;
			}
			else
			{
				_Result = static_cast< uintmax_t >( -1 );
			}

			return _Error;
		}

	public:
		uintmax_t hard_link_count() const
		{
			uintmax_t _Result;
			const auto _Error = _Hard_link_count( _Result );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_entry::hard_link_count", _Error, _Path );
			}

			return _Result;
		}

		uintmax_t hard_link_count( std::error_code & _Ec ) const noexcept
		{
			uintmax_t _Result;
			_Ec = _Make_ec( _Hard_link_count( _Result ) );
			return _Result;
		}

	private:
		__std_win_error _Last_write_time( file_time_type & _Result ) const noexcept
		{
			if( _Available( __std_fs_stats_flags::_Last_write_time ) )
			{
				_Result = file_time_type{ file_time_type::duration{_Cached_data._Last_write_time} };
				return __std_win_error::_Success;
			}

			__std_fs_stats _Stats;
			constexpr auto _Flags = __std_fs_stats_flags::_Last_write_time | __std_fs_stats_flags::_Follow_symlinks;
			const auto _Error =
				__std_fs_get_stats( _Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes() );
			if( _Error == __std_win_error::_Success )
			{
				_Result = file_time_type{ file_time_type::duration{_Stats._Last_write_time} };
			}
			else
			{
				_Result = file_time_type{ file_time_type::duration{LLONG_MIN} };
			}

			return _Error;
		}

	public:
		file_time_type last_write_time() const
		{
			file_time_type _Result;
			const auto _Error = _Last_write_time( _Result );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_entry::last_write_time", _Error, _Path );
			}

			return _Result;
		}

		file_time_type last_write_time( std::error_code & _Ec ) const noexcept
		{
			file_time_type _Result;
			_Ec = _Make_ec( _Last_write_time( _Result ) );
			return _Result;
		}

	private:
		_File_status_and_error _Get_any_status( const __std_fs_stats_flags _Flags ) const noexcept
		{
			_File_status_and_error _Result;
			__std_fs_stats _Stats;

			if( _Bitmask_includes_all( _Cached_data._Available, _Flags ) )
			{
				_Result._Error = __std_win_error::_Success;
				_Result._Status._Refresh( __std_win_error::_Success, _Cached_data );
			}
			else
			{
				const auto _Error =
					__std_fs_get_stats( _Path.c_str(), &_Stats, _Flags, _Cached_data._Symlink_hint_attributes() );
				_Result._Error = _Error;
				_Result._Status._Refresh( _Error, _Stats );
			}

			return _Result;
		}

	public:
		file_status status() const
		{
			const auto _Result = _Get_any_status( _Status_stats_flags );
			if( _Result._Not_good() )
			{
				_Throw_fs_error( "directory_entry::status", _Result._Error, _Path );
			}

			return _Result._Status;
		}

		file_status status( std::error_code & _Ec ) const noexcept
		{
			const auto _Result = _Get_any_status( _Status_stats_flags );
			_Ec = _Make_ec( _Result._Error );
			return _Result._Status;
		}

		file_status symlink_status() const
		{
			const auto _Result = _Get_any_status( _Symlink_status_stats_flags );
			if( _Result._Not_good() )
			{
				_Throw_fs_error( "directory_entry::symlink_status", _Result._Error, _Path );
			}

			return _Result._Status;
		}

		file_status symlink_status( std::error_code & _Ec ) const noexcept
		{
			const auto _Result = _Get_any_status( _Symlink_status_stats_flags );
			_Ec = _Make_ec( _Result._Error );
			return _Result._Status;
		}

		bool operator<( const directory_entry & _Rhs ) const noexcept
		{
			return _Path < _Rhs._Path;
		}

		bool operator==( const directory_entry & _Rhs ) const noexcept
		{
			return _Path == _Rhs._Path;
		}

		bool operator!=( const directory_entry & _Rhs ) const noexcept
		{
			return _Path != _Rhs._Path;
		}

		bool operator<=( const directory_entry & _Rhs ) const noexcept
		{
			return _Path <= _Rhs._Path;
		}

		bool operator>( const directory_entry & _Rhs ) const noexcept
		{
			return _Path > _Rhs._Path;
		}

		bool operator>=( const directory_entry & _Rhs ) const noexcept
		{
			return _Path >= _Rhs._Path;
		}

	private:
		void _Refresh( const __std_fs_find_data & _Data ) noexcept
		{
			_Cached_data._Attributes = _Data._Attributes;
			_Cached_data._Reparse_point_tag = _Data._Reparse_point_tag;
			_Cached_data._Available = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;
			if( !_Bitmask_includes( _Data._Attributes, __std_fs_file_attr::_Reparse_point ) )
			{
				_Cached_data._File_size = ( static_cast< uintmax_t >( _Data._File_size_high ) << 32 )
					+ static_cast< uintmax_t >( _Data._File_size_low );
				::memcpy(
					&_Cached_data._Last_write_time, &_Data._Last_write_time, sizeof( _Cached_data._Last_write_time ) );
				_Cached_data._Available |= __std_fs_stats_flags::_File_size | __std_fs_stats_flags::_Last_write_time;
			}
		}

		static __std_win_error _Refresh( __std_fs_stats & _Stats, const FileSystem::Path & _Path ) noexcept
		{
			const auto _Error = __std_fs_get_stats( _Path.c_str(), &_Stats, __std_fs_stats_flags::_All_data );
			if( _Error == __std_win_error::_Success )
			{
				if( _Bitmask_includes( _Stats._Attributes, __std_fs_file_attr::_Reparse_point ) )
				{
					_Stats._Available = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Reparse_tag;
				}
				else
				{
					_Stats._Available = __std_fs_stats_flags::_All_data;
				}
			}
			else
			{
				_Stats._Available = __std_fs_stats_flags::_None;
			}

			return _Error;
		}

		friend struct _Dir_enum_impl;
		friend struct _Recursive_dir_enum_impl;
		friend void _Copy_impl(
			const directory_entry & _From, const FileSystem::Path & _To, copy_options _Options, std::error_code & _Ec );

		__std_fs_stats _Cached_data;
		FileSystem::Path _Path;
	};

	enum class directory_options
	{
		none = 0, follow_directory_symlink = 1, skip_permission_denied = 2
	};
	XE_BITMASK_OPS( directory_options )

	struct _Dir_enum_impl
	{
		static __std_win_error _Advance_and_reset_if_no_more_files( std::shared_ptr<_Dir_enum_impl> & _Ptr )
		{
			auto & _Impl = *_Ptr;
			__std_fs_find_data _Data;
			const auto _Error = __std_fs_directory_iterator_advance( _Impl._Dir._Handle, &_Data );
			if( _Error == __std_win_error::_Success )
			{
				_Impl._Refresh( _Data );
			}
			else if( _Error == __std_win_error::_No_more_files )
			{
				_Ptr.reset();
				return __std_win_error::_Success;
			}

			return _Error;
		}

		static __std_win_error _Skip_dots(
			__std_fs_dir_handle _Dir_handle, __std_fs_find_data & _Data ) noexcept
		{
			while( _Is_dot_or_dotdot( _Data ) )
			{
				const auto _Error = __std_fs_directory_iterator_advance( _Dir_handle, &_Data );
				if( _Error != __std_win_error::_Success )
				{
					return _Error;
				}
			}

			return __std_win_error::_Success;
		}

		static __std_win_error _Open_dir(
			Path & _Path, const directory_options _Options_arg, _Find_file_handle & _Dir, __std_fs_find_data & _Data )
		{
			using namespace std::string_view_literals;
			const size_t _Null_term_len = ::wcslen( _Path.c_str() );
			if( _Null_term_len == 0 || _Null_term_len != _Path.native().size() )
			{
				return __std_win_error::_File_not_found;
			}

			_Path /= L"*"sv;
			auto _Error = _Dir._Open( _Path.c_str(), &_Data );
			if( _Error == __std_win_error::_Success )
			{
				return _Skip_dots( _Dir._Handle, _Data );
			}

			if( _Error == __std_win_error::_Access_denied
				&& _Bitmask_includes( _Options_arg, directory_options::skip_permission_denied ) )
			{
				_Error = __std_win_error::_No_more_files;
			}

			return _Error;
		}

		struct _Creator
		{
			Path _Path;
			_Find_file_handle _Dir;
			__std_fs_find_data _Find_data;

			struct _Create_status
			{
				bool _Should_create_impl;
				__std_win_error _Error;
			};

			_Create_status _Status;

			_Creator( const Path & _Path_arg, const directory_options _Options ) : _Path( _Path_arg )
			{
				const auto _Error = _Open_dir( _Path, _Options, _Dir, _Find_data );
				if( _Error == __std_win_error::_Success )
				{
					_Status = { true, __std_win_error::_Success };
				}
				else if( _Error == __std_win_error::_No_more_files )
				{
					_Status = { false, __std_win_error::_Success };
				}
				else
				{
					_Status = { false, _Error };
				}
			}
		};

		void _Refresh( const __std_fs_find_data & _Data )
		{
			_Entry._Refresh( _Data );
			_Entry._Path.replace_filename( std::wstring_view{ _Data._File_name } );
		}

		explicit _Dir_enum_impl( _Creator && _Create_data, const directory_options = {} )
			: _Dir( std::move( _Create_data._Dir ) )
		{
			_Entry._Path = std::move( _Create_data._Path );
			_Refresh( _Create_data._Find_data );
		}

		template <class _Dir_enum_kind>
		static __std_win_error _Initialize_dir_enum(
			std::shared_ptr<_Dir_enum_kind> & _Impl, const Path & _Path, const directory_options _Options = {} )
		{
			_Creator _Create_data( _Path, _Options );
			if( _Create_data._Status._Should_create_impl )
			{
				_Impl = std::make_shared<_Dir_enum_kind>( std::move( _Create_data ), _Options );
			}
			return _Create_data._Status._Error;
		}

		directory_entry _Entry;
		_Find_file_handle _Dir;
	};

	class directory_iterator;
	class recursive_directory_iterator;

	struct _Directory_entry_proxy
	{
		directory_entry operator*() && noexcept
		{
			return std::move( _Entry );
		}

	private:
		friend directory_iterator;
		friend recursive_directory_iterator;

		explicit _Directory_entry_proxy( const directory_entry & _Entry_arg ) : _Entry( _Entry_arg )
		{
		}

		directory_entry _Entry;
	};

	class directory_iterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = directory_entry;
		using difference_type = std::ptrdiff_t;
		using pointer = const directory_entry *;
		using reference = const directory_entry &;

		directory_iterator() noexcept = default;
		explicit directory_iterator( const Path & _Path )
		{
			const auto _Error = _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_iterator::directory_iterator", _Error, _Path );
			}
		}

		directory_iterator( const Path & _Path, const directory_options _Options )
		{
			const auto _Error = _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path, _Options );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_iterator::directory_iterator", _Error, _Path );
			}
		}

		directory_iterator( const Path & _Path, std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path ) );
		}

		directory_iterator( const Path & _Path, const directory_options _Options, std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path, _Options ) );
		}

		directory_iterator( const directory_iterator & ) noexcept = default;
		directory_iterator( directory_iterator && ) noexcept = default;
		~directory_iterator() noexcept = default;

		directory_iterator & operator=( const directory_iterator & ) noexcept = default;
		directory_iterator & operator=( directory_iterator && ) noexcept = default;

		const directory_entry & operator*() const noexcept
		{
			return _Impl->_Entry;
		}

		const directory_entry * operator->() const noexcept
		{
			return &**this;
		}

		directory_iterator & operator++()
		{
			const auto _Error = _Dir_enum_impl::_Advance_and_reset_if_no_more_files( _Impl );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "directory_iterator::operator++", _Error );
			}

			return *this;
		}

		directory_iterator & increment( std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Dir_enum_impl::_Advance_and_reset_if_no_more_files( _Impl ) );
			return *this;
		}

		bool operator==( const directory_iterator & _Rhs ) const noexcept
		{
			return _Impl == _Rhs._Impl;
		}

		bool operator!=( const directory_iterator & _Rhs ) const noexcept
		{
			return _Impl != _Rhs._Impl;
		}

		_Directory_entry_proxy operator++( int )
		{
			_Directory_entry_proxy _Proxy( **this );
			++ * this;
			return _Proxy;
		}

		bool _At_end() const noexcept
		{
			return !_Impl;
		}

	private:
		std::shared_ptr<_Dir_enum_impl> _Impl;
	};

	directory_iterator begin( directory_iterator _Iter ) noexcept
	{
		return _Iter;
	}

	directory_iterator end( directory_iterator ) noexcept
	{
		return {};
	}

	struct _Should_recurse_result
	{
		bool _Should_recurse;
		__std_win_error _Error;
	};

	struct _Recursive_dir_enum_impl : _Dir_enum_impl
	{
		std::vector<_Find_file_handle> _Stack;
		directory_options _Options = {};
		bool _Recursion_pending = true;

		_Should_recurse_result _Should_recurse() const noexcept
		{
			bool _Should_recurse = false;
			__std_win_error _Error = __std_win_error::_Success;
			if( _Recursion_pending )
			{
				if( _Entry._Is_symlink_or_junction() )
				{
					if( _Bitmask_includes( _Options, directory_options::follow_directory_symlink ) )
					{
						__std_fs_stats _Target_stats;
						constexpr auto _Flags =
							__std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Follow_symlinks;
						_Error = __std_fs_get_stats(
							_Entry._Path.c_str(), &_Target_stats, _Flags, _Entry._Cached_data._Attributes );
						if( _Error == __std_win_error::_Success )
						{
							_Should_recurse =
								_Bitmask_includes( _Target_stats._Attributes, __std_fs_file_attr::_Directory );
						}
						else if( _Is_file_not_found( _Error )
								 || ( _Error == __std_win_error::_Access_denied
									  && _Bitmask_includes( _Options, directory_options::skip_permission_denied ) ) )
						{
							_Error = __std_win_error::_Success;
						}
					}
				}
				else
				{
					_Should_recurse = _Entry._Has_cached_attribute( __std_fs_file_attr::_Directory );
				}
			}

			return { _Should_recurse, _Error };
		}

		__std_win_error _Advance_and_skip_dots( __std_fs_find_data & _Data ) noexcept
		{
			const auto _Error = __std_fs_directory_iterator_advance( _Dir._Handle, &_Data );
			if( _Error != __std_win_error::_Success )
			{
				return _Error;
			}

			return _Skip_dots( _Dir._Handle, _Data );
		}

		static __std_win_error _Pop_and_reset_if_no_more_files( std::shared_ptr<_Recursive_dir_enum_impl> & _Ptr )
		{
			__std_win_error _Error;
			auto & _Impl = *_Ptr;
			__std_fs_find_data _Data;

			_Impl._Recursion_pending = true;

			do
			{
				if( _Impl._Stack.empty() )
				{
					_Error = __std_win_error::_Success;
					break;
				}

				_Impl._Dir = std::move( _Impl._Stack.back() );
				_Impl._Stack.pop_back();
				_Impl._Entry._Path._Remove_filename_and_separator();
				_Error = _Impl._Advance_and_skip_dots( _Data );

				if( _Error == __std_win_error::_Success )
				{
					_Impl._Refresh( _Data );
					return __std_win_error::_Success;
				}
			} while( _Error == __std_win_error::_No_more_files );

			_Ptr.reset();
			return _Error;
		}

		static __std_win_error _Advance_and_reset_if_no_more_files(
			std::shared_ptr<_Recursive_dir_enum_impl> & _Ptr )
		{
			auto & _Impl = *_Ptr;
			__std_fs_find_data _Data;
			auto [_Should_recurse, _Error] = _Impl._Should_recurse();
			if( _Error != __std_win_error::_Success )
			{
				_Ptr.reset();
				return _Error;
			}

			if( _Should_recurse )
			{
				_Impl._Stack.push_back( std::move( _Impl._Dir ) );
				_Error = _Open_dir( _Impl._Entry._Path, _Impl._Options, _Impl._Dir, _Data );
			}
			else
			{
				_Error = _Impl._Advance_and_skip_dots( _Data );
			}

			_Impl._Recursion_pending = true;
			for( ;; _Error = _Impl._Advance_and_skip_dots( _Data ) )
			{
				if( _Error == __std_win_error::_Success )
				{
					_Impl._Refresh( _Data );
					return __std_win_error::_Success;
				}

				if( _Error != __std_win_error::_No_more_files )
				{
					break;
				}

				if( _Impl._Stack.empty() )
				{
					_Error = __std_win_error::_Success;
					break;
				}

				_Impl._Dir = std::move( _Impl._Stack.back() );
				_Impl._Stack.pop_back();
				_Impl._Entry._Path._Remove_filename_and_separator();
			}

			_Ptr.reset();
			return _Error;
		}

		_Recursive_dir_enum_impl( _Dir_enum_impl::_Creator && _Create_data, const directory_options _Options_arg )
			: _Dir_enum_impl( std::move( _Create_data ) ), _Options( _Options_arg )
		{
		}
	};

	class recursive_directory_iterator
	{
	public:
		using iterator_category = std::input_iterator_tag;
		using value_type = directory_entry;
		using difference_type = std::ptrdiff_t;
		using pointer = const directory_entry *;
		using reference = const directory_entry &;


		recursive_directory_iterator() noexcept = default;
		explicit recursive_directory_iterator( const Path & _Path )
		{
			const auto _Error = _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "recursive_directory_iterator::recursive_directory_iterator", _Error, _Path );
			}
		}

		recursive_directory_iterator( const Path & _Path, const directory_options _Options )
		{
			const auto _Error = _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path, _Options );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "recursive_directory_iterator::recursive_directory_iterator", _Error, _Path );
			}
		}

		recursive_directory_iterator( const Path & _Path, const directory_options _Options, std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path, _Options ) );
		}

		recursive_directory_iterator( const Path & _Path, std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Dir_enum_impl::_Initialize_dir_enum( _Impl, _Path ) );
		}

		recursive_directory_iterator( const recursive_directory_iterator & ) noexcept = default;
		recursive_directory_iterator( recursive_directory_iterator && ) noexcept = default;
		~recursive_directory_iterator() noexcept = default;

		directory_options options() const noexcept
		{
			return _Impl->_Options;
		}
		int depth() const noexcept
		{
			return static_cast< int >( _Impl->_Stack.size() );
		}
		bool recursion_pending() const noexcept
		{
			return _Impl->_Recursion_pending;
		}

		const directory_entry & operator*() const noexcept
		{
			return _Impl->_Entry;
		}

		const directory_entry * operator->() const noexcept
		{
			return &**this;
		}

		recursive_directory_iterator & operator=( recursive_directory_iterator && ) noexcept = default;
		recursive_directory_iterator & operator=( const recursive_directory_iterator & ) noexcept = default;

		recursive_directory_iterator & operator++()
		{
			const auto _Error = _Recursive_dir_enum_impl::_Advance_and_reset_if_no_more_files( _Impl );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "recursive_directory_iterator::operator++", _Error );
			}
			return *this;
		}

		recursive_directory_iterator & increment( std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Recursive_dir_enum_impl::_Advance_and_reset_if_no_more_files( _Impl ) );
			return *this;
		}

		void pop()
		{
			const auto _Error = _Recursive_dir_enum_impl::_Pop_and_reset_if_no_more_files( _Impl );
			if( _Error != __std_win_error::_Success )
			{
				_Throw_fs_error( "recursive_directory_iterator::pop", _Error );
			}
		}

		void pop( std::error_code & _Ec )
		{
			_Ec = _Make_ec( _Recursive_dir_enum_impl::_Pop_and_reset_if_no_more_files( _Impl ) );
		}

		void disable_recursion_pending() noexcept
		{
			_Impl->_Recursion_pending = false;
		}

		bool operator==( const recursive_directory_iterator & _Rhs ) const noexcept
		{
			return _Impl == _Rhs._Impl;
		}

		bool operator!=( const recursive_directory_iterator & _Rhs ) const noexcept
		{
			return _Impl != _Rhs._Impl;
		}

		_Directory_entry_proxy operator++( int )
		{
			_Directory_entry_proxy _Proxy( **this );
			++ * this;
			return _Proxy;
		}

	private:
		std::shared_ptr<_Recursive_dir_enum_impl> _Impl;
	};

	recursive_directory_iterator begin( recursive_directory_iterator _Iter ) noexcept
	{
		return _Iter;
	}

	recursive_directory_iterator end( recursive_directory_iterator ) noexcept
	{
		return {};
	}

	__std_win_error _Absolute( Path & _Result, const std::wstring & _Text )
	{
		if( _Text.empty() )
		{
			return __std_win_error::_Success;
		}

		_Result._Text.resize( __std_fs_max_path );
		__std_win_error _Err;
		for( ;;)
		{
			const auto _Requested_size = static_cast< unsigned long >( _Result._Text.size() );
			const auto _Full_path_result =
				__std_fs_get_full_path_name( _Text.c_str(), _Requested_size, _Result._Text.data() );
			_Err = _Full_path_result._Error;
			_Result._Text.resize( _Full_path_result._Size );
			if( _Full_path_result._Size < _Requested_size )
			{
				break;
			}
		}

		return _Err;
	}

	Path absolute( const Path & _Input )
	{
		Path _Result;
		const auto _Err = _Absolute( _Result, _Input.native() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "absolute", _Err, _Input );
		}

		return _Result;
	}

	Path absolute( const Path & _Input, std::error_code & _Ec )
	{
		_Ec.clear();
		Path _Result;
		_Ec = _Make_ec( _Absolute( _Result, _Input.native() ) );
		return _Result;
	}

	__std_win_error _Canonical( Path & _Result, const std::wstring & _Text )
	{
		using namespace std::string_view_literals;
		if( _Text.empty() )
		{
			return __std_win_error::_Success;
		}

		auto _Name_kind = __std_fs_volume_name_kind::_Dos;
		{
			__std_win_error _Err;
			const _Fs_file _Handle( _Text.c_str(), __std_access_rights::_File_read_attributes,
									__std_fs_file_flags::_Backup_semantics, &_Err );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}

			_Result._Text.resize( __std_fs_max_path );
			for( ;;)
			{
				const auto _Requested_size = static_cast< unsigned long >( _Result._Text.size() );
				const auto _Final_path_result = __std_fs_get_final_path_name_by_handle(
					_Handle._Raw, _Result._Text.data(), _Requested_size, _Name_kind );
				_Err = _Final_path_result._Error;
				if( _Final_path_result._Size == 0 )
				{
					if( _Err == __std_win_error::_Path_not_found && _Name_kind == __std_fs_volume_name_kind::_Dos )
					{
						_Name_kind = __std_fs_volume_name_kind::_Nt;
						continue;
					}

					_Result._Text.clear();
					return _Err;
				}

				_Result._Text.resize( _Final_path_result._Size );
				if( _Final_path_result._Size < _Requested_size )
				{
					break;
				}
			}
		}

		if( _Name_kind == __std_fs_volume_name_kind::_Dos )
		{
			if( _Is_drive_prefix_with_slash_slash_question( _Result._Text ) )
			{
				_Result._Text.erase( 0, 4 );
			}
			else if( _Result._Text._Starts_with( LR"(\\?\UNC\)"sv ) )
			{
				_Result._Text.erase( 2, 6 );
			}
		}
		else
		{
			_Result._Text.insert( 0, LR"(\\?\GLOBALROOT)"sv );
		}

		return __std_win_error::_Success;
	}

	Path canonical( const Path & _Input )
	{
		Path _Result;
		const auto _Err = _Canonical( _Result, _Input.native() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "canonical", _Err, _Input );
		}

		return _Result;
	}

	Path canonical( const Path & _Input, std::error_code & _Ec )
	{
		_Ec.clear();
		Path _Result;
		_Ec = _Make_ec( _Canonical( _Result, _Input.native() ) );
		return _Result;
	}

	std::unique_ptr<wchar_t[]> _Get_cleaned_symlink_target( const Path & _To ) noexcept
	{
		const auto & _To_str = _To.native();
		std::unique_ptr<wchar_t[]> _Cleaned_link( ::new wchar_t[_To_str.size() + 1] );
		if( !_Cleaned_link )
		{
			return _Cleaned_link;
		}

		const auto _First = _To_str.c_str();
		const auto _Last = _First + _To_str.size();
		auto _Next = _Find_root_name_end( _First, _Last );
		auto _Dest = std::replace_copy_if( _First, _Next, _Cleaned_link.get(), _Is_slash, L'\\' );
		for( ;;)
		{
			const wchar_t _Ch = *_Next;
			if( _Is_slash( _Ch ) )
			{
				*_Dest = L'\\';
				do
				{
					++_Next;
				} while( _Is_slash( *_Next ) );
			}
			else
			{
				*_Dest = _Ch;
				if( _Ch == L'\0' )
				{
					break;
				}

				++_Next;
			}

			++_Dest;
		}

		return _Cleaned_link;
	}

	void create_directory_symlink( const Path & _To, const Path & _New_symlink )
	{
		const auto _Cleaned = _Get_cleaned_symlink_target( _To );
		if( !_Cleaned )
		{
			std::_Xbad_alloc();
		}

		const auto _Err = __std_fs_create_directory_symbolic_link( _New_symlink.c_str(), _Cleaned.get() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "create_directory_symlink", _Err, _To, _New_symlink );
		}
	}

	void create_directory_symlink( const Path & _To, const Path & _New_symlink, std::error_code & _Ec ) noexcept
	{
		const auto _Cleaned = _Get_cleaned_symlink_target( _To );
		if( _Cleaned )
		{
			_Ec = _Make_ec( __std_fs_create_directory_symbolic_link( _New_symlink.c_str(), _Cleaned.get() ) );
		}
		else
		{
			_Ec = std::make_error_code( std::errc::not_enough_memory );
		}
	}

	void create_hard_link( const Path & _To, const Path & _New_hard_link )
	{
		const auto _Err = __std_fs_create_hard_link( _New_hard_link.c_str(), _To.c_str() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "create_hard_link", _Err, _To, _New_hard_link );
		}
	}

	void create_hard_link( const Path & _To, const Path & _New_hard_link, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( __std_fs_create_hard_link( _New_hard_link.c_str(), _To.c_str() ) );
	}

	void create_symlink( const Path & _To, const Path & _New_symlink )
	{
		const auto _Cleaned = _Get_cleaned_symlink_target( _To );
		if( !_Cleaned )
		{
			std::_Xbad_alloc();
		}

		const auto _Err = __std_fs_create_symbolic_link( _New_symlink.c_str(), _Cleaned.get() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "create_symlink", _Err, _To, _New_symlink );
		}
	}

	void create_symlink( const Path & _To, const Path & _New_symlink, std::error_code & _Ec ) noexcept
	{
		const auto _Cleaned = _Get_cleaned_symlink_target( _To );
		if( _Cleaned )
		{
			_Ec = _Make_ec( __std_fs_create_symbolic_link( _New_symlink.c_str(), _Cleaned.get() ) );
		}
		else
		{
			_Ec = std::make_error_code( std::errc::not_enough_memory );
		}
	}

	__std_win_error _Read_symlink_reparse_data(
		const _Fs_file & _Handle, std::unique_ptr<char[]> & _Buffer_unique_ptr ) noexcept
	{
		constexpr auto _Buffer_size = 16 * 1024 + sizeof( wchar_t );

		_Buffer_unique_ptr.reset( ::new char[_Buffer_size] );
		if( !_Buffer_unique_ptr )
		{
			return __std_win_error::_Not_enough_memory;
		}

		const auto _Buffer = reinterpret_cast< __std_fs_reparse_data_buffer * >( _Buffer_unique_ptr.get() );
		const __std_win_error _Err = __std_fs_read_reparse_data_buffer( _Handle._Raw, _Buffer, _Buffer_size );
		if( _Err != __std_win_error::_Success )
		{
			return _Err;
		}

		return __std_win_error::_Success;
	}

	__std_win_error _Read_symlink( const Path & _Symlink_path, Path & _Result ) noexcept
	{
		__std_win_error _Err;
		std::unique_ptr<char[]> _Buffer_unique_ptr;
		{
			const _Fs_file _Handle( _Symlink_path.c_str(), __std_access_rights::_File_read_attributes,
									__std_fs_file_flags::_Backup_semantics | __std_fs_file_flags::_Open_reparse_point, &_Err );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}

			_Err = _Read_symlink_reparse_data( _Handle, _Buffer_unique_ptr );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}
		}

		const auto _Buffer = reinterpret_cast< __std_fs_reparse_data_buffer * >( _Buffer_unique_ptr.get() );
		unsigned short _Length;
		wchar_t * _Offset;
		_Err = __std_fs_read_name_from_reparse_data_buffer( _Buffer, &_Offset, &_Length );
		if( _Err != __std_win_error::_Success )
		{
			return _Err;
		}

		_Result._Text.resize( _Length );
		::memcpy( _Result._Text.data(), _Offset, _Length * sizeof( wchar_t ) );

		return __std_win_error::_Success;
	}

	Path read_symlink( const Path & _Symlink_path, std::error_code & _Ec )
	{
		_Ec.clear();
		Path _Result;
		_Ec = _Make_ec( _Read_symlink( _Symlink_path, _Result ) );
		return _Result;
	}

	Path read_symlink( const Path & _Symlink_path )
	{
		Path _Result;
		const auto _Err = _Read_symlink( _Symlink_path, _Result );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "read_symlink", _Err, _Symlink_path );
		}
		return _Result;
	}

	__std_win_error _Copy_symlink( const Path & _Symlink, const Path & _New_symlink ) noexcept
	{
		__std_win_error _Err;
		std::unique_ptr<char[]> _Buffer_unique_ptr;
		bool _Is_directory;
		{
			const _Fs_file _Handle( _Symlink.c_str(), __std_access_rights::_File_read_attributes,
									__std_fs_file_flags::_Backup_semantics | __std_fs_file_flags::_Open_reparse_point, &_Err );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}

			_Err = _Read_symlink_reparse_data( _Handle, _Buffer_unique_ptr );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}

			unsigned long _File_attributes;
			_Err = __std_fs_get_file_attributes_by_handle( _Handle._Raw, &_File_attributes );
			if( _Err != __std_win_error::_Success )
			{
				return _Err;
			}

			_Is_directory = ( _File_attributes & static_cast< unsigned long >( __std_fs_file_attr::_Directory ) ) != 0;
		}

		const auto _Buffer = reinterpret_cast< __std_fs_reparse_data_buffer * >( _Buffer_unique_ptr.get() );
		unsigned short _Length;
		wchar_t * _Offset;
		_Err = __std_fs_read_name_from_reparse_data_buffer( _Buffer, &_Offset, &_Length );
		if( _Err != __std_win_error::_Success )
		{
			return _Err;
		}

		_Offset[_Length] = L'\0';

		if( _Is_directory )
		{
			_Err = __std_fs_create_directory_symbolic_link( _New_symlink.c_str(), _Offset );
		}
		else
		{
			_Err = __std_fs_create_symbolic_link( _New_symlink.c_str(), _Offset );
		}

		return _Err;
	}

	void copy_symlink( const Path & _Symlink, const Path & _New_symlink, std::error_code & _Ec )
	{
		_Ec = _Make_ec( _Copy_symlink( _Symlink, _New_symlink ) );
	}

	void copy_symlink( const Path & _Symlink, const Path & _New_symlink )
	{
		const auto _Err = _Copy_symlink( _Symlink, _New_symlink );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "copy_symlink", _Err, _Symlink, _New_symlink );
		}
	}

	bool copy_file(
		const Path & _From, const Path & _To, const copy_options _Options, std::error_code & _Ec ) noexcept
	{
		const auto _Result =
			__std_fs_copy_file( _From.c_str(), _To.c_str(), static_cast< __std_fs_copy_options >( _Options ) );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Copied;
	}

	bool copy_file( const Path & _From, const Path & _To, const copy_options _Options )
	{
		const auto _Result =
			__std_fs_copy_file( _From.c_str(), _To.c_str(), static_cast< __std_fs_copy_options >( _Options ) );
		if( _Result._Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "copy_file", _Result._Error, _From, _To );
		}

		return _Result._Copied;
	}

	bool copy_file( const Path & _From, const Path & _To, std::error_code & _Ec ) noexcept
	{
		return FileSystem::copy_file( _From, _To, copy_options::none, _Ec );
	}

	bool copy_file( const Path & _From, const Path & _To )
	{
		return FileSystem::copy_file( _From, _To, copy_options::none );
	}

	std::pair<__std_win_error, bool> _Equivalent(
		const wchar_t * const _Lhs, const wchar_t * const _Rhs ) noexcept
	{
		__std_fs_file_id _Left_id;
		__std_fs_file_id _Right_id;
		auto _Last_error = __std_fs_get_file_id( &_Left_id, _Lhs );
		if( _Last_error != __std_win_error::_Success )
		{
			return { _Last_error, false };
		}

		_Last_error = __std_fs_get_file_id( &_Right_id, _Rhs );
		if( _Last_error != __std_win_error::_Success )
		{
			return { _Last_error, false };
		}

		return { __std_win_error::_Success, ::memcmp( &_Left_id, &_Right_id, sizeof( __std_fs_file_id ) ) == 0 };
	}

	bool equivalent( const Path & _Lhs, const Path & _Rhs )
	{
		const auto _Result = _Equivalent( _Lhs.c_str(), _Rhs.c_str() );
		if( _Result.first != __std_win_error::_Success )
		{
			_Throw_fs_error( "equivalent", _Result.first, _Lhs, _Rhs );
		}

		return _Result.second;
	}

	bool equivalent( const Path & _Lhs, const Path & _Rhs, std::error_code & _Ec ) noexcept
	{
		const auto _Result = _Equivalent( _Lhs.c_str(), _Rhs.c_str() );
		_Ec = _Make_ec( _Result.first );
		return _Result.second;
	}

	file_status status( const Path & _Path );
	file_status status( const Path & _Path, std::error_code & _Ec ) noexcept;
	file_status symlink_status( const Path & _Path );
	file_status symlink_status( const Path & _Path, std::error_code & _Ec ) noexcept;

	bool exists( const Path & _Target, std::error_code & _Ec ) noexcept
	{
		const auto _Type = FileSystem::status( _Target, _Ec ).type();
		if( _Type != file_type::none )
		{
			_Ec.clear();
			return _Type != file_type::not_found;
		}

		return false;
	}

	bool exists( const Path & _Target )
	{
		std::error_code _Ec;
		const bool _Result = FileSystem::exists( _Target, _Ec );
		if( _Ec )
		{
			_Throw_fs_error( "exists", _Ec, _Target );
		}

		return _Result;
	}

	__std_win_error _File_size( const Path & _Path, uintmax_t & _Result ) noexcept
	{
		__std_fs_stats _Stats;
		const auto _Error = __std_fs_get_stats(
			_Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_File_size );
		if( _Error == __std_win_error::_Success )
		{
			_Result = _Stats._File_size;
		}
		else
		{
			_Result = static_cast< uintmax_t >( -1 );
		}

		return _Error;
	}

	uintmax_t file_size( const Path & _Path )
	{
		uintmax_t _Result;
		const auto _Error = _File_size( _Path, _Result );
		if( _Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "file_size", _Error, _Path );
		}

		return _Result;
	}

	uintmax_t file_size( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		uintmax_t _Result;
		_Ec = _Make_ec( _File_size( _Path, _Result ) );
		return _Result;
	}

	__std_win_error _Hard_link_count( const Path & _Path, uintmax_t & _Result ) noexcept
	{
		__std_fs_stats _Stats;
		const auto _Error = __std_fs_get_stats(
			_Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_Link_count );
		if( _Error == __std_win_error::_Success )
		{
			_Result = _Stats._Link_count;
		}
		else
		{
			_Result = static_cast< uintmax_t >( -1 );
		}

		return _Error;
	}

	uintmax_t hard_link_count( const Path & _Target )
	{
		uintmax_t _Result;
		const auto _Err = _Hard_link_count( _Target, _Result );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "hard_link_count", _Err, _Target );
		}

		return _Result;
	}

	uintmax_t hard_link_count( const Path & _Target, std::error_code & _Ec ) noexcept
	{
		uintmax_t _Result;
		_Ec = _Make_ec( _Hard_link_count( _Target, _Result ) );
		return _Result;
	}

	bool is_block_file( const Path & ) noexcept
	{
		return false;
	}

	bool is_block_file( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		( void ) FileSystem::status( _Path, _Ec );
		return false;
	}

	bool is_character_file( const Path & ) noexcept
	{
		return false;
	}

	bool is_character_file( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		( void ) FileSystem::status( _Path, _Ec );
		return false;
	}

	bool is_directory( const Path & _Path )
	{
		return FileSystem::is_directory( FileSystem::status( _Path ) );
	}

	bool is_directory( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		return FileSystem::is_directory( FileSystem::status( _Path, _Ec ) );
	}

	bool is_empty( const Path & _Path, std::error_code & _Ec )
	{
		constexpr auto _Flags = __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_File_size
			| __std_fs_stats_flags::_Follow_symlinks;
		__std_fs_stats _Stats;
		const auto _Error = __std_fs_get_stats( _Path.c_str(), &_Stats, _Flags );
		_Ec = _Make_ec( _Error );
		if( _Error != __std_win_error::_Success )
		{
			return false;
		}

		if( ( _Stats._Attributes & __std_fs_file_attr::_Directory ) == __std_fs_file_attr{} )
		{
			return _Stats._File_size == 0;
		}
		else
		{
			directory_iterator _Iter( _Path, _Ec );
			return !_Ec && _Iter._At_end();
		}
	}

	bool is_empty( const Path & _Path )
	{
		std::error_code _Ec;
		const bool _Result = is_empty( _Path, _Ec );
		if( _Ec )
		{
			_Throw_fs_error( "is_empty", _Ec, _Path );
		}

		return _Result;
	}

	bool is_fifo( const Path & ) noexcept
	{
		return false;
	}

	bool is_fifo( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		( void ) FileSystem::status( _Path, _Ec );
		return false;
	}

	bool is_other( const Path & _Path )
	{
		return FileSystem::is_other( FileSystem::status( _Path ) );
	}

	bool is_other( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		return FileSystem::is_other( FileSystem::status( _Path, _Ec ) );
	}

	bool is_regular_file( const Path & _Path )
	{
		return FileSystem::is_regular_file( FileSystem::status( _Path ) );
	}

	bool is_regular_file( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		return FileSystem::is_regular_file( FileSystem::status( _Path, _Ec ) );
	}

	bool is_socket( const Path & ) noexcept
	{
		return false;
	}

	bool is_socket( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		( void ) FileSystem::status( _Path, _Ec );
		return false;
	}

	bool is_symlink( const Path & _Path )
	{
		return FileSystem::is_symlink( FileSystem::symlink_status( _Path ) );
	}

	bool is_symlink( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		return FileSystem::is_symlink( FileSystem::symlink_status( _Path, _Ec ) );
	}

	bool remove( const Path & _Target )
	{
		const auto _Result = __std_fs_remove( _Target.c_str() );
		if( _Result._Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "remove", _Result._Error, _Target );
		}

		return _Result._Removed;
	}

	bool remove( const Path & _Target, std::error_code & _Ec ) noexcept
	{
		const auto _Result = __std_fs_remove( _Target.c_str() );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Removed;
	}

	void rename( const Path & _Old_p, const Path & _New_p )
	{
		const auto _Err = __std_fs_rename( _Old_p.c_str(), _New_p.c_str() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "rename", _Err, _Old_p, _New_p );
		}
	}

	void rename( const Path & _Old_p, const Path & _New_p, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( __std_fs_rename( _Old_p.c_str(), _New_p.c_str() ) );
	}

	void resize_file( const Path & _Target, const uintmax_t _New_size )
	{
		const auto _Err = __std_fs_resize_file( _Target.c_str(), _New_size );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "resize_file", _Err, _Target );
		}
	}

	void resize_file( const Path & _Target, const uintmax_t _New_size, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( __std_fs_resize_file( _Target.c_str(), _New_size ) );
	}

	struct space_info
	{
		uintmax_t capacity;
		uintmax_t free;
		uintmax_t available;
	};

	space_info space( const Path & _Target )
	{
		space_info _Result;
		const auto _Last_error = __std_fs_space( _Target.c_str(), &_Result.available, &_Result.capacity, &_Result.free );
		if( _Last_error != __std_win_error::_Success )
		{
			_Throw_fs_error( "space", _Last_error, _Target );
		}

		return _Result;
	}

	space_info space( const Path & _Target, std::error_code & _Ec ) noexcept
	{
		space_info _Result;
		_Ec = _Make_ec( __std_fs_space( _Target.c_str(), &_Result.available, &_Result.capacity, &_Result.free ) );
		return _Result;
	}

	bool status_known( const file_status _Status ) noexcept
	{
		return _Status.type() != file_type::none;
	}

	_File_status_and_error _Get_any_status(
		const Path & _Path, const __std_fs_stats_flags _Flags ) noexcept
	{
		_File_status_and_error _Result;
		__std_fs_stats _Stats;

		const auto _Error = __std_fs_get_stats( _Path.c_str(), &_Stats, _Flags );
		_Result._Error = _Error;
		_Result._Status._Refresh( _Error, _Stats );

		return _Result;
	}

	file_status status( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		const auto _Result = _Get_any_status( _Path, _Status_stats_flags );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Status;
	}

	file_status status( const Path & _Path )
	{
		const auto _Result = _Get_any_status( _Path, _Status_stats_flags );
		if( _Result._Not_good() )
		{
			_Throw_fs_error( "status", _Result._Error, _Path );
		}
		return _Result._Status;
	}

	file_status symlink_status( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		const auto _Result = _Get_any_status( _Path, _Symlink_status_stats_flags );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Status;
	}

	file_status symlink_status( const Path & _Path )
	{
		const auto _Result = _Get_any_status( _Path, _Symlink_status_stats_flags );
		if( _Result._Not_good() )
		{
			_Throw_fs_error( "symlink_status", _Result._Error, _Path );
		}

		return _Result._Status;
	}

	bool create_directory( const Path & _Path )
	{
		const auto _Result = __std_fs_create_directory( _Path.c_str() );
		if( _Result._Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "create_directory", _Result._Error, _Path );
		}

		return _Result._Created;
	}

	bool create_directory( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		const auto _Result = __std_fs_create_directory( _Path.c_str() );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Created;
	}

	bool create_directory( const Path & _Path, const Path & _Existing_p )
	{
		const auto _Result = __std_fs_create_directory( _Path.c_str() );
		if( _Result._Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "create_directory", _Result._Error, _Path, _Existing_p );
		}

		return _Result._Created;
	}

	bool create_directory( const Path & _Path, const Path &, std::error_code & _Ec ) noexcept
	{
		const auto _Result = __std_fs_create_directory( _Path.c_str() );
		_Ec = _Make_ec( _Result._Error );
		return _Result._Created;
	}

	bool create_directories( const Path & _Path, std::error_code & _Ec )
	{
		_Ec.clear();
		const std::wstring & _Text = _Path.native();
		std::wstring _Tmp;
		_Tmp.reserve( _Text.size() );
		auto _Cursor = _Text.data();
		const auto _End = _Text.data() + _Text.size();
		auto _Root_path_end = _Find_relative_path( _Cursor, _End );
		if( _Root_path_end != _Cursor && _End - _Root_path_end >= 3 && _Is_drive_prefix( _Root_path_end )
			&& _Is_slash( _Root_path_end[2] ) )
		{
			_Root_path_end += 2;
		}

		_Tmp.append( _Cursor, _Root_path_end );
		_Cursor = _Root_path_end;


		bool _Created_last = false;
		__std_win_error _Error = __std_win_error::_Success;
		__std_win_error _Most_recent_not_file_not_found = __std_win_error::_Success;
		while( _Cursor != _End )
		{
			const auto _Added_end = std::find_if( std::find_if_not( _Cursor, _End, _Is_slash ), _End, _Is_slash );
			_Tmp.append( _Cursor, _Added_end );
			const auto _Create_result = __std_fs_create_directory( _Tmp.c_str() );
			_Error = _Create_result._Error;
			_Created_last = _Create_result._Created;
			_Error = _Create_result._Error;
			if( _Error != __std_win_error::_Success && !_Is_file_not_found( _Error ) )
			{
				_Most_recent_not_file_not_found = _Error;
			}

			_Cursor = _Added_end;
		}

		if( _Error != __std_win_error::_Success && _Most_recent_not_file_not_found != __std_win_error::_Success )
		{
			_Error = _Most_recent_not_file_not_found;
		}

		_Ec = _Make_ec( _Error );
		return _Created_last;
	}

	bool create_directories( const Path & _Path )
	{
		std::error_code _Ec;
		const bool _Result = FileSystem::create_directories( _Path, _Ec );
		if( _Ec )
		{
			_Throw_fs_error( "create_directories", _Ec, _Path );
		}

		return _Result;
	}

	constexpr int _Remove_all_retry_count = 10;

	void _Remove_all_dir( const Path & _Path, std::error_code & _Ec, uintmax_t & _Removed_count )
	{
		for( directory_iterator _It( _Path, _Ec );; _It.increment( _Ec ) )
		{
			if( _Ec )
			{
				if( _Ec.category() != std::system_category()
					|| !_Is_file_not_found( static_cast< __std_win_error >( _Ec.value() ) ) )
				{
					return;
				}

				break;
			}

			if( _It._At_end() )
			{
				break;
			}

			const auto & _Subpath = _It->path();
			const auto _Substatus = _It->symlink_status( _Ec );
			if( _Ec )
			{
				return;
			}

			if( _Substatus.type() == file_type::directory )
			{
				_Remove_all_dir( _Subpath, _Ec, _Removed_count );
			}
			else
			{
				_Removed_count += FileSystem::remove( _Subpath, _Ec );
			}

			if( _Ec )
			{
				return;
			}
		}

		for( int _Retry = 0; _Retry < _Remove_all_retry_count; ++_Retry )
		{
			const auto _Path_remove_result = __std_fs_remove( _Path.c_str() );
			_Removed_count += _Path_remove_result._Removed;
			_Ec = _Make_ec( _Path_remove_result._Error );
			if( _Path_remove_result._Error != __std_win_error::_Directory_not_empty
				&& _Path_remove_result._Error != __std_win_error::_Access_denied )
			{
				return;
			}
		}
	}

	uintmax_t remove_all( const Path & _Path, std::error_code & _Ec )
	{
		_Ec.clear();
		const auto _First_remove_result = __std_fs_remove( _Path.c_str() );
		uintmax_t _Removed_count = _First_remove_result._Removed;
		_Ec = _Make_ec( _First_remove_result._Error );
		if( _First_remove_result._Error == __std_win_error::_Directory_not_empty )
		{
			_Remove_all_dir( _Path, _Ec, _Removed_count );
		}

		if( _Ec )
		{
			_Removed_count = static_cast< uintmax_t >( -1 );
		}

		return _Removed_count;
	}

	uintmax_t remove_all( const Path & _Path )
	{
		std::error_code _Ec;
		const auto _Removed_count = FileSystem::remove_all( _Path, _Ec );
		if( _Ec )
		{
			_Throw_fs_error( "remove_all", _Ec, _Path );
		}

		return _Removed_count;
	}

	__std_win_error _Last_write_time( const Path & _Path, file_time_type & _Result ) noexcept
	{
		__std_fs_stats _Stats;
		const auto _Error = __std_fs_get_stats(
			_Path.c_str(), &_Stats, __std_fs_stats_flags::_Follow_symlinks | __std_fs_stats_flags::_Last_write_time );
		if( _Error == __std_win_error::_Success )
		{
			_Result = file_time_type{ file_time_type::duration{_Stats._Last_write_time} };
		}
		else
		{
			_Result = ( file_time_type::min )( );
		}

		return _Error;
	}

	file_time_type last_write_time( const Path & _Path )
	{
		file_time_type _Result;
		const auto _Error = _Last_write_time( _Path, _Result );
		if( _Error != __std_win_error::_Success )
		{
			_Throw_fs_error( "last_write_time", _Error, _Path );
		}

		return _Result;
	}

	file_time_type last_write_time( const Path & _Path, std::error_code & _Ec ) noexcept
	{
		file_time_type _Result;
		_Ec = _Make_ec( _Last_write_time( _Path, _Result ) );
		return _Result;
	}

	void last_write_time( const Path & _Target, const file_time_type _New_time )
	{
		const auto _Err = __std_fs_set_last_write_time( _New_time.time_since_epoch().count(), _Target.c_str() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "last_write_time", _Err, _Target );
		}
	}

	void last_write_time( const Path & _Target, const file_time_type _New_time, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( __std_fs_set_last_write_time( _New_time.time_since_epoch().count(), _Target.c_str() ) );
	}

	enum class perm_options
	{
		replace = 0x1, add = 0x2, remove = 0x4, nofollow = 0x8
	};

	XE_BITMASK_OPS( perm_options )

	__std_win_error _Permissions( const Path & _Target, const perms _Perms, perm_options _Options ) noexcept
	{
		bool _Readonly;
		const bool _Follow_symlinks = ( _Options & perm_options::nofollow ) == perm_options{};
		_Options &= ~perm_options::nofollow;
		const auto _Write_perms = _Perms & perms::_All_write;
		switch( _Options )
		{
		case perm_options::replace:
			_Readonly = _Write_perms == perms::none;
			break;
		case perm_options::add:
			if( _Write_perms == perms::none )
			{
				return __std_win_error::_Success;
			}

			_Readonly = false;
			break;
		case perm_options::remove:
			if( _Write_perms != perms::_All_write )
			{
				return __std_win_error::_Success;
			}

			_Readonly = true;
			break;
		case perm_options::nofollow:
		default:
			return __std_win_error::_Invalid_parameter;
		}

		return __std_fs_change_permissions( _Target.c_str(), _Follow_symlinks, _Readonly );
	}

	void permissions( const Path & _Target, const perms _Perms, const perm_options _Options = perm_options::replace )
	{
		const auto _Err = _Permissions( _Target, _Perms, _Options );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "permissions", _Err, _Target );
		}
	}

	void permissions( const Path & _Target, const perms _Perms, const perm_options _Options, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( _Permissions( _Target, _Perms, _Options ) );
	}

	void permissions( const Path & _Target, const perms _Perms, std::error_code & _Ec ) noexcept
	{
		FileSystem::permissions( _Target, _Perms, perm_options::replace, _Ec );
	}

	Path temp_directory_path( std::error_code & _Ec )
	{
		_Ec.clear();
		Path _Result;
		_Result._Text.resize( __std_fs_temp_path_max );
		const auto _Temp_result = __std_fs_get_temp_path( _Result._Text.data() );
		_Result._Text.resize( _Temp_result._Size );
		if( _Temp_result._Error == __std_win_error::_Max )
		{
			_Ec = std::make_error_code( std::errc::not_a_directory );
		}
		else
		{
			_Ec = _Make_ec( _Temp_result._Error );
		}

		return _Result;
	}

	Path temp_directory_path()
	{
		std::error_code _Ec;
		Path _Result( FileSystem::temp_directory_path( _Ec ) );
		if( _Ec )
		{
			_Throw_fs_error( "temp_directory_path", _Ec, _Result );
		}
		return _Result;
	}

	__std_win_error _Current_path( Path & _Result ) noexcept
	{
		_Result._Text.resize( __std_fs_max_path );
		for( ;;)
		{
			const auto _Requested_size = static_cast< unsigned long >( _Result._Text.size() );
			const auto _Temp_result = __std_fs_get_current_path( _Requested_size, _Result._Text.data() );
			_Result._Text.resize( _Temp_result._Size );
			if( _Temp_result._Size < _Requested_size )
			{
				return _Temp_result._Error;
			}
		}
	}

	Path current_path( std::error_code & _Ec )
	{
		_Ec.clear();
		Path _Result;
		_Ec = _Make_ec( _Current_path( _Result ) );
		return _Result;
	}

	Path current_path()
	{
		Path _Result;
		const auto _Err = _Current_path( _Result );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "current_path()", _Err );
		}
		return _Result;
	}

	void current_path( const Path & _To, std::error_code & _Ec ) noexcept
	{
		_Ec = _Make_ec( __std_fs_set_current_path( _To._Text.data() ) );
	}

	void current_path( const Path & _To )
	{
		const auto _Err = __std_fs_set_current_path( _To._Text.data() );
		if( _Err != __std_win_error::_Success )
		{
			_Throw_fs_error( "current_path(const path&)", _Err, _To );
		}
	}

	Path weakly_canonical( const Path & _Input, std::error_code & _Ec )
	{
		_Ec.clear();

		Path _Temp;

		{
			const auto _Err = _Canonical( _Temp, _Input.native() );

			if( _Err == __std_win_error::_Success )
			{
				return _Temp;
			}

			if( !_Is_file_not_found( _Err ) )
			{
				_Ec = _Make_ec( _Err );
				return Path();
			}
		}

		const Path _Normalized = _Input.lexically_normal();

		Path _Result = _Normalized.root_path();

		const Path _Normalized_relative = _Normalized.relative_path();

		bool _Call_canonical = true;

		for( const auto & _Elem : _Normalized_relative )
		{
			_Result /= _Elem;

			if( _Call_canonical )
			{
				_Temp.clear();

				const auto _Err = _Canonical( _Temp, _Result.native() );

				if( _Err == __std_win_error::_Success )
				{
					_Result = std::move( _Temp );
				}
				else if( _Is_file_not_found( _Err ) )
				{
					_Call_canonical = false;
				}
				else
				{
					_Ec = _Make_ec( _Err );
					return Path();
				}
			}
		}

		return _Result;
	}

	Path weakly_canonical( const Path & _Input )
	{
		std::error_code _Ec;

		Path _Result = FileSystem::weakly_canonical( _Input, _Ec );

		if( _Ec )
		{
			_Throw_fs_error( "weakly_canonical", _Ec, _Input );
		}

		return _Result;
	}

	Path proximate( const Path & _Path, const Path & _Base = FileSystem::current_path() )
	{
		const Path _Weakly_canonical_path = FileSystem::weakly_canonical( _Path );
		const Path _Weakly_canonical_base = FileSystem::weakly_canonical( _Base );
		return _Weakly_canonical_path.lexically_proximate( _Weakly_canonical_base );
	}

	Path proximate( const Path & _Path, const Path & _Base, std::error_code & _Ec )
	{
		const Path _Weakly_canonical_path = FileSystem::weakly_canonical( _Path, _Ec );

		if( _Ec )
		{
			return Path();
		}

		const Path _Weakly_canonical_base = FileSystem::weakly_canonical( _Base, _Ec );

		if( _Ec )
		{
			return Path();
		}

		return _Weakly_canonical_path.lexically_proximate( _Weakly_canonical_base );
	}

	Path proximate( const Path & _Path, std::error_code & _Ec )
	{
		const Path _Base = FileSystem::current_path( _Ec );
		if( _Ec )
		{
			return Path();
		}

		return FileSystem::proximate( _Path, _Base, _Ec );
	}

	Path relative( const Path & _Path, const Path & _Base = FileSystem::current_path() )
	{
		const Path _Weakly_canonical_path = FileSystem::weakly_canonical( _Path );
		const Path _Weakly_canonical_base = FileSystem::weakly_canonical( _Base );
		return _Weakly_canonical_path.lexically_relative( _Weakly_canonical_base );
	}

	Path relative( const Path & _Path, const Path & _Base, std::error_code & _Ec )
	{
		const Path _Weakly_canonical_path = FileSystem::weakly_canonical( _Path, _Ec );

		if( _Ec )
		{
			return Path();
		}

		const Path _Weakly_canonical_base = FileSystem::weakly_canonical( _Base, _Ec );

		if( _Ec )
		{
			return Path();
		}

		return _Weakly_canonical_path.lexically_relative( _Weakly_canonical_base );
	}

	Path relative( const Path & _Path, std::error_code & _Ec )
	{
		const Path _Base = FileSystem::current_path( _Ec );
		if( _Ec )
		{
			return Path();
		}

		return FileSystem::relative( _Path, _Base, _Ec );
	}

	void _Copy_impl( const directory_entry & _From, const Path & _To, const copy_options _Options, std::error_code & _Ec )
	{
		const bool _Flink = ( _Options & ( copy_options::skip_symlinks | copy_options::copy_symlinks ) )
			!= copy_options::none;
		const auto _Fstat = _From._Get_any_status( _Flink ? _Symlink_status_stats_flags : _Status_stats_flags );
		if( _Fstat._Error != __std_win_error::_Success )
		{
			_Ec = _Make_ec( _Fstat._Error );
			return;
		}

		const bool _Tlink =
			( _Options & ( copy_options::create_symlinks | copy_options::skip_symlinks ) ) != copy_options::none;
		const auto _Tstat = _Get_any_status( _To, _Tlink ? _Symlink_status_stats_flags : _Status_stats_flags );
		if( _Tstat._Not_good() )
		{
			_Ec = _Make_ec( _Tstat._Error );
			return;
		}

		if( FileSystem::exists( _Tstat._Status ) )
		{
			if( FileSystem::equivalent( _From, _To, _Ec ) )
			{
				_Ec = std::make_error_code( std::errc::file_exists );
				return;
			}

			if( _Ec )
			{
				return;
			}
		}

		if( FileSystem::is_other( _Fstat._Status ) || FileSystem::is_other( _Tstat._Status ) )
		{
			_Ec = std::make_error_code( std::errc::operation_not_supported );
			return;
		}

		if( FileSystem::is_directory( _Fstat._Status ) && FileSystem::is_regular_file( _Tstat._Status ) )
		{
			_Ec = std::make_error_code( std::errc::file_exists );
			return;
		}

		if( FileSystem::is_symlink( _Fstat._Status ) )
		{
			if( ( _Options & copy_options::skip_symlinks ) != copy_options::none )
			{
				return;
			}

			if( !FileSystem::exists( _Tstat._Status )
				&& ( _Options & copy_options::copy_symlinks ) != copy_options::none )
			{
				FileSystem::copy_symlink( _From, _To, _Ec );
				return;
			}

			_Ec = std::make_error_code( std::errc::operation_not_supported );
			return;
		}

		if( FileSystem::is_regular_file( _Fstat._Status ) )
		{
			if( ( _Options & copy_options::directories_only ) != copy_options::none )
			{
				return;
			}

			if( ( _Options & copy_options::create_symlinks ) != copy_options::none )
			{
				FileSystem::create_symlink( _From, _To, _Ec );
				return;
			}

			if( ( _Options & copy_options::create_hard_links ) != copy_options::none )
			{
				FileSystem::create_hard_link( _From, _To, _Ec );
				return;
			}

			if( FileSystem::is_directory( _Tstat._Status ) )
			{
				FileSystem::copy_file( _From, _To / _From.path().filename(), _Options, _Ec );
				return;
			}

			FileSystem::copy_file( _From, _To, _Options, _Ec );
			return;
		}

		if( FileSystem::is_directory( _Fstat._Status ) )
		{
			if( ( _Options & copy_options::create_symlinks ) != copy_options::none )
			{
				_Ec = std::make_error_code( std::errc::is_a_directory );
				return;
			}

			FileSystem::create_directory( _To, _From, _Ec );
			if( _Ec )
			{
				return;
			}

			if( ( _Options & copy_options::recursive ) != copy_options::none
				|| ( _Options & copy_options::directories_only ) == copy_options::none )
			{
				for( directory_iterator _It( _From, _Ec );; _It.increment( _Ec ) )
				{
					if( _Ec || _It._At_end() )
					{
						return;
					}

					bool _Recurse = ( _Options & copy_options::recursive ) != copy_options::none;
					if( !_Recurse )
					{
						const auto _Child_status_result =
							_It->_Get_any_status( _Flink ? _Symlink_status_stats_flags : _Status_stats_flags );
						if( _Child_status_result._Error != __std_win_error::_Success )
						{
							_Ec = _Make_ec( _Child_status_result._Error );
							return;
						}

						_Recurse = !FileSystem::is_directory( _Child_status_result._Status );
					}

					if( _Recurse )
					{
						_Copy_impl( *_It, _To / _It->path().filename(), _Options, _Ec );
						if( _Ec )
						{
							return;
						}
					}
				}
			}
		}

	}

	void copy( const Path & _From, const Path & _To, const copy_options _Options, std::error_code & _Ec )
	{
		const directory_entry _From_dir( _From, _Ec );
		if( _Ec )
		{
			return;
		}

		_Copy_impl( _From_dir, _To, _Options, _Ec );
	}

	void copy( const Path & _From, const Path & _To, const copy_options _Options )
	{
		std::error_code _Ec;
		FileSystem::copy( _From, _To, _Options, _Ec );
		if( _Ec )
		{
			_Throw_fs_error( "copy", _Ec, _From, _To );
		}
	}

	void copy( const Path & _From, const Path & _To, std::error_code & _Ec )
	{
		return FileSystem::copy( _From, _To, copy_options::none, _Ec );
	}

	void copy( const Path & _From, const Path & _To )
	{
		return FileSystem::copy( _From, _To, copy_options::none );
	}
};

#endif

inline std::string ToString( const XE::FileSystem::Path & _Val )
{
	return _Val.u8string();
}

inline bool FromString( const std::string & _Str, XE::FileSystem::Path & _Val )
{
	_Val = _Str;
}

END_XE_NAMESPACE

#endif // FILESYSTEM_H__9E3E6B04_2D43_49AE_9FD4_08CEED267D20