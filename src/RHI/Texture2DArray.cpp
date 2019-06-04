#include "Texture2DArray.h"

USING_XE

BEG_META(Texture2DArray)
END_META()

XE::Texture2DArray::Texture2DArray()
{

}

XE::Texture2DArray::~Texture2DArray()
{

}

XE::uint32 XE::Texture2DArray::GetSize() const
{
	return _Size;
}
