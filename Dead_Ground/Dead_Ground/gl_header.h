// OpenGL�� �ʿ��� ��� ���� ���� �� ������Ʈ ���� ���� ����
#pragma once
#include "shader.h"
#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "translate.h"
#include "gl_func.h"
#include "Framework.h"
#include "stb_image.h"

#define START_MODE _play_

extern int WIDTH, HEIGHT;  // ������ ������

extern GLfloat ratio;  // ������ ��Ⱦ��
extern GLfloat mx, my, map_rotation;  // ���콺 ��ġ, ȭ�� ȸ�� ����