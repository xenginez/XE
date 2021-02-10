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

const XE::String & XE::Object::Tr( const XE::String & val ) const
{
	return XE::IFramework::GetCurrentFramework()->GetServiceT< XE::ILocalizationService >()->LocalizedString( GetMetaClass()->GetFullName() + "." + val, val );
}

void XE::Object::ProcessEvent( const XE::EventPtr & val )
{

}
