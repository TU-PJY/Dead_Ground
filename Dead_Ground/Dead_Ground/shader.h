// 셰이더 프로그램 생성
#pragma once
#include "header.h"


extern GLchar* vertexSource, * fragmentSource;
extern GLuint vertexShader, fragmentShader;
extern GLuint ID;


char* load_buffer(const char* file);
void set_shader();
