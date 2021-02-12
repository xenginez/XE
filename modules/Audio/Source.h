/*!
 * \file   Source.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef SOURCE_H__8934EC6F_3D1F_48A3_A867_9ADF05FDC5B0
#define SOURCE_H__8934EC6F_3D1F_48A3_A867_9ADF05FDC5B0

#include "Clip.h"

BEG_AUDIO_NAMESPACE

class AUDIO_API Source : public XE::Object
{
	OBJECT( Source, Object )

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

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	bool GetPlayOnStart() const;

	void SetPlayOnStart( bool val );

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

	const XE::AudioClipPtr & GetAudioClip() const;

	void SetAudioClip( const XE::AudioClipPtr & val );

private:
	bool _Loop = false;
	bool _PlayOnStart = false;
	XE::float32 _Gain = 0.0f;
	XE::float32 _Pitch = 1.0f;
	XE::Vec3f _Position = {};
	XE::Vec3f _Velocity = {};
	XE::Vec3f _Direction = {};
	XE::float32 _MinDistance = 1.0f;
	XE::float32 _MaxDistance = 1000.0f;
	XE::AudioClipPtr _AudioClip = nullptr;
};

END_AUDIO_NAMESPACE

#endif // SOURCE_H__8934EC6F_3D1F_48A3_A867_9ADF05FDC5B0
