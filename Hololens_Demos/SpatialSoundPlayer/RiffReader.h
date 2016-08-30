#pragma once
#include <pch.h>
#include <Xaudio2.h>
#include "DataStructures\ChunkInfo.h"
#include "DataStructures\AudioData.h"

using namespace Microsoft::WRL;
using namespace Windows::Storage::Streams;

namespace SpatialSoundPlayer {
	class RiffReader sealed
	{
	private:
		ChunkInfo FindChunk(byte* buffer, int bufferSize, uint32 chunkId);
		

	public:
		RiffReader();
		AudioData Read(byte* buffer, int bufferSize);
	};
}

