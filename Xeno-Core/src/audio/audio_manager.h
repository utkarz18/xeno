#pragma once

#include <vector>
#include "audio.h"

#ifdef XENO_PLATFORM_WEB
	#include <emscripten/emscripten.h>
#else
	#include "../../ext/gorilla-audio/ga.h"
	#include "../../ext/gorilla-audio/gau.h"
#endif

#ifdef XENO_PLATFORM_WEB
	extern "C" void SoundManagerAdd(const char* name, const char* filename);
	extern "C" void SoundManagerPlay(const char* name);
	extern "C" void SoundManagerPause(const char* name);
	extern "C" void SoundManagerStop(const char* name);
	extern "C" void SoundManagerLoop(const char* name);
	extern "C" void SoundManagerSetGain(const char* name, double gain);
#endif

namespace xeno { namespace audio {

	class AudioManager
	{
	private:
		friend class Audio;

#ifndef XENO_PLATFORM_WEB
		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;
#endif

		static std::vector<Audio*> m_AudioList;

	private:
		AudioManager() { }

	public:
		static void init();
		static Audio* add(Audio* audio);
		static Audio* get(const std::string& name);
		static void clean();
		static void update();
	};

}}