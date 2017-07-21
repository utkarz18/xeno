#pragma once

#include <GL/glew.h>
#include "../maths/maths.h"
#include "renderable2D.h"

namespace xeno { namespace graphics {

	class Renderer2D
	{
	protected:
		std::vector<maths::mat4> m_TransformationStack;

	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(maths::mat4::indentity());
		}

	public:
		void push(const maths::mat4& matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
		}

		void pop()
		{
			if(m_TransformationStack.size() > 1)
				m_TransformationStack.pop_back();
		}

		virtual void begin() {};
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void end() {};
		virtual void flush() = 0;
	};
}}