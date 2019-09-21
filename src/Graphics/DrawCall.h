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

class XE_API DrawCall : public XE::NonCopyable
{
public:
	DrawCall();

	virtual ~DrawCall();

public:
	virtual void Execute( IRenderContextPtr & val ) = 0;

};

class XE_API RenderDrawCall : public DrawCall
{
public:
	RenderDrawCall();

	~RenderDrawCall() override;

public:
	void Execute( IRenderContextPtr & val ) override;

};

class XE_API IndirectDrawcall : public DrawCall
{
public:
	IndirectDrawcall();

	~IndirectDrawcall() override;

public:
	void Execute( IRenderContextPtr & val ) override;

};

class XE_API InstanceDrawcall : public DrawCall
{
public:
	InstanceDrawcall();

	~InstanceDrawcall() override;

public:
	void Execute( IRenderContextPtr & val ) override;

};

class XE_API IndexInstanceDrawcall : public InstanceDrawcall
{
public:
	IndexInstanceDrawcall();

	~IndexInstanceDrawcall() override;

public:
	void Execute( IRenderContextPtr & val ) override;

public:
	XE::uint64 BegIndex;
	XE::uint64 EndIndex;
};

class XE_API ComputeDrawCall : public DrawCall
{
public:
	ComputeDrawCall();

	~ComputeDrawCall() override;

public:
	void Execute( IRenderContextPtr & val ) override;

};

template< typename ... _DC > class PacketDrawCall : public DrawCall
{
public:
	PacketDrawCall()
	{ 
	}

	~PacketDrawCall() override
	{
	}

public:
	void Execute( IRenderContextPtr & val ) override
	{
		for_each_in_tuple( [val]( auto & draw_call )
						   {
							   draw_call.Execute( val );
						   } );
	}

public:
	std::tuple<_DC...> _DrawCalls;

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
