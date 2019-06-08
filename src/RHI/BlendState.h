/*!
 * \file   BlendState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725
#define __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API BlendState : public std::enable_shared_from_this<BlendState>
{
	OBJECT(BlendState)

public:
	BlendState();
	
	~BlendState();

public:
	Vec4 GetBlendFactor() const;
	
	void SetBlendFactor( const Vec4 &val );
	
	bool GetEnableIndependentBlend() const;
	
	void SetEnableIndependentBlend( bool val );
	
	bool GetAlphaToCoverageEnabled() const;
	
	void SetAlphaToCoverageEnabled( bool val );
	
	uint64 GetRenderTargetCount() const;
	
	RenderTargetPtr GetRenderTarget( uint64 index ) const;
	
	void SetRenderTarget( uint64 index, const RenderTargetPtr &val );

private:
	Vec4 _BlendFactor;
	bool _EnableIndependentBlend;
	bool _AlphaToCoverageEnabled;
	Array < RenderTargetPtr > _RenderTargets;
};

END_XE_NAMESPACE

#endif // __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725
