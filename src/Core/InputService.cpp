#include "InputService.h"



BEG_META( XE::InputService )
END_META()

class XEPAction
{
	OBJECT( XEPAction )

public:
	XE::KeyCode Code = XE::KeyCode::None;
	XE::Operation Operator = XE::Operation::EQUAL;
	XE::Variant Operand;
};
BEG_META( XEPAction )
type->Property( "Code", &XEPAction::Code );
type->Property( "Operator", &XEPAction::Operand );
type->Property( "Operator", &XEPAction::Operator );
END_META()

class XEPInputAction
{
	OBJECT( XEPInputAction )

public:
	XE::String Name;
	XE::Array<XEPAction> Keys;
};
BEG_META( XEPInputAction )
type->Property( "Name", &XEPInputAction::Name );
type->Property( "Keys", &XEPInputAction::Keys );
END_META()


struct XE::InputService::Private
{
	XE::Array<XE::IInputControlPtr> _Controls;
	XE::Map<XE::String, XEPInputAction> _Actions;
	XE::UnorderedMap<XE::String, XE::Variant> _ValueMaps;
};

XE::InputService::InputService()
	:_p( new Private )
{

}

XE::InputService::~InputService()
{
	delete _p;
}

bool XE::InputService::Startup()
{
	// TODO: InputAction Serialization

	IInputControl::GetMetaClassStatic()->VisitDerivedClass( [&]( IMetaClassPtr derived )
		{
			if( !derived->IsAbstract() )
			{
				if( IInputControlPtr c = derived->ConstructPtr().Value< IInputControlPtr >() )
				{
					c->_InputService = XE_THIS( InputService );

					c->Startup();

					_p->_Controls.push_back( c );
				}
			}
		} );

	return true;
}

void XE::InputService::Update()
{
	for( auto control : _p->_Controls )
	{
		control->Update();
	}
}

void XE::InputService::Clearup()
{
	for( auto control : _p->_Controls )
	{
		control->Clearup();
	}

	_p->_Controls.clear();
}

XE::int32 XE::InputService::GetPov( const XE::String& val ) const
{
	return GetValue( val ).Value<XE::int32>();
}

XE::int32 XE::InputService::GetPov( XE::KeyCode val ) const
{
	return GetValue( val ).Value<XE::int32>();
}

XE::float32 XE::InputService::GetAxis( const XE::String& val ) const
{
	return GetValue( val ).Value<XE::float32>();
}

XE::float32 XE::InputService::GetAxis( XE::KeyCode val ) const
{
	return GetValue( val ).Value<XE::float32>();
}

XE::int32 XE::InputService::GetButton( const XE::String& val ) const
{
	return GetValue( val ).Value<XE::int32>();
}

XE::int32 XE::InputService::GetButton( XE::KeyCode val ) const
{
	return GetValue( val ).Value<XE::int32>();
}

XE::Variant XE::InputService::GetValue( const XE::String& val ) const
{
	{
		auto it = _p->_ValueMaps.find( val );
		if( it != _p->_ValueMaps.end() )
		{
			return it->second;
		}
	}

	{
		auto it = _p->_Actions.find( val );
		if( it != _p->_Actions.end() )
		{
			if( it->second.Keys.size() == 1 )
			{
				return GetValue( it->second.Keys[0].Code );
			}
			else
			{
				for( auto k : it->second.Keys )
				{
					Variant v = GetValue( k.Code );

					bool pass = false;
					switch( k.Operator )
					{
					case Operation::EQUAL:
						pass = CallEQUAL( v, k.Operand );
						break;
					case Operation::NOT_EQUAL:
						pass = CallNOT_EQUAL( v, k.Operand );
						break;
					case Operation::LESS:
						pass = CallLESS( v, k.Operand );
						break;
					case Operation::GREATER:
						pass = CallGREATER( v, k.Operand );
						break;
					case Operation::LESS_EQUAL:
						pass = CallLESS_EQUAL( v, k.Operand );
						break;
					case Operation::GREATER_EQUAL:
						pass = CallGREATER_EQUAL( v, k.Operand );
						break;
					}

					if( pass )
					{
						continue;
					}

					return false;
				}

				return true;
			}
		}
	}

	return nullptr;
}

XE::Variant XE::InputService::GetValue( XE::KeyCode val ) const
{
	auto it = _p->_ValueMaps.find( GetKeycodeString( val ) );

	if( it != _p->_ValueMaps.end() )
	{
		return it->second;
	}

	return nullptr;
}

void XE::InputService::SetValue( const XE::String& code, const XE::Variant& val )
{
	_p->_ValueMaps[code] = val;
}

XE::String XE::InputService::GetKeycodeString( XE::KeyCode val ) const
{
	return EnumID<KeyCode>::Get()->FindName( ( XE::int64 )val );
}

void XE::InputService::Prepare()
{

}

bool XE::InputService::CallEQUAL( const XE::Variant& a, const XE::Variant& b ) const
{
	return( 
		( a.GetType() == TypeID<bool>::Get() && a.Value<bool>() == b.Value<bool>() ) ||
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() == b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() == b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() == b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() == b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() == b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() == b.Value<XE::float64>() ) );
}

bool XE::InputService::CallNOT_EQUAL( const XE::Variant& a, const XE::Variant& b ) const
{
	return(
		( a.GetType() == TypeID<bool>::Get() && a.Value<bool>() != b.Value<bool>() ) ||
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() != b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() != b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() != b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() != b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() != b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() != b.Value<XE::float64>() ) );
}

bool XE::InputService::CallLESS( const XE::Variant& a, const XE::Variant& b ) const
{
	return(
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() < b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() < b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() < b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() < b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() < b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() < b.Value<XE::float64>() ) );
}

bool XE::InputService::CallGREATER( const XE::Variant& a, const XE::Variant& b ) const
{
	return(
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() > b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() > b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() > b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() > b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() > b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() > b.Value<XE::float64>() ) );
}

bool XE::InputService::CallLESS_EQUAL( const XE::Variant& a, const XE::Variant& b ) const
{
	return(
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() <= b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() <= b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() <= b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() <= b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() <= b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() <= b.Value<XE::float64>() ) );
}

bool XE::InputService::CallGREATER_EQUAL( const XE::Variant& a, const XE::Variant& b ) const
{
	return(
		( a.GetType() == TypeID<XE::int32>::Get() && a.Value<XE::int32>() >= b.Value<XE::int32>() ) ||
		( a.GetType() == TypeID<XE::int64>::Get() && a.Value<XE::int64>() >= b.Value<XE::int64>() ) ||
		( a.GetType() == TypeID<XE::uint32>::Get() && a.Value<XE::uint32>() >= b.Value<XE::uint32>() ) ||
		( a.GetType() == TypeID<XE::uint64>::Get() && a.Value<XE::uint64>() >= b.Value<XE::uint64>() ) ||
		( a.GetType() == TypeID<XE::float32>::Get() && a.Value<XE::float32>() >= b.Value<XE::float32>() ) ||
		( a.GetType() == TypeID<XE::float64>::Get() && a.Value<XE::float64>() >= b.Value<XE::float64>() ) );
}
