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

		init_transform();

		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
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


	Center(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//object//spr_center.png", W, H, channel);
	}
};
