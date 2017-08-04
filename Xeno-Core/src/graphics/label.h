#pragma once

#include "renderable2D.h"

namespace xeno { namespace graphics {
	
	class Label : public Renderable2D
	{
	private:
		std::string m_Text;
		maths::vec3& position;
		float x, y;
	public:
		Label(std::string text, float x, float y, maths::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};

}}