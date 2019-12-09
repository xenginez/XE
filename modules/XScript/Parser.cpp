#include "Parser.h"

USING_XE

Parser::Parser( const std::string & src )
	:_Lex( src ), _Path( std::filesystem::current_path() )
{

}

Parser::Parser( const std::filesystem::path & path, const std::string & src )
	: _Lex( src ), _Path( path )
{

}

Parser::~Parser()
{

}

ModuleNodePtr Parser::ParseModule()
{
	ModuleNodePtr p = XE::MakeShared< ModuleNode >();

	p->Name = _Path.stem().string();

	while( _Lex.LookToken().Type != TokenType::UNKNOWN )
	{
		switch( _Lex.LookToken().Type )
		{
		case TokenType::IMPORT:
			p->Imports.push_back( ParseImport() );
			break;
		case TokenType::USING:
			p->Usings.push_back( ParseUsing() );
			break;
		case TokenType::ENUM:
			p->Enums.push_back( ParseEnum() );
			break;
		case TokenType::CLASS:
			p->Classes.push_back( ParseClass() );
			break;
		case TokenType::SEMICOLON:
			_Lex.NextToken();
			break;
		default:
			throw XE::RuntimeException();
			break;
		}
	}

	return p;
}

UsingNodePtr Parser::ParseUsing()
{
	Ignore( TokenType::USING );

	auto p = XE::MakeShared< UsingNode >();

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	return p;
}

ImportNodePtr Parser::ParseImport()
{
	Ignore( TokenType::IMPORT );

	auto p = XE::MakeShared< ImportNode >();

	p->Name = Check( TokenType::STRING_CONST ).Value;

	return p;
}

EnumNodePtr Parser::ParseEnum()
{
	Ignore( TokenType::ENUM );

	EnumNodePtr p = XE::MakeShared<EnumNode>();

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	Ignore( TokenType::LBRACE );

	while( !Look(TokenType::RBRACE) )
	{
		p->Values.push_back( Check( TokenType::IDENTIFIER ).Value );

		if( !Skip( TokenType::COMMA ) )
		{
			break;
		}
	}

	Ignore( TokenType::RBRACE );

	return p;
}

ClassNodePtr Parser::ParseClass()
{
	Ignore( TokenType::CLASS );

	ClassNodePtr p = XE::MakeShared<ClassNode>();

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	if( Skip( TokenType::COLON ) )
	{
		p->Super = Check( TokenType::IDENTIFIER ).Value;
	}

	Ignore( TokenType::LBRACE );

	while( !Look( TokenType::RBRACE ) )
	{
		switch( _Lex.LookToken().Type )
		{
		case TokenType::ENUM:
		{
			auto pp = ParseEnum();
			pp->Owner = p->Name;
			p->Enums.push_back( pp );
		}
			break;
		case TokenType::CLASS:
		{
			auto pp = ParseClass();
			pp->Owner = p->Name;
			p->Classes.push_back( pp );
		}
			break;
		case TokenType::FUNCTION:
		{
			auto pp = ParseMethod();
			pp->Owner = p->Name;
			p->Methods.push_back( pp );
		}
			break;
		case TokenType::OPERATOR:
		{
			auto pp = ParseOperator();
			pp->Owner = p->Name;
			p->Operators.push_back( pp );
		}
			break;
		case TokenType::VARIABLE:
		{
			auto pp = ParseProperty();
			pp->Owner = p->Name;
			p->Propertys.push_back( pp );
		}
			break;
		case TokenType::SEMICOLON:
			_Lex.NextToken();
			break;
		default:
			throw XE::RuntimeException();
			break;
		}
	}

	Ignore( TokenType::RBRACE );

	return p;
}

MethodNodePtr Parser::ParseMethod()
{
	Ignore( TokenType::FUNCTION );

	auto p = XE::MakeShared<MethodNode>();

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	Ignore( TokenType::LPAREN );

	while( !Look(TokenType::RPAREN) )
	{
		p->Params.push_back( Check( TokenType::IDENTIFIER ).Value );

		if( !Skip( TokenType::COLON ) )
		{
			break;
		}
	}

	Ignore( TokenType::RPAREN );

	p->Block = ParseBlock();

	return p;
}

