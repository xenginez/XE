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

	~LocalizationService() override;

public:
	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	Language GetCurrentLanguage() const override;

	void SetCurrentLanguage( Language val ) override;

public:
	String LocalizedString( const String& val ) const override;

private:
	void UpdateLocalized();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __LOCALIZATIONSERVICE_H__547E0953_14F0_436F_A09E_141D3E4DAA47
