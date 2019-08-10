/*!
 * \file	ASTNode.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASTNODE_H__3BC198E8_3EE1_413F_840E_E5BCD8712A1D
#define ASTNODE_H__3BC198E8_3EE1_413F_840E_E5BCD8712A1D

#include "Type.h"

BEG_XE_NAMESPACE

class ASTNode
{
public:
	virtual void GenCode( Codegen & val ) = 0;
};

class ImportNode : public ASTNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Str;
};

class UsingNode : public ASTNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Name;
};


class MetaNode : public ASTNode
{
public:
	XE::String Name;
};

class ModuleNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<UsingNodePtr> Usings;
	Array<ImportNodePtr> Imports;
	Array<EnumNodePtr> Enums;
	Array<ClassNodePtr> Classes;
};

class EnumNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<XE::String> Values;
};

class ClassNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Super;
	Array<EnumNodePtr> Enums;
	Array<ClassNodePtr> Classes;
	Array<MethodNodePtr> Methods;
	Array<OperatorNodePtr> Operators;
	Array<PropertyNodePtr> Propertys;
};

class MethodNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<XE::String> Params;
	BlockNodePtr Block;
};

class OperatorNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<XE::String> Params;
	BlockNodePtr Block;
};

class PropertyNode : public MetaNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr InitExpr;
};


class StatementNode : public ASTNode
{
};

class BlockNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<StatementNodePtr> Statements;
};

class IfNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Expr;
	BlockNodePtr Block;
	BlockNodePtr ElseBlock;
};

class ForNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	StatementNodePtr Statement;
	ExpressionNodePtr Expr;
	ExpressionNodePtr Iter;
	BlockNodePtr Block;
};

class WhileNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Expr;
	BlockNodePtr Block;
};

class SwitchNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Expr;
	Array<CaseNodePtr> Cases;
	DefaultNodePtr Default;
};

class CaseNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	StatementNodePtr Stat;
	BlockNodePtr Block;
};

class DefaultNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	BlockNodePtr Block;
};

class BreakNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;
};

class ContinueNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;
};

class ReturnNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Expr;
};

class NewNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Type;
};

class SizeofNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Value;
};

class TypeofNode : public StatementNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Value;
};


class ExpressionNode : public StatementNode
{
};

class ExprUnaryNode : public ExpressionNode
{
public:
	enum class UnaryType
	{
		NOT,					// !
		REVE,					// ~
		ADDADD,					// ++
		SUBSUB,					// --
	};

public:
	static UnaryType TokenTypeToUnaryType( TokenType val );

public:
	void GenCode( Codegen & val ) override;

public:
	UnaryType Type;
	ExpressionNodePtr Expr;
};

class ExprBinaryNode : public ExpressionNode
{
public:
	enum class BinaryType
	{
		DOT,					// .
		MUL,					// *
		DIV,					// /
		MOD,					// %
		ADD,					// +
		SUB,					// -
		L_SHFIT,				// <<
		R_SHFIT,				// >>
		GREA,					// <
		GREA_EQUAL,				// <=
		LESS,					// >
		LESS_EQUAL,				// >=
		EQUAL,					// ==
		NOT_EQUAL,				// !=
		B_AND,					// &
		B_XOR,					// ^
		B_OR,					// |
		L_AND,					// &&
		L_OR,					// ||
		ASSIGN, 				// =
		MUL_ASSIGN,				// *=
		DIV_ASSIGN,				// /=
		MOD_ASSIGN,				// %=
		ADD_ASSIGN,				// +=
		SUB_ASSIGN,				// -=
		AND_ASSIGN,				// &=
		XOR_ASSIGN,				// ^=
		OR_ASSIGN,				// |=
		L_SHFIT_ASSIGN,			// <<=
		R_SHFIT_ASSIGN,			// >>=
	};

public:
	static BinaryType TokenTypeToBinaryType( TokenType val );

public:
	void GenCode( Codegen & val ) override;

public:
	BinaryType Type;
	ExpressionNodePtr Left;
	ExpressionNodePtr Right;
};

class NilNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;
};

class IntNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::int32 Data;
};

class BoolNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	bool Data;
};

class FloatNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::float32 Data;
};

class StringNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Data;
};

class ExprVariableNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::String Name;
};

class ExprIndexNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Variable;
	ExpressionNodePtr Expr;
};

class ExprVisitNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Variable;
	ExpressionNodePtr Property;
};

class ExprCallbackNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	ExpressionNodePtr Variable;
	ExprArgumentNodePtr Argument;
};

class ExprCloseureNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	XE::uint64 Index;
	Array<XE::String> Params;
	BlockNodePtr Block;
};

class ExprArgumentNode : public ExpressionNode
{
public:
	void GenCode( Codegen & val ) override;

public:
	Array<ExpressionNodePtr> Argument;
};


END_XE_NAMESPACE

#endif // ASTNODE_H__3BC198E8_3EE1_413F_840E_E5BCD8712A1D
