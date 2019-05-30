/*!
 * \file   Profiler.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PROFILER_H__9E55EED9_BD27_44A2_849C_1E9BD331A20C
#define __PROFILER_H__9E55EED9_BD27_44A2_849C_1E9BD331A20C

#include "Type.h"

BEG_XE_NAMESPACE


class UTILS_API ProfilerItem
{
public:
	std::chrono::system_clock::time_point StartTime;
	std::chrono::system_clock::time_point StopTime;
	Array<ProfilerItem> Children;
	String Function;
	XE::uint64 Line;
	String File;
};

class UTILS_API ProfilerFrame : public std::enable_shared_from_this<ProfilerFrame>
{
public:
	std::thread::id TID;
	Array<ProfilerItem> Children;
};

class UTILS_API ProfilerTrack
{
public:
	ProfilerTrack( const String& file, XE::uint64 line, const String& function );

	ProfilerTrack( ProfilerTrack &&val );

	ProfilerTrack& operator=( ProfilerTrack &&val );

	~ProfilerTrack();

private:
	ProfilerItem * _Item;
};


class UTILS_API Profiler : public XE::Singleton< Profiler >
{
private:
	struct Private;

public:
	friend class ProfilerTrack;

public:
	using ListenerType = std::function<void( ProfilerFramePtr )>;

public:
	Profiler();

	~Profiler();

public:
	static void Beg();

	static void End();

public:
	static XE::uint64 RegisterListener(ListenerType val, std::thread::id tid = std::this_thread::get_id());

	static void UnregisterListener(XE::uint64 val);

private:
	static ProfilerItem * Begin( const String& file, XE::uint64 line, const String& function );

	static void End( ProfilerItem * val );

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __PROFILER_H__9E55EED9_BD27_44A2_849C_1E9BD331A20C
