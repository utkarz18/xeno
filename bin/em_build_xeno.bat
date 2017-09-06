emcc -std=c++11 -I"../Dependencies/Freeimage/include" "../Xeno-core/src/graphics/buffers/buffer.cpp" "../Xeno-core/src/graphics/buffers/indexbuffer.cpp" "../Xeno-core/src/graphics/buffers/vertexarray.cpp" "../Xeno-core/src/graphics/layers/group.cpp" "../Xeno-core/src/graphics/layers/layer.cpp" "../Xeno-core/src/graphics/label.cpp" "../Xeno-core/src/graphics/sprite.cpp" "../Xeno-core/src/graphics/BatchRenderer2D.cpp" "../Xeno-core/src/graphics/font.cpp" "../Xeno-core/src/graphics/font_manager.cpp" "../Xeno-core/src/graphics/shader.cpp" "../Xeno-core/src/graphics/texture.cpp" "../Xeno-core/src/graphics/window.cpp" "../Xeno-core/src/maths/mat4.cpp" "../Xeno-core/src/maths/vec2.cpp" "../Xeno-core/src/maths/vec3.cpp" "../Xeno-core/src/maths/vec4.cpp" "../Xeno-core/examples/game.cpp" "../Xeno-core/src/audio/audio.cpp" "../Xeno-core/src/audio/audio_manager.cpp" freetype.bc freeimage.bc -s USE_GLFW=3 -s FULL_ES3=1 -DXENO_PLATFORM_WEB=1 --memory-init-file 0 --embed-file res -O3 -o Web\xeno.html