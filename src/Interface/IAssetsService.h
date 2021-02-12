/*!
 * \file   IAssetsService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
#define __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IAssetsService : public IService
{
	OBJECT( IAssetsService, IService )

public:
	using LoadFinishCallback = std::function<void( XE::MemoryView )>;

	using LoadObjectFinishCallback = std::function<void( XE::ObjectPtr )>;

public:
	IAssetsService();

	~IAssetsService() override;

public:
    virtual XE::MemoryView Load( const XE::String & path ) = 0;

    virtual void AsyncLoad( const XE::String & path, const LoadFinishCallback & callback ) = 0;

public:
	virtual XE::ObjectPtr LoadObject( const XE::String & path ) = 0;

	virtual void AsyncLoadObject( const XE::String & path, const LoadObjectFinishCallback & callback ) = 0;

public:
	template< typename T > T LoadObjectT( const XE::String & path )
	{
		return DP_CAST< T::element_type >( LoadObject( path ) );
	}

	template< typename T > void AsyncLoadObjectT( const XE::String & path, const std::function< void( T ) > & callback )
	{
		AsyncLoadObject( path, [callback]( XE::ObjectPtr obj )
						 {
							 if( callback )
							 {
								 callback( DP_CAST< T::element_type >( obj ) );
							 }
						 } );
	}
};

END_XE_NAMESPACE

#endif // __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
