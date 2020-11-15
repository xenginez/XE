#include "AIElement.h"

#include "Utils/Logger.h"

#include "Blueprint.h"

BEG_META( XE::AIElement )
type->Property( "Name", &XE::AIElement::_Name );
type->Property( "Slots", &XE::AIElement::_Slots, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &XE::AIElement::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "Input", &XE::AIElement::_InputPort, XE::IMetaProperty::NoDesign );
type->Property( "Output", &XE::AIElement::_OutputPort, XE::IMetaProperty::NoDesign );
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

const XE::AIInputPortPtr & XE::AIElement::GetInputPort() const
{
	return _InputPort;
}

void XE::AIElement::SetInputPort( const XE::AIInputPortPtr & val )
{
	_InputPort = val;
}

const XE::AIOutputPortPtr & XE::AIElement::GetOutputPort() const
{
	return _OutputPort;
}

void XE::AIElement::SetOutputPort( const XE::AIOutputPortPtr & val )
{
	_OutputPort = val;
}

void XE::AIElement::Startup()
{
	OnStartup();
}

void XE::AIElement::Execute()
{
	auto blueprint = GetBlueprint();
	for( const auto & slot : _Slots )
	{
		if (auto output = blueprint->GetElement( slot.OutputHandle ) )
		{
			if( output->GetType() == XE::AIElementType::CALC_ELEMENET )
			{
				output->Execute();
			}

			_InputPort->SetProperty( slot.InputPortName, output->_OutputPort->GetProperty( slot.OutputPortName ) );
		}
	}

	OnExecute();
}

void XE::AIElement::Clearup()
{
	OnClearup();

	_InputPort = nullptr;
	_OutputPort = nullptr;
}

void XE::AIElement::OnStartup()
{

}

void XE::AIElement::OnExecute()
{

}

void XE::AIElement::OnClearup()
{

}

IMPLEMENT_META( XE::DataElement )

XE::DataElement::DataElement()
{
	SetType( AIElementType::DATA_ELEMENET );
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::DataElement::~DataElement()
{

}

void XE::DataElement::OnStartup()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::CalcElement )

XE::CalcElement::CalcElement()
{
	SetType( AIElementType::CALC_ELEMENET );
}

XE::CalcElement::~CalcElement()
{

}

IMPLEMENT_META( XE::NotCalcElement )

XE::NotCalcElement::NotCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::NotCalcElement::~NotCalcElement()
{

}

void XE::NotCalcElement::OnExecute()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = !SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::RevCalcElement )

XE::RevCalcElement::RevCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::RevCalcElement::~RevCalcElement()
{

}

void XE::RevCalcElement::OnExecute()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = ~SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::IncCalcElement )

XE::IncCalcElement::IncCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::IncCalcElement::~IncCalcElement()
{

}

void XE::IncCalcElement::OnExecute()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = ++SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::DecCalcElement )

XE::DecCalcElement::DecCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::DecCalcElement::~DecCalcElement()
{

}

void XE::DecCalcElement::OnExecute()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = --SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::NegCalcElement )

XE::NegCalcElement::NegCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::NegCalcElement::~NegCalcElement()
{

}

void XE::NegCalcElement::OnExecute()
{
	SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = -SP_CAST<XE::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( XE::AddCalcElement )

XE::AddCalcElement::AddCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::AddCalcElement::~AddCalcElement()
{

}

void XE::AddCalcElement::OnExecute()
{
	if (auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First + input->Second;
	}
}

IMPLEMENT_META( XE::SubCalcElement )

XE::SubCalcElement::SubCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::SubCalcElement::~SubCalcElement()
{

}

void XE::SubCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First - input->Second;
	}
}

IMPLEMENT_META( XE::MulCalcElement )

XE::MulCalcElement::MulCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::MulCalcElement::~MulCalcElement()
{

}

void XE::MulCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First * input->Second;
	}
}

IMPLEMENT_META( XE::DivCalcElement )

XE::DivCalcElement::DivCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::DivCalcElement::~DivCalcElement()
{

}

void XE::DivCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First / input->Second;
	}
}

IMPLEMENT_META( XE::ModCalcElement )

XE::ModCalcElement::ModCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::ModCalcElement::~ModCalcElement()
{

}

void XE::ModCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First % input->Second;
	}
}

IMPLEMENT_META( XE::XorCalcElement )

XE::XorCalcElement::XorCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::XorCalcElement::~XorCalcElement()
{

}

