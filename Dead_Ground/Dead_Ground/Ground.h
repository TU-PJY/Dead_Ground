#pragma once
#include "gl_header.h"


class Ground : public Framework {
private:
	GLuint VAO;
	unsigned int tex;

	int layer;

public:
	void update_index(int idx) {}

	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(map_size, map_size, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		draw_image(tex, VAO);
	}

	void update() {}

	Ground(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//map//spr_ground.png", 1500, 1500, 1);
	}
};


class CenterGround : public Framework {
private:
	GLuint VAO;

	int W = 1500, H = 1500;
	unsigned int tex;
	int channel = 1;

	int layer;


public:
	void update_index(int idx) {}

	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(5.0, 5.0, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		draw_image(tex, VAO);
	}


	void check_collision() {}


	void update() {}


	CenterGround(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//map//spr_center_ground.png", 1500, 1500, 1);
	}
};