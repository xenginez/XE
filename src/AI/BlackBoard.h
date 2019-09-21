/*!
 * \file   BlackBoard.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BLACKBOARD_H__969FD98B_F332_4E99_8B0B_745F2A23B795
#define __BLACKBOARD_H__969FD98B_F332_4E99_8B0B_745F2A23B795

#include "BBKeyPtr.hpp"

BEG_XE_NAMESPACE

class XE_API BlackBoard
{
	OBJECT( BlackBoard )

public:
	BlackBoard();

	~BlackBoard();

public:
	template< typename T > BBKeyPtr<T> GetKey( const String& val )
	{
		auto it = _Keys.find( val );

		if ( it != _Keys.end() )
		{
			return &( it->second );
		}

		return nullptr;
	}

private:
	Map<String, Variant> _Keys;
};

END_XE_NAMESPACE

#endif // __BLACKBOARD_H__969FD98B_F332_4E99_8B0B_745F2A23B795
