#pragma once
#include "header.h"
#define LAYER 6

// 모드 열거형 모음
enum Mods {
	_title_,
	_play_,
	_pause_,
	_gameover_,
};

// 오브젝트 종류 별로 레이어를 분리하도록 한다. 순서를 바꿀시 출력 순서가 달라진다.
enum LAYERS {
	layer_ground,
	layer_map_object,
	layer_player,
	layer_particle,
	layer_monster,
	layer_ui,
};

class Framework {
private:
	GLfloat x = 0, y = 0;
public:
	// 플레이어 움직임 여부, Player 클래스로 상속
	bool player_move_up = false , player_move_down = false, player_move_right = false, player_move_left = false;

	virtual void render() {}
	virtual void check_collision() {}
	virtual void update() {}

	// 현재 x, y좌표 반환
	virtual GLfloat get_x() const { return x; }
	virtual GLfloat get_y() const { return y; }

	// 충돌 처리 영역 배열 반환
	// x_min, x_max, y_min, y_mx
	virtual std::array<GLfloat, 4> get_collision_area() const { return {}; }


	virtual ~Framework() {
		//std::cout << "deleted fw" << std::endl;
	}
};

extern std::array<std::vector<Framework*>, LAYER> framework;


extern double ft;
extern int mode;

void fw_routine();
void fw_add(Framework*&& object, int layer);
void fw_delete(Framework* object, int layer);
void fw_sweep_layer(int layer);
void fw_sweep();
