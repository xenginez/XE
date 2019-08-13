#include "Resource.h"

USING_XE

BEG_META(Resource)
END_META()

XE::Resource::Resource()
{

}

XE::Resource::~Resource()
{

}

XE::ResourceHandle XE::Resource::GetHandle() const
{
	return _Handle;
}
