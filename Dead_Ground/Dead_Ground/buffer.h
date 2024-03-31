// 버퍼 초기화
#pragma once
#include "header.h"


extern GLuint VBO;


void set_canvas(GLuint &VAO);
void set_text(GLuint &VAO);

void set_texture(unsigned int &tex, const char* directory, int width, int height, int channel);
void draw_image(unsigned int tex, GLuint VAO);

GLvoid BuildFont(const char* fontName, int fontSize);
GLvoid BuildFontWithEnum(int fontSize);
GLvoid KillFont(GLvoid);
GLvoid glPrint(GLuint VAO, unsigned int tex, const char* fmt, ...);
int InitFont(GLvoid);