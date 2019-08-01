#include "RenderQueue.h"

USING_XE

XE::RenderQueue::RenderQueue()
{

}

XE::RenderQueue::~RenderQueue()
{

}

void XE::RenderQueue::Flush( CommandListPtr & val )
{
	XE::uint8 * p = _DrawCalls.data();

	SortKeyPair pair;

	while( !_Background.empty() )
	{
		pair = _Background.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( val );
		_Background.pop();
	}

	while( !_Geometry.empty() )
	{
		pair = _Geometry.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( val );
		_Geometry.pop();
	}

	while( !_AlphaTest.empty() )
	{
		pair = _AlphaTest.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( val );
		_AlphaTest.pop();
	}

	while( !_Transparent.empty() )
	{
		pair = _Transparent.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( val );
		_Transparent.pop();
	}

	while( !_Overlay.empty() )
	{
		pair = _Overlay.top();
		DrawCall * call = (DrawCall * )( p + pair.draw );
		call->Execute( val );
		_Overlay.pop();
	}

	_DrawCalls.clear();
}
