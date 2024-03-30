#pragma once
#include "gl_header.h"


class Ground : public Framework {
private:
	GLuint VAO;

	int W = 1500, H = 1500;
	unsigned int tex;
	int channel = 1;

	int layer;

public:
	void translate_image() {
		using namespace glm;

		init_transform();

		scale_matrix = scale(scale_matrix, vec3(40.0, 40.0, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // 최종 변환

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void update() {}

	Ground(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//map//spr_ground.png", W, H, channel);
	}
};


class CenterGround : public Framework {
private:
	GLuint VAO;

	int W = 1500, H = 1500;
	unsigned int tex;
	int channel = 1;

	int layer;

public:
	void translate_image() {
		using namespace glm;

		init_transform();

		scale_matrix = scale(scale_matrix, vec3(5.0, 5.0, 0.0));
		translate_matrix = translate(translate_matrix, vec3(0.0, 0.0, 0.0));

		result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // 최종 변환

		transmit();
	}


	void render() {
		translate_image();

		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	void update() {}


	CenterGround(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//map//spr_center_ground.png", W, H, channel);
	}
};