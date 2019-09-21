/*!
 * \file   NonCopyable.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __NONCOPYABLE_HPP__51063BED_9A8D_4E17_8341_3300C518CD58
#define __NONCOPYABLE_HPP__51063BED_9A8D_4E17_8341_3300C518CD58

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NonCopyable
{
public:
	NonCopyable() = default;
	~NonCopyable() = default;

private:
	NonCopyable( const NonCopyable& ) = delete;
	NonCopyable& operator =( const NonCopyable& ) = delete;
};

END_XE_NAMESPACE

#endif // __NONCOPYABLE_HPP__51063BED_9A8D_4E17_8341_3300C518CD58
