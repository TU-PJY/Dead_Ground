#pragma once
#include "gl_header.h"


class Center : public Framework {
private:
	GLuint VAO;

	int W = 85, H = 85;
	unsigned int tex;
	int channel = 1;
	int layer;

	int hp = 100;

public:
	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		draw_image(tex, VAO);
	}


	void update() {}


	Center(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//object//spr_center.png", W, H, channel);
	}
};
