/*!
 * \file   Clip.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef CLIP_H__D56A55CE_C49C_464A_A3F7_920219F5F4C8
#define CLIP_H__D56A55CE_C49C_464A_A3F7_920219F5F4C8

#include "Type.h"

BEG_AUDIO_NAMESPACE

class AUDIO_API Clip : public XE::Object
{
	OBJECT( Clip, Object )

public:
	Clip();

	~Clip();

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

END_AUDIO_NAMESPACE

#endif // CLIP_H__D56A55CE_C49C_464A_A3F7_920219F5F4C8
