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

BEG_XE_NAMESPACE

class XE_API AudioSoundSource : public XE::Object
{
    OBJECT( AudioSoundSource, Object )

public:
	virtual void Startup() = 0;

	virtual void Update( XE::float32 dt ) = 0;

	virtual void Clearup() = 0;

public:
	virtual void Play() = 0;

	virtual void Stop() = 0;

	virtual void Resume() = 0;

	virtual void Suspend() = 0;

public:
	bool GetLoop() const;

    void SetLoop( bool val );

	XE::float32  GetGain() const;

	void SetGain( XE::float32 val );

	XE::float32  GetPitch() const;

	void SetPitch( XE::float32 val );

	const XE::Vec3f & GetPosition() const;

	void SetPosition( const XE::Vec3f & val );

	const XE::Vec3f & GetVelocity() const;

	void SetVelocity( const XE::Vec3f & val );

	const XE::Vec3f & GetDirection() const;

	void SetDirection( const XE::Vec3f & val );

	XE::float32 GetMinDistacne() const;

	void SetMinDistance( XE::float32 val );

    XE::float32 GetMaxDistance() const;

    void SetMaxDistance( XE::float32 val );

private:
    bool _Loop = false;
    XE::float32 _Gain = 0.0f;
    XE::float32 _Pitch = 1.0f;
	XE::Vec3f _Position = {};
	XE::Vec3f _Velocity = {};
	XE::Vec3f _Direction = {};
	XE::float32 _MinDistance = 1.0f;
	XE::float32 _MaxDistance = 1000.0f;
	XE::FileSystem::Path _Sound;
};

END_XE_NAMESPACE

#endif // AUDIOSOUNDSOURCE_H__1D751335_F408_4FA5_9AB3_4EFEE45DF522
