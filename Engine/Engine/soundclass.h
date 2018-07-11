///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_
/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
///////////////////////////////////////////////////////////////////////////////
class SoundClass
{
private:

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();

	bool Initialize(HWND);
	void Shutdown();
	bool PlayWaveFile(IDirectSoundBuffer8*);

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

	

private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;


public:
	IDirectSoundBuffer8* m_secondaryBufferLC, *m_secondaryBufferLD, *m_secondaryBufferLE, *m_secondaryBufferLF, *m_secondaryBufferLG, *m_secondaryBufferLA, *m_secondaryBufferLB;
	IDirectSoundBuffer8* m_secondaryBufferMC, *m_secondaryBufferMD, *m_secondaryBufferME, *m_secondaryBufferMF, *m_secondaryBufferMG, *m_secondaryBufferMA, *m_secondaryBufferMB;
	IDirectSoundBuffer8* m_secondaryBufferHC, *m_secondaryBufferHD, *m_secondaryBufferHE, *m_secondaryBufferHF, *m_secondaryBufferHG, *m_secondaryBufferHA, *m_secondaryBufferHB;

	};

#endif
#pragma once
