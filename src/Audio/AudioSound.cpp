#include "AudioSound.h"

#define MA_NO_WASAPI
#define MA_NO_DSOUND
#define MA_NO_WINMM
#define MA_NO_ALSA
#define MA_NO_PULSEAUDIO
#define MA_NO_JACK
#define MA_NO_COREAUDIO
#define MA_NO_SNDIO
#define MA_NO_AUDIO4
#define MA_NO_OSS
#define MA_NO_AAUDIO
#define MA_NO_OPENSL
#define MA_NO_WEBAUDIO
#define MA_NO_NULL
#define MA_NO_ENCODING
#define MA_NO_DEVICE_IO
#define MA_NO_THREADING
#define MA_NO_DEVICE_IO
#define MA_NO_GENERATION
#define MA_LOG_LEVEL MA_LOG_LEVEL_ERROR


#define STB_VORBIS_HEADER_ONLY
#include <miniaudio/stb_vorbis.c>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#undef STB_VORBIS_HEADER_ONLY
#include <miniaudio/stb_vorbis.c>

#define AUDIO_FARME_SIZE 640

BEG_META( AudioSound )
type->Property( "Sound", &AudioSound::_Path );
END_META()

XE::AudioSound::AudioSound()
{

}

XE::AudioSound::~AudioSound()
{

}

void XE::AudioSound::AssetLoad()
{
	ma_decoder_config config = ma_decoder_config_init( ma_format_s16, 2, 48000 );

	_Decoder = new ma_decoder;
	ma_result result = ma_decoder_init_file( _Path.u8string().c_str(), &config, _Decoder );
	if( result != MA_SUCCESS )
	{
		delete _Decoder;
		_Decoder = nullptr;
	}
}

void XE::AudioSound::AssetUnload()
{
	if( _Decoder )
	{
		ma_decoder_uninit( _Decoder );

		delete _Decoder;
		_Decoder = nullptr;
	}
}

XE::uint32 XE::AudioSound::GetBits() const
{
	switch( _Decoder->outputFormat )
	{
	case ma_format::ma_format_u8:
		return 8;
	case ma_format::ma_format_s16:
		return 16;
	case ma_format::ma_format_s24:
		return 24;
	case ma_format::ma_format_s32:
	case ma_format::ma_format_f32:
		return 32;
	default:
		break;
	}

	return 0;
}

XE::uint32 XE::AudioSound::GetChannels() const
{
	return _Decoder->outputChannels;
}

XE::uint32 XE::AudioSound::GetSampleRate() const
{
	return _Decoder->outputSampleRate;
}

XE::uint32 XE::AudioSound::GetFrameCount() const
{
	return ma_decoder_get_length_in_pcm_frames( _Decoder );
}

const XE::FileSystem::Path & XE::AudioSound::GetSoundPath() const
{
	return _Path;
}

bool XE::AudioSound::Seek( XE::uint32 val )
{
	return ma_decoder_seek_to_pcm_frame( _Decoder, val ) == MA_SUCCESS;
}

XE::Array<XE::uint8> XE::AudioSound::GetOneFrame()
{
	XE::uint8 buf[AUDIO_FARME_SIZE] = {};
	XE::Array<XE::uint8> arr( XE::MemoryResource::GetStackMemoryResource() );

	auto sz = ma_decoder_read_pcm_frames( _Decoder, buf, AUDIO_FARME_SIZE );
	if( sz != 0 )
	{
		arr.insert( arr.begin(), buf, buf + sz );
	}

	return std::move( arr );
}
