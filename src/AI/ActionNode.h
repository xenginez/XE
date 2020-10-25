/*!
 * \file   ActionNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
#define __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1

#include "AINode.h"

BEG_XE_NAMESPACE

class ConditionNode;

class XE_API ActionNode : public AINode
{
	OBJECT( ActionNode, AINode )

public:
	ActionNode();

	~ActionNode();

};

END_XE_NAMESPACE

#endif // __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
