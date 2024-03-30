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


// ������ ��ǥ�� -> OpenGL ��ǥ�� ��ȯ
void convert_cursor_position(int x, int y) {  //GL��ǥ��� ��ȯ
	mx = (GLfloat)(x - (GLfloat)WIDTH / 2.0) * (GLfloat)(1.0 / (GLfloat)(WIDTH / 2.0));
	my = -(GLfloat)(y - (GLfloat)HEIGHT / 2.0) * (GLfloat)(1.0 / (GLfloat)(HEIGHT / 2.0));
}


void Mouse(int button, int state, int x, int y) {  // ���콺 Ŭ��
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}

	glutPostRedisplay();
}


// Ŭ�� ���� ���� ���
void pMotion(int x, int y) { 
	convert_cursor_position(x, y);

	rotate_camera(x);

	glutPostRedisplay();
}


// Ŭ�� �� ���� ���
void Motion(int x, int y) {  
	convert_cursor_position(x, y);

	rotate_camera(x);

	glutPostRedisplay();
}