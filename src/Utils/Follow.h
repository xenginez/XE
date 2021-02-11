/*!
 * \file   Follow.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/11
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef FOLLOW_H__770E7900_32CB_49A3_B8BC_4D4CC99B89C1
#define FOLLOW_H__770E7900_32CB_49A3_B8BC_4D4CC99B89C1

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Follow
{
public:
    using CallbackType = std::function<void()>;

    struct PairType 
	{
		CallbackType Callback;
        std::atomic< XE::uint64 > Count;
    };

public:
    Follow();

    Follow( const Follow & val );

    Follow( const CallbackType & val );

    ~Follow();

public:
    Follow & operator= ( const Follow & val );

public:
    void Cancel();

private:
    std::atomic< PairType * > _Pair;
};

END_XE_NAMESPACE

#endif // FOLLOW_H__770E7900_32CB_49A3_B8BC_4D4CC99B89C1
