/*!
 * \file	RenderQueue.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
#define RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD

#include "DrawCall.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderQueue
{
public:
	union SortKey
	{
		XE::uint64 key;
		struct 
		{
			XE::uint32 m_depth;
			XE::uint32 m_seq;
			XE::uint32 m_shader;
			XE::uint32 m_trans;
		};
	};

public:
	RenderQueue();

	~RenderQueue();

public:
	static XE::uint64 GenKey();

public:
	template<typename _DC> _DC * CreateDrawCall( XE::uint64 key )
	{
		return new ( CreateDrawCall( key, sizeof( _DC ) ) ) _DC();
	}

private:
	XE::uint8 * CreateDrawCall( XE::uint64 key, XE::uint64 size );

};

END_XE_NAMESPACE

#endif // RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
