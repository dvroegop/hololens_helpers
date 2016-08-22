#pragma once

using namespace Windows::Storage::Streams;

using namespace Platform;
namespace SpatialSoundPlayer {
	public ref class SpatialAudioPlayer sealed
	{
	public:
		SpatialAudioPlayer();

		void PlaySoundFromResource(String^ resourceName);

	private:
		HRESULT LoadData(String^ resourceName, IBuffer^ result);
	};

}