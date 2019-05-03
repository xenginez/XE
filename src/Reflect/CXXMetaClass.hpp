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
	virtual void * Construct() const override
	{
		if constexpr ( !std::is_abstract_v<ClassType> )
		{
			return new ClassType();
		}
		else
		{
			throw MetaException( shared_from_this(), "is abstract type!" );
		}
	}

	virtual std::shared_ptr<void> ConstructPtr() const override
	{
		if constexpr ( !std::is_abstract_v<ClassType> )
		{
			return XE::make_shared<ClassType>();
		}
		else
		{
			throw MetaException( shared_from_this(), "is abstract type!" );
		}
	}

	virtual void Destruct( void * val ) const override
	{
		delete (ClassType*)val;
	}

	virtual void Serialize( Archive * arc, Variant& val ) const override
	{
		if ( val.IsNull() )
		{
			if ( val.IsSharedPtr() )
			{
				val = SP_CAST<ClassType>( ConstructPtr() );
			}
			else
			{
				val = static_cast<ClassType*>( Construct() );
			}
		}

		if ( arc->GetType() == ArchiveType::LOAD )
		{
			Serializable<ClassType>::Load( *arc, val.Value<ClassType&>() );
		}
		else
		{
			Serializable<ClassType>::Save( *arc, val.Value<ClassType&>() );
		}
	}

