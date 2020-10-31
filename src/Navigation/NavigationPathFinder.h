/*!
 * \file	NavigationPathFinder.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef NAVIGATIONPATHFINDER_H__23ECBC68_505C_40D1_A5D4_FD1B4F308A9E
#define NAVIGATIONPATHFINDER_H__23ECBC68_505C_40D1_A5D4_FD1B4F308A9E

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NavigationPathFinder : public XE::Object
{
	OBJECT( NavigationPathFinder, Object )

public:
	NavigationPathFinder();

	~NavigationPathFinder() override;

public:

};

END_XE_NAMESPACE

#endif // NAVIGATIONPATHFINDER_H__23ECBC68_505C_40D1_A5D4_FD1B4F308A9E
