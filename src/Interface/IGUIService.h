/*!
 * \file	IGUIService.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IGUISERVICE_H__68002849_A17F_4FAA_930A_CAE3068E8678
#define IGUISERVICE_H__68002849_A17F_4FAA_930A_CAE3068E8678

#include "IService.h"
#include "IUserInterface.h"

BEG_XE_NAMESPACE

DECL_PTR( UserInterface );

class XE_API IGUIService : public XE::IService
{
	OBJECT( IGUIService, IService )

public:
	IGUIService();

	~IGUIService();

public:
	virtual void Insert( const XE::String & name, const XE::IUserInterfacePtr & ui ) = 0;

	virtual const XE::IUserInterfacePtr Find( const XE::String & val ) = 0;

	virtual void Remove( const XE::String & val ) = 0;

};

END_XE_NAMESPACE

#endif // IGUISERVICE_H__68002849_A17F_4FAA_930A_CAE3068E8678
