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

#include "Type.h"

BEG_XE_NAMESPACE

struct GRAPHICS_API DrawCall : public XE::NonCopyable
{
public:
	SortKey GetSortKey() const;

public:
	virtual void Execute( CommandListPtr & val );

};

struct GRAPHICS_API RenderDrawCall : public DrawCall
{
public:
	IndexBufferPtr _IndexBuffer;
	VertexBufferPtr _VertexBuffer;
	GraphicsPipelineStatePtr _PipelineState;
};

struct GRAPHICS_API ComputeDrawCall : public DrawCall
{
public:
	ComputeBufferPtr _ComputeBuffer;
	ComputePipelineStatePtr _PipelineState;
};

template< typename ... _DC >struct DrawCallPacket : public DrawCall
{
public:
	std::tuple<_DC...> _DrawCalls;

public:
	SortKey GetSortKey() const
	{
		return std::get<0>( _DrawCalls ).GetSortKey();
	}

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
