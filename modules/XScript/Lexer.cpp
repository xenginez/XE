#include "Lexer.h"

constexpr XE::int32 STATUS_BEG = 0;
constexpr XE::int32 STATUS_INT = 1;
constexpr XE::int32 STATUS_FLT = 2;
constexpr XE::int32 STATUS_STR = 3;
constexpr XE::int32 STATUS_TRA = 4;
constexpr XE::int32 STATUS_NTE = 5;
constexpr XE::int32 STATUS_OPE = 6;
constexpr XE::int32 STATUS_SPE = 7;
constexpr XE::int32 STATUS_IDF = 8;
constexpr XE::int32 STATUS_END = 9;



XE::Lexer::Lexer( const std::string & val )
	:_Src( val ), _CurToken( 0 ), _State( 0 )
{
	_Cursor = _Src.begin();
}

XE::Lexer::~Lexer()
{

}

const XE::Token & XE::Lexer::LookToken()
{
	if( _Tokens.empty() )
	{
		Next();
	}

	return _Tokens[_CurToken];
}

const XE::Token & XE::Lexer::NextToken()
{
	_CurToken++;

	if( _CurToken >= _Tokens.size() )
	{
		Next();
	}

	return _Tokens[_CurToken];
}

const XE::Token & XE::Lexer::BackToken()
{
	_CurToken--;

	return _Tokens[_CurToken];
}

XE_INLINE void XE::Lexer::Next()
{
	while( true )
	{
		if( _Cursor == _Src.end() )
		{
			End();
		}

		switch( _State )
		{
		case STATUS_BEG:
			Beg();
			break;
		case STATUS_INT:
			Int();
			break;
		case STATUS_FLT:
			Flt();
			break;
		case STATUS_STR:
			Str();
			break;
		case STATUS_NTE:
			Nte();
			break;
		case STATUS_OPE:
			Ope();
			break;
		case STATUS_SPE:
			Spe();
			break;
		case STATUS_IDF:
			Idf();
			break;
		case STATUS_END:
			_State = STATUS_BEG;
			return;
		default:
			throw XE::RuntimeException();
			break;
		}
	}
}

XE_INLINE void XE::Lexer::Beg()
{
	if( ( *_Cursor ) == ' ' || ( *_Cursor ) == '\n' || ( *_Cursor ) == '\t' || ( *_Cursor ) == '\r' )
	{
		_Cursor++;
		_State = STATUS_BEG;
	}
	else if( ( *_Cursor ) >= '0' && ( *_Cursor ) <= '9' )
	{
		_State = STATUS_INT;
	}
	else if( ( *_Cursor ) == '\"' )
	{
		_Cursor++;
		_State = STATUS_STR;
	}
	else if( ( *_Cursor ) == '#' )
	{
		_State = STATUS_NTE;
	}
	else if( 
		( *_Cursor ) == '_' ||
		( ( *_Cursor ) >= 'a' && ( *_Cursor ) <= 'z' ) ||
		( ( *_Cursor ) >= 'A' && ( *_Cursor ) <= 'Z' ) )
	{
		_State = STATUS_IDF;
	}
	else if(
		( *_Cursor ) == '[' || ( *_Cursor ) == '(' || ( *_Cursor ) == '{' ||
		( *_Cursor ) == ']' || ( *_Cursor ) == ')' || ( *_Cursor ) == '}' ||
		( *_Cursor ) == ',' || ( *_Cursor ) == ';' || ( *_Cursor ) == ':' )
	{
		_State = STATUS_SPE;
	}
	else if(
		( *_Cursor ) == '!' || ( *_Cursor ) == '~' ||
		( *_Cursor ) == '.' || ( *_Cursor ) == '*' || ( *_Cursor ) == '/' ||
		( *_Cursor ) == '%' || ( *_Cursor ) == '+' || ( *_Cursor ) == '-' ||
		( *_Cursor ) == '&' || ( *_Cursor ) == '|' || ( *_Cursor ) == '^' ||
		( *_Cursor ) == '<' || ( *_Cursor ) == '>' || ( *_Cursor ) == '=' )
	{
		_State = STATUS_OPE;
	}
	else
	{
		throw XE::RuntimeException();
	}
}

XE_INLINE void XE::Lexer::Int()
{
	if( ( *_Cursor ) >= '0' && ( *_Cursor ) <= '9' )
	{
		_Word.push_back( *_Cursor );
		_Cursor++;
	}
	else if( ( *_Cursor ) == '.' )
	{
		_Word.push_back( *_Cursor );
		_Cursor++;
		_State = STATUS_FLT;
	}
	else
	{
		End();
	}
}

XE_INLINE void XE::Lexer::Flt()
{
	if( ( *_Cursor ) >= '0' && ( *_Cursor ) <= '9' )
	{
		_Word.push_back( *_Cursor );
		_Cursor++;
	}
	else
	{
		End();
	}
}

XE_INLINE void XE::Lexer::Str()
{
	if( ( *_Cursor ) == '\\' )
	{
		_Cursor++;
		_State = STATUS_TRA;
	}
	else if( ( *_Cursor ) == '\"' )
	{
		_Cursor++;

		End();
	}
	else
	{
		_Word.push_back( *_Cursor );
		_Cursor++;
	}
}