public:
	template< typename Result, typename ... Types > void Method( const String& Name, Result( *Callback )( Types... ) )
	{
		auto method = XE::make_shared< CXXMetaMethod< Result( *)( Types... )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Result, typename ... Types > void Method( const String& Name, Result( ClassType::*Callback )( Types... ) )
	{
		auto method = XE::make_shared< CXXMetaMethod<Result( ClassType::* )( Types... )> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Result, typename ... Types > void Method( const String& Name, Result( ClassType::*Callback )( Types... ) const )
	{
		auto method = XE::make_shared< CXXMetaMethod<Result( ClassType::* )( Types... ) const> >( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterMethod( method );
	}

	template< typename Value > void Property( const String& Name, Value * Prop, uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::make_shared<CXXMetaProperty<Value>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename Value > void Property( const String& Name, Value( ClassType::*Prop ), uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::make_shared<CXXMetaProperty<Value( ClassType::* )>>( Name, Prop, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( *Get )( ), void( *Set )( SetType ), uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::make_shared<CXXMetaProperty<GetType( *)( ), void( *)( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ), void( ClassType::*Set )( SetType ), uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::make_shared<CXXMetaProperty<GetType( ClassType::* )( ), void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename GetType, typename SetType > void Property( const String& Name, GetType( ClassType::*Get )( ) const, void( ClassType::*Set )( SetType ), uint8 Flag = IMetaProperty::Default )
	{
		auto prop = XE::make_shared<CXXMetaProperty<GetType( ClassType::* )( ) const, void( ClassType::* )( SetType )>>( Name, Get, Set, Flag, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterProperty( prop );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( ClassType::* )( )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( ClassType::*Callback )( ) const )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( ClassType::* )( ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( ClassType::* )( Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( ClassType::*Callback )( Right ) const )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( ClassType::* )( Right ) const>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType * ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( *)( ClassType * )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result > void Operator( const String& Name, Result( *Callback )( ClassType & ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( *)( ClassType & )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType *, Right ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( *)( ClassType *, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

	template< typename Result, typename Right > void Operator( const String& Name, Result( *Callback )( ClassType &, Right ) )
	{
		auto oper = XE::make_shared<CXXMetaOperator<Result( *)( ClassType &, Right )>>( Name, Callback, SP_CAST<IMetaClass>( shared_from_this() ) );
		_RegisterOperator( oper );
	}

};

template< typename ClassType > class CXXMetaFundamental : public IMetaClass
{
public:
	CXXMetaFundamental( const String& Name )
		:IMetaClass( Name, sizeof( ClassType ), false, false, nullptr, nullptr )
	{
	}

public:
	virtual void * Construct() const override
	{
		return nullptr;
	}

	virtual std::shared_ptr<void> ConstructPtr() const override
	{
		return nullptr;
	}

	virtual void Destruct( void * val ) const override
	{

	}

	virtual void Serialize( Archive * arc, Variant& val ) const override
	{
		ClassType t = val.Value<ClassType>();
		arc->Serialize( &t );
	}

};

template<> class CXXMetaFundamental<std::nullptr_t> : public IMetaClass
{
public:
	CXXMetaFundamental( const String& Name )
		:IMetaClass( Name, 0, false, false, nullptr, nullptr )
	{
	}

public:
	virtual void * Construct() const override
	{
		return nullptr;
	}

	virtual std::shared_ptr<void> ConstructPtr() const override
	{
		return nullptr;
	}

	virtual void Destruct( void * val ) const override
	{

	}

	virtual void Serialize( Archive * arc, Variant& val ) const override
	{

	}

};


template<> struct REFLECT_API ClassID< void >
{
	static IMetaClassPtr Get( const void * val = nullptr )
	{
		return nullptr;
	}
};

template<> struct REFLECT_API ClassID< std::nullptr_t >
{
	static IMetaClassPtr Get( const std::nullptr_t * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<std::nullptr_t> >( "null" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< bool >
{
	static IMetaClassPtr Get( const bool * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<bool> >( "bool" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< int8 >
{
	static IMetaClassPtr Get( const int8 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<int8> >( "int8" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< int16 >
{
	static IMetaClassPtr Get( const int16 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<int16> >( "int16" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< int32 >
{
	static IMetaClassPtr Get( const int32 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<int32> >( "int32" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< int64 >
{
	static IMetaClassPtr Get( const int64 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<int64> >( "int64" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< uint8 >
{
	static IMetaClassPtr Get( const uint8 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<uint8> >( "uint8" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< uint16 >
{
	static IMetaClassPtr Get( const uint16 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<uint16> >( "uint16" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< uint32 >
{
	static IMetaClassPtr Get( const uint32 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<uint32> >( "uint32" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< uint64 >
{
	static IMetaClassPtr Get( const uint64 * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<uint64> >( "uint64" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< float >
{
	static IMetaClassPtr Get( const float * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<float> >( "float" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< double >
{
	static IMetaClassPtr Get( const double * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaFundamental<uint64> >( "double" );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< Variant >
{
	static IMetaClassPtr Get( const Variant * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<Variant> >( "Variant", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API MetaID< Variant >
{
	static IMetaInfoPtr Get( const Variant * val = nullptr )
	{
		if ( val )
		{
			return val->GetMeta();
		}

		return ClassID<Variant>::Get();
	}
};


template<> struct REFLECT_API ClassID< String >
{
	static IMetaClassPtr Get( const String * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<String> >( "String", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantList >
{
	static IMetaClassPtr Get( const VariantList * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantList> >( "List", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantDeque >
{
	static IMetaClassPtr Get( const VariantDeque * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantDeque> >( "Deque", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantStack >
{
	static IMetaClassPtr Get( const VariantStack * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantStack> >( "Stack", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantQueue >
{
	static IMetaClassPtr Get( const VariantQueue * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantQueue> >( "Queue", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantArray >
{
	static IMetaClassPtr Get( const VariantArray * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantArray> >( "Array", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantPair >
{
	static IMetaClassPtr Get( const VariantPair * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantPair> >( "Pair", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantSet >
{
	static IMetaClassPtr Get( const VariantSet * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantSet> >( "Set", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantMap >
{
	static IMetaClassPtr Get( const VariantMap * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantMap> >( "Map", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantMultiSet >
{
	static IMetaClassPtr Get( const VariantMultiSet * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantMultiSet> >( "MultiSet", nullptr, nullptr );
		return meta;
	}
};

template<> struct REFLECT_API ClassID< VariantMultiMap >
{
	static IMetaClassPtr Get( const VariantMultiMap * val = nullptr )
	{
		static auto meta = XE::make_shared< CXXMetaClass<VariantMultiMap> >( "MultiMap", nullptr, nullptr );
		return meta;
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


END_XE_NAMESAPCE

#endif // __CXXMETACLASS_HPP__B0EBC0E5_97E9_4A1F_B8EE_EF87D334D01A
