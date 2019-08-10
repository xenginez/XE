/*!
 * \file	Type.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TYPE_H__07888413_7FA0_4779_9F78_3885B25018B0
#define TYPE_H__07888413_7FA0_4779_9F78_3885B25018B0

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( Codegen );
DECL_PTR( Interpreter );
DECL_PTR( XSMetaEnum );
DECL_PTR( XSMetaClass );
DECL_PTR( XSMetaMethod );
DECL_PTR( XSMetaOperator );
DECL_PTR( XSMetaProperty );

DECL_PTR( ASTNode );
DECL_PTR( ImportNode );
DECL_PTR( UsingNode );
DECL_PTR( ModuleNode );
DECL_PTR( EnumNode );
DECL_PTR( ClassNode );
DECL_PTR( MethodNode );
DECL_PTR( OperatorNode );
DECL_PTR( PropertyNode );
DECL_PTR( StatementNode );
DECL_PTR( NilNode );
DECL_PTR( IntNode );
DECL_PTR( BoolNode );
DECL_PTR( FloatNode );
DECL_PTR( StringNode );
DECL_PTR( BlockNode );
DECL_PTR( IfNode );
DECL_PTR( ForNode );
DECL_PTR( WhileNode );
DECL_PTR( SwitchNode );
DECL_PTR( CaseNode );
DECL_PTR( DefaultNode );
DECL_PTR( BreakNode );
DECL_PTR( ContinueNode );
DECL_PTR( ReturnNode );
DECL_PTR( NewNode );
DECL_PTR( SizeofNode );
DECL_PTR( TypeofNode );
DECL_PTR( ExpressionNode );
DECL_PTR( ExprUnaryNode );
DECL_PTR( ExprBinaryNode );
DECL_PTR( ExprVariableNode );
DECL_PTR( ExprCloseureNode );
DECL_PTR( ExprArgumentNode );


enum class TokenType
{
	UNKNOWN = 0,

	TYPE_BEG,
	INT = TYPE_BEG,
	VOID,
	BOOL,
	FLOAT,
	STRING,
	IDENTIFIER,
	TYPE_END = IDENTIFIER,

	VALUE_BEG,
	NIL = VALUE_BEG,
	TRUE,
	FALSE,
	INT_CONST,
	FLOAT_CONST,
	STRING_CONST,
	VALUE_END = STRING_CONST,

	KEYWORD_BEG,
	IF = KEYWORD_BEG,		// if
	ELSE,					// else
	FOR,					// for
	WHILE,					// while
	SWITCH,					// switch
	CASE,					// case
	DEFAULT,				// default
	BREAK,					// break
	CONTINUE,				// continue
	RETURN,					// return
	ENUM,					// enum
	CLASS,					// class
	OPERATOR,				// operator
	FUNCTION,				// function
	VARIABLE,				// variable
	IMPORT,					// import
	USING,					// using
	THIS,					// this
	SUPER,					// super
	KEYAORD_END = SUPER,

	UNARY_BEG,
	NEW = UNARY_BEG,		// new
	DELETE,					// delete
	SIZEOF,					// sizeof
	TYPEOF,					// typeof
	NOT,					// !
	REVE,					// ~
	ADDADD,					// ++
	SUBSUB,					// --
	UNARY_END = SUBSUB,

	SPE_BEG,
	LBRACE = SPE_BEG,		// {
	RBRACE,					// }
	LPAREN,					// (
	RPAREN,					// )
	LBRACKET,				// [
	RBRACKET,				// ]
	SEMICOLON,				// ;
	COLON,					// :
	COMMA,					// ,
	SPE_END = COMMA,

	BINARY_BEG,
	DOT = BINARY_BEG,		// .
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
	BINARY_END = R_SHFIT_ASSIGN,
};

END_XE_NAMESPACE

#endif // TYPE_H__07888413_7FA0_4779_9F78_3885B25018B0
