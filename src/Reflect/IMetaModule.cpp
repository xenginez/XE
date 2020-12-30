#include "IMetaModule.h"

#include "Reflection.h"

XE::IMetaModule::IMetaModule( const String & Name, IMetaInfoPtr Owner )
	:IMetaInfo( Name, MetaType::MODULE, Owner, nullptr )
{

}

XE::IMetaModule::~IMetaModule()
{

}

XE::IMetaInfoPtr XE::IMetaModule::FindMetaInfo( const String & val ) const
{
	for( const auto & it : _MetaInfos )
	{
		if( it->GetName() == val )
		{
			return it;
		}
		else if( it->GetFullName() == val )
		{
			return it;
		}
	}

	return nullptr;
}

void XE::IMetaModule::Visit( const std::function<void( XE::IMetaInfoPtr )> & val ) const
{
	for( const auto & it : _MetaInfos )
	{
		val( it );
	}
}

XE::IMetaModulePtr GetModule()
{
	return nullptr;
}

IMPLEMENT_META_MODULE( XE );
