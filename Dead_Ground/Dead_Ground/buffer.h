// 버퍼 초기화
#pragma once
#include "header.h"


extern GLuint VBO;


void set_canvas(GLuint &VAO);
void set_text(GLuint &VAO);

void set_texture(unsigned int &tex, const char* directory, int width, int height, int channel);
void draw_image(unsigned int tex, GLuint VAO);

GLvoid build_font(const char* fontName, int fontSize);
GLvoid build_text(int fontSize);
GLvoid kill_text(GLvoid);
int set_text(int size);
GLvoid draw_text(GLuint VAO, unsigned int tex, int size, const char* fmt, ...);