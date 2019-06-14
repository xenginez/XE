/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
#define __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( AudioSound );

END_XE_NAMESPACE

#define AL_CHECK(EXPR) EXPR; AudioUtil::CheckError(__FILE__, __LINE__, #EXPR)

#endif // __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
