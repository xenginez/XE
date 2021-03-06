#include "Archive.h"

#include "Reflection.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>



XE::Archive::Archive( ArchiveType val )
	:_Type( val )
{

}

XE::ArchiveType XE::Archive::GetType() const
{
	return _Type;
}

struct XE::JsonLoadArchive::Private
{
	rapidjson::Document Doc;
	std::stack<rapidjson::Value *> Values;
};

XE::JsonLoadArchive::JsonLoadArchive( std::istream & val )
	:Archive( ArchiveType::LOAD ), _p( new Private )
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
	std::string name = val.Name == "" ? "@item" : val.Name;
	if (name == "Handle")
	{
		int i = 0;
	}
	rapidjson::Value & node = _p->Values.top()->FindMember( name.c_str() )->value;

	if( node.IsBool() )
	{
		val.Value = node.GetBool();
	}
	else if( node.IsInt() )
	{
		val.Value = node.GetInt();
	}
	else if( node.IsInt64() )
	{
		val.Value = node.GetInt64();
	}
	else if( node.IsUint() )
	{
		val.Value = node.GetUint();
	}
	else if( node.IsUint64() )
	{
		val.Value = node.GetUint64();
	}
	else if( node.IsFloat() )
	{
		val.Value = node.GetFloat();
	}
	else if( node.IsDouble() )
	{
		val.Value = node.GetDouble();
	}
	else if( node.IsString() )
	{
		val.Value = XE::String( node.GetString() );
	}
	else
	{
		auto type = Reflection::FindType( node.FindMember( "@type" )->value.GetString() );
		XE::uint32 flag = node.FindMember( "@flag" )->value.GetUint();

		if( flag != ( XE::uint32 )XE::Variant::Flag::HANDLE && node.FindMember( "@value" )->value.IsNull() )
		{
			val.Value = XE::Variant( type, XE::Variant::UnionData(), ( XE::Variant::Flag )flag );
		}
		else if( auto enm = DP_CAST<IMetaEnum>( type ) )
		{
			val.Value = enm->FindValue( node.FindMember( "@value" )->value.GetString() );
		}
		else if( auto cls = DP_CAST<IMetaClass>( type ) )
		{
			if( val.Value.IsNull() )
			{
				if( flag == ( XE::uint32 )Variant::Flag::POINTER || flag == ( XE::uint32 )Variant::Flag::PRIVATEPTR || flag == ( XE::uint32 )Variant::Flag::SHAREDPTR )
				{
					val.Value = cls->ConstructPtr();
				}
				else if( flag == ( XE::uint32 )Variant::Flag::HANDLE )
				{
					val.Value = XE::Variant( type, Variant::UnionData( std::numeric_limits<XE::uint64>::max() ), Variant::Flag::HANDLE );
				}
			}

			_p->Values.push( &node );
			cls->Serialize( this, val.Value );
			_p->Values.pop();
		}
	}
}

struct XE::JsonSaveArchive::Private
{
	rapidjson::Document Doc;
	std::stack<rapidjson::Value *> Values;
};

XE::JsonSaveArchive::JsonSaveArchive()
	:Archive( ArchiveType::SAVE ), _p( new Private )
{
	_p->Doc.SetObject();
	_p->Values.push( &_p->Doc );
}

XE::JsonSaveArchive::~JsonSaveArchive()
{
	delete _p;
}

void XE::JsonSaveArchive::Save( std::ostream & val ) const
{
	rapidjson::OStreamWrapper wrapper( val );

	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer( wrapper );

	_p->Doc.Accept( writer );
}

