#include "AudioUtil.h"

#include <AL/al.h>
#include <AL/alc.h>

void XE::AudioUtil::CheckError(const String& file, XE::uint64 line, const String& expr)
{
	ALenum err = alGetError();

	if (err != AL_NO_ERROR)
	{
// 		switch (err)
// 		{
// 		case AL_INVALID_NAME:
// 			XE_LOG(LoggerLevel::Error, "OpenAL Failed: \n\t AL_INVALID_NAME\n\t\t a bad name (ID) has been specified.\n\t\t\t%1:{%1}\t{%2}", file, line, expr);
// 			break;
// 		case AL_INVALID_ENUM:
// 			XE_LOG(LoggerLevel::Error, "OpenAL Failed: \n\t AL_INVALID_ENUM\n\t\t an unacceptable value has been specified for an enumerated argument.\n\t\t\t%1:{%1}\t{%2}", file, line, expr);
// 			break;
// 		case AL_INVALID_VALUE:
// 			XE_LOG(LoggerLevel::Error, "OpenAL Failed: \n\t AL_INVALID_VALUE\n\t\t a numeric argument is out of range.\n\t\t\t%1:{%1}\t{%2}", file, line, expr);
// 			break;
// 		case AL_OUT_OF_MEMORY:
// 			XE_LOG(LoggerLevel::Error, "OpenAL Failed: \n\t AL_OUT_OF_MEMORY\n\t\t there is not enough memory left to execute the command.\n\t\t\t%1:{%1}\t{%2}", file, line, expr);
// 			break;
// 		case AL_INVALID_OPERATION:
// 			XE_LOG(LoggerLevel::Error, "OpenAL Failed: \n\t AL_INVALID_OPERATION\n\t\t the specified operation is not allowed in the current state.\n\t\t\t%1:{%1}\t{%2}", file, line, expr);
// 			break;
// 		default:
// 			break;
// 		}
	}
}
