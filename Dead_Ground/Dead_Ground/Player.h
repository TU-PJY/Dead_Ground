// 플레이어 클래스
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLuint VAO;
	std::array<unsigned int, 3> tex{};
	int layer;  // framework layer number

	GLfloat walk_speed = 0.75;
	GLfloat num = 0;
	GLfloat rotation = 0;

	GLfloat foot_y = 0;

	GLfloat x = 0.0, y = -0.2;  // 충돌처리를 위한 변수

public:
	void render() {
		using namespace glm;

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


		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation + rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다

		draw_image(tex[2], VAO);
	}


	// 플레이어 걷기 애니메이션
	// 걷기를 멈추면 각도를 다시 복구한다
	void animation_walk() {
		if (player_move_up || player_move_down || player_move_right || player_move_left) {
			num += ft * walk_speed * 10;
			rotation = -sin(num) * 10;
			foot_y = sin(num) / 20;
		}

		else {
			num = 0;
			if (rotation > 0) {
				rotation -= ft * 30;
				if (rotation < 0)
					rotation = 0;
			}
			else if (rotation < 0) {
				rotation += ft * 30;
				if (rotation > 0)
					rotation = 0;
			}


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
		}
	}


	void move() {
		GLfloat degree = cam_rotation * 3.14 / 180;
		GLfloat degree_vertical = (cam_rotation + 90) * 3.14 / 180;

		// 플레이어 이동
		if (player_move_up) {
			if (player_move_right || player_move_left) {
				x += walk_speed * ft * sin(degree) / 1.414;
				y += walk_speed * ft * cos(degree) / 1.414;
			}
			else {
				x += walk_speed * ft * sin(degree);
				y += walk_speed * ft * cos(degree);
			}
		}

		if (player_move_down) {
			if (player_move_right || player_move_left) {
				x -= walk_speed * ft * sin(degree) / 1.414;
				y -= walk_speed * ft * cos(degree) / 1.414;
			}
			else {
				x -= walk_speed * ft * sin(degree);
				y -= walk_speed * ft * cos(degree);
			}
		}

		if (player_move_right) {
			if (player_move_up || player_move_down) {
				x += walk_speed * ft * sin(degree_vertical) / 1.414;
				y += walk_speed * ft * cos(degree_vertical) / 1.414;
			}
			else {
				x += walk_speed * ft * sin(degree_vertical);
				y += walk_speed * ft * cos(degree_vertical);
			}
		}

		if (player_move_left) {
			if (player_move_up || player_move_down) {
				x -= walk_speed * ft * sin(degree_vertical) / 1.414;
				y -= walk_speed * ft * cos(degree_vertical) / 1.414;
			}
			else {
				x -= walk_speed * ft * sin(degree_vertical);
				y -= walk_speed * ft * cos(degree_vertical);
			}
		}
	}


	// 플레이어 현재 위치 리턴
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }

	void update() {
		move();
		animation_walk();
	}


	Player(int l) {
		layer = l;

		player_move_up = false;
		player_move_down = false;
		player_move_right = false;
		player_move_left = false;

		set_canvas(VAO);
		set_texture(tex[0], "res//player//spr_foot_left.png", 18, 18, 1);
		set_texture(tex[1], "res//player//spr_foot_right.png", 18, 18, 1);
		set_texture(tex[2], "res//player//spr_player_0.png", 56, 56, 1);
	}
};