#include "audio.h"
#include "audio_manager.h"

namespace xeno { namespace audio {

	Audio::Audio(const std::string& name, const std::string& filename)
		: m_Name(name), m_Filename(filename), m_Playing(false), m_Handle(nullptr)
	{
		std::vector<std::string> split = split_string(m_Filename, '.');
		if (split.size() < 2)
		{
			std::cout << "[Sound] Invalid file name '" << m_Filename << "'!" << std::endl;
			return;
		}
		m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

		if (m_Sound == nullptr)
			std::cout << "[Sound] Could not load file '" << m_Filename << "'!" << std::endl;
	}

	Audio::~Audio()
	{
		ga_sound_release(m_Sound);
	}

	void Audio::play()
	{
		if (m_Playing)
			return;

		gc_int32 quit = 0;
		
		if (m_Handle == nullptr)
		{
			m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound, &destroy_on_finish, &quit, NULL);
			m_Handle->audio = this;
		}
		
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Audio::loop()
	{
		if (m_Playing)
			return;

		gc_int32 quit = 0;
		gau_SampleSourceLoop* loopSrc = 0;
		
		if (m_Handle == nullptr)
		{
			m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound, &destroy_on_finish, &quit, &loopSrc);
			m_Handle->audio = this;
		}
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Audio::pause()
	{
		if (!m_Playing)
			return;

		ga_handle_stop(m_Handle);
		m_Playing = false;
	}

	void Audio::stop()
	{
		if (!m_Playing)
			return;
		ga_handle_destroy(m_Handle);
		m_Handle = nullptr;
		m_Playing = false;
	}	

	void Audio::setGain(float gain)
	{
		if (!m_Playing)
			return;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void destroy_on_finish(ga_Handle* in_handle, void* in_context)
	{	
		Audio* audio = (Audio*)in_handle->audio;
		audio->stop();
	}


}}