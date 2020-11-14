#include "AIElement.h"

#include "Utils/Logger.h"

#include "Blueprint.h"

BEG_META( XE::AISlot )
type->Property( "OutputHandle", &XE::AISlot::OutputHandle, XE::IMetaProperty::NoDesign );
type->Property( "InputPortName", &XE::AISlot::InputPortName, XE::IMetaProperty::NoDesign );
type->Property( "OutputPortName", &XE::AISlot::OutputPortName, XE::IMetaProperty::NoDesign );
END_META()

BEG_META( XE::AIOutput )
type->Property( "Handle", &XE::AIOutput::Handle, XE::IMetaProperty::NoDesign );
END_META()
IMPLEMENT_META( XE::AIInputPort );

IMPLEMENT_META( XE::AIOutputPort );

BEG_META( XE::AIElement )
type->Property( "Name", &XE::AIElement::_Name );
type->Property( "Slots", &XE::AIElement::_Slots, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &XE::AIElement::_Handle, XE::IMetaProperty::NoDesign );
END_META()

XE::AIElement::AIElement()
{
	_Name = GetMetaClass()->GetName();
}

XE::AIElement::~AIElement()
{

}

const XE::String & XE::AIElement::GetName() const
{
	return _Name;
}

void XE::AIElement::SetName( const XE::String & val )
{
	_Name;
}

XE::AIElementType XE::AIElement::GetType() const
{
	return _Type;
}

void XE::AIElement::SetType( XE::AIElementType val )
{
	_Type = val;
}

XE::BlueprintPtr XE::AIElement::GetBlueprint() const
{
	return _Blueprint.lock();
}

void XE::AIElement::SetBlueprint( BlueprintPtr val )
{
	_Blueprint = val;
}

XE::AIElementHandle XE::AIElement::GetHandle() const
{
	return _Handle;
}

void XE::AIElement::SetHandle( XE::AIElementHandle val )
{
	_Handle = val;
}

const XE::Array< XE::AISlot > & XE::AIElement::GetSlots() const
{
	return _Slots;
}

void XE::AIElement::SetSlots( const XE::Array< XE::AISlot > & val )
{
	_Slots = val;
}

void XE::AIElement::Execute()
{
	auto blueprint = GetBlueprint();
	for( const auto & slot : _Slots )
	{
		if (auto elem = blueprint->GetElement( slot.OutputHandle ) )
		{
			SetInputValue( slot.InputPortName, elem->GetOutputValue( slot.OutputPortName ) );
		}
	}

	OnExecute();

	if( auto prop = GetMetaClass()->FindProperty( "Output" ) )
	{
		if( auto elem = blueprint->GetElement( prop->Get( this ).Value<AIOutput>().Handle ) )
		{
			elem->Execute();
		}
	}
}

void XE::AIElement::OnExecute()
{

}

XE::Variant XE::AIElement::GetOutputValue( const XE::String & val )
{

}

void XE::AIElement::SetInputValue( const XE::String & name, const XE::Variant & val )
{

}

BEG_META( XE::DataElement )
type->Property( "Value", &XE::DataElement::_Value );
type->Property( "Result", &XE::DataElement::_ResultOutputPort, XE::IMetaProperty::NoDesign );
END_META()

XE::DataElement::DataElement()
{
	SetType( AIElementType::DATA_ELEMENET );
}

XE::DataElement::~DataElement()
{

}

const XE::Variant & XE::DataElement::GetValue() const
{
	return _Value;
}

void XE::DataElement::SetValue( const XE::Variant & val )
{
	_Value = val;
}

XE::Variant XE::DataElement::GetOutputValue( const XE::String & val )
{
	return _Value;
}

BEG_META( XE::CalcElement )
END_META()

XE::CalcElement::CalcElement()
{
	SetType( AIElementType::CALC_ELEMENET );
}

XE::CalcElement::~CalcElement()
{

}

