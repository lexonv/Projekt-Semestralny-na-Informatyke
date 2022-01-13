#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Healthbar{
private:
    sf::Sprite healthbar;
    sf::Texture tekstura;
    sf::IntRect ksztalt;
    sf::Vector2f pozycja;

public:
    Healthbar();
    sf::Sprite& getHealthbar(){return healthbar;}
    void update_hp(Gracz);
};

Healthbar::Healthbar() {
    tekstura.loadFromFile("textures/healthbar.png");
    ksztalt = sf::IntRect({0,0,630,179});
    healthbar.setTexture(tekstura);
    healthbar = sf::Sprite(tekstura, ksztalt);
    pozycja.x = 20.0f;
    pozycja.y = -5.0f;
    healthbar.setScale(0.18f, 0.18f);
    healthbar.setPosition(pozycja);
}

void Healthbar::update_hp(Gracz dane) {
    if(dane.zycie >= 6)
        ksztalt.top = 895;
    if(dane.zycie == 5)
        ksztalt.top = 710;
    if(dane.zycie == 4)
        ksztalt.top = 525;
    if(dane.zycie == 3)
        ksztalt.top = 340;
    if(dane.zycie == 2)
        ksztalt.top = 155;
    if(dane.zycie == 1)
        ksztalt.top = -30;
    healthbar.setTextureRect(ksztalt);
}