/*!
 * \file	AudioUtil.h
 *
 * \author	ZhengYuanQing
 * \date	2019/06/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AUDIOUTIL_H__461A9296_E4F1_47F4_99C3_BF6945B53888
#define AUDIOUTIL_H__461A9296_E4F1_47F4_99C3_BF6945B53888

#include "Type.h"

BEG_XE_NAMESPACE

class AUDIO_API AudioUtil
{
public:
	static void CheckError(const String& file, XE::uint64 line, const String& expr);
};

END_XE_NAMESPACE

#endif // AUDIOUTIL_H__461A9296_E4F1_47F4_99C3_BF6945B53888
