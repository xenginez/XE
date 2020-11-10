/*!
 * \file	Blueprint.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLUEPRINT_H__8940906E_DDA9_470B_B409_B962E67B7A58
#define BLUEPRINT_H__8940906E_DDA9_470B_B409_B962E67B7A58

#include "AIModule.h"

BEG_XE_NAMESPACE

class XE_API Blueprint : public XE::AIModule
{
	OBJECT( Blueprint, AIModule )

public:
	Blueprint();

	~Blueprint() override;

public:
	void Startup() override;

	void Update( XE::float32 dt );

	void Clearup() override;

	void AssetLoad() override;

public:
	XE::AIElementHandle GetRoot() const;

	void SetRoot( XE::AIElementHandle val );

	const XE::Array< XE::AIElementPtr > & GetElements() const;

	void SetElements( const XE::Array< XE::AIElementPtr > & val );

	XE::AIElementPtr GetElement( XE::AIElementHandle val ) const;

public:
	XE::AIElementHandle _Root;
	XE::Array< XE::AIElementPtr > _Elements;
};

END_XE_NAMESPACE

#endif // BLUEPRINT_H__8940906E_DDA9_470B_B409_B962E67B7A58
