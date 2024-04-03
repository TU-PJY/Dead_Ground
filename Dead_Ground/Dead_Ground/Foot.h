#pragma once
#include "gl_header.h"


class Foot : public Framework{
private:
	std::array<unsigned int, 2> tex{};
	GLuint VAO;

	// 발 위치를 나타내기 위한 변수
	GLfloat num = 0, foot_y = 0;
	std::string tag;
	int layer, index;

	Framework* p;


public:
	void render() {
		using namespace glm;

		if (tag == "monster") {
			auto ptr = framework[layer_monster][index];

			if (ptr != nullptr) {
				GLfloat x = ptr->get_x();
				GLfloat y = ptr->get_y();
				GLfloat rotation = ptr->get_rotation();

				// left foot
				init_transform();
				scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
				translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
				translate_matrix = rotate(translate_matrix, radians(rotation + 90), vec3(0.0, 0.0, 1.0));
				translate_matrix = translate(translate_matrix, vec3(-0.02, -0.03 + foot_y, 0.0));

				draw_image(tex[0], VAO);


				// right foot
				init_transform();
				scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
				translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
				translate_matrix = rotate(translate_matrix, radians(rotation + 90), vec3(0.0, 0.0, 1.0));
				translate_matrix = translate(translate_matrix, vec3(0.02, -0.03 - foot_y, 0.0));

				draw_image(tex[1], VAO);
			}
		}

		else if (tag == "player") {
			auto ptr = framework[layer_player][0];

			if (ptr != nullptr) {
				GLfloat x = ptr->get_x();
				GLfloat y = ptr->get_y();

				// left foot
				init_transform();
				scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
				translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
				translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다
				translate_matrix = translate(translate_matrix, vec3(-0.02, -0.03 + foot_y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다

				draw_image(tex[0], VAO);


				// right foot
				init_transform();
				scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
				translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
				translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다
				translate_matrix = translate(translate_matrix, vec3(0.02, -0.03 - foot_y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다

				draw_image(tex[1], VAO);
			}
		}
	}

	void update() {
		if (tag == "monster") {
			if (index >= framework[layer_monster].size())
				fw_delete(this, layer);
			else
				p = framework[layer_monster][index];
		}

		else if (tag == "player") {
			if (index >= framework[layer_player].size())
				fw_delete(this, layer);
			else
				p = framework[layer_player][index];
		}


		if (p != nullptr) {
			// 걸을 때는 발이 움직인다.
			if (p->get_state()) {
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