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

class REFLECT_API Archive : public NonCopyable
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
	Archive() = default;

	virtual ~Archive() = default;

public:
	template< typename T > Archive & operator&( T & val )
	{
		NameValue nv;

		if constexpr( std::is_enum_v<T> )
		{
			nv.Value = val;
			Serialize( nv );
			val = nv.Value.Value<T>();
		}
		else
		{
			nv.Value = &val;
			Serialize( nv );
			val = nv.Value.Value<T &>();
		}

		return *this;
	}

	template< typename T > Archive & operator&( T *& val )
	{
		NameValue nv;

		nv.Value = val;

		Serialize( nv );

		val = static_cast< T * >( nv.Value.Detach() );

		return *this;
	}

	template< typename T > Archive & operator&( std::shared_ptr< T > & val )
	{
		NameValue nv;

		nv.Value = val;

		Serialize( nv );

		val = SP_CAST<T>( nv.Value.DetachPtr() );

		return *this;
	}

	template< typename T > Archive & operator&( NVP< T > & val )
	{
		NameValue nv;

		nv.Name = val.Name;

		if constexpr( std::is_pointer_v<T> )
		{
			nv.Value = val.Value;
			Serialize( nv );
			val.Value = static_cast< T * >( nv.Value.Detach() );
		}
		else if constexpr( std::is_shared_ptr_v<T> )
		{
			nv.Value = val.Value;
			Serialize( nv );
			val.Value = SP_CAST< typename T::element_type >( nv.Value.DetachPtr() );
		}
		else
		{
			nv.Value = &val.Value;
			Serialize( nv );
			val.Value = nv.Value.Value<T &>();
		}

		return *this;
	}

protected:
	virtual void Serialize( NameValue & val ) = 0;

};

class REFLECT_API JsonLoadArchive : public Archive
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

class REFLECT_API JsonSaveArchive : public Archive
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

class REFLECT_API BinaryLoadArchive : public Archive
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

class REFLECT_API BinarySaveArchive : public Archive
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


template< typename T > struct Serializable
{
public:
	template<typename U> struct HasMemberLoad
	{
	private:
		template <typename Ty, void( Ty:: * )( Archive & ) = &Ty::Load>
		static constexpr auto check( Ty * ) { return true; };

		static constexpr bool check( ... ) { return false; };

	public:
		static constexpr bool value = check( static_cast< U * >( nullptr ) );
	};

	template<typename U> struct HasMemberSave
	{
		template <typename Ty, void( Ty:: * )( Archive & ) = &Ty::Save>
		static constexpr bool check( Ty * ) { return true; };

		static constexpr bool check( ... ) { return false; };

	public:
		static constexpr bool value = check( static_cast< U * >( nullptr ) );
	};

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
										if( !prop->IsConst() && !prop->IsStatic() )
										{
											Variant v = prop->Get( val );
											arc & v;
											prop->Set( val, v );
										}
									} );
			}
		}
	}
};

END_XE_NAMESPACE

#endif // __ARCHIVE_H__2AE531B5_C127_4A0B_A947_6B304A884EAA
