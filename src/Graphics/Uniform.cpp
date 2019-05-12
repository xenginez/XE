#include "Uniform.h"

#include "GFX.h"

USING_XE

BEGIN_META(Uniform)
END_META()

XE::Uniform::Uniform()
{

}

XE::Uniform::Uniform( const String& name, UniformType type, uint16 num /*= 1 */ )
{
	_Handle = GFX::CreateUniform(name, type, num);
}

XE::Uniform::Uniform( UniformHandle handle )
{
	GFX::GetUniformInfo(_Handle, _Info);
	_Handle = GFX::CreateUniform(_Info.name, _Info.type, _Info.num);
}

XE::Uniform::~Uniform()
{
	if ( _Handle.idx != UINT16_MAX )
	{
		GFX::Destroy(_Handle);
	}
}

XE::UniformHandle XE::Uniform::GetHandle() const
{
	return _Handle;
}

const XE::UniformInfo& XE::Uniform::GetInfo() const
{
	return _Info;
}
