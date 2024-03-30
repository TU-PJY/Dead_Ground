#pragma once
#include "header.h"


// 회전하는 방향 결정
GLfloat calc_min_rotation(GLfloat from, GLfloat to);

// 각도를 -180 ~ 180으로 매핑
GLfloat normalize_angle(GLfloat angle);

// 두 오브젝트 간의 거리 계산
GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2);
