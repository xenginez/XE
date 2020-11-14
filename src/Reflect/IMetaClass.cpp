#include "IMetaClass.h"

#include "IMetaMethod.h"
#include "IMetaProperty.h"
#include "IMetaOperator.h"



XE::IMetaClass::IMetaClass( const String & Name, XE::uint64 Size, bool IsAbs, bool IsSin, IMetaClassPtr Super, IMetaInfoPtr Owner, const String & ModuleName /*= "XE" */ )
	:IMetaType( Name, MetaType::CLASS, Size, Owner, ModuleName ), _IsAbstract( IsAbs ), _IsSingleton( IsSin ), _Super( Super )
{
	if( Super )
	{
		Super->_DerivedClasses.push_back( this );
	}
}

XE::IMetaClass::~IMetaClass()
{

}

bool XE::IMetaClass::IsAbstract() const
{
	return _IsAbstract;
}

bool XE::IMetaClass::IsSingleton() const
{
	return _IsSingleton;
}

XE::uint64 XE::IMetaClass::GetMethodSize() const
{
	return _Methods.size();
}

XE::uint64 XE::IMetaClass::GetPropertySize() const
{
	return _Propertys.size();
}

XE::uint64 XE::IMetaClass::GetOperatorSize() const
{
	return _Operators.size();
}

XE::uint64 XE::IMetaClass::GetDerivedClassSize() const
{
	return _DerivedClasses.size();
}

bool XE::IMetaClass::CanConvert( const IMetaClassPtr& val ) const
{
	auto cls = SP_CAST<const IMetaClass>( shared_from_this() );

	do 
	{
		if (cls == val)
		{
			return true;
		}

		cls = cls->GetSuper();

	} while ( cls );

	return false;
}

XE::IMetaClassPtr XE::IMetaClass::GetSuper() const
{
	return _Super.lock();
}

void XE::IMetaClass::VisitMethod( const std::function<void( IMetaMethodPtr )> & val ) const
{
	for ( auto var : _Methods )
	{
		val( var );
	}
	if( auto super = _Super.lock() )
	{
		super->VisitMethod( val );
	}
}

void XE::IMetaClass::VisitProperty( const std::function<void( IMetaPropertyPtr )> & val ) const
{
	for ( auto var : _Propertys )
	{
		val( var );
	}
	if( auto super = _Super.lock() )
	{
		super->VisitProperty( val );
	}
}

void XE::IMetaClass::VisitOperator( const std::function<void( IMetaOperatorPtr )> & val ) const
{
	for ( auto var : _Operators )
	{
		val( var );
	}
}

void XE::IMetaClass::VisitDerivedClass( const std::function<void( IMetaClassPtr )> & val ) const
{
	for ( const auto& var : _DerivedClasses )
	{
		val(std::static_pointer_cast<IMetaClass>(var->shared_from_this()));
	}
}

XE::IMetaMethodPtr XE::IMetaClass::FindMethod( const String & Name ) const
{
	for( auto var : _Methods )
	{
		if( var->GetName() == Name )
		{
			return var;
		}
	}

	if( auto super = _Super.lock() )
	{
		return super->FindMethod( Name );
	}

	return nullptr;
}

XE::IMetaMethodPtr XE::IMetaClass::FindMethod( const String& Name, const ParameterType& Types /*= MakeParameterType() */ ) const
{
	return FindMethod( Name + XE::ToString( Types ) );
}

XE::IMetaPropertyPtr XE::IMetaClass::FindProperty( const String& Name ) const
{
	for ( auto var : _Propertys )
	{
		if ( var->GetName() == Name )
		{
			return var;
		}
	}

	if ( auto super = _Super.lock() )
	{
		return super->FindProperty( Name );
	}

	return nullptr;
}

XE::IMetaOperatorPtr XE::IMetaClass::FindOperator( const String & Name ) const
{
	for( auto var : _Operators )
	{
		if( var->GetName() == Name )
		{
			return var;
		}
	}

	if( auto super = _Super.lock() )
	{
		return super->FindOperator( Name );
	}

	return nullptr;
}

XE::IMetaOperatorPtr XE::IMetaClass::FindOperator( const String& Name, const ParameterType & Types ) const
{
	return FindOperator( Name + XE::ToString( Types ) );
}

void XE::IMetaClass::_RegisterMethod( const IMetaMethodPtr& val )
{
	_Methods.push_back( val );
}

void XE::IMetaClass::_RegisterProperty( const IMetaPropertyPtr& val )
{
	_Propertys.push_back( val );
}

void XE::IMetaClass::_RegisterOperator( const IMetaOperatorPtr& val )
{
	_Operators.push_back( val );
}
