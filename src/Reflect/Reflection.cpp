#include "Reflection.h"

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
	XE::Map<String, IMetaModulePtr> Modules;
	XE::Map<String, IMetaMethodPtr> Methods;
	XE::Map<String, IMetaPropertyPtr> Propertys;
	XE::Map<String, IMetaOperatorPtr> Operators;
};

XE::Reflection::Reflection()
	:_p( new Private )
{
	_p->Classes.insert( { ::XE_TypeID<std::nullptr_t>::Get()->GetFullName(), ::XE_ClassID<std::nullptr_t>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<bool>::Get()->GetFullName(), ::XE_ClassID<bool>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::int8>::Get()->GetFullName(), ::XE_ClassID<XE::int8>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::int16>::Get()->GetFullName(), ::XE_ClassID<XE::int16>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::int32>::Get()->GetFullName(), ::XE_ClassID<XE::int32>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::int64>::Get()->GetFullName(), ::XE_ClassID<XE::int64>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::uint8>::Get()->GetFullName(), ::XE_ClassID<XE::uint8>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::uint16>::Get()->GetFullName(), ::XE_ClassID<XE::uint16>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::uint32>::Get()->GetFullName(), ::XE_ClassID<XE::uint32>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::uint64>::Get()->GetFullName(), ::XE_ClassID<XE::uint64>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::float32>::Get()->GetFullName(), ::XE_ClassID<XE::float32>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::float64>::Get()->GetFullName(), ::XE_ClassID<XE::float64>::Get() } );

	_p->Classes.insert( { ::XE_TypeID<XE::String>::Get()->GetFullName(), ::XE_ClassID<XE::String>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantList>::Get()->GetFullName(), ::XE_ClassID<XE::VariantList>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantDeque>::Get()->GetFullName(), ::XE_ClassID<XE::VariantDeque>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantStack>::Get()->GetFullName(), ::XE_ClassID<XE::VariantStack>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantQueue>::Get()->GetFullName(), ::XE_ClassID<XE::VariantQueue>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantArray>::Get()->GetFullName(), ::XE_ClassID<XE::VariantArray>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantPair>::Get()->GetFullName(), ::XE_ClassID<XE::VariantPair>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantSet>::Get()->GetFullName(), ::XE_ClassID<XE::VariantSet>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantMap>::Get()->GetFullName(), ::XE_ClassID<XE::VariantMap>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantMultiSet>::Get()->GetFullName(), ::XE_ClassID<XE::VariantMultiSet>::Get() } );
	_p->Classes.insert( { ::XE_TypeID<XE::VariantMultiMap>::Get()->GetFullName(), ::XE_ClassID<XE::VariantMultiMap>::Get() } );
}

XE::Reflection::~Reflection()
{
	delete _p;
}

#define _p XE::Reflection::Instance()->_p

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
	case MetaType::MODULE:
		_p->Modules.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaModule>( val ) ) );
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

	VisitModule( [&]( IMetaModulePtr var )
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

void XE::Reflection::VisitModule( const std::function<void( IMetaModulePtr )> & val )
{
	for( auto var : _p->Modules )
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

XE::IMetaModulePtr XE::Reflection::FindModule( const String & FullName )
{
	auto it = _p->Modules.find( FullName );

	if( it != _p->Modules.end() )
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
