/*!
 * \file	ConditionNode.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONDITIONNODE_H__6EC1A1E4_3026_416A_8F03_7C5BDD9A391A
#define CONDITIONNODE_H__6EC1A1E4_3026_416A_8F03_7C5BDD9A391A

#include "AINode.h"

BEG_XE_NAMESPACE

class XE_API ConditionNode : public XE::AINode
{
	OBJECT( ConditionNode, AINode )

public:
	ConditionNode();

	~ConditionNode();

public:
	XE::AINodeHandle GetChild() const;

	void SetChild( XE::AINodeHandle val );

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

public:
	virtual bool ConditionalJudgment() const = 0;

private:
	bool _MultiJudgment;
	XE::AINodeHandle _Child;
};

END_XE_NAMESPACE

#endif // CONDITIONNODE_H__6EC1A1E4_3026_416A_8F03_7C5BDD9A391A
