/*!
 * \file   Resource.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8
#define __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Resource : public XE::Object
{
	OBJECT( Resource, Object )

public:
	Resource();

	~Resource() override;

public:
	virtual void Startup( RenderContextRPtr context ) = 0;

	virtual void Clearup( RenderContextRPtr context ) = 0;

public:
	ResourceHandle GetHandle() const;

protected:
	void SetHandle( ResourceHandle handle );

private:
	ResourceHandle _Handle;
};

END_XE_NAMESPACE

#endif // __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8