OperatorNodePtr Parser::ParseOperator()
{
	Ignore( TokenType::OPERATOR );

	auto p = XE::MakeShared<OperatorNode>();

	if( Look( TokenType::MUL ) || Look( TokenType::DIV ) || Look( TokenType::MOD ) ||
		Look( TokenType::ADD ) || Look( TokenType::SUB ) || Look( TokenType::L_SHFIT ) ||
		Look( TokenType::R_SHFIT ) || Look( TokenType::GREA ) || Look( TokenType::GREA_EQUAL ) ||
		Look( TokenType::LESS ) || Look( TokenType::LESS_EQUAL ) || Look( TokenType::EQUAL ) ||
		Look( TokenType::NOT_EQUAL ) || Look( TokenType::B_AND ) || Look( TokenType::B_XOR ) ||
		Look( TokenType::B_OR ) || Look( TokenType::L_AND ) || Look( TokenType::L_OR ) ||
		Look( TokenType::ASSIGN ) || Look( TokenType::MUL_ASSIGN ) || Look( TokenType::DIV_ASSIGN ) ||
		Look( TokenType::MOD_ASSIGN ) || Look( TokenType::ADD_ASSIGN ) || Look( TokenType::SUB_ASSIGN ) ||
		Look( TokenType::AND_ASSIGN ) || Look( TokenType::XOR_ASSIGN ) || Look( TokenType::OR_ASSIGN ) ||
		Look( TokenType::L_SHFIT_ASSIGN ) || Look( TokenType::R_SHFIT_ASSIGN ) )
	{
		p->Name = Token::TypeToString( _Lex.LookToken().Type );
		_Lex.NextToken();
	}
	else
	{
		throw XE::RuntimeException();
	}

	Ignore( TokenType::LPAREN );

	while( !Look( TokenType::RPAREN ) )
	{
		p->Params.push_back( Check( TokenType::IDENTIFIER ).Value );

		if( !Skip( TokenType::COLON ) )
		{
			break;
		}
	}

	Ignore( TokenType::RPAREN );

	p->Block = ParseBlock();

	return p;
}

PropertyNodePtr Parser::ParseProperty()
{
	Ignore( TokenType::VARIABLE );

	auto p = XE::MakeShared<PropertyNode>();

	if( Look( TokenType::LBRACKET ) )
	{
		Ignore( TokenType::LBRACKET );

		while( !Look(TokenType::RBRACKET) )
		{
			const std::string& s = Check( TokenType::IDENTIFIER ).Value;

			if( s == "NoClone" )
			{
				p->Flag |= IMetaProperty::NoClone;
			}
			else if( s == "NoDesign" )
			{
				p->Flag |= IMetaProperty::NoClone;
			}
			else if( s == "NoRuntime" )
			{
				p->Flag |= IMetaProperty::NoClone;
			}
			else if( s == "NoSerialize" )
			{
				p->Flag |= IMetaProperty::NoClone;
			}
			else
			{
				throw XE::RuntimeException();
			}

			if( !Skip( TokenType::COMMA ) )
			{
				break;
			}
		}

		Ignore( TokenType::RBRACKET );
	}

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	if( Skip( TokenType::ASSIGN ) )
	{
		p->InitExpr = ParseExpression();
	}

	return p;
}

StatementNodePtr Parser::ParseStatement()
{
	switch( _Lex.LookToken().Type )
	{
	case TokenType::IF:
		return ParseIf();
	case TokenType::FOR:
		return ParseFor();
	case TokenType::WHILE:
		return ParseWhile();
	case TokenType::SWITCH:
		return ParseSwitch();
	case TokenType::BREAK:
		return ParseBreak();
	case TokenType::CONTINUE:
		return ParseContinue();
	case TokenType::RETURN:
		return ParseReturn();
	case TokenType::LBRACE:
		return ParseBlock();
	case TokenType::SEMICOLON:
		_Lex.NextToken();
		return ParseStatement();
	case TokenType::IDENTIFIER:
	case TokenType::VARIABLE:
	case TokenType::FUNCTION:
	case TokenType::ADDADD:
	case TokenType::SUBSUB:
		return ParseExpression();
	}

	throw XE::RuntimeException();
}

