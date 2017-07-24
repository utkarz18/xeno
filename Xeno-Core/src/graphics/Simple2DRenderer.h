#pragma once

#include <deque>
#include "renderer2D.h"
#include "renderable2D.h"
#include "static_sprite.h"

namespace xeno { namespace graphics {

	class Simple2DRenderer : public Renderer2D
	{
	private:
		std::deque<const StaticSprite*> m_RenderQueue;
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;
	};
}}