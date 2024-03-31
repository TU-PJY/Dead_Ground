// 전역 변수 선언
#include "gl_header.h"

GLfloat mx, my, cam_rotation, cam_x, cam_y;  // 마우스 위치, 화면 회전 각도, 카메라 위치
int font = (int)GLUT_BITMAP_HELVETICA_18;  // 레스터 폰트