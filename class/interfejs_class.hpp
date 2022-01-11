#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Interfejs{
protected:
    sf::Vector2f bounds;
    sf::Text* goraLewy;
    sf::Font* czcionka;
    void inicjuj();
public:
    Interfejs(sf::Vector2f _bounds);
    Interfejs();
    void draw(sf::RenderWindow& _okno);
    void update(std::string _goraLewy);
};

void Interfejs::inicjuj() {
    czcionka = new sf::Font;
    if (!czcionka->loadFromFile("fonts/vikingfont.ttf"))
        return;

    goraLewy = new sf::Text;

    goraLewy->setFont(*czcionka);
    goraLewy->setCharacterSize(18);
    goraLewy->setPosition(10, 5);
    goraLewy->setFillColor(sf::Color::Black);
    goraLewy->setStyle(sf::Text::Bold);
    goraLewy->setString("DEBUG");
}

void Interfejs::update(const std::string _goraLewy) {
    goraLewy->setString(_goraLewy);
}

Interfejs::Interfejs(sf::Vector2f _bounds) :bounds(_bounds) {
    this->inicjuj();
}

Interfejs::Interfejs() {
    this->bounds.x = 476.0;
    this->bounds.y = 476.0;
    this->inicjuj();
}

void Interfejs::draw(sf::RenderWindow& okno) {
    okno.draw(*goraLewy);
}



class gameOver :public sf::Text {
private:
    sf::Font czcionka;
public:
    gameOver() {
        if (!czcionka.loadFromFile("fonts/vikingfont.ttf"))
            return;

        this->setFont(czcionka);
        this->setCharacterSize(50);
        this->setPosition(30, 200);
        this->setFillColor(sf::Color::Red);
        this->setStyle(sf::Text::Bold);
        this->rotate(5);
        this->setString("GAME OVER");
    }
};

int CD(sf::Clock zegar_pocisk){
    if(zegar_pocisk.getElapsedTime().asSeconds() < 1){
        return 2;
    }
    else if(zegar_pocisk.getElapsedTime().asSeconds() >= 1 && zegar_pocisk.getElapsedTime().asSeconds()< 2){
        return 1;
    }
    else if(zegar_pocisk.getElapsedTime().asSeconds() >= 2){
        return 0;
    }
}