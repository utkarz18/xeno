#include "Font.h"

namespace xeno{ namespace graphics
{
	Font::Font(std::string name, std::string filename, int size)
		:m_Filename(filename), m_Size(size)
	{
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, m_Filename.c_str());
		createFontTexture(m_FTAtlas);
	}

	void Font::createFontTexture(ftgl::texture_atlas_t* atlas)
	{
		glGenTextures(1, &atlas->id);
		glBindTexture(GL_TEXTURE_2D, atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, atlas->data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}}