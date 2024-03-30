#pragma once
//#include <random>
#include "gl_header.h"
#include "Regular.h"
#include "Small.h"


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
			type = 1;  // 일단 1번 타입으로만 스폰시켜 본다

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> rand_type(1, 2);
			std::uniform_real_distribution<GLfloat> rand_position(-2.0, 2.0);

			type = rand_type(gen);

			x = rand_position(gen);
			y = rand_position(gen);
				
			// 랜덤 타입 몬스터 추가
			switch (type) {
			case 1:
			{
				std::uniform_real_distribution<GLfloat> rand_speed(2.0, 5.0);
				speed = rand_speed(gen) * 0.1;
				fw_add(new Regular(x, y, speed, layer_monster), layer_monster);
			}
				break;
			case 2:
			{
				std::uniform_real_distribution<GLfloat> rand_speed(5.0, 7.0);
				speed = rand_speed(gen) * 0.1;
				fw_add(new Small(x, y, speed, layer_monster), layer_monster);
				break;
			}
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