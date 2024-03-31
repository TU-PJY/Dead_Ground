#pragma once
#include "header.h"

void set_text(GLuint& VAO);
GLvoid build_font(const char* fontName, int fontSize);
GLvoid build_text(int fontSize);
GLvoid kill_text(GLvoid);
int set_text(int size);
GLvoid draw_text(GLuint VAO, unsigned int tex, int size, const char* fmt, ...);