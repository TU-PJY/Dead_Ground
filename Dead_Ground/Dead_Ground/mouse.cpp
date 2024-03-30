#include "gl_header.h"

void rotate_camera(int x) {
	int delta = x - WIDTH / 2;
	cam_rotation += delta * 0.05;

	if (cam_rotation > 360)
		cam_rotation -= 360;
	if (cam_rotation < 0)
		cam_rotation += 360;

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);
}


// 윈도우 좌표계 -> OpenGL 좌표계 변환
void convert_cursor_position(int x, int y) {  //GL좌표계로 변환
	mx = (GLfloat)(x - (GLfloat)WIDTH / 2.0) * (GLfloat)(1.0 / (GLfloat)(WIDTH / 2.0));
	my = -(GLfloat)(y - (GLfloat)HEIGHT / 2.0) * (GLfloat)(1.0 / (GLfloat)(HEIGHT / 2.0));
}


void Mouse(int button, int state, int x, int y) {  // 마우스 클릭
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}

	glutPostRedisplay();
}


// 클릭 안할 때의 모션
void pMotion(int x, int y) { 
	convert_cursor_position(x, y);

	rotate_camera(x);

	glutPostRedisplay();
}


// 클릭 할 때의 모션
void Motion(int x, int y) {  
	convert_cursor_position(x, y);

	rotate_camera(x);

	glutPostRedisplay();
}