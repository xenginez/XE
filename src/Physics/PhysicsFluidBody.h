/*!
 * \file	PhysicsFluidBody.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSFLUIDBODY_H__F45C9AF6_B377_4477_8887_141B71C436C6
#define PHYSICSFLUIDBODY_H__F45C9AF6_B377_4477_8887_141B71C436C6

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsFluidBody : public XE::Object
{
	OBJECT( PhysicsFluidBody, Object )

public:
	PhysicsFluidBody();

	~PhysicsFluidBody();

};

END_XE_NAMESPACE

#endif // PHYSICSFLUIDBODY_H__F45C9AF6_B377_4477_8887_141B71C436C6
