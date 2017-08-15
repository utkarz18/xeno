#pragma once

#include <iostream>

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

#include "../utils/stringutils.h"

namespace xeno { namespace audio {

	class Audio
	{
	private:
		std::string m_Name;
		std::string m_Filename;
		bool m_Playing;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		float m_Gain;

	public:
		Audio(const std::string& name, const std::string& filename);
		~Audio();

		void play();
		void loop();
		void pause();
		void stop();

		void setGain(float gain);

		inline const float getGain() const { return m_Gain; }
		inline const std::string& getName() const { return m_Name; }
		inline const std::string& getFileName() const { return m_Filename; }
		inline const bool isPlaying() const { return m_Playing; }

		friend void destroy_on_finish(ga_Handle* in_handle, void* in_context);
	};

}}