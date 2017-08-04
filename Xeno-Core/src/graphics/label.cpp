#include "label.h"

namespace xeno { namespace graphics {

	Label::Label(std::string text, float x, float y, Font* font, maths::vec4 color)
		:Renderable2D(), m_Text(text), position(m_Position), m_Font(font)
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::submit(Renderer2D* renderer) const
	{	
		renderer->drawString(m_Text, m_Position, *m_Font, m_Color);
	}
}}