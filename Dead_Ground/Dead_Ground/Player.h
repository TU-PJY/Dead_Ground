// �÷��̾� Ŭ����
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLfloat walk_speed = 0.75;
	GLfloat x = 0.0, y = -0.4;  // �浹ó���� ���� ����

	GLfloat max_hp = 500;
	GLfloat hp = max_hp;  // �÷��̾� hp

	GLfloat damage = 0;  // �÷��̾ �޴� �����
	GLfloat damage_delay = 0;  // ����� �ޱ� ������

	GLfloat recovery_delay = 0;  // ü�� ȸ�� ������

	bool is_move = false;  // true �Ͻ� �÷��̾� ������

	GLfloat num = 0;
	GLfloat rotation = 0;

	GLfloat move_degree = 0;  // �÷��̾� �̵� ���⿡ ���Ǵ� ����
	GLfloat move_radian = 0;  // �÷��̾� �̵� ����
	GLfloat cam_radian = 0; // ī�޶� ȸ�� ����

	bool player_move_up = false;
	bool player_move_down = false;
	bool player_move_right = false;
	bool player_move_left = false;

	// �÷��̾� �浹 ó�� ����
	std::array<GLfloat, 4> bound = { -0.12, 0.12, -0.12, 0.12 };

	// �ٿ�� �ڽ�
	unsigned int bound_box;

	GLuint VAO;
	unsigned int tex;
	int layer;  // framework layer number


