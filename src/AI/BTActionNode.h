/*!
 * \file   ActionNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BTACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
#define __BTACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1

#include "Node.h"

BEG_XE_NAMESPACE

class BTConditionNode;

class XE_API BTActionNode : public Node
{
	OBJECT( BTActionNode, Node )

public:
	BTActionNode();

	~BTActionNode();

};

END_XE_NAMESPACE

#endif // __BTACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
