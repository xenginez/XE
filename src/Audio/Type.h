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

#include "Reflect/Reflect.h"

BEG_XE_NAMESPACE

DECL_PTR( AudioClip );
DECL_PTR( AudioSource );
DECL_PTR( AudioMixer );

enum class AudioFormat
{
	PCM,
	MP3,
	OGG,
};
DECL_META_ENUM( XE_API, AudioFormat );

END_XE_NAMESPACE

#endif // __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
