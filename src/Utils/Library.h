/*!
 * \file   Library.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/17
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LIBRARY_H__752AAED6_001C_4D36_A353_57FC8E154A2A
#define __LIBRARY_H__752AAED6_001C_4D36_A353_57FC8E154A2A

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Library : public XE::Singleton< Library >
{
	struct Private;

public:
	Library();

	~Library();

public:
	static uint64 Open( const String& name );

	template< typename T >
	static T SymbolT( uint64 index, const String& name )
	{
		return reinterpret_cast<T>( Symbol( index, name ) );
	}

	static void * Symbol( uint64 index, const String& name );

	static void Close( uint64 index );

	static String Name( uint64 index );

	static void InsertSearchPath( const std::filesystem::path& val );

	const Array< std::filesystem::path >& GetSearchPaths() const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __LIBRARY_H__752AAED6_001C_4D36_A353_57FC8E154A2A
