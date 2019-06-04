/*!
 * \file   MeshComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/17
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MESHCOMPONENT_H__372F9591_A896_4B73_949B_0B951ED0C85A
#define __MESHCOMPONENT_H__372F9591_A896_4B73_949B_0B951ED0C85A

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API MeshComponent : public XE::RenderComponent
{
	OBJECT( MeshComponent, RenderComponent )

public:
	MeshComponent();

	~MeshComponent();

};

END_XE_NAMESPACE

#endif // __MESHCOMPONENT_H__372F9591_A896_4B73_949B_0B951ED0C85A
