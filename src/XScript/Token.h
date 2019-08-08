/*!
 * \file	Token.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TOKEN_H__CEAC062D_CC26_4FBF_B783_E0FA576DA0F1
#define TOKEN_H__CEAC062D_CC26_4FBF_B783_E0FA576DA0F1

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API Token
{
public:
	Token();

	Token( TokenType val );

	Token( TokenType type, const std::string & val );

public:
	static TokenType StringToType( const std::string & val );

	static const std::string & TypeToString( TokenType val );

public:
	TokenType _Token;
	std::string _Value;
};

END_XE_NAMESPACE

#endif // TOKEN_H__CEAC062D_CC26_4FBF_B783_E0FA576DA0F1
