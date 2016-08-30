#pragma once

using namespace Windows::Storage::Streams;

namespace SpatialSoundPlayer {

	//public ref class AudioSample sealed {
	//private:
	//	int _bufferSize;
	//	Platform::Array<byte> _buffer;

	//public:
	//	AudioSample();
	//	property Platform::Array<byte> buffer {
	//		Platform::Array<byte> get() { return _buffer }
	//		void set(Platform::Array<byte> value) { _buffer = value; }
	//	}

	//	property int bufferSize {
	//		int get() { return _bufferSize; }
	//		void set(int value) { _bufferSize = value; }
	//	}

	//};

	class AudioSample {
	public:
		unsigned int bufferSize;
		byte* buffer;
	};
}