#include "IMetaClass.h"

#include "IMetaMethod.h"
#include "IMetaProperty.h"
#include "IMetaOperator.h"

USING_XE

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

void XE::IMetaClass::VisitMethod( std::function<void( IMetaMethodPtr )> val ) const
{
	if (auto super = _Super.lock())
	{
		super->VisitMethod( val );
	}

	for ( auto var : _Methods )
	{
		val( var );
	}
}

void XE::IMetaClass::VisitProperty( std::function<void( IMetaPropertyPtr )> val ) const
{
	if ( auto super = _Super.lock() )
	{
		super->VisitProperty( val );
	}

	for ( auto var : _Propertys )
	{
		val( var );
	}
}

void XE::IMetaClass::VisitOperator( std::function<void( IMetaOperatorPtr )> val ) const
{
	if ( auto super = _Super.lock() )
	{
		super->VisitOperator( val );
	}

	for ( auto var : _Operators )
	{
		val( var );
	}
}

void XE::IMetaClass::VisitDerivedClass( std::function<void( IMetaClassPtr )> val ) const
{
	for ( const auto& var : _DerivedClasses )
	{
		val(std::static_pointer_cast<IMetaClass>(var->shared_from_this()));
	}
}

XE::IMetaMethodPtr XE::IMetaClass::FindMethod( const String& Name, const ParameterType& Types /*= MakeParameterType() */ ) const
{
	for ( auto var : _Methods )
	{
		if (var->GetName() == Name)
		{
			ParameterType VarTypes = var->GetParameter();
			if ( Types.size() == VarTypes.size() && std::equal( Types.begin(), Types.end(), VarTypes.begin(), VarTypes.end() ) )
			{
				return var;
			}
		}
	}

	if (auto super = _Super.lock())
	{
		return super->FindMethod( Name );
	}

	return nullptr;
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

XE::IMetaOperatorPtr XE::IMetaClass::FindOperator( const String& Name, const IMetaInfoPtr& Type /*= nullptr */ ) const
{
	for ( auto var : _Operators )
	{
		if ( var->GetName() == Name && var->GetParameter() == Type )
		{
			return var;
		}
	}

	return nullptr;
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
