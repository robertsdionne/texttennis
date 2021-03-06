#include <Box2D/Box2D.h>

#include "constants.h"
#include "ofMain.h"
#include "parameter.h"

DEFINE_PARAMETER_RANGE(float, angular_damping, 0.1, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, angular_velocity, 200.0, -100.0, 200.0);
DEFINE_PARAMETER_RANGE(float, aspect_ratio,
                 static_cast<float>(DEPENDENCY(window_width)) /
                 static_cast<float>(DEPENDENCY(window_height)), 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, ball_cartoon_factor, 2.0, 0.0, 5.0);
DEFINE_PARAMETER(ofVec2f, ball_initial_position, ofVec2f(11.8, 2));
DEFINE_PARAMETER(ofVec2f, ball_initial_velocity,
                 (DEPENDENCY(low_hit_mean) + 0.25) * (ofVec2f(0, DEPENDENCY(half_court_height)) -
                                                     DEPENDENCY(ball_initial_position)).normalized());
DEFINE_PARAMETER_RANGE(float, ball_mass, 0.056, 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, ball_radius, DEPENDENCY(ball_cartoon_factor) * 0.03429, 0.0, 10.0);
DEFINE_PARAMETER(int, ball_trail_length, 256);
DEFINE_PARAMETER(int, ball_trail_length_scholar, 400);
DEFINE_PARAMETER_RANGE(int, box2d_velocity_iterations, 8, 1, 10);
DEFINE_PARAMETER_RANGE(int, box2d_position_iterations, 3, 1, 10);
DEFINE_PARAMETER_RANGE(float, ceiling_height, 100.0, 0.0, 100.0);
DEFINE_PARAMETER_RANGE(float, court_height,
                 DEPENDENCY(court_length) / DEPENDENCY(aspect_ratio), 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, court_length, 23.78, 0.0, 50.0);
DEFINE_PARAMETER_RANGE(float, court_thickness, 0.5, 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, default_angle, 0.0, 0.0, 2.0 * M_PI);
DEFINE_PARAMETER_RANGE(float, default_angular_velocity, 0.0, -100.0, 100.0);
DEFINE_PARAMETER_RANGE(float, delta_time, 0.9 / DEPENDENCY(frame_rate), 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, density,
                 DEPENDENCY(ball_mass) / M_PI /
                 DEPENDENCY(ball_radius) / DEPENDENCY(ball_radius), 0.0, 100.0);
DEFINE_PARAMETER(std::string, font_filename, "UbuntuMono-R.ttf");
DEFINE_PARAMETER_RANGE(float, frame_rate, 60.0, 10.0, 120.0);
DEFINE_PARAMETER_RANGE(float, friction, 0.3, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, gravity, 9.81, -10.0, 10.0);
DEFINE_PARAMETER(b2Vec2, gravity_vector, b2Vec2(0.0, -DEPENDENCY(gravity)));
DEFINE_PARAMETER_RANGE(float, half_court_height, DEPENDENCY(court_height) / 2.0, 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, half_court_length, DEPENDENCY(court_length) / 2.0, 0.0, 25.0);
DEFINE_PARAMETER_RANGE(float, half_court_thickness, DEPENDENCY(court_thickness) / 2.0, 0.0, 5.0);
DEFINE_PARAMETER_RANGE(float, half_net_thickness, DEPENDENCY(ball_radius) / 2.0, 0.0, 10.0);
DEFINE_PARAMETER(float, half_window_width, DEPENDENCY(window_width) / 2.0);
DEFINE_PARAMETER_RANGE(float, high_hit_mean, 10.0, 0.0, 50.0);
DEFINE_PARAMETER_RANGE(float, hit_variance, 0.05, 0.0, 5.0);
DEFINE_PARAMETER_RANGE(float, linear_damping, 0.1, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, low_hit_mean, 13.0, 0.0, 50.0);
DEFINE_PARAMETER_RANGE(int, max_balls, 1500, 0.0, 5000.0);
DEFINE_PARAMETER(float, max_balls_goal, DEPENDENCY(max_balls_goal_fraction) * DEPENDENCY(max_balls));
DEFINE_PARAMETER_RANGE(float, max_balls_goal_fraction, 0.8, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, net_height, 0.914, 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, net_thickness, DEPENDENCY(ball_radius), 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, player_move_smooth_factor, 0.2, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, racket_radius, DEPENDENCY(ball_cartoon_factor) * 0.1155, 0.0, 10.0);
DEFINE_PARAMETER_RANGE(float, racket_speed, 0.135, 0.0, 10.0);
DEFINE_PARAMETER(ofVec2f, racket_diagonal_hit_direction, ofVec2f(1.0, 1.5).normalized());
DEFINE_PARAMETER(ofVec2f, racket1_high_hit_direction, ofVec2f(1.0, 1.0).normalized());
DEFINE_PARAMETER(ofVec2f, racket1_low_hit_direction, ofVec2f(1.0, 0.5).normalized());
DEFINE_PARAMETER(ofVec2f, racket1_start_position,
                 ofVec2f(-8, DEPENDENCY(court_thickness) + DEPENDENCY(racket_radius)));
DEFINE_PARAMETER(ofVec2f, racket2_high_hit_direction, ofVec2f(-1.0, 1.0).normalized());
DEFINE_PARAMETER(ofVec2f, racket2_low_hit_direction, ofVec2f(-1.0, 0.5).normalized());
DEFINE_PARAMETER(ofVec2f, racket2_start_position,
                 ofVec2f(8, DEPENDENCY(court_thickness) + DEPENDENCY(racket_radius)));
DEFINE_PARAMETER_RANGE(float, rect_line_width, .1, 0, 10);
DEFINE_PARAMETER_RANGE(float, restitution, 0.728, 0.0, 2.0);
DEFINE_PARAMETER_RANGE(int, save_every_n_frames, 2, 1, 60);
DEFINE_PARAMETER_RANGE(float, sound_volume_rate, 0.01, 0, 1);
DEFINE_PARAMETER(ofMatrix4x4, view_matrix,
                 ofMatrix4x4::newScaleMatrix(DEPENDENCY(window_width) / DEPENDENCY(court_length),
                                             -DEPENDENCY(window_height) / DEPENDENCY(court_height), 1) *
                 ofMatrix4x4::newTranslationMatrix(DEPENDENCY(half_window_width),
                                                   DEPENDENCY(window_height), 0.0));
DEFINE_PARAMETER(ofMatrix4x4, view_matrix_inverse,
                 ofMatrix4x4::getInverseOf(DEPENDENCY(view_matrix)));
DEFINE_PARAMETER(int, window_height, 640);
DEFINE_PARAMETER(int, window_width, 1024);
