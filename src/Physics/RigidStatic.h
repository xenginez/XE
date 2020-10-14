/*!
 * \file	RigidStatic.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62
#define RIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62

#include "RigidBody.h"

BEG_XE_NAMESPACE

class XE_API RigidStatic : public XE::RigidBody
{
	OBJECT( RigidStatic, RigidBody )

public:
	RigidStatic();

	~RigidStatic();
};

END_XE_NAMESPACE

#endif // RIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62
