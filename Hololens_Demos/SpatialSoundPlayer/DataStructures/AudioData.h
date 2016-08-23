#pragma once
#include <pch.h>
using namespace Platform;

namespace SpatialSoundPlayer {
	struct AudioData
	{
		byte * bytes;
		unsigned int numberOfBytes;
		WAVEFORMATEX* waveFormat;
	};
}