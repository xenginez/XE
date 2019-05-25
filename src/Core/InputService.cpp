#include "InputService.h"

USING_XE

BEG_META( InputService )
END_META()

class XEPInputAction
{
	OBJECT( XEPInputAction )

public:
	String Name;
	Array<KeyCode> Keys;
};
DECL_PTR( XEPInputAction );
BEG_META( XEPInputAction )
type->Property( "Name", &XEPInputAction::Name );
type->Property( "Keys", &XEPInputAction::Keys );
END_META()


struct InputService::Private
{
	Array<IInputControlPtr> _Controls;
	Map<String, XEPInputActionPtr> _Actions;
	UnorderedMap<String, Variant> _ValueMaps;
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
	
	IInputControl::GetMetaClassStatic()->VisitDerivedClass( [&] ( IMetaClassPtr derived )
	{
		if ( !derived->IsAbstract() )
		{
			if ( auto p = derived->ConstructPtr() )
			{
				if ( IInputControlPtr c = SP_CAST<IInputControl>( p ) )
				{
					c->_InputService = XE_THIS( InputService );

					c->Startup();

					_p->_Controls.push_back( c );
				}
			}
		}
	} );

	return true;
}

void XE::InputService::Update()
{
	for ( auto control : _p->_Controls )
	{
		control->Update();
	}
}

void XE::InputService::Clearup()
{
	for ( auto control : _p->_Controls )
	{
		control->Clearup();
	}

	_p->_Controls.clear();
}

XE::int32 XE::InputService::GetPov( const String& val ) const
{
	return GetValue( val ).Value<int32>();
}

XE::int32 XE::InputService::GetPov( KeyCode val ) const
{
	return GetValue( val ).Value<int32>();
}

XE::float32 XE::InputService::GetAxis( const String& val ) const
{
	return GetValue( val ).Value<XE::float32>();
}

XE::float32 XE::InputService::GetAxis( KeyCode val ) const
{
	return GetValue( val ).Value<XE::float32>();
}

XE::int32 XE::InputService::GetButton( const String& val ) const
{
	return GetValue( val ).Value<int32>();
}

XE::int32 XE::InputService::GetButton( KeyCode val ) const
{
	return GetValue( val ).Value<int32>();
}

XE::Variant XE::InputService::GetValue( const String& val ) const
{
	{
		auto it = _p->_ValueMaps.find( val );
		if ( it != _p->_ValueMaps.end() )
		{
			return it->second;
		}
	}

	{
		auto it = _p->_Actions.find( val );
		if ( it != _p->_Actions.end() )
		{
			if ( it->second->Keys.size() == 1 )
			{
				return GetValue( it->second->Keys[0] );
			}
			else
			{
				for ( auto k : it->second->Keys )
				{
					Variant v = GetValue( k );

					if ( v.GetMeta() == MetaID<bool>::Get() && v.Value<bool>() )
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

XE::Variant XE::InputService::GetValue( KeyCode val ) const
{
	auto it = _p->_ValueMaps.find( GetKeycodeString( val ) );

	if ( it != _p->_ValueMaps.end() )
	{
		return it->second;
	}

	return nullptr;
}

void XE::InputService::SetValue( const String& code, const Variant& val )
{
	_p->_ValueMaps[code] = val;
}

XE::String XE::InputService::GetKeycodeString( KeyCode val ) const
{
	return EnumID<KeyCode>::Get()->FindName( (int64)val );
}
