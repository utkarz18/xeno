#include "font.h"

namespace xeno{namespace graphics{
	
	Font::Font(std::string name, std::string filename, unsigned int size)
		:m_Name(name), m_Filename(filename), m_Size(size)
	{
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 32, m_Filename.c_str());
	}
}}