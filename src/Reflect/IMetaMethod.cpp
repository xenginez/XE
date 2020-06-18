#include "IMetaMethod.h"

#include "IMetaClass.h"



XE::IMetaMethod::IMetaMethod( const String & Name, bool IsStatic, bool IsConst, IMetaInfoPtr Result, ParameterType && Parameter, IMetaClassPtr Owner, const String & ModuleName /*= "XE" */ )
	:IMetaInfo( Name, MetaType::METHOD, SP_CAST<IMetaInfo>( Owner ), ModuleName ), _IsStatic( IsStatic ), _IsConst( IsConst ), _Result( Result ), _Parameter( Parameter )
{

}

XE::IMetaMethod::~IMetaMethod()
{

}

bool XE::IMetaMethod::IsConst() const
{
	return _IsConst;
}

bool XE::IMetaMethod::IsStatic() const
{
	return _IsStatic;
}

XE::IMetaInfoPtr XE::IMetaMethod::GetResult() const
{
	return _Result.lock();
}

const XE::ParameterType& XE::IMetaMethod::GetParameter() const
{
	return _Parameter;
}
