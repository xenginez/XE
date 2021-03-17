/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
#define __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A

#include "Math/Math.h"
#include "Utils/Utils.h"

BEG_XE_NAMESPACE

enum class Format
{
	PCM,
	MP3,
	OGG,
};
DECL_META_ENUM( XE_API, Format );

END_XE_NAMESPACE

#endif // __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
