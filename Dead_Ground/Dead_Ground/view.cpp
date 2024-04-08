#include "gl_header.h"


// 변환 관련 변수들을 여기에 선언 및 사용
glm::vec3 cam_pos, cam_dir, cam_up;
glm::mat4 result_matrix, view, projection, scale_matrix, rotate_matrix, translate_matrix, cam_matrix;
GLfloat transparent;

unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location;

// 플레이어 위치로 카메라 추적
void get_player_position(Framework* ptr) {
    cam_x = ptr->get_x();
    cam_y = ptr->get_y();
}


void set_view() {  // 시점 세팅
    using namespace glm;

    view = mat4(1.0f);
    projection = mat4(1.0f);

    cam_pos = vec3(0.0f, 0.0f, 1.0f);
    cam_dir = vec3(0.0, 0.0, 0.0);
    cam_up = vec3(0.0f, 1.0f, 0.0f);

    view = lookAt(cam_pos, cam_dir, cam_up);
    view = translate(view, vec3(0.0, -0.4, 0.0));
   
    auto ptr = fw_set_tracking(layer_player, 0);  // 플레이어는 항상 플레이어 레이어의 가장 첫 번째 인덱스
    if (ptr != nullptr)   // 플레이어 클래스로부터 위치를 받아 카메라 위치 업데이트
        get_player_position(ptr);

    view = rotate(view, radians(cam_rotation), vec3(0.0, 0.0, 1.0));
    view = translate(view, vec3(-cam_x, -cam_y, 0.0));
    

    projection = ortho(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0, -100.0, 100.0);
}

// 오브젝트가 특정 위치에 계속 출력되도록 변환하는 함수
void fix_image_at(GLfloat x, GLfloat y) {
    using namespace glm;

    translate_matrix = translate(translate_matrix, vec3(cam_x, cam_y, 0.0));
    translate_matrix = rotate(translate_matrix, radians(-cam_rotation), vec3(0.0, 0.0, 1.0));
    translate_matrix = translate(translate_matrix, vec3(x, y, 0.0));
}


glm::mat4 move_image(GLfloat x, GLfloat y) {
    using namespace glm;
    mat4 matrix{ mat4(1.0f) };
    matrix = translate(matrix, vec3(x, y, 0.0));
    return matrix;
}


glm::mat4 rotate_image(GLfloat rad) {
    using namespace glm;
    mat4 matrix{ mat4(1.0f) };
    matrix = rotate(matrix, radians(rad), vec3(0.0, 0.0, 1.0));
    return matrix;
}


glm::mat4 scale_image(GLfloat x, GLfloat y) {
    using namespace glm;
    mat4 matrix{ mat4(1.0f) };
    matrix = scale(matrix, vec3(x, y, 0.0));
    return matrix;
}


void init_transform() {  // 변환 초기화
    using namespace glm;

    result_matrix = mat4(1.0f);  // 최종 행렬

    scale_matrix = mat4(1.0f);  // 신축 행렬
    rotate_matrix = mat4(1.0f);  // 회전 행렬
    translate_matrix = mat4(1.0f);  // 이동 행렬

    transparent = 1.0f;
}