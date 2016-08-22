#include "pch.h"
#include "SpatialAudioPlayer.h"
#include <comutil.h>

using namespace concurrency;
using namespace Windows::Foundation;
using namespace Windows::Storage;

namespace SpatialSoundPlayer {

	SpatialAudioPlayer::SpatialAudioPlayer()
	{
	}

	IAsyncAction^ SpatialAudioPlayer::PlaySoundFromResourceAsync(String^ resourceName)
	{
		return create_async([this, resourceName]
		{
			InternalPlaySound(resourceName);
		});

		//return nullptr;
	}

	void SpatialAudioPlayer::InternalPlaySound(String^ resourceName) {

		this->LoadData(resourceName);

	}

	task<IBuffer^> SpatialAudioPlayer::LoadData(String^ resourceName) 
	{
		auto uri = ref new Windows::Foundation::Uri(resourceName);

		auto file = co_await StorageFile::GetFileFromApplicationUriAsync(uri);
		////if (nullptr == file)
		////	return nullptr;

		//IBuffer^ buffer = await FileIO::ReadBufferAsync(file);
		////return buffer;
		return nullptr;
	}
}
