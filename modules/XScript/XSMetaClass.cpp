#include "XSMetaClass.h"

USING_XE

XE::XSMetaClass::XSMetaClass( const String & Name, XE::uint64 Size, IMetaClassPtr Super, IMetaInfoPtr Owner, const String & ModuleName )
	:IMetaClass( Name, Size, false, false, Super, Owner, ModuleName )
{

}

XE::XSMetaClass::~XSMetaClass()
{

}

XE::Variant XE::XSMetaClass::Construct( void * ptr ) const
{
	void * p = ptr;

	if( ptr == nullptr )
	{
		p = XE::Alloc::Allocate( GetSize() );
	}

	std::memset( p, 0, GetSize() );

	if( GetSuper() )
	{
		GetSuper()->Construct( p );
	}

	return Variant( CP_CAST<IMetaInfo>( shared_from_this() ), Variant::UnionData( p ), Variant::POINTER );
}

XE::Variant XE::XSMetaClass::ConstructPtr( std::shared_ptr<void> ptr ) const
{
	std::shared_ptr<void> p = ptr;

	if( ptr == nullptr )
	{
		p = std::shared_ptr<void>( XE::Alloc::Allocate( GetSize() ) );
	}

	std::memset( p.get(), 0, GetSize() );

	if( GetSuper() )
	{
		GetSuper()->ConstructPtr( p );
	}

	return Variant( CP_CAST<IMetaInfo>( shared_from_this() ), std::shared_ptr<void>( p ), Variant::SHAREDPTR );
}

void XE::XSMetaClass::Destruct( Variant & val ) const
{
	if( GetSuper() )
	{
		GetSuper()->Destruct( val );
	}

	VisitProperty( [val]( IMetaPropertyPtr prop )
				   {
					   prop->Set( val, nullptr );
				   }
	);
}

void XE::XSMetaClass::Serialize( Archive * arc, Variant & val ) const
{
	if( GetSuper() )
	{
		GetSuper()->Serialize( arc, val );
	}

	VisitProperty( [&]( IMetaPropertyPtr prop )
						{
							if( !prop->IsConst() && !prop->IsStatic() )
							{
								Variant v = prop->Get( val );
								( *arc ) & v;
								prop->Set( val, v );
							}
						} );
}