public:
	void update_index(int idx) {}

	// �÷��̾� ���� ��ġ ����
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }

	// �÷��̾� ü�� ����
	GLfloat get_hp() const { return hp; }

	// �÷��̾� �̵� �ӵ� ����
	GLfloat get_speed() const { return walk_speed; }

	// �÷��̾� �̵� ���� ����
	bool get_state() const { return is_move; }

	// �÷��̾� �̵� ���� ����
	void set_state(int opt) {
		switch (opt) {
		case 0:
			player_move_up = true;  break;
		case 1:
			player_move_down = true;  break;
		case 2:
			player_move_right = true;  break;
		case 3:
			player_move_left = true;  break;

		case 4:
			player_move_up = false;  break;
		case 5:
			player_move_down = false;  break;
		case 6:
			player_move_right = false;  break;
		case 7:
			player_move_left = false;  break;
		}
	}


	std::array<GLfloat, 4> get_collision_area() const { return bound; }


	void render() {
		using namespace glm;

		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation + rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�

		draw_image(tex, VAO);


		// bound box
		if (BOUND_BOX == 1) {
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.6, 0.6, 0.0));
			translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));

			draw_image(bound_box, VAO);
		}
	}


	void animation_walk() {
		if (is_move) {
			num += ft * walk_speed * 10;
			rotation = -sin(num) * 10;
		}

		else {
			num = 0;
			if (rotation > 0) {
				rotation -= ft * 30;
				if (rotation < 0)
					rotation = 0;
			}
			else if (rotation < 0) {
				rotation += ft * 30;
				if (rotation > 0)
					rotation = 0;
			}
		}
	}


	// �÷��̾�� ������� �ο��Ѵ�
	void give_damage(GLfloat damage) {
		if (damage > 0 && damage_delay == 0) {
			hp -= damage;
			damage_delay = 10;
			damage = 0;
		}
	}


	// ���� �ð� ���� ������� ���� �� �ֵ��� ����� ������ ������Ʈ
	void update_damage_delay() {
		if (damage_delay > 0) {
			damage_delay -= ft * 10;
			if (damage_delay < 0)
				damage_delay = 0;
		}
	}


	// �÷��̾� ü�� ȸ��
	void recover_hp() {
		if (recovery_delay > 0) {
			recovery_delay -= ft * 5;
			if (recovery_delay < 0)
				recovery_delay = 0;
		}

		// ���� ���� ���� ü���� ȸ���Ѵ�
		if (hp < max_hp && recovery_delay == 0) {
			hp += 10;

			if (hp > max_hp)
				hp = max_hp;
			else
			 recovery_delay = 10;
		}
	}
	

	// �� �𼭸� �浹 ó��, �� ������ ��� �� ����
	void check_map_collision() {
		if (x > 4.0 || x < -4.0)
			x += -sin(move_radian + cam_radian) * ft * walk_speed;

		if (y > 4.0 || y < -4.0) 
			y += -cos(move_radian + cam_radian) * ft * walk_speed;
			
	}


	//�� ������Ʈ �浹 ó��
	// layer_object �� �����ϴ� ��� ������Ʈ�κ��� ��� ��ǥ�� ��� �浹ó�� �Ѵ�.
	void check_map_object_collision() {
		for (int i = 0; i < framework[layer_map_object].size(); ++i) {
			auto ptr = framework[layer_map_object][i];

			if (ptr != nullptr) {
				// ������Ʈ�� return�ϴ� �ٿ�� ������ �����´�
				std::array<GLfloat, 4> b = ptr->get_collision_area(); 

				// ������Ʈ �߽����� �������� ������Ʈ���� ��� ���⿡ �ִ��� �Ǵ��Ѵ�
				// �ٶ󺸴� ����, �̵� ����, �浹 ������ �Ǵ��Ͽ� �浹ó�� �Ѵ�

				// �ٿ�� �ڽ� �߽���
				GLfloat b_center = b[1] / 2;

				// ���� ������ �ٶ󺸴� ���� (ȭ�� �󿡼� ����)
				// ������
				if (b[2] <= y && y <= b[3] && b[0] < x && x < b[0] + b_center) {
					if ((player_move_right && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_down && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_left && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_up && 0 < cam_rotation && cam_rotation < 180)) {
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				// ������
				if (b[2] <= y && y <= b[3] && b[1] >= x && x > b[1] - b_center) {
					if ((player_move_left && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_right && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_up && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_down && 0 < cam_rotation && cam_rotation < 180)) {
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				//// �Ʒ���
				if (b[2] <= y && y < b[2] + b_center && b[0] <= x && x <= b[1]) {
					if ((player_move_up && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_right && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_down && 90 < cam_rotation && cam_rotation < 270) ||
						(player_move_left && 0 < cam_rotation && cam_rotation < 180)) {
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
					}
				}

				// ����
				if (b[3] >= y && y > b[3] - b_center && b[0] <= x && x <= b[1]) {
					if ((player_move_down && ((270 < cam_rotation && cam_rotation < 360) || (0 < cam_rotation && cam_rotation < 90))) ||
						(player_move_left && 180 < cam_rotation && cam_rotation < 360) ||
						(player_move_right && 0 < cam_rotation && cam_rotation < 180) ||
						(player_move_up && 90 < cam_rotation && cam_rotation < 270)) {
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
					}
				}
			}
		}
	}


	void set_move_direction() {
		// ���� ����Ű ����
		if (player_move_up && player_move_right && !player_move_left && !player_move_down)
			move_degree = 45;

		else if (player_move_up && player_move_left && !player_move_right && !player_move_down)
			move_degree = -45;

		else if (player_move_up &&
			(!player_move_left && !player_move_right && !player_move_down) ||
			(player_move_left && player_move_right && !player_move_down))
			move_degree = 0;


		// �Ʒ��� ����Ű ����
		else if (player_move_down && player_move_right && !player_move_left && !player_move_up)
			move_degree = 135;

		else if (player_move_down && player_move_left && !player_move_right && !player_move_up)
			move_degree = -135;

		else if (player_move_down &&
			(!player_move_left && !player_move_right && !player_move_up) ||
			(player_move_left && player_move_right && !player_move_up))
			move_degree = 180;


		// ������ ����Ű ����
		else if (player_move_right && player_move_up && !player_move_down && !player_move_left)
			move_degree = 45;

		else if (player_move_right && player_move_down && !player_move_up && !player_move_left)
			move_degree = 135;

		else if (player_move_right &&
			(!player_move_up && !player_move_down && !player_move_left) ||
			(player_move_up && player_move_down && !player_move_left))
			move_degree= 90;


		// ���� ����Ű ����
		else if (player_move_left && player_move_up && !player_move_down && !player_move_right)
			move_degree = -45;

		else if (player_move_left && player_move_down && !player_move_up && !player_move_right)
			move_degree = -135;

		else if (player_move_left &&
			(!player_move_up && !player_move_down && !player_move_right) ||
			(player_move_up && player_move_down && !player_move_right))
			move_degree = -90;

		// ���� ���� ���� ���
		move_radian = move_degree * 3.14 / 180;
		cam_radian = cam_rotation * 3.14 / 180;
	}


	// ������ �� �ִ��� Ȯ��
	void check_move() {
		is_move = false;

		// Ư�� Ű ������ �������� Ȱ��ȭ���� �ʴ´�
		// is_move�� false�� ���·� �����Ͽ� �÷��̾�� �������� �ʴ´�
		if (!player_move_up && !player_move_right && !player_move_left && !player_move_down)
			return;

		else if (player_move_up && player_move_right && player_move_left && player_move_down)
			return;

		else if ((player_move_right && player_move_left && !player_move_up && !player_move_down) ||
			(player_move_up && player_move_down && !player_move_left && !player_move_right))
			return;

		else {
			x += sin(move_radian + cam_radian) * ft * walk_speed;
			y += cos(move_radian + cam_radian) * ft * walk_speed;

			// ������ �� �ִ� ���¶�� true
			is_move = true;
		}
	}


	void check_collision() {
		check_map_object_collision();
		check_map_collision();
	}


	void update() {
		update_damage_delay();
		recover_hp();
		animation_walk();

		set_move_direction();
		check_move();

		for (int i = 0; i < framework[layer_monster].size(); ++i) {
			auto ptr = framework[layer_monster][i];
			if (ptr != nullptr) {
				if (calc_distance(x, ptr->get_x(), y, ptr->get_y()) < 0.1) {
					fw_delete(ptr, layer_monster);
				}
					
			}
		}
	}


	Player(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//player//spr_player_0.png", 56, 56, 1);

		if (BOUND_BOX == 1)  // �ٿ�� �ڽ� Ȱ��ȭ �ÿ��� ����
			set_bound_box(bound_box);
	}
};