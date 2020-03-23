/*!
 * \file   Archive.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ARCHIVE_H__2AE531B5_C127_4A0B_A947_6B304A884EAA
#define __ARCHIVE_H__2AE531B5_C127_4A0B_A947_6B304A884EAA

#include "IMetaEnum.h"
#include "IMetaClass.h"
#include "IMetaProperty.h"

BEG_XE_NAMESPACE

class Archive;
template< typename T > struct Serializable;

class XE_API Archive : public XE::NonCopyable
{
public:
	template< typename T > struct NVP
	{
		NVP( const std::string & name, T & val )
			:Name( name ), Value( val )
		{ }

		std::string Name;
		T & Value;
	};

protected:
	struct NameValue
	{
		std::string Name;
		XE::Variant Value;
	};

protected:
	Archive( ArchiveType val );

	virtual ~Archive() = default;

public:
	template< typename T > Archive & operator&( T & val )
	{
		NameValue nv;

		nv.Value = val;

		Serialize( nv );

		val = nv.Value.Value<T>();

		return *this;
	}

	template< typename T > Archive & operator&( NVP< T > & val )
	{
		NameValue nv;

		nv.Name = val.Name;

		nv.Value = val.Value;

		Serialize( nv );

		val.Value = nv.Value.Value<T>();

		return *this;
	}

public:
	template< typename T > Archive & operator&( const T & val )
	{
		NameValue nv;

		nv.Value = val;

		Serialize( nv );

		return *this;
	}

	template< typename T > Archive & operator&( const NVP< T > & val )
	{
		NameValue nv;

		nv.Name = val.Name;
		nv.Value = val.Value;

		Serialize( nv );

		return *this;
	}

public:
	ArchiveType GetType() const;

protected:
	virtual void Serialize( NameValue & val ) = 0;

private:
	ArchiveType _Type;
};

class XE_API JsonLoadArchive : public Archive
{
	struct Private;

public:
	JsonLoadArchive( std::istream & val );

	~JsonLoadArchive() override;

protected:
	void Serialize( NameValue & val ) override;

private:
	Private * _p;
};

class XE_API JsonSaveArchive : public Archive
{
	struct Private;
public:
	JsonSaveArchive();

	~JsonSaveArchive() override;

public:
	void Save( std::ostream & val ) const;

protected:
	void Serialize( NameValue & val ) override;

private:
	Private * _p;
};

class XE_API BinaryLoadArchive : public Archive
{
	struct Private;

public:
	BinaryLoadArchive( XE::memory_view & val );

	~BinaryLoadArchive() override;

protected:
	void Serialize( NameValue & val ) override;

private:
	Private * _p;
};

class XE_API BinarySaveArchive : public Archive
{
	struct Private;
public:
	BinarySaveArchive();

	~BinarySaveArchive() override;

public:
	void Save( std::ostream & val ) const;

protected:
	void Serialize( NameValue & val ) override;

private:
	Private * _p;
};


template< typename T > struct Cloneable
{
public:
	static T * Clone( T * val )
	{
		if( auto cls = ClassID<T>::Get( val ) )
		{
			return cls->Clone( val ).Value<T *>();
		}

		return nullptr;
	}

	static XE::SharedPtr<T> Clone( XE::SharedPtr<T> val )
	{
		if( auto cls = ClassID<T>::Get( val.get() ) )
		{
			return XE::SharedPtr<T>( cls->Clone( val.get() ).Value<T *>() );
		}

		return nullptr;
	}
};

template< typename T > struct Serializable
{
public:
	template< typename U > struct HasMemberSerialize
	{
	private:
		template <typename Ty, void( Ty:: * )( Archive & ) = &Ty::Serialize>
		static constexpr auto check( Ty * ) { return true; };

		static constexpr bool check( ... ) { return false; };

	public:
		static constexpr bool value = check( static_cast< U * >( nullptr ) );
	};

public:
	static void Serialize( Archive & arc, T * val )
	{
		if constexpr( HasMemberSerialize<T>::value )
		{
			val->Serialize( arc );
		}
		else
		{
			if( auto cls = ClassID<T>::Get( val ) )
			{
				cls->VisitProperty( [&]( IMetaPropertyPtr prop )
									{
										if( !prop->IsConst() && !prop->IsStatic() && !( prop->GetFlag() & IMetaProperty::NoSerialize ) )
										{
											Variant v = prop->Get( val );

											auto nvp = Archive::NVP( prop->GetName(), v );

											arc & nvp;

											prop->Set( val, v );
										}
									} );
			}
		}
	}
};

END_XE_NAMESPACE

#endif // __ARCHIVE_H__2AE531B5_C127_4A0B_A947_6B304A884EAA
