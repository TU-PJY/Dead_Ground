// 변환
#pragma once
#include "header.h"


extern glm::vec3 cameraPos, cameraDirection, cameraUp, lightPos, objColor;
extern glm::mat4 transformMatrix, view, projection, lightMatrix, scaleMatrix, rotateMatrix, translateMatrix, camMaxtrix;
extern glm::vec3 selectedColor, threshold;
extern GLfloat transparent, ratio;

extern unsigned int projectionLocation, viewLocation, modelLocation, viewPosLocation;
extern unsigned int lightPosLocation, lightColorLocation, objColorLocation;
extern unsigned int colorLocation, thresholdLocation;
extern unsigned int transparencyLocation;


void setWindowView();
void initTransform();
void transmit();
