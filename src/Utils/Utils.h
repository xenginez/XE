/*!
 * \file	Utils.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3
#define UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3

#include "MD5.h"
#include "CRC32.h"
#include "Event.h"
#include "Layer.h"
#include "Order.h"
#include "Logger.h"
#include "BASE64.h"
#include "Buffer.h"
#include "Object.h"
#include "Zipper.h"
#include "Flags.hpp"
#include "Library.h"
#include "Platform.h"
#include "Handle.hpp"
#include "Signals.hpp"


#define XE_LOG(LEVEL, FMT, ...) \
XE::Logger::Instance()->Log( LEVEL, XE::StringUtils::Format(FMT, __VA_ARGS__) )

#define DECL_HANDLE( _DLL_EXPORT, NAME ) class NAME; using NAME##Handle = XE::Handle< NAME >; DECL_META_CLASS( _DLL_EXPORT, NAME##Handle );using NAME##HandleAllocator = XE::HandleAllocator< XE::Handle< NAME > >; DECL_META_CLASS( _DLL_EXPORT, NAME##HandleAllocator );

#define DECL_GROUP( _DLL_EXPORT, INDEX, NAME ) \
template<> class _DLL_EXPORT XE::OrderGroup< INDEX > \
{ \
public: \
    static constexpr XE::uint8 group_value = INDEX; \
}; \
namespace XE{ using NAME##Group = XE::OrderGroup< INDEX >; }

#define DECL_EVENT( NAME, DESC, PARAM ) \
DLL_VAR_WEAK extern const XE::Handle<XE::Event> NAME = XE::Order::RegisterOrder< XE::EventGroup >( #NAME, DESC, XE::TypeID< PARAM >::Get() )


DECL_GROUP( XE_API, 1, Event );

BEG_XE_NAMESPACE

template<> struct BufferReadable< std::string >
{
	static void Read( Buffer & buf, std::string & val )
	{
		std::string::size_type size = 0;

		buf.Read( size );

		val.resize( size );

		buf.Read( ( char * )val.data(), size );
	}
};

template<> struct BufferWirteable< std::string >
{
	static void Wirte( Buffer & buf, const std::string & val )
	{
		buf.Wirte( val.size() );

		buf.Wirte( val.c_str(), val.size() );
	}
};

END_XE_NAMESPACE

#endif // UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3
