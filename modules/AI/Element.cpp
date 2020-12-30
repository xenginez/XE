#include "Element.h"

#include "Blueprint.h"
#include "ElementPort.h"

BEG_META( AI::Element )
type->Property( "Name", &AI::Element::_Name );
type->Property( "Slots", &AI::Element::_Slots, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &AI::Element::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "Input", &AI::Element::_InputPort, XE::IMetaProperty::NoDesign );
type->Property( "Output", &AI::Element::_OutputPort, XE::IMetaProperty::NoDesign );
END_META()

AI::Element::Element()
{
	_Name = GetMetaClass()->GetName();
}

AI::Element::~Element()
{

}

const XE::String & AI::Element::GetName() const
{
	return _Name;
}

void AI::Element::SetName( const XE::String & val )
{
	_Name;
}

AI::AIElementType AI::Element::GetType() const
{
	return _Type;
}

void AI::Element::SetType( AI::AIElementType val )
{
	_Type = val;
}

AI::BlueprintPtr AI::Element::GetBlueprint() const
{
	return _Blueprint.lock();
}

void AI::Element::SetBlueprint( BlueprintPtr val )
{
	_Blueprint = val;
}

AI::ElementHandle AI::Element::GetHandle() const
{
	return _Handle;
}

void AI::Element::SetHandle( AI::ElementHandle val )
{
	_Handle = val;
}

const XE::Array< AI::AISlot > & AI::Element::GetSlots() const
{
	return _Slots;
}

void AI::Element::SetSlots( const XE::Array< AI::AISlot > & val )
{
	_Slots = val;
}

const AI::InputPortPtr & AI::Element::GetInputPort() const
{
	return _InputPort;
}

void AI::Element::SetInputPort( const AI::InputPortPtr & val )
{
	_InputPort = val;
}

const AI::OutputPortPtr & AI::Element::GetOutputPort() const
{
	return _OutputPort;
}

void AI::Element::SetOutputPort( const AI::OutputPortPtr & val )
{
	_OutputPort = val;
}

void AI::Element::Startup()
{
	OnStartup();
}

void AI::Element::Execute()
{
	auto blueprint = GetBlueprint();
	for( const auto & slot : _Slots )
	{
		if (auto output = blueprint->GetElement( slot.OutputHandle ) )
		{
			if( output->GetType() == AI::AIElementType::CALC_ELEMENET )
			{
				output->Execute();
			}

			_InputPort->SetProperty( slot.InputPortName, output->_OutputPort->GetProperty( slot.OutputPortName ) );
		}
	}

	OnExecute();
}

void AI::Element::Clearup()
{
	OnClearup();

	_InputPort = nullptr;
	_OutputPort = nullptr;
}

void AI::Element::OnStartup()
{

}

void AI::Element::OnExecute()
{

}

void AI::Element::OnClearup()
{

}

IMPLEMENT_META( AI::DataElement )

AI::DataElement::DataElement()
{
	SetType( AIElementType::DATA_ELEMENET );
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::DataElement::~DataElement()
{

}

void AI::DataElement::OnStartup()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::CalcElement )

AI::CalcElement::CalcElement()
{
	SetType( AIElementType::CALC_ELEMENET );
}

AI::CalcElement::~CalcElement()
{

}

IMPLEMENT_META( AI::NotCalcElement )

AI::NotCalcElement::NotCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::NotCalcElement::~NotCalcElement()
{

}

void AI::NotCalcElement::OnExecute()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = !SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::RevCalcElement )

AI::RevCalcElement::RevCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::RevCalcElement::~RevCalcElement()
{

}

void AI::RevCalcElement::OnExecute()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = ~SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::IncCalcElement )

AI::IncCalcElement::IncCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::IncCalcElement::~IncCalcElement()
{

}

void AI::IncCalcElement::OnExecute()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = ++SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::DecCalcElement )

AI::DecCalcElement::DecCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::DecCalcElement::~DecCalcElement()
{

}

