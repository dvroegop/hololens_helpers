#include "pch.h"
#include "SpatialAudioPlayer.h"
#include <comutil.h>
#include <robuffer.h>


using namespace concurrency;



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

	Windows::Foundation::IAsyncAction^ SpatialAudioPlayer::PlaySoundFromResourceAsync(String^ resourceName)
	{		
		return create_async([this, resourceName]
		{
			InternalPlaySound(resourceName);
		});
	}

	void SpatialAudioPlayer::InternalPlaySound(String^ resourceName) {
		std::shared_ptr<AudioSample> sample = create_task(LoadData(resourceName)).then();
	
		auto reader = new RiffReader();
		auto data = reader->Read(sample->buffer, sample->bufferSize);

		IXAudio2SourceVoice* voice = CreateVoice(data.waveFormat);
		XAUDIO2_BUFFER audioBuffer = CreateAudioBuffer(data);
		HRESULT hr = voice->SubmitSourceBuffer(&audioBuffer);
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

	std::shared_ptr<AudioSample> SpatialAudioPlayer::LoadData(String^ resourceName)
	{

		auto uri = ref new Windows::Foundation::Uri(resourceName);

		auto file = co_await Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(uri);
		//
		//auto buffer = co_await Windows::Storage::FileIO::ReadBufferAsync(file);

		//byte* resultingData = GetBufferByteAccess(buffer);
		auto sample = std::make_shared<AudioSample>();
		//sample->buffer = resultingData;
		//sample->bufferSize = buffer->Length;
		return sample;
	}

	byte * SpatialAudioPlayer::GetBufferByteAccess(IBuffer ^ buffer)
	{
		Object^ obj = buffer;

		ComPtr<IInspectable> insp(reinterpret_cast<IInspectable*>(obj));
		ComPtr<IBufferByteAccess> bufferByteAccess;

		insp.As(&bufferByteAccess);

		byte* soundData = nullptr;

		bufferByteAccess->Buffer(&soundData);

		return soundData;
	}


}
