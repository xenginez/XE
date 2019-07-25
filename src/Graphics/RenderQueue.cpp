#include "RenderQueue.h"

USING_XE

XE::RenderQueue::RenderQueue( const CommandListPtr & val )
	:_CommandList( val )
{

}

XE::RenderQueue::~RenderQueue()
{

}

void XE::RenderQueue::Flush()
{
	XE::uint8 * p = _DrawCalls.data();

	SortKeyPair pair;

	while( !_Background.empty() )
	{
		pair = _Background.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( _CommandList );
		_Background.pop();
	}

	while( !_Geometry.empty() )
	{
		pair = _Geometry.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( _CommandList );
		_Geometry.pop();
	}

	while( !_AlphaTest.empty() )
	{
		pair = _AlphaTest.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( _CommandList );
		_AlphaTest.pop();
	}

	while( !_Transparent.empty() )
	{
		pair = _Transparent.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( _CommandList );
		_Transparent.pop();
	}

	while( !_Overlay.empty() )
	{
		pair = _Overlay.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( _CommandList );
		_Overlay.pop();
	}

	_DrawCalls.clear();
}

const XE::CommandListPtr & XE::RenderQueue::GetCommandList() const
{
	return _CommandList;
}
