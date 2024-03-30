#pragma once
#include "gl_header.h"


class Regular : public Framework {
private:
	GLuint VAO;
	int W = 48, H = 48;
	unsigned int tex;
	int channel = 1;

	GLfloat x, y;
	GLfloat direction = 0, rotation = 0;
	GLfloat direction2 = 0, rotation2 = 0;
	GLfloat speed = 0.3;

	int hp = 100;
	int damage = 10;
	int layer;

public:
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }


	void translate_image() {
		using namespace glm;

		initTransform();
		translateMatrix = translate(translateMatrix, vec3(x, y, 0.0));
		translateMatrix = rotate(translateMatrix, radians(rotation2), vec3(0.0, 0.0, 1.0)); 

		transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // ���� ��ȯ

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	// ȸ���ϴ� ���� ����
	GLfloat calc_min_rotation(GLfloat from, GLfloat to) {
		GLfloat distance = to - from;
		if (distance > 180.0f)
			return distance - 360.0f;

		else if (distance < -180.0f)
			return distance + 360.0f;

		else
			return distance;

	}


	// ������ -180 ~ 180���� ����
	GLfloat normalizeAngle(GLfloat angle) {
		while (angle <= -180.0f)
			angle += 360.0f;

		while (angle > 180.0f)
			angle -= 360.0f;

		return angle;
	}


	// �� ������Ʈ ���� �Ÿ� ���
	GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2) {
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	}


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
			GLfloat rotationSpeed = ft * 150;

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


	Regular(GLfloat rand_x, GLfloat rand_y, int l) {
		x = rand_x;
		y = rand_y;
		layer = l;

		//buffer set
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		vertexInput();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // ��ġ �Ӽ�
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // �ؽ�ó ��ǥ �Ӽ� 
		glEnableVertexAttribArray(2);

		// texture set
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		parameteri();
		texture_data = stbi_load("res//monster//spr_zombie_0.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};