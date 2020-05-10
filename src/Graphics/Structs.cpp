#include "Structs.h"

void XE::Frame::Reset()
{
	RenderBindSize = 0;
	RenderItemSize = 0;
	RenderBlitSize = 0;
	RenderOcclusionSize = 0;

	PrevCmd.Reset();
	PostCmd.Reset();
	TransientBuffer.Reset();
}
