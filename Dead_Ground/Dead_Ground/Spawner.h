#pragma once
//#include <random>
#include "gl_header.h"
#include "Regular.h"


class Spawner : public Framework {
private:
	GLfloat timer = 0;
	bool spawn = false;
	int type = 0;
	GLfloat x = 0, y = 0;
	GLfloat speed = 0;

	int layer;


public:
	void render() {}


	void spawn_monster() {
		timer += ft * 10;
		if (timer > 20) {
			type = 1;  // �ϴ� 1�� Ÿ�����θ� �������� ����

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<GLfloat> rand_position(-1.0, 1.0);
			std::uniform_int_distribution<int> rand_speed(2, 5);

			x = rand_position(gen);
			y = rand_position(gen);
			speed = rand_speed(gen) * 0.1;  // ���� �ӵ��� ��� �ٸ��� �����Ѵ� -> ���� ��ħ ����

			switch (type) {
			case 1:
				fw_add(new Regular(x, y, speed, layer_monster), layer_monster);
				break;
			}

			timer = 0;
		}
	}


	void update() {
		spawn_monster();
	}


	Spawner(int l) {
		layer = l;
	}
};