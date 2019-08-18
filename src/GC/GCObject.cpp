#include "GCObject.h"

USING_XE

void * XE::GCObject::operator new( std::size_t count )
{
	return Alloc::Allocate( count );
}

void * XE::GCObject::operator new( std::size_t count, std::align_val_t al )
{
	return Alloc::Allocate( count );
}

void * XE::GCObject::operator new[]( std::size_t count )
{
	return Alloc::Allocate( count );
}

void * XE::GCObject::operator new[]( std::size_t count, std::align_val_t al )
{
	return Alloc::Allocate( count );
}

void XE::GCObject::operator delete( void * ptr )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete( void * ptr, std::align_val_t al )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete( void * ptr, std::size_t sz )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete( void * ptr, std::size_t sz, std::align_val_t al )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete[]( void * ptr )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete[]( void * ptr, std::align_val_t al )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete[]( void * ptr, std::size_t sz )
{
	Alloc::Deallocate( ptr );
}

void XE::GCObject::operator delete[]( void * ptr, std::size_t sz, std::align_val_t al )
{
	Alloc::Deallocate( ptr );
}
