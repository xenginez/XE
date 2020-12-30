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

#include "Module.h"

BEG_AI_NAMESPACE

class EventElement;

class AI_API Blueprint : public AI::Module
{
	OBJECT( Blueprint, Module )

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

	void ProcessEvent( const XE::EventPtr & val ) override;

public:
	const XE::Array< AI::ElementPtr > & GetElements() const;

	void SetElements( const XE::Array< AI::ElementPtr > & val );

	AI::ElementPtr GetElement( AI::ElementHandle val ) const;

	template< typename T > XE::SharedPtr< T > GetElementT( AI::ElementHandle val ) const
	{
		return DP_CAST< T >( GetElement( val ) );
	}

public:
	XE::Array< AI::ElementPtr > _Elements;
	XE::Array< AI::EventElement * > _Events;
	XE::Array< AI::EventElement * > _Updates;
};

END_AI_NAMESPACE

#endif // BLUEPRINT_H__8940906E_DDA9_470B_B409_B962E67B7A58
