/*!
 * \file	GCObject.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GCOBJECT_H__F9C3F87E_6D63_4041_B20A_1853B2AE945A
#define GCOBJECT_H__F9C3F87E_6D63_4041_B20A_1853B2AE945A

#include "Alloc.h"

BEG_XE_NAMESPACE

class XE_API GCObject : public std::enable_shared_from_this< GCObject >
{
public:
	GCObject() = default;

	virtual ~GCObject() = default;

public:
	void * operator new  ( std::size_t count );

	void * operator new[]( std::size_t count );

	void * operator new  ( std::size_t count, std::align_val_t al );

	void * operator new[]( std::size_t count, std::align_val_t al );

	template<typename ...args> void * operator new  ( std::size_t count, args... )
	{
		return Alloc::Allocate( count );
	}

	template<typename ...args> void * operator new[]( std::size_t count, args... )
	{
		return Alloc::Allocate( count );
	}
		
	template<typename ...args> void * operator new  ( std::size_t count, std::align_val_t al, args... )
	{
		return Alloc::Allocate( count );
	}

	template<typename ...args> void * operator new[]( std::size_t count, std::align_val_t al, args... )
	{
		return Alloc::Allocate( count );
	}

public:
	void operator delete  ( void * ptr );

	void operator delete[]( void * ptr );

	void operator delete  ( void * ptr, std::align_val_t al );

	void operator delete[]( void * ptr, std::align_val_t al );

	void operator delete  ( void * ptr, std::size_t sz );

	void operator delete[]( void * ptr, std::size_t sz );

	void operator delete  ( void * ptr, std::size_t sz, std::align_val_t al );

	void operator delete[]( void * ptr, std::size_t sz, std::align_val_t al );

	template<typename ...args> void operator delete  ( void * ptr, args... )
	{
		Alloc::Deallocate( ptr );
	}

	template<typename ...args> void operator delete[]( void * ptr, args... )
	{
		Alloc::Deallocate( ptr );
	}
};

END_XE_NAMESPACE

#endif // GCOBJECT_H__F9C3F87E_6D63_4041_B20A_1853B2AE945A
