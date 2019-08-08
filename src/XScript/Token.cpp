#include "Token.h"

USING_XE

XE::Token::Token()
	: _Token( TokenType::UNKNOWN ), _Value( 0 )
{
	
}

XE::Token::Token( TokenType val )
	: _Token( val )
{

}

XE::Token::Token( TokenType type, const std::string & val )
	: _Token( type ), _Value( val )
{

}

XE::TokenType XE::Token::StringToType( const std::string & val )
{
	static std::map<std::string, TokenType> map =
	{
	{"unknown", TokenType::UNKNOWN},
	{"int", TokenType::INT},
	{"void", TokenType::VOID},
	{"bool", TokenType::BOOL},
	{"float", TokenType::FLOAT},
	{"string", TokenType::STRING},
	{"identifier", TokenType::IDENTIFIER},
	{"nil", TokenType::NIL},
	{"true", TokenType::TRUE},
	{"false", TokenType::FALSE},
	{"int_const", TokenType::INT_CONST},
	{"float_const", TokenType::FLOAT_CONST},
	{"string_const", TokenType::STRING_CONST},
	{"import", TokenType::IMPORT},
	{"using", TokenType::USING},
	{"if", TokenType::IF},
	{"else", TokenType::ELSE},
	{"for", TokenType::FOR},
	{"while", TokenType::WHILE},
	{"switch", TokenType::SWITCH},
	{"case", TokenType::CASE},
	{"default", TokenType::DEFAULT},
	{"break", TokenType::BREAK},
	{"continue", TokenType::CONTINUE},
	{"return", TokenType::RETURN},
	{"enum", TokenType::ENUM},
	{"class", TokenType::CLASS},
	{"operator", TokenType::OPERATOR},
	{"function", TokenType::FUNCTION},
	{"variable", TokenType::VARIABLE},
	{"this", TokenType::THIS},
	{"super", TokenType::SUPER},
	{"new", TokenType::NEW},
	{"delete", TokenType::DELETE},
	{"sizeof", TokenType::SIZEOF},
	{"typeof", TokenType::TYPEOF},
	{"!", TokenType::NOT},
	{"~", TokenType::REVE},
	{"{", TokenType::LBRACE},
	{"}", TokenType::RBRACE},
	{"(", TokenType::LPAREN},
	{")", TokenType::RPAREN},
	{"[", TokenType::LBRACKET},
	{"]", TokenType::RBRACKET},
	{";", TokenType::SEMICOLON},
	{":", TokenType::COLON},
	{",", TokenType::COMMA},
	{".", TokenType::DOT},
	{"*", TokenType::MUL},
	{"/", TokenType::DIV},
	{"%", TokenType::MOD},
	{"+", TokenType::ADD},
	{"-", TokenType::SUB},
	{"<<", TokenType::L_SHFIT},
	{">>", TokenType::R_SHFIT},
	{"<", TokenType::GREA},
	{"<=", TokenType::GREA_EQUAL},
	{">", TokenType::LESS},
	{">=", TokenType::LESS_EQUAL},
	{"==", TokenType::EQUAL},
	{"!=", TokenType::NOT_EQUAL},
	{"&", TokenType::B_AND},
	{"^", TokenType::B_XOR},
	{"|", TokenType::B_OR},
	{"&&", TokenType::L_AND},
	{"||", TokenType::L_OR},
	{"=", TokenType::ASSIGN},
	{"*=", TokenType::MUL_ASSIGN},
	{"/=", TokenType::DIV_ASSIGN},
	{"%=", TokenType::MOD_ASSIGN},
	{"+=", TokenType::ADD_ASSIGN},
	{"-=", TokenType::SUB_ASSIGN},
	{"&=", TokenType::AND_ASSIGN},
	{"^=", TokenType::XOR_ASSIGN},
	{"|=", TokenType::OR_ASSIGN},
	{"<<=", TokenType::L_SHFIT_ASSIGN},
	{">>=", TokenType::R_SHFIT_ASSIGN},
	};

	auto it = map.find( val );
	if( it != map.end() )
	{
		return it->second;
	}

	return TokenType::UNKNOWN;
}

