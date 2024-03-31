#include "gl_header.h"
#define DEFAULTFONTSIZE 40

HDC hDC;              // Private GDI Device Context
HGLRC hRC;            // Permanent Rendering Context
HWND hWnd;            // Holds Our Window Handle
HINSTANCE hInstance;  // Holds The Instance Of The Application
GLuint  base;  // Base Display List For The Font Set

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

GLfloat canvas_text[][48] = {  // 텍스트 출력에 사용할 canvas
	-0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0,
	0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	-0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0,
	-0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0
};


void set_canvas(GLuint &VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(canvas), canvas, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // 위치 속성
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // 텍스처 좌표 속성 
	glEnableVertexAttribArray(2);
}


void set_text(GLuint &VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(canvas_text), canvas_text, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // 위치 속성
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // 텍스처 좌표 속성 
	glEnableVertexAttribArray(2);
}


void set_texture(unsigned int &tex, const char* directory, int width, int height, int channel) {
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture_data = stbi_load(directory, &width, &height, &channel, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
}


void draw_image(unsigned int tex, GLuint VAO) {
	result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // 최종 변환

	transperancy_location = glGetUniformLocation(ID, "transparency");
	glUniform1f(transperancy_location, transparent);

	projection_location = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);

	view_location = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);

	viewpos_location = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
	glUniform3f(viewpos_location, cam_pos.x, cam_pos.y, cam_pos.z);

	object_color_location = glGetUniformLocation(ID, "objectColor");
	glUniform3f(object_color_location, 1.0, 1.0, 1.0);

	model_location = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(result_matrix)); // 변환 값 적용하기

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


GLvoid BuildFont(const char* fontName, int fontSize) {
	HFONT   font;     // Windows Font ID
	HFONT   oldfont;  // Used For Good House Keeping

	base = glGenLists(96);  // Storage For 96 Characters

	font = CreateFont(-fontSize, // Height Of Fonts
		0,              // Width Of Font
		0,              // Angle Of Escapement
		0,              // Orientation Angle
		FW_BOLD,        // Font Weight
		FALSE,          // Italic     (취소선)
		FALSE,          // Underline (밑줄)
		FALSE,          // Strikeout (취소선)
		ANSI_CHARSET,   // Character Set Identifier
		OUT_TT_PRECIS,  // Output Precision
		CLIP_DEFAULT_PRECIS,        // Clipping Precision
		ANTIALIASED_QUALITY,        // Output Quality
		FF_DONTCARE | DEFAULT_PITCH,  // Family And Pitch
		fontName);         // Font Name

	oldfont = (HFONT)SelectObject(hDC, font); // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);     // Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);               // Selects The Font We Want
	DeleteObject(font);                       // Delete The Font
}


GLvoid BuildFontWithEnum(int fontSize) {
	BuildFont("Helvetica", fontSize);
}


GLvoid KillFont(GLvoid) {                     // Delete The Font List
	glDeleteLists(base, 96);                // Delete All 96 Characters
}


GLvoid glPrint(GLuint VAO, unsigned int tex, const char* fmt, ...) { // Custom GL "Print" Routin
	result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // 최종 변환

	transperancy_location = glGetUniformLocation(ID, "transparency");
	glUniform1f(transperancy_location, transparent);

	projection_location = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);

	view_location = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);

	viewpos_location = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
	glUniform3f(viewpos_location, cam_pos.x, cam_pos.y, cam_pos.z);

	object_color_location = glGetUniformLocation(ID, "objectColor");
	glUniform3f(object_color_location, 1.0, 1.0, 1.0);

	model_location = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(result_matrix)); // 변환 값 적용하기

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, tex);
	glRasterPos3f(0.0, 0.0, 0.0);

	char        text[256];          // Holds Our String
	va_list     ap;                 // Pointer To List Of Arguments

	if (fmt == NULL)                // If There's No Text
		return;                     // Do Nothing

	va_start(ap, fmt);              // Parses The String For Variables
	vsprintf(text, fmt, ap);    // And Converts Symbols To Actual Numbers
	va_end(ap);                     // Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits
	glListBase(base - 32);                  // Sets The Base Character to 32

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text
	glPopAttrib();                      // Pops The Display List Bits
}


int InitFont(GLvoid) {                     // All Setup For OpenGL Goes Here
	glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
	hDC = wglGetCurrentDC();            // 현재 openGL 윈도우의 hDC를 가져온다.
	BuildFontWithEnum(DEFAULTFONTSIZE);       // Build The Font

	return TRUE;                        // Initialization Went OK
}
