/*!
 * \file	AudioSource.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/31
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AUDIOSOURCE_H__9AF6C834_D4EF_4967_B7BF_13DEC13A6B79
#define AUDIOSOURCE_H__9AF6C834_D4EF_4967_B7BF_13DEC13A6B79

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AudioClip : public XE::Object
{
	OBJECT( AudioClip, Object )

public:
	AudioClip();

	~AudioClip();

public:
	XE::uint16 GetBits() const;

	XE::uint16 GetChannels() const;

	XE::uint32 GetSampleRate() const;

	XE::AudioFormat GetAudioFormat() const;

private:
	XE::uint16 _Bits;
	XE::uint16 _Channels;
	XE::uint32 _SampleRate;
	XE::AudioFormat _Format;

	XE::Asset _SoundPath;
};

END_XE_NAMESPACE

#endif // AUDIOSOURCE_H__9AF6C834_D4EF_4967_B7BF_13DEC13A6B79
