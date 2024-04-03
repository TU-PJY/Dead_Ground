#pragma once
#include "header.h"
#define LAYER 8

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

	// �÷��̾� �̵� ���� ����
	virtual void set_state(int opt) {}

	// ��ü x, y��ǥ ����
	virtual GLfloat get_x() const { return data; }
	virtual GLfloat get_y() const { return data; }

	// ��ü ȸ�� ���� ����
	virtual GLfloat get_rotation() const { return data; }

	// ��ü hp ����
	virtual GLfloat get_hp() const { return data; }

	// ��ü ������ ���� ����
	virtual bool get_state() const { return state; }

	// ��ü �̵� �ӵ� ����
	virtual GLfloat get_speed() const { return data; }

	// ��ü ����� �ֱ�
	virtual void give_damage(GLfloat damage) {}

	// �浹 ó�� ���� �迭 ����
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
