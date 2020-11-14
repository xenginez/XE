#include "IMetaInfo.h"



XE::IMetaInfo::IMetaInfo( const String & Name, MetaType Type, IMetaInfoPtr Owner, const String & ModuleName /*= "XE" */ )
	:_Type( Type ), _Name( Name ), _FullName( Name ), _Owner( Owner ), _ModuleName( ModuleName )
{
	if( auto owner = _Owner.lock() )
	{
		_FullName = owner->GetFullName() + "." + _Name;
	}
	else
	{
		_FullName = ( _ModuleName != "" ? _ModuleName + "." : _ModuleName ) + _Name;
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

const XE::String & XE::IMetaInfo::GetModuleName() const
{
	return _ModuleName;
}
