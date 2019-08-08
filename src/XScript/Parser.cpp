#include "Parser.h"

#include "XSMetaEnum.h"
#include "XSMetaClass.h"
#include "XSMetaMethod.h"
#include "XSMetaOperator.h"
#include "XSMetaProperty.h"

#include "Interpreter.h"

USING_XE

XE::Parser::Parser( InterpreterPtr inter, const std::string & src )
	: _Lex( src ), _Ast( "" ), _Path( std::filesystem::current_path() ), _Inter( inter )
{

}

XE::Parser::Parser( InterpreterPtr inter, const std::filesystem::path & path, const std::string & src )
	: _Lex( src ), _Ast( path.stem().string() ), _Path( path ), _Inter( inter )
{

}

XE::Parser::~Parser()
{

}

const XE::AST & XE::Parser::GetAST() const
{
	return _Ast;
}

const XE::AST & XE::Parser::Parse()
{
	while( _Lex.LookToken()._Token != TokenType::UNKNOWN )
	{
		switch( _Lex.LookToken()._Token )
		{
		case TokenType::IMPORT:
			Import();
			break;
		case TokenType::USING:
			Using();
			break;
		case TokenType::ENUM:
			ParseEnum();
			break;
		case TokenType::CLASS:
			ParseClass();
			break;
		default:
			throw XE::RuntimeException();
			break;
		}
	}

	return _Ast;
}

void XE::Parser::Using()
{
	Ignore( TokenType::USING );

	_Ast.AddUsing( Check( TokenType::IDENTIFIER )._Value );
}

void XE::Parser::Import()
{
	Ignore( TokenType::IMPORT );

	_Inter.lock()->LoadScript( _Path / Check( TokenType::IDENTIFIER )._Value );
}

void XE::Parser::ParseEnum()
{
	Ignore( TokenType::ENUM );

	auto enu = _Ast.AddEnum( Check( TokenType::IDENTIFIER )._Value );

	XE::int64 index = 0;

	Ignore( TokenType::LBRACE );

	do
	{
		enu->Value( Check( TokenType::IDENTIFIER )._Value, index++ );
	} while( !Skip( TokenType::COMMA ) );

	Ignore( TokenType::RBRACE );
}
				 
void XE::Parser::ParseClass()
{
	Ignore( TokenType::CLASS );

	std::string name = Check( TokenType::IDENTIFIER )._Value;
	std::string base;
	if( Skip( TokenType::COLON ) )
	{
		base = Check( TokenType::IDENTIFIER )._Value;
	}

	auto cls = _Ast.AddClass( name, base );

	Ignore( TokenType::LBRACE );

	do 
	{
		switch( _Lex.LookToken()._Token )
		{
		case TokenType::FUNCTION:
			ParseMethod();
			break;
		case TokenType::OPERATOR:
			ParseOperator();
			break;
		case TokenType::VARIABLE:
			ParseProperty();
			break;
		case TokenType::SEMICOLON:
			Ignore( TokenType::SEMICOLON );
		default:
			throw XE::RuntimeException();
			break;
		}
	} while (!Look(TokenType::RBRACE));

	Ignore( TokenType::RBRACE );
}

void XE::Parser::ParseMethod()
{
	Ignore( TokenType::FUNCTION );

	std::string name = Check( TokenType::IDENTIFIER )._Value;
	List<std::string> params;

	Ignore( TokenType::LPAREN );

	while( !Look(TokenType::RPAREN) )
	{
		params.emplace_back( Check( TokenType::IDENTIFIER )._Value );
		
		if( !Skip( TokenType::COMMA ) && !Look(TokenType::RPAREN) )
		{
			throw XE::RuntimeException();
		}
	}

	Ignore( TokenType::RPAREN );

	_Ast.AddMethod( name, std::move( params ) );

	ParseBlock();
}
				 
