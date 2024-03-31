#pragma once
#include "gl_header.h"


class Text : public Framework {
private:
	GLuint VAO;
	int W = 10, H = 10;
	unsigned int tex;
	int channel = 1;

	int layer;

public:
	void render() {
		using namespace glm;
		init_transform();
		set_object_static(-1.7, -0.5);

		draw_text(VAO, tex, 20, "Dead Ground Indev");
	}


	void update() {}


	Text(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//ui//text//text_skin.png", W, H, channel);
	}
};