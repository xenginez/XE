#include "Exception.h"

USING_XE

XE::Exception::Exception()
{

}

XE::Exception::~Exception()
{

}

const char * XE::Exception::What() const
{
	return "Unknown Exception";
}

XE::RuntimeException::RuntimeException()
{

}

XE::RuntimeException::~RuntimeException()
{

}

const char * XE::RuntimeException::What() const
{
	return "Unknown RuntimeException";
}
