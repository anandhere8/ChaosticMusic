#include "ball.h"
#include "circle.h"
#include <math.h>
#include <SFML/Audio.hpp>

float sq(float a) {
  return a * a;
}



bool IsCollision(Ball ball, Circle Circle) {
  auto circle_center = Circle.getCenter();
  auto ball_center = ball.getCenter();
  float circle_radius = Circle.getRadius();
  float ball_radius = ball.getRadius();

  float minDistance = circle_radius - ball_radius;
  float maxDistance = circle_radius + ball_radius;

  float distance_diff = sqrt(sq(circle_center.x - ball_center.x) + sq(circle_center.y - ball_center.y));
  
  
  
  if (minDistance <= distance_diff && distance_diff <= maxDistance) {
    // Collision happens
    
    // printf("Circle_center - %f, %f\n", circle_center.x, circle_center.y);
    // printf("Ball_center - %f, %f\n", ball_center.x, ball_center.y);
    return true;
  }
  
  return false;
}


void handleCollision(Ball &ball, Circle &circle) {
  sf :: Vector2f normal = ball.getCenter() - circle.getCenter();
  float dx = normal.x;
  float dy = normal.y;

  float distance = sqrt(sq(dx) + sq(dy));

  const float eps = 1e-6;
  if (distance <= eps) {
    printf("distance is zero, there is no possiblity of collision but it happened\n");
    return;
  }
  // normalize the vector

  float nx = 0; 
  nx = dx / distance;
  float ny = 0; ny = dy / distance;

  // Calculate the reflection vector
  float velX = ball.getVelocity().x;
  float velY = ball.getVelocity().y;
  double dotProduct = velX * nx + velY * ny;
  double rx = velX - 2 * dotProduct * nx;
  double ry = velY - 2 * dotProduct * ny;

  // Update the position of the ball using the reflection vector
  double newVelX = rx;
  double newVelY = ry;
  double newX = ball.getCenter().x + newVelX;
  double newY = ball.getCenter().y + newVelY;

  // Update the position and velocity of the ball
  // ball.setPosition(newX, newY);
  ball.setVelocity(newVelX, newVelY);


  // printf("New position of the ball is - %f, %f\n", newVelX, newVelY);
}


void playSound() {
  sf :: SoundBuffer buffer;

  if (!buffer.loadFromFile("/home/layman/layman/Projects/SFML/audio/golf_ball.wav")) {
    printf("Failed to load the audio file.\n");
    // return EXIT_FAILURE;
  }
  sf :: Sound sound;
  sound.setBuffer(buffer);
  sound.play();
}
