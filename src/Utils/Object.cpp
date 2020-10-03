#include "Object.h"

#include <Interface/IFramework.h>
#include <Interface/ILocalizationService.h>



BEG_META( XE::Object )
END_META()

XE::Object::Object()
{

}

XE::Object::~Object()
{

}

void XE::Object::AssetLoad()
{

}

void XE::Object::AssetUnload()
{

}

const XE::String & XE::Object::tr( const String & val ) const
{
	return XE::IFramework::GetCurrentFramework()->GetLocalizationService()->LocalizedString( GetMetaClass()->GetFullName() + "." + val, val );
}

void XE::Object::ProcessEvent( EventPtr & val )
{

}
