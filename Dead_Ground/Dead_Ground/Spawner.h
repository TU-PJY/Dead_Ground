#pragma once
#include "gl_header.h"
#include "Regular.h"
#include "Small.h"
#include "Foot.h"
#include "Shadow.h"


class Spawner : public Framework {
private:
	GLfloat timer = 20;
	bool spawn{};
	int type{}, range{};
	GLfloat x{}, y{};
	GLfloat speed{};

	int layer{};


public:
	void render() {}


	void spawn_monster() {
		timer += ft * 10;

		// 설정한 타이머 시간이 되면 몬스터를 랜덤 스폰한다
		if (timer > 20) {
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
				fw_add(new Shadow(layer_entity, framework[layer_monster].size() - 1, "monster"), layer_entity);
				fw_add(new Foot(layer_entity, framework[layer_monster].size() - 1, "monster"), layer_entity);
			}

			if (type == 2) {
				std::uniform_real_distribution<GLfloat> rand_speed(5.0, 7.0);
				speed = rand_speed(gen) * 0.1;
				fw_add(new Small(x, y, speed, layer_monster), layer_monster);
				fw_add(new Shadow(layer_entity, framework[layer_monster].size() - 1, "monster"), layer_entity);
				fw_add(new Foot(layer_entity, framework[layer_monster].size() - 1, "monster"), layer_entity);
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