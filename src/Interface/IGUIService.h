/*!
 * \file   IGUIService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IGUISERVICE_H__4179635E_3DD6_44F3_A701_02D1D99EDB79
#define __IGUISERVICE_H__4179635E_3DD6_44F3_A701_02D1D99EDB79

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API IGUIService : public IService
{
	OBJECT( IGUIService, IService )

public:
	IGUIService();

	~IGUIService() override;

};

END_XE_NAMESPACE

#endif // __IGUISERVICE_H__4179635E_3DD6_44F3_A701_02D1D99EDB79