void AI::DecCalcElement::OnExecute()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = --SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::NegCalcElement )

AI::NegCalcElement::NegCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::NegCalcElement::~NegCalcElement()
{

}

void AI::NegCalcElement::OnExecute()
{
	SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = -SP_CAST<AI::VariantInputPort>( GetInputPort() )->Value;
}

IMPLEMENT_META( AI::AddCalcElement )

AI::AddCalcElement::AddCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::AddCalcElement::~AddCalcElement()
{

}

void AI::AddCalcElement::OnExecute()
{
	if (auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First + input->Second;
	}
}

IMPLEMENT_META( AI::SubCalcElement )

AI::SubCalcElement::SubCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::SubCalcElement::~SubCalcElement()
{

}

void AI::SubCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First - input->Second;
	}
}

IMPLEMENT_META( AI::MulCalcElement )

AI::MulCalcElement::MulCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::MulCalcElement::~MulCalcElement()
{

}

void AI::MulCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First * input->Second;
	}
}

IMPLEMENT_META( AI::DivCalcElement )

AI::DivCalcElement::DivCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::DivCalcElement::~DivCalcElement()
{

}

void AI::DivCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First / input->Second;
	}
}

IMPLEMENT_META( AI::ModCalcElement )

AI::ModCalcElement::ModCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::ModCalcElement::~ModCalcElement()
{

}

void AI::ModCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First % input->Second;
	}
}

IMPLEMENT_META( AI::XorCalcElement )

AI::XorCalcElement::XorCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::XorCalcElement::~XorCalcElement()
{

}

void AI::XorCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First ^ input->Second;
	}
}

IMPLEMENT_META( AI::AndCalcElement )

AI::AndCalcElement::AndCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::AndCalcElement::~AndCalcElement()
{

}

void AI::AndCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First & input->Second;
	}
}

IMPLEMENT_META( AI::OrCalcElement )

AI::OrCalcElement::OrCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::OrCalcElement::~OrCalcElement()
{

}

void AI::OrCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::VariantOutputPort>( GetOutputPort() )->Result = input->First | input->Second;
	}
}

IMPLEMENT_META( AI::GreaterCalcElement )

AI::GreaterCalcElement::GreaterCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::GreaterCalcElement::~GreaterCalcElement()
{

}

void AI::GreaterCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First > input->Second;
	}
}

IMPLEMENT_META( AI::LessCalcElement )

AI::LessCalcElement::LessCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::LessCalcElement::~LessCalcElement()
{

}

void AI::LessCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First < input->Second;
	}
}

IMPLEMENT_META( AI::GreaterEqualCalcElement )

AI::GreaterEqualCalcElement::GreaterEqualCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::GreaterEqualCalcElement::~GreaterEqualCalcElement()
{

}

void AI::GreaterEqualCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First >= input->Second;
	}
}

IMPLEMENT_META( AI::LessEqualCalcElement )

AI::LessEqualCalcElement::LessEqualCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::LessEqualCalcElement::~LessEqualCalcElement()
{

}

void AI::LessEqualCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First != input->Second;
	}
}

IMPLEMENT_META( AI::EqualCalcElement )

AI::EqualCalcElement::EqualCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::EqualCalcElement::~EqualCalcElement()
{

}

void AI::EqualCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First == input->Second;
	}
}

IMPLEMENT_META( AI::NotEqualCalcElement )

AI::NotEqualCalcElement::NotEqualCalcElement()
{
	SetInputPort( XE::MakeShared<AI::VariantPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::BoolOutputPort>() );
}

AI::NotEqualCalcElement::~NotEqualCalcElement()
{

}

void AI::NotEqualCalcElement::OnExecute()
{
	if( auto input = SP_CAST<AI::VariantPairInputPort>( GetInputPort() ) )
	{
		SP_CAST<AI::BoolOutputPort>( GetOutputPort() )->Result = input->First == input->Second;
	}
}

IMPLEMENT_META( AI::LogicElement )

AI::LogicElement::LogicElement()
{
	SetType( AIElementType::LOGIC_ELEMENET );
}

