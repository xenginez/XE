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

	virtual ~IConfigService();

public:
	bool GetBool( const std::string& key ) const;

	void SetBool( const std::string& key, bool val );

	int8 GetInt8( const std::string& key ) const;

	void SetInt8( const std::string& key, int8 val );

	int16 GetInt16( const std::string& key ) const;

	void SetInt16( const std::string& key, int16 val );

	int32 GetInt32( const std::string& key ) const;

	void SetInt32( const std::string& key, int32 val );

	int64 GetInt64( const std::string& key ) const;

	void SetInt64( const std::string& key, int64 val );

	uint8  GetUInt8( const std::string& key ) const;

	void  SetUInt8( const std::string& key, uint8 val );

	uint16 GetUInt16( const std::string& key ) const;

	void SetUInt16( const std::string& key, uint16 val );

	uint32 GetUInt32( const std::string& key ) const;

	void SetUInt32( const std::string& key, uint32 val );

	uint64 GetUInt64( const std::string& key ) const;

	void SetUInt64( const std::string& key, uint64 val );

	float GetFloat( const std::string& key ) const;

	void SetFloat( const std::string& key, float val );

	double GetDouble( const std::string& key ) const;

	void SetDouble( const std::string& key, double val );

	std::string GetString( const std::string& key ) const;

	void SetString( const std::string& key, const std::string& val ) const;

protected:
	virtual std::string GetValue( const std::string& key ) const = 0;

	virtual void SetValue( const std::string& key, const std::string& val ) const = 0;

};

END_XE_NAMESAPCE

#endif // __ICONFIGSERVICE_H__DC28E0D8_069A_4E9A_84DB_12E887976B63