const std::string & XE::Token::TypeToString( TokenType val )
{
	static std::map<TokenType, std::string> map =
	{
	{TokenType::UNKNOWN, "unknown"},
	{TokenType::INT, "int"},
	{TokenType::VOID, "void"},
	{TokenType::BOOL, "bool"},
	{TokenType::FLOAT, "float"},
	{TokenType::STRING, "string"},
	{TokenType::IDENTIFIER, "identifier"},
	{TokenType::NIL, "nil"},
	{TokenType::TRUE, "true"},
	{TokenType::FALSE, "false"},
	{TokenType::INT_CONST, "int_const"},
	{TokenType::FLOAT_CONST, "float_const"},
	{TokenType::STRING_CONST, "string_const"},
	{TokenType::IMPORT, "import"},
	{TokenType::USING, "using"},
	{TokenType::IF, "if"},
	{TokenType::ELSE, "else"},
	{TokenType::FOR, "for"},
	{TokenType::WHILE, "while"},
	{TokenType::SWITCH, "switch"},
	{TokenType::CASE, "case"},
	{TokenType::DEFAULT, "default"},
	{TokenType::BREAK, "break"},
	{TokenType::CONTINUE, "continue"},
	{TokenType::RETURN, "return"},
	{TokenType::ENUM, "enum"},
	{TokenType::CLASS, "class"},
	{TokenType::OPERATOR, "operator"},
	{TokenType::FUNCTION, "function"},
	{TokenType::VARIABLE, "variable"},
	{TokenType::THIS, "this"},
	{TokenType::SUPER, "super"},
	{TokenType::NEW, "new"},
	{TokenType::DELETE, "delete"},
	{TokenType::SIZEOF, "sizeof"},
	{TokenType::TYPEOF, "typeof"},
	{TokenType::NOT, "!"},
	{TokenType::REVE, "~"},
	{TokenType::LBRACE, "{"},
	{TokenType::RBRACE, "}"},
	{TokenType::LPAREN, "("},
	{TokenType::RPAREN, ")"},
	{TokenType::LBRACKET, "["},
	{TokenType::RBRACKET, "]"},
	{TokenType::SEMICOLON, ";"},
	{TokenType::COLON, ":"},
	{TokenType::COMMA, ","},
	{TokenType::DOT, "."},
	{TokenType::MUL, "*"},
	{TokenType::DIV, "/"},
	{TokenType::MOD, "%"},
	{TokenType::ADD, "+"},
	{TokenType::SUB, "-"},
	{TokenType::L_SHFIT, "<<"},
	{TokenType::R_SHFIT, ">>"},
	{TokenType::GREA, "<"},
	{TokenType::GREA_EQUAL, "<="},
	{TokenType::LESS, ">"},
	{TokenType::LESS_EQUAL, ">="},
	{TokenType::EQUAL, "=="},
	{TokenType::NOT_EQUAL, "!="},
	{TokenType::B_AND, "&"},
	{TokenType::B_XOR, "^"},
	{TokenType::B_OR, "|"},
	{TokenType::L_AND, "&&"},
	{TokenType::L_OR, "||"},
	{TokenType::ASSIGN, "="},
	{TokenType::MUL_ASSIGN, "*="},
	{TokenType::DIV_ASSIGN, "/="},
	{TokenType::MOD_ASSIGN, "%="},
	{TokenType::ADD_ASSIGN, "+="},
	{TokenType::SUB_ASSIGN, "-="},
	{TokenType::AND_ASSIGN, "&="},
	{TokenType::XOR_ASSIGN, "^="},
	{TokenType::OR_ASSIGN, "|="},
	{TokenType::L_SHFIT_ASSIGN, "<<="},
	{TokenType::R_SHFIT_ASSIGN, ">>="},
	};

	auto it = map.find( val );
	if( it != map.end() )
	{
		return it->second;
	}

	return map[TokenType::UNKNOWN];
}
