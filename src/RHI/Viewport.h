/*!
 * \file   Viewport.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA
#define __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Viewport : public Resource
{
	OBJECT( Viewport, Resource )

public:
	Viewport();

	~Viewport() override;

public:
	XE::real GetX() const;

	void SetX( XE::real val );

	XE::real GetY() const;

	void SetY( XE::real val );

	XE::real GetWidth() const;

	void SetWidth( XE::real val );

	XE::real GetHeight() const;

	void SetHeight( XE::real val );

	const Rect & GetRect() const;

	void SetRect( const Rect & rect );

private:
	Rect _Rect;
};

END_XE_NAMESPACE

#endif // __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA
