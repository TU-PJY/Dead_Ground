#pragma once
#include "gl_header.h"


class Text : public Framework {
private:
	GLuint VAO;
	unsigned int text_tex;
	int channel = 1;

	int layer;

public:
	void render() {
		using namespace glm;
		init_transform();
		set_object_static(-1.68, 1.3);
		draw_text(text_tex, VAO, 20, FW_NORMAL, "Dead Ground Indev Test");
	}


	void update() {}


	void check_collision() {}


	Text(int l) {
		layer = l;

		set_canvas(VAO);
		set_text(text_tex, "black");
	}
};