#include "constants.h"
#include "ofMain.h"
#include "parameter.h"

auto param_angular_damping = Parameter<float>(0.1);

auto param_angular_velocity = Parameter<float>(100.0);

auto param_ball_cartoon_factor = Parameter<float>(2.0);

auto param_ball_initial_position = Parameter<ofVec2f>(ofVec2f(11, 1));

auto param_ball_mass = Parameter<float>(0.056);

auto param_ball_radius = Parameter<float>([] () {
  return param_ball_cartoon_factor * 0.03429;
});

auto param_box2d_velocity_iterations = Parameter<int>(8);

auto param_box2d_position_iterations = Parameter<int>(3);

auto param_ceiling_height = Parameter<float>(100.0);

auto param_court_length = Parameter<float>(23.78);

auto param_court_thickness = Parameter<float>(0.5);

auto param_default_angle = Parameter<float>(0.0);

auto param_default_angular_velocity = Parameter<float>(0.0);

auto param_delta_time = Parameter<float>([] () {
  return 1.0 / param_frame_rate;
});

auto param_density = Parameter<float>([] () {
  return param_ball_mass / M_PI / param_ball_radius / param_ball_radius;
});

auto param_frame_rate = Parameter<float>(60.0);

auto param_friction = Parameter<float>(0.3);

auto param_gravity = Parameter<float>(9.81);

auto param_gravity_vector = Parameter<b2Vec2>([] () {
  return b2Vec2(0.0, -param_gravity);
});

auto param_half_court_length = Parameter<float>([] () {
  return param_court_length / 2.0;
});

auto param_half_court_thickness = Parameter<float>([] () {
  return param_court_thickness / 2.0;
});

auto param_half_net_thickness = Parameter<float>([] () {
  return param_ball_radius / 2.0;
});

auto param_half_window_width = Parameter<float>([]() {
  return param_window_width / 2.0;
});

auto param_high_hit_mean = Parameter<float>(10.0);

auto param_hit_variance = Parameter<float>(0.05);

auto param_linear_damping = Parameter<float>(0.1);

auto param_low_hit_mean = Parameter<float>(13.0);

auto param_max_balls = Parameter<long>(500);

auto param_net_height = Parameter<float>(0.914);

auto param_net_thickness = Parameter<float>([] () {
  return param_ball_radius;
});

auto param_racket_radius = Parameter<float>([] () {
  return param_ball_cartoon_factor * 0.1155;
});

auto param_racket_speed = Parameter<float>(0.15);

auto param_racket1_high_hit_direction = Parameter<ofVec2f>(ofVec2f(1.0, 1.0).normalized());

auto param_racket1_low_hit_direction = Parameter<ofVec2f>(ofVec2f(1.0, 0.5).normalized());

auto param_racket1_start_position = Parameter<ofVec2f>([] () {
  return ofVec2f(-8, param_court_thickness + param_racket_radius);
});

auto param_racket2_high_hit_direction = Parameter<ofVec2f>(ofVec2f(-1.0, 1.0).normalized());

auto param_racket2_low_hit_direction = Parameter<ofVec2f>(ofVec2f(-1.0, 0.5).normalized());

auto param_racket2_start_position = Parameter<ofVec2f>([] () {
  return ofVec2f(8, param_court_thickness + param_racket_radius);
});

auto param_restitution = Parameter<float>(0.728);

auto param_save_every_n_frames = Parameter<int>(2);

auto param_view_matrix = Parameter<ofMatrix4x4>([] () {
  return ofMatrix4x4::newScaleMatrix(param_window_width / param_court_length, -param_window_width / param_court_length, 1) *
      ofMatrix4x4::newTranslationMatrix(param_half_window_width, param_window_height, 0.0);
});

auto param_view_matrix_inverse = Parameter<ofMatrix4x4>([] () {
  return ofMatrix4x4::getInverseOf(param_view_matrix);
});

auto param_window_height = Parameter<int>(600);

auto param_window_width = Parameter<int>(1200);