void XE::JsonSaveArchive::Serialize( NameValue & val )
{
	std::string name = val.Name == "" ? "@item" : val.Name;

	if( val.Value.GetType() == ::XE_TypeID<bool>::Get() )
	{
		rapidjson::Value value( rapidjson::kFalseType );
		value.SetBool( val.Value.Value<bool>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::int8>::Get() ||
			 val.Value.GetType() == ::XE_TypeID<XE::int16>::Get() ||
			 val.Value.GetType() == ::XE_TypeID<XE::int32>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetInt( val.Value.Value<XE::int32>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::int64>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetInt64( val.Value.Value<XE::int64>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::uint8>::Get() ||
			 val.Value.GetType() == ::XE_TypeID<XE::uint16>::Get() ||
			 val.Value.GetType() == ::XE_TypeID<XE::uint32>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetUint( val.Value.Value<XE::uint32>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::uint64>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetUint64( val.Value.Value<XE::uint64>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::float32>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetFloat( val.Value.Value<XE::float32>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<XE::float64>::Get() )
	{
		rapidjson::Value value( rapidjson::kNumberType );
		value.SetDouble( val.Value.Value<XE::float64>() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else if( val.Value.GetType() == ::XE_TypeID<String>::Get() )
	{
		rapidjson::Value value( rapidjson::kStringType );
		value.SetString( val.Value.Value<String>().c_str(), _p->Doc.GetAllocator() );
		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
	else
	{
		rapidjson::Value value( rapidjson::kObjectType );

		auto type = val.Value.GetType();
		XE::uint32 flag = ( XE::uint32 )val.Value.GetFlag();

		rapidjson::Value v_type( rapidjson::kStringType );
		v_type.SetString( type->GetFullName().c_str(), _p->Doc.GetAllocator() );
		value.AddMember( rapidjson::StringRef( "@type" ), v_type, _p->Doc.GetAllocator() );
		rapidjson::Value v_flag( rapidjson::kNumberType );
		v_flag.SetUint( flag );
		value.AddMember( rapidjson::StringRef( "@flag" ), v_flag, _p->Doc.GetAllocator() );

		if( val.Value.IsNull() )
		{
			rapidjson::Value v( rapidjson::kStringType );
			v.SetNull();
			value.AddMember( rapidjson::StringRef( "@value" ), v.Move(), _p->Doc.GetAllocator() );
		}
		else if( auto enm = DP_CAST<IMetaEnum>( type ) )
		{
			rapidjson::Value v( rapidjson::kStringType );
			v.SetString( enm->FindName( val.Value ).c_str(), _p->Doc.GetAllocator() );
			value.AddMember( rapidjson::StringRef( "@value" ), v.Move(), _p->Doc.GetAllocator() );
		}
		else if( auto cls = DP_CAST<IMetaClass>( type ) )
		{
			_p->Values.push( &value );
			cls->Serialize( this, val.Value );
			_p->Values.pop();
		}

		_p->Values.top()->AddMember( rapidjson::Value( name.c_str(), _p->Doc.GetAllocator() ).Move(), value, _p->Doc.GetAllocator() );
	}
}

struct XE::BinaryLoadArchive::Private
{
	Private( XE::MemoryView & val )
		:Stream( val )
	{
	}

	XE::IMemoryStream Stream;
};

XE::BinaryLoadArchive::BinaryLoadArchive( XE::MemoryView & val )
	:Archive( ArchiveType::LOAD ), _p( new Private( val ) )
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
			if( type == ::XE_TypeID<std::nullptr_t>::Get() )
			{
				val.Value = nullptr;
			}
			else if( type == ::XE_TypeID<bool>::Get() )
			{
				bool v = false;
				_p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::int8>::Get() )
			{
				XE::int8 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::int16>::Get() )
			{
				XE::int16 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::int32>::Get() )
			{
				XE::int32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::int64>::Get() )
			{
				XE::int64 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::uint8>::Get() )
			{
				XE::uint8 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::uint16>::Get() )
			{
				XE::uint16 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::uint32>::Get() )
			{
				XE::uint32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::uint64>::Get() )
			{
				XE::uint64 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::float32>::Get() )
			{
				XE::float32 v = 0; _p->Stream >> v; val.Value = v;
			}
			else if( type == ::XE_TypeID<XE::float32>::Get() )
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
				auto nvp = NVP( nullptr, v );
				( *this ) & nvp;
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
	XE::OMemoryStream Stream;
};

XE::BinarySaveArchive::BinarySaveArchive()
	:Archive( ArchiveType::SAVE ), _p( new Private )
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

	_p->Stream << type->GetFullName().std_str() << flag;

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
			if( type == ::XE_TypeID<std::nullptr_t>::Get() )
			{

			}
			else if( type == ::XE_TypeID<bool>::Get() )
			{
				_p->Stream << val.Value.Value<bool>();
			}
			else if( type == ::XE_TypeID<XE::int8>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int8>();
			}
			else if( type == ::XE_TypeID<XE::int16>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int16>();
			}
			else if( type == ::XE_TypeID<XE::int32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int32>();
			}
			else if( type == ::XE_TypeID<XE::int64>::Get() )
			{
				_p->Stream << val.Value.Value<XE::int64>();
			}
			else if( type == ::XE_TypeID<XE::uint8>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint8>();
			}
			else if( type == ::XE_TypeID<XE::uint16>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint16>();
			}
			else if( type == ::XE_TypeID<XE::uint32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint32>();
			}
			else if( type == ::XE_TypeID<XE::uint64>::Get() )
			{
				_p->Stream << val.Value.Value<XE::uint64>();
			}
			else if( type == ::XE_TypeID<XE::float32>::Get() )
			{
				_p->Stream << val.Value.Value<XE::float32>();
			}
			else if( type == ::XE_TypeID<XE::float32>::Get() )
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
