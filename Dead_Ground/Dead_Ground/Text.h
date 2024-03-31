#pragma once
#include "gl_header.h"


class Text : public Framework {
private:
	GLuint VAO;
	int W = 10, H = 10;
	unsigned int tex;
	int channel = 1;

	int layer;

public:
	void render() {
		using namespace glm;
		init_transform();
		//translate_matrix = translate(translate_matrix, vec3(cam_x, cam_y, 0.0));
		//translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));
		//translate_matrix = translate(translate_matrix, vec3(-1.7, -0.5, 0.0));

		draw_text((void*)font, (char*)"Dead Ground Indev", tex, VAO);
	}


	void update() {}


	Text(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//ui//text//text_skin.png", W, H, channel);
	}
};