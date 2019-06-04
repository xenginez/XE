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

	XE::float32 GetDuration() const;

	uint32 GetChannels() const;

	uint32 GetSampleRate() const;

	uint8 GetBytesPerSample() const;

	uint32 GetBufferHandle() const;

	const Array<uint8>& GetBuffer() const;

public:
	virtual void Load( Archive &val ) override;

	virtual void Save( Archive &val ) const override;

private:
	int32 GetFormat();

private:
	String _Name;
	XE::float32 _Duration;
	uint32 _Channels;
	uint32 _SampleRate;
	uint8 _BytesPerSample;
	Array<uint8> _Buffer;
	uint32 _BuffHandle;
};

END_XE_NAMESPACE

#endif // __AUDIOSOUND_H__792F6B33_B197_4F1A_8CEC_DF46C88D9DC4
