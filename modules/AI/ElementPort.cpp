#include "ElementPort.h"

BEG_META( AI::AISlot )
type->Property( "OutputHandle", &AI::AISlot::OutputHandle, XE::IMetaProperty::NoDesign );
type->Property( "InputPortName", &AI::AISlot::InputPortName, XE::IMetaProperty::NoDesign );
type->Property( "OutputPortName", &AI::AISlot::OutputPortName, XE::IMetaProperty::NoDesign );
END_META()

BEG_META( AI::AIOutput )
type->Property( "Handle", &AI::AIOutput::Handle, XE::IMetaProperty::NoDesign );
END_META()

IMPLEMENT_META( AI::InputPort );

IMPLEMENT_META( AI::OutputPort );

BEG_META( AI::VariantInputPort )
type->Property( "Value", &AI::VariantInputPort::Value );
END_META()

BEG_META( AI::VariantOutputPort )
type->Property( "Result", &AI::VariantOutputPort::Result );
END_META()

BEG_META( AI::VariantPairInputPort )
type->Property( "First", &AI::VariantPairInputPort::First );
type->Property( "Second", &AI::VariantPairInputPort::Second );
END_META()

BEG_META( AI::VariantPairOutputPort )
type->Property( "First", &AI::VariantPairOutputPort::First );
type->Property( "Second", &AI::VariantPairOutputPort::Second );
END_META()

BEG_META( AI::BoolInputPort )
type->Property( "Value", &AI::BoolInputPort::Value );
END_META()

BEG_META( AI::BoolOutputPort )
type->Property( "Result", &AI::BoolOutputPort::Result );
END_META()

BEG_META( AI::IntegerInputPort )
type->Property( "Value", &AI::IntegerInputPort::Value );
END_META()

BEG_META( AI::IntegerOutputPort )
type->Property( "Result", &AI::IntegerOutputPort::Result );
END_META()

BEG_META( AI::IntegerPairInputPort )
type->Property( "First", &AI::IntegerPairInputPort::First );
type->Property( "Second", &AI::IntegerPairInputPort::Second );
END_META()

BEG_META( AI::IntegerPairOutputPort )
type->Property( "First", &AI::IntegerPairOutputPort::First );
type->Property( "Second", &AI::IntegerPairOutputPort::Second );
END_META()

BEG_META( AI::InvokeInputPort )
END_META()

XE::IMetaClassPtr AI::InvokeInputPort::GetMetaClassStatic()
{
	static auto p = XE::MakeShared< XE::CXXMetaClass<InvokeInputPort> >( "InvokeInputPort", ::XE_ClassID<InputPort>::Get(), nullptr, GetModule() );
	return p;
}

XE::IMetaClassPtr AI::InvokeInputPort::GetMetaClass() const
{
	if( _Meta )
	{
		return _Meta;
	}

	return GetMetaClassStatic();
}

void AI::InvokeInputPort::Init( const XE::IMetaMethodPtr & method )
{
	auto p = XE::MakeShared< XE::CXXMetaClass<InvokeInputPort> >( "InvokeInputPort", ::XE_ClassID<InputPort>::Get(), nullptr, GetModule() );

	if (!method->IsStatic())
	{
		p->Property( "This", &AI::InvokeInputPort::This );
	}

	switch( method->GetParameter().size() )
	{
	case 9:
		p->Property( "Arg_9", &AI::InvokeInputPort::Arg_9 );
	case 8:
		p->Property( "Arg_8", &AI::InvokeInputPort::Arg_8 );
	case 7:
		p->Property( "Arg_7", &AI::InvokeInputPort::Arg_7 );
	case 6:
		p->Property( "Arg_6", &AI::InvokeInputPort::Arg_6 );
	case 5:
		p->Property( "Arg_5", &AI::InvokeInputPort::Arg_5 );
	case 4:
		p->Property( "Arg_4", &AI::InvokeInputPort::Arg_4 );
	case 3:
		p->Property( "Arg_3", &AI::InvokeInputPort::Arg_3 );
	case 2:
		p->Property( "Arg_2", &AI::InvokeInputPort::Arg_2 );
	case 1:
		p->Property( "Arg_1", &AI::InvokeInputPort::Arg_1 );
	case 0:
		p->Property( "Arg_0", &AI::InvokeInputPort::Arg_0 );
	default:
		break;
	}

	_Meta = p;
}

BEG_META( AI::SetVariableInputPort )
type->Property( "This", &AI::SetVariableInputPort::This );
type->Property( "Value", &AI::SetVariableInputPort::Value );
END_META()

BEG_META( AI::GetVariableInputPort )
type->Property( "This", &AI::GetVariableInputPort::This );
END_META()
