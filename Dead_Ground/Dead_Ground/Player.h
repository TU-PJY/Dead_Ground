// 플레이어 클래스
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLuint VAO;

	int W = 56, H = 56;  // image size
	unsigned int tex;
	int channel = 1;
	int layer;  // framework layer number

	GLfloat num;
	GLfloat rotation;

public:
	GLfloat x = 0.0, y = 0.0;  // 충돌처리를 위한 변수

	void translate_image() {
		using namespace glm;

		initTransform();
		translateMatrix = translate(translateMatrix, vec3(x, y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
		translateMatrix = rotate(translateMatrix, radians(-map_rotation + rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다

		transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // 최종 변환

		transmit();
	}

	void move() {
		GLfloat degree = map_rotation * 3.14 / 180;
		GLfloat degree_vertical = (map_rotation + 90) * 3.14 / 180;

		// 플레이어 이동
		if (player_move_up) {
			if (player_move_right || player_move_left) {
				x += 0.005 * ft * 150 * sin(degree) / 1.414;
				y += 0.005 * ft * 150 * cos(degree) / 1.414;
			}
			else {
				x += 0.005 * ft * 150 * sin(degree);
				y += 0.005 * ft * 150 * cos(degree);
			}
		}

		if (player_move_down) {
			if (player_move_right || player_move_left) {
				x -= 0.005 * ft * 150 * sin(degree) / 1.414;
				y -= 0.005 * ft * 150 * cos(degree) / 1.414;
			}
			else {
				x -= 0.005 * ft * 150 * sin(degree);
				y -= 0.005 * ft * 150 * cos(degree);
			}
		}

		if (player_move_right) {
			if (player_move_up || player_move_down) {
				x += 0.005 * ft * 150 * sin(degree_vertical) / 1.414;
				y += 0.005 * ft * 150 * cos(degree_vertical) / 1.414;
			}
			else {
				x += 0.005 * ft * 150 * sin(degree_vertical);
				y += 0.005 * ft * 150 * cos(degree_vertical);
			}
		}

		if (player_move_left) {
			if (player_move_up || player_move_down) {
				x -= 0.005 * ft * 150 * sin(degree_vertical) / 1.414;
				y -= 0.005 * ft * 150 * cos(degree_vertical) / 1.414;
			}
			else {
				x -= 0.005 * ft * 150 * sin(degree_vertical);
				y -= 0.005 * ft * 150 * cos(degree_vertical);
			}
		}

		// 플레이어 걷기 애니메이션
		// 걷기를 멈추면 각도를 다시 복구한다
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

	// 플레이어 현재 위치 리턴
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
		
	}


	Player(int l) {
		layer = l;

		player_move_up = false;
		player_move_down = false;
		player_move_right = false;
		player_move_left = false;

		//buffer set
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		vertexInput();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // 위치 속성
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // 텍스처 좌표 속성 
		glEnableVertexAttribArray(2);

		// texture set
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		parameteri();
		texture_data = stbi_load("res//player//spr_player_0.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};

class Foot : public Framework {
private:
	GLuint VAO;
	int W = 18, H = 18;
	unsigned tex[2];
	int channel = 1;
	int layer;

	GLfloat num, degree;
	GLfloat y;

public:
	void render() {
		using namespace glm;

		auto ptr = framework[layer_player][0];

		if (ptr != nullptr) {
			initTransform();
			scaleMatrix = scale(scaleMatrix, vec3(0.3, 0.3, 0.0));
			translateMatrix = translate(translateMatrix, vec3(ptr->get_x(), ptr->get_y(), 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
			translateMatrix = rotate(translateMatrix, radians(-map_rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다
			translateMatrix = translate(translateMatrix, vec3(-0.02, -0.03 + y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
			transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // 최종 변환
			transmit();

			glBindVertexArray(VAO);
			glBindTexture(GL_TEXTURE_2D, tex[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);


			initTransform();
			scaleMatrix = scale(scaleMatrix, vec3(0.3, 0.3, 0.0));
			translateMatrix = translate(translateMatrix, vec3(ptr->get_x(), ptr->get_y(), 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
			translateMatrix = rotate(translateMatrix, radians(-map_rotation), vec3(0.0, 0.0, 1.0));  // 플레이어는 카메라 회전에 영향을 받지 않는다
			translateMatrix = translate(translateMatrix, vec3(0.02, -0.03 - y, 0.0));  // 플레이어는 카메라 위치에 영향을 받지 않는다
			transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // 최종 변환
			transmit();

			glBindVertexArray(VAO);
			glBindTexture(GL_TEXTURE_2D, tex[1]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	
	void update() {
		auto ptr = framework[layer_player][0];
		
		// 발 움직임 애니메이션
		// 플레이어가 움직일 때는 움직이고 움직이지 않으면 멈춘다
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
		vertexInput();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // 위치 속성
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // 텍스처 좌표 속성 
		glEnableVertexAttribArray(2);

		// texture set
		glGenTextures(1, &tex[0]);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		parameteri();
		texture_data = stbi_load("res//player//spr_foot_left.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

		// texture set2
		glGenTextures(1, &tex[1]);
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		parameteri();
		texture_data = stbi_load("res//player//spr_foot_right.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};