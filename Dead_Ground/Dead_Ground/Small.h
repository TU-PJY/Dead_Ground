#pragma once
#include "gl_header.h"


class Small : public Framework {
private:
	GLuint VAO{};
	unsigned int tex{};
	int layer{};

	GLfloat x{}, y{};
	GLfloat direction{}, rotation{};
	GLfloat direction2{}, rotation2{};
	GLfloat body_rotation{};
	GLfloat speed{};

	GLfloat num{};

	int hp = 150;
	int damage = 45;

	bool hit_player{};  // 충돌 처리
	bool hit_center{};
	bool track_player{};  // 플레이어 추격 여부
	bool is_move{};

	// 랜덤으로 이미지 중 하나를 선택하여 텍스처 매핑
	std::array<const char*, 7> directory = {
		"res//monster//small//spr_zombie_0.png",
		"res//monster//small//spr_zombie_1.png",
		"res//monster//small//spr_zombie_2.png",
		"res//monster//small//spr_zombie_3.png",
		"res//monster//small//spr_zombie_4.png",
		"res//monster//small//spr_zombie_5.png",
		"res//monster//small//spr_zombie_6.png",
	};


public:
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }
	GLfloat get_rotation() const { return rotation2; }
	GLfloat get_speed() const { return speed; }
	bool get_move_state() const { return is_move; }


	void render() {
		using namespace glm;

		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
		translate_matrix = rotate(translate_matrix, radians(rotation2 + body_rotation), vec3(0.0, 0.0, 1.0));

		draw_image(tex, VAO);
	}


	// 좀비 이동 방향 및 좁비 회전 각도 설정
	void set_move_direction_and_rotation() {
		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			// 플레이어가 근처에 있으면 플레이어를 추격
			if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.9) {
				direction = atan2(ptr->get_y() - y, ptr->get_x() - x);
				track_player = true;
			}

			// 아니라면 센터로 이동
			else {
				direction = atan2(0.0 - y, 0.0 - x);
				track_player = false;
			}
		}

		// 이동 방향의 기울기로 오브젝트 회전 각도를 구한다
		rotation = direction * 180 / 3.14;

		// 플레이어 감지 또는 플레이어 추격 해제 시 오브젝트를 회전시킨다.
		if (rotation2 != rotation) {
			GLfloat min_rotation_distance = calc_min_rotation(rotation2, rotation);

			if (min_rotation_distance < -180.0f)
				rotation2 += ft * 250;
			else if (min_rotation_distance > 180.0f)
				rotation2 -= ft * 250;

			else {
				if (min_rotation_distance < 0)
					rotation2 += ft * 250;
				else
					rotation2 -= ft * 250;
			}
		}

		rotation2 = normalize_angle(rotation2);

		direction = (rotation2 - 180) * 3.14 / 180;
	}


	void check_monster_collision() {
		auto ptr = fw_set_tracking(layer_player, 0);

		// 플레이어와 닿으면 플레이어에게 대미지를 입힘
		// 대미지를 입히는 동안에는 움직이지 않음
		if (track_player && !hit_center) {
			if (ptr != nullptr) {
				if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.12) {
					hit_player = true;
					ptr->give_damage(damage);  // 플레이어에게 25대미지를 준다
				}
				else 
					hit_player = false;
			}
		}

		else {  // 한 번 센터를 공격하기 시작하면 계속 센터만 공격한다
			if (calc_distance(0.0, x, 0.0, y) < 0.15)
				hit_center = true;
		}
	}


	void set_move_state() {
		if (!hit_player && !hit_center)
			is_move = true;
		else
			is_move = false;
	}


	void animation_walk() {
		if (!hit_center && !hit_player) {
			num += ft * speed * 10;
			body_rotation = -sin(num) * 10;
		}

		else {
			num = 0;

			if (body_rotation > 0) {
				body_rotation -= ft * 30;
				if (body_rotation < 0)
					body_rotation = 0;
			}
			else if (body_rotation < 0) {
				body_rotation += ft * 30;
				if (body_rotation > 0)
					body_rotation = 0;
			}
		}
	}


	void move() {
		if (!hit_player && !hit_center) {
			x += cos(direction) * ft * speed;
			y += sin(direction) * ft * speed;
		}
	}


	void check_collision() {
		check_monster_collision();
	}


	void update() {
		if (!hit_center)
			set_move_direction_and_rotation();

		set_move_state();

		animation_walk();
		move();

		if (hp < 0) {
			fw_delete(this, layer);
		}
	}


	Small (GLfloat rand_x, GLfloat rand_y, GLfloat rand_speed, int l) {
		x = rand_x;
		y = rand_y;
		speed = rand_speed;
		layer = l;

		std::random_device rd;
		std::mt19937 gen(rd());
		
		std::uniform_int_distribution<int> tex_type(0, 6);

		set_canvas(VAO);
		// 0번에서 6번 이미지 경로 중 하나를 랜덤으로 선택한다
		set_texture(tex, directory[tex_type(gen)], 47, 47, 1);
	}
};