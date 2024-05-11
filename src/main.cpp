#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "time.h"

#include "ball.h"
#include "circle.h"
#include "util.h"
#include "info.h"
// #include <bits/stdc++.h>
#include <map>
#include <utility>
#include <vector>

// using namespace std;


const int screen_w = 800;
const int screen_h = 800;
const int circle_R = 300;
const int ball_R   = 7;
const int NumberOfBalls = 1;
const int relativeX = screen_w / 2;// - circle_R / 2;
const int relativeY = screen_h / 2;// - circle_R / 2;

std :: map<std :: pair<int, int>, std :: vector<int>> mp;

void preProcess() {
  sf::Image image;
    if (!image.loadFromFile("/home/layman/layman/Projects/ChaosticMusic/img/aha.jpeg"))
    {
        // Handle loading error
        printf("FAILEd\n");
        return;
    }

    // Get dimensions of the image
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;

    // Iterate over each pixel of the image
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // Get the color of the pixel at position (x, y)
            int ax = x + relativeX - width / 2, ay = y + relativeY - height / 2;
            sf::Color color = image.getPixel(x, y);
            mp[{ax, ay}] = {color.r, color.g, color.b, color.a};
        }
    }
    printf("Loaded all the pixels\n");
}



sf::Color generateRainbowColor(float position) {
    int i = position * 6;
    float f = position * 6 - i;
    float q = 1 - f;
    switch(i % 6){
        case 0: return sf::Color(255, 255 * f, 0); break;
        case 1: return sf::Color(255 * q, 255, 0); break;
        case 2: return sf::Color(0, 255, 255 * f); break;
        case 3: return sf::Color(0, 255 * q, 255); break;
        case 4: return sf::Color(255 * f, 0, 255); break;
        case 5: return sf::Color(255, 0, 255 * q); break;
    }
    return sf::Color();
}


bool kk = false;
sf::Color generateRandomColor() {
    // Seed the random number generator with the current time
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random values for red, green, and blue components
    sf::Uint8 r = std::rand() % 255;
    sf::Uint8 g = std::rand() % 255;
    sf::Uint8 b = std::rand() % 255;
    if (kk) {
      g = 200;
      kk = false;
    } else {
      r = 200;
      kk = true;
    }
    return sf::Color(r, g, b);
}

sf::Vector2f generateRandomPosition() {
    // Seed the random number generator with the current time
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random x and y coordinates
    int xCenter = screen_w / 2;
    int yCenter = screen_h / 2;
    int xLimit  = xCenter - circle_R / 2; 
    int yLimit  = yCenter - circle_R / 2; 

    float x = static_cast<float>(std::rand() % circle_R + xLimit);
    float y = static_cast<float>(std::rand() % circle_R / 2 + yLimit);
    return sf::Vector2f(x, y);
}

int getRandomInt(int a, int b) {
  return 30;
  int diff = b - a;
  return std :: rand() % diff + a;
}


void myMusic(bool ok, sf :: Music &music, sf :: Clock &clock, int cnt) {
  float second = clock.getElapsedTime().asMilliseconds();
  if (ok and music.getStatus() != sf :: Music :: Playing) {
    music.play();
    clock.restart();
  } else if (second > cnt + 50 and cnt < 300) {
    music.pause();
  }
}
int tot = 0;
void drawPainting(sf :: RenderTexture &t, sf :: Vector2f pos, Ball &B) {
  
  sf :: Color pixelColor;
  if (mp.count({pos.x, pos.y})) {
    // if (tot % 100) return;
    std :: vector<int> cc = mp[{pos.x, pos.y}];
    int fac = 45;
    int r = cc[0];//std :: max(fac, cc[0]);
    int g = cc[1];//std :: max(fac, cc[1]);
    int b = cc[2];//cc[2];//std :: max(fac, cc[2]);
    int a = cc[3]- cc[3] * 0.2;
    // g = 255;
    pixelColor = sf :: Color(r, g, b, a);
  } else {
    pixelColor = B.getFillColor();
    pixelColor.a = 0;
  }
  // pixelColor = sf :: Color :: Red;
  sf::RectangleShape point(sf::Vector2f(1.f, 1.f)); 
  point.setOutlineThickness(0.01f);
  point.setPosition(pos.x, pos.y);
  point.setFillColor(pixelColor);

  t.draw(point);
  // t.display();
}



int main()
{
    preProcess();
    sf :: Clock clock;

    int xCenter = screen_w / 2;
    int yCenter = screen_h / 2;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(screen_w, screen_h), "Chaotic Universe", sf :: Style :: Default);
    
    window.setFramerateLimit(2000);

    
    
    Info info;

    std :: vector<Ball> allBalls(NumberOfBalls);
    Circle circle;
    circle.setRadius(circle_R);
    circle.setPosition(xCenter, yCenter);

    int i = 0;
    for (auto &newBall : allBalls) {
      // i++;
      newBall.setFillColor(generateRandomColor());
      newBall.setRadius(getRandomInt(ball_R, 3 * ball_R));
      auto center = generateRandomPosition();
      newBall.setPosition(center.x, center.y);
      newBall.setInitialPosition(center.x, center.y);


      // newBall.print();
    }
    // exit(0);
    int loopCounter = 1;
    bool start = false;

    
    std :: string audioFilePath = "/home/layman/layman/Projects/SFML/audio/chipchip.wav";

    sf :: Music music;

    // if (!music.openFromFile(audioFilePath)) {
    //   printf("Failed to load the music file\n");
    //   return EXIT_FAILURE;
    // }

    sf :: Texture texture;
    sf :: RenderTexture RT;

    RT.create(screen_w, screen_h);
    sf::Sprite sprite;
    
    // sprite.setPosition(sf :: Vector2f(100, 100));
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();                     
        }      
        
      
        if (sf :: Keyboard::isKeyPressed(sf ::Keyboard :: Space)) {
          start = true;
        }

        if (!start) {
          continue;
        }
        // clear the window with black color
        window.clear(sf :: Color::Black);
             
        circle.draw(window);
        
        info.draw(window);
        sprite.setTexture(RT.getTexture());
        window.draw(sprite);   

        for (auto &B : allBalls) {
          B.draw(window); // drawing the ball on the window and lines on the texture
          auto pos = B.getCenter();
          drawPainting(RT, pos, B);
          B.motion();    
          
          if (IsCollision(B, circle)) {  
              // myMusic(true, music, clock, info.getCollisionCount());
              B.increaseRadius();   
              while(IsCollision(B, circle)) {
                B.motion(-1);
              }   
              
              
              info.increaseCollisionCount();    
             
              handleCollision(B, circle);
              
              if ((int)allBalls.size() < 50) {
                  Ball newB;
                  newB = B;
                  auto vel = B.getVelocity();

                  float eps = 0.5;      
                  float RR = B.getRadius() / (2.0f);
                  newB.setRadius(RR);
                  B.setRadius(RR);
                  newB.setVelocity(vel.x + eps, vel.y + eps);
                  B.setVelocity(vel.x, vel.y);
                  allBalls.push_back(newB);
                  break;
                }
          }
          // myMusic(false, music, clock, info.getCollisionCount());                                        
        }   
        RT.display();
        window.display();
    }

    return 0;
}