#include "RendererContext.h"

#include "Structs.h"

struct XE::RendererContext::Private
{

};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}
