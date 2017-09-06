#include "audio_manager.h"

namespace xeno { namespace audio {

#ifndef XENO_PLATFORM_WEB
	gau_Manager* AudioManager::m_Manager = nullptr;
	ga_Mixer* AudioManager::m_Mixer = nullptr;
#endif

	std::vector<Audio*> AudioManager::m_AudioList;

	void AudioManager::init()
	{

#ifdef XENO_PLATFORM_WEB
		EM_ASM(
		Module.SoundManager = {};
		Module.SoundManager.m_AudioList = {};
		Module.SoundManagerAdd = function(name, filename) { Module.SoundManager.m_AudioList[name] = new Audio(filename); };
		Module.SoundManagerPlay = function(name) { Module.SoundManager.m_AudioList[name].play(); };
		Module.SoundManagerPause = function(name) { Module.SoundManager.m_AudioList[name].pause(); };
		Module.SoundManagerStop = function(name) { Module.SoundManagerPause(name); Module.SoundManager.m_AudioList[name].currentTime = 0; Module.SoundManager.m_AudioList[name].loop = false; };
		Module.SoundManagerLoop = function(name) { Module.SoundManager.m_AudioList[name].play(); Module.SoundManager.m_AudioList[name].loop = true; };
		Module.SoundManagerSetGain = function(name, gain) { Module.SoundManager.m_AudioList[name].volume = gain; };
		);
#else
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
#endif
	}

	Audio* AudioManager::add(Audio* audio)
	{
		m_AudioList.push_back(audio);

#ifdef XENO_PLATFORM_WEB
		SoundManagerAdd(audio->getName().c_str(), audio->getFileName().c_str());
#endif
		return audio;
	}

	Audio* AudioManager::get(const std::string& name)
	{
		for (Audio* audio : m_AudioList)
		{
			if (audio->getName() == name)
				return audio;
		}
	}


	void AudioManager::clean()
	{	
		for (int i = 0; i < m_AudioList.size(); i++)
			delete m_AudioList[i];

#ifndef XENO_PLATFORM_WEB
		gau_manager_destroy(m_Manager);
		gc_shutdown();
#endif

	}

	void AudioManager::update()
	{
#ifndef XENO_PLATFORM_WEB
		gau_manager_update(m_Manager);
#endif
	}
}}