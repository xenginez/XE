/*!
 * \file   Mixer.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef MIXER_H__CB4561E0_62A1_4154_B128_2138CF778838
#define MIXER_H__CB4561E0_62A1_4154_B128_2138CF778838

#include "Source.h"

BEG_AUDIO_NAMESPACE

class AUDIO_API Mixer : public XE::Object
{
	OBJECT( Mixer, Object )

public:
	Mixer();

	~Mixer();

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

END_AUDIO_NAMESPACE

#endif // MIXER_H__CB4561E0_62A1_4154_B128_2138CF778838
