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
	layer_particle,
	layer_monster,
	layer_ui,
};

class Framework {
private:
	GLfloat x = 0, y = 0;
public:
	// �÷��̾� ������ ����, Player Ŭ������ ���
	bool player_move_up = false , player_move_down = false, player_move_right = false, player_move_left = false;

	virtual void render() {}
	virtual void check_collision() {}
	virtual void update() {}

	// ���� x, y��ǥ ��ȯ
	virtual GLfloat get_x() const { return x; }
	virtual GLfloat get_y() const { return y; }

	// �浹 ó�� ���� �迭 ��ȯ
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
