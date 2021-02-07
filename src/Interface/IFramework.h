/*!
 * \file   IFramework.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57
#define __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57

#include "Utils/Platform.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API IFramework : public XE::NonCopyable
{
	OBJECT( IFramework )

public:
	IFramework();

	virtual ~IFramework();

public:
	static IFrameworkPtr GetCurrentFramework();

public:
	template< typename T > XE::SharedPtr< T > GetServiceT() const
	{
		return SP_CAST< T >( GetService( ::XE_ClassID< typename T >::Get() ) );
	}

public:
	virtual ITimerServicePtr GetTimerService() const = 0;

	virtual IEventServicePtr GetEventService() const = 0;

	virtual IInputServicePtr GetInputService() const = 0;

	virtual IAudioServicePtr GetAudioService() const = 0;

	virtual IWorldServicePtr GetWorldService() const = 0;

	virtual IThreadServicePtr GetThreadService() const = 0;

	virtual IAssetsServicePtr GetAssetsService() const = 0;

	virtual IRenderServicePtr GetRenderService() const = 0;

	virtual IPhysicsServicePtr GetPhysicsService() const = 0;

	virtual INavigationServicePtr GetINavigationService() const = 0;

	virtual ILocalizationServicePtr GetLocalizationService() const = 0;

public:
	virtual IServicePtr GetService( const IMetaClassPtr & val ) const = 0;

	virtual bool RegisterService( const IMetaClassPtr & val ) = 0;

	virtual void UnregisterService( const IMetaClassPtr & val ) = 0;

public:
	virtual void Exit() = 0;

	virtual void WaitExit() = 0;

	virtual bool IsExit() const = 0;

	virtual Language GetSystemLanguage() const = 0;

	virtual std::filesystem::path GetModulePath() const = 0;

	virtual std::filesystem::path GetAssetsPath() const = 0;

	virtual std::filesystem::path GetUserDataPath() const = 0;

	virtual std::filesystem::path GetApplicationPath() const = 0;

public:
	virtual void Save() = 0;

	virtual void Reload() = 0;

public:
	void SetBool( const String & key, bool val );

	bool GetBool( const String & key, bool def = false );

	void SetInt8( const String & key, XE::int8 val );

	XE::int8 GetInt8( const String & key, XE::int8 def = 0 );

	void SetInt16( const String & key, XE::int16 val );

	XE::int16 GetInt16( const String & key, XE::int16 def = 0 );

	void SetInt32( const String & key, XE::int32 val );

	XE::int32 GetInt32( const String & key, XE::int32 def = 0 );

	void SetInt64( const String & key, XE::int64 val );

	XE::int64 GetInt64( const String & key, XE::int64 def = 0 );

	void  SetUInt8( const String & key, XE::uint8 val );

	XE::uint8  GetUInt8( const String & key, XE::uint8 def = 0 );

	void SetUInt16( const String & key, XE::uint16 val );

	XE::uint16 GetUInt16( const String & key, XE::uint16 def = 0 );

	void SetUInt32( const String & key, XE::uint32 val );

	XE::uint32 GetUInt32( const String & key, XE::uint32 def = 0 );

	void SetUInt64( const String & key, XE::uint64 val );

	XE::uint64 GetUInt64( const String & key, XE::uint64 def = 0 );

	void SetFloat32( const String & key, XE::float32 val );

	XE::float32 GetFloat32( const String & key, XE::float32 def = 0.0f );

	void SetFloat64( const String & key, XE::float64 val );

	XE::float64 GetFloat64( const String & key, XE::float64 def = 0.0 );

	void SetString( const String & key, const String & val );

	String GetString( const String & key, const String & def = "" );

protected:
	virtual String GetValue( const String & key ) = 0;

	virtual void SetValue( const String & key, const String & val ) = 0;

private:
	static IFrameworkPtr _CurrentFramework;
};

END_XE_NAMESPACE

#endif // __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57
