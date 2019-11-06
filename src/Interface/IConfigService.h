/*!
 * \file   IConfigService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ICONFIGSERVICE_H__DC28E0D8_069A_4E9A_84DB_12E887976B63
#define __ICONFIGSERVICE_H__DC28E0D8_069A_4E9A_84DB_12E887976B63

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IConfigService : public IService
{
	OBJECT( IConfigService, IService )

public:
	IConfigService();

	~IConfigService() override;

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

};

END_XE_NAMESPACE

#endif // __ICONFIGSERVICE_H__DC28E0D8_069A_4E9A_84DB_12E887976B63
