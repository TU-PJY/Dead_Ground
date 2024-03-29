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


public:
	GLfloat x = 0.0, y = 0.0;  // �浹ó���� ���� ����

	void translate_image() {
		using namespace glm;

		initTransform();
		translateMatrix = translate(translateMatrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translateMatrix = rotate(translateMatrix, radians(-map_rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�

		transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // ���� ��ȯ

		transmit();
	}

	void move() {
		GLfloat degree = map_rotation * 3.14 / 180;
		GLfloat degree_vertical = (map_rotation + 90) * 3.14 / 180;

		if (player_move_up) {
			x += 0.005 * ft * 150 * sin(degree);
			y += 0.005 * ft * 150 * cos(degree);
		}
		if (player_move_down) {
			x -= 0.005 * ft * 150 * sin(degree);
			y -= 0.005 * ft * 150 * cos(degree);
		}
		if (player_move_right) {
			x += 0.005 * ft * 150 * sin(degree_vertical);
			y += 0.005 * ft * 150 * cos(degree_vertical);
		}
		if (player_move_left) {
			x -= 0.005 * ft * 150 * sin(degree_vertical);
			y -= 0.005 * ft * 150 * cos(degree_vertical);
		}
	}


	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	void check_collision() {

	}

	void update() {
		move();
	}


	Player(int l) {
		layer = l;
		
		// buffer set
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
		texture_data = stbi_load("res//player//spr_player_0.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};