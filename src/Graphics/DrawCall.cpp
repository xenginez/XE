#include "DrawCall.h"

#include "RenderQueue.h"

USING_XE

XE::SortKey XE::DrawCall::GetSortKey() const
{
	return 0;
}

void XE::DrawCall::operator()( CommandListPtr & val )
{
	XE_ASSERT( _Callback != nullptr && "" );

	_Callback( std::ref( val ) );
}

XE::RenderQueue * XE::DrawCall::GetRenderQueue() const
{
	return _Queue;
}
