// �÷��̾� Ŭ����
#pragma once
#include "gl_header.h"


class Player : public Framework {
private:
	GLuint VAO;
	std::array<unsigned int, 3> tex{};
	int layer;  // framework layer number

	GLfloat walk_speed = 0.75;
	GLfloat num = 0;
	GLfloat rotation = 0;

	GLfloat foot_y = 0;

	GLfloat x = 0.0, y = -0.4;  // �浹ó���� ���� ����

	GLfloat move_degree = 0;  // �÷��̾� �̵� ���⿡ ���Ǵ� ����
	GLfloat move_radian = 0;  // �÷��̾� �̵� ����
	GLfloat cam_radian = 0; // ī�޶� ȸ�� ����

	bool is_move = false;  // true �Ͻ� �÷��̾� ������

	// �÷��̾� �浹 ó�� ����
	std::array<GLfloat, 4> bound = { -0.12, 0.12, -0.12, 0.12 };

	// �ٿ�� �ڽ�
	unsigned int bound_box;

public:
	bool hit = false;  // true

	// �÷��̾� ���� ��ġ ����
	GLfloat get_x() const { return x; }
	GLfloat get_y() const { return y; }


	virtual std::array<GLfloat, 4> get_collision_area() const { return bound; }


	void render() {
		using namespace glm;

		// left foot
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�
		translate_matrix = translate(translate_matrix, vec3(-0.02, -0.03 + foot_y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�

		draw_image(tex[0], VAO);


		// right foot
		init_transform();
		scale_matrix = scale(scale_matrix, vec3(0.3, 0.3, 0.0));
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�
		translate_matrix = translate(translate_matrix, vec3(0.02, -0.03 - foot_y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�

		draw_image(tex[1], VAO);


		// body
		init_transform();
		translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));  // �÷��̾�� ī�޶� ��ġ�� ������ ���� �ʴ´�
		translate_matrix = rotate(translate_matrix, radians(-cam_rotation + rotation), vec3(0.0, 0.0, 1.0));  // �÷��̾�� ī�޶� ȸ���� ������ ���� �ʴ´�

		draw_image(tex[2], VAO);


		// bound box
		if (BOUND_BOX == 1) {
			init_transform();
			scale_matrix = scale(scale_matrix, vec3(0.6, 0.6, 0.0));
			translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));

			draw_image(bound_box, VAO);
		}
	}


	// �÷��̾� �ȱ� �ִϸ��̼�
	// �ȱ⸦ ���߸� ������ �ٽ� �����Ѵ�
	void animation_walk() {
		if (is_move) {
			num += ft * walk_speed * 10;
			rotation = -sin(num) * 10;
			foot_y = sin(num) / 20;
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


			if (foot_y > 0) {
				foot_y -= ft / 2;
				if (foot_y < 0)
					foot_y = 0;
			}
			else if (foot_y < 0) {
				foot_y += ft / 2;
				if (foot_y > 0)
					foot_y = 0;
			}
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
		for (int i = 0; i < framework[layer_map_object].size(); i++) {
			auto ptr = framework[layer_map_object][i];

			if (ptr != nullptr) {
				std::array<GLfloat, 4> b = ptr->get_collision_area();  // get objects's border

				// ������Ʈ �߽����� �������� ������Ʈ���� ��� ���⿡ �ִ��� �Ǵ��Ѵ�
				// �ٶ󺸴� ����, �̵� ����, �浹 ������ �Ǵ��Ͽ� �浹ó�� �Ѵ�

				// �ٿ�� �ڽ� �߽���
				GLfloat b_center = b[1] / 2;

				// ���� ������ �ٶ󺸴� ���� (ȭ�� �󿡼� ����)
				// ������
				if (b[2] <= y && y <= b[3] && b[0] < x && x < b[0] + b_center) {
					if (player_move_up && 0 < cam_rotation && cam_rotation < 180)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 180 < cam_rotation && cam_rotation < 360)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 90 < cam_rotation && cam_rotation < 270)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
				}

				// ������
				if (b[2] <= y && y <= b[3] && b[1] >= x && x > b[1] - b_center) {
					if (player_move_up && 180 < cam_rotation && cam_rotation < 360)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 0 < cam_rotation && cam_rotation < 180)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 90 < cam_rotation && cam_rotation < 270)
						x -= sin(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						x -= sin(move_radian + cam_radian) * ft * walk_speed;
				}

				//// �Ʒ���
				if (b[2] <= y && y < b[2] + b_center && b[0] <= x && x <= b[1]) {
					if (player_move_up && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && 90 < cam_rotation && cam_rotation < 270)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 180 < cam_rotation && cam_rotation < 360)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 0 < cam_rotation && cam_rotation < 180)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
				}

				// ����
				if (b[3] >= y && y > b[3] - b_center && b[0] <= x && x <= b[1]) {
					if (player_move_up && 90 < cam_rotation && cam_rotation < 270)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_down && ((270 < cam_rotation && cam_rotation < 360) || 0 < cam_rotation && cam_rotation < 90))
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_right && 0 < cam_rotation && cam_rotation < 180)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;

					else if(player_move_left && 180 < cam_rotation && cam_rotation < 360)
						y -= cos(move_radian + cam_radian) * ft * walk_speed;
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
		set_move_direction();
		check_move();
		animation_walk();
	}


	Player(int l) {
		layer = l;

		player_move_up = false;
		player_move_down = false;
		player_move_right = false;
		player_move_left = false;

		set_canvas(VAO);
		set_texture(tex[0], "res//player//spr_foot_left.png", 18, 18, 1);
		set_texture(tex[1], "res//player//spr_foot_right.png", 18, 18, 1);
		set_texture(tex[2], "res//player//spr_player_0.png", 56, 56, 1);

		if (BOUND_BOX == 1)  // �ٿ�� �ڽ� Ȱ��ȭ �ÿ��� ����
			set_bound_box(bound_box);
	}
};