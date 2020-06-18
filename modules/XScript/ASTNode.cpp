#include "ASTNode.h"

#include "Codegen.h"



ExprUnaryNode::UnaryType ExprUnaryNode::TokenTypeToUnaryType( TokenType val )
{
	switch( val )
	{
	case XE::TokenType::NOT:
		return UnaryType::NOT;
	case XE::TokenType::REVE:
		return UnaryType::REVE;
	case XE::TokenType::ADDADD:
		return UnaryType::ADDADD;
	case XE::TokenType::SUBSUB:
		return UnaryType::SUBSUB;
	}

	throw XE::RuntimeException();
}

ExprBinaryNode::BinaryType ExprBinaryNode::TokenTypeToBinaryType( TokenType val )
{
	switch( val )
	{
	case XE::TokenType::DOT:
		return BinaryType::DOT;
	case XE::TokenType::MUL:
		return BinaryType::MUL;
	case XE::TokenType::DIV:
		return BinaryType::DIV;
	case XE::TokenType::MOD:
		return BinaryType::MOD;
	case XE::TokenType::ADD:
		return BinaryType::ADD;
	case XE::TokenType::SUB:
		return BinaryType::SUB;
	case XE::TokenType::L_SHFIT:
		return BinaryType::L_SHFIT;
	case XE::TokenType::R_SHFIT:
		return BinaryType::R_SHFIT;
	case XE::TokenType::GREA:
		return BinaryType::GREA;
	case XE::TokenType::GREA_EQUAL:
		return BinaryType::GREA_EQUAL;
	case XE::TokenType::LESS:
		return BinaryType::LESS;
	case XE::TokenType::LESS_EQUAL:
		return BinaryType::LESS_EQUAL;
	case XE::TokenType::EQUAL:
		return BinaryType::EQUAL;
	case XE::TokenType::NOT_EQUAL:
		return BinaryType::NOT_EQUAL;
	case XE::TokenType::B_AND:
		return BinaryType::B_AND;
	case XE::TokenType::B_XOR:
		return BinaryType::B_XOR;
	case XE::TokenType::B_OR:
		return BinaryType::B_OR;
	case XE::TokenType::L_AND:
		return BinaryType::L_AND;
	case XE::TokenType::L_OR:
		return BinaryType::L_OR;
	case XE::TokenType::ASSIGN:
		return BinaryType::ASSIGN;
	case XE::TokenType::MUL_ASSIGN:
		return BinaryType::MUL_ASSIGN;
	case XE::TokenType::DIV_ASSIGN:
		return BinaryType::DIV_ASSIGN;
	case XE::TokenType::MOD_ASSIGN:
		return BinaryType::MOD_ASSIGN;
	case XE::TokenType::ADD_ASSIGN:
		return BinaryType::ADD_ASSIGN;
	case XE::TokenType::SUB_ASSIGN:
		return BinaryType::SUB_ASSIGN;
	case XE::TokenType::AND_ASSIGN:
		return BinaryType::AND_ASSIGN;
	case XE::TokenType::XOR_ASSIGN:
		return BinaryType::XOR_ASSIGN;
	case XE::TokenType::OR_ASSIGN:
		return BinaryType::OR_ASSIGN;
	case XE::TokenType::L_SHFIT_ASSIGN:
		return BinaryType::L_SHFIT_ASSIGN;
	case XE::TokenType::R_SHFIT_ASSIGN:
		return BinaryType::R_SHFIT_ASSIGN;
	}

	throw XE::RuntimeException();
}


void ImportNode::GenCode( Codegen & val )
{

}

void UsingNode::GenCode( Codegen & val )
{

}

void ModuleNode::GenCode( Codegen & val )
{

}

void EnumNode::GenCode( Codegen & val )
{

}

void ClassNode::GenCode( Codegen & val )
{

}

void MethodNode::GenCode( Codegen & val )
{

}

void OperatorNode::GenCode( Codegen & val )
{

}

void PropertyNode::GenCode( Codegen & val )
{

}

void BlockNode::GenCode( Codegen & val )
{

}

void IfNode::GenCode( Codegen & val )
{

}

void ForNode::GenCode( Codegen & val )
{

}

void WhileNode::GenCode( Codegen & val )
{

}

void SwitchNode::GenCode( Codegen & val )
{

}

void CaseNode::GenCode( Codegen & val )
{

}

void DefaultNode::GenCode( Codegen & val )
{

}

void BreakNode::GenCode( Codegen & val )
{

}

void ContinueNode::GenCode( Codegen & val )
{

}

void ReturnNode::GenCode( Codegen & val )
{

}

void NewNode::GenCode( Codegen & val )
{

}

void SizeofNode::GenCode( Codegen & val )
{

}

void TypeofNode::GenCode( Codegen & val )
{

}

void ExprUnaryNode::GenCode( Codegen & val )
{

}

void ExprBinaryNode::GenCode( Codegen & val )
{

}

void NilNode::GenCode( Codegen & val )
{

}

void IntNode::GenCode( Codegen & val )
{

}

void BoolNode::GenCode( Codegen & val )
{

}

void FloatNode::GenCode( Codegen & val )
{

}

void StringNode::GenCode( Codegen & val )
{

}

void ExprVariableNode::GenCode( Codegen & val )
{

}

void ExprIndexNode::GenCode( Codegen & val )
{

}

void ExprVisitNode::GenCode( Codegen & val )
{

}

void ExprCallbackNode::GenCode( Codegen & val )
{

}

void ExprCloseureNode::GenCode( Codegen & val )
{

}

void ExprArgumentNode::GenCode( Codegen & val )
{

}
