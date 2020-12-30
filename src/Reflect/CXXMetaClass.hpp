/*!
 * \file   CXXMetaClass.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CXXMETACLASS_HPP__B0EBC0E5_97E9_4A1F_B8EE_EF87D334D01A
#define __CXXMETACLASS_HPP__B0EBC0E5_97E9_4A1F_B8EE_EF87D334D01A

#include "IMetaClass.h"

#include "Archive.h"
#include "IMetaModule.h"
#include "CXXMetaMethod.hpp"
#include "CXXMetaOperator.hpp"
#include "CXXMetaProperty.hpp"

BEG_XE_NAMESPACE

template< typename ClassType > class CXXMetaClass : public IMetaClass
{
public:
	CXXMetaClass( const String& Name, IMetaClassPtr Super, IMetaInfoPtr Owner, IMetaModulePtr Module )
		:IMetaClass( Name, sizeof( ClassType ), std::is_abstract_v<ClassType>, std::is_base_of<XE::Singleton<ClassType>, ClassType>::value, Super, Owner, Module )
	{
	}

public:
	virtual Variant ConstructPtr( XE::SharedPtr<void> ptr ) const override
	{
		if constexpr ( !std::is_abstract_v<ClassType> )
		{
			if( ptr != nullptr )
			{
				new ( ptr.get() ) ClassType();

				return SP_CAST<ClassType>( ptr );
			}

			return XE::MakeShared<ClassType>();
		}
		else
		{
			throw MetaException( shared_from_this(), "is abstract type!" );
		}
	}

	virtual Variant Clone( const Variant & val ) const override
	{
		auto ret = ConstructPtr( nullptr );

		VisitProperty( [&]( IMetaPropertyPtr prop )
					   {
						   prop->Set( ret, prop->Get( val ) );
					   } );

		return ret;
	}

	virtual void Destruct( Variant & val ) const override
	{
		( (ClassType * )val.ToPointer() )->~ClassType();
	}

	virtual void Serialize( Archive * arc, Variant& val ) const override
	{
		Serializable<ClassType>::Serialize( *arc, val.Value<ClassType *>() );
	}

public:
	template< typename Result, typename T > void Method( const String& Name, Result( *Callback )( T ) )
	{
		auto method = XE::MakeShared< CXXMetaMethod< Result( *)( T )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterMethod( method );
	}

	template< typename Result, typename T > void Method( const String& Name, Result( ClassType::*Callback )( T ) )
	{
		auto method = XE::MakeShared< CXXMetaMethod<Result( ClassType::* )( T )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterMethod( method );
	}

	template< typename Result, typename T > void Method( const String& Name, Result( ClassType::*Callback )( T ) const )
	{
		auto method = XE::MakeShared< CXXMetaMethod<Result( ClassType::* )( T ) const> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterMethod( method );
	}

	template< typename Value > void Property( const String& Name, Value * Prop, XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<Value>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename Value > void Property( const String& Name, Value( ClassType::*Prop ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<Value( ClassType::* )>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( *Get )( ), void( *Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( *)( ), void( *)( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ), void( ClassType::*Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType::* )( ), void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ) const, void( ClassType::*Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType::* )( ) const, void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename GetType > void Property( const String & Name, GetType( *Get )( ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( * )( )>>( Name, Get, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename GetType > void Property( const String & Name, GetType( ClassType:: * Get )( ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType:: * )( )>>( Name, Get, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename SetType > void Property( const String & Name, void( *Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<void( * )( SetType )>>( Name, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename SetType > void Property( const String & Name, void( ClassType:: * Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<void( ClassType:: * )( SetType )>>( Name, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterProperty( prop );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) const )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) const )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( Right ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType * ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType * )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType & ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType & )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType *, Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType *, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType &, Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType &, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ), GetModule() );
		_RegisterOperator( oper );
	}

};

template< typename ClassType > class CXXMetaFundamental : public IMetaClass
{
public:
	CXXMetaFundamental( const String& Name )
		:IMetaClass( Name, sizeof( ClassType ), false, false, nullptr, nullptr, nullptr )
	{
	}

public:
	virtual Variant ConstructPtr( XE::SharedPtr<void> ptr ) const override
	{
		if( ptr != nullptr )
		{
			return SP_CAST<ClassType>( ptr );
		}

		return XE::MakeShared<ClassType>();
	}

	virtual Variant Clone( const Variant & val ) const override
	{
		return val;
	}

	virtual void Destruct( Variant & val ) const override
	{

	}

	virtual void Serialize( Archive * arc, Variant& val ) const override
	{

	}
};


template<> struct XE_API ::XE_ClassID< void >
{
	static XE::IMetaClassPtr Get( const void * val = nullptr )
	{
		return nullptr;
	}
};

template<> struct XE_API ::XE_ClassID< std::nullptr_t >
{
	static XE::IMetaClassPtr Get( const std::nullptr_t * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<std::nullptr_t> >( "null" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< bool >
{
	static XE::IMetaClassPtr Get( const bool * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<bool> >( "bool" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::int8 >
{
	static XE::IMetaClassPtr Get( const XE::int8 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::int8> >( "int8" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::int16 >
{
	static XE::IMetaClassPtr Get( const XE::int16 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::int16> >( "int16" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::int32 >
{
	static XE::IMetaClassPtr Get( const XE::int32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::int32> >( "int32" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< long >
{
	static XE::IMetaClassPtr Get( const long * val = nullptr )
	{
		return ::XE_ClassID< XE::int32 >::Get();
	}
};

template<> struct XE_API ::XE_ClassID< XE::int64 >
{
	static XE::IMetaClassPtr Get( const XE::int64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::int64> >( "int64" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::uint8 >
{
	static XE::IMetaClassPtr Get( const XE::uint8 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::uint8> >( "uint8" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::uint16 >
{
	static XE::IMetaClassPtr Get( const XE::uint16 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::uint16> >( "uint16" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::uint32 >
{
	static XE::IMetaClassPtr Get( const XE::uint32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::uint32> >( "uint32" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< unsigned long >
{
	static XE::IMetaClassPtr Get( const unsigned long * val = nullptr )
	{
		return ::XE_ClassID< XE::uint32 >::Get();
	}
};

template<> struct XE_API ::XE_ClassID< XE::uint64 >
{
	static XE::IMetaClassPtr Get( const XE::uint64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::uint64> >( "uint64" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::float32 >
{
	static XE::IMetaClassPtr Get( const XE::float32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::float32> >( "float32" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::float64 >
{
	static XE::IMetaClassPtr Get( const XE::float64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaFundamental<XE::float64> >( "float64" );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::Variant >
{
	static XE::IMetaClassPtr Get( const XE::Variant * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::Variant> >( "Variant", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API XE_TypeID< XE::Variant >
{
	static XE::IMetaTypePtr Get( const XE::Variant * val = nullptr )
	{
		if( val != nullptr && val->IsInvalid() == false )
		{
			return val->GetType();
		}

		return ::XE_ClassID<XE::Variant>::Get();
	}
};


template<> struct XE_API ::XE_ClassID< XE::String >
{
	static XE::IMetaClassPtr Get( const XE::String * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::String> >( "String", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::FileSystem::Path >
{
	static XE::IMetaClassPtr Get( const XE::FileSystem::Path * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::String> >( "Path", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantList >
{
	static XE::IMetaClassPtr Get( const XE::VariantList * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantList> >( "List", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantDeque >
{
	static XE::IMetaClassPtr Get( const XE::VariantDeque * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantDeque> >( "Deque", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantStack >
{
	static XE::IMetaClassPtr Get( const XE::VariantStack * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantStack> >( "Stack", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantQueue >
{
	static XE::IMetaClassPtr Get( const XE::VariantQueue * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantQueue> >( "Queue", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantArray >
{
	static XE::IMetaClassPtr Get( const XE::VariantArray * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantArray> >( "Array", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantPair >
{
	static XE::IMetaClassPtr Get( const XE::VariantPair * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantPair> >( "Pair", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantSet >
{
	static XE::IMetaClassPtr Get( const XE::VariantSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantSet> >( "Set", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantMap >
{
	static XE::IMetaClassPtr Get( const XE::VariantMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantMap> >( "Map", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantMultiSet >
{
	static XE::IMetaClassPtr Get( const XE::VariantMultiSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantMultiSet> >( "MultiSet", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantMultiMap >
{
	static XE::IMetaClassPtr Get( const XE::VariantMultiMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantMultiMap> >( "MultiMap", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantUnorderedSet >
{
	static XE::IMetaClassPtr Get( const XE::VariantUnorderedSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantUnorderedSet> >( "UnorderedSet", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantUnorderedMap >
{
	static XE::IMetaClassPtr Get( const XE::VariantUnorderedMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantUnorderedMap> >( "UnorderedMap", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantUnorderedMultiSet >
{
	static XE::IMetaClassPtr Get( const XE::VariantUnorderedMultiSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantUnorderedMultiSet> >( "UnorderedMultiSet", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<> struct XE_API ::XE_ClassID< XE::VariantUnorderedMultiMap >
{
	static XE::IMetaClassPtr Get( const XE::VariantUnorderedMultiMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::VariantUnorderedMultiMap> >( "UnorderedMultiMap", nullptr, nullptr, GetModule() );
		return meta;
	}
};


template<> struct XE_API ::XE_ClassID< XE::MemoryView >
{
	static XE::IMetaClassPtr Get( const XE::MemoryView * val = nullptr )
	{
		static auto meta = XE::MakeShared< XE::CXXMetaClass<XE::MemoryView> >( "MemoryView", nullptr, nullptr, GetModule() );
		return meta;
	}
};

template<typename T> struct ::XE_ClassID< XE::BasicMemoryView< T > >
{
	static XE::IMetaClassPtr Get( const XE::BasicMemoryView< T > * val = nullptr )
	{
		return ::XE_ClassID< XE::MemoryView >::Get( nullptr );
	}
};

template<typename T> struct ::XE_ClassID< std::basic_string<T> >
{
	static XE::IMetaClassPtr Get( const std::basic_string<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::String>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::List<T> >
{
	static XE::IMetaClassPtr Get( const XE::List<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantList>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::Deque<T> >
{
	static XE::IMetaClassPtr Get( const XE::Deque<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantDeque>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::Stack<T> >
{
	static XE::IMetaClassPtr Get( const XE::Stack<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantStack>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::Queue<T> >
{
	static XE::IMetaClassPtr Get( const XE::Queue<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantQueue>::Get();
	}
};

template<typename T, std::size_t N> struct ::XE_ClassID< std::array<T, N> >
{
	static XE::IMetaClassPtr Get( const std::array<T, N> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantArray>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::Array<T> >
{
	static XE::IMetaClassPtr Get( const XE::Array<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantArray>::Get();
	}
};

template<typename K, typename V> struct ::XE_ClassID< XE::Pair<K, V> >
{
	static XE::IMetaClassPtr Get( const XE::Pair<K, V> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantPair>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::Set<T> >
{
	static XE::IMetaClassPtr Get( const XE::Set<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantSet>::Get();
	}
};

template<typename K, typename V> struct ::XE_ClassID< XE::Map<K, V> >
{
	static XE::IMetaClassPtr Get( const XE::Map<K, V> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantMap>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::MultiSet<T> >
{
	static XE::IMetaClassPtr Get( const XE::MultiSet<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantMultiSet>::Get();
	}
};

template<typename K, typename V> struct ::XE_ClassID< XE::MultiMap<K, V> >
{
	static XE::IMetaClassPtr Get( const XE::MultiMap<K, V> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantMultiMap>::Get();
	}
};

template<typename T> struct ::XE_ClassID< XE::UnorderedMultiSet<T> >
{
	static XE::IMetaClassPtr Get( const XE::UnorderedMultiSet<T> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantUnorderedMultiSet>::Get();
	}
};

template<typename K, typename V> struct ::XE_ClassID< XE::UnorderedMultiMap<K, V> >
{
	static XE::IMetaClassPtr Get( const XE::UnorderedMultiMap<K, V> * val = nullptr )
	{
		return ::XE_ClassID<XE::VariantUnorderedMultiMap>::Get();
	}
};

END_XE_NAMESPACE

#define DECL_META_CLASS_3(_DLL_EXPORT, _CLASS, _SUPER) \
template<> struct _DLL_EXPORT ::XE_ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, ::XE_ClassID<_SUPER>::Get(), nullptr, GetModule() ); \
		return p; \
	} \
}
#define DECL_META_CLASS_2(_DLL_EXPORT, _CLASS) \
template<> struct _DLL_EXPORT ::XE_ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr, GetModule() ); \
		return p; \
	} \
}
#define DECL_META_CLASS(...)            MACRO_EXP_(MACRO_GLUE(DECL_META_CLASS_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#endif // __CXXMETACLASS_HPP__B0EBC0E5_97E9_4A1F_B8EE_EF87D334D01A
