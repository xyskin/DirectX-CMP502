///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "soundclass.h"

SoundClass::SoundClass()
{
	m_DirectSound = 0;
	m_primaryBuffer = 0;
	m_secondaryBufferLC = 0;
	m_secondaryBufferLD = 0;
	m_secondaryBufferLE = 0;
	m_secondaryBufferLF = 0;
	m_secondaryBufferLG = 0;
	m_secondaryBufferLA = 0;
	m_secondaryBufferLB = 0;
	m_secondaryBufferMC = 0;
	m_secondaryBufferMD = 0;
	m_secondaryBufferME = 0;
	m_secondaryBufferMF = 0;
	m_secondaryBufferMG = 0;
	m_secondaryBufferMA = 0;
	m_secondaryBufferMB = 0;
	m_secondaryBufferHC = 0;
	m_secondaryBufferHD = 0;
	m_secondaryBufferHE = 0;
	m_secondaryBufferHF = 0;
	m_secondaryBufferHG = 0;
	m_secondaryBufferHA = 0;
	m_secondaryBufferHB = 0;
}


SoundClass::SoundClass(const SoundClass& other)
{
}


SoundClass::~SoundClass()
{
}


bool SoundClass::Initialize(HWND hwnd)
{
	bool result;

	// Initialize direct sound and the primary sound buffer.
	result = InitializeDirectSound(hwnd);
	if (!result)
	{
		return false;
	}

	// Load a wave audio file onto a secondary buffer.
	//char* str = (char*)malloc(sizeof(s)+);

	result = LoadWaveFile("../Engine/data/LC.wav", &m_secondaryBufferLC);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LD.wav", &m_secondaryBufferLD);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LE.wav", &m_secondaryBufferLE);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LF.wav", &m_secondaryBufferLF);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LG.wav", &m_secondaryBufferLG);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LA.wav", &m_secondaryBufferLA);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/LB.wav", &m_secondaryBufferLB);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MC.wav", &m_secondaryBufferMC);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MD.wav", &m_secondaryBufferMD);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/ME.wav", &m_secondaryBufferME);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MF.wav", &m_secondaryBufferMF);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MG.wav", &m_secondaryBufferMG);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MA.wav", &m_secondaryBufferMA);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/MB.wav", &m_secondaryBufferMB);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HC.wav", &m_secondaryBufferHC);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HD.wav", &m_secondaryBufferHD);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HE.wav", &m_secondaryBufferHE);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HF.wav", &m_secondaryBufferHF);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HG.wav", &m_secondaryBufferHG);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HA.wav", &m_secondaryBufferHA);
	if (!result)
	{
		return false;
	}
	result = LoadWaveFile("../Engine/data/HB.wav", &m_secondaryBufferHB);
	if (!result)
	{
		return false;
	}

	//std::string st("../Engine/data/");
	//st.append(s);
	//st.append(".wav");

	//result = LoadWaveFile("../Engine/data/3g.wav", &m_secondaryBuffer1);

	// Play the wave file now that it has been loaded.
	//result = PlayWaveFile();
	//if (!result)
	//{
	//	return false;
	//}
	return true;
}


void SoundClass::Shutdown()
{
	// Release the secondary buffer.
	ShutdownWaveFile(&m_secondaryBufferLC);
	ShutdownWaveFile(&m_secondaryBufferLD); 
	ShutdownWaveFile(&m_secondaryBufferLE); 
	ShutdownWaveFile(&m_secondaryBufferLF);
	ShutdownWaveFile(&m_secondaryBufferLG);
	ShutdownWaveFile(&m_secondaryBufferLA);
	ShutdownWaveFile(&m_secondaryBufferLB);
	// Shutdown the Direct Sound API.
	ShutdownDirectSound();

	return;
}

bool SoundClass::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;


	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void SoundClass::ShutdownDirectSound()
{
	// Release the primary sound buffer pointer.
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// Release the direct sound interface pointer.
	if (m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}

	return;
}

bool SoundClass::LoadWaveFile(char* filename, IDirectSoundBuffer8** secondaryBuffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if (waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		MessageBox(NULL, L"Could not initialize the Sound object.", L"Error", MB_OK);
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	return true;
}

void SoundClass::ShutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	// Release the secondary sound buffer.
	if (*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = 0;
	}

	return;
}
bool SoundClass::PlayWaveFile(IDirectSoundBuffer8* m_secondaryBuffer1)
{
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	result = m_secondaryBuffer1->SetCurrentPosition(0);
	if (FAILED(result))
	{
		return false;
	}

	// Set volume of the buffer to 100%.
	result = m_secondaryBuffer1->SetVolume(DSBVOLUME_MAX);
	if (FAILED(result))
	{
		return false;
	}

	// Play the contents of the secondary sound buffer.
	result = m_secondaryBuffer1->Play(0, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}