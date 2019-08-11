#include "XSMetaOperator.h"

USING_XE

XE::XSMetaOperator::XSMetaOperator( const String & Name, IMetaInfoPtr Result, IMetaInfoPtr Parameter, IMetaClassPtr Owner, const String & ModuleName )
	:IMetaOperator( Name, Result, std::move( Parameter ), Owner, ModuleName )
{

}

XE::XSMetaOperator::~XSMetaOperator()
{

}

XE::Variant XE::XSMetaOperator::Invoke( InvokeStack * params ) const
{
	return nullptr;
}
