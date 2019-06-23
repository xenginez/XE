/*!
 * \file   AudioSourceComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/09
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972
#define __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972

#include "Type.h"

BEG_XE_NAMESPACE

DECL_PTR(AudioSound);

class BEHAVIOR_API AudioSourceComponent : public SceneComponent
{
	OBJECT( AudioSourceComponent, SceneComponent )

public:
	AudioSourceComponent();

	~AudioSourceComponent();

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	XE::real GetVolume() const;

	void SetVolume( XE::real val );

	XE::real GetPitch() const;

	void SetPitch( XE::real val );

	const String& GetSound() const;

	void SetSound( const String& val );

public:
	void Play();

	void Stop();

	void Pause();

	bool IsPlay() const;

	bool IsStop() const;

	bool IsPause() const;

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

	virtual void OnClearup() override;

private:
	bool _Play = true;
	bool _Pause = false;
	bool _Loop = true;
	XE::real _Volume = 1.0f;
	XE::real _Pitch = 1.0f;

	String _SoundPath;
	XE::uint32 _SourceHandle = 0;
	AudioSoundPtr _Sound;
	XE::real _SoundPlayDt = 0;
};

END_XE_NAMESPACE

#endif // __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972
