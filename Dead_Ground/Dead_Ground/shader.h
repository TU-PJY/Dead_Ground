// 셰이더 프로그램 생성
#pragma once
#include "header.h"


extern GLchar* vertex_source, * fragment_source;
extern GLuint vertex_shader, fragment_shader;
extern GLuint ID;


char* load_buffer(const char* file);
void set_shader();