BlockNodePtr Parser::ParseBlock()
{
	Ignore( TokenType::LBRACE );

	auto p = XE::MakeShared<BlockNode>();

	while( !Look( TokenType::RBRACE ) )
	{
		if( _Lex.LookToken().Type == TokenType::SEMICOLON )
		{
			_Lex.NextToken();
		}
		else
		{
			p->Statements.push_back( ParseStatement() );
		}
	}

	Ignore( TokenType::RBRACE );

	return p;
}

IfNodePtr Parser::ParseIf()
{
	Ignore( TokenType::IF );

	auto p = XE::MakeShared<IfNode>();

	p->Expr = ParseExprRelation();

	p->Block = ParseBlock();

	if( Skip( TokenType::ELSE ) )
	{
		p->Else = ParseStatement();
	}

	return p;
}

ForNodePtr Parser::ParseFor()
{
	Ignore( TokenType::FOR );

	auto p = XE::MakeShared<ForNode>();

	Ignore( TokenType::LPAREN );
	
	p->Stat = ParseStatement();
	p->Expr = ParseExpression();
	p->Iter = ParseExpression();
	
	Ignore( TokenType::RPAREN );

	p->Block = ParseBlock();

	return p;
}

WhileNodePtr Parser::ParseWhile()
{
	Ignore( TokenType::WHILE );

	auto p = XE::MakeShared<WhileNode>();

	p->Expr = ParseExpression();

	p->Block = ParseBlock();

	return p;
}

SwitchNodePtr Parser::ParseSwitch()
{
	Ignore( TokenType::SWITCH );

	auto p = XE::MakeShared<SwitchNode>();

	p->Expr = ParseExpression();

	Ignore( TokenType::LBRACE );

	while( !Look(TokenType::RBRACE) )
	{
		if( _Lex.LookToken().Type == TokenType::CASE )
		{
			p->Cases.push_back( ParseCase() );
		}
		else if( _Lex.LookToken().Type == TokenType::DEFAULT )
		{
			p->Default = ParseDefault();
			break;
		}
	}

	Ignore( TokenType::RBRACE );

	return p;
}

CaseNodePtr Parser::ParseCase()
{
	Ignore( TokenType::CASE );

	auto p = XE::MakeShared<CaseNode>();

	p->Expr = ParseExpression();

	p->Block = ParseBlock();

	return p;
}

DefaultNodePtr Parser::ParseDefault()
{
	Ignore( TokenType::DEFAULT );

	auto p = XE::MakeShared<DefaultNode>();

	p->Block = ParseBlock();

	return p;
}

BreakNodePtr Parser::ParseBreak()
{
	Ignore( TokenType::BREAK );

	return XE::MakeShared<BreakNode>();
}

ContinueNodePtr Parser::ParseContinue()
{
	Ignore( TokenType::CONTINUE );

	return XE::MakeShared<ContinueNode>();
}

ReturnNodePtr Parser::ParseReturn()
{
	Ignore( TokenType::RETURN );

	auto p = XE::MakeShared<ReturnNode>();

	p->Expr = ParseExpression();

	return p;
}

