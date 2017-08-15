#include "audio_manager.h"

namespace xeno { namespace audio {

	gau_Manager* AudioManager::m_Manager = nullptr;
	ga_Mixer* AudioManager::m_Mixer = nullptr;

	std::vector<Audio*> AudioManager::m_AudioList;

	void AudioManager::init()
	{
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
	}

	void AudioManager::add(Audio* audio)
	{
		m_AudioList.push_back(audio);
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

		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}

	void AudioManager::update()
	{
		gau_manager_update(m_Manager);
	}
	
}}