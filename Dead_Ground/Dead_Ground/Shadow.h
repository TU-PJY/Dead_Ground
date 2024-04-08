#pragma once
#include "gl_header.h"


class Shadow : public Framework {
private:
	GLuint VAO{};
	unsigned int tex{};
	int layer{}, index{};
	std::string tag{};  // 태그에 따라 몬스터 또는 플레이어의 위치를 추적하여 그림자가 출력된다

public:
	void render() {
		if (tag == "monster") {
			auto ptr = fw_set_tracking(layer_monster, index);
			if (ptr != nullptr) {
				init_transform();
				translate_matrix *= move_image(ptr->get_x(), ptr->get_y());
				translate_matrix *= rotate_image(ptr->get_rotation());
				transparent = 0.2f;

				draw_image(tex, VAO);
			}
		}

		else if (tag == "player") {
			auto ptr = fw_set_tracking(layer_player, 0);
			if (ptr != nullptr) {
				init_transform();
				translate_matrix *= move_image(ptr->get_x(), ptr->get_y());
				translate_matrix *= rotate_image(-cam_rotation - 90);
				transparent = 0.2f;

				draw_image(tex, VAO);
			}
		}
	}


	void check_collision() {}


	void update() {
		if (tag == "monster") {
			if(!fw_check_tracking_valid(layer_monster, index))
				fw_delete(this, layer_entity);
		}

		else if (tag == "player") {
			if (!fw_check_tracking_valid(layer_player, 0))
				fw_delete(this, layer_entity);
		}
	}


	Shadow(int l, int i, std::string str) {
		layer = l;
		index = i;
		tag = str;

		set_canvas(VAO);
		set_texture(tex, "res//object//spr_shadow_mob.png", 47, 47, 1);
	}
};