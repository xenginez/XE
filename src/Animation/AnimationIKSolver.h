/*!
 * \file	AnimationIKSolver.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8
#define ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationIKSolver : public XE::Object
{
	OBJECT( AnimationIKSolver, Object )

public:
	AnimationIKSolver();

	~AnimationIKSolver();
};

END_XE_NAMESPACE

#endif // ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8