void XE::Parser::ParseOperator()
{
	Ignore( TokenType::OPERATOR );

	std::string name;
	List<std::string> params;

	if( !Look( TokenType::ADD ) || !Look( TokenType::MUL ) || !Look( TokenType::DIV ) ||
		!Look( TokenType::MOD ) || !Look( TokenType::ADD ) || !Look( TokenType::SUB ) ||
		!Look( TokenType::L_SHFIT ) || !Look( TokenType::R_SHFIT ) || !Look( TokenType::GREA ) ||
		!Look( TokenType::GREA_EQUAL ) || !Look( TokenType::LESS ) || !Look( TokenType::LESS_EQUAL ) ||
		!Look( TokenType::EQUAL ) || !Look( TokenType::NOT_EQUAL ) || !Look( TokenType::B_AND ) ||
		!Look( TokenType::B_XOR ) || !Look( TokenType::B_OR ) || !Look( TokenType::L_AND ) ||
		!Look( TokenType::L_OR ) || !Look( TokenType::ASSIGN ) || !Look( TokenType::MUL_ASSIGN ) ||
		!Look( TokenType::DIV_ASSIGN ) || !Look( TokenType::MOD_ASSIGN ) || !Look( TokenType::ADD_ASSIGN ) ||
		!Look( TokenType::SUB_ASSIGN ) || !Look( TokenType::AND_ASSIGN ) || !Look( TokenType::XOR_ASSIGN ) ||
		!Look( TokenType::OR_ASSIGN ) || !Look( TokenType::L_SHFIT_ASSIGN ) || !Look( TokenType::R_SHFIT_ASSIGN ) 
	)
	{
		name = Token::TypeToString( _Lex.LookToken()._Token );
	}

	Ignore( TokenType::LPAREN );

	while( !Look( TokenType::RPAREN ) )
	{
		params.emplace_back( Check( TokenType::IDENTIFIER )._Value );

		if( !Skip( TokenType::COMMA ) && !Look( TokenType::RPAREN ) )
		{
			throw XE::RuntimeException();
		}
	}

	Ignore( TokenType::RPAREN );

	_Ast.AddMethod( name, std::move( params ) );

	ParseBlock();
}
				 
void XE::Parser::ParseProperty()
{
	Ignore( TokenType::VARIABLE );

	auto prop = _Ast.AddProperty( Check( TokenType::IDENTIFIER )._Value );

	if( Skip( TokenType::ASSIGN ) )
	{
		ParseStatement();
	}
}

void XE::Parser::ParseBlock()
{
	Ignore( TokenType::LBRACE );

	_Ast.PushBlock();

	while( !Look( TokenType::RBRACE ) )
	{
		ParseStatement();
	}

	_Ast.PopBlock();

	Ignore( TokenType::RBRACE );
}

void XE::Parser::ParseStatement()
{
	switch( _Lex.LookToken()._Token )
	{
	case TokenType::VARIABLE:
		ParseVariable();
		break;
	case TokenType::IF:
		ParseIf();
		break;
	case TokenType::FOR:
		ParseFor();
		break;
	case TokenType::WHILE:
		ParseWhile();
		break;
	case TokenType::SWITCH:
		ParseSwitch();
		break;
	case TokenType::BREAK:
		ParseBreak();
		break;
	case TokenType::CONTINUE:
		ParseContinue();
		break;
	case TokenType::RETURN:
		ParseReturn();
		break;
	case TokenType::FUNCTION:
		ParseCloseure();
		break;
	case TokenType::SEMICOLON:
		Ignore( TokenType::SEMICOLON );
		break;
	default:
		ParseExpression();
		break;
	}
}

void XE::Parser::ParseVariable()
{

}

void XE::Parser::ParseIf()
{

}

void XE::Parser::ParseFor()
{

}

void XE::Parser::ParseWhile()
{

}

void XE::Parser::ParseSwitch()
{

}

void XE::Parser::ParseCase()
{

}

void XE::Parser::ParseDefault()
{

}

void XE::Parser::ParseBreak()
{

}

void XE::Parser::ParseContinue()
{

}

void XE::Parser::ParseReturn()
{

}

void XE::Parser::ParseCloseure()
{

}

void XE::Parser::ParseExpression()
{

}

void XE::Parser::ParseExprRelation()
{

}

void XE::Parser::ParseExprShiftition()
{

}

void XE::Parser::ParseExprAddition()
{

}

void XE::Parser::ParseExprMultiplication()
{

}

void XE::Parser::ParseUnary1()
{

}

void XE::Parser::ParseUnary2()
{

}

void XE::Parser::ParseFactor()
{

}

void XE::Parser::ParseArgsList()
{

}

bool XE::Parser::Look( TokenType val ) noexcept
{
	return _Lex.LookToken()._Token == val;
}

bool XE::Parser::Skip( TokenType val ) noexcept
{
	if( _Lex.LookToken()._Token == val )
	{
		_Lex.NextToken();
		return true;
	}

	return false;
}

void XE::Parser::Ignore( TokenType val )
{
	if( _Lex.LookToken()._Token == val )
	{
		_Lex.NextToken();
	}

	throw XE::RuntimeException();
}

const XE::Token & XE::Parser::Check( TokenType val )
{
	if( _Lex.LookToken()._Token == val )
	{
		return _Lex.NextToken();
	}

	throw XE::RuntimeException();
}
