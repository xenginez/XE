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

/// LLVM Instruction
enum class InstructType
{
//	Terminator Instructions
	RET,
	BR,
	SWITCH,
	INDIRECTBR,
	INVOKE,
	RESUME,
	UNREACHABLE,
	CLEANUPRET,
	CATCHRET,
	CATCHSWITCH,
	CALLBR,

//	Standard unary operators
	FNEG,

//	Standard binary operators
	ADD,
	FADD,
	SUB,
	FSUB,
	MUL,
	FMUL,
	UDIV,
	SDIV,
	FDIV,
	UREM,
	SREM,
	FREM,

//	Logical operators
	SHL,
	LSHR,
	ASHR,
	AND,
	OR,
	XOR,

//	Memory operators
	ALLOCA,
	LOAD,
	STORE,
	GETELEMENTPTR,
	FENCE,
	ATOMICCMPXCHG,
	ATOMICRMW,

//	Cast operators
	TRUNC,
	ZEXT,
	SEXT,
	FPTOUI,
	FPTOSI,
	UITOFP,
	SITOFP,
	FPTRUNC,
	FPEXT,
	PTRTOINT,
	INTTOPTR,
	BITCAST,
	ADDRSPACECAST,
	CLEANUPPAD,
	CATCHPAD,

//	Other operators
	ICMP,
	FCMP,
	PHI,
	CALL,
	SELECT,
	USEROP1,
	USEROP2,
	VAARG,
	EXTRACTELEMENT,
	INSERTELEMENT,
	SHUFFLEVECTOR,
	EXTRACTVALUE,
	INSERTVALUE,
	LANDINGPAD,
};

