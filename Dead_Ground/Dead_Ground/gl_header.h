// OpenGL�� �ʿ��� ��� ���� ���� �� ������Ʈ ���� ���� ����
#pragma once
#include "shader.h"
#include "shader.h"
#include "translate.h"
#include "gl_func.h"
#include "Framework.h"
#include "math_util.h"
#include "image_text_util.h"
#define START_MODE _play_
#define BOUND_BOX 0  // 1: true, 0: false

extern int WIDTH, HEIGHT;  // ������ ������

extern GLfloat ratio;  // ������ ��Ⱦ��
extern GLfloat mx, my, cam_rotation, cam_x, cam_y;  // ���콺 ��ġ, ȭ�� ȸ�� ����, ī�޶� ��ġ
extern GLfloat map_size;  // �� ����

extern std::string vendor;  // �׷��� ī�� ������ ��