void XE::XorCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First ^ input->Second;
	}
}

IMPLEMENT_META( XE::AndCalcElement )

XE::AndCalcElement::AndCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::AndCalcElement::~AndCalcElement()
{

}

void XE::AndCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First & input->Second;
	}
}

IMPLEMENT_META( XE::OrCalcElement )

XE::OrCalcElement::OrCalcElement()
{
	SetInputPort( XE::MakeShared<XE::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::OrCalcElement::~OrCalcElement()
{

}

void XE::OrCalcElement::OnExecute()
{
	if( auto input = SP_CAST<XE::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<XE::VariantOutputPort>( GetOutputPort() )->Result = input->First | input->Second;
	}
}

IMPLEMENT_META( XE::LogicElement )

XE::LogicElement::LogicElement()
{
	SetType( AIElementType::LOGIC_ELEMENET );
}

XE::LogicElement::~LogicElement()
{

}

BEG_META( XE::IfLogicElement )
type->Property( "If", &XE::IfLogicElement::_IfOutput, XE::IMetaProperty::NoDesign );
type->Property( "Else", &XE::IfLogicElement::_ElseOutput, XE::IMetaProperty::NoDesign );
END_META()

XE::IfLogicElement::IfLogicElement()
{
	SetInputPort( XE::MakeShared<XE::BoolInputPort>() );
}

XE::IfLogicElement::~IfLogicElement()
{

}

void XE::IfLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();

	if( SP_CAST<XE::BoolInputPort>( GetInputPort() )->Value )
	{
		if( _IfOutput.Handle ) blueprint->GetElement( _IfOutput.Handle )->Execute();
	}
	else
	{
		if( _ElseOutput.Handle ) blueprint->GetElement( _ElseOutput.Handle )->Execute();
	}
}

BEG_META( XE::ForLogicElement )
type->Property( "Loop", &XE::ForLogicElement::_LoopOutput, XE::IMetaProperty::NoDesign );
type->Property( "Completed", &XE::ForLogicElement::_CompletedOutput, XE::IMetaProperty::NoDesign );
END_META()

XE::ForLogicElement::ForLogicElement()
{
	SetInputPort( XE::MakeShared<XE::IntegerPairInputPort>() );
	SetOutputPort( XE::MakeShared<XE::IntegerOutputPort>() );
}

XE::ForLogicElement::~ForLogicElement()
{

}

void XE::ForLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<XE::IntegerPairInputPort>( GetInputPort() );
	auto output = SP_CAST<XE::IntegerOutputPort>( GetOutputPort() );
	for( XE::uint64 i = input->First; i < input->Second; ++i )
	{
		output->Result = i;
		if( _LoopOutput.Handle ) blueprint->GetElement( _LoopOutput.Handle )->Execute();
	}
	if( _CompletedOutput.Handle ) blueprint->GetElement( _CompletedOutput.Handle )->Execute();
}

BEG_META( XE::SwitchLogicElement )
type->Property( "Case0", &XE::SwitchLogicElement::_CaseOutput0, XE::IMetaProperty::NoDesign );
type->Property( "Case1", &XE::SwitchLogicElement::_CaseOutput1, XE::IMetaProperty::NoDesign );
type->Property( "Case2", &XE::SwitchLogicElement::_CaseOutput2, XE::IMetaProperty::NoDesign );
type->Property( "Case3", &XE::SwitchLogicElement::_CaseOutput3, XE::IMetaProperty::NoDesign );
type->Property( "Case4", &XE::SwitchLogicElement::_CaseOutput4, XE::IMetaProperty::NoDesign );
type->Property( "Case5", &XE::SwitchLogicElement::_CaseOutput5, XE::IMetaProperty::NoDesign );
type->Property( "Case6", &XE::SwitchLogicElement::_CaseOutput6, XE::IMetaProperty::NoDesign );
type->Property( "Case7", &XE::SwitchLogicElement::_CaseOutput7, XE::IMetaProperty::NoDesign );
type->Property( "Case8", &XE::SwitchLogicElement::_CaseOutput8, XE::IMetaProperty::NoDesign );
type->Property( "Case9", &XE::SwitchLogicElement::_CaseOutput9, XE::IMetaProperty::NoDesign );
type->Property( "Default", &XE::SwitchLogicElement::_DefaultOutput, XE::IMetaProperty::NoDesign );
END_META()

XE::SwitchLogicElement::SwitchLogicElement()
{
	SetInputPort( XE::MakeShared<XE::IntegerInputPort>() );
}

