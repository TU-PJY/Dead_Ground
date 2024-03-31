#pragma once
#include "gl_header.h"

//Date 클래스 내부에서 Clock 클래스가 동작한다

class Clock {
private:
	std::array<GLuint, 2> VAO{};
	std::array<unsigned int, 2> tex{};

	GLfloat num = 0;


public:
	int hour = 6, minute = 0;
	bool plus_day = false; // true 일 시 Date 클래스에서 Day 수치가 증가

	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		set_object_static(-1.0 * ratio + 0.5, -0.4);
		draw_image(tex[0], VAO[0]);

		init_transform();
		set_object_static(-1.0 * ratio + 0.42, -0.42);
		draw_text(tex[1], VAO[1], 30, "%02d:%02d", FW_BOLD, hour, minute); 
	}

	void update() {
		num += ft * 5;

		if (num > 60) {
			num = 0;
			hour++;
			if (hour > 23) {
				hour = 0;
				plus_day = true;
			}
		}

		minute = (int)num;
	}

	Clock() {
		set_canvas(VAO[0]);
		set_texture(tex[0], "res//ui/spr_ui_clock.png", 88, 88, 1);

		set_text_canvas(VAO[1]);
		set_texture(tex[1], "res//ui//text//text_skin_red.png", 10, 10, 1);
	}
};


class Date : public Framework {
private:
	std::array<GLuint, 2> VAO{};
	std::array<unsigned int, 2> tex{};

	int layer;
	int day = 0;


public:
	Clock clock;

	void render() {
		using namespace glm;

		clock.render();

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		set_object_static(-1.0 * ratio + 0.2, -0.4);
		draw_image(tex[0], VAO[0]);

		init_transform();
		if(day < 10)
			set_object_static(-1.0 * ratio + 0.17, -0.48);
		if(10 < day && day < 100)
			set_object_static(-1.0 * ratio + 0.135, -0.48);

		draw_text(tex[1], VAO[1], 60, "%d", FW_BOLD, day);

	}

	void update() {
		clock.update();

		//24시가 되면 하루가 지난다
		if (clock.plus_day) {
			day++;
			clock.plus_day = false;
		}
	}

	Date(int l) {
		layer = l;

		set_canvas(VAO[0]);
		set_text_canvas(VAO[1]);

		set_texture(tex[0], "res//ui//spr_ui_day.png", 91, 91, 1);
		set_texture(tex[1], "res//ui//text//text_skin_black.png", 10, 10, 1);
	}
};
