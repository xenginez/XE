/*!
 * \file	AudioMixer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/31
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AUDIOMIXER_H__A160FF5D_1E77_4412_B0F6_5A271CBF7A1D
#define AUDIOMIXER_H__A160FF5D_1E77_4412_B0F6_5A271CBF7A1D

#include "AudioSource.h"

BEG_XE_NAMESPACE

class XE_API AudioMixer : public XE::Object
{
	OBJECT( AudioMixer, Object )

public:
	AudioMixer();

	~AudioMixer();

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

public:
	virtual void Play() = 0;

	virtual void Mute() = 0;

	virtual void Stop() = 0;

	virtual void Resume() = 0;

	virtual void Suspend() = 0;

};

END_XE_NAMESPACE

#endif // AUDIOMIXER_H__A160FF5D_1E77_4412_B0F6_5A271CBF7A1D
