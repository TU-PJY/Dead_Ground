#pragma once
#include "gl_header.h"


class Center : public Framework {
private:
	GLuint VAO;

	int W = 85, H = 85;
	unsigned int tex;
	int channel = 1;
	int layer;

	int hp = 100;

public:
	void translate_image() {
		using namespace glm;

		initTransform();

		scaleMatrix = scale(scaleMatrix, vec3(1.5, 1.5, 0.0));
		translateMatrix = translate(translateMatrix, vec3(0.0, 0.0, 0.0));

		transformMatrix = rotateMatrix * translateMatrix * scaleMatrix;  // ���� ��ȯ

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	void update() {}


	Center(int l) {
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
		texture_data = stbi_load("res//object//spr_center.png", &W, &H, &channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	}
};
