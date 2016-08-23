#pragma once

#include <experimental\resumable>
#include <pplawait.h>
#include "RiffReader.h"

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
		task<IBuffer^> LoadData(String^ resourceName);
		IXAudio2MasteringVoice* masteringVoice;

		void InternalPlaySound(String^ resourceName);
		IXAudio2SourceVoice* CreateVoice(WAVEFORMATEX* wavFormat);
		XAUDIO2_BUFFER CreateAudioBuffer(AudioData data);
	};

}