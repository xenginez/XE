#include "IMetaOperator.h"

#include "IMetaClass.h"



XE::IMetaOperator::IMetaOperator( const String & Name, IMetaInfoPtr Result, IMetaInfoPtr Parameter, IMetaClassPtr Owner, IMetaModulePtr Module )
	:IMetaInfo( Name, MetaType::OPERATOR, SP_CAST<IMetaInfo>( Owner ), Module ), _Result( Result ), _Parameter( Parameter )
{

}

XE::IMetaOperator::~IMetaOperator()
{

}

XE::IMetaInfoPtr XE::IMetaOperator::GetResult() const
{
	return _Result.lock();
}

XE::IMetaInfoPtr XE::IMetaOperator::GetParameter() const
{
	return _Parameter.lock();
}
