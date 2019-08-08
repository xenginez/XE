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

#include "AST.h"
#include "Lexer.h"

BEG_XE_NAMESPACE

class XSCRIPT_API Parser
{
public:
	Parser( InterpreterPtr inter, const std::string & src );

	Parser( InterpreterPtr inter, const std::filesystem::path & path, const std::string & src );

	~Parser();

public:
	const AST & GetAST() const;

public:
	const AST & Parse();

private:
	void Using();

	void Import();

private:
	void ParseEnum();
		 
	void ParseClass();
		 
	void ParseMethod();
		 
	void ParseProperty();

	void ParseOperator();

private:
	void ParseBlock();

	void ParseStatement();

	void ParseVariable();

	void ParseIf();

	void ParseFor();

	void ParseWhile();

	void ParseSwitch();

	void ParseCase();

	void ParseDefault();

	void ParseBreak();

	void ParseContinue();

	void ParseReturn();

	void ParseCloseure();

	void ParseExpression();

	void ParseExprRelation();

	void ParseExprShiftition();

	void ParseExprAddition();

	void ParseExprMultiplication();

	void ParseUnary1();

	void ParseUnary2();

	void ParseFactor();

private:
	void ParseArgsList();

private:
	bool Look( TokenType val ) noexcept;

	bool Skip( TokenType val ) noexcept;

	void Ignore( TokenType val );

	const Token & Check( TokenType val );

private:
	AST _Ast;
	Lexer _Lex;
	InterpreterWPtr _Inter;
	std::filesystem::path _Path;
};

END_XE_NAMESPACE

#endif // PARSER_H__371E59F2_4FF4_41A3_B76F_28F7AC32B2E8
