/*!
 * \file	BluePrint.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLUEPRINT_H__EB39E9E6_D204_453A_BF18_6917DB4D76F1
#define BLUEPRINT_H__EB39E9E6_D204_453A_BF18_6917DB4D76F1

#include "AIModule.h"

BEG_XE_NAMESPACE

class XE_API BluePrint : public XE::AIModule
{
	OBJECT( BluePrint, AIModule )

public:
	BluePrint();

	~BluePrint() override;

public:
	virtual void Startup() override;

	virtual void Update( XE::float32 dt ) override;

	virtual void Clearup() override;

public:
	XE::AIElementHandle GetRoot() const;

	void SetRoot( XE::AIElementHandle val );

	XE::AIElementPtr GetElement( XE::AIElementHandle val ) const;

private:
	const XE::Array< XE::AIElementPtr > & GetElements() const;

	void SetElements( const XE::Array< XE::AIElementPtr > & val );

public:
	XE::AIElementHandle _Root;
	XE::Array< XE::AIElementPtr > _Elements;
};

END_XE_NAMESPACE

#endif // BLUEPRINT_H__EB39E9E6_D204_453A_BF18_6917DB4D76F1
