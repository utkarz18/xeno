#include "audio.h"
#include "audio_manager.h"

namespace xeno { namespace audio {

	void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);

	Audio::Audio(const std::string& name, const std::string& filename)
		:m_Name(name), m_Filename(filename)
	{
		m_Sound = gau_load_sound_file(filename.c_str(), "wav");
	}

	Audio::~Audio()
	{
		ga_sound_release(m_Sound);
	}

	void Audio::play()
	{
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
		ga_handle_play(m_Handle);
	}

	void Audio::loop()
	{

	}

	void Audio::pause()
	{

	}

	void Audio::stop()
	{

	}


	void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		gc_int32* flag = (gc_int32*)(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);
	}
}}