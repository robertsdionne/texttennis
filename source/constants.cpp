#include <Box2D/Box2D.h>

#include "constants.h"
#include "ofMain.h"
#include "parameter.h"

DEFINE_PARAMETER(float, param_angular_damping, 0.1);
DEFINE_PARAMETER(float, param_angular_velocity, 100.0);
DEFINE_PARAMETER(float, param_aspect_ratio, [] () {
  return static_cast<float>(param_window_width) / static_cast<float>(param_window_height);
});
DEFINE_PARAMETER(float, param_ball_cartoon_factor, 2.0);
DEFINE_PARAMETER(ofVec2f, param_ball_initial_position, ofVec2f(11, 1));
DEFINE_PARAMETER(float, param_ball_mass, 0.056);
DEFINE_PARAMETER( float, param_ball_radius, [] () {
  return param_ball_cartoon_factor * 0.03429;
});
DEFINE_PARAMETER(int, param_box2d_velocity_iterations, 8);
DEFINE_PARAMETER(int, param_box2d_position_iterations, 3);
DEFINE_PARAMETER(float, param_ceiling_height, 100.0);
DEFINE_PARAMETER(float, param_court_height, [] () {
  return param_court_length / param_aspect_ratio;
});
DEFINE_PARAMETER(float, param_court_length, 23.78);
DEFINE_PARAMETER(float, param_court_thickness, 0.5);
DEFINE_PARAMETER(float, param_default_angle, 0.0);
DEFINE_PARAMETER(float, param_default_angular_velocity, 0.0);
DEFINE_PARAMETER(float, param_delta_time, [] () {
  return 1.0 / param_frame_rate;
});
DEFINE_PARAMETER(float, param_density, [] () {
  return param_ball_mass / M_PI / param_ball_radius / param_ball_radius;
});
DEFINE_PARAMETER(float, param_frame_rate, 60.0);
DEFINE_PARAMETER(float, param_friction, 0.3);
DEFINE_PARAMETER(float, param_gravity, 9.81);
DEFINE_PARAMETER(b2Vec2, param_gravity_vector, [] () {
  return b2Vec2(0.0, -param_gravity);
});
DEFINE_PARAMETER(float, param_half_court_height, [] () {
  return param_court_height / 2.0;
});
DEFINE_PARAMETER(float, param_half_court_length, [] () {
  return param_court_length / 2.0;
});
DEFINE_PARAMETER(float, param_half_court_thickness, [] () {
  return param_court_thickness / 2.0;
});
DEFINE_PARAMETER(float, param_half_net_thickness, [] () {
  return param_ball_radius / 2.0;
});
DEFINE_PARAMETER(float, param_half_window_width, []() {
  return param_window_width / 2.0;
});
DEFINE_PARAMETER(float, param_high_hit_mean, 10.0);
DEFINE_PARAMETER(float, param_hit_variance, 0.05);
DEFINE_PARAMETER(float, param_linear_damping, 0.1);
DEFINE_PARAMETER(float, param_low_hit_mean, 13.0);
DEFINE_PARAMETER(int, param_max_balls, 500);
DEFINE_PARAMETER(float, param_net_height, 0.914);
DEFINE_PARAMETER(float, param_net_thickness, [] () {
  return param_ball_radius;
});
DEFINE_PARAMETER(float, param_racket_radius, [] () {
  return param_ball_cartoon_factor * 0.1155;
});
DEFINE_PARAMETER(float, param_racket_speed, 0.15);
DEFINE_PARAMETER(ofVec2f, param_racket1_high_hit_direction, ofVec2f(1.0, 1.0).normalized());
DEFINE_PARAMETER(ofVec2f, param_racket1_low_hit_direction, ofVec2f(1.0, 0.5).normalized());
DEFINE_PARAMETER(ofVec2f, param_racket1_start_position, [] () {
  return ofVec2f(-8, param_court_thickness + param_racket_radius);
});
DEFINE_PARAMETER(ofVec2f, param_racket2_high_hit_direction, ofVec2f(-1.0, 1.0).normalized());
DEFINE_PARAMETER(ofVec2f, param_racket2_low_hit_direction, ofVec2f(-1.0, 0.5).normalized());
DEFINE_PARAMETER(ofVec2f, param_racket2_start_position, [] () {
  return ofVec2f(8, param_court_thickness + param_racket_radius);
});
DEFINE_PARAMETER(float, param_restitution, 0.728);
DEFINE_PARAMETER(int, param_save_every_n_frames, 2);
DEFINE_PARAMETER(ofMatrix4x4, param_view_matrix,[] () {
  return ofMatrix4x4::newScaleMatrix(param_window_width / param_court_length,
                                     -param_window_width / param_court_length, 1) *
      ofMatrix4x4::newTranslationMatrix(param_half_window_width, param_window_height, 0.0);
});
DEFINE_PARAMETER(ofMatrix4x4, param_view_matrix_inverse, [] () {
  return ofMatrix4x4::getInverseOf(param_view_matrix);
});
DEFINE_PARAMETER(int, param_window_height, 600);
DEFINE_PARAMETER(int, param_window_width, 1200);
