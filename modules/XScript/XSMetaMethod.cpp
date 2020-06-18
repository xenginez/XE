#include "XSMetaMethod.h"



XE::XSMetaMethod::XSMetaMethod( const String & Name, IMetaInfoPtr Result, ParameterType && Parameter, IMetaClassPtr Owner, const String & ModuleName )
	:IMetaMethod( Name, false, false, Result, std::move( Parameter ), Owner, ModuleName )
{

}

XE::XSMetaMethod::~XSMetaMethod()
{

}

XE::Variant XE::XSMetaMethod::Invoke( InvokeStack * params ) const
{
	return nullptr;
}
