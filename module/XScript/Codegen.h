/*!
 * \file	Codegen.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CODEGEN_H__1DA87CFC_99BD_428A_B078_694860818A80
#define CODEGEN_H__1DA87CFC_99BD_428A_B078_694860818A80

#include "Type.h"

BEG_XE_NAMESPACE

class Codegen
{
public:
	void SetModuleName( const String & val );

	void AddUsing( const String & val );

	XE::uint32 AddString( const String & val );

public:
	XE::uint32 CodeIndex();

	XE::uint32 StackIndex();

public:
	void PushBlock();

	void PopBlock();

public:
	XE::uint32 Nop();

	XE::uint32 NopI();

	void Insert( InstructType type );

	void Insert( InstructType type, XE::uint32 val );

	void Insert( InstructType type, XE::float32 val );

	void Reset( XE::uint32 index, InstructType type );

	void Reset( XE::uint32 index, InstructType type, XE::uint32 val );

	void Reset( XE::uint32 index, InstructType type, XE::float32 val );

public:
	void LoadModule( const String & val );
};

END_XE_NAMESPACE

#endif // CODEGEN_H__1DA87CFC_99BD_428A_B078_694860818A80
