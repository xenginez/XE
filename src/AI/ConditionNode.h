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

#include "Node.h"

BEG_XE_NAMESPACE

class XE_API ConditionNode : public XE::Node
{
	OBJECT( ConditionNode, Node )

public:
	ConditionNode();

	~ConditionNode();

public:
	NodeHandle GetChild() const;

	NodeHandle AddChild( const IMetaClassPtr & val );

	void RemoveChild();

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

	void OnRemove() override;

	void OnResetHandle() override;

public:
	virtual bool ConditionalJudgment() const = 0;

private:
	NodeHandle _Child;
	bool _MultiJudgment;
};

END_XE_NAMESPACE

#endif // CONDITIONNODE_H__6EC1A1E4_3026_416A_8F03_7C5BDD9A391A
