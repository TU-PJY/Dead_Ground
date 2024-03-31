#pragma once
#include "gl_header.h"


class Compass : public Framework {
private:
	GLuint VAO;
	std::array<unsigned int, 3> tex{};
	
	GLfloat rotation = 0;

	int layer;

public:
	void render() {
		using namespace glm;

		// 나침반 몸체
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(2.0, 2.0, 0.0));
		set_object_static(1.0 * ratio - 0.3, -0.3);
		translate_matrix = rotate(translate_matrix, radians(cam_rotation), vec3(0.0, 0.0, 1.0));

		draw_image(tex[0], VAO);


		// 나침반 침
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(2.0, 2.0, 0.0));
		set_object_static(1.0 * ratio - 0.3, -0.3);

		draw_image(tex[1], VAO);


		// 센터 인디케이터
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(0.4, 0.4, 0.0));
		set_object_static(1.0 * ratio - 0.3, -0.3);
		translate_matrix = rotate(translate_matrix, radians(cam_rotation + rotation), vec3(0.0, 0.0, 1.0));
		translate_matrix = translate(translate_matrix, vec3(-0.23, -0.0, 0.0));
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation - rotation), vec3(0.0, 0.0, 1.0));

		draw_image(tex[2], VAO);
	}


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