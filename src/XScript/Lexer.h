/*!
 * \file	Lexer.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LEXER_H__13767E40_89D3_4C2D_B5C3_44053F33EE02
#define LEXER_H__13767E40_89D3_4C2D_B5C3_44053F33EE02

#include "Token.h"

BEG_XE_NAMESPACE

class XSCRIPT_API Lexer : public std::enable_shared_from_this< Lexer >, public XE::NonCopyable
{
public:
	Lexer( const std::string & val );

	~Lexer();

public:
	const Token & LookToken();

	const Token & NextToken();

	const Token & BackToken();

public:
	void Reset( XE::uint64 val = 0 );

private:
	XE_INLINE void Next();

	XE_INLINE void Beg();

	XE_INLINE void Int();

	XE_INLINE void Flt();

	XE_INLINE void Str();

	XE_INLINE void Tra();

	XE_INLINE void Nte();

	XE_INLINE void Ope();

	XE_INLINE void Spe();

	XE_INLINE void Idf();

	XE_INLINE void End();

private:
	XE::int32 _State;
	std::string _Src;
	std::string _Word;
	XE::uint64 _CurToken;
	Array<Token> _Tokens;
	std::string::const_iterator _Cursor;
};

END_XE_NAMESPACE

#endif // LEXER_H__13767E40_89D3_4C2D_B5C3_44053F33EE02
