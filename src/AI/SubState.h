/*!
 * \file   SubState.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SUBSTATE_H__1E7A8AE4_FEC7_4239_A537_E55BF56FFB34
#define __SUBSTATE_H__1E7A8AE4_FEC7_4239_A537_E55BF56FFB34

#include "State.h"

BEG_XE_NAMESPACE

class XE_API SubState : public XE::State
{
	OBJECT( SubState, State )

public:
	SubState();

	~SubState();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AssetInstance< AIModule > _SubAI;
};

END_XE_NAMESPACE

#endif // __SUBSTATE_H__1E7A8AE4_FEC7_4239_A537_E55BF56FFB34
