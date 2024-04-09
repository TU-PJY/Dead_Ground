#pragma once
#include "gl_header.h"


class Ground : public Framework {
private:
	GLuint VAO{};
	unsigned int tex{};

	int layer{};

public:

	void render() {
		using namespace glm;

		init_transform();
		s_mat = scale(s_mat, vec3(map_size, map_size, 0.0));
		t_mat = translate(t_mat, vec3(0.0, 0.0, 0.0));

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
	unsigned int tex{};

	int layer{};


public:

	void render() {
		init_transform();
		s_mat *= scale_image(5.0, 5.0);
		t_mat *= move_image(0.0, 0.0);

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