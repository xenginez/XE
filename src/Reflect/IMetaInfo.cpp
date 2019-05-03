#include "IMetaInfo.h"

USING_XE

XE::IMetaInfo::IMetaInfo( const String& Name, MetaType Type, IMetaInfoPtr Owner )
	:_Type( Type ), _Name( Name ), _FullName( Name ), _Owner( Owner )
{
	if ( auto owner = _Owner.lock() )
	{
		_FullName = owner->GetFullName() + "::" + _Name;
	}
}

XE::IMetaInfo::~IMetaInfo()
{

}

const XE::MetaType XE::IMetaInfo::GetType() const
{
	return _Type;
}

const XE::String& XE::IMetaInfo::GetName() const
{
	return _Name;
}

const XE::String& XE::IMetaInfo::GetFullName() const
{
	return _FullName;
}

XE::IMetaInfoPtr XE::IMetaInfo::GetOwner() const
{
	return _Owner.lock();
}
