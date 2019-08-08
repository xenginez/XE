/*!
 * \file	AST.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AST_H__5ABF1C1A_FB7A_4385_B27F_47E6480FA3A7
#define AST_H__5ABF1C1A_FB7A_4385_B27F_47E6480FA3A7

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API AST
{
public:
	AST( const std::string & val );

	~AST();

public:
	void AddUsing( const std::string & val );

	XSMetaEnumPtr AddEnum( const std::string & name );

	XSMetaClassPtr AddClass( const std::string & name, const std::string & base );

	XSMetaMethodPtr AddMethod( const std::string & name, List<std::string> && params );

	XSMetaOperatorPtr AddOperator( const std::string & name, List<std::string> && params );

	XSMetaPropertyPtr AddProperty( const std::string & name );

public:
	void PushBlock();

	void PopBlock();

	void AddStatement();
};

END_XE_NAMESPACE

#endif // AST_H__5ABF1C1A_FB7A_4385_B27F_47E6480FA3A7
