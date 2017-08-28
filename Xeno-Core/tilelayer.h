#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchRenderer2D.h"


class TileLayer : public xeno::graphics::Layer
{
public:
	TileLayer(xeno::graphics::Shader* shader);
	~TileLayer();
};

