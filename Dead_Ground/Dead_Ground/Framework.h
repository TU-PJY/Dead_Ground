#pragma once
#include "header.h"
#define LAYER 8

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
	layer_entity,
	layer_map_object,
	layer_particle,
	layer_player,
	layer_monster,
	layer_ui,
};

class Framework {
private:
	GLfloat data;
	bool state;

public:
	virtual void render() {}
	virtual void check_collision() {}
	virtual void update() {}

	// 플레이어 이동 상태 변경
	virtual void set_state(int opt) {}

	// 객체 x, y좌표 리턴
	virtual GLfloat get_x() const { return data; }
	virtual GLfloat get_y() const { return data; }

	// 객체 회전 각도 리턴
	virtual GLfloat get_rotation() const { return data; }

	// 객체 hp 리턴
	virtual GLfloat get_hp() const { return data; }

	// 객체 움직임 상태 리턴
	virtual bool get_state() const { return state; }

	// 객체 이동 속도 리턴
	virtual GLfloat get_speed() const { return data; }

	// 객체 대미지 주기
	virtual void give_damage(GLfloat damage) {}

	// 충돌 처리 영역 배열 리턴
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
