// 버퍼 초기화
#pragma once
#include "header.h"

extern GLuint VBO;
extern unsigned char* texture_data;


void set_canvas(GLuint &VAO);
void set_text_canvas(GLuint &VAO);

void set_texture(unsigned int &tex, const char* directory, int width, int height, int channel);
void draw_image(unsigned int tex, GLuint VAO);

GLvoid build_font(const char* fontName, int fontSize, int type);
GLvoid build_text(int fontSize, int type);
GLvoid kill_text(GLvoid);
int set_text(int size, int type);
GLvoid draw_text(GLuint VAO, unsigned int tex, int size, const char* fmt, int type, ...);