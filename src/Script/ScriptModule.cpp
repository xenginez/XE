#include "ScriptModule.h"

BEG_META( XE::ScriptModule )
END_META()

XE::ScriptModule::ScriptModule()
{

}

XE::ScriptModule::~ScriptModule()
{

}

XE::IMetaModulePtr XE::ScriptModule::GetMetaModule() const
{
	return _MetaModule;
}

XE::ScriptModulePtr XE::ScriptModule::LoadModule( const std::filesystem::path & path )
{
	return nullptr;
}
