#include "Archive.h"

#include "Reflection.h"

#include <pugixml/pugixml.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

USING_XE

struct XE::XmlLoadArchive::Private
{
	pugi::xml_document Doc;
	std::stack< pugi::xml_node * > Nodes;
};

XE::XmlLoadArchive::XmlLoadArchive( std::istream & val )
	:_p( new Private )
{
	if( _p->Doc.load( val ).status == pugi::status_ok )
	{
		_p->Nodes.push( &_p->Doc );
	}
}

XE::XmlLoadArchive::~XmlLoadArchive()
{
	delete _p;
}

void XE::XmlLoadArchive::Serialize( NameValue & val )
{
	std::string name = val.Name == "" ? "item" : val.Name;

	pugi::xml_node node = _p->Nodes.top()->select_node( val.Name.c_str() ).node();
	IMetaInfoPtr type = Reflection::FindMeta( node.attribute( "type" ).value() );
	XE::uint32 flag = node.attribute( "flag" ).as_uint();

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			XE::int64 v = enm->FindValue( node.value() );
			val.Value = Variant( type, { v }, flag );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == Variant::FUNDAMENTAL )
		{
			if( type == MetaID<std::nullptr_t>::Get() )
			{
				val.Value = nullptr;
			}
			else if( type == MetaID<bool>::Get() )
			{
				val.Value = ( std::string( node.value() ) == "true" );
			}
			else if( type == MetaID<XE::int8>::Get() )
			{
				val.Value = std::atoi( node.value() );
			}
			else if( type == MetaID<XE::int16>::Get() )
			{
				val.Value = std::atoi( node.value() );
			}
			else if( type == MetaID<XE::int32>::Get() )
			{
				val.Value = std::atoi( node.value() );
			}
			else if( type == MetaID<XE::int64>::Get() )
			{
				val.Value = std::strtoll( node.value(), nullptr, 10 );
			}
			else if( type == MetaID<XE::uint8>::Get() )
			{
				val.Value = ( XE::uint8 )std::atoi( node.value() );
			}
			else if( type == MetaID<XE::uint16>::Get() )
			{
				val.Value = ( XE::uint16 )std::atoll( node.value() );
			}
			else if( type == MetaID<XE::uint32>::Get() )
			{
				val.Value = std::strtoul( node.value(), nullptr, 10 );
			}
			else if( type == MetaID<XE::uint64>::Get() )
			{
				val.Value = std::strtoull( node.value(), nullptr, 10 );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				val.Value = std::strtof( node.value(), nullptr );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				val.Value = std::strtod( node.value(), nullptr );
			}
		}
		else if( flag == Variant::CONTAINER )
		{
			VariantArray arr;

			XE::uint64 size = node.attribute( "count" ).as_ullong();

			arr.resize( size );

			_p->Nodes.push( &node );
			for( XE::uint64 i = 0; i < size; ++i )
			{
				Variant v;
				( *this ) & NVP( "item_" + std::to_string( i ), v );
				arr[i] = v;
			}
			_p->Nodes.pop();
		}
		else
		{
			if( val.Value.IsNull() )
			{
				if( flag == Variant::POINTER )
				{
					val.Value = Variant( type, cls->Construct(), flag );
				}
				else if( flag == Variant::SHAREDPTR )
				{
					val.Value = Variant( type, cls->ConstructPtr(), flag );
				}

				_p->Nodes.push( &node );
				cls->Serialize( this, val.Value );
				_p->Nodes.pop();
			}
		}
	}
}

struct XE::XmlSaveArchive::Private
{
	pugi::xml_document Doc;
	std::stack< pugi::xml_node * > Nodes;
};

XE::XmlSaveArchive::XmlSaveArchive()
	:_p( new Private )
{
	_p->Nodes.push( &_p->Doc );
}

XE::XmlSaveArchive::~XmlSaveArchive()
{
	delete _p;
}

void XE::XmlSaveArchive::Save( std::ostream & val ) const
{
	_p->Doc.save( val );
}

