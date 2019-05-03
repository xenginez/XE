/*!
 * \file   LocalizationService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LOCALIZATIONSERVICE_H__547E0953_14F0_436F_A09E_141D3E4DAA47
#define __LOCALIZATIONSERVICE_H__547E0953_14F0_436F_A09E_141D3E4DAA47

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API LocalizationService : public ILocalizationService
{
	OBJECT( LocalizationService, ILocalizationService )

private:
	struct Private;

public:
	LocalizationService();

	~LocalizationService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual Language GetCurrentLanguage() const override;

	virtual void SetCurrentLanguage( Language val ) override;

public:
	virtual String LocalizedString( const String& val ) const override;

private:
	void UpdateLocalized();

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __LOCALIZATIONSERVICE_H__547E0953_14F0_436F_A09E_141D3E4DAA47
