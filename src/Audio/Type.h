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
DECL_PTR( AudioSourceComponent );
DECL_PTR( AudioListenerComponent );


void openal_check_error( const String& file, XE::uint64 line, const String& expr );

END_XE_NAMESAPCE

#define AL_CHECK(EXPR) EXPR; openal_check_error(__FILE__, __LINE__, #EXPR)

#endif // __TYPE_H__EB1374C2_88D3_4E49_9C23_BF526801C55A
