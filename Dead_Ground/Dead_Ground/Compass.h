#pragma once
#include "gl_header.h"


class Compass : public Framework {
private:
	GLuint VAO{};
	std::array<unsigned int, 3> tex{};
	
	GLfloat rotation{};

	int layer{};

public:
	void render() {
		// 나침반 몸체
		init_transform();
		s_mat *= scale_image(2.0, 2.0);
		fix_image_at(rectR - 0.3, -0.3);
		t_mat *= rotate_image(cam_rotation);

		draw_image(tex[0], VAO);


		// 나침반 침
		init_transform();
		s_mat *= scale_image(2.0, 2.0);
		fix_image_at(rectR - 0.3, -0.3);

		draw_image(tex[1], VAO);


		// 센터 인디케이터
		init_transform();
		s_mat *= scale_image(0.4, 0.4);
		fix_image_at(rectR - 0.3, -0.3);
		t_mat *= rotate_image(cam_rotation + rotation);
		t_mat *= move_image(-0.23, -0.0);
		t_mat *= rotate_image(-cam_rotation - rotation);

		draw_image(tex[2], VAO);
	}


	void check_collision() {}


	void update() {
		rotation = atan2(-cam_y, -cam_x) * 180 / 3.14 + 180;
	}


	Compass(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex[0], "res//ui//compass//spr_ui_compass_0.png", 89, 89, 1);
		set_texture(tex[1], "res//ui//compass//spr_ui_compass_1.png", 89, 89, 1);
		set_texture(tex[2], "res//ui//compass////spr_center_icon.png", 85, 85, 1);
	}
};