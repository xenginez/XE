#include "BlendState.h"

USING_XE

BEG_META(BlendState)
END_META()

XE::BlendState::BlendState()
{

}

XE::BlendState::~BlendState()
{

}

XE::BlendStateHandle XE::BlendState::GetHandle() const
{
	return _Handle;
}
