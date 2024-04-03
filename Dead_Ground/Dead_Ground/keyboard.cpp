// 키보드 조작
#include "gl_header.h"
#include "object_header.h"


void key_down(unsigned char KEY, int x, int y) {
	auto ptr = framework[layer_player][0];

	switch (KEY) {
	case 27:  // ESC
		glutDestroyWindow(1);
		break;
	
	// 플레이어 움직임
	case 'w':
		if (ptr != nullptr)
			ptr->set_state(0);
		break;

	case 's':
		if (ptr != nullptr)
			ptr->set_state(1);
		break;

	case 'd':
		if (ptr != nullptr)
			ptr->set_state(2);
		break;

	case 'a':
		if (ptr != nullptr)
			ptr->set_state(3);
		break;
	///////////
	}
	
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}


void key_up(unsigned char KEY, int x, int y) {
	auto ptr = framework[layer_player][0];

	switch (KEY) {
		// 플레이어 움직임
	case 'w':
		if (ptr != nullptr)
			ptr->set_state(4);
		break;

	case 's':
		if (ptr != nullptr)
			ptr->set_state(5);
		break;

	case 'd':
		if (ptr != nullptr)
			ptr->set_state(6);
		break;

	case 'a':
		if (ptr != nullptr)
			ptr->set_state(7);
		break;
		///////////
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}
