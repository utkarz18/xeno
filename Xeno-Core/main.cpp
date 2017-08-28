#if 0
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/sprite.h"
#include "src/graphics/batchRenderer2D.h"
#include <FreeImage.h>
#include "src/graphics/font_manager.h"
#include "src/audio/audio_manager.h"

#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"
#include "src/graphics/label.h"

#include "tilelayer.h"

int main()
{
	using namespace xeno;
	using namespace graphics;
	using namespace audio;
	using namespace maths;

	Window window("Xeno!", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);
	Texture* textures[] = 
	{
		new Texture("test.png"),
		new Texture("tb.png"),
		new Texture("tc.png")
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			int r = rand() % 250;
			int color = 0xffff00 << 8 | r;

			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, color));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
	Label* fps = new Label("", 0.4f, 0.4f, 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);

	layer.add(g);

	shader.enable();	
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	//AudioManager::add(new Audio("test", "test1.wav"));
	AudioManager::add(new Audio("loop", "loop.ogg"));
	//AudioManager::get("loop")->play();

	float gain = 0.5f;
	AudioManager::get("loop")->setGain(gain);

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	while (!window.closed())
	{	
		t += 0.001f;
		window.clear();
		double x, y;
		window.getMousePosition(x, y);

		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();


		const std::vector<Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < rs.size(); i++)
		{
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		if(window.isKeyTyped(GLFW_KEY_P))
			AudioManager::get("loop")->play();
		
		if (window.isKeyTyped(GLFW_KEY_L))
			AudioManager::get("loop")->loop();

		if (window.isKeyTyped(GLFW_KEY_1))
			AudioManager::get("loop")->pause();

		if (window.isKeyTyped(GLFW_KEY_S))
			AudioManager::get("loop")->stop();

		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain += 0.05f;
			AudioManager::get("loop")->setGain(gain);
		}

		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain -= 0.05f;
			AudioManager::get("loop")->setGain(gain);
		}

		window.update();
		AudioManager::update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d FPS\n", frames);
			frames = 0;
		}
	}

	for (int i = 0; i < 3; i++)
		delete textures[i];
	return 0;
}
#endif
