#include "Zipper.h"

#include <zlib/zlib.h>
#include <zlib/zconf.h>

struct XE::Zipper::Private
{
	bool _IsOpen = false;
	bool _IsFile = false;
	std::iostream * _Stream = nullptr;
	XE::Map< std::string, XE::Zipper::Entry > _Entrics;
};

XE::Zipper::Zipper()
	:_p( new Private )
{

}

XE::Zipper::Zipper( std::iostream & buffer )
	: _p( new Private )
{
	Open( buffer );
}

XE::Zipper::Zipper( const std::string & zipname, const std::string & password /*= "" */ )
	: _p( new Private )
{
	Open( zipname, password );
}

XE::Zipper::~Zipper()
{
	Close();

	delete _p;
}

bool XE::Zipper::Add( std::istream & source, const std::string & name )
{
	return false;
}

XE::Array< XE::Zipper::Entry > XE::Zipper::GetEntries() const
{

}

bool XE::Zipper::ExtractEntiy( const std::string & name )
{
	return false;
}

void XE::Zipper::GetEntryData( const XE::Zipper::Entry & entry, std::ostream & stream )
{

}

void XE::Zipper::GetEntryData( const std::string & entry_name, std::ostream & stream )
{

}

bool XE::Zipper::Open( std::iostream & buffer )
{
	_p->_Stream = &buffer;
	_p->_IsOpen = true;


	return true;
}

bool XE::Zipper::Open( const std::string & zipname, const std::string & password /*= "" */ )
{
	auto f = new std::fstream( zipname, std::ios::in | std::ios::out | std::ios::app | std::ios::binary );
	if( f->is_open() )
	{
		_p->_Stream = f;
		_p->_IsFile = true;
		_p->_IsOpen = true;

		return true;
	}

	delete f;

	return false;
}

bool XE::Zipper::IsOpen() const
{
	return _p->_IsOpen;
}

void XE::Zipper::Flush()
{

}

void XE::Zipper::Close()
{
	Flush();

	if( _p->_Stream && _p->_IsFile )
	{
		delete _p->_Stream;
	}

	_p->_IsFile = false;
	_p->_IsOpen = false;
	_p->_Stream = nullptr;
}
