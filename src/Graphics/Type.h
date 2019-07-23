/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
#define __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848

#include "Global.h"

BEG_XE_NAMESPACE

class DrawCall;
class RenderQueue;


DECL_PTR( Mesh );
DECL_PTR( Camera );
DECL_PTR( Material );
DECL_PTR( Renderer );
DECL_PTR( RenderPass );
DECL_PTR( Renderable );


enum RenderGroup
{
	BACKGROUND = 1000,
	GEOMETRY = 2000,
	ALPHATEST = 2450,
	TRANSPARENT = 3000,
	OVERLAY = 4000,
};
DECL_META_ENUM( RHI_API, RenderGroup );


END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
