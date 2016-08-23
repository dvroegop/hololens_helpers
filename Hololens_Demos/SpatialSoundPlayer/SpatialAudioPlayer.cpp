#include "pch.h"
#include "SpatialAudioPlayer.h"
#include <comutil.h>

using namespace concurrency;
using namespace Windows::Foundation;
using namespace Windows::Storage;


namespace SpatialSoundPlayer {

	SpatialAudioPlayer::SpatialAudioPlayer()
	{
		HRESULT hr = XAudio2Create(&xAudio);
		if (FAILED(hr))
			ref new COMException(hr, "Cannot create XAudio2");

		XAUDIO2_DEBUG_CONFIGURATION debugConfig = { 0 };
		debugConfig.TraceMask = XAUDIO2_LOG_DETAIL | XAUDIO2_LOG_WARNINGS;
		xAudio->SetDebugConfiguration(&debugConfig);

		hr = xAudio->CreateMasteringVoice(&masteringVoice);
		if (FAILED(hr))
			ref new COMException(hr, "Cannot create mastering voice");

		xAudio->StartEngine();

	}

	IAsyncAction^ SpatialAudioPlayer::PlaySoundFromResourceAsync(String^ resourceName)
	{
		return create_async([this, resourceName]
		{
			InternalPlaySound(resourceName);
		});
	}

	void SpatialAudioPlayer::InternalPlaySound(String^ resourceName) {
		//auto buffer = this->LoadData(resourceName).then([this, buffer]() {
		//	
		//auto reader = new RiffReader();
		//auto data = reader->Read(buffer);

		//IXAudio2SourceVoice* voice = this->CreateVoice(data.waveFormat);
		//XAUDIO2_BUFFER audioBuffer = this->CreateAudioBuffer(data);
		//HRESULT hr = voice->SubmitSourceBuffer(&audioBuffer);
		//});

	}

	IXAudio2SourceVoice * SpatialAudioPlayer::CreateVoice(WAVEFORMATEX * wavFormat)
	{
		IXAudio2SourceVoice* voice = NULL;
		HRESULT hr = xAudio->CreateSourceVoice(&voice, wavFormat);
		if (FAILED(hr))
			throw ref new COMException(hr, "CreateSourceVoice failed");

		return voice;
	}

	XAUDIO2_BUFFER SpatialAudioPlayer::CreateAudioBuffer(AudioData data)
	{
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.AudioBytes = data.numberOfBytes;
		buffer.pAudioData = data.bytes;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

		return buffer;
	}

	task<IBuffer^> SpatialAudioPlayer::LoadData(String^ resourceName)
	{
		auto uri = ref new Windows::Foundation::Uri(resourceName);

		auto file = co_await StorageFile::GetFileFromApplicationUriAsync(uri);
		if (nullptr == file)
			return nullptr;

		IBuffer^ buffer = co_await FileIO::ReadBufferAsync(file);

		return buffer;
	}
}
