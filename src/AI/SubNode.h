/*!
 * \file   SubNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SUBNODE_H__36B8D658_944F_4236_ADA5_C25C5FF33393
#define __SUBNODE_H__36B8D658_944F_4236_ADA5_C25C5FF33393

#include "Node.h"

BEG_XE_NAMESPACE

class XE_API SubNode : public XE::Node
{
	OBJECT( SubNode, Node )

public:
	SubNode();

	~SubNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AssetInstance< AIModule > _SubAI;
};

END_XE_NAMESPACE

#endif // __SUBNODE_H__36B8D658_944F_4236_ADA5_C25C5FF33393