XE::SwitchLogicElement::~SwitchLogicElement()
{

}

void XE::SwitchLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<XE::IntegerInputPort>( GetInputPort() );
	switch( input->Value )
	{
	case 0:
		if( _CaseOutput0.Handle ) blueprint->GetElement( _CaseOutput0.Handle )->Execute();
		break;
	case 1:
		if( _CaseOutput1.Handle ) blueprint->GetElement( _CaseOutput1.Handle )->Execute();
		break;
	case 2:
		if( _CaseOutput2.Handle ) blueprint->GetElement( _CaseOutput2.Handle )->Execute();
		break;
	case 3:
		if( _CaseOutput3.Handle ) blueprint->GetElement( _CaseOutput3.Handle )->Execute();
		break;
	case 4:
		if( _CaseOutput4.Handle ) blueprint->GetElement( _CaseOutput4.Handle )->Execute();
		break;
	case 5:
		if( _CaseOutput5.Handle ) blueprint->GetElement( _CaseOutput5.Handle )->Execute();
		break;
	case 6:
		if( _CaseOutput6.Handle ) blueprint->GetElement( _CaseOutput6.Handle )->Execute();
		break;
	case 7:
		if( _CaseOutput7.Handle ) blueprint->GetElement( _CaseOutput7.Handle )->Execute();
		break;
	case 8:
		if( _CaseOutput8.Handle ) blueprint->GetElement( _CaseOutput8.Handle )->Execute();
		break;
	case 9:
		if( _CaseOutput9.Handle ) blueprint->GetElement( _CaseOutput9.Handle )->Execute();
	default:
		if( _DefaultOutput.Handle ) blueprint->GetElement( _DefaultOutput.Handle )->Execute();
		break;
	}
}

BEG_META( XE::SequenceLogicElement )
type->Property( "Output0", &XE::SequenceLogicElement::_Output0, XE::IMetaProperty::NoDesign );
type->Property( "Output1", &XE::SequenceLogicElement::_Output1, XE::IMetaProperty::NoDesign );
type->Property( "Output2", &XE::SequenceLogicElement::_Output2, XE::IMetaProperty::NoDesign );
type->Property( "Output3", &XE::SequenceLogicElement::_Output3, XE::IMetaProperty::NoDesign );
type->Property( "Output4", &XE::SequenceLogicElement::_Output4, XE::IMetaProperty::NoDesign );
type->Property( "Output5", &XE::SequenceLogicElement::_Output5, XE::IMetaProperty::NoDesign );
type->Property( "Output6", &XE::SequenceLogicElement::_Output6, XE::IMetaProperty::NoDesign );
type->Property( "Output7", &XE::SequenceLogicElement::_Output7, XE::IMetaProperty::NoDesign );
type->Property( "Output8", &XE::SequenceLogicElement::_Output8, XE::IMetaProperty::NoDesign );
type->Property( "Output9", &XE::SequenceLogicElement::_Output9, XE::IMetaProperty::NoDesign );
END_META()

XE::SequenceLogicElement::SequenceLogicElement()
{

}

XE::SequenceLogicElement::~SequenceLogicElement()
{

}

void XE::SequenceLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<XE::IntegerInputPort>( GetInputPort() );

	if( _Output0.Handle ) blueprint->GetElement( _Output0.Handle )->Execute();
	if( _Output1.Handle ) blueprint->GetElement( _Output1.Handle )->Execute();
	if( _Output2.Handle ) blueprint->GetElement( _Output2.Handle )->Execute();
	if( _Output3.Handle ) blueprint->GetElement( _Output3.Handle )->Execute();
	if( _Output4.Handle ) blueprint->GetElement( _Output4.Handle )->Execute();
	if( _Output5.Handle ) blueprint->GetElement( _Output5.Handle )->Execute();
	if( _Output6.Handle ) blueprint->GetElement( _Output6.Handle )->Execute();
	if( _Output7.Handle ) blueprint->GetElement( _Output7.Handle )->Execute();
	if( _Output8.Handle ) blueprint->GetElement( _Output8.Handle )->Execute();
	if( _Output9.Handle ) blueprint->GetElement( _Output9.Handle )->Execute();
}

