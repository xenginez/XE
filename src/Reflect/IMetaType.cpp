#include "IMetaType.h"



XE::IMetaType::IMetaType( const String & Name, MetaType Type, XE::uint64 Size, IMetaInfoPtr Owner, const String & ModuleName /*= "XE" */ )
	:IMetaInfo( Name, Type, Owner, ModuleName ), _Size( Size )
{

}


XE::IMetaType::~IMetaType()
{

}

XE::uint64 XE::IMetaType::GetSize() const
{
	return _Size;
}
