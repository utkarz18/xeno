#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/Simple2DRenderer.h"
#include "src/graphics/batchRenderer2D.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include <FreeImage.h>
#include "src/graphics/texture.h"
#include "src/graphics/label.h"
#include "src/graphics/font_manager.h"
#include "src/audio/audio_manager.h"

#include "ext/gorilla-audio/ga.h"
#include "ext/gorilla-audio/gau.h"

#if 1
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

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	AudioManager::add(new Audio("test", "test.wav"));
	AudioManager::get("test")->play();

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

#if 0
static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}
int main(int argc, char** argv)
{
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 0;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("test1.wav", "wav");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
}
#endif