BEG_META( XE::EventElement )
type->Property( "ListenerEvent", &XE::EventElement::_ListenerEvent );
type->Property( "Output", &XE::EventElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::EventElement::EventElement()
{
	SetType( AIElementType::EVENT_ELEMENET );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::EventElement::~EventElement()
{

}

XE::EventHandle XE::EventElement::GetListenerEvent() const
{
	return _ListenerEvent;
}

void XE::EventElement::SetListenerEvent( XE::EventHandle val )
{
	_ListenerEvent = val;
}

void XE::EventElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto output = SP_CAST<XE::VariantOutputPort>( GetOutputPort() );

	if( _Output.Handle ) blueprint->GetElement( _Output.Handle )->Execute();
}

BEG_META( XE::ActionElement )
type->Property( "MethodFullName", &XE::ActionElement::_MethodFullName );
type->Property( "Output", &XE::ActionElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::ActionElement::ActionElement()
{
	SetType( AIElementType::ACTION_ELEMENET );

	SetInputPort( XE::MakeShared<XE::InvokeInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
}

XE::ActionElement::~ActionElement()
{

}

const XE::String & XE::ActionElement::GetMethodFullName() const
{
	return _MethodFullName;
}

void XE::ActionElement::SetMethodFullName( const XE::String & val )
{
	_MethodFullName = val;
}

void XE::ActionElement::OnStartup()
{
	if( auto method = XE::Reflection::FindMethod( _MethodFullName ) )
	{
		auto input = SP_CAST<XE::InvokeInputPort>( GetInputPort() );
		input->Init( method );
	}
}

void XE::ActionElement::OnExecute()
{
	auto input = SP_CAST<XE::InvokeInputPort>( GetInputPort() );
	auto output = SP_CAST<XE::VariantOutputPort>( GetOutputPort() );

	if( auto method = XE::Reflection::FindMethod( _MethodFullName ) )
	{
		XE::InvokeStack params;

		if( !method->IsStatic() )
		{
			params.Push( input->GetProperty("This") );
		}

		auto parameter = method->GetParameter();
		for( int i = 0; i < parameter.size(); ++i )
		{
			params.Push( input->GetProperty( XE::StringUtils::Format( "Arg_%1", i ) ) );
		}

		output->Result = method->Invoke( &params );
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
END_META()

XE::SetVariableElement::SetVariableElement()
{
	SetInputPort( XE::MakeShared<XE::SetVariableInputPort>() );
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

void XE::SetVariableElement::OnExecute()
{
	auto input = SP_CAST<XE::SetVariableInputPort>( GetInputPort() );
	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		prop->Set( input->This, input->Value );
	}

	if( _Output.Handle ) GetBlueprint()->GetElement( _Output.Handle )->Execute();
}

BEG_META( XE::GetVariableElement )
type->Property( "PropertyFullName", &XE::GetVariableElement::_PropertyFullName );
END_META()

XE::GetVariableElement::GetVariableElement()
{
	SetInputPort( XE::MakeShared<XE::GetVariableInputPort>() );
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
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

void XE::GetVariableElement::OnExecute()
{
	auto input = SP_CAST<XE::GetVariableInputPort>( GetInputPort() );
	auto output = SP_CAST<XE::VariantOutputPort>( GetOutputPort() );

	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		output->Result = prop->Get( input->This );
	}
}

BEG_META( XE::SetBlackboardKeyElement )
type->Property( "BlackboardKey", &XE::SetBlackboardKeyElement::_BlackboardKey );
type->Property( "Output", &XE::SetBlackboardKeyElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

XE::SetBlackboardKeyElement::SetBlackboardKeyElement()
{
	SetInputPort( XE::MakeShared<XE::VariantInputPort>() );
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

void XE::SetBlackboardKeyElement::OnExecute()
{
	auto input = SP_CAST<XE::VariantInputPort>( GetInputPort() );

	GetBlueprint()->SetKey( _BlackboardKey, input->Value );

	if( _Output.Handle ) GetBlueprint()->GetElement( _Output.Handle )->Execute();
}

BEG_META( XE::GetBlackboardKeyElement )
type->Property( "BlackboardKey", &XE::GetBlackboardKeyElement::_BlackboardKey );
END_META()

XE::GetBlackboardKeyElement::GetBlackboardKeyElement()
{
	SetOutputPort( XE::MakeShared<XE::VariantOutputPort>() );
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

void XE::GetBlackboardKeyElement::OnExecute()
{
	auto output = SP_CAST<XE::VariantOutputPort>( GetOutputPort() );

	 output->Result = GetBlueprint()->GetKey( _BlackboardKey );
}
