// 키보드 조작
#include "gl_header.h"
#include "object_header.h"


void keyDown(unsigned char KEY, int x, int y) {
	auto ptr = framework[layer_player][0];

	switch (KEY) {
	case 27:  // ESC
		glutDestroyWindow(1);
		break;
	
	// 플레이어 움직임
	case 'w':
		if(ptr != nullptr)
			ptr->player_move_up = true;
		break;

	case 's':
		if (ptr != nullptr)
			ptr->player_move_down = true;
		break;

	case 'd':
		if (ptr != nullptr)
			ptr->player_move_right = true;
		break;

	case 'a':
		if (ptr != nullptr)
			ptr->player_move_left = true;
		break;
	///////////

	}
	
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}


void keyUp(unsigned char KEY, int x, int y) {
	auto ptr = framework[layer_player][0];

	switch (KEY) {
		// 플레이어 움직임
	case 'w':
		if (ptr != nullptr)
			ptr->player_move_up = false;
		break;

	case 's':
		if (ptr != nullptr)
			ptr->player_move_down = false;
		break;

	case 'd':
		if (ptr != nullptr)
			ptr->player_move_right = false;
		break;

	case 'a':
		if (ptr != nullptr)
			ptr->player_move_left = false;
		break;
		///////////
	}
	if (glutGetWindow() != 0)
		glutPostRedisplay();
}
