#include "IMetaType.h"

USING_XE

XE::IMetaType::IMetaType( const String& Name, MetaType Type, XE::uint64 Size, IMetaInfoPtr Owner )
	:IMetaInfo( Name, Type, Owner ), _Size( Size )
{

}

XE::IMetaType::~IMetaType()
{

}

XE::uint64 XE::IMetaType::GetSize() const
{
	return _Size;
}
