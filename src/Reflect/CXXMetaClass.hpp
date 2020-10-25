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

#include "CXXMetaMethod.hpp"
#include "CXXMetaOperator.hpp"
#include "CXXMetaProperty.hpp"

BEG_XE_NAMESPACE

template< typename ClassType > class CXXMetaClass : public IMetaClass
{
public:
	CXXMetaClass( const String& Name, IMetaClassPtr Super, IMetaInfoPtr Owner )
		:IMetaClass( Name, sizeof( ClassType ), std::is_abstract_v<ClassType>, std::is_base_of<XE::Singleton<ClassType>, ClassType>::value, Super, Owner )
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
	template< typename Result, typename ... Types > void Method( const String& Name, Result( *Callback )( Types... ) )
	{
		auto method = XE::MakeShared< CXXMetaMethod< Result( *)( Types... )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Result, typename ... Types > void Method( const String& Name, Result( ClassType::*Callback )( Types... ) )
	{
		auto method = XE::MakeShared< CXXMetaMethod<Result( ClassType::* )( Types... )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Result, typename ... Types > void Method( const String& Name, Result( ClassType::*Callback )( Types... ) const )
	{
		auto method = XE::MakeShared< CXXMetaMethod<Result( ClassType::* )( Types... ) const> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Value > void Property( const String& Name, Value * Prop, XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<Value>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename Value > void Property( const String& Name, Value( ClassType::*Prop ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<Value( ClassType::* )>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( *Get )( ), void( *Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( *)( ), void( *)( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ), void( ClassType::*Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType::* )( ), void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ) const, void( ClassType::*Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType::* )( ) const, void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType > void Property( const String & Name, GetType( *Get )( ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( * )( )>>( Name, Get, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType > void Property( const String & Name, GetType( ClassType:: * Get )( ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<GetType( ClassType:: * )( )>>( Name, Get, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename SetType > void Property( const String & Name, void( *Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<void( * )( SetType )>>( Name, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename SetType > void Property( const String & Name, void( ClassType:: * Set )( SetType ), XE::uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::MakeShared<CXXMetaProperty<void( ClassType:: * )( SetType )>>( Name, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) const )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) const )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( ClassType::* )( Right ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType * ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType * )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType & ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType & )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType *, Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType *, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType &, Right ) )
	{
		auto oper = XE::MakeShared<CXXMetaOperator<Result( *)( ClassType &, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

};

template< typename ClassType > class CXXMetaFundamental : public IMetaClass
{
public:
	CXXMetaFundamental( const String& Name )
		:IMetaClass( Name, sizeof( ClassType ), false, false, nullptr, nullptr, "" )
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


template<> struct XE_API ClassID< void >
{
	static IMetaClassPtr Get( const void * val = nullptr )
	{
		return nullptr;
	}
};

template<> struct XE_API ClassID< std::nullptr_t >
{
	static IMetaClassPtr Get( const std::nullptr_t * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<std::nullptr_t> >( "null" );
		return meta;
	}
};

template<> struct XE_API ClassID< bool >
{
	static IMetaClassPtr Get( const bool * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<bool> >( "bool" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::int8 >
{
	static IMetaClassPtr Get( const XE::int8 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::int8> >( "int8" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::int16 >
{
	static IMetaClassPtr Get( const XE::int16 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::int16> >( "int16" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::int32 >
{
	static IMetaClassPtr Get( const XE::int32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::int32> >( "int32" );
		return meta;
	}
};

template<> struct XE_API ClassID< long >
{
	static IMetaClassPtr Get( const long * val = nullptr )
	{
		return ClassID< XE::int32 >::Get();
	}
};

template<> struct XE_API ClassID< XE::int64 >
{
	static IMetaClassPtr Get( const XE::int64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::int64> >( "int64" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::uint8 >
{
	static IMetaClassPtr Get( const XE::uint8 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::uint8> >( "uint8" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::uint16 >
{
	static IMetaClassPtr Get( const XE::uint16 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::uint16> >( "uint16" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::uint32 >
{
	static IMetaClassPtr Get( const XE::uint32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::uint32> >( "uint32" );
		return meta;
	}
};

template<> struct XE_API ClassID< unsigned long >
{
	static IMetaClassPtr Get( const unsigned long * val = nullptr )
	{
		return ClassID< XE::uint32 >::Get();
	}
};

template<> struct XE_API ClassID< XE::uint64 >
{
	static IMetaClassPtr Get( const XE::uint64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::uint64> >( "uint64" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::float32 >
{
	static IMetaClassPtr Get( const XE::float32 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::float32> >( "float32" );
		return meta;
	}
};

template<> struct XE_API ClassID< XE::float64 >
{
	static IMetaClassPtr Get( const XE::float64 * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaFundamental<XE::float64> >( "float64" );
		return meta;
	}
};

template<> struct XE_API ClassID< Variant >
{
	static IMetaClassPtr Get( const Variant * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<Variant> >( "Variant", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API TypeID< Variant >
{
	static IMetaTypePtr Get( const Variant * val = nullptr )
	{
		if( val != nullptr && val->IsInvalid() == false )
		{
			return val->GetType();
		}

		return ClassID<Variant>::Get();
	}
};


template<> struct XE_API ClassID< String >
{
	static IMetaClassPtr Get( const String * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<String> >( "String", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< FileSystem::Path >
{
	static IMetaClassPtr Get( const FileSystem::Path * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<String> >( "Path", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantList >
{
	static IMetaClassPtr Get( const VariantList * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantList> >( "List", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantDeque >
{
	static IMetaClassPtr Get( const VariantDeque * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantDeque> >( "Deque", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantStack >
{
	static IMetaClassPtr Get( const VariantStack * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantStack> >( "Stack", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantQueue >
{
	static IMetaClassPtr Get( const VariantQueue * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantQueue> >( "Queue", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantArray >
{
	static IMetaClassPtr Get( const VariantArray * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantArray> >( "Array", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantPair >
{
	static IMetaClassPtr Get( const VariantPair * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantPair> >( "Pair", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantSet >
{
	static IMetaClassPtr Get( const VariantSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantSet> >( "Set", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantMap >
{
	static IMetaClassPtr Get( const VariantMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantMap> >( "Map", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantMultiSet >
{
	static IMetaClassPtr Get( const VariantMultiSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantMultiSet> >( "MultiSet", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantMultiMap >
{
	static IMetaClassPtr Get( const VariantMultiMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantMultiMap> >( "MultiMap", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantUnorderedSet >
{
	static IMetaClassPtr Get( const VariantUnorderedSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantUnorderedSet> >( "UnorderedSet", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantUnorderedMap >
{
	static IMetaClassPtr Get( const VariantUnorderedMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantUnorderedMap> >( "UnorderedMap", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantUnorderedMultiSet >
{
	static IMetaClassPtr Get( const VariantUnorderedMultiSet * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantUnorderedMultiSet> >( "UnorderedMultiSet", nullptr, nullptr );
		return meta;
	}
};

template<> struct XE_API ClassID< VariantUnorderedMultiMap >
{
	static IMetaClassPtr Get( const VariantUnorderedMultiMap * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<VariantUnorderedMultiMap> >( "UnorderedMultiMap", nullptr, nullptr );
		return meta;
	}
};


template<> struct XE_API ClassID< XE::MemoryView >
{
	static IMetaClassPtr Get( const XE::MemoryView * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass<XE::MemoryView> >( "MemoryView", nullptr, nullptr );
		return meta;
	}
};

template<typename T> struct ClassID< XE::BasicMemoryView< T > >
{
	static IMetaClassPtr Get( const XE::BasicMemoryView< T > * val = nullptr )
	{
		return ClassID< XE::MemoryView >::Get( nullptr );
	}
};

template<typename ... Types> struct ClassID< std::basic_string<Types...> >
{
	static IMetaClassPtr Get( const std::basic_string<Types...> * val = nullptr )
	{
		return ClassID<String>::Get();
	}
};

template<typename ... Types> struct ClassID< std::list<Types...> >
{
	static IMetaClassPtr Get( const std::list<Types...> * val = nullptr )
	{
		return ClassID<VariantList>::Get();
	}
};

template<typename ... Types> struct ClassID< std::deque<Types...> >
{
	static IMetaClassPtr Get( const std::deque<Types...> * val = nullptr )
	{
		return ClassID<VariantDeque>::Get();
	}
};

template<typename ... Types> struct ClassID< std::stack<Types...> >
{
	static IMetaClassPtr Get( const std::stack<Types...> * val = nullptr )
	{
		return ClassID<VariantStack>::Get();
	}
};

template<typename ... Types> struct ClassID< std::queue<Types...> >
{
	static IMetaClassPtr Get( const std::queue<Types...> * val = nullptr )
	{
		return ClassID<VariantQueue>::Get();
	}
};

template<typename ... Types> struct ClassID< std::array<Types...> >
{
	static IMetaClassPtr Get( const std::array<Types...> * val = nullptr )
	{
		return ClassID<VariantArray>::Get();
	}
};

template<typename ... Types> struct ClassID< std::vector<Types...> >
{
	static IMetaClassPtr Get( const std::vector<Types...> * val = nullptr )
	{
		return ClassID<VariantArray>::Get();
	}
};

template<typename ... Types> struct ClassID< std::pair<Types...> >
{
	static IMetaClassPtr Get( const std::pair<Types...> * val = nullptr )
	{
		return ClassID<VariantPair>::Get();
	}
};

template<typename ... Types> struct ClassID< std::set<Types...> >
{
	static IMetaClassPtr Get( const std::set<Types...> * val = nullptr )
	{
		return ClassID<VariantSet>::Get();
	}
};

template<typename ... Types> struct ClassID< std::map<Types...> >
{
	static IMetaClassPtr Get( const std::map<Types...> * val = nullptr )
	{
		return ClassID<VariantMap>::Get();
	}
};

template<typename ... Types> struct ClassID< std::multiset<Types...> >
{
	static IMetaClassPtr Get( const std::multiset<Types...> * val = nullptr )
	{
		return ClassID<VariantMultiSet>::Get();
	}
};

template<typename ... Types> struct ClassID< std::multimap<Types...> >
{
	static IMetaClassPtr Get( const std::multimap<Types...> * val = nullptr )
	{
		return ClassID<VariantMultiMap>::Get();
	}
};

END_XE_NAMESPACE

#define DECL_META_CLASS_3(_DLL_EXPORT, _CLASS, _SUPER) \
template<> struct _DLL_EXPORT XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, XE::ClassID<_SUPER>::Get(), nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_2(_DLL_EXPORT, _CLASS) \
template<> struct _DLL_EXPORT XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS(...)            MACRO_EXP_(MACRO_GLUE(DECL_META_CLASS_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#define DECL_META_CLASS_P_2(_CLASS, _SUPER) \
template<> struct XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, XE::ClassID<_SUPER>::Get(), nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_P_1(_CLASS) \
template<> struct XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_P(...)            MACRO_EXP_(MACRO_GLUE(DECL_META_CLASS_P_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#endif // __CXXMETACLASS_HPP__B0EBC0E5_97E9_4A1F_B8EE_EF87D334D01A
