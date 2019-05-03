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
	static constexpr uint64 Version = ( ( (uint64)1 ) << 48 ) | ( ( (uint64)1 ) << 32 ) | ( ( (uint64)1 ) << 16 ) | ( ( (uint64)1 ) << 0 );

protected:
	Archive( ArchiveType val );

	virtual ~Archive();

public:
	uint64 GetVersion() const;

	ArchiveType GetType() const;

protected:
	void SetVersion( uint64 val );

public:
	template< typename T > Archive& operator&( T &val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = &val;

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

	template< typename T > Archive& operator&( const T &val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = &const_cast<T&>( val );

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

	template< typename T > Archive& operator&( T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = val;

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

	template< typename T > Archive& operator&( const T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = const_cast<T*>( val );

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

	template< typename T > Archive& operator&( const std::weak_ptr<T>& val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = val.lock().get();

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

	template< typename T > Archive& operator&( const std::shared_ptr<T>& val )
	{
		using type = typename TypeTraits<T>::raw_t;

		auto p = val.get();

		if ( auto meta = TypeID<type>::Get( p ) )
		{
			Variant v( p );
			meta->Serialize( this, v );
		}

		return *this;
	}

public:
	virtual void Serialize( bool * ptr ) = 0;

	virtual void Serialize( int8 * ptr ) = 0;

	virtual void Serialize( int16 * ptr ) = 0;

	virtual void Serialize( int32 * ptr ) = 0;

	virtual void Serialize( int64 * ptr ) = 0;

	virtual void Serialize( uint8 * ptr ) = 0;

	virtual void Serialize( uint16 * ptr ) = 0;

	virtual void Serialize( uint32 * ptr ) = 0;

	virtual void Serialize( uint64 * ptr ) = 0;

	virtual void Serialize( float * ptr ) = 0;

	virtual void Serialize( double * ptr ) = 0;

	virtual void Serialize( void * ptr, XE::uint64 size ) = 0;

private:
	uint64 _Version;
	ArchiveType _Type;
};

class REFLECT_API ArchiveLoad : public Archive
{
public:
	ArchiveLoad( std::istream& val );

	~ArchiveLoad();

public:
	virtual void Serialize( bool * ptr ) override;

	virtual void Serialize( int8 * ptr ) override;

	virtual void Serialize( int16 * ptr ) override;

	virtual void Serialize( int32 * ptr ) override;

	virtual void Serialize( int64 * ptr ) override;

	virtual void Serialize( uint8 * ptr ) override;

	virtual void Serialize( uint16 * ptr ) override;

	virtual void Serialize( uint32 * ptr ) override;

	virtual void Serialize( uint64 * ptr ) override;

	virtual void Serialize( float * ptr ) override;

	virtual void Serialize( double * ptr ) override;

	virtual void Serialize( void * ptr, XE::uint64 size ) override;

private:
	bool _IsConvert;
	std::istream _Stream;
};

class REFLECT_API ArchiveSave : public Archive
{
public:
	ArchiveSave( std::ostream& val );

	~ArchiveSave();

public:
	virtual void Serialize( bool * ptr ) override;

	virtual void Serialize( int8 * ptr ) override;

	virtual void Serialize( int16 * ptr ) override;

	virtual void Serialize( int32 * ptr ) override;

	virtual void Serialize( int64 * ptr ) override;

	virtual void Serialize( uint8 * ptr ) override;

	virtual void Serialize( uint16 * ptr ) override;

	virtual void Serialize( uint32 * ptr ) override;

	virtual void Serialize( uint64 * ptr ) override;

	virtual void Serialize( float * ptr ) override;

	virtual void Serialize( double * ptr ) override;

	virtual void Serialize( void * ptr, XE::uint64 size ) override;

private:
	std::ostream _Stream;
};


template< typename T > struct Serializable
{
public:
	template<typename U>
	struct HasMemberLoad
	{
	private:
		template <typename Ty, void( Ty::* )( Archive& ) = &Ty::Load>
		static constexpr auto check( Ty* ) { return true; };

		static constexpr bool check( ... ) { return false; };

	public:
		static constexpr bool value = check( static_cast<U*>( nullptr ) );
	};

	template<typename U>
	struct HasMemberSave
	{
		template <typename Ty, void( Ty::* )( Archive& ) const = &Ty::Save>
		static constexpr bool check( Ty* ) { return true; };

		static constexpr bool check( ... ) { return false; };

	public:
		static constexpr bool value = check( static_cast<U*>( nullptr ) );
	};

public:
	static void Load( Archive& arc, T & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr (HasMemberLoad<type>::value)
		{
			val.Load( arc );
		}
		else
		{
			if ( auto meta = ClassID<type>::Get( &val ) )
			{
				meta->VisitProperty( [&] ( IMetaPropertyPtr prop )
				{
					Variant v( &val );
					prop->Serialize( &arc, v );
				} );
			}
		}
	}

	static void Save( Archive& arc, T & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr (HasMemberSave<type>::value)
		{
			val.Save( arc );
		}
		else
		{
			if ( auto meta = ClassID<type>::Get( &val ) )
			{
				meta->VisitProperty( [&] ( IMetaPropertyPtr prop )
				{
					Variant v( &val );
					prop->Serialize( &arc, v );
				} );
			}
		}
	}
};

template<> struct Serializable<std::string>
{
	static void Load( Archive& arc, std::string & val )
	{
		XE::uint64 sz = 0;

		arc.Serialize( &sz, sizeof( XE::uint64 ) );

		val.resize( sz, 0 );

		arc.Serialize( (void*)val.data(), sz );
	}

	static void Save( Archive& arc, std::string & val )
	{
		XE::uint64 sz = val.size();

		arc.Serialize( &sz, sizeof( XE::uint64 ) );

		arc.Serialize( (void*)val.data(), sz );
	}
};

template<> struct Serializable<String>
{
	static void Load( Archive& arc, String & val )
	{
		std::string s = val.ToStdString();
		Serializable<std::string>::Load( arc, s );
		val = s;
	}

	static void Save( Archive& arc, String & val )
	{
		std::string s = val.ToStdString();
		Serializable<std::string>::Load( arc, s );
	}
};

template<> struct Serializable<Variant>
{
	static void Load( Archive& arc, Variant & val )
	{
		std::string meta_name;
		Serializable<std::string>::Load( arc, meta_name );

		uint64 flag;
		arc.Serialize( &flag, sizeof( uint64 ) );

		if ( IMetaTypePtr meta = GetReclectionType( meta_name ) )
		{
			Variant::UnionData d;
			val = Variant( meta, d, flag );

			meta->Serialize( &arc, val );
		}
	}

	static void Save( Archive& arc, Variant & val )
	{
		std::string meta_name = val.GetMeta()->GetFullName().ToStdString();
		Serializable<std::string>::Save( arc, meta_name );

		uint64 flag = val.GetFlag();
		arc.Serialize( &flag, sizeof( uint64 ) );

		if ( auto e = SP_CAST<IMetaType>( val.GetMeta() ) )
		{
			e->Serialize( &arc, val );
		}
	}
};

END_XE_NAMESAPCE

#endif // __ARCHIVE_H__2AE531B5_C127_4A0B_A947_6B304A884EAA
