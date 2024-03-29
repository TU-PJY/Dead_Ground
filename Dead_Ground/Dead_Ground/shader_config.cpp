// 셰이더 프로그램 생성
#include "gl_header.h"


GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;
GLuint ID;


char* load_buffer(const char* file) {
	FILE* fptr; long length; char* buf;

	fptr = fopen(file, "rb");
	if (!fptr) return NULL;

	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}


void set_vertex_shader() {
	vertexSource = load_buffer("GLSL_vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader err\n" << errorLog << std::endl;
		return;
	}
}


void set_fragment() {
	fragmentSource = load_buffer("GLSL_fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader err\n" << errorLog << std::endl;
		return;
	}
}

void set_shader() {
	set_vertex_shader();
	set_fragment();
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(ID);
}
