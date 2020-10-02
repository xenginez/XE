#include "FileSystem.h"

XE::FileSystem::__std_ulong_and_error XE::FileSystem::__std_fs_get_full_path_name( const wchar_t * _Source, unsigned long _Target_size, wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_open_handle( __std_fs_file_handle * _Handle, const wchar_t * _File_name, __std_access_rights _Desired_access, __std_fs_file_flags _Flags ) noexcept
{
	return {};
}

void XE::FileSystem::__std_fs_close_handle( __std_fs_file_handle _Handle ) noexcept
{

}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_get_file_attributes_by_handle( __std_fs_file_handle _Handle, unsigned long * _File_attributes ) noexcept
{
	return {};
}

XE::FileSystem::__std_ulong_and_error XE::FileSystem::__std_fs_get_final_path_name_by_handle( __std_fs_file_handle _Handle, wchar_t * _Target, unsigned long _Target_size, __std_fs_volume_name_kind _Flags ) noexcept
{
	return {};
}

XE::FileSystem::__std_fs_copy_file_result XE::FileSystem::__std_fs_copy_file( const wchar_t * _Source, const wchar_t * _Target, __std_fs_copy_options _Options ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_directory_iterator_open( const wchar_t * _Path_spec, __std_fs_dir_handle * _Handle, __std_fs_find_data * _Results ) noexcept
{
	return {};
}

void XE::FileSystem::__std_fs_directory_iterator_close( __std_fs_dir_handle _Handle ) noexcept
{

}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_get_stats( const wchar_t * _Path, __std_fs_stats * _Stats, __std_fs_stats_flags _Flags, __std_fs_file_attr _Symlink_attribute_hint /*= __std_fs_file_attr::_Invalid */ ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_directory_iterator_advance( __std_fs_dir_handle _Handle, __std_fs_find_data * _Results ) noexcept
{
	return {};
}

XE::FileSystem::__std_code_page XE::FileSystem::__std_fs_code_page() noexcept
{
	return {};
}

XE::FileSystem::__std_fs_convert_result XE::FileSystem::__std_fs_convert_narrow_to_wide( __std_code_page _Code_page, const char * _Input_str, int _Input_len, wchar_t * _Output_str, int _Output_len ) noexcept
{
	return {};
}

XE::FileSystem::__std_fs_convert_result XE::FileSystem::__std_fs_convert_wide_to_narrow( __std_code_page _Code_page, const wchar_t * _Input_str, int _Input_len, char * _Output_str, int _Output_len ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_get_file_id( __std_fs_file_id * _Id, const wchar_t * _Path ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_set_last_write_time( long long _Last_write_filetime, const wchar_t * _Path ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_change_permissions( const wchar_t * _Path, bool _Follow_symlinks, bool _Readonly ) noexcept
{
	return {};
}

XE::FileSystem::__std_ulong_and_error XE::FileSystem::__std_fs_get_temp_path( wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_ulong_and_error XE::FileSystem::__std_fs_get_current_path( unsigned long _Target_size, wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_set_current_path( const wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_create_directory_symbolic_link( const wchar_t * _Symlink_file_name, const wchar_t * _Target_file_name ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_create_hard_link( const wchar_t * _File_name, const wchar_t * _Existing_file_name ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_create_symbolic_link( const wchar_t * _Symlink_file_name, const wchar_t * _Target_file_name ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_read_reparse_data_buffer( __std_fs_file_handle _Handle, void * _Buffer, unsigned long _Buffer_size ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_read_name_from_reparse_data_buffer( __std_fs_reparse_data_buffer * _Handle, wchar_t ** _Offset, unsigned short * _Length ) noexcept
{
	return {};
}

XE::FileSystem::__std_fs_create_directory_result XE::FileSystem::__std_fs_create_directory( const wchar_t * _New_directory ) noexcept
{
	return {};
}

XE::FileSystem::__std_fs_remove_result XE::FileSystem::__std_fs_remove( const wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_rename( const wchar_t * _Source, const wchar_t * _Target ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_resize_file( const wchar_t * _Target, uintmax_t _New_size ) noexcept
{
	return {};
}

XE::FileSystem::__std_win_error XE::FileSystem::__std_fs_space( const wchar_t * _Target, uintmax_t * _Available, uintmax_t * _Total_bytes, uintmax_t * _Free_bytes ) noexcept
{
	return {};
}
