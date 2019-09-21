/*!
 * \file   ConditionNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BTCONDITIONNODE_H__905E19A0_46A9_4C5D_B618_50671CE3A1C3
#define __BTCONDITIONNODE_H__905E19A0_46A9_4C5D_B618_50671CE3A1C3

#include "Node.h"

BEG_XE_NAMESPACE

class XE_API BTConditionNode : public Node
{
	OBJECT( BTConditionNode, Node )

public:
	BTConditionNode();

	~BTConditionNode();

};

END_XE_NAMESPACE

#endif // __BTCONDITIONNODE_H__905E19A0_46A9_4C5D_B618_50671CE3A1C3
