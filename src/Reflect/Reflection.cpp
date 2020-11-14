#include "Reflection.h"

#define _p XE::Reflection::Instance()->_p

template<> struct XE::MetaDataCollector<XE::Reflection>
{
	MetaDataCollector()
	{
		{
			auto type = Reflection::Class<String>::Get();
		}
		{
			auto type = Reflection::Class<VariantList>::Get();
		}
		{
			auto type = Reflection::Class<VariantDeque>::Get();
		}
		{
			auto type = Reflection::Class<VariantStack>::Get();
		}
		{
			auto type = Reflection::Class<VariantQueue>::Get();
		}
		{
			auto type = Reflection::Class<VariantArray>::Get();
		}
		{
			auto type = Reflection::Class<VariantPair>::Get();
		}
		{
			auto type = Reflection::Class<VariantSet>::Get();
		}
		{
			auto type = Reflection::Class<VariantMap>::Get();
		}
		{
			auto type = Reflection::Class<VariantMultiSet>::Get();
		}
		{
			auto type = Reflection::Class<VariantMultiMap>::Get();
		}
	}
	static void Use()
	{
		ActiveSingleton< MetaDataCollector<Reflection> >::Register();
	}
};

struct XE::Reflection::Private
{
	XE::Map<String, IMetaEnumPtr> Enums;
	XE::Map<String, IMetaClassPtr> Classes;
	XE::Map<String, IMetaMethodPtr> Methods;
	XE::Map<String, IMetaPropertyPtr> Propertys;
	XE::Map<String, IMetaOperatorPtr> Operators;
};

XE::Reflection::Reflection()
	:_p( new Private )
{
	_p->Classes.insert( { TypeID<std::nullptr_t>::Get()->GetFullName(), ClassID<std::nullptr_t>::Get() } );
	_p->Classes.insert( { TypeID<bool>::Get()->GetFullName(), ClassID<bool>::Get() } );
	_p->Classes.insert( { TypeID<XE::int8>::Get()->GetFullName(), ClassID<XE::int8>::Get() } );
	_p->Classes.insert( { TypeID<XE::int16>::Get()->GetFullName(), ClassID<XE::int16>::Get() } );
	_p->Classes.insert( { TypeID<XE::int32>::Get()->GetFullName(), ClassID<XE::int32>::Get() } );
	_p->Classes.insert( { TypeID<XE::int64>::Get()->GetFullName(), ClassID<XE::int64>::Get() } );
	_p->Classes.insert( { TypeID<XE::uint8>::Get()->GetFullName(), ClassID<XE::uint8>::Get() } );
	_p->Classes.insert( { TypeID<XE::uint16>::Get()->GetFullName(), ClassID<XE::uint16>::Get() } );
	_p->Classes.insert( { TypeID<XE::uint32>::Get()->GetFullName(), ClassID<XE::uint32>::Get() } );
	_p->Classes.insert( { TypeID<XE::uint64>::Get()->GetFullName(), ClassID<XE::uint64>::Get() } );
	_p->Classes.insert( { TypeID<XE::float32>::Get()->GetFullName(), ClassID<XE::float32>::Get() } );
	_p->Classes.insert( { TypeID<XE::float64>::Get()->GetFullName(), ClassID<XE::float64>::Get() } );

	_p->Classes.insert( { TypeID<XE::String>::Get()->GetFullName(), ClassID<XE::String>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantList>::Get()->GetFullName(), ClassID<XE::VariantList>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantDeque>::Get()->GetFullName(), ClassID<XE::VariantDeque>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantStack>::Get()->GetFullName(), ClassID<XE::VariantStack>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantQueue>::Get()->GetFullName(), ClassID<XE::VariantQueue>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantArray>::Get()->GetFullName(), ClassID<XE::VariantArray>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantPair>::Get()->GetFullName(), ClassID<XE::VariantPair>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantSet>::Get()->GetFullName(), ClassID<XE::VariantSet>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantMap>::Get()->GetFullName(), ClassID<XE::VariantMap>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantMultiSet>::Get()->GetFullName(), ClassID<XE::VariantMultiSet>::Get() } );
	_p->Classes.insert( { TypeID<XE::VariantMultiMap>::Get()->GetFullName(), ClassID<XE::VariantMultiMap>::Get() } );
}

XE::Reflection::~Reflection()
{
	delete _p;
}

void XE::Reflection::Clear()
{
	if( _p )
	{
		_p->Enums.clear();
		_p->Methods.clear();
		_p->Propertys.clear();
		_p->Operators.clear();
		_p->Classes.clear();
	}
}

