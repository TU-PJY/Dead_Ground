#pragma once
#include "gl_header.h"


class Health : public Framework {
private:
	GLuint VAO{};
	std::array<unsigned int, 3> tex{};

	int layer;

public:
	void render() {
		using namespace glm;

		// 배경
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 1.5));
		set_object_static(-1.0 * ratio + 0.75, -0.4);
		draw_image(tex[0], VAO);

		// 체력 표시
		auto ptr = framework[layer_player][0];
		if (ptr != nullptr) {
			int hp = ptr->get_hp();
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(1.5, (1.5 * hp / 500), 1.5));
			set_object_static(-1.0 * ratio + 0.75, -0.4);
			draw_image(tex[1], VAO);
		}

		// 프레임
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 1.5));
		set_object_static(-1.0 * ratio + 0.75, -0.4);
		draw_image(tex[2], VAO);
	}


	void check_collision() {}


	void update() {}


	Health(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex[0], "res//ui//health//spr_ui_health_bottom.png", 91, 91, 1);
		set_texture(tex[1], "res//ui//health//spr_ui_health_middle.png", 91, 91, 1);
		set_texture(tex[2], "res//ui//health//spr_ui_health_top.png", 91, 91, 1);
	}
};