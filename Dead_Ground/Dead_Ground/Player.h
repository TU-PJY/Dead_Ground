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

	GLfloat x = 0.0, y = -0.4;  // 충돌처리를 위한 변수

	GLfloat move_degree = 0;  // 플레이어 이동 방향에 사용되는 각도
	GLfloat move_radian = 0;  // 플레이어 이동 라디안
	GLfloat cam_radian = 0; // 카메라 회전 라디안

	bool is_move = false;  // true 일시 플레이어 움직임

	// 플레이어 충돌 처리 범위
	std::array<GLfloat, 4> bound = { -0.12, 0.12, -0.12, 0.12 };

	// 바운드 박스
	unsigned int bound_box;

public:
	bool hit = false;  // true

	// 플레이어 현재 위치 리턴
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }


	virtual std::array<GLfloat, 4> get_collision_area() const { return bound; }


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


		// bound box
		if (BOUND_BOX == 1) {
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.6, 0.6, 0.0));
			translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));

			draw_image(bound_box, VAO);
		}
	}


	// 플레이어 걷기 애니메이션
	// 걷기를 멈추면 각도를 다시 복구한다
	void animation_walk() {
		if (is_move) {
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


	// 맵 모서리 충돌 처리, 맵 밖으로 벗어날 수 없음
	void check_map_collision() {
		if (x > 4.0 || x < -4.0)
			x += -sin(move_radian + cam_radian) * ft * walk_speed;

		if (y > 4.0 || y < -4.0) 
			y += -cos(move_radian + cam_radian) * ft * walk_speed;
			
	}


	//맵 오브젝트 충돌 처리
	// layer_object 에 존재하는 모든 오브젝트로부터 경계 좌표를 얻어 충돌처리 한다.
	void check_map_object_collision() {
		for (int i = 0; i < framework[layer_map_object].size(); i++) {
			auto ptr = framework[layer_map_object][i];

			if (ptr != nullptr) {
				std::array<GLfloat, 4> b = ptr->get_collision_area();  // get objects's border

				// 오브젝트 중심점을 기준으로 오브젝트로의 어느 방향에 있는지 판단한다
				// 바라보는 방향, 이동 방향, 충돌 방향을 판단하여 충돌처리 한다

				// 바운드 박스 중심점
				GLfloat b_center = b[1] / 2;

				// 기준 방향은 바라보는 방향 (화면 상에서 위쪽)
				// 좌측면
				if (b[2] <= y && y <= b[3] && b[0] < x && x < b[0] + b_center) {
					if (player_move_up && 0 < cam_rotation && cam_rotation < 180)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 180 < cam_rotation && cam_rotation < 360)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 90 < cam_rotation && cam_rotation < 270)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
				}

				// 우측면
				if (b[2] <= y && y <= b[3] && b[1] >= x && x > b[1] - b_center) {
					if (player_move_up && 180 < cam_rotation && cam_rotation < 360)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 0 < cam_rotation && cam_rotation < 180)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 90 < cam_rotation && cam_rotation < 270)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
				}

				//// 아랫면
				if (b[2] <= y && y < b[2] + b_center && b[0] <= x && x <= b[1]) {
					if (player_move_up && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 90 < cam_rotation && cam_rotation < 270)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 180 < cam_rotation && cam_rotation < 360)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 0 < cam_rotation && cam_rotation < 180)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
				}

				// 윗면
				if (b[3] >= y && y > b[3] - b_center && b[0] <= x && x <= b[1]) {
					if (player_move_up && 90 < cam_rotation && cam_rotation < 270)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 0 < cam_rotation && cam_rotation < 180)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 180 < cam_rotation && cam_rotation < 360)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
				}

			}
		}
	}


	void set_move_direction() {
		// 위쪽 방향키 기준
		if (player_move_up && player_move_right && !player_move_left && !player_move_down)
			move_degree = 45;

		else if (player_move_up && player_move_left && !player_move_right && !player_move_down)
			move_degree = -45;

		else if (player_move_up &&
			(!player_move_left && !player_move_right && !player_move_down) ||
			(player_move_left && player_move_right && !player_move_down))
			move_degree = 0;


		// 아래쪽 방향키 기준
		else if (player_move_down && player_move_right && !player_move_left && !player_move_up)
			move_degree = 135;

		else if (player_move_down && player_move_left && !player_move_right && !player_move_up)
			move_degree = -135;

		else if (player_move_down &&
			(!player_move_left && !player_move_right && !player_move_up) ||
			(player_move_left && player_move_right && !player_move_up))
			move_degree = 180;


		// 오른쪽 방향키 기준
		else if (player_move_right && player_move_up && !player_move_down && !player_move_left)
			move_degree = 45;

		else if (player_move_right && player_move_down && !player_move_up && !player_move_left)
			move_degree = 135;

		else if (player_move_right &&
			(!player_move_up && !player_move_down && !player_move_left) ||
			(player_move_up && player_move_down && !player_move_left))
			move_degree= 90;


		// 왼쪽 방향키 기준
		else if (player_move_left && player_move_up && !player_move_down && !player_move_right)
			move_degree = -45;

		else if (player_move_left && player_move_down && !player_move_up && !player_move_right)
			move_degree = -135;

		else if (player_move_left &&
			(!player_move_up && !player_move_down && !player_move_right) ||
			(player_move_up && player_move_down && !player_move_right))
			move_degree = -90;


		move_radian = move_degree * 3.14 / 180;
		cam_radian = cam_rotation * 3.14 / 180;
	}


	// 움직일 수 있는지 확인
	void check_move() {
		is_move = false;

		// 특정 키 조합은 움직임을 활성화하지 않는다
		// is_move가 false인 상태로 리턴하여 플레이어는 움직이지 않는다
		if (!player_move_up && !player_move_right && !player_move_left && !player_move_down)
			return;

		else if (player_move_up && player_move_right && player_move_left && player_move_down)
			return;

		else if ((player_move_right && player_move_left && !player_move_up && !player_move_down) ||
			(player_move_up && player_move_down && !player_move_left && !player_move_right))
			return;

		else {
			x += sin(move_radian + cam_radian) * ft * walk_speed;
			y += cos(move_radian + cam_radian) * ft * walk_speed;

			// 움직일 수 있는 상태라면 true
			is_move = true;
		}
	}


	void check_collision() {
		check_map_object_collision();
		check_map_collision();
	}


	void update() {
		set_move_direction();
		check_move();
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

		if (BOUND_BOX == 1)  // 바운드 박스 활성화 시에만 세팅
			set_bound_box(bound_box);
	}
};