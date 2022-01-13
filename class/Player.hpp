#pragma once
#include <SFML/Graphics.hpp>
#include <random>
//GRACZ
class Player{
private:
    sf::Sprite gracz;
    sf::Texture tekstura;
    sf::Vector2f position;
    sf::Vector2f vel = { 1.1f, 1.1f};
    sf::IntRect ksztalt;
public:
    Player(float x, float y);
    void moveW(float x, float y);
    void moveA(float x, float y);
    void moveS(float x, float y);
    void moveD(float x, float y);
    sf::Sprite& getPlayer(){ return gracz; }
    sf::Vector2f getPos() { return gracz.getPosition(); }
};

