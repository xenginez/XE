#include "ScriptRoot.h"

XE::ScriptObjectRoot::ScriptObjectRoot( XE::ScriptObject * val )
	:_Object( val )
{

}

void XE::ScriptObjectRoot::Visit( const VisitCallbackType & val )
{
	val( _Object );
}
