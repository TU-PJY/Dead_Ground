// �÷��̾� Ŭ����
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLuint VAO;

	int W = 56, H = 56;  // image size
	unsigned int tex;
	int channel = 1;
	int layer;  // framework layer number

	GLfloat walk_speed = 0.75;
	GLfloat num = 0;
	GLfloat rotation = 0;

	GLfloat x = 0.0, y = -0.2;  // �浹ó���� ���� ����

public:


	void translate_image() {
		using namespace glm;

		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation + rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�

		result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // ���� ��ȯ

		transmit();
	}


	// �÷��̾� �ȱ� �ִϸ��̼�
	// �ȱ⸦ ���߸� ������ �ٽ� �����Ѵ�
	void animation_walk() {
		if (player_move_up || player_move_down || player_move_right || player_move_left) {
			num += ft * 8;
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


	void move() {
		GLfloat degree = cam_rotation * 3.14 / 180;
		GLfloat degree_vertical = (cam_rotation + 90) * 3.14 / 180;

		// �÷��̾� �̵�
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


	// �÷��̾� ���� ��ġ ����
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


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
		set_texture(tex, "res//player//spr_player_0.png", W, H, channel);
	}
};


class Foot : public Framework {
private:
	GLuint VAO;
	int W = 18, H = 18;
	unsigned tex[2];
	int channel = 1;
	int layer;

	GLfloat num = 0, degree = 0;
	GLfloat y = 0;

public:
	void render() {
		using namespace glm;

		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
			translate_matrix = translate(translate_matrix, vec3(ptr->get_x(), ptr->get_y(), 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
			translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�
			translate_matrix = translate(translate_matrix, vec3(-0.02, -0.03 + y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
			result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // ���� ��ȯ
			transmit();

			glBindVertexArray(VAO);
			glBindTexture(GL_TEXTURE_2D, tex[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);


			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
			translate_matrix = translate(translate_matrix, vec3(ptr->get_x(), ptr->get_y(), 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
			translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�
			translate_matrix = translate(translate_matrix, vec3(0.02, -0.03 - y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
			result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // ���� ��ȯ
			transmit();

			glBindVertexArray(VAO);
			glBindTexture(GL_TEXTURE_2D, tex[1]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	

	void update() {
		auto ptr = framework[layer_player][0];
		
		// �� ������ �ִϸ��̼�
		// �÷��̾ ������ ���� �����̰� �������� ������ �����
		if (ptr != nullptr) {
			if (ptr->player_move_up || ptr->player_move_down || ptr->player_move_right || ptr->player_move_left) {
				num += ft * 8;
				y = sin(num) / 20;
			}

			else {
				num = 0;
				if (y > 0) {
					y -= ft / 2;
					if (y < 0)
						y = 0;
				}
				else if (y < 0) {
					y += ft / 2;
					if (y > 0)
						y = 0;
				}
			}
		}
	}


	Foot(int l) {
		layer = l;

		//buffer set
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		input_canvas();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // ��ġ �Ӽ�
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // �ؽ�ó ��ǥ �Ӽ� 
		glEnableVertexAttribArray(2);

		// texture set
		glGenTextures(1, &tex[0]);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		set_parameteri();
		texture_data = stbi_load("res//player//spr_foot_left.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

		// texture set2
		glGenTextures(1, &tex[1]);
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		set_parameteri();
		texture_data = stbi_load("res//player//spr_foot_right.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};