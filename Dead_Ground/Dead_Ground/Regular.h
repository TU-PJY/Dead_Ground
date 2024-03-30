#pragma once
#include "gl_header.h"


class Regular : public Framework {
private:
	GLuint VAO;
	int W = 47, H = 47;
	unsigned int tex;
	int channel = 1;

	GLfloat x, y;
	GLfloat direction = 0, rotation = 0;
	GLfloat direction2 = 0, rotation2 = 0;
	GLfloat speed = 0;

	int hp = 100;
	int damage = 10;
	int layer;

	// �������� �̹��� �� �ϳ��� �����Ͽ� �ؽ�ó ����
	const char* directory[6] = {
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


	void translate_image() {
		using namespace glm;

		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
		translate_matrix = rotate(translate_matrix, radians(rotation2), vec3(0.0, 0.0, 1.0)); 

		result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // ���� ��ȯ

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	
	// ���� �̵� ���� �� ���� ȸ�� ���� ����
	void set_move_direction_and_rotation() {
		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			// �÷��̾ ��ó�� ������ �÷��̾ �߰�
			if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.8)
				direction = atan2(ptr->get_y() - y, ptr->get_x() - x);

			// �ƴ϶�� ���ͷ� �̵�
			else 
				direction = atan2(0.0 - y, 0.0 - x);
		}

		// �̵� ������ ����� ������Ʈ ȸ�� ������ ���Ѵ�
		rotation = direction * 180 / 3.14;

		// �÷��̾� ���� �Ǵ� �÷��̾� �߰� ���� �� ������Ʈ�� ȸ����Ų��.
		if (rotation2 != rotation) {
			GLfloat min_rotation_distance = calc_min_rotation(rotation2, rotation);

			if (min_rotation_distance < -180.0f) 
				rotation2 += ft * 150;
			else if (min_rotation_distance > 180.0f) 
				rotation2 -= ft * 150;
			
			else {
				if (min_rotation_distance < 0) 
					rotation2 += ft * 150;
				else 
					rotation2 -= ft * 150;
			}
		}

		rotation2 = normalizeAngle(rotation2);
	}


	void move() {
		x += cos(direction) * ft * speed;
		y += sin(direction) * ft * speed;
	}


	void update() {
		set_move_direction_and_rotation();
		move();
	}


	Regular(GLfloat rand_x, GLfloat rand_y, GLfloat rand_speed, int l) {
		x = rand_x;
		y = rand_y;
		speed = rand_speed;
		layer = l;

		std::random_device rd;
		std::mt19937 gen(rd());
		// 0������ 5�� �̹��� ��� �� �ϳ��� �������� �����Ѵ�
		std::uniform_int_distribution<int> tex_type(0, 5);

		set_canvas(VAO);
		set_texture(tex, directory[tex_type(gen)], W, H, channel);
	}
};