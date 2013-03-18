#ifndef TEXTTENNIS_CONSTANTS_H_
#define TEXTTENNIS_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"

constexpr int kHalfWindowWidth = 600;

constexpr int kWindowWidth = 2 * kHalfWindowWidth;

constexpr int kWindowHeight = 600;

constexpr float kAngularDamping = 0.1;

constexpr float kAngularVelocity = 100.0;

constexpr float kBallCartoonFactor = 2.0;

const ofVec2f kBallInitialPosition = ofVec2f(11, 1);

constexpr float kBallMass = 0.056;

constexpr float kBallRadius = kBallCartoonFactor * 0.03429;

constexpr int kBox2dVelocityIterations = 8;

constexpr int kBox2dPositionIterations = 3;

constexpr float kCeilingHeight = 100.0;

constexpr float kCourtLength = 23.78;

constexpr float kCourtThickness = 0.5;

constexpr float kDefaultAngle = 0.0;

constexpr float kDefaultAngularVelocity = 0.0;

constexpr float kDeltaTime = 1.0 / 60.0;

constexpr float kDensity = kBallMass / M_PI / kBallRadius / kBallRadius;

constexpr float kFrameRate = 1.0 / kDeltaTime;

constexpr float kFriction = 0.3;

constexpr float kGravity = 9.81;

const b2Vec2 kGravityVector = b2Vec2(0.0, -kGravity);

constexpr float kHalfCourtLength = kCourtLength / 2.0;

constexpr float kHalfCourtThickness = kCourtThickness / 2.0;

constexpr float kHalfNetThickness = kBallRadius / 2.0;

constexpr float kHighHitMean = 10.0;

constexpr float kHitVariance = 0.05;

constexpr float kLinearDamping = 0.1;

constexpr float kLowHitMean = 13.0;

constexpr long kMaxBalls = 500;

constexpr float kNetHeight = 0.914;

constexpr float kNetThickness = kBallRadius;

constexpr float kRacketRadius = kBallCartoonFactor * 0.1155;

const ofVec2f kRacket1HighHitDirection = ofVec2f(1.0, 1.0).normalized();

const ofVec2f kRacket1LowHitDirection = ofVec2f(1.0, 0.5).normalized();

const ofVec2f kRacket1StartPosition = ofVec2f(-8, kCourtThickness + kRacketRadius);

const ofVec2f kRacket2HighHitDirection = ofVec2f(-1.0, 1.0).normalized();

const ofVec2f kRacket2LowHitDirection = ofVec2f(-1.0, 0.5).normalized();

const ofVec2f kRacket2StartPosition = ofVec2f(8, kCourtThickness + kRacketRadius);

constexpr float kRacketSpeed = 0.15;

constexpr float kRestitution = 0.728;

constexpr int kSaveEveryNFrames = 2;

const ofMatrix4x4 kViewMatrix =
    ofMatrix4x4::newScaleMatrix(kWindowWidth / kCourtLength, -kWindowWidth / kCourtLength, 1) *
        ofMatrix4x4::newTranslationMatrix(kHalfWindowWidth, kWindowHeight, 0.0);

const ofMatrix4x4 kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

#endif
