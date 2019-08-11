/*!
 * \file	DrawCall.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/23
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120
#define DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120

#include "SortKey.h"

BEG_XE_NAMESPACE

class GRAPHICS_API DrawCall : public XE::NonCopyable
{
public:
	virtual void Execute( CommandListPtr & val ) = 0;

public:
	SortKey _Key;
};

class GRAPHICS_API RenderDrawCall : public DrawCall
{
public:
	IndexBufferPtr _IndexBuffer;
	VertexBufferPtr _VertexBuffer;
	GraphicsPipelineStatePtr _PipelineState;
};

class GRAPHICS_API ComputeDrawCall : public DrawCall
{
public:
	ComputeBufferPtr _ComputeBuffer;
	ComputePipelineStatePtr _PipelineState;
};

template< typename ... _DC >class DrawCallPacket : public DrawCall
{
public:
	std::tuple<_DC...> _DrawCalls;

public:
	void Execute( CommandListPtr & val ) override
	{
		for_each_in_tuple( [val]( auto & draw_call )
						   {
							   draw_call.Execute( val );
						   } );
	}

private:
	template<class F, std::size_t...Is> void for_each_in_tuple( F func, std::index_sequence<Is...> )
	{
		using expander = int[];
		(void )expander
		{
			0, ( (void )func( std::get<Is>( _DrawCalls ) ), 0 )...
		};
	}

	template<class F> void for_each_in_tuple( F func )
	{
		for_each_in_tuple( func, std::make_index_sequence<sizeof...( _DC )>() );
	}

};

END_XE_NAMESPACE

#endif // DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120
