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
	MemoryView()
	:_Size(0), _Data(nullptr)
	{
	}
	
	MemoryView( XE::uint8 * data, XE::uint64 size )
			:_Size(size), _Data(data)
	{
	}
	
public:
	XE::uint64 Size() const
	{
		return _Size;
	}
	
	void * Data() const
	{
		return _Data;
	}

private:
	XE::uint64 _Size;
	XE::uint8 * _Data;
	
};

END_XE_NAMESPACE

#endif //__MEMORYVIEW_HPP__6B85EBD2_7C72_434A_8F47_02AD85158DF8
