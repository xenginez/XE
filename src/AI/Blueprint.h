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

class SubElement;
class EventElement;

class XE_API Blueprint : public XE::AIModule
{
	OBJECT( Blueprint, AIModule )

public:
	Blueprint();

	~Blueprint() override;

public:
	void Startup() override;

	void Enter() override;

	void Update( XE::float32 dt );

	void Quit() override;

	void Clearup() override;

	bool IsStopped() const override;

	void AssetLoad() override;

	void ProcessEvent( const EventPtr & val ) override;

public:
	const XE::Array< XE::AIElementPtr > & GetElements() const;

	void SetElements( const XE::Array< XE::AIElementPtr > & val );

	XE::AIElementPtr GetElement( XE::AIElementHandle val ) const;

	template< typename T > XE::SharedPtr< T > GetElementT( XE::AIElementHandle val ) const
	{
		return DP_CAST< T >( GetElement( val ) );
	}

public:
	XE::Array< XE::AIElementPtr > _Elements;

	XE::Array< XE::SubElement * > _Subs;
	XE::Array< XE::EventElement * > _Events;
	XE::Array< XE::EventElement * > _Updates;
};

END_XE_NAMESPACE

#endif // BLUEPRINT_H__8940906E_DDA9_470B_B409_B962E67B7A58
