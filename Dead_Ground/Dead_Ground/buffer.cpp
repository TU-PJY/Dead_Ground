﻿#include "gl_header.h"


GLuint VBO;
unsigned char* texture_data;  // 텍스처 저장에 사용되는 임시 변수

GLfloat canvas[][48] = {  // 이미지 출력에 사용할 canvas
	-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0,
	0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0,
	0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	-0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0,
	-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0
};


void input_vertex() {  // 이미지 출력 목적으로 사용되므로 모두 같은 버텍스를 버퍼에 저장한다.
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(canvas), canvas, GL_STATIC_DRAW);
}


void set_parameteri() {  // 텍스처 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}