XE_INLINE void XE::Lexer::Tra()
{
	switch( *_Cursor )
	{
	case '\\':
		_Word.push_back( '\\' );
		break;
	case '\n':
		_Word.push_back( '\n' );
		break;
	case '\r':
		_Word.push_back( '\r' );
		break;
	case '\t':
		_Word.push_back( '\t' );
		break;
	case '\0':
		_Word.push_back( '\0' );
		break;
	case '\'':
		_Word.push_back( '\'' );
		break;
	case '\"':
		_Word.push_back( '\"' );
		break;
	default:
		throw XE::RuntimeException();
		break;
	}

	_Cursor++;
	_State = STATUS_STR;
}

XE_INLINE void XE::Lexer::Nte()
{
	while( (*_Cursor) != '\n' )
	{
		_Cursor++;
	}

	_State = STATUS_BEG;
}

XE_INLINE void XE::Lexer::Ope()
{
	if(
		( *_Cursor ) == '!' || ( *_Cursor ) == '~' ||
		( *_Cursor ) == '.' || ( *_Cursor ) == '*' || ( *_Cursor ) == '/' ||
		( *_Cursor ) == '%' || ( *_Cursor ) == '+' || ( *_Cursor ) == '-' ||
		( *_Cursor ) == '&' || ( *_Cursor ) == '|' || ( *_Cursor ) == '^' ||
		( *_Cursor ) == '<' || ( *_Cursor ) == '>' || ( *_Cursor ) == '=' )
	{
		_Word.push_back( *_Cursor );
		_Cursor++;

		if( (
			( *_Cursor ) == '=' && (
			( *_Cursor ) == '!' ||
			( *_Cursor ) == '~' || ( *_Cursor ) == '*' || ( *_Cursor ) == '/' ||
			( *_Cursor ) == '%' || ( *_Cursor ) == '+' || ( *_Cursor ) == '-' ||
			( *_Cursor ) == '&' || ( *_Cursor ) == '|' || ( *_Cursor ) == '^' ||
			( *_Cursor ) == '<' || ( *_Cursor ) == '>' || ( *_Cursor ) == '='
			)
			) ||
			( ( *_Cursor ) == '<' && _Word[0] == '<' ) ||
			( ( *_Cursor ) == '>' && _Word[0] == '>' ) ||
			( ( *_Cursor ) == '&' && _Word[0] == '&' ) ||
			( ( *_Cursor ) == '|' && _Word[0] == '|' ) ||
			( ( *_Cursor ) == '+' && _Word[0] == '+' ) ||
			( ( *_Cursor ) == '-' && _Word[0] == '-' )
			)
		{
			_Word.push_back( *_Cursor );
			_Cursor++;
		}
		else
		{
			End();
		}
	}
}

XE_INLINE void XE::Lexer::Spe()
{
	if(
		( *_Cursor ) == '[' || ( *_Cursor ) == '(' || ( *_Cursor ) == '{' ||
		( *_Cursor ) == ']' || ( *_Cursor ) == ')' || ( *_Cursor ) == '}' ||
		( *_Cursor ) == ',' || ( *_Cursor ) == ';' || ( *_Cursor ) == ':' )
	{
		_Word.push_back( *_Cursor );
		_Cursor++;

		End();
	}
}

XE_INLINE void XE::Lexer::Idf()
{
	if(
		( *_Cursor ) == '_' ||
		( ( *_Cursor ) >= 'a' && ( *_Cursor ) <= 'z' ) ||
		( ( *_Cursor ) >= 'A' && ( *_Cursor ) <= 'Z' ) ||
		( !_Word.empty() && ( ( *_Cursor ) >= '0' && ( *_Cursor ) <= '9' ) )
	)
	{
		_Word.push_back( *_Cursor );
		_Cursor++;
	}
	else
	{
		End();
	}
}

XE_INLINE void XE::Lexer::End()
{
	switch( _State )
	{
	case STATUS_INT:
		_Tokens.push_back( { TokenType::INT_CONST,_Word } );
		break;
	case STATUS_FLT:
		_Tokens.push_back( { TokenType::FLOAT_CONST,_Word } );
		break;
	case STATUS_STR:
		_Tokens.push_back( { TokenType::STRING_CONST, _Word } );
		break;
	case STATUS_OPE:
		if( Token::StringToType( _Word ) != TokenType::UNKNOWN )
		{
			_Tokens.push_back( { Token::StringToType( _Word ) } );
		}
		break;
	case STATUS_SPE:
		if( Token::StringToType( _Word ) != TokenType::UNKNOWN )
		{
			_Tokens.push_back( { Token::StringToType( _Word ) } );
		}
		break;
	case STATUS_IDF:
		if( Token::StringToType( _Word ) != TokenType::UNKNOWN )
		{
			_Tokens.push_back( { Token::StringToType( _Word ) } );
		}
		else
		{
			_Tokens.push_back( { TokenType::IDENTIFIER, _Word } );
		}
		break;
	default:
		throw XE::RuntimeException();
		break;
	}

	_Word.clear();

	_State = STATUS_END;
}

void XE::Lexer::Reset( XE::uint64 val /*= 0 */ )
{
	_CurToken = val;
}
