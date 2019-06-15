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

void XE::Reflection::RegisterMetaInfo( IMetaInfoPtr val )
{
	switch ( val->GetType() )
	{
	case MetaType::ENUM:
		This()->_p->Enums.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaEnum>( val ) ) );
		break;
	case MetaType::METHOD:
		This()->_p->Methods.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaMethod>( val ) ) );
		break;
	case MetaType::PROPERTY:
		This()->_p->Propertys.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaProperty>( val ) ) );
		break;
	case MetaType::OPERATOR:
		This()->_p->Operators.insert( std::make_pair( val->GetFullName(), SP_CAST<IMetaOperator>( val ) ) );
		break;
	case MetaType::CLASS:
		if ( IMetaClassPtr cls = SP_CAST<IMetaClass>( val ) )
		{
			This()->_p->Classes.insert( std::make_pair( val->GetFullName(), cls ) );

			cls->VisitMethod( [] ( IMetaMethodPtr method )
			{
				This()->_p->Methods.insert( std::make_pair( method->GetFullName(), method ) );
			} );
			cls->VisitProperty( [] ( IMetaPropertyPtr prop )
			{
				This()->_p->Propertys.insert( std::make_pair( prop->GetFullName(), prop ) );
			} );
			cls->VisitOperator( [] ( IMetaOperatorPtr oper )
			{
				This()->_p->Operators.insert( std::make_pair( oper->GetFullName(), oper ) );
			} );
		}
		break;
	default:
		break;
	}
}

void XE::Reflection::VisitEnum( std::function<void( IMetaEnumPtr )> val )
{
	for ( auto var : This()->_p->Enums )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitClass( std::function<void( IMetaClassPtr )> val )
{
	for ( auto var : This()->_p->Classes )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitMethod( std::function<void( IMetaMethodPtr )> val )
{
	for ( auto var : This()->_p->Methods )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitProperty( std::function<void( IMetaPropertyPtr )> val )
{
	for ( auto var : This()->_p->Propertys )
	{
		val( var.second );
	}
}

void XE::Reflection::VisitOperator( std::function<void( IMetaOperatorPtr )> val )
{
	for ( auto var : This()->_p->Operators )
	{
		val( var.second );
	}
}

XE::IMetaEnumPtr XE::Reflection::FindEnum( const String& FullName )
{
	auto it = This()->_p->Enums.find( FullName );

	if (it != This()->_p->Enums.end())
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaClassPtr XE::Reflection::FindClass( const String& FullName )
{
	auto it = This()->_p->Classes.find( FullName );

	if ( it != This()->_p->Classes.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaPropertyPtr XE::Reflection::FindProperty( const String& FullName )
{
	auto it = This()->_p->Propertys.find( FullName );

	if ( it != This()->_p->Propertys.end() )
	{
		return it->second;
	}

	return nullptr;
}

XE::IMetaOperatorPtr XE::Reflection::FindOperator( const String& FullName, const IMetaInfoPtr& Type /*= nullptr */ )
{
	auto range = This()->_p->Operators.equal_range( FullName );

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
	auto range = This()->_p->Methods.equal_range( FullName );

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
