#include "Reflection.h"

USING_XE

template<> struct XE::MetaDataCollector<Reflection>
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
	std::map<String, IMetaEnumPtr> Enums;
	std::map<String, IMetaClassPtr> Classes;
	std::map<String, IMetaMethodPtr> Methods;
	std::multimap<String, IMetaPropertyPtr> Propertys;
	std::multimap<String, IMetaOperatorPtr> Operators;
};

XE::Reflection::Reflection()
	:_p(new Private)
{
	_p->Classes.insert( std::make_pair( "void", nullptr ) );

	_p->Classes.insert( { MetaID<std::nullptr_t>::Get()->GetFullName(), ClassID<std::nullptr_t>::Get() } );
	_p->Classes.insert( { MetaID<bool>::Get()->GetFullName(), ClassID<bool>::Get() } );
	_p->Classes.insert( { MetaID<XE::int8>::Get()->GetFullName(), ClassID<XE::int8>::Get() } );
	_p->Classes.insert( { MetaID<XE::int16>::Get()->GetFullName(), ClassID<XE::int16>::Get() } );
	_p->Classes.insert( { MetaID<XE::int32>::Get()->GetFullName(), ClassID<XE::int32>::Get() } );
	_p->Classes.insert( { MetaID<XE::int64>::Get()->GetFullName(), ClassID<XE::int64>::Get() } );
	_p->Classes.insert( { MetaID<XE::uint8>::Get()->GetFullName(), ClassID<XE::uint8>::Get() } );
	_p->Classes.insert( { MetaID<XE::uint16>::Get()->GetFullName(), ClassID<XE::uint16>::Get() } );
	_p->Classes.insert( { MetaID<XE::uint32>::Get()->GetFullName(), ClassID<XE::uint32>::Get() } );
	_p->Classes.insert( { MetaID<XE::uint64>::Get()->GetFullName(), ClassID<XE::uint64>::Get() } );
	_p->Classes.insert( { MetaID<XE::float32>::Get()->GetFullName(), ClassID<XE::float32>::Get() } );
	_p->Classes.insert( { MetaID<XE::float64>::Get()->GetFullName(), ClassID<XE::float64>::Get() } );

	_p->Classes.insert( { MetaID<XE::String>::Get()->GetFullName(), ClassID<XE::String>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantList>::Get()->GetFullName(), ClassID<XE::VariantList>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantDeque>::Get()->GetFullName(), ClassID<XE::VariantDeque>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantStack>::Get()->GetFullName(), ClassID<XE::VariantStack>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantQueue>::Get()->GetFullName(), ClassID<XE::VariantQueue>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantArray>::Get()->GetFullName(), ClassID<XE::VariantArray>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantPair>::Get()->GetFullName(), ClassID<XE::VariantPair>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantSet>::Get()->GetFullName(), ClassID<XE::VariantSet>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantMap>::Get()->GetFullName(), ClassID<XE::VariantMap>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantMultiSet>::Get()->GetFullName(), ClassID<XE::VariantMultiSet>::Get() } );
	_p->Classes.insert( { MetaID<XE::VariantMultiMap>::Get()->GetFullName(), ClassID<XE::VariantMultiMap>::Get() } );
}

XE::Reflection::~Reflection()
{
	delete _p;
}

void Reflection::Clear()
{
	if( Instance()->_p )
	{
		Instance()->_p->Enums.clear();
		Instance()->_p->Methods.clear();
		Instance()->_p->Propertys.clear();
		Instance()->_p->Operators.clear();
		Instance()->_p->Classes.clear();
	}
}

void XE::Reflection::RegisterMetaInfo( IMetaInfoPtr val )
{
	switch ( val->GetType() )
	{
	case MetaType::ENUM:
		Instance()->_p->Enums.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaEnum>( val ) ) );
		break;
	case MetaType::METHOD:
		Instance()->_p->Methods.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaMethod>( val ) ) );
		break;
	case MetaType::PROPERTY:
		Instance()->_p->Propertys.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaProperty>( val ) ) );
		break;
	case MetaType::OPERATOR:
		Instance()->_p->Operators.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaOperator>( val ) ) );
		break;
	case MetaType::CLASS:
		if ( IMetaClassPtr cls = SP_CAST<IMetaClass>( val ) )
		{
			Instance()->_p->Classes.insert( std::make_pair( val->GetFullName(), cls ) );

			cls->VisitMethod( [] ( IMetaMethodPtr method )
			{
				Instance()->_p->Methods.insert( std::make_pair( method->GetFullName(), method ) );
			} );
			cls->VisitProperty( [] ( IMetaPropertyPtr prop )
			{
				Instance()->_p->Propertys.insert( std::make_pair( prop->GetFullName(), prop ) );
			} );
			cls->VisitOperator( [] ( IMetaOperatorPtr oper )
			{
				Instance()->_p->Operators.insert( std::make_pair( oper->GetFullName(), oper ) );
			} );
		}
		break;
	default:
		break;
	}
}

void XE::Reflection::VisitMeta( std::function<void( IMetaInfoPtr )> val )
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

void XE::Reflection::VisitEnum( std::function<void( IMetaEnumPtr )> val )
{
	for ( auto var : Instance()->_p->Enums )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitClass( std::function<void( IMetaClassPtr )> val )
{
	for ( auto var : Instance()->_p->Classes )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitMethod( std::function<void( IMetaMethodPtr )> val )
{
	for ( auto var : Instance()->_p->Methods )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitProperty( std::function<void( IMetaPropertyPtr )> val )
{
	for ( auto var : Instance()->_p->Propertys )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitOperator( std::function<void( IMetaOperatorPtr )> val )
{
	for ( auto var : Instance()->_p->Operators )
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

	return nullptr;
}

XE::IMetaEnumPtr XE::Reflection::FindEnum( const String& FullName )
{
	auto it = Instance()->_p->Enums.find( FullName );

	if (it != Instance()->_p->Enums.end())
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaClassPtr XE::Reflection::FindClass( const String& FullName )
{
	auto it = Instance()->_p->Classes.find( FullName );

	if ( it != Instance()->_p->Classes.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaPropertyPtr XE::Reflection::FindProperty( const String& FullName )
{
	auto it = Instance()->_p->Propertys.find( FullName );

	if ( it != Instance()->_p->Propertys.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaOperatorPtr XE::Reflection::FindOperator( const String& FullName, const IMetaInfoPtr& Type /*= nullptr */ )
{
	auto range = Instance()->_p->Operators.equal_range( FullName );

	for (; range.first != range.second; ++range.first)
	{
		if (range.first->second->GetParameter() == Type)
		{
			return range.first->second;
		}
	}

	return nullptr;
}

XE::IMetaMethodPtr XE::Reflection::FindMethod( const String& FullName, const ParameterType& Types /*= MakeParameterType() */ )
{
	auto range = Instance()->_p->Methods.equal_range( FullName );

	for ( ; range.first != range.second; ++range.first )
	{
		ParameterType itTypes = range.first->second->GetParameter();
		if ( itTypes.size() == Types.size() && std::equal( itTypes.begin(), itTypes.end(), Types.begin(), Types.end() ) )
		{
			return range.first->second;
		}
	}

	return nullptr;
}
