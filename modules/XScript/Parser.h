/*!
 * \file	Parser.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PARSER_H__371E59F2_4FF4_41A3_B76F_28F7AC32B2E8
#define PARSER_H__371E59F2_4FF4_41A3_B76F_28F7AC32B2E8

#include "Lexer.h"
#include "ASTNode.h"

BEG_XE_NAMESPACE

class Parser
{
public:
	Parser( const std::string & src );

	Parser( const XE::FileSystem::path & path, const std::string & src );

	~Parser();

public:
	ModuleNodePtr ParseModule();

private:
	UsingNodePtr ParseUsing();

	ImportNodePtr ParseImport();

private:
	EnumNodePtr ParseEnum();
		 
	ClassNodePtr ParseClass();
		
private:
	MethodNodePtr ParseMethod();

	OperatorNodePtr ParseOperator();

	PropertyNodePtr ParseProperty();

private:
	StatementNodePtr ParseStatement();

	BlockNodePtr ParseBlock();

	IfNodePtr ParseIf();

	ForNodePtr ParseFor();

	WhileNodePtr ParseWhile();

	SwitchNodePtr ParseSwitch();

	CaseNodePtr ParseCase();

	DefaultNodePtr ParseDefault();

	BreakNodePtr ParseBreak();

	ContinueNodePtr ParseContinue();

	ReturnNodePtr ParseReturn();

	ExpressionNodePtr ParseExpression();

	ExpressionNodePtr ParseExprRelation();

	ExpressionNodePtr ParseExprShiftition();

	ExpressionNodePtr ParseExprAddition();

	ExpressionNodePtr ParseExprMultiplication();

	ExpressionNodePtr ParseExprUnary2();

	ExpressionNodePtr ParseExprUnary1();

	ExpressionNodePtr ParseExprFactor();

	ExprArgumentNodePtr ParseArgument();

	ExprVariableNodePtr ParseExprVariable();

	ExprCloseureNodePtr ParseExprCloseure();

private:
	bool Look( TokenType val ) noexcept;

	bool Skip( TokenType val ) noexcept;

	void Ignore( TokenType val );

	const Token & Check( TokenType val );

private:
	Lexer _Lex;
	XE::FileSystem::path _Path;
};

END_XE_NAMESPACE

#endif // PARSER_H__371E59F2_4FF4_41A3_B76F_28F7AC32B2E8
