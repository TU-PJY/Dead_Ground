// 플레이어 클래스
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLfloat walk_speed = 0.75;
	GLfloat x = 0.0, y = -0.4;  // 충돌처리를 위한 변수

	GLfloat max_hp = 500;
	GLfloat hp = max_hp;  // 플레이어 hp

	GLfloat damage = 0;  // 플레이어가 받는 대미지
	GLfloat damage_delay = 0;  // 대미지 받기 딜레이

	GLfloat recovery_delay = 0;  // 체력 회복 딜레이

	bool is_move = false;  // true 일시 플레이어 움직임

	GLfloat num = 0;
	GLfloat rotation = 0;

	GLfloat move_degree = 0;  // 플레이어 이동 방향에 사용되는 각도
	GLfloat move_radian = 0;  // 플레이어 이동 라디안
	GLfloat cam_radian = 0; // 카메라 회전 라디안

	bool player_move_up = false;
	bool player_move_down = false;
	bool player_move_right = false;
	bool player_move_left = false;

	// 플레이어 충돌 처리 범위
	std::array<GLfloat, 4> bound = { -0.12, 0.12, -0.12, 0.12 };

	// 바운드 박스
	unsigned int bound_box;

	GLuint VAO;
	unsigned int tex;
	int layer;  // framework layer number


public:
	void update_index(int idx) {}

	// 플레이어 현재 위치 리턴
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }

	// 플레이어 체력 리턴
	GLfloat get_hp() const { return hp; }

	// 플레이어 이동 속도 리턴
	GLfloat get_speed() const { return walk_speed; }

	// 플레이어 이동 상태 리턴
	bool get_state() const { return is_move; }

	// 플레이어 이동 상태 설정
	void set_state(int opt) {
		switch (opt) {
		case 0:
			player_move_up = true;  break;
		case 1:
			player_move_down = true;  break;
		case 2:
			player_move_right = true;  break;
		case 3:
			player_move_left = true;  break;

		case 4:
			player_move_up = false;  break;
		case 5:
			player_move_down = false;  break;
		case 6:
			player_move_right = false;  break;
		case 7:
			player_move_left = false;  break;
		}
	}


	std::array<GLfloat, 4> get_collision_area() const { return bound; }


	void render() {
		using namespace glm;

		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation + rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다

		draw_image(tex, VAO);


		// bound box
		if (BOUND_BOX == 1) {
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.6, 0.6, 0.0));
			translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));

			draw_image(bound_box, VAO);
		}
	}


	void animation_walk() {
		if (is_move) {
			num += ft * walk_speed * 10;
			rotation = -sin(num) * 10;
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
		}
	}


	// 플레이어에게 대미지를 부여한다
	void give_damage(GLfloat damage) {
		if (damage > 0 && damage_delay == 0) {
			hp -= damage;
			damage_delay = 10;
			damage = 0;
		}
	}


	// 일정 시간 마다 대미지를 받을 수 있도록 대미지 딜레이 업데이트
	void update_damage_delay() {
		if (damage_delay > 0) {
			damage_delay -= ft * 10;
			if (damage_delay < 0)
				damage_delay = 0;
		}
	}


	// 플레이어 체력 회복
	void recover_hp() {
		if (recovery_delay > 0) {
			recovery_delay -= ft * 5;
			if (recovery_delay < 0)
				recovery_delay = 0;
		}

		// 일정 간격 마다 체력을 회복한다
		if (hp < max_hp && recovery_delay == 0) {
			hp += 10;

			if (hp > max_hp)
				hp = max_hp;
			else
			 recovery_delay = 10;
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
		for (int i = 0; i < framework[layer_map_object].size(); ++i) {
			auto ptr = framework[layer_map_object][i];

			if (ptr != nullptr) {
				// 오브젝트가 return하는 바운드 범위를 가져온다
				std::array<GLfloat, 4> b = ptr->get_collision_area(); 

				// 오브젝트 중심점을 기준으로 오브젝트로의 어느 방향에 있는지 판단한다
				// 바라보는 방향, 이동 방향, 충돌 방향을 판단하여 충돌처리 한다

				// 바운드 박스 중심점
				GLfloat b_center = b[1] / 2;

				// 기준 방향은 바라보는 방향 (화면 상에서 위쪽)
				// 좌측면
				if (b[2] <= y && y <= b[3] && b[0] < x && x < b[0] + b_center) {
					if ((player_move_right && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_down && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_left && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_up && 0 < cam_rotation && cam_rotation < 180)) {
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				// 우측면
				if (b[2] <= y && y <= b[3] && b[1] >= x && x > b[1] - b_center) {
					if ((player_move_left && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_right && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_up && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_down && 0 < cam_rotation && cam_rotation < 180)) {
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				//// 아랫면
				if (b[2] <= y && y < b[2] + b_center && b[0] <= x && x <= b[1]) {
					if ((player_move_up && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_right && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_down && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_left && 0 < cam_rotation && cam_rotation < 180)) {
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				// 윗면
				if (b[3] >= y && y > b[3] - b_center && b[0] <= x && x <= b[1]) {
					if ((player_move_down && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_left && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_right && 0 < cam_rotation && cam_rotation < 180) ||
						(player_move_up && 90 < cam_rotation && cam_rotation < 270)) {
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
					}
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

		// 최종 방향 라디안 계산
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
		update_damage_delay();
		recover_hp();
		animation_walk();

		set_move_direction();
		check_move();

		for (int i = 0; i < framework[layer_monster].size(); ++i) {
			auto ptr = framework[layer_monster][i];
			if (ptr != nullptr) {
				if (calc_distance(x, ptr->get_x(), y, ptr->get_y()) < 0.1) {
					fw_delete(ptr, layer_monster);
				}
					
			}
		}
	}


	Player(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//player//spr_player_0.png", 56, 56, 1);

		if (BOUND_BOX == 1)  // 바운드 박스 활성화 시에만 세팅
			set_bound_box(bound_box);
	}
};