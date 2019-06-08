/*!
 * \file    Material.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MATERIAL_H__9907196C_05D4_4454_A53F_1BA7865664DC
#define __MATERIAL_H__9907196C_05D4_4454_A53F_1BA7865664DC

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Material : public Object
{
	OBJECT(Material, Object)
	
public:
	Material();
	
	~Material() override;

};

END_XE_NAMESPACE

#endif //__MATERIAL_H__9907196C_05D4_4454_A53F_1BA7865664DC
