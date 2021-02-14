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

#include "Global.h"

BEG_AUDIO_NAMESPACE

DECL_PTR( Clip );
DECL_PTR( Mixer );
DECL_PTR( Source );

enum class Format
{
	PCM,
	MP3,
	OGG,
};
DECL_META_ENUM( AUDIO_API, Format );

DECL_META_MODULE( AUDIO_API );

END_AUDIO_NAMESPACE

#endif // __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
