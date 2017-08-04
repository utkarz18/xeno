#pragma once

#include <string>
#include "../../ext/freetype-gl/freetype-gl.h"

namespace xeno { namespace graphics {

	class Font
	{
	private:
		std::string m_Filename;
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		unsigned int m_Size;

	public:
		Font(std::string name, std::string filename, int size);

		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
		inline const unsigned int getID() const { return m_FTAtlas->id; }
		inline const std::string& getFileName() const { return m_Filename; }
		inline const int getSize() const { return m_Size; }

	private:
		void createFontTexture(ftgl::texture_atlas_t* atlas);
	};
}}