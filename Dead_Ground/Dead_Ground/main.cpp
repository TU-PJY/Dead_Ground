﻿#define STB_IMAGE_IMPLEMENTATION
#include "gl_header.h"
#include "mode_header.h"
#include "object_header.h"


int WIDTH = 800;//GetSystemMetrics(SM_CXSCREEN);  // 화면 사이즈에 맞추어 창을 출력한다
int HEIGHT = 600;//GetSystemMetrics(SM_CYSCREEN);


GLvoid displayOutput() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glUseProgram(ID);
	
	setWindowView();

	// 프레임워크 루프
	fw_routine();
	
	glutSwapBuffers();
}


GLvoid displayReshape(int w, int h) {
	glViewport(0, 0, w, h);
}


void main(int argc, char** argv) {
	{  // fold here
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GL_MULTISAMPLE);

		glutInitWindowPosition(0, 0);
		glutInitWindowSize(WIDTH, HEIGHT);

		glutCreateWindow("Dead Ground");

		glutSetCursor(GLUT_CURSOR_NONE);
		//glutFullScreen();  // 전체화면으로 전환한다

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Unable to initialize GLEW" << std::endl;  exit(EXIT_FAILURE);
		}

		else std::cout << "GLEW Initialized" << std::endl;

		glEnable(GL_DEPTH_TEST | GL_MULTISAMPLE | GL_ALPHA_TEST | GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);  // 이미지 뒤집힘 방지

		set_shader();
	}

	// 설정한 모드부터 실행, gl_header.h에 정의되어있음
	switch (START_MODE) {
	case _play_:
		play_mode();
		break;
	}
	
	glutDisplayFunc(displayOutput);
	glutReshapeFunc(displayReshape);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(pMotion);

	glutTimerFunc(10, timerOperation, 1);

	glutMainLoop();
}
