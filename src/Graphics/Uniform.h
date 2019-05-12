/*!
 * \file   Uniform.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __UNIFORM_H__EF5B7D92_9204_42A9_994C_E2EDCD45228C
#define __UNIFORM_H__EF5B7D92_9204_42A9_994C_E2EDCD45228C

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Uniform : public XE::Object
{
	OBJECT(Uniform, Object)
	
public:
	Uniform();

	Uniform( const String& name, UniformType type, uint16 num = 1 );

	Uniform( UniformHandle handle );

	~Uniform();

public:
	UniformHandle GetHandle() const;

	const UniformInfo& GetInfo() const;

private:
	UniformHandle _Handle;

	UniformInfo _Info;
};

END_XE_NAMESAPCE

#endif // __UNIFORM_H__EF5B7D92_9204_42A9_994C_E2EDCD45228C
