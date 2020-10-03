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

class XE_API AudioSound : public XE::Object
{
	OBJECT( AudioSound, Object )

public:
	AudioSound();

	~AudioSound();

public:
	void AssetLoad() override;

public:
    XE::uint32 GetBits() const;

    XE::uint32 GetChannel() const;

	XE::uint32 GetSampleRate() const;

    XE::uint32 GetFrameCount() const;

    const XE::String & GetSoundPath() const;

public:
    void Seek( XE::uint32 val );

    XE::Array<XE::uint8> GetOneFrame();

private:
    XE::String _Path;
};

END_XE_NAMESPACE

#endif // __AUDIOSOUND_H__792F6B33_B197_4F1A_8CEC_DF46C88D9DC4
