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

	while( !_Queue.empty() )
	{
		pair = _Queue.top();

		( (DrawCall * )( p + pair.second ) )->Execute( val );

		_Queue.pop();
	}

	_DrawCalls.clear();
}
