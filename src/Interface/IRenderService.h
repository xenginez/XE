/*!
 * \file   IRenderService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC
#define __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API IRenderService : public IService
{
	OBJECT( IRenderService, IService )

public:
	IRenderService();

	~IRenderService() override;

public:
};

END_XE_NAMESPACE

#endif // __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC
