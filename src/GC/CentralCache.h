#ifndef CENTRALCACHE_H__01ADCBB1_599A_4791_A1D6_CAE68957E793
#define CENTRALCACHE_H__01ADCBB1_599A_4791_A1D6_CAE68957E793

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API CentralCache
{
public:
	CentralCache( PageCache * page );

public:
	void * Allocate( std::size_t size );

	void Deallocate( void * ptr );

private:
	PageCache * _Page;
};

END_XE_NAMESPACE

#endif // CENTRALCACHE_H__01ADCBB1_599A_4791_A1D6_CAE68957E793
