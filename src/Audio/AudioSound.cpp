#include "AudioSound.h"

#include <AL/al.h>

#include "AudioUtil.h"

USING_XE

BEG_META( AudioSound )
type->Property( "Name", &AudioSound::_Name );
type->Property( "Duration", &AudioSound::_Duration );
type->Property( "Channels", &AudioSound::_Channels );
type->Property( "SampleRate", &AudioSound::_SampleRate );
type->Property( "BytesPerSample", &AudioSound::_BytesPerSample );
type->Property( "Buffer", &AudioSound::_Buffer, IMetaProperty::NoDesign );
END_META()

XE::AudioSound::AudioSound()
	:_BytesPerSample( 0 ), _SampleRate( 0 ), _Channels( 0 ), _Duration( 0 ), _BuffHandle( 0 )
{

}

XE::AudioSound::~AudioSound()
{
	if (_BuffHandle != 0)
	{
		AL_CHECK( alDeleteBuffers( 1, &_BuffHandle ) );
	}
}

const XE::String& XE::AudioSound::GetName() const
{
	return _Name;
}

XE::float32 XE::AudioSound::GetDuration() const
{
	return _Duration;
}

XE::uint32 XE::AudioSound::GetChannels() const
{
	return _Channels;
}

XE::uint32 XE::AudioSound::GetSampleRate() const
{
	return _SampleRate;
}

XE::uint8 XE::AudioSound::GetBytesPerSample() const
{
	return _BytesPerSample;
}

XE::uint32 XE::AudioSound::GetBufferHandle() const
{
	return _BuffHandle;
}

const XE::Array<XE::uint8>& XE::AudioSound::GetBuffer() const
{
	return _Buffer;
}

XE::int32 XE::AudioSound::GetFormat()
{
	XE::int32 format = 0;

	switch ( _Channels )
	{
	case 1:
	{
		switch ( _BytesPerSample )
		{
		case 1:
			format = AL_FORMAT_MONO8;
			break;
		case 2:
			format = AL_FORMAT_MONO16;
			break;
		default:
			XE_LOG( LoggerLevel::Error, "unsupported bytes per sample count : %1", _BytesPerSample );
			break;
		}
	}
	break;
	case 2:
	{
		switch ( _BytesPerSample )
		{
		case 1:
			format = AL_FORMAT_STEREO8;
			break;
		case 2:
			format = AL_FORMAT_STEREO16;
			break;
		default:
			XE_LOG( LoggerLevel::Error, "unsupported bytes per sample count : %1", _BytesPerSample );
			break;
		}
	}
	break;
	default:
		XE_LOG( LoggerLevel::Error, "unsupported channel count : %1", _Channels );
		break;
	}

	return format;
}