void XE::XmlSaveArchive::Serialize( NameValue & val )
{
	std::string name = val.Name == "" ? "item" : val.Name;

	IMetaInfoPtr type = val.Value.GetMeta();
	XE::uint32 flag = val.Value.GetFlag();

	pugi::xml_node node = _p->Nodes.top()->child( name.c_str() );
	node.append_attribute( "type" ).set_value( type->GetFullName().ToCString() );
	node.append_attribute( "flag" ).set_value( flag );

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			node.set_value( enm->FindName( val.Value.Value<XE::int64>() ).ToCString() );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == Variant::FUNDAMENTAL )
		{
			if( type == MetaID<std::nullptr_t>::Get() )
			{
				node.set_value( "null" );
			}
			else if( type == MetaID<bool>::Get() )
			{
				node.set_value( val.Value.Value<bool>() ? "true" : "false" );
			}
			else if( type == MetaID<XE::int8>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::int8>() ).c_str() );
			}
			else if( type == MetaID<XE::int16>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::int16>() ).c_str() );
			}
			else if( type == MetaID<XE::int32>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::int32>() ).c_str() );
			}
			else if( type == MetaID<XE::int64>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::int64>() ).c_str() );
			}
			else if( type == MetaID<XE::uint8>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::uint8>() ).c_str() );
			}
			else if( type == MetaID<XE::uint16>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::uint16>() ).c_str() );
			}
			else if( type == MetaID<XE::uint32>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::uint32>() ).c_str() );
			}
			else if( type == MetaID<XE::uint64>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::uint64>() ).c_str() );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::float32>() ).c_str() );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				node.set_value( std::to_string( val.Value.Value<XE::float64>() ).c_str() );
			}
		}
		else if( flag == Variant::CONTAINER )
		{
			VariantArray arr = val.Value.Value<VariantArray>();

			node.append_attribute( "count" ).set_value( arr.size() );

			_p->Nodes.push( &node );
			for( XE::uint64 i = 0; i < arr.size(); ++i )
			{
				( *this ) & NVP( "item_" + std::to_string( i ), arr[i] );
			}
			_p->Nodes.pop();
		}
		else
		{
			_p->Nodes.push( &node );
			cls->Serialize( this, val.Value );
			_p->Nodes.pop();
		}
	}
}

struct XE::JsonLoadArchive::Private
{
	rapidjson::Document Doc;
	std::stack<rapidjson::Value *> Values;
};

XE::JsonLoadArchive::JsonLoadArchive( std::istream & val )
	:_p( new Private )
{
	rapidjson::IStreamWrapper wrapper( val );
	_p->Doc.ParseStream( wrapper );
	_p->Values.push( &_p->Doc );
}

XE::JsonLoadArchive::~JsonLoadArchive()
{
	delete _p;
}

void XE::JsonLoadArchive::Serialize( NameValue & val )
{
	std::string name = val.Name == "" ? "item" : val.Name;

	rapidjson::Value &node = _p->Values.top()->FindMember( name.c_str() )->value;
	IMetaInfoPtr type = Reflection::FindMeta( node.FindMember( "type" )->value.GetString() );
	XE::uint32 flag = node.FindMember( "flag" )->value.GetUint();

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			XE::int64 v = enm->FindValue( node.FindMember( "value" )->value.GetString() );
			val.Value = Variant( type, { v }, flag );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == Variant::FUNDAMENTAL )
		{
			if( type == MetaID<std::nullptr_t>::Get() )
			{
				val.Value = nullptr;
			}
			else if( type == MetaID<bool>::Get() )
			{
				val.Value = ( std::string( node.FindMember( "value" )->value.GetString() ) == "true" );
			}
			else if( type == MetaID<XE::int8>::Get() )
			{
				val.Value = ( XE::int8 )node.FindMember( "value" )->value.GetInt();
			}
			else if( type == MetaID<XE::int16>::Get() )
			{
				val.Value = ( XE::int16 )node.FindMember( "value" )->value.GetInt();
			}
			else if( type == MetaID<XE::int32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetInt();
			}
			else if( type == MetaID<XE::int64>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetInt64();
			}
			else if( type == MetaID<XE::uint8>::Get() )
			{
				val.Value = ( XE::uint8 )node.FindMember( "value" )->value.GetUint();
			}
			else if( type == MetaID<XE::uint16>::Get() )
			{
				val.Value = ( XE::uint16 )node.FindMember( "value" )->value.GetUint();
			}
			else if( type == MetaID<XE::uint32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetUint();
			}
			else if( type == MetaID<XE::uint64>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetUint64();
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetFloat();
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetDouble();
			}
		}
		else if( flag == Variant::CONTAINER )
		{
			VariantArray arr;

			XE::uint64 size = node.FindMember( "count" )->value.GetUint64();

			arr.resize( size );

			_p->Values.push( &node );
			for( XE::uint64 i = 0; i < size; ++i )
			{
				Variant v;
				( *this ) & NVP( "item_" + std::to_string( i ), v );
				arr[i] = v;
			}
			_p->Values.pop();
		}
		else
		{
			if( val.Value.IsNull() )
			{
				if( flag == Variant::POINTER )
				{
					val.Value = Variant( type, cls->Construct(), flag );
				}
				else if( flag == Variant::SHAREDPTR )
				{
					val.Value = Variant( type, cls->ConstructPtr(), flag );
				}

				_p->Values.push( &node );
				cls->Serialize( this, val.Value );
				_p->Values.pop();
			}
		}
	}
}

