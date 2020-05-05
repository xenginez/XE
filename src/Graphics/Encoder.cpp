#include "Encoder.h"

#include "Structs.h"

struct XE::Encoder::Private
{
	bool _Discard;
	XE::Frame * _Frame;
	XE::RenderBind _Bind;
	XE::RenderDraw _Draw;
	XE::RenderCompute _Compute;
};

void XE::Encoder::SetFrame( Frame * val )
{
	_p->_Frame = val;
}
