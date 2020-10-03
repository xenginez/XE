#include "AudioSound.h"



BEG_META( XE::AudioSound )
END_META()

XE::AudioSound::AudioSound()
{

}

XE::AudioSound::~AudioSound()
{

}

void XE::AudioSound::AssetLoad()
{

}

XE::uint32 XE::AudioSound::GetBits() const
{
	return 0;
}

XE::uint32 XE::AudioSound::GetChannel() const
{
	return 0;
}

XE::uint32 XE::AudioSound::GetSampleRate() const
{
	return 0;
}

XE::uint32 XE::AudioSound::GetFrameCount() const
{
	return 0;
}

const XE::String & XE::AudioSound::GetSoundPath() const
{
	return _Path;
}

void XE::AudioSound::Seek( XE::uint32 val )
{

}

XE::Array<XE::uint8> XE::AudioSound::GetOneFrame()
{
	XE::Array<XE::uint8> buf( XE::MemoryResource::GetStackMemoryResource() );


	return std::move( buf );
}
