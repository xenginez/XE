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

public:
	virtual XE::uint64 GetWidth() const = 0;

	virtual void SetWidth( XE::uint64 val ) = 0;

	virtual XE::uint64 GetHeight() const = 0;

	virtual void SetHeight( XE::uint64 val ) = 0;

	virtual int32 GetPositionX() const = 0;

	virtual void SetPositionX( int32 val ) = 0;

	virtual int32 GetPositionY() const = 0;

	virtual void SetPositionY( int32 val ) = 0;

public:
	virtual void IsFullScreen() const = 0;

	virtual void SetFullScreen( bool val ) = 0;

public:
	virtual std::intptr_t GetWindowHandle() const = 0;

};

END_XE_NAMESPACE

#endif // __IGUISERVICE_H__4179635E_3DD6_44F3_A701_02D1D99EDB79
