/*!
 * \file   AudioSound.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AUDIOSOUND_H__792F6B33_B197_4F1A_8CEC_DF46C88D9DC4
#define __AUDIOSOUND_H__792F6B33_B197_4F1A_8CEC_DF46C88D9DC4

#include "Type.h"

BEG_XE_NAMESPACE

class AUDIO_API AudioSound : public Object
{
	OBJECT( AudioSound, Object )

public:
	AudioSound();

	~AudioSound();

public:
	const String& GetName() const;

	XE::real GetDuration() const;

	XE::uint32 GetChannels() const;

	XE::uint32 GetSampleRate() const;

	XE::uint8 GetBytesPerSample() const;

	XE::uint32 GetBufferHandle() const;

	const Array<XE::uint8>& GetBuffer() const;

private:
	XE::int32 GetFormat();

private:
	String _Name;
	XE::real _Duration;
	XE::uint32 _Channels;
	XE::uint32 _SampleRate;
	XE::uint8 _BytesPerSample;
	Array<XE::uint8> _Buffer;
	XE::uint32 _BuffHandle;
};

END_XE_NAMESPACE

#endif // __AUDIOSOUND_H__792F6B33_B197_4F1A_8CEC_DF46C88D9DC4
