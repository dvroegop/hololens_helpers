#include "pch.h"
#include "SpatialAudioPlayer.h"
#include <comutil.h>

namespace SpatialSoundPlayer {

	SpatialAudioPlayer::SpatialAudioPlayer()
	{
	}

	void SpatialAudioPlayer::PlaySoundFromResource(String^ resourceName)
	{
		HRESULT hr;
		IBuffer fileHandle;;
		if (FAILED(hr = this->LoadData(resourceName, fileHandle))) {
			throw Platform::Exception::CreateException(hr);
		}


	}

	HRESULT SpatialAudioPlayer::LoadData(String^ resourceName, IBuffer^ result)
	{

		return S_OK;
	}
}
