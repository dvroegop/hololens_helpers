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

	IAsyncAction^ SpatialAudioPlayer::PlaySoundFromResource(String^ resourceName)
	{		
		return create_async([this, resourceName]
		{
			this->InternalPlaySound(resourceName);
		});
	}

	void SpatialAudioPlayer::InternalPlaySound(String^ resourceName) {

		auto res = this->LoadData(resourceName);

		if (res == nullptr) {
			// Error
		}

	}

	IBuffer^ SpatialAudioPlayer::LoadData(String^ resourceName)
	{
		auto uri = ref new Windows::Foundation::Uri(resourceName);

		IAsyncOperation<StorageFile^>^ sourceFile = StorageFile::GetFileFromApplicationUriAsync(uri);
		auto xx = create_task(sourceFile);
		xx.then([](StorageFile^ file) -> IAsyncOperation<IBuffer^>^ {
			return FileIO::ReadBufferAsync(file);
		}).then([](IBuffer^ buffer) -> IBuffer^ {
			return buffer;
		});

		return nullptr;
	}
}
