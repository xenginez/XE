#include "AIElementPort.h"

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

BEG_META( XE::VariantInputPort )
type->Property( "Value", &XE::VariantInputPort::Value );
END_META()

BEG_META( XE::VariantOutputPort )
type->Property( "Result", &XE::VariantOutputPort::Result );
END_META()

BEG_META( XE::VariantPairInputPort )
type->Property( "First", &XE::VariantPairInputPort::First );
type->Property( "Second", &XE::VariantPairInputPort::Second );
END_META()

BEG_META( XE::VariantPairOutputPort )
type->Property( "First", &XE::VariantPairOutputPort::First );
type->Property( "Second", &XE::VariantPairOutputPort::Second );
END_META()

BEG_META( XE::BoolInputPort )
type->Property( "Value", &XE::BoolInputPort::Value );
END_META()

BEG_META( XE::BoolOutputPort )
type->Property( "Result", &XE::BoolOutputPort::Result );
END_META()

BEG_META( XE::IntegerInputPort )
type->Property( "Value", &XE::IntegerInputPort::Value );
END_META()

BEG_META( XE::IntegerOutputPort )
type->Property( "Result", &XE::IntegerOutputPort::Result );
END_META()

BEG_META( XE::IntegerPairInputPort )
type->Property( "First", &XE::IntegerPairInputPort::First );
type->Property( "Second", &XE::IntegerPairInputPort::Second );
END_META()

BEG_META( XE::IntegerPairOutputPort )
type->Property( "First", &XE::IntegerPairOutputPort::First );
type->Property( "Second", &XE::IntegerPairOutputPort::Second );
END_META()

BEG_META( XE::InvokeInputPort )
END_META()

XE::IMetaClassPtr XE::InvokeInputPort::GetMetaClassStatic()
{
	static auto p = XE::MakeShared< XE::CXXMetaClass<InvokeInputPort> >( "InvokeInputPort", XE::ClassID<AIInputPort>::Get(), nullptr );
	return p;
}

XE::IMetaClassPtr XE::InvokeInputPort::GetMetaClass() const
{
	if( _Meta )
	{
		return _Meta;
	}

	return GetMetaClassStatic();
}

void XE::InvokeInputPort::Init( const XE::IMetaMethodPtr & method )
{
	auto p = XE::MakeShared< XE::CXXMetaClass<InvokeInputPort> >( "InvokeInputPort", XE::ClassID<AIInputPort>::Get(), nullptr );

	if (!method->IsStatic())
	{
		p->Property( "This", [this]()->XE::Variant { return Parameter["This"]; }, [this]( XE::Variant val ) { Parameter["This"] = val; } );
	}
	auto parameter = method->GetParameter();
	for( int i = 0; i < parameter.size(); ++i )
	{
		XE::String name = XE::StringUtils::Format( "Arg_%1", i );
		p->Property( name, [this, name]()->XE::Variant { return Parameter[name]; }, [this, name]( XE::Variant val ) { Parameter[name] = val; } );
	}

	_Meta = p;
}

BEG_META( XE::SetVariableInputPort )
type->Property( "This", &XE::SetVariableInputPort::This );
type->Property( "Value", &XE::SetVariableInputPort::Value );
END_META()

BEG_META( XE::GetVariableInputPort )
type->Property( "This", &XE::GetVariableInputPort::This );
END_META()
