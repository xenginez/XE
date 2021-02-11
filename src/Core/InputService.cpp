#include "InputService.h"

BEG_META( XE::InputService )
END_META()

struct XE::InputService::Private
{
	bool _ResetInput = false;
	XE::Array< XE::IInputControlPtr > _Controls;
	XE::UnorderedMap< XE::String, XE::Variant > _ValueMaps;
	XE::Map< XE::KeyCode, XE::Array< ButtonChangedCallbackType > > _ButtonPressedCallbacks;
	XE::Map< XE::KeyCode, XE::Array< ButtonChangedCallbackType > > _ButtonReleaseCallbacks;
};

XE::InputService::InputService()
	:_p( new Private )
{

}

XE::InputService::~InputService()
{
	delete _p;
}

void XE::InputService::Prepare()
{

}

bool XE::InputService::Startup()
{
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

	_p->_ResetInput = false;
}

void XE::InputService::Clearup()
{
	for( auto control : _p->_Controls )
	{
		control->Clearup();
	}

	_p->_Controls.clear();
}

void XE::InputService::ResetInputValues()
{
	_p->_ResetInput = true;
	_p->_ValueMaps.clear();
}

XE::Follow XE::InputService::RegisterButtonPressed( XE::KeyCode key, const ButtonChangedCallbackType & callback )
{
	if( key < KeyCode::Backspace || key > KeyCode::MouseWheel )
	{
		return {};
	}

	auto & callbacks = _p->_ButtonPressedCallbacks[key];
	for( size_t i = 0; i < callbacks.size(); i++ )
	{
		if( callbacks[i] == nullptr )
		{
			callbacks[i] = callback;

			return [this, key, i]()
			{
				auto & callbacks = _p->_ButtonPressedCallbacks[key];

				if( callbacks.size() > i )
				{
					callbacks[i] = nullptr;
				}
			};
		}
	}

	auto i = callbacks.size();
	callbacks.push_back( callback );

	return [this, key, i]()
	{
		auto & callbacks = _p->_ButtonPressedCallbacks[key];

		if( callbacks.size() > i )
		{
			callbacks[i] = nullptr;
		}
	};
}

XE::Follow XE::InputService::RegisterButtonRelease( XE::KeyCode key, const ButtonChangedCallbackType & callback )
{
	if( key < KeyCode::Backspace || key > KeyCode::MouseWheel )
	{
		return {};
	}

	auto & callbacks = _p->_ButtonReleaseCallbacks[key];
	for( size_t i = 0; i < callbacks.size(); i++ )
	{
		if( callbacks[i] == nullptr )
		{
			callbacks[i] = callback;

			return [this, key, i]()
			{
				auto & callbacks = _p->_ButtonReleaseCallbacks[key];

				if( callbacks.size() > i )
				{
					callbacks[i] = nullptr;
				}
			};
		}
	}

	auto i = callbacks.size();
	callbacks.push_back( callback );

	return [this, key, i]()
	{
		auto & callbacks = _p->_ButtonReleaseCallbacks[key];

		if( callbacks.size() > i )
		{
			callbacks[i] = nullptr;
		}
	};
}

XE::Variant XE::InputService::GetValue( const XE::String& val ) const
{
	auto it = _p->_ValueMaps.find( val );
	if( it != _p->_ValueMaps.end() )
	{
		return it->second;
	}

	return {};
}

void XE::InputService::SetValue( const XE::String& code, XE::Variant val )
{
	if( _p->_ResetInput )
	{
		return;
	}

	auto var = ::XE_EnumID< XE::KeyCode >::Get()->FindValue( code );
	if( !var.IsInvalid() )
	{
		XE::KeyCode key = var.Value< XE::KeyCode >();

		if( key >= KeyCode::Backspace && key <= KeyCode::MouseWheel )
		{
			XE::int32 prev = _p->_ValueMaps[code].ToInt32();
			XE::int32 next = val.ToInt32();

			if( prev != next )
			{
				if( prev == 0 )
				{
					auto it = _p->_ButtonPressedCallbacks.find( key );
					if( it != _p->_ButtonPressedCallbacks.end() )
					{
						for( auto & callback : it->second )
						{
							if( callback )
							{
								callback();
							}
						}
					}
				}
				else
				{
					auto it = _p->_ButtonReleaseCallbacks.find( key );
					if( it != _p->_ButtonReleaseCallbacks.end() )
					{
						for( auto & callback : it->second )
						{
							if( callback )
							{
								callback();
							}
						}
					}
				}
			}
		}
	}

	_p->_ValueMaps[code] = val;
}
