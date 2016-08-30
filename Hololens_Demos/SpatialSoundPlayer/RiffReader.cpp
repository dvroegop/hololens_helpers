#include "pch.h"
#include "RiffReader.h"

#include <robuffer.h>

using namespace SpatialSoundPlayer;


ChunkInfo RiffReader::FindChunk(byte*buffer, int bufferSize, uint32 chunkId)
{
	auto ptr = buffer;

	byte* endPtr = ptr + (sizeof(byte) * bufferSize);

	ChunkInfo info;

	while (ptr < endPtr) {
		auto chunk = reinterpret_cast<RiffChunk*>(ptr);
		info.id = chunk->tag;
		info.size = chunk->size;

		ptr += sizeof(RiffChunk);

		if (chunk->tag == fourccRIFF) {
			auto type = reinterpret_cast<uint32*>(ptr);
			info.size = 4;
		}

		info.data = ptr;
		ptr += (info.size * sizeof(byte));

		if (info.id = chunkId)
		{
			return info;
		}
	}

	return info;
}





RiffReader::RiffReader()
{
}

AudioData RiffReader::Read(byte* buffer, int bufferSize)
{
	
	auto formatChunk = FindChunk(buffer, fourccFMT, bufferSize);
	auto dataChunk = FindChunk(buffer, fourccDATA, bufferSize);

	auto waveFormat = reinterpret_cast<WAVEFORMATEX*>(formatChunk.data);

	AudioData data;
	data.bytes = dataChunk.data;
	data.numberOfBytes = dataChunk.size;
	data.waveFormat = waveFormat;

	return data;
}





