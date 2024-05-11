#include "info.h"

void Info :: setCollisionCounter(int counter) {
  collisionCounter = counter;
}

Info :: Info(std :: string fontPath){
  if (!font.loadFromFile(fontPath)) {
    printf("Failed to load the font\n.");
    exit(0);
  }
  collisionCounter = 0;
  printf("Font loaded successfully.");
}

void Info :: increaseCollisionCount() {
  collisionCounter += 1;
}

void Info ::draw(sf :: RenderWindow& window) {
  text.setFont(font);
  std :: string collisionStr = "Collision Count : " + std :: to_string(collisionCounter);
  text.setString(collisionStr);
  text.setCharacterSize(10); // in pixels
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  text.setPosition(20, 20);
  window.draw(text);
}

int Info :: getCollisionCount() {
  return collisionCounter;
}