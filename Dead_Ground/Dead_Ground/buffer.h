// 버퍼 초기화
#pragma once
#include "header.h"


extern GLuint VBO;

void input_canvas();
void set_parameteri();
void set_canvas(GLuint &VAO);
void set_texture(unsigned int &tex, const char* directory, int width, int height, int channel);