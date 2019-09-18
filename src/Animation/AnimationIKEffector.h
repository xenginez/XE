/*!
 * \file	AnimationIKEffector.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80
#define ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationIKEffector : public XE::Object
{
	OBJECT( AnimationIKEffector, Object )

public:
	AnimationIKEffector();

	~AnimationIKEffector();
};

END_XE_NAMESPACE

#endif // ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80
