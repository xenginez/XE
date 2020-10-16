/*!
 * \file	Collection.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
#define COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Collection : public XE::Object
{
	OBJECT( Collection, Object )

public:
	Collection();

	~Collection();

public:
	void FindRigidBody( const XE::String val );

	void InsertRigidBody( XE::RigidBodyHandle val );

	void RemoveRigidBody( XE::RigidBodyHandle val );

	void ContainsRigidBody( XE::RigidBodyHandle val );

	void MergeCollection( XE::CollectionHandle val );

};

END_XE_NAMESPACE

#endif // COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
