#pragma once
#include "gl_header.h"


class Center : public Framework {
private:
	GLuint VAO{};
	unsigned int tex{};

	int layer{};

	int hp = 1500;


public:
	std::array<GLfloat, 4> get_collision_area() const {return { -0.12, 0.12, -0.12, 0.12 };}


	void render() {
		init_transform();
		scale_matrix *= scale_image(1.5, 1.5);
		translate_matrix *= move_image(0.0, 0.0);

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
