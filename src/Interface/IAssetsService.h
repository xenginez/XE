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
    virtual XE::MemoryView Load( const std::filesystem::path & path ) = 0;

    virtual void AsyncLoad( const std::filesystem::path & path, const LoadFinishCallback & callback ) = 0;

public:
	virtual XE::ObjectPtr LoadObject( const std::filesystem::path & path ) = 0;

	virtual void AsyncLoadObject( const std::filesystem::path & path, const LoadObjectFinishCallback & callback ) = 0;

public:
	template< typename T > T LoadObjectT( const std::filesystem::path & path )
	{
		return DP_CAST<T::value_type>( LoadObject( path ) );
	}

};

END_XE_NAMESPACE

#endif // __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
