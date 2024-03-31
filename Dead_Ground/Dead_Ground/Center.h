#pragma once
#include "gl_header.h"


class Center : public Framework {
private:
	GLuint VAO;
	unsigned int tex;

	int layer;

	int hp = 100;


public:
	std::array<GLfloat, 4> get_collision_area() const {return { -0.12, 0.12, -0.12, 0.12 };}


	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		draw_image(tex, VAO);
	}


	void check_collision() {}


	void update() {}


	Center(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//object//spr_center.png", 85, 85, 1);
	}
};
