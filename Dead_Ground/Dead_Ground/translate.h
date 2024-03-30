// 변환
#pragma once
#include "header.h"


extern glm::vec3 cam_pos, cam_dir, cam_up;
extern glm::mat4 result_matrix, view, projection, scale_matrix, rotate_matrix, translate_matrix, cam_matrix;
extern GLfloat transparent, ratio;

extern unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location;


void set_view();
void init_transform();
void transmit();
