#include <SFML/Graphics.hpp>

class Info{
  private :
    int collisionCounter;
    sf::Text text;
    sf :: Font font;

  public :

    Info(std :: string fontPath = "/home/layman/layman/Projects/SFML/font/pixelmix.ttf");
    void setCollisionCounter(int count);

    void draw(sf :: RenderWindow& window);
    
    void increaseCollisionCount(); 

    int getCollisionCount();
};