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
	XE::uint8 * beg = _DrawCalls.data();

	DrawCallPair pair;

	while( !_Queue.empty() )
	{
		pair = _Queue.top();

		DrawCall * draw = ( (DrawCall * )( beg + pair.second ) );

		draw->Execute( val );

		draw->~DrawCall();

		_Queue.pop();
	}

	_DrawCalls.clear();
}
