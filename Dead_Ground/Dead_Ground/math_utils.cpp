#include "gl_header.h"



// 회전하는 방향 결정
GLfloat calc_min_rotation(GLfloat from, GLfloat to) {
	GLfloat distance = to - from;
	if (distance > 180.0f)
		return distance - 360.0f;

	else if (distance < -180.0f)
		return distance + 360.0f;

	else
		return distance;
}


// 각도를 -180 ~ 180으로 매핑
GLfloat normalize_angle(GLfloat angle) {
	while (angle <= -180.0f)
		angle += 360.0f;

	while (angle > 180.0f)
		angle -= 360.0f;

	return angle;
}


// 두 오브젝트 간의 거리 계산
GLfloat calc_distance(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
