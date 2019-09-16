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
DECL_PTR( Light );
DECL_PTR( Camera );
DECL_PTR( Renderer );
DECL_PTR( Skeleton );
DECL_PTR( Technique );
DECL_PTR( RenderPass );
DECL_PTR( Renderable );
DECL_PTR( RenderQueue );
DECL_PTR( RenderMaterial );


enum class CameraType
{
	PERSPECTIVE,
	ORTHOGRAPHIC,
};
DECL_META_ENUM( GRAPHICS_API, CameraType );

enum RenderLayer
{
	BACKGROUND,
	GEOMETRY,
	ALPHATEST,
	TRANSPARENT,
	OVERLAY,
};
DECL_META_ENUM( GRAPHICS_API, RenderLayer );

enum class Humanoid
{
	ROOT = 0,
	PELVIS,
	SPINE_01,
	SPINE_02,
	SPINE_03,
	CLAVICLE_L,
	UPPERARM_L,
	LOWERARM_L,
	HAND_L,
	CLAVICLE_R,
	UPPERARM_R,
	LOWERARM_R,
	HAND_R,
	NECK_01,
	HEAD,
	THIGH_L,
	CALF_L,
	FOOT_L,
	THIGH_R,
	CALF_R,
	FOOT_R,
};
DECL_META_ENUM( GRAPHICS_API, Humanoid );

END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
