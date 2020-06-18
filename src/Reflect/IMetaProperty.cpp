#include "IMetaProperty.h"

#include "IMetaClass.h"



XE::IMetaProperty::IMetaProperty( const String & Name, XE::uint8 Flag, bool IsStatic, bool IsConst, bool IsObject, bool IsPointer, bool IsSharedPtr, bool IsReference, IMetaInfoPtr Value, IMetaClassPtr Owner, const String & ModuleName /*= "XE" */ )
	:IMetaInfo( Name, MetaType::PROPERTY, SP_CAST<IMetaInfo>( Owner ), ModuleName ), _Flag( Flag ), _IsStatic( IsStatic ), _IsConst( IsConst ), _IsObject( IsObject ), _IsPointer( IsPointer ), _IsSharedPtr( IsSharedPtr ), _IsReference( IsReference ), _Value( Value )
{

}

XE::IMetaProperty::~IMetaProperty()
{

}

bool XE::IMetaProperty::IsConst() const
{
	return _IsConst;
}

bool XE::IMetaProperty::IsStatic() const
{
	return _IsStatic;
}

bool XE::IMetaProperty::IsObject() const
{
	return _IsObject;
}

bool XE::IMetaProperty::IsPointer() const
{
	return _IsPointer;
}

bool XE::IMetaProperty::IsSharedPtr() const
{
	return _IsSharedPtr;
}

bool XE::IMetaProperty::IsReference() const
{
	return _IsReference;
}

XE::IMetaInfoPtr XE::IMetaProperty::GetValue() const
{
	return _Value.lock();
}

XE::uint8 XE::IMetaProperty::GetFlag() const
{
	return _Flag;
}
