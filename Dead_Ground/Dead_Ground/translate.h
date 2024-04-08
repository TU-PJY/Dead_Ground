// 변환
#pragma once
#include "header.h"
#include "Framework.h"


extern glm::vec3 cam_pos, cam_dir, cam_up;
extern glm::mat4 result_matrix, view, projection, scale_matrix, rotate_matrix, translate_matrix, cam_matrix;
extern GLfloat transparent;

extern unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location;


void set_view();
void get_player_position(Framework* ptr);
void set_object_static(GLfloat x, GLfloat y);

glm::mat4 move_image(GLfloat x, GLfloat y);
glm::mat4 rotate_image(GLfloat rad);
glm::mat4 scale_image(GLfloat x, GLfloat y);

void init_transform();