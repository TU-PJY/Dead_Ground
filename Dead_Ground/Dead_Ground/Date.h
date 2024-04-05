#pragma once
#include "gl_header.h"

//Date Ŭ���� ���ο��� Clock Ŭ������ �����Ѵ�

class Clock {
private:
	GLuint VAO{}, VAO_text{};
	unsigned int tex{}, text_tex{};
	GLuint base{};
	HDC hDC{};

	GLfloat num{};


public:
	int hour = 6, minute = 0;
	bool plus_day = false; // true �� �� Date Ŭ�������� Day ��ġ�� ����

	void render() {
		using namespace glm;

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		set_object_static(-1.0 * ratio + 0.5, -0.4);
		draw_image(tex, VAO);

		init_transform();
		set_object_static(-1.0 * ratio + 0.42, -0.42);
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
		set_font(30, FW_NORMAL, base, hDC);
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
		using namespace glm;

		clock.render();

		init_transform();
		scale_matrix = scale(scale_matrix, vec3(1.5, 1.5, 0.0));
		set_object_static(-1.0 * ratio + 0.2, -0.4);
		draw_image(tex, VAO);

		init_transform();
		if(day < 10)
			set_object_static(-1.0 * ratio + 0.17, -0.48);
		if(10 < day && day < 100)
			set_object_static(-1.0 * ratio + 0.135, -0.48);

		draw_text(text_tex, VAO_text, base, "%d", day);
	}


	void check_collision() {}


	void update() {
		clock.update();

		//24�ð� �Ǹ� �Ϸ簡 ������
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
};
