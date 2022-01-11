#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Pocisk{
private:
    sf::Sprite pocisk;
    sf::Texture tekstura_pocisk;
    sf::Vector2f position_pocisk;
    sf::Vector2f vel = {1.0f, 1.0f};
    sf::IntRect ksztalt_pocisk;
public:
    explicit Pocisk(Player);
    void move_pocisk(float);
    sf::Sprite& getPocisk(){ return pocisk;};
    void set_pocisk(Player);
    bool warunek_pocisk();
    sf::Vector2f getPos_pocisk() { return pocisk.getPosition(); }
    void respawn_pocisk();
};

Pocisk::Pocisk(Player p){
    tekstura_pocisk.loadFromFile("textures/fireball.png");
    ksztalt_pocisk = sf::IntRect({0, 0, 512, 512});
    position_pocisk.x = -100.0f;
    position_pocisk.y = -50.0f;
    pocisk = sf::Sprite (tekstura_pocisk, ksztalt_pocisk);
    pocisk.setPosition(position_pocisk);
    pocisk.setScale(0.2f, 0.2f);
}

void Pocisk::set_pocisk(Player p) {
    position_pocisk.x = p.getPos().x;
    position_pocisk.y = p.getPos().y;
    pocisk.setPosition(position_pocisk);
}

void Pocisk::move_pocisk(float dx){
    sf::Vector2f pos;
    ksztalt_pocisk.top = 0;
    if(ksztalt_pocisk.left == 3072)
        ksztalt_pocisk.left = 0;
    else
        ksztalt_pocisk.left += 512;
    pocisk.setTextureRect(ksztalt_pocisk);

    if(position_pocisk.x<=480){
        pos.x = dx * vel.x;
        pocisk.move(pos);
    }
}

bool Pocisk::warunek_pocisk() {
    if(pocisk.getPosition().x >=480 || pocisk.getPosition().x <= -10)
    {
        return false;
    }
    else
        return true;
}

void Pocisk::respawn_pocisk() {
    position_pocisk.x = -100.0f;
    position_pocisk.y = -50.0f;
    pocisk.setPosition(position_pocisk);
}