#pragma once

#include "renderable2D.h"

namespace xeno { namespace graphics {
	
	class Label : public Renderable2D
	{
	public:
		std::string text;
		maths::vec3& position;
		float x, y;
	public:
		Label(std::string text, float x, float y, unsigned int color);
		void submit(Renderer2D* renderer) const override;
	};

}}