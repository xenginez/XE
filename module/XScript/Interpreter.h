/*!
 * \file	Interpreter.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef INTERPRETER_H__6E075EA6_8D7E_4295_B597_7CE844B735FD
#define INTERPRETER_H__6E075EA6_8D7E_4295_B597_7CE844B735FD

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API Interpreter
{
public:
	Interpreter();

	~Interpreter();

public:
	void LoadScript( const std::string & val );

	void LoadScript( const std::filesystem::path & val );

};

END_XE_NAMESPACE

#endif // INTERPRETER_H__6E075EA6_8D7E_4295_B597_7CE844B735FD
