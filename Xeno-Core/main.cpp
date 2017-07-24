#include "src/graphics/window.h"
#include "src/maths/maths.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/Simple2DRenderer.h"
#include "src/graphics/batchRenderer2D.h"
#include "src/utils/timer.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#define TEST_50K 0

int main()
{
	using namespace xeno;
	using namespace graphics;
	using namespace maths;

	Window window("Xeno!", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader2.enable();
	shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));


	TileLayer layer(&shader);

#if TEST_50K
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

#else
	Group* group = new Group(mat4::translation(vec3(-15.0f, 5.0f, 0)) * mat4::rotation(45.0f, vec3(0, 0, 1)));
	group->add(new Sprite(0, 0, 6, 3, maths::vec4(1, 1, 1, 1)));

	Group* button = new Group(mat4::translation(vec3(0.5f, 0.5f, 0)));
	button->add(new Sprite(0, 0, 5.0f, 2.0f, maths::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, maths::vec4(0.9, 0.2, 0.1, 1)));
	group->add(button);
	layer.add(group);

#endif

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(0, 0, -2, -2, maths::vec4(1, 0, 1, 1)));
		
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();	
		double x, y;
		window.getMousePosition(x, y);
		
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		//shader2.enable();
		//shader2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		
		layer.render();
		//layer2.render();

		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d FPS\n", frames);
			frames = 0;
		}
	}

	return 0;
}