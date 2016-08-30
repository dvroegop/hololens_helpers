#pragma once

#include "pch.h"
#include <pplawait.h>
#include <experimental\resumable>
#include <ppltasks.h>
#include "RiffReader.h"
#include "DataStructures\AudioSample.h"

using namespace Microsoft::WRL;
using namespace Windows::Storage::Streams;
using namespace Platform;
using namespace concurrency;

namespace SpatialSoundPlayer {
	public ref class SpatialAudioPlayer sealed
	{
	public:
		SpatialAudioPlayer();
		
		Windows::Foundation::IAsyncAction^ PlaySoundFromResourceAsync(String^ resourceName);

	private:
		
		ComPtr<IXAudio2> xAudio;
		std::shared_ptr<AudioSample> LoadData(String^ resourceName);
		byte * GetBufferByteAccess(IBuffer ^ buffer);
		IXAudio2MasteringVoice* masteringVoice;

		void InternalPlaySound(String^ resourceName);
		IXAudio2SourceVoice* CreateVoice(WAVEFORMATEX* wavFormat);
		XAUDIO2_BUFFER CreateAudioBuffer(AudioData data);
	};

}