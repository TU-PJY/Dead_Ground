#pragma once
#include "header.h"


// ȸ���ϴ� ���� ����
GLfloat calc_min_rotation(GLfloat from, GLfloat to);

// ������ -180 ~ 180���� ����
GLfloat normalize_angle(GLfloat angle);

// �� ������Ʈ ���� �Ÿ� ���
GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
