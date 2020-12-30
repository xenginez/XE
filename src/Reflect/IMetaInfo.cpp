#include "IMetaInfo.h"

#include "IMetaModule.h"

XE::IMetaInfo::IMetaInfo( const String & Name, MetaType Type, IMetaInfoPtr Owner, IMetaModulePtr Module )
	:_Type( Type ), _Name( Name ), _FullName( Name ), _Owner( Owner ), _Module( Module )
{
	if( Owner )
	{
		_FullName = Owner->GetFullName() + "." + _Name;
	}
	else if( Module )
	{
		_FullName = Module->GetFullName() + "." + _Name;
	}
	else
	{
		_FullName = _Name;
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

XE::IMetaModulePtr XE::IMetaInfo::GetModule() const
{
	return _Module.lock();
}