void XE::Reflection::RegisterMetaInfo( IMetaInfoPtr val )
{
	switch( val->GetType() )
	{
	case MetaType::ENUM:
		_p->Enums.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaEnum>( val ) ) );
		break;
	case MetaType::METHOD:
		_p->Methods.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaMethod>( val ) ) );
		break;
	case MetaType::PROPERTY:
		_p->Propertys.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaProperty>( val ) ) );
		break;
	case MetaType::OPERATOR:
		_p->Operators.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaOperator>( val ) ) );
		break;
	case MetaType::CLASS:
		if( IMetaClassPtr cls = SP_CAST<IMetaClass>( val ) )
		{
			_p->Classes.insert( std::make_pair( val->GetFullName(), cls ) );

			cls->VisitMethod( []( IMetaMethodPtr method )
							  {
								  _p->Methods.insert( std::make_pair( method->GetFullName(), method ) );
							  } );
			cls->VisitProperty( []( IMetaPropertyPtr prop )
								{
									_p->Propertys.insert( std::make_pair( prop->GetFullName(), prop ) );
								} );
			cls->VisitOperator( []( IMetaOperatorPtr oper )
								{
									_p->Operators.insert( std::make_pair( oper->GetFullName(), oper ) );
								} );
		}
		break;
	default:
		break;
	}
}

void XE::Reflection::VisitMeta( const std::function<void( IMetaInfoPtr )> & val )
{
	VisitEnum( [&]( IMetaEnumPtr var )
			   {
				   val( var );
			   } );

	VisitClass( [&]( IMetaClassPtr var )
				{
					val( var );
				} );

	VisitMethod( [&]( IMetaMethodPtr var )
				 {
					 val( var );
				 } );

	VisitProperty( [&]( IMetaPropertyPtr var )
				   {
					   val( var );
				   } );

	VisitOperator( [&]( IMetaOperatorPtr var )
				   {
					   val( var );
				   } );
}

void XE::Reflection::VisitType( const std::function<void( IMetaTypePtr )> & val )
{
	VisitEnum( [&]( IMetaEnumPtr enm )
			   {
				   val( enm );
			   } );

	VisitClass( [&]( IMetaClassPtr cls )
				{
					val( cls );
				} );
}

void XE::Reflection::VisitEnum( const std::function<void( IMetaEnumPtr )> & val )
{
	for( auto var : _p->Enums )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitClass( const std::function<void( IMetaClassPtr )> & val )
{
	for( auto var : _p->Classes )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitMethod( const std::function<void( IMetaMethodPtr )> & val )
{
	for( auto var : _p->Methods )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitProperty( const std::function<void( IMetaPropertyPtr )> & val )
{
	for( auto var : _p->Propertys )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitOperator( const std::function<void( IMetaOperatorPtr )> & val )
{
	for( auto var : _p->Operators )
	{
		val( var.second );
	}
}

XE::IMetaInfoPtr XE::Reflection::FindMeta( const String & FullName )
{
	if( auto ret = FindEnum( FullName ) )
	{
		return ret;
	}

	if( auto ret = FindClass( FullName ) )
	{
		return ret;
	}

	if( auto ret = FindProperty( FullName ) )
	{
		return ret;
	}

	if( auto ret = FindOperator( FullName ) )
	{
		return ret;
	}

	if( auto ret = FindMethod( FullName ) )
	{
		return ret;
	}

	return nullptr;
}

XE::IMetaTypePtr XE::Reflection::FindType( const String & FullName )
{
	if( auto ret = FindEnum( FullName ) )
	{
		return ret;
	}

	if( auto ret = FindClass( FullName ) )
	{
		return ret;
	}

	return nullptr;
}

XE::IMetaEnumPtr XE::Reflection::FindEnum( const String & FullName )
{
	auto it = _p->Enums.find( FullName );

	if( it != _p->Enums.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaClassPtr XE::Reflection::FindClass( const String & FullName )
{
	auto it = _p->Classes.find( FullName );

	if( it != _p->Classes.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaMethodPtr XE::Reflection::FindMethod( const String & FullName )
{
	auto it = _p->Methods.find( FullName );

	if( it != _p->Methods.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaPropertyPtr XE::Reflection::FindProperty( const String & FullName )
{
	auto it = _p->Propertys.find( FullName );

	if( it != _p->Propertys.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaOperatorPtr XE::Reflection::FindOperator( const String & FullName )
{
	auto it = _p->Operators.find( FullName );

	if( it != _p->Operators.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaMethodPtr XE::Reflection::FindMethod( const String & FullName, const ParameterType & Types )
{
	return FindMethod( FullName + XE::ToString( Types ) );
}

XE::IMetaOperatorPtr XE::Reflection::FindOperator( const String & FullName, const ParameterType & Types )
{
	return FindOperator( FullName + XE::ToString( Types ) );
}
