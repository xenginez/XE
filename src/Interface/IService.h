/*!
 * \file   IService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ISERVICE_H__963670C3_A42A_4D62_844E_62A87B29D0D6
#define __ISERVICE_H__963670C3_A42A_4D62_844E_62A87B29D0D6

#include "Object.h"

BEG_XE_NAMESPACE

class INTERFACE_API IService : public Object
{
	OBJECT( IService, Object )

public:
	IService();

	~IService() override;

public:
	IFrameworkPtr GetFramework() const;

	void SetFramework( IFrameworkPtr val );

public:
	virtual bool Startup() = 0;

	virtual void Update() = 0;

	virtual void Clearup() = 0;

public:
	ObjectPtr Clone() const override;

private:
	IFrameworkPtr _Framework;
};

END_XE_NAMESAPCE

#endif // __ISERVICE_H__963670C3_A42A_4D62_844E_62A87B29D0D6
