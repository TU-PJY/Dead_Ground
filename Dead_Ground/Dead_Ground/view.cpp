#include "gl_header.h"


// 변환 관련 변수들을 여기에 선언 및 사용
glm::vec3 cam_pos, cam_dir, cam_up;
glm::mat4 result_matrix, view, projection, scale_matrix, rotate_matrix, translate_matrix, cam_matrix;
GLfloat transparent, ratio;

unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location, object_color_location;


void set_view() {  // 시점 세팅
    using namespace glm;

    view = mat4(1.0f);

    cam_pos = vec3(0.0f, 0.0f, 1.0f);
    cam_dir = -normalize(cam_pos);
    cam_up = vec3(0.0f, 1.0f, 0.0f);

    projection = mat4(1.0f);

    view = lookAt(cam_pos, cam_pos + cam_dir, cam_up);
    view = translate(view, vec3(0.0, -0.4, 0.0));
   
    auto ptr = framework[layer_player][0];  // 플레이어는 항상 플레이어 레이어의 가장 첫 번째 인덱스
    if (ptr != nullptr) {  // 플레이어 클래스로부터 위치를 받아 카메라 위치 업데이트
        view = rotate(view, radians(cam_rotation), vec3(0.0, 0.0, 1.0));
        view = translate(view, vec3(-(ptr->get_x()), -(ptr->get_y()), 0.0));
    }

    ratio = 1.0 * WIDTH / HEIGHT;

    projection = ortho(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0, -100.0, 100.0);
}


void get_player_position() {
    auto ptr = framework[layer_player][0];  // 플레이어는 항상 플레이어 레이어의 가장 첫 번째 인덱스

    if (ptr != nullptr) {
        cam_x = ptr->get_x();
        cam_y = ptr->get_y();
    }
}


void init_transform() {  // 변환 초기화
    using namespace glm;

    result_matrix = mat4(1.0f);  // 최종 행렬

    scale_matrix = mat4(1.0f);  // 신축 행렬
    rotate_matrix = mat4(1.0f);  // 회전 행렬
    translate_matrix = mat4(1.0f);  // 이동 행렬

    transparent = 1.0f;
}