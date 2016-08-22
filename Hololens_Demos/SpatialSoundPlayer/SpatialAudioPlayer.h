#pragma once

#include <experimental\resumable>
#include <pplawait.h>

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
		task<IBuffer^> LoadData(String^ resourceName);

		void InternalPlaySound(String^ resourceName);
	};

}