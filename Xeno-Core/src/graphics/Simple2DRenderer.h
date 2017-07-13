#pragma once

#include <deque>
#include "renderer2D.h"

namespace xeno { namespace graphics {

	class Simple2DRenderer : public Renderer2D
	{
	private:
		std::deque<const Renderable2D*> m_RenderQueue;
	public:
		virtual void submit(const Renderable2D* renderable) override;
		virtual void flush() override;
	};
}}