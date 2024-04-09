#pragma once
#include "gl_header.h"

//Date 클래스 내부에서 Clock 클래스가 동작한다

class Clock {
private:
	GLuint VAO{}, VAO_text{};
	unsigned int tex{}, text_tex{};
	GLuint base{};
	HDC hDC{};

	GLfloat num{};


public:
	int hour = 6, minute = 0;
	bool plus_day = false; // true 일 시 Date 클래스에서 Day 수치가 증가

	void render() {
		init_transform();
		s_mat *= scale_image(1.5, 1.5);
		fix_image_at(rectL + 0.5, -0.4);
		draw_image(tex, VAO);

		init_transform();
		fix_image_at(rectL + 0.4, -0.42);
		draw_text(text_tex, VAO_text, base, "%02d:%02d", hour, minute);
	}

	void update() {
		num += ft * 10;

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
		set_canvas(VAO);
		set_texture(tex, "res//ui//date//spr_ui_clock.png", 88, 88, 1);

		set_canvas(VAO_text);
		set_text(text_tex, "red");
		set_font(32, FW_BOLD, base, hDC);
	}

	~Clock() {
		kill_text(base);
	}
};


class Date : public Framework {
private:
	GLuint VAO{}, VAO_text{};
	unsigned int tex{}, text_tex{};
	GLuint base{};
	HDC hDC{};

	int layer{};
	int day{};


public:
	Clock clock;


	void render() {
		clock.render();

		init_transform();
		s_mat *= scale_image(1.5, 1.5);
		fix_image_at(rectL + 0.2, -0.4);
		draw_image(tex, VAO);

		init_transform();
		fix_image_at(rectL + 0.1, -0.48);

		draw_text(text_tex, VAO_text, base, "%d", day);
	}


	void check_collision() {}


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

		set_canvas(VAO);
		set_texture(tex, "res//ui//date//spr_ui_day.png", 91, 91, 1);

		set_canvas(VAO_text);
		set_text(text_tex, "black");
		set_font(60, FW_BOLD, base, hDC);
	}

	~Date() {
		kill_text(base);
	}
};