ExpressionNodePtr Parser::ParseExpression()
{
	ExpressionNodePtr node = ParseExprRelation();

	switch( _Lex.LookToken().Type )
	{
	case TokenType::ASSIGN:
	case TokenType::MUL_ASSIGN:
	case TokenType::DIV_ASSIGN:
	case TokenType::MOD_ASSIGN:
	case TokenType::ADD_ASSIGN:
	case TokenType::SUB_ASSIGN:
	case TokenType::AND_ASSIGN:
	case TokenType::XOR_ASSIGN:
	case TokenType::OR_ASSIGN:
	case TokenType::L_SHFIT_ASSIGN:
	case TokenType::R_SHFIT_ASSIGN:
	{
		auto p = XE::MakeShared<ExprBinaryNode>();

		p->Type = ExprBinaryNode::TokenTypeToBinaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Left = node;
		p->Right = ParseExpression();

		return p;
	}
	break;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprRelation()
{
	ExpressionNodePtr node = ParseExprShiftition();

	if(
		_Lex.LookToken().Type == TokenType::EQUAL ||
		_Lex.LookToken().Type == TokenType::NOT_EQUAL ||
		_Lex.LookToken().Type == TokenType::GREA ||
		_Lex.LookToken().Type == TokenType::GREA_EQUAL ||
		_Lex.LookToken().Type == TokenType::LESS ||
		_Lex.LookToken().Type == TokenType::LESS_EQUAL
		)
	{
		auto p = XE::MakeShared<ExprBinaryNode>();

		p->Type = ExprBinaryNode::TokenTypeToBinaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Left = node;
		p->Right = ParseExprShiftition();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprShiftition()
{
	ExpressionNodePtr node = ParseExprAddition();

	if(
		_Lex.LookToken().Type == TokenType::L_SHFIT ||
		_Lex.LookToken().Type == TokenType::R_SHFIT
		)
	{
		auto p = XE::MakeShared<ExprBinaryNode>();

		p->Type = ExprBinaryNode::TokenTypeToBinaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Left = node;
		p->Right = ParseExprAddition();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprAddition()
{
	ExpressionNodePtr node = ParseExprMultiplication();

	if(
		_Lex.LookToken().Type == TokenType::ADD ||
		_Lex.LookToken().Type == TokenType::SUB
		)
	{
		auto p = XE::MakeShared<ExprBinaryNode>();

		p->Type = ExprBinaryNode::TokenTypeToBinaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Left = node;
		p->Right = ParseExprMultiplication();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprMultiplication()
{
	ExpressionNodePtr node = ParseExprUnary2();

	if(
		_Lex.LookToken().Type == TokenType::MUL ||
		_Lex.LookToken().Type == TokenType::DIV ||
		_Lex.LookToken().Type == TokenType::MOD
		)
	{
		auto p = XE::MakeShared<ExprBinaryNode>();

		p->Type = ExprBinaryNode::TokenTypeToBinaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Left = node;
		p->Right = ParseExprUnary2();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprUnary2()
{
	ExpressionNodePtr node = nullptr;

	if(
		_Lex.LookToken().Type == TokenType::NEW ||
		_Lex.LookToken().Type == TokenType::DELETE ||
		_Lex.LookToken().Type == TokenType::SIZEOF ||
		_Lex.LookToken().Type == TokenType::TYPEOF ||
		_Lex.LookToken().Type == TokenType::NOT ||
		_Lex.LookToken().Type == TokenType::REVE ||
		_Lex.LookToken().Type == TokenType::ADDADD ||
		_Lex.LookToken().Type == TokenType::SUBSUB
		)
	{
		auto p = XE::MakeShared<ExprUnaryNode>();

		p->Type = ExprUnaryNode::TokenTypeToUnaryType( _Lex.LookToken().Type );
		_Lex.NextToken();

		p->Expr = ParseExprUnary1();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprUnary1()
{
	ExpressionNodePtr node = ParseExprFactor();

	if( _Lex.LookToken().Type == TokenType::LPAREN  )
	{
		auto p = XE::MakeShared<ExprCallbackNode>();

		p->Variable = node;

		p->Argument = ParseArgument();

		return p;
	}
	else if( _Lex.LookToken().Type == TokenType::LBRACKET )
	{
		auto p = XE::MakeShared<ExprIndexNode>();

		p->Variable = node;

		p->Expr = ParseExpression();

		return p;
	}
	else if( _Lex.LookToken().Type == TokenType::DOT )
	{
		auto p = XE::MakeShared<ExprVisitNode>();

		p->Variable = node;

		p->Property = ParseExprFactor();

		return p;
	}

	return node;
}

ExpressionNodePtr Parser::ParseExprFactor()
{
	switch( _Lex.LookToken().Type )
	{
	case TokenType::VARIABLE:
	{
		return ParseExprVariable();
	}
	case TokenType::FUNCTION:
	{
		return ParseExprCloseure();
	}
	case TokenType::LBRACE:
	{
		Ignore( TokenType::LBRACE );
		auto p = ParseExpression();
		Ignore( TokenType::RBRACE );
		return p;
	}
	case TokenType::IDENTIFIER:
	{
		auto p = XE::MakeShared<ExprVariableNode>();

		p->Name = Check( TokenType::IDENTIFIER ).Value;

		return p;
	}
	case TokenType::NIL:
	{
		_Lex.NextToken();
		auto p = XE::MakeShared<NilNode>();
		return p;
	}
	case TokenType::TRUE:
	{
		_Lex.NextToken();
		auto p = XE::MakeShared<BoolNode>();
		p->Data = true;
		return p;
	}
	case TokenType::FALSE:
	{
		_Lex.NextToken();
		auto p = XE::MakeShared<BoolNode>();
		p->Data = false;
		return p;
	}
	case TokenType::INT_CONST:
	{
		auto p = XE::MakeShared<IntNode>();
		p->Data = std::stoi( Check( TokenType::INT_CONST ).Value );
		return p;
	}
	case TokenType::FLOAT_CONST:
	{
		auto p = XE::MakeShared<FloatNode>();
		p->Data = std::stof( Check( TokenType::FLOAT_CONST ).Value );
		return p;
	}
	case TokenType::STRING_CONST:
	{
		auto p = XE::MakeShared<StringNode>();
		p->Data = Check( TokenType::STRING_CONST ).Value;
		return p;
	}
	}

	return nullptr;
}

ExprArgumentNodePtr Parser::ParseArgument()
{
	Ignore( TokenType::LPAREN );

	auto p = XE::MakeShared<ExprArgumentNode>();

	while( !Look(TokenType::RPAREN) )
	{
		p->Argument.push_back( ParseExpression() );
	}
	Ignore( TokenType::RPAREN );

	return p;
}

ExprVariableNodePtr Parser::ParseExprVariable()
{
	Ignore( TokenType::VARIABLE );

	auto p = XE::MakeShared< ExprVariableNode>();

	p->Name = Check( TokenType::IDENTIFIER ).Value;

	return p;
}

ExprCloseureNodePtr Parser::ParseExprCloseure()
{
	Ignore( TokenType::FUNCTION );

	auto p = XE::MakeShared<ExprCloseureNode>();

	static XE::uint64 index = 0;

	p->Index = index++;

	Ignore( TokenType::LPAREN );

	while( !Look( TokenType::RPAREN ) )
	{
		p->Params.push_back( Check( TokenType::IDENTIFIER ).Value );

		if( !Skip( TokenType::COLON ) )
		{
			break;
		}
	}

	Ignore( TokenType::RPAREN );

	p->Block = ParseBlock();

	return p;

}

bool Parser::Look( TokenType val ) noexcept
{
	if (_Lex.LookToken().Type == val)
	{
		return true;
	}

	return false;
}

bool Parser::Skip( TokenType val ) noexcept
{
	if( _Lex.LookToken().Type == val )
	{
		_Lex.NextToken();
		return true;
	}

	return false;
}

void Parser::Ignore( TokenType val )
{
	if( _Lex.LookToken().Type == val )
	{
		_Lex.NextToken();
	}

	throw XE::RuntimeException();
}

const Token & Parser::Check( TokenType val )
{
	const Token & ret = _Lex.LookToken();

	if( ret.Type == val )
	{
		_Lex.NextToken();
		return ret;
	}

	throw XE::RuntimeException();
}
