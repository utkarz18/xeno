#include "label.h"

namespace xeno { namespace graphics {

	Label::Label(std::string text, float x, float y, maths::vec4 color)
		:m_Text(text)
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::submit(Renderer2D* renderer) const
	{
		renderer->drawString(m_Text, m_Position, m_Color);
	}
}}