/*!
 * \file	KeyboardInputControl.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef KEYBOARDINPUTCONTROL_H__49E0C9F6_9C14_4752_92AB_24B03E798676
#define KEYBOARDINPUTCONTROL_H__49E0C9F6_9C14_4752_92AB_24B03E798676

#include "Type.h"

#include <tbb/concurrent_queue.h>

BEG_XE_NAMESPACE

class DLL_EXPORT KeyboardInputControl : public IInputControl
{
	OBJECT( KeyboardInputControl, IInputControl )

public:
	KeyboardInputControl();

	~KeyboardInputControl() override;

public:
	bool Startup() override;

	void Update() override;

	void Clearup() override;

private:
	XE::uint64 _UpStub, _DownStub;
	tbb::concurrent_queue<XE::EventPtr> _UpEvents, _DownEvents;
};

END_XE_NAMESPACE

#endif // KEYBOARDINPUTCONTROL_H__49E0C9F6_9C14_4752_92AB_24B03E798676
