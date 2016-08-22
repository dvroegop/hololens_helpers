#pragma once
#include <pch.h>

namespace SpatialSoundPlayer {
	struct AudioData
	{
		byte * bytes;
		unsigned int numberOfBytes;
		WAVEFORMATEX* waveFormat;
	};
}