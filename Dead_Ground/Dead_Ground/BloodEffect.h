#pragma once
#include "gl_header.h"

// 플레이어 대미지 효과 이펙트 클래스
class BloodEffect : public Framework {
private:
	GLuint VAO{};
	unsigned int tex{};
	GLfloat transparency = 0.7f;
	int layer{};

public:
	void render() {
		using namespace glm;
		init_transform();
		set_object_static(0.0, 0.4);
		translate_matrix = scale(translate_matrix, vec3(10.0 * ratio, 10.0, 0.0));
		transparent = transparency;
		draw_image(tex, VAO);
	}

	void update() {
		// 점차 투명해지며 완전히 투명해지면 삭제된다
		transparency -= ft;
		if (transparency < 0)
			fw_delete(this, layer);
	}

	void check_collision() {}

	BloodEffect(int l) {
		layer = l;

		set_canvas(VAO);
		set_texture(tex, "res//ui//spr_blood.png", 280, 158, 1);
	}

};