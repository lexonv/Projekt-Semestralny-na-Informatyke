#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


class Menu
{

private:
    sf::Font font;
    sf::Text menu[6];//maksymalna liczba poziomow
    int selectedItem = 0;
    int max_poziom = 6;

public:
    Menu(float width, float height);
    void przesunG();//przesun do gory
    void przesunD();//przesun w dol
    int getSelectedItem() { return selectedItem; }//zwroc poziom menu
    void draw(sf::RenderWindow &window);
    void pomoc(float width, float height);
    void menuglowne(float width, float height);
    void poziomtrudnosci(float width, float height);
};

Menu::Menu(float width, float height){
    if (!font.loadFromFile("fonts/vikingfont.ttf"))
    {
        std::cout<<"ER00R"<<std::endl;
        return;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Graj");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Sterowanie");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Zapisz");
    menu[3].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 4));

    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Trudnosc");
    menu[4].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 5));

    menu[5].setFont(font);
    menu[5].setFillColor(sf::Color::Red);
    menu[5].setString("Wyjscie");
    menu[5].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 6));
}

void Menu::poziomtrudnosci(float width, float height) {
    max_poziom = 4;
    if(selectedItem == 0){
        menu[selectedItem]=menu[1];
    }
    if(selectedItem>3){
        selectedItem = 0;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Sesja:");
    menu[0].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Zerowa");
    menu[1].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Podstawowa");
    menu[2].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Poprawkowa");
    menu[3].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 4));
}

void Menu::menuglowne(float width, float height) {
    max_poziom = 6;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Graj");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Sterowanie");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Zapisz");
    menu[3].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 4));
    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Trudnosc");
    menu[4].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 5));
    menu[5].setFont(font);
    menu[5].setFillColor(sf::Color::Red);
    menu[5].setString("Wyjscie");
    menu[5].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 6));
}

void Menu::pomoc(float width, float height){
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("W - gora");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("A - lewo");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("S - dol");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("D - prawo");
    menu[3].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 4));
    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Spacja - strzal");
    menu[4].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 5));
    menu[5].setFont(font);
    menu[5].setFillColor(sf::Color::Red);
    menu[5].setString("Wyjscie");
    menu[5].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 6));
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < max_poziom; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::przesunG()
{
    if (selectedItem >= 0 && selectedItem < max_poziom)
    {
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = max_poziom - 1;
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < max_poziom)
    {
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= max_poziom)
            selectedItem = 0;
        menu[selectedItem].setStyle(sf::Text::Bold);
    }
}

void myDelay(int opoznienie)
{
    sf::Clock zegar;
    sf::Time czas;
    while (true)
    {
        czas = zegar.getElapsedTime();
        if (czas.asMilliseconds() > opoznienie)
        {
            zegar.restart();
            break;
        }
    }
}