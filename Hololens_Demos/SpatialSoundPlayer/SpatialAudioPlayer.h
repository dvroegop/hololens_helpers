#pragma once

using namespace Windows::Storage::Streams;
using namespace Platform;


namespace SpatialSoundPlayer {
	public ref class SpatialAudioPlayer sealed
	{
	public:
		SpatialAudioPlayer();

		IAsyncAction^ PlaySoundFromResource(String^ resourceName);

	private:
		IBuffer^ LoadData(String^ resourceName);

		void InternalPlaySound(String^ resourceName);
	};

}