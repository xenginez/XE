#include "Machine.h"



Machine::Machine()
{
	_Callbacks.resize( std::numeric_limits<XE::uint8>::max() );

//	_Callbacks[( XE::uint64 )InstructType::NOP] = &Machine::NOP;
}

void Machine::Exec( XE::basic_memory_view<XE::uint8> val )
{
	_Cursor = val.begin();

	while( _Cursor != val.end() )
	{
		( this->*_Callbacks[*( _Cursor++ )] )( );
	}

	_Cursor = XE::basic_memory_view<XE::uint8>::iterator();
}