AI::LogicElement::~LogicElement()
{

}

BEG_META( AI::IfLogicElement )
type->Property( "If", &AI::IfLogicElement::_IfOutput, XE::IMetaProperty::NoDesign );
type->Property( "Else", &AI::IfLogicElement::_ElseOutput, XE::IMetaProperty::NoDesign );
END_META()

AI::IfLogicElement::IfLogicElement()
{
	SetInputPort( XE::MakeShared<AI::BoolInputPort>() );
}

AI::IfLogicElement::~IfLogicElement()
{

}

void AI::IfLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();

	if( SP_CAST<AI::BoolInputPort>( GetInputPort() )->Value )
	{
		if( _IfOutput.Handle ) blueprint->GetElement( _IfOutput.Handle )->Execute();
	}
	else
	{
		if( _ElseOutput.Handle ) blueprint->GetElement( _ElseOutput.Handle )->Execute();
	}
}

BEG_META( AI::ForLogicElement )
type->Property( "Loop", &AI::ForLogicElement::_LoopOutput, XE::IMetaProperty::NoDesign );
type->Property( "Completed", &AI::ForLogicElement::_CompletedOutput, XE::IMetaProperty::NoDesign );
END_META()

AI::ForLogicElement::ForLogicElement()
{
	SetInputPort( XE::MakeShared<AI::IntegerPairInputPort>() );
	SetOutputPort( XE::MakeShared<AI::IntegerOutputPort>() );
}

AI::ForLogicElement::~ForLogicElement()
{

}

void AI::ForLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<AI::IntegerPairInputPort>( GetInputPort() );
	auto output = SP_CAST<AI::IntegerOutputPort>( GetOutputPort() );
	for( XE::int64 i = input->First; i < input->Second; ++i )
	{
		output->Result = i;
		if( _LoopOutput.Handle ) blueprint->GetElement( _LoopOutput.Handle )->Execute();
	}
	if( _CompletedOutput.Handle ) blueprint->GetElement( _CompletedOutput.Handle )->Execute();
}

BEG_META( AI::SwitchLogicElement )
type->Property( "Case0", &AI::SwitchLogicElement::_CaseOutput0, XE::IMetaProperty::NoDesign );
type->Property( "Case1", &AI::SwitchLogicElement::_CaseOutput1, XE::IMetaProperty::NoDesign );
type->Property( "Case2", &AI::SwitchLogicElement::_CaseOutput2, XE::IMetaProperty::NoDesign );
type->Property( "Case3", &AI::SwitchLogicElement::_CaseOutput3, XE::IMetaProperty::NoDesign );
type->Property( "Case4", &AI::SwitchLogicElement::_CaseOutput4, XE::IMetaProperty::NoDesign );
type->Property( "Case5", &AI::SwitchLogicElement::_CaseOutput5, XE::IMetaProperty::NoDesign );
type->Property( "Case6", &AI::SwitchLogicElement::_CaseOutput6, XE::IMetaProperty::NoDesign );
type->Property( "Case7", &AI::SwitchLogicElement::_CaseOutput7, XE::IMetaProperty::NoDesign );
type->Property( "Case8", &AI::SwitchLogicElement::_CaseOutput8, XE::IMetaProperty::NoDesign );
type->Property( "Case9", &AI::SwitchLogicElement::_CaseOutput9, XE::IMetaProperty::NoDesign );
type->Property( "Default", &AI::SwitchLogicElement::_DefaultOutput, XE::IMetaProperty::NoDesign );
END_META()

AI::SwitchLogicElement::SwitchLogicElement()
{
	SetInputPort( XE::MakeShared<AI::IntegerInputPort>() );
}

AI::SwitchLogicElement::~SwitchLogicElement()
{

}

void AI::SwitchLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<AI::IntegerInputPort>( GetInputPort() );
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

