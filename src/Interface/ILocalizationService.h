/*!
 * \file   ILocalizationService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ILOCALIZATIONSERVICE_H__518B05CA_E9A3_47B1_8AA8_5417C4BA813F
#define __ILOCALIZATIONSERVICE_H__518B05CA_E9A3_47B1_8AA8_5417C4BA813F

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API ILocalizationService : public IService
{
	OBJECT( ILocalizationService, IService )

public:
	ILocalizationService();

	virtual ~ILocalizationService();

public:
	virtual Language GetCurrentLanguage() const = 0;

	virtual void SetCurrentLanguage( Language val ) = 0;

public:
	virtual String LocalizedString( const String& val ) const = 0;
};

END_XE_NAMESAPCE

#endif // __ILOCALIZATIONSERVICE_H__518B05CA_E9A3_47B1_8AA8_5417C4BA813F
