// OpenGL에 필요한 헤더 파일 모음 및 프로젝트 전역 변수 모음
#pragma once
#include "shader.h"
#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "translate.h"
#include "gl_func.h"
#include "Framework.h"
#include "math_util.h"
#define START_MODE _play_

extern int WIDTH, HEIGHT;  // 윈도우 사이즈

extern GLfloat ratio;  // 윈도우 종횡비
extern GLfloat mx, my, cam_rotation, cam_x, cam_y;  // 마우스 위치, 화면 회전 각도, 카메라 위치
extern int font;