BEG_META( AI::SequenceLogicElement )
type->Property( "Output0", &AI::SequenceLogicElement::_Output0, XE::IMetaProperty::NoDesign );
type->Property( "Output1", &AI::SequenceLogicElement::_Output1, XE::IMetaProperty::NoDesign );
type->Property( "Output2", &AI::SequenceLogicElement::_Output2, XE::IMetaProperty::NoDesign );
type->Property( "Output3", &AI::SequenceLogicElement::_Output3, XE::IMetaProperty::NoDesign );
type->Property( "Output4", &AI::SequenceLogicElement::_Output4, XE::IMetaProperty::NoDesign );
type->Property( "Output5", &AI::SequenceLogicElement::_Output5, XE::IMetaProperty::NoDesign );
type->Property( "Output6", &AI::SequenceLogicElement::_Output6, XE::IMetaProperty::NoDesign );
type->Property( "Output7", &AI::SequenceLogicElement::_Output7, XE::IMetaProperty::NoDesign );
type->Property( "Output8", &AI::SequenceLogicElement::_Output8, XE::IMetaProperty::NoDesign );
type->Property( "Output9", &AI::SequenceLogicElement::_Output9, XE::IMetaProperty::NoDesign );
END_META()

AI::SequenceLogicElement::SequenceLogicElement()
{

}

AI::SequenceLogicElement::~SequenceLogicElement()
{

}

void AI::SequenceLogicElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto input = SP_CAST<AI::IntegerInputPort>( GetInputPort() );

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

