#include "RendererContext.h"

#include "Structs.h"

struct XE::RenderContext::Private
{

};

XE::RenderContext::RenderContext()
	:_p( new Private )
{

}

XE::RenderContext::~RenderContext()
{
	delete _p;
}
