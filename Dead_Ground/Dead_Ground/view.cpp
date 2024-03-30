#include "gl_header.h"


// 변환 관련 변수들을 여기에 선언 및 사용
glm::vec3 cam_pos, cam_dir, cam_up;
glm::mat4 result_matrix, view, projection, scale_matrix, rotate_matrix, translate_matrix, cam_matrix;
GLfloat transparent, ratio;

unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location;


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


void init_transform() {  // 변환 초기화
    using namespace glm;

    result_matrix = mat4(1.0f);  // 최종 행렬

    scale_matrix = mat4(1.0f);  // 신축 행렬
    rotate_matrix = mat4(1.0f);  // 회전 행렬
    translate_matrix = mat4(1.0f);  // 이동 행렬

    transparent = 1.0f;
}


void transmit() {  // glsl 코드로 변환 데이터 전달
    transperancy_location = glGetUniformLocation(ID, "transparency");
    glUniform1f(transperancy_location, transparent);

    projection_location = glGetUniformLocation(ID, "projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection[0][0]);

    view_location = glGetUniformLocation(ID, "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);

    viewpos_location = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
    glUniform3f(viewpos_location, cam_pos.x, cam_pos.y, cam_pos.z);

    model_location = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
    glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(result_matrix)); // 변환 값 적용하기
}
