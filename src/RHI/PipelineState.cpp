#include "PipelineState.h"

USING_XE

BEG_META(ComputePipelineState)
END_META()

XE::ComputePipelineState::ComputePipelineState()
{

}

XE::ComputePipelineState::~ComputePipelineState()
{

}

XE::ComputeShaderPtr XE::ComputePipelineState::GetComputeShader() const
{
	return _CS;
}

void XE::ComputePipelineState::SetComputeShader(ComputeShaderPtr val)
{
	_CS = val;
}
