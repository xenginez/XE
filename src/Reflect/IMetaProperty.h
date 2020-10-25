/*!
 * \file   IMetaProperty.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETAPROPERTY_H__5D5C09CC_58EB_41F1_9D84_BD6FC0BCB621
#define __IMETAPROPERTY_H__5D5C09CC_58EB_41F1_9D84_BD6FC0BCB621

#include "IMetaInfo.h"
#include "Variant.h"

BEG_XE_NAMESPACE

class Archive;

class XE_API IMetaProperty : public IMetaInfo
{
public:
	static constexpr XE::uint8 Default = 0;
	static constexpr XE::uint8 NoClone = 1 << 1;
	static constexpr XE::uint8 NoDesign  = 1 << 2;
	static constexpr XE::uint8 NoRuntime = 1 << 3;
	static constexpr XE::uint8 NoSerialize = 1 << 4;
	static constexpr XE::uint8 NoRead = 1 << 5;
	static constexpr XE::uint8 NoWirte = 1 << 6;

public:
	IMetaProperty( const String& Name, XE::uint8 Flag, bool IsStatic, bool IsConst, bool IsObject, bool IsPointer, bool IsSharedPtr, bool IsReference, IMetaInfoPtr Value, IMetaClassPtr Owner, const String & ModuleName = "XE" );

	~IMetaProperty();

public:
	bool IsConst() const;

	bool IsStatic() const;

	bool IsObject() const;

	bool IsPointer() const;

	bool IsSharedPtr() const;

	bool IsReference() const;

public:
	XE::uint8 GetFlag() const;

	IMetaInfoPtr GetValue() const;

public:
	virtual Variant Get( const Variant& obj ) const = 0;

	virtual void Set( const Variant& obj, const Variant& val ) const = 0;

private:
	XE::uint8 _Flag;
	bool _IsConst;
	bool _IsStatic;
	bool _IsObject;
	bool _IsPointer;
	bool _IsSharedPtr;
	bool _IsReference;
	IMetaInfoWPtr _Value;
};

END_XE_NAMESPACE

#endif // __IMETAPROPERTY_H__5D5C09CC_58EB_41F1_9D84_BD6FC0BCB621
