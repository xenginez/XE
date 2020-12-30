/*!
 * \file	IUserInterface.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IUSERINTERFACE_H__C2C6E88E_182A_4349_BD15_30E91A258533
#define IUSERINTERFACE_H__C2C6E88E_182A_4349_BD15_30E91A258533

#include "Object.h"

BEG_XE_NAMESPACE

class XE_API IUserInterface : public XE::Object
{
	OBJECT( IUserInterface, Object )

public:
	IUserInterface();

	~IUserInterface();

};

END_XE_NAMESPACE

#endif // IUSERINTERFACE_H__C2C6E88E_182A_4349_BD15_30E91A258533