BEG_META( XE::LogicElement )
type->Property( "Output", &XE::LogicElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::LogicElement::LogicElement()
{
	SetType( AIElementType::LOGIC_ELEMENET );
}

XE::LogicElement::~LogicElement()
{

}

const XE::AIOutput & XE::LogicElement::GetOutput() const
{
	return _Output;
}

void XE::LogicElement::SetOutput( const XE::AIOutput & val )
{
	_Output = val;
}

BEG_META( XE::EventElement )
type->Property( "ListenerEvent", &XE::EventElement::_ListenerEvent );
type->Property( "Output", &XE::EventElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::EventElement::EventElement()
{
	SetType( AIElementType::EVENT_ELEMENET );
}

XE::EventElement::~EventElement()
{

}

const XE::Variant & XE::EventElement::GetValue() const
{
	return _Value;
}

void XE::EventElement::SetValue( const XE::Variant & val )
{
	_Value = val;
}

const XE::AIOutput & XE::EventElement::GetOutput() const
{
	return _Output;
}

void XE::EventElement::SetOutput( const XE::AIOutput & val )
{
	_Output = val;
}

XE::EventHandle XE::EventElement::GetListenerEvent() const
{
	return _ListenerEvent;
}

void XE::EventElement::SetListenerEvent( XE::EventHandle val )
{
	_ListenerEvent = val;
}

BEG_META( XE::ActionElement )
type->Property( "MethodFullName", &XE::ActionElement::_MethodFullName );
type->Property( "Output", &XE::ActionElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::ActionElement::ActionElement()
	:_Params( 10 )
{
	SetType( AIElementType::ACTION_ELEMENET );
}

XE::ActionElement::~ActionElement()
{

}

const XE::AIOutput & XE::ActionElement::GetOutput() const
{
	return _Output;
}

void XE::ActionElement::SetOutput( const XE::AIOutput & val )
{
	_Output = val;
}

const XE::String & XE::ActionElement::GetMethodFullName() const
{
	return _MethodFullName;
}

void XE::ActionElement::SetMethodFullName( const XE::String & val )
{
	_MethodFullName = val;
}

void XE::ActionElement::OnExecute()
{
	if( auto method = XE::Reflection::FindMethod( _MethodFullName ) )
	{
		XE::InvokeStack params;

		if( !method->IsStatic() )
		{
			params.Push( _This );
		}
		for( const auto & var : _Params )
		{
			params.Push( var );
		}

		_Result = method->Invoke( &params );
	}
}

XE::Variant XE::ActionElement::GetOutputValue( const XE::String & val )
{
	if( val == "Result" )
	{
		return _Result;
	}

	return {};
}

void XE::ActionElement::SetInputValue( const XE::String & name, const XE::Variant & val )
{
	for( int i = 0; i < 10; ++i )
	{
		if( name == XE::StringUtils::Format( "arg_$1", i ) )
		{
			_Params[i] = val;
			return;
		}
	}
}

BEG_META( XE::VariableElement )
END_META()

XE::VariableElement::VariableElement()
{
	SetType( AIElementType::VARIABLE_ELEMENET );
}

XE::VariableElement::~VariableElement()
{

}

BEG_META( XE::SetVariableElement )
type->Property( "PropertyFullName", &XE::SetVariableElement::_PropertyFullName );
type->Property( "Output", &XE::SetVariableElement::_Output, XE::IMetaProperty::NoDesign );
type->Property( "This", &XE::SetVariableElement::_ThisInputPort, XE::IMetaProperty::NoDesign );
type->Property( "Value", &XE::SetVariableElement::_ValueInputPort, XE::IMetaProperty::NoDesign );
END_META()

XE::SetVariableElement::SetVariableElement()
{

}

XE::SetVariableElement::~SetVariableElement()
{

}

const XE::AIOutput & XE::SetVariableElement::GetOutput() const
{
	return _Output;
}

void XE::SetVariableElement::SetOutput( const XE::AIOutput & val )
{
	_Output = val;
}

const XE::String & XE::SetVariableElement::GetPropertyFullName() const
{
	return _PropertyFullName;
}

void XE::SetVariableElement::SetPropertyFullName( const XE::String & val )
{
	_PropertyFullName = val;
}

void XE::SetVariableElement::SetInputValue( const XE::String & name, const XE::Variant & val )
{
	if( name == "This" )
	{
		_This = val;
	}
	else if( name == "Value" )
	{
		_Value = val;
	}
}

void XE::SetVariableElement::OnExecute()
{
	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		prop->Set( _This, _Value );
	}
}

BEG_META( XE::GetVariableElement )
type->Property( "PropertyFullName", &XE::GetVariableElement::_PropertyFullName );
type->Property( "This", &XE::GetVariableElement::_PropertyFullName, XE::IMetaProperty::NoDesign );
type->Property( "Result", &XE::GetVariableElement::_PropertyFullName, XE::IMetaProperty::NoDesign );
END_META()

XE::GetVariableElement::GetVariableElement()
{

}

XE::GetVariableElement::~GetVariableElement()
{

}

const XE::String & XE::GetVariableElement::GetPropertyFullName() const
{
	return _PropertyFullName;
}

void XE::GetVariableElement::SetPropertyFullName( const XE::String & val )
{
	_PropertyFullName = val;
}

XE::Variant XE::GetVariableElement::GetOutputValue( const XE::String & val )
{
	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		return prop->Get( _This );
	}
}

void XE::GetVariableElement::SetInputValue( const XE::String & name, const XE::Variant & val )
{
	_This = val;
}

BEG_META( XE::SetBlackboardKeyElement )
type->Property( "BlackboardKey", &XE::SetBlackboardKeyElement::_BlackboardKey );
type->Property( "Output", &XE::SetBlackboardKeyElement::_Output, XE::IMetaProperty::NoDesign );
type->Property( "Value", &XE::SetBlackboardKeyElement::_ValueInputPort, XE::IMetaProperty::NoDesign );
END_META()

XE::SetBlackboardKeyElement::SetBlackboardKeyElement()
{

}

XE::SetBlackboardKeyElement::~SetBlackboardKeyElement()
{

}

const XE::AIOutput & XE::SetBlackboardKeyElement::GetOutput() const
{
	return _Output;
}

void XE::SetBlackboardKeyElement::SetOutput( const XE::AIOutput & val )
{
	_Output = val;
}

const XE::BlackboardKey & XE::SetBlackboardKeyElement::GetBlackboardKey() const
{
	return _BlackboardKey;
}

void XE::SetBlackboardKeyElement::SetBlackboardKey( const XE::BlackboardKey & val )
{
	_BlackboardKey = val;
}

void XE::SetBlackboardKeyElement::SetInputValue( const XE::String & name, const XE::Variant & val )
{
	GetBlueprint()->SetKey( _BlackboardKey, val );
}

BEG_META( XE::GetBlackboardKeyElement )
type->Property( "BlackboardKey", &XE::GetBlackboardKeyElement::_BlackboardKey );
type->Property( "Result", &XE::GetBlackboardKeyElement::_ResultOutputPort, XE::IMetaProperty::NoDesign );
END_META()

XE::GetBlackboardKeyElement::GetBlackboardKeyElement()
{

}

XE::GetBlackboardKeyElement::~GetBlackboardKeyElement()
{

}

const XE::BlackboardKey & XE::GetBlackboardKeyElement::GetBlackboardKey() const
{
	return _BlackboardKey;
}

void XE::GetBlackboardKeyElement::SetBlackboardKey( const XE::BlackboardKey & val )
{
	_BlackboardKey = val;
}

XE::Variant XE::GetBlackboardKeyElement::GetOutputValue( const XE::String & val )
{
	return GetBlueprint()->GetKey( val );
}
