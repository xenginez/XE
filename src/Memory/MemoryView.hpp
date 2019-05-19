/*!
 * \file    MemoryView.hpp
 *
 * \author  ZhengYuanQing
 * \date    2019-05-19
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MEMORYVIEW_HPP__6B85EBD2_7C72_434A_8F47_02AD85158DF8
#define __MEMORYVIEW_HPP__6B85EBD2_7C72_434A_8F47_02AD85158DF8

#include "Type.h"

BEG_XE_NAMESPACE

class MemoryView
{
public:
	MemoryView( std::intptr_t data, uint64 size )
			:_Size(size), _Data(data)
	{
	}
	
public:
	uint64 Size() const
	{
		return _Size;
	}
	
	const std::intptr_t Data() const
	{
		return _Data;
	}

private:
	uint64 _Size;
	const std::intptr_t _Data;
	
};

END_XE_NAMESAPCE

#endif //__MEMORYVIEW_HPP__6B85EBD2_7C72_434A_8F47_02AD85158DF8
