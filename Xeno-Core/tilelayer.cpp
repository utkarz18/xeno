#include "tilelayer.h"

TileLayer::TileLayer(xeno::graphics::Shader* shader)
: Layer(new  xeno::graphics::BatchRenderer2D(), shader, xeno::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
	
}

TileLayer::~TileLayer()
{
}