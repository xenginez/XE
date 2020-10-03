/*!
 * \file   AudioService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/13
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AUDIOSERVICE_H__C1E7D394_61A9_4E9B_878E_0FAAF5C8AAD9
#define __AUDIOSERVICE_H__C1E7D394_61A9_4E9B_878E_0FAAF5C8AAD9

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AudioService : public IAudioService
{
	OBJECT( AudioService, IAudioService )

public:
	AudioService();

	~AudioService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void Resume() override;

	void Suspend() override;

};

END_XE_NAMESPACE

#endif // __AUDIOSERVICE_H__C1E7D394_61A9_4E9B_878E_0FAAF5C8AAD9
