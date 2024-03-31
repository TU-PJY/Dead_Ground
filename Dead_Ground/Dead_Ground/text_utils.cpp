#include "gl_header.h"


HDC hDC;              // Private GDI Device Context
HGLRC hRC;            // Permanent Rendering Context
HWND hWnd;            // Holds Our Window Handle
HINSTANCE hInstance;  // Holds The Instance Of The Application
GLuint  base;  // Base Display List For The Font Set


GLfloat canvas_text[][48] = {  // �ؽ�Ʈ ��¿� ����� canvas
	-0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0,
	0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
	-0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0,
	-0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0
};


void set_text(GLuint& VAO) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(canvas_text), canvas_text, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0); // ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat))); // �ؽ�ó ��ǥ �Ӽ� 
	glEnableVertexAttribArray(2);
}


GLvoid build_font(const char* fontName, int fontSize) {
	HFONT   font;     // Windows Font ID
	HFONT   oldfont;  // Used For Good House Keeping

	base = glGenLists(96);  // Storage For 96 Characters

	font = CreateFont(-fontSize, // Height Of Fonts
		0,              // Width Of Font
		0,              // Angle Of Escapement
		0,              // Orientation Angle
		FW_NORMAL,        // Font Weight
		FALSE,          // Italic     (��Ҽ�)
		FALSE,          // Underline (����)
		FALSE,          // Strikeout (��Ҽ�)
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


GLvoid build_text(int fontSize) {
	build_font("Arial", fontSize);
}


GLvoid kill_text(GLvoid) {                     // Delete The Font List
	glDeleteLists(base, 96);                // Delete All 96 Characters
}


int set_text(int size) {                     // All Setup For OpenGL Goes Here
	hDC = wglGetCurrentDC();            // ���� openGL �������� hDC�� �����´�.
	build_text(size);       // Build The Font

	return TRUE;                        // Initialization Went OK
}


GLvoid draw_text(GLuint VAO, unsigned int tex, int size, const char* fmt, ...) { // Custom GL "Print" Routin
	set_text(size);

	result_matrix = rotate_matrix * translate_matrix * scale_matrix;  // ���� ��ȯ

	transperancy_location = glGetUniformLocation(ID, "transparency");
	glUniform1f(transperancy_location, transparent);

	projection_location = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);

	view_location = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);

	viewpos_location = glGetUniformLocation(ID, "viewPos"); // viewPos �� ����: ī�޶� ��ġ
	glUniform3f(viewpos_location, cam_pos.x, cam_pos.y, cam_pos.z);

	object_color_location = glGetUniformLocation(ID, "objectColor");
	glUniform3f(object_color_location, 1.0, 1.0, 1.0);

	model_location = glGetUniformLocation(ID, "model"); // ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(result_matrix)); // ��ȯ �� �����ϱ�

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

