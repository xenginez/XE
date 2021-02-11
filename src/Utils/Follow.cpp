#include "Follow.h"

XE::Follow::Follow()
	:_Pair( nullptr )
{

}

XE::Follow::Follow( const Follow & val )
	: _Pair( val._Pair.load() )
{
	++( _Pair.load()->Count );
}

XE::Follow::Follow( const CallbackType & val )
{
	auto pair = new PairType;

	pair->Callback = val;
	pair->Count = 1;

	_Pair = pair;
}

XE::Follow::~Follow()
{
	Cancel();
}

XE::Follow & XE::Follow::operator=( const Follow & val )
{
	if( _Pair != val._Pair )
	{
		if( _Pair )
		{
			Cancel();
		}

		_Pair = val._Pair.load();

		++( _Pair.load()->Count );
	}

	return *this;
}

void XE::Follow::Cancel()
{
	auto pair = _Pair.load();

	if( pair != nullptr )
	{
		--pair->Count;

		if( pair->Count == 0 )
		{
			if( pair->Callback )
			{
				pair->Callback();
			}

			delete pair;
		}
	}

	_Pair = nullptr;
}
