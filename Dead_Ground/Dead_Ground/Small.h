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

	bool hit_player{};  // �浹 ó��
	bool hit_center{};
	bool track_player{};  // �÷��̾� �߰� ����
	bool is_move{};

	// �������� �̹��� �� �ϳ��� �����Ͽ� �ؽ�ó ����
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


	// ���� �̵� ���� �� ���� ȸ�� ���� ����
	void set_move_direction_and_rotation() {
		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			// �÷��̾ ��ó�� ������ �÷��̾ �߰�
			if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.9) {
				direction = atan2(ptr->get_y() - y, ptr->get_x() - x);
				track_player = true;
			}

			// �ƴ϶�� ���ͷ� �̵�
			else {
				direction = atan2(0.0 - y, 0.0 - x);
				track_player = false;
			}
		}

		// �̵� ������ ����� ������Ʈ ȸ�� ������ ���Ѵ�
		rotation = direction * 180 / 3.14;

		// �÷��̾� ���� �Ǵ� �÷��̾� �߰� ���� �� ������Ʈ�� ȸ����Ų��.
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

		// �÷��̾�� ������ �÷��̾�� ������� ����
		// ������� ������ ���ȿ��� �������� ����
		if (track_player && !hit_center) {
			if (ptr != nullptr) {
				if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.12) {
					hit_player = true;
					ptr->give_damage(damage);  // �÷��̾�� 25������� �ش�
				}
				else 
					hit_player = false;
			}
		}

		else {  // �� �� ���͸� �����ϱ� �����ϸ� ��� ���͸� �����Ѵ�
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
		// 0������ 6�� �̹��� ��� �� �ϳ��� �������� �����Ѵ�
		set_texture(tex, directory[tex_type(gen)], 47, 47, 1);
	}
};