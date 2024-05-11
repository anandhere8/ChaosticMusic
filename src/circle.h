// circle

#ifndef CIRCLE_H
#define CIRCLE_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <vector>
// #include<SFML/Audio.hpp>


class Circle{
private :
  int id;
  sf :: Vector2f position;
  sf :: Vector2f center;
  sf :: Vector2f initialPosition;
  float radius;
  sf :: Color fillColor;
  sf :: Color outlineColor;
  sf :: Vector2f velocity;
  
  
  

  
  int trailHead = 0;

protected : 
  float gravity;
  float delta_t;
  float thickness;
  std :: vector<sf::Vector2f> positionVector;
  std :: vector<sf::Vector2f> trails;
public: 

  // sf :: Music bgMusic;
  Circle(float x = 0, float y = 0, 
         sf::Color fillColor = sf::Color::Transparent,
         sf::Color outlineColor = sf::Color::White, 
         float thickness = 5, 
         float radius = 100, 
         int id = 2, float g = 9.81, float delta_t = 0.01);

  void draw(sf :: RenderWindow& window);
  void draw(sf :: RenderTexture& texture);
  void draw(sf :: RenderWindow& window, sf :: RenderTexture& texture);
  void print();

  // Getters
  sf :: Vector2f getPosition() const;

  sf :: Vector2f getVelocity() const;
  sf :: Vector2f getCenter() ;

  float getRadius();
  sf :: Color getFillColor();

  // Setters
  void setPosition(float x, float y) ;

  void setInitialPosition(float x, float y);

  void setRadius(float r) ;

  void setFillColor(sf :: Color color) ;

  void setOutlineColor(sf :: Color color) ;
  void setThickness(float t) ;

  void setVelocity(float x, float y);
  void setGravity(float g);
  // void setMusic(int id);

  void updateTrail(sf:: Vector2f position);
};

#endif 