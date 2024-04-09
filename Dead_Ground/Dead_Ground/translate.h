// 변환
#pragma once
#include "header.h"
#include "Framework.h"


extern glm::vec3 cam_pos, cam_dir, cam_up;
extern glm::mat4 result, view, projection, s_mat, r_mat, t_mat, cam_mat;
extern GLfloat alpha;

extern unsigned int projection_location, view_location, model_location, viewpos_location, transperancy_location;


void set_view();
void get_player_position(Framework* ptr);
void fix_image_at(GLfloat x, GLfloat y);

glm::mat4 move_image(GLfloat x, GLfloat y);
glm::mat4 rotate_image(GLfloat rad);
glm::mat4 scale_image(GLfloat x, GLfloat y);

void init_transform();