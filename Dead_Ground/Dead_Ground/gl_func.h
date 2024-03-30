// OpenGL 기능 함수
#pragma once
#include "header.h"


void key_down(unsigned char KEY, int x, int y);
void key_up(unsigned char KEY, int x, int y);
void mouse_button(int button, int state, int x, int y);
void mouse_passive_motion(int x, int y);
void mouse_motion(int x, int y);
void timer_operation(int value);