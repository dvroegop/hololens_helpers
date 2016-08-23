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
		ChunkInfo FindChunk(IBuffer^ buffer, uint32 chunkId);
		byte* GetBufferByteAccess(IBuffer^ buffer);

	public:
		RiffReader();
		AudioData Read(IBuffer^ buffer);
	};
}

