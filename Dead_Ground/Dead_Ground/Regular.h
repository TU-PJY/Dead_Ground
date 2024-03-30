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

	// 랜덤으로 이미지 중 하나를 선택하여 텍스처 매핑
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

		result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // 최종 변환

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	
	// 좀비 이동 방향 및 좁비 회전 각도 설정
	void set_move_direction_and_rotation() {
		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			// 플레이어가 근처에 있으면 플레이어를 추격
			if (calc_distance(ptr->get_x(), x, ptr->get_y(), y) < 0.8)
				direction = atan2(ptr->get_y() - y, ptr->get_x() - x);

			// 아니라면 센터로 이동
			else 
				direction = atan2(0.0 - y, 0.0 - x);
		}

		// 이동 방향의 기울기로 오브젝트 회전 각도를 구한다
		rotation = direction * 180 / 3.14;

		// 플레이어 감지 또는 플레이어 추격 해제 시 오브젝트를 회전시킨다.
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
		// 0번에서 5번 이미지 경로 중 하나를 랜덤으로 선택한다
		std::uniform_int_distribution<int> tex_type(0, 5);

		set_canvas(VAO);
		set_texture(tex, directory[tex_type(gen)], W, H, channel);
	}
};