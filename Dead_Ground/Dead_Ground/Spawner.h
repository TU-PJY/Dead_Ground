#pragma once
#include "gl_header.h"
#include "Regular.h"
#include "Small.h"


class Spawner : public Framework {
private:
	GLfloat timer = 0;
	bool spawn = false;
	int type = 0, range = 0;
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

			std::uniform_int_distribution<int> rand_type(1, 2);  // 타입 랜덤
			std::uniform_int_distribution<int> rand_range(1, 4);  // 스폰되는 위치 범위 랜덤

			range = rand_range(gen);

			GLfloat size = map_size * 0.1;

			// 몬스터 랜덤 위치 스폰
			if (range == 1) {  // up
				std::uniform_real_distribution<GLfloat> rand_position_x(-size, size);
				x = rand_position_x(gen);
				y = 4.5;
			}
			if (range == 2) {  // down
				std::uniform_real_distribution<GLfloat> rand_position_x(-size, size);
				x = rand_position_x(gen);
				y = -4.5;
			}
		    if (range == 3) {  // right
				std::uniform_real_distribution<GLfloat> rand_position_y(-size, size);
				x = 4.5;
				y = rand_position_y(gen);
			}
			if (range == 4) {  //left
				std::uniform_real_distribution<GLfloat> rand_position_y(-size, size);
				x = -4.5;
				y = rand_position_y(gen);
			}

			type = rand_type(gen);

			// 몬스터 랜덤 스폰
			if (type == 1) {
				std::uniform_real_distribution<GLfloat> rand_speed(2.0, 5.0);
				speed = rand_speed(gen) * 0.1;
				fw_add(new Regular(x, y, speed, layer_monster), layer_monster);
			}

			if (type == 2) {
				std::uniform_real_distribution<GLfloat> rand_speed(5.0, 7.0);
				speed = rand_speed(gen) * 0.1;
				fw_add(new Small(x, y, speed, layer_monster), layer_monster);
			}

			timer = 0;
		}
	}


	void check_collision() {}


	void update() {
		spawn_monster();
	}


	Spawner(int l) {
		layer = l;
	}
};