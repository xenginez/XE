#include "Archive.h"

#include "Reflection.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>

USING_XE

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

	rapidjson::Value & node = _p->Values.top()->FindMember( name.c_str() )->value;
	auto type = Reflection::FindType( node.FindMember( "type" )->value.GetString() );
	XE::uint32 flag = node.FindMember( "flag" )->value.GetUint();

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			val.Value = enm->FindValue( node.FindMember( "value" )->value.GetString() );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == ( XE::uint32 )Variant::Flag::FUNDAMENTAL )
		{
			if( type == TypeID<std::nullptr_t>::Get() )
			{
				val.Value = nullptr;
			}
			else if( type == TypeID<bool>::Get() )
			{
				val.Value = ( std::string( node.FindMember( "value" )->value.GetString() ) == "true" );
			}
			else if( type == TypeID<XE::int8>::Get() )
			{
				val.Value = ( XE::int8 )node.FindMember( "value" )->value.GetInt();
			}
			else if( type == TypeID<XE::int16>::Get() )
			{
				val.Value = ( XE::int16 )node.FindMember( "value" )->value.GetInt();
			}
			else if( type == TypeID<XE::int32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetInt();
			}
			else if( type == TypeID<XE::int64>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetInt64();
			}
			else if( type == TypeID<XE::uint8>::Get() )
			{
				val.Value = ( XE::uint8 )node.FindMember( "value" )->value.GetUint();
			}
			else if( type == TypeID<XE::uint16>::Get() )
			{
				val.Value = ( XE::uint16 )node.FindMember( "value" )->value.GetUint();
			}
			else if( type == TypeID<XE::uint32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetUint();
			}
			else if( type == TypeID<XE::uint64>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetUint64();
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetFloat();
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				val.Value = node.FindMember( "value" )->value.GetDouble();
			}
		}
		else if( flag == ( XE::uint32 )Variant::Flag::CONTAINER )
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
				if( flag == ( XE::uint32 )Variant::Flag::POINTER )
				{
					val.Value = Variant( type, cls->Construct().Detach(), ( XE::Variant::Flag )flag );
				}
				else if( flag == ( XE::uint32 )Variant::Flag::SHAREDPTR )
				{
					val.Value = Variant( type, cls->ConstructPtr().DetachPtr(), ( XE::Variant::Flag )flag );
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

	auto type = val.Value.GetType();
	XE::uint32 flag = ( XE::uint32 )val.Value.GetFlag();

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
		if( flag == ( XE::uint32 )Variant::Flag::FUNDAMENTAL )
		{
			if( type == TypeID<std::nullptr_t>::Get() )
			{
				rapidjson::Value v( rapidjson::kStringType );
				v.SetString( "null", _p->Doc.GetAllocator() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<bool>::Get() )
			{
				rapidjson::Value v( rapidjson::kStringType );
				v.SetString( val.Value.Value<bool>() ? "true" : "false", _p->Doc.GetAllocator() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::int8>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int8>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::int16>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int16>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::int32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt( val.Value.Value<XE::int32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::int64>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetInt64( val.Value.Value<XE::int64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::uint8>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint8>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::uint16>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint16>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::uint32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint( val.Value.Value<XE::uint32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::uint64>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetUint64( val.Value.Value<XE::uint64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetFloat( val.Value.Value<XE::float32>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				rapidjson::Value v( rapidjson::kNumberType );
				v.SetDouble( val.Value.Value<XE::float64>() );
				value.AddMember( rapidjson::StringRef( "value" ), v, _p->Doc.GetAllocator() );
			}
		}
		else if( flag == ( XE::uint32 )Variant::Flag::CONTAINER )
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

struct XE::BinaryLoadArchive::Private
{
	Private( XE::memory_view & val )
		:Stream( val )
	{
	}

	XE::imemorystream Stream;
};

XE::BinaryLoadArchive::BinaryLoadArchive( XE::memory_view & val )
	:_p( new Private( val ) )
{

}

XE::BinaryLoadArchive::~BinaryLoadArchive()
{
	delete _p;
}

void XE::BinaryLoadArchive::Serialize( NameValue & val )
{
	std::string type_name;
	_p->Stream >> type_name;

	auto type = Reflection::FindType( type_name );
	XE::uint32 flag;
	_p->Stream >> flag;

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			XE::int64 v = 0;
			_p->Stream >> v;
			val.Value = Variant( type, { v }, ( XE::Variant::Flag )flag );
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == ( XE::uint32 )Variant::Flag::FUNDAMENTAL )
		{
			if( type == TypeID<std::nullptr_t>::Get() )
			{
				val.Value = nullptr;
			}
			else if( type == TypeID<bool>::Get() )
			{
				bool v = false;
				_p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::int8>::Get() )
			{
				XE::uint8 v = 0; _p->Stream >> v; val.Value = ( XE::int8 )( v );
			}
			else if( type == TypeID<XE::int16>::Get() )
			{
				XE::int16 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::int32>::Get() )
			{
				XE::int32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::int64>::Get() )
			{
				XE::int64 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::uint8>::Get() )
			{
				XE::uint8 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::uint16>::Get() )
			{
				XE::uint16 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::uint32>::Get() )
			{
				XE::uint32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::uint64>::Get() )
			{
				XE::uint64 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				XE::float32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				XE::float64 v = 0; _p->Stream >> v; val.Value = v;
			}
		}
		else if( flag == ( XE::uint32 )Variant::Flag::CONTAINER )
		{
			VariantArray arr;

			XE::uint64 size = 0;
			_p->Stream >> size;

			arr.resize( size );

			for( XE::uint64 i = 0; i < size; ++i )
			{
				Variant v;
				( *this ) & NVP( nullptr, v );
				arr[i] = v;
			}
		}
		else
		{
			cls->Serialize( this, val.Value );
		}
	}
}

struct XE::BinarySaveArchive::Private
{
	XE::omemorystream Stream;
};

XE::BinarySaveArchive::BinarySaveArchive()
	:_p( new Private )
{

}

XE::BinarySaveArchive::~BinarySaveArchive()
{
	delete _p;
}

void XE::BinarySaveArchive::Save( std::ostream & val ) const
{
	val << _p->Stream.rdbuf();
}

void XE::BinarySaveArchive::Serialize( NameValue & val )
{
	auto type = val.Value.GetType();
	XE::uint32 flag = ( XE::uint32 )val.Value.GetFlag();

	_p->Stream << type->GetFullName().ToStdString() << flag;

	if( type->GetType() == MetaType::ENUM )
	{
		if( auto enm = SP_CAST<IMetaEnum>( type ) )
		{
			_p->Stream << val.Value.Value<XE::int64>();
		}
	}
	else if( auto cls = SP_CAST<IMetaClass>( type ) )
	{
		if( flag == ( XE::uint32 )Variant::Flag::FUNDAMENTAL )
		{
			if( type == TypeID<std::nullptr_t>::Get() )
			{

			}
			else if( type == TypeID<bool>::Get() )
			{
				_p->Stream << val.Value.Value<bool>();
			}
			else if( type == TypeID<XE::int8>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int8>();
			}
			else if( type == TypeID<XE::int16>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int16>();
			}
			else if( type == TypeID<XE::int32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int32>();
			}
			else if( type == TypeID<XE::int64>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int64>();
			}
			else if( type == TypeID<XE::uint8>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint8>();
			}
			else if( type == TypeID<XE::uint16>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint16>();
			}
			else if( type == TypeID<XE::uint32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint32>();
			}
			else if( type == TypeID<XE::uint64>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint64>();
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::float32>();
			}
			else if( type == TypeID<XE::float32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::float64>();
			}
		}
		else if( flag == ( XE::uint32 )Variant::Flag::CONTAINER )
		{
			VariantArray arr = val.Value.Value<VariantArray>();

			_p->Stream << arr.size();

			for( XE::uint64 i = 0; i < arr.size(); ++i )
			{
				( *this ) & NVP( nullptr, arr[i] );
			}
		}
		else
		{
			cls->Serialize( this, val.Value );
		}
	}
}
