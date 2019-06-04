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

class INTERFACE_API IConfigService : public IService
{
	OBJECT( IConfigService, IService )

public:
	IConfigService();
	
	~IConfigService() override;

public:
	void SetBool( const String& key, bool val );
	
	bool GetBool( const String& key, bool def = false ) const;

	void SetInt8( const String& key, int8 val );
	
	int8 GetInt8( const String& key, int8 def = 0 ) const;

	void SetInt16( const String& key, int16 val );
	
	int16 GetInt16( const String& key, int16 def = 0 ) const;

	void SetInt32( const String& key, int32 val );
	
	int32 GetInt32( const String& key, int32 def = 0 ) const;

	void SetInt64( const String& key, int64 val );
	
	int64 GetInt64( const String& key, int64 def = 0 ) const;

	void  SetUInt8( const String& key, uint8 val );
	
	uint8  GetUInt8( const String& key, uint8 def = 0 ) const;

	void SetUInt16( const String& key, uint16 val );
	
	uint16 GetUInt16( const String& key, uint16 def = 0 ) const;

	void SetUInt32( const String& key, uint32 val );
	
	uint32 GetUInt32( const String& key, uint32 def = 0 ) const;

	void SetUInt64( const String& key, uint64 val );
	
	uint64 GetUInt64( const String& key, uint64 def = 0 ) const;

	void SetFloat32( const String& key, XE::float32 val );
	
	XE::float32 GetFloat32( const String& key, XE::float32 def = 0.0f ) const;

	void SetFloat64( const String& key, XE::float64 val );
	
	XE::float64 GetFloat64( const String& key, XE::float64 def = 0.0 ) const;

	void SetString( const String& key, const String& val ) const;
	
	String GetString( const String& key, const String& def = "" ) const;

protected:
	virtual String GetValue( const String& key ) const = 0;

	virtual void SetValue( const String& key, const String& val ) const = 0;

};

END_XE_NAMESPACE

#endif // __ICONFIGSERVICE_H__DC28E0D8_069A_4E9A_84DB_12E887976B63
