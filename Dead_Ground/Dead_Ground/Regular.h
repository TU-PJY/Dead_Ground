#pragma once
#include "gl_header.h"


class Regular : public Framework {
private:
	GLuint VAO;
	std::array<unsigned int, 3> tex{};

	GLfloat x, y;
	GLfloat direction = 0, rotation = 0;
	GLfloat direction2 = 0, rotation2 = 0;
	GLfloat body_rotation = 0;
	GLfloat speed = 0;

	GLfloat foot_x = 0, foot_y = 0;
	GLfloat num = 0;

	int hp = 100;
	int damage = 10;
	int layer;

	bool hit_player = false;  // �浹 ó��
	bool hit_center = false;  // �浹 ó��
	bool track_player = false; // �÷��̾� �߰� ����

	// �������� �̹��� �� �ϳ��� �����Ͽ� �ؽ�ó ����
	std::array<const char*, 6> directory = {
		"res//monster//regular//spr_zombie_0.png",
		"res//monster//regular//spr_zombie_1.png",
		"res//monster//regular//spr_zombie_2.png",
		"res//monster//regular//spr_zombie_3.png",
		"res//monster//regular//spr_zombie_4.png",
		"res//monster//regular//spr_zombie_5.png",
	};

public:
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }

	void render() {
		using namespace glm;

		// left foot
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0)); 
		translate_matrix = rotate(translate_matrix, radians(rotation2 + 90), vec3(0.0, 0.0, 1.0)); 
		translate_matrix = translate(translate_matrix, vec3(-0.02, -0.03 + foot_y, 0.0)); 

		draw_image(tex[0], VAO);


		// right foot
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
		translate_matrix = rotate(translate_matrix, radians(rotation2 + 90), vec3(0.0, 0.0, 1.0));
		translate_matrix = translate(translate_matrix, vec3(0.02, -0.03 - foot_y, 0.0)); 

		draw_image(tex[1], VAO);


		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
		translate_matrix = rotate(translate_matrix, radians(rotation2 + body_rotation), vec3(0.0, 0.0, 1.0));

		draw_image(tex[2], VAO);
	}

	
	// ���� �̵� ���� �� ���� ȸ�� ���� ����
	void set_move_direction_and_rotation() {
		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			// �÷��̾ ��ó�� ������ �÷��̾ �߰�
			if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.8) {
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


	void check_collision() {
		auto ptr = framework[layer_player][0];

		// �÷��̾�� ������ �÷��̾�� ������� ����
		// ������� ������ ���ȿ��� �������� ����
		if (track_player && !hit_center) {
			if (ptr != nullptr) {
				if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.1)
					hit_player = true;
				else
					hit_player = false;
			}
		}

		else {  // �� �� ���͸� �����ϱ� �����ϸ� ��� ���͸� �����Ѵ�
			if (calc_distance(0.0, x, 0.0, y) < 0.15)
				hit_center = true;
		}
	}


	void animation_walk() {
		if (!hit_center && !hit_player) {
			num += ft * speed * 10;
			body_rotation = -sin(num) * 10;
			foot_y = sin(num) / 20;
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
		if (!hit_player && !hit_center) {
			x += cos(direction) * ft * speed;
			y += sin(direction) * ft * speed;
		}
	}


	void update() {
		if(!hit_center)
			set_move_direction_and_rotation();
		animation_walk();
		move();
		check_collision();
	}


	Regular(GLfloat rand_x, GLfloat rand_y, GLfloat rand_speed, int l) {
		x = rand_x;
		y = rand_y;
		speed = rand_speed;
		layer = l;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> tex_type(0, 5);

		set_canvas(VAO);
		set_texture(tex[0], "res//monster//spr_zombie_foot_left.png", 18, 18, 1);
		set_texture(tex[1], "res//monster//spr_zombie_foot_right.png", 18, 18, 1);
		// 0������ 5�� �̹��� ��� �� �ϳ��� �������� �����Ѵ�
		set_texture(tex[2], directory[tex_type(gen)], 47, 47, 1);
	}
};