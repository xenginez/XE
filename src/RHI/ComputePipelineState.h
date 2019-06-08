/*!
 * \file   ComputePipelineState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COMPUTEPIPELINESTATE_H__9F6F1EDD_0852_4AC0_BFED_7403AB042FA3
#define __COMPUTEPIPELINESTATE_H__9F6F1EDD_0852_4AC0_BFED_7403AB042FA3

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API ComputePipelineState : public std::enable_shared_from_this<ComputePipelineState>
{
	OBJECT(ComputePipelineState)

public:
	ComputePipelineState();

	~ComputePipelineState();

public:
	ComputeShaderPtr GetComputeShader() const;

	void SetComputeShader(ComputeShaderPtr val);

private:
	ComputeShaderPtr _CS;
};

END_XE_NAMESPACE

#endif // __COMPUTEPIPELINESTATE_H__9F6F1EDD_0852_4AC0_BFED_7403AB042FA3