/*

/// WebAssembly Instruction
enum class InstructType : XE::uint8
{
//	control flow operators
	UNREACHABLE			= 0x00,
	NOP					= 0x01,
	BLOCK				= 0x02,
	LOOP				= 0x03,
	IF					= 0x04,
	ELSE				= 0x05,
	END					= 0x0b,
	BR					= 0x0c,
	BR_IF				= 0x0d,
	BR_TABLE			= 0x0e,
	RETURN				= 0x0f,

//	call operators
	CALL				= 0x10,
	CALL_INDIRECT		= 0x11,

//	parametric operators
	DROP				= 0x1a,
	SELECT				= 0x1b,

//	variable access
	GET_LOCAL			= 0x20,
	SET_LOCAL			= 0x21,
	TEE_LOCAL			= 0x22,
	GET_GLOBAL			= 0x23,
	SET_GLOBAL			= 0x24,

//	memory related operators
	I32_LOAD			= 0x28,
	I64_LOAD			= 0x29,
	F32_LOAD			= 0x2a,
	F64_LOAD			= 0x2b,
	I32_LOAD8_S			= 0x2c,
	I32_LOAD8_U			= 0x2d,
	I32_LOAD16_S		= 0x2e,
	I32_LOAD16_U		= 0x2f,
	I64_LOAD8_S			= 0x30,
	I64_LOAD8_U			= 0x31,
	I64_LOAD16_S		= 0x32,
	I64_LOAD16_U		= 0x33,
	I64_LOAD32_S		= 0x34,
	I64_LOAD32_U		= 0x35,
	I32_STORE			= 0x36,
	I64_STORE			= 0x37,
	F32_STORE			= 0x38,
	F64_STORE			= 0x39,
	I32_STORE8			= 0x3a,
	I32_STORE16			= 0x3b,
	I64_STORE8			= 0x3c,
	I64_STORE16			= 0x3d,
	I64_STORE32			= 0x3e,
	CURRENT_MEMORY		= 0x3f,
	GROW_MEMORY			= 0x40,
	
//	constants
	I32_CONST			= 0x41,
	I64_CONST			= 0x42,
	F32_CONST			= 0x43,
	F64_CONST			= 0x44,

//	comparison operators
	I32_EQZ				= 0x45,
	I32_EQ				= 0x46,
	I32_NE				= 0x47,
	I32_LT_S			= 0x48,
	I32_LT_U			= 0x49,
	I32_GT_S			= 0x4a,
	I32_GT_U			= 0x4b,
	I32_LE_S			= 0x4c,
	I32_LE_U			= 0x4d,
	I32_GE_S			= 0x4e,
	I32_GE_U			= 0x4f,
	I64_EQZ				= 0x50,
	I64_EQ				= 0x51,
	I64_NE				= 0x52,
	I64_LT_S			= 0x53,
	I64_LT_U			= 0x54,
	I64_GT_S			= 0x55,
	I64_GT_U			= 0x56,
	I64_LE_S			= 0x57,
	I64_LE_U			= 0x58,
	I64_GE_S			= 0x59,
	I64_GE_U			= 0x5a,
	F32_EQ				= 0x5b,
	F32_NE				= 0x5c,
	F32_LT				= 0x5d,
	F32_GT				= 0x5e,
	F32_LE				= 0x5f,
	F32_GE				= 0x60,
	F64_EQ				= 0x61,
	F64_NE				= 0x62,
	F64_LT				= 0x63,
	F64_GT				= 0x64,
	F64_LE				= 0x65,
	F64_GE				= 0x66,

//	numeric operators
	I32_CLZ				= 0x67,
	I32_CTZ				= 0x68,
	I32_POPCNT			= 0x69,
	I32_ADD				= 0x6a,
	I32_SUB				= 0x6b,
	I32_MUL				= 0x6c,
	I32_DIV_S			= 0x6d,
	I32_DIV_U			= 0x6e,
	I32_REM_S			= 0x6f,
	I32_REM_U			= 0x70,
	I32_AND				= 0x71,
	I32_OR				= 0x72,
	I32_XOR				= 0x73,
	I32_SHL				= 0x74,
	I32_SHR_S			= 0x75,
	I32_SHR_U			= 0x76,
	I32_ROTL			= 0x77,
	I32_ROTR			= 0x78,
	I64_CLZ				= 0x79,
	I64_CTZ				= 0x7a,
	I64_POPCNT			= 0x7b,
	I64_ADD				= 0x7c,
	I64_SUB				= 0x7d,
	I64_MUL				= 0x7e,
	I64_DIV_S			= 0x7f,
	I64_DIV_U			= 0x80,
	I64_REM_S			= 0x81,
	I64_REM_U			= 0x82,
	I64_AND				= 0x83,
	I64_OR				= 0x84,
	I64_XOR				= 0x85,
	I64_SHL				= 0x86,
	I64_SHR_S			= 0x87,
	I64_SHR_U			= 0x88,
	I64_ROTL			= 0x89,
	I64_ROTR			= 0x8a,
	F32_ABS				= 0x8b,
	F32_NEG				= 0x8c,
	F32_CEIL			= 0x8d,
	F32_FLOOR			= 0x8e,
	F32_TRUNC			= 0x8f,
	F32_NEAREST			= 0x90,
	F32_SQRT			= 0x91,
	F32_ADD				= 0x92,
	F32_SUB				= 0x93,
	F32_MUL				= 0x94,
	F32_DIV				= 0x95,
	F32_MIN				= 0x96,
	F32_MAX				= 0x97,
	F32_COPYSIGN		= 0x98,
	F64_ABS				= 0x99,
	F64_NEG				= 0x9a,
	F64_CEIL			= 0x9b,
	F64_FLOOR			= 0x9c,
	F64_TRUNC			= 0x9d,
	F64_NEAREST			= 0x9e,
	F64_SQRT			= 0x9f,
	F64_ADD				= 0xa0,
	F64_SUB				= 0xa1,
	F64_MUL				= 0xa2,
	F64_DIV				= 0xa3,
	F64_MIN				= 0xa4,
	F64_MAX				= 0xa5,
	F64_COPYSIGN		= 0xa6,

//	conversions
	I32_WRAP_I64		= 0xa7,
	I32_TRUNC_S_F32		= 0xa8,
	I32_TRUNC_U_F32		= 0xa9,
	I32_TRUNC_S_F64		= 0xaa,
	I32_TRUNC_U_F64		= 0xab,
	I64_EXTEND_S_I32	= 0xac,
	I64_EXTEND_U_I32	= 0xad,
	I64_TRUNC_S_F32		= 0xae,
	I64_TRUNC_U_F32		= 0xaf,
	I64_TRUNC_S_F64		= 0xb0,
	I64_TRUNC_U_F64		= 0xb1,
	F32_CONVERT_S_I32	= 0xb2,
	F32_CONVERT_U_I32	= 0xb3,
	F32_CONVERT_S_I64	= 0xb4,
	F32_CONVERT_U_I64	= 0xb5,
	F32_DEMOTE_F64		= 0xb6,
	F64_CONVERT_S_I32	= 0xb7,
	F64_CONVERT_U_I32	= 0xb8,
	F64_CONVERT_S_I64	= 0xb9,
	F64_CONVERT_U_I64	= 0xba,
	F64_PROMOTE_F32		= 0xbb,

//	reinterpretations
	I32_REINTERPRET_F32	= 0xbc,
	I64_REINTERPRET_F64	= 0xbd,
	F32_REINTERPRET_I32	= 0xbe,
	F64_REINTERPRET_I64	= 0xbf,
};
*/
END_XE_NAMESPACE

#endif // TYPE_H__07888413_7FA0_4779_9F78_3885B25018B0
