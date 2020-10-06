/*!
 * \file   AudioSoundSource.h
 *
 * \author ZhengYuanQing
 * \date   2020/10/02
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef AUDIOSOUNDSOURCE_H__1D751335_F408_4FA5_9AB3_4EFEE45DF522
#define AUDIOSOUNDSOURCE_H__1D751335_F408_4FA5_9AB3_4EFEE45DF522

#include "Math/Vec3.h"
#include "Utils/Object.h"

#include "Type.h"

struct ma_decoder;

BEG_XE_NAMESPACE

class XE_API AudioSoundSource : public XE::Object
{
    OBJECT( AudioSoundSource, Object )

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

public:
    void Play();

    void Stop();

    void Resume();

	void Suspend();

public:
	bool GetLoop() const;

    void SetLoop( bool val );

	XE::float32  GetGain() const;

	void SetGain( XE::float32 val );

	XE::float32  GetPitch() const;

	void SetPitch( XE::float32 val );

	const XE::Vec3 & GetPosition() const;

	void SetPosition( const XE::Vec3 & val );

	const XE::Vec3 & GetVelocity() const;

	void SetVelocity( const XE::Vec3 & val );

	const XE::Vec3 & GetDirection() const;

	void SetDirection( const XE::Vec3 & val );

	XE::float32 GetMinDistacne() const;

	void SetMinDistance( XE::float32 val );

    XE::float32 GetMaxDistance() const;

    void SetMaxDistance( XE::float32 val );

private:
	void SetAudioParam();

private:
    bool _Loop = false;
    XE::float32 _Gain = 0.0f;
    XE::float32 _Pitch = 1.0f;
	XE::Vec3 _Position = {};
	XE::Vec3 _Velocity = {};
	XE::Vec3 _Direction = {};
	XE::float32 _MinDistance = 1.0f;
	XE::float32 _MaxDistance = 1000.0f;
	XE::String _SoundPath;
	bool _Dirty = false;
private:
    XE::uint32 _SourceID = 0;
	XE::FileSystem::Path _Sound;
	ma_decoder * _Decoder = nullptr;
};

END_XE_NAMESPACE

#endif // AUDIOSOUNDSOURCE_H__1D751335_F408_4FA5_9AB3_4EFEE45DF522
