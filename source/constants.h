#ifndef TEXTTENNIS_CONSTANTS_H_
#define TEXTTENNIS_CONSTANTS_H_

#include <Box2D/Box2D.h>
#include <string>

#include "ofMain.h"
#include "parameter.h"

extern Parameter<float> angular_damping;
extern Parameter<float> angular_velocity;
extern Parameter<float> aspect_ratio;
extern Parameter<float> ball_cartoon_factor;
extern Parameter<ofVec2f> ball_initial_position;
extern Parameter<ofVec2f> ball_initial_velocity;
extern Parameter<float> ball_mass;
extern Parameter<float> ball_radius;
extern Parameter<int> ball_trail_length;
extern Parameter<int> ball_trail_length_scholar;
extern Parameter<int> box2d_velocity_iterations;
extern Parameter<int> box2d_position_iterations;
extern Parameter<float> ceiling_height;
extern Parameter<float> court_height;
extern Parameter<float> court_length;
extern Parameter<float> court_thickness;
extern Parameter<float> default_angle;
extern Parameter<float> default_angular_velocity;
extern Parameter<float> delta_time;
extern Parameter<float> density;
extern Parameter<std::string> font_filename;
extern Parameter<float> frame_rate;
extern Parameter<float> friction;
extern Parameter<float> gravity;
extern Parameter<b2Vec2> gravity_vector;
extern Parameter<float> half_court_height;
extern Parameter<float> half_court_length;
extern Parameter<float> half_court_thickness;
extern Parameter<float> half_net_thickness;
extern Parameter<float> half_window_width;
extern Parameter<float> high_hit_mean;
extern Parameter<float> hit_variance;
extern Parameter<float> linear_damping;
extern Parameter<float> low_hit_mean;
extern Parameter<int> max_balls;
extern Parameter<float> max_balls_goal;
extern Parameter<float> max_balls_goal_fraction;
extern Parameter<float> net_height;
extern Parameter<float> net_thickness;
extern Parameter<float> player_move_smooth_factor;
extern Parameter<float> racket_radius;
extern Parameter<float> racket_speed;
extern Parameter<ofVec2f> racket_diagonal_hit_direction;
extern Parameter<ofVec2f> racket1_high_hit_direction;
extern Parameter<ofVec2f> racket1_low_hit_direction;
extern Parameter<ofVec2f> racket1_start_position;
extern Parameter<ofVec2f> racket2_high_hit_direction;
extern Parameter<ofVec2f> racket2_low_hit_direction;
extern Parameter<ofVec2f> racket2_start_position;
extern Parameter<float> rect_line_width;
extern Parameter<float> restitution;
extern Parameter<int> save_every_n_frames;
extern Parameter<float> sound_volume_rate;
extern Parameter<ofMatrix4x4> view_matrix;
extern Parameter<ofMatrix4x4> view_matrix_inverse;
extern Parameter<int> window_height;
extern Parameter<int> window_width;

#endif  // TEXTTENNIS_CONSTANTS_H_
