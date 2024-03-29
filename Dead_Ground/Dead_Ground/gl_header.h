// OpenGL에 필요한 헤더 파일 모음 및 프로젝트 전역 변수 모음
#pragma once
#include "shader.h"
#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "translate.h"
#include "gl_func.h"
#include "Framework.h"
#include "stb_image.h"

#define START_MODE _play_

extern int WIDTH, HEIGHT;  // 윈도우 사이즈

extern GLfloat ratio;  // 윈도우 종횡비
extern GLfloat mx, my, map_rotation;  // 마우스 위치, 회면 회전 각도

// 플레이어 움직임 여부
extern GLfloat player_move_up, player_move_down, player_move_right, player_move_left;
extern GLfloat player_x, player_y;