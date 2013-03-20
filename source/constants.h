#ifndef TEXTTENNIS_CONSTANTS_H_
#define TEXTTENNIS_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"
#include "parameter.h"

extern Parameter<float> param_angular_damping;
extern Parameter<float> param_angular_velocity;
extern Parameter<float> param_ball_cartoon_factor;
extern Parameter<ofVec2f> param_ball_initial_position;
extern Parameter<float> param_ball_mass;
extern Parameter<float> param_ball_radius;
extern Parameter<int> param_box2d_velocity_iterations;
extern Parameter<int> param_box2d_position_iterations;
extern Parameter<float> param_ceiling_height;
extern Parameter<float> param_court_length;
extern Parameter<float> param_court_thickness;
extern Parameter<float> param_default_angle;
extern Parameter<float> param_default_angular_velocity;
extern Parameter<float> param_delta_time;
extern Parameter<float> param_density;
extern Parameter<float> param_frame_rate;
extern Parameter<float> param_friction;
extern Parameter<float> param_gravity;
extern Parameter<b2Vec2> param_gravity_vector;
extern Parameter<float> param_half_court_length;
extern Parameter<float> param_half_court_thickness;
extern Parameter<float> param_half_net_thickness;
extern Parameter<float> param_half_window_width;
extern Parameter<float> param_high_hit_mean;
extern Parameter<float> param_hit_variance;
extern Parameter<float> param_linear_damping;
extern Parameter<float> param_low_hit_mean;
extern Parameter<long> param_max_balls;
extern Parameter<float> param_net_height;
extern Parameter<float> param_net_thickness;
extern Parameter<float> param_racket_radius;
extern Parameter<float> param_racket_speed;
extern Parameter<ofVec2f> param_racket1_high_hit_direction;
extern Parameter<ofVec2f> param_racket1_low_hit_direction;
extern Parameter<ofVec2f> param_racket1_start_position;
extern Parameter<ofVec2f> param_racket2_high_hit_direction;
extern Parameter<ofVec2f> param_racket2_low_hit_direction;
extern Parameter<ofVec2f> param_racket2_start_position;
extern Parameter<float> param_restitution;
extern Parameter<int> param_save_every_n_frames;
extern Parameter<ofMatrix4x4> param_view_matrix;
extern Parameter<ofMatrix4x4> param_view_matrix_inverse;
extern Parameter<int> param_window_height;
extern Parameter<int> param_window_width;

#endif  // TEXTTENNIS_CONSTANTS_H_
