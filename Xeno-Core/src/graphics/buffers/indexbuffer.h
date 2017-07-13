#pragma once

#include <GL/glew.h>

namespace xeno { namespace graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(GLushort* data, GLsizei count);

			void bind() const;
			void unbind() const;

			~IndexBuffer();

			inline GLuint getCount() const { return m_Count; }
		};

	}
}