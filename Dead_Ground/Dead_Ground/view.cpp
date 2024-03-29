#include "gl_header.h"


// 변환 관련 변수들을 여기에 선언 및 사용
glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos, objColor;
glm::mat4 transformMatrix, view, projection, lightMatrix, scaleMatrix, rotateMatrix, translateMatrix, camMaxtrix;
glm::vec3 selectedColor, threshold;
GLfloat transparent, ratio;

unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
unsigned int lightPosLocation, lightColorLocation, objColorLocation;
unsigned int colorLocation, thresholdLocation;
unsigned int transparencyLocation;


void setWindowView() {  // 시점 세팅
    using namespace glm;

    view = mat4(1.0f);

    cameraPos = vec3(0.0f, 0.0f, 1.0f);
    cameraDirection = -normalize(cameraPos);
    cameraUp = vec3(0.0f, 1.0f, 0.0f);

    projection = mat4(1.0f);

    view = lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
    view = translate(view, vec3(0.0, -0.45, 0.0));
    view = rotate(view, radians(map_rotation), vec3(0.0, 0.0, 1.0));

    auto ptr = framework[layer_player][0];  // 플레이어는 항상 플레이어 레이어의 가장 첫 번째 인덱스
    if(ptr != nullptr)  // 플레이어 클래스로부터 위치를 받아 카메라 위치 업데이트
        view = translate(view, vec3(-(ptr->get_x()), -(ptr->get_y()), 0.0));

    ratio = 1.0 * WIDTH / HEIGHT;

    projection = ortho(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0, -100.0, 100.0);
}


void initTransform() {  // 변환 초기화
    using namespace glm;

    transformMatrix = mat4(1.0f);  // 최종 행렬

    scaleMatrix = mat4(1.0f);  // 신축 행렬
    rotateMatrix = mat4(1.0f);  // 회전 행렬
    translateMatrix = mat4(1.0f);  // 이동 행렬

    transparent = 1.0f;
}


void transmit() {  // glsl 코드로 변환 데이터 전달
    transparencyLocation = glGetUniformLocation(ID, "transparency");
    glUniform1f(transparencyLocation, transparent);

    projectionLocation = glGetUniformLocation(ID, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

    viewLocation = glGetUniformLocation(ID, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

    objColorLocation = glGetUniformLocation(ID, "objectColor");
    glUniform3f(objColorLocation, 1.0, 1.0, 1.0);

    viewPosLocation = glGetUniformLocation(ID, "viewPos"); // viewPos 값 전달: 카메라 위치
    glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

    modelLocation = glGetUniformLocation(ID, "model"); // 버텍스 세이더에서 모델링 변환 위치 가져오기
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transformMatrix)); // 변환 값 적용하기
}
