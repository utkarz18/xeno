#pragma once

#include<string>

#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace xeno { namespace audio {

	class Audio
	{
	private:
		std::string m_Name;
		std::string m_Filename;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;

	public:
		Audio(const std::string& name, const std::string& filename);
		~Audio();

		void play();
		void loop();
		void pause();
		void stop();

		inline const std::string& getName() const { return m_Name; }
		inline const std::string& getFileName() const { return m_Filename; }
	};

}}