struct XE::JsonSaveArchive::Private
{
	rapidjson::Document Doc;
	std::stack<rapidjson::Value *> Values;
};

XE::JsonSaveArchive::JsonSaveArchive()
	:_p( new Private )
{
	_p->Values.push( &_p->Doc );
}

XE::JsonSaveArchive::~JsonSaveArchive()
{
	delete _p;
}

void XE::JsonSaveArchive::Save( std::ostream & val ) const
{
	rapidjson::OStreamWrapper wrapper( val );
	rapidjson::Writer<rapidjson::OStreamWrapper> writer( wrapper );
	_p->Doc.Accept( writer );
}

void XE::JsonSaveArchive::Serialize( NameValue & val )
{
	std::string name = val.Name == "" ? "item" : val.Name;

	rapidjson::Value & value = _p->Values.top()->AddMember( rapidjson::StringRef( name.c_str() ), rapidjson::Value( rapidjson::kObjectType ), _p->Doc.GetAllocator() );

	IMetaInfoPtr type = val.Value.GetMeta();
	XE::uint32 flag = val.Value.GetFlag();

	rapidjson::Value v_type( rapidjson::kStringType );
	v_type.SetString( type->GetFullName().ToCString(), _p->Doc.GetAllocator() );
	value.AddMember( rapidjson::StringRef( "type" ), v_type, _p->Doc.GetAllocator() );
	rapidjson::Value v_flag( rapidjson::kStringType );
	v_flag.SetUint( flag );
	value.AddMember( rapidjson::StringRef( "flag" ), v_flag, _p->Doc.GetAllocator() );

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			rapidjson::Value v( rapidjson::kStringType );
			v.SetString( enm->FindName( val.Value.Value<XE::int64>() ).ToCString(), _p->Doc.GetAllocator() );
			value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == Variant::FUNDAMENTAL )
		{
			if( type == MetaID<std::nullptr_t>::Get() )
			{
				rapidjson::Value v( rapidjson::kStringType );
				v.SetString( "null", _p->Doc.GetAllocator() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<bool>::Get() )
			{
				rapidjson::Value v( rapidjson::kStringType );
				v.SetString( val.Value.Value<bool>() ? "true" : "false", _p->Doc.GetAllocator() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::int8>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int8>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::int16>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int16>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::int32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::int64>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt64( val.Value.Value<XE::int64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::uint8>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint8>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::uint16>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint16>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::uint32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::uint64>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint64( val.Value.Value<XE::uint64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetFloat( val.Value.Value<XE::float32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == MetaID<XE::float32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetDouble( val.Value.Value<XE::float64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
		}
		else if( flag == Variant::CONTAINER )
		{
			VariantArray arr = val.Value.Value<VariantArray>();

			rapidjson::Value v( rapidjson::kNumberType );
			v.SetUint64( arr.size() );
			value.AddMember( rapidjson::StringRef( "count" ), v, _p->Doc.GetAllocator() );

			_p->Values.push( &value );
			for( XE::uint64 i = 0; i < arr.size(); ++i )
			{
				( *this ) & NVP( "item_" + std::to_string( i ), arr[i] );
			}
			_p->Values.pop();
		}
		else
		{
			_p->Values.push( &value );
			cls->Serialize( this, val.Value );
			_p->Values.pop();
		}
	}
}