BEG_META( AI::EventElement )
type->Property( "ListenerEvent", &AI::EventElement::_ListenerEvent );
type->Property( "Output", &AI::EventElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

AI::EventElement::EventElement()
{
	SetType( AIElementType::EVENT_ELEMENET );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::EventElement::~EventElement()
{

}

XE::EventHandle AI::EventElement::GetListenerEvent() const
{
	return _ListenerEvent;
}

void AI::EventElement::SetListenerEvent( XE::EventHandle val )
{
	_ListenerEvent = val;
}

void AI::EventElement::OnExecute()
{
	auto blueprint = GetBlueprint();
	auto output = SP_CAST<AI::VariantOutputPort>( GetOutputPort() );

	if( _Output.Handle ) blueprint->GetElement( _Output.Handle )->Execute();

	output->Result.Reset();
}

BEG_META( AI::ActionElement )
type->Property( "MethodFullName", &AI::ActionElement::_MethodFullName );
type->Property( "Output", &AI::ActionElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

AI::ActionElement::ActionElement()
{
	SetType( AIElementType::ACTION_ELEMENET );

	SetInputPort( XE::MakeShared<AI::InvokeInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::ActionElement::~ActionElement()
{

}

const XE::String & AI::ActionElement::GetMethodFullName() const
{
	return _MethodFullName;
}

void AI::ActionElement::SetMethodFullName( const XE::String & val )
{
	_MethodFullName = val;
}

void AI::ActionElement::OnStartup()
{
	if( auto method = XE::Reflection::FindMethod( _MethodFullName ) )
	{
		auto input = SP_CAST<AI::InvokeInputPort>( GetInputPort() );
		input->Init( method );
	}
}

void AI::ActionElement::OnExecute()
{
	auto input = SP_CAST<AI::InvokeInputPort>( GetInputPort() );
	auto output = SP_CAST<AI::VariantOutputPort>( GetOutputPort() );

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

BEG_META( AI::VariableElement )
END_META()

AI::VariableElement::VariableElement()
{
	SetType( AIElementType::VARIABLE_ELEMENET );
}

AI::VariableElement::~VariableElement()
{

}

BEG_META( AI::SetVariableElement )
type->Property( "PropertyFullName", &AI::SetVariableElement::_PropertyFullName );
type->Property( "Output", &AI::SetVariableElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

AI::SetVariableElement::SetVariableElement()
{
	SetInputPort( XE::MakeShared<AI::SetVariableInputPort>() );
}

AI::SetVariableElement::~SetVariableElement()
{

}

const AI::AIOutput & AI::SetVariableElement::GetOutput() const
{
	return _Output;
}

void AI::SetVariableElement::SetOutput( const AI::AIOutput & val )
{
	_Output = val;
}

const XE::String & AI::SetVariableElement::GetPropertyFullName() const
{
	return _PropertyFullName;
}

void AI::SetVariableElement::SetPropertyFullName( const XE::String & val )
{
	_PropertyFullName = val;
}

void AI::SetVariableElement::OnExecute()
{
	auto input = SP_CAST<AI::SetVariableInputPort>( GetInputPort() );
	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		prop->Set( input->This, input->Value );
	}

	if( _Output.Handle ) GetBlueprint()->GetElement( _Output.Handle )->Execute();
}

BEG_META( AI::GetVariableElement )
type->Property( "PropertyFullName", &AI::GetVariableElement::_PropertyFullName );
END_META()

AI::GetVariableElement::GetVariableElement()
{
	SetInputPort( XE::MakeShared<AI::GetVariableInputPort>() );
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::GetVariableElement::~GetVariableElement()
{

}

const XE::String & AI::GetVariableElement::GetPropertyFullName() const
{
	return _PropertyFullName;
}

void AI::GetVariableElement::SetPropertyFullName( const XE::String & val )
{
	_PropertyFullName = val;
}

void AI::GetVariableElement::OnExecute()
{
	auto input = SP_CAST<AI::GetVariableInputPort>( GetInputPort() );
	auto output = SP_CAST<AI::VariantOutputPort>( GetOutputPort() );

	if( auto prop = XE::Reflection::FindProperty( _PropertyFullName ) )
	{
		output->Result = prop->Get( input->This );
	}
}

BEG_META( AI::SetBlackboardKeyElement )
type->Property( "BlackboardKey", &AI::SetBlackboardKeyElement::_BlackboardKey );
type->Property( "Output", &AI::SetBlackboardKeyElement::_Output, XE::IMetaProperty::NoDesign );
END_META()

AI::SetBlackboardKeyElement::SetBlackboardKeyElement()
{
	SetInputPort( XE::MakeShared<AI::VariantInputPort>() );
}

AI::SetBlackboardKeyElement::~SetBlackboardKeyElement()
{

}

const AI::AIOutput & AI::SetBlackboardKeyElement::GetOutput() const
{
	return _Output;
}

void AI::SetBlackboardKeyElement::SetOutput( const AI::AIOutput & val )
{
	_Output = val;
}

const AI::BlackboardKey & AI::SetBlackboardKeyElement::GetBlackboardKey() const
{
	return _BlackboardKey;
}

void AI::SetBlackboardKeyElement::SetBlackboardKey( const AI::BlackboardKey & val )
{
	_BlackboardKey = val;
}

void AI::SetBlackboardKeyElement::OnExecute()
{
	auto input = SP_CAST<AI::VariantInputPort>( GetInputPort() );

	GetBlueprint()->SetKey( _BlackboardKey, input->Value );

	if( _Output.Handle ) GetBlueprint()->GetElement( _Output.Handle )->Execute();
}

BEG_META( AI::GetBlackboardKeyElement )
type->Property( "BlackboardKey", &AI::GetBlackboardKeyElement::_BlackboardKey );
END_META()

AI::GetBlackboardKeyElement::GetBlackboardKeyElement()
{
	SetOutputPort( XE::MakeShared<AI::VariantOutputPort>() );
}

AI::GetBlackboardKeyElement::~GetBlackboardKeyElement()
{

}

const AI::BlackboardKey & AI::GetBlackboardKeyElement::GetBlackboardKey() const
{
	return _BlackboardKey;
}

void AI::GetBlackboardKeyElement::SetBlackboardKey( const AI::BlackboardKey & val )
{
	_BlackboardKey = val;
}

void AI::GetBlackboardKeyElement::OnExecute()
{
	auto output = SP_CAST<AI::VariantOutputPort>( GetOutputPort() );

	 output->Result = GetBlueprint()->GetKey( _BlackboardKey );
}
