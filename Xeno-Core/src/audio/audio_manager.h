#pragma once

#include <vector>
#include "audio.h"

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace xeno { namespace audio {

	class AudioManager
	{
	private:
		friend class Audio;

		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;

		static std::vector<Audio*> m_AudioList;

	private:
		AudioManager() { }

	public:
		static void init();
		static void add(Audio* audio);
		static Audio* get(const std::string& name);
		static void clean();
		static void update();
	};

}}