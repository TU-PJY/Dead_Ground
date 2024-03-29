#pragma once
#include "header.h"
#define LAYER 6

// ��� ������ ����
enum Mods {
	_title_,
	_play_,
	_pause_,
	_gameover_,
};

// ������Ʈ ���� ���� ���̾ �и��ϵ��� �Ѵ�. ������ �ٲܽ� ��� ������ �޶�����.
enum LAYERS {
	layer_ground,
	layer_map_object,
	layer_player,
	layer_bullet,
	layer_monster,
	layer_ui,
};

class Framework {
private:
	GLfloat x, y;
public:
	virtual void render() {}
	virtual void check_collision() {}
	virtual void update() {}

	virtual GLfloat get_x() const { return x; }
	virtual  GLfloat get_y() const { return y; }
};

extern std::array<std::vector<Framework*>, LAYER> framework;


extern double ft;
extern int mode;

void fw_routine();
void fw_add(Framework*&& object, int layer);
void fw_delete(Framework* object, int layer);
void fw_sweep_layer(int layer);
void fw_sweep();
