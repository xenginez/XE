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

class XE_API LocalizationService : public ILocalizationService
{
	OBJECT( LocalizationService, ILocalizationService )

private:
	struct Private;

public:
	LocalizationService();

	~LocalizationService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	Language GetCurrentLanguage() const override;

	void SetCurrentLanguage( Language val ) override;

public:
	const String & LocalizedString( const String & key, const String& defualt = "" ) const override;

private:
	void LoadLocalized();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __LOCALIZATIONSERVICE_H__547E0953_14F0_436F_A09E_141D3E4DAA47
