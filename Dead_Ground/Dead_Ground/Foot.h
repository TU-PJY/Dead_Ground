#pragma once
#include "gl_header.h"


class Foot : public Framework{
private:
	std::array<unsigned int, 2> tex{};
	GLuint VAO{};

	// 발 위치를 나타내기 위한 변수
	GLfloat num{}, foot_y{};
	std::string tag{};
	int layer{}, index{};

	Framework* p{};


public:
	void render() {
		if (tag == "monster") {
			auto ptr = fw_set_tracking(layer_monster, index);

			if (ptr != nullptr) {
				GLfloat x = ptr->get_x();
				GLfloat y = ptr->get_y();
				GLfloat rotation = ptr->get_rotation();

				// left foot
				init_transform();
				scale_matrix *= scale_image(0.3, 0.3);
				translate_matrix *= move_image(x, y);
				translate_matrix *= rotate_image(rotation + 90);
				translate_matrix *= move_image(-0.02, -0.03 + foot_y);

				draw_image(tex[0], VAO);


				// right foot
				init_transform();
				scale_matrix *= scale_image(0.3, 0.3);
				translate_matrix *= move_image(x, y);
				translate_matrix *= rotate_image (rotation + 90);
				translate_matrix *= move_image(0.02, -0.03 - foot_y);

				draw_image(tex[1], VAO);
			}
		}

		else if (tag == "player") {
			auto ptr = fw_set_tracking(layer_player, 0);

			if (ptr != nullptr) {
				GLfloat x = ptr->get_x();
				GLfloat y = ptr->get_y();

				// left foot
				init_transform();
				scale_matrix *= scale_image(0.3, 0.3);
				translate_matrix *= move_image(x, y); 
				translate_matrix *= rotate_image(-cam_rotation);  
				translate_matrix *= move_image(-0.02, -0.03 + foot_y);

				draw_image(tex[0], VAO);


				// right foot
				init_transform();
				scale_matrix *= scale_image(0.3, 0.3);
				translate_matrix *= move_image(x, y);
				translate_matrix *= rotate_image(-cam_rotation);
				translate_matrix *= move_image(0.02, -0.03 - foot_y);

				draw_image(tex[1], VAO);
			}
		}
	}

	void update() {
		if (tag == "monster") {
			if (fw_check_tracking_valid(layer_monster, index))
				p = fw_set_tracking(layer_monster, index);
			else
				fw_delete(this, layer);
		}

		else if (tag == "player") {
			if (fw_check_tracking_valid(layer_player, 0))
				p = fw_set_tracking(layer_player, 0);
			else
				fw_delete(this, layer);
		}

		if (p != nullptr) {
			// 걸을 때는 발이 움직인다.
			if (p->get_move_state()) {
				num += ft * p->get_speed() * 10;
				foot_y = sin(num) / 20;
			}

			// 걷기를 멈추면 발이 다시 원래 위치로 돌아온다
			else {
				if (foot_y > 0) {
					foot_y -= ft / 2;
					if (foot_y < 0)
						foot_y = 0;
				}

				else if (foot_y < 0) {
					foot_y += ft / 2;
					if (foot_y > 0)
						foot_y = 0;
				}

				num = 0;
			}
		}
	}

	void check_collision() {}


	Foot(int l, int i, std::string str) {
		layer = l;
		index = i;

		tag = str;

		set_canvas(VAO);
		
		if (tag == "monster") {
			set_texture(tex[0], "res//monster//spr_zombie_foot_left.png", 18, 18, 1);
			set_texture(tex[1], "res//monster//spr_zombie_foot_right.png", 18, 18, 1);
		}
		else if (tag == "player") {
			set_texture(tex[0], "res//player//spr_foot_left.png", 18, 18, 1);
			set_texture(tex[1], "res//player//spr_foot_right.png", 18, 18, 1);
		}
	}
};