/*!
 * \file   IMetaClass.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETACLASS_H__0775C1BF_63EA_4CCE_84ED_90EBF29B082B
#define __IMETACLASS_H__0775C1BF_63EA_4CCE_84ED_90EBF29B082B

#include "IMetaType.h"
#include "ParameterType.hpp"

BEG_XE_NAMESPACE

class Archive;

class REFLECT_API IMetaClass : public IMetaType
{
public:
	IMetaClass( const String& Name, XE::uint64 Size, bool IsAbs, bool IsSin, IMetaClassPtr Super, IMetaInfoPtr Owner );

	~IMetaClass();

public:
	bool IsAbstract() const;

	bool IsSingleton() const;

public:
	bool CanConvert( const IMetaClassPtr& val ) const;

public:
	IMetaClassPtr GetSuper() const;

public:
	void VisitMethod( std::function<void( IMetaMethodPtr )> val ) const;

	void VisitProperty( std::function<void( IMetaPropertyPtr )> val ) const;

	void VisitOperator( std::function<void( IMetaOperatorPtr )> val ) const;

	void VisitDerivedClass( std::function<void( IMetaClassPtr )> val ) const;

public:
	IMetaMethodPtr FindMethod( const String& Name, const ParameterType& Types = MakeParameterType() ) const;

	IMetaPropertyPtr FindProperty( const String& Name ) const;

	IMetaOperatorPtr FindOperator( const String& Name, const IMetaInfoPtr& Type = nullptr ) const;

public:
	virtual void * Construct() const = 0;

	virtual std::shared_ptr<void> ConstructPtr() const = 0;

	virtual void Destruct( void * val ) const = 0;

protected:
	void _RegisterMethod( const IMetaMethodPtr& val );

	void _RegisterProperty( const IMetaPropertyPtr& val );

	void _RegisterOperator( const IMetaOperatorPtr& val );

private:
	bool _IsAbstract;
	bool _IsSingleton;
	IMetaClassWPtr _Super;
	Array< IMetaMethodPtr > _Methods;
	Array< IMetaPropertyPtr > _Propertys;
	Array< IMetaOperatorPtr > _Operators;
	Array< IMetaClassPtr > _DerivedClasses;
};

END_XE_NAMESAPCE

#endif // __IMETACLASS_H__0775C1BF_63EA_4CCE_84ED_90EBF29B082B
