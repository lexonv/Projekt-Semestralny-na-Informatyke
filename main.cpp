#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.hpp"

int main() {
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(476.0, 476.0), "Szkieletor Atakuje");

    sf::Texture background_texture;
    sf::IntRect background(0,0,476.0,476.0);
    background_texture.loadFromFile("textures/background.png"); //tło to placeholder
    sf::Sprite background1(background_texture, background);

    interfejsTekst* int1 = new interfejsTekst(sf::Vector2f(476.0, 476.0), &window);

    Menu menu(window.getSize().x, window.getSize().y);
    int menu_selected_flag = 0;

    Player p1(100, 100);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //MENU
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    myDelay(250);
                    menu.przesunG();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    myDelay(250);
                    menu.przesunD();
                }
                if (event.key.code == sf::Keyboard::Escape){
                    menu_selected_flag = 0;
                }
                if (menu_selected_flag == 0)
                {
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
                    {
                        menu_selected_flag = 1;
                    }

                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
                    {
                        std::cout << "Kontrola piłki przez WASD:" <<"\n"<<"W - "<<"Ruch w górę"<<"\n"<<"S - "<<"Ruch w dół"<<"\n"<<"A - "<<"Ruch w prawo"<<"\n"<<"D - "<<"Ruch w lewo"<<"\n"<< std::endl;

                    }
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
                    {
                        std::cout << "Zapisywanie..."<< std::endl;

                    }

                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
                    {
                        std::cout << "Koniec gry..." << std::endl;
                        menu_selected_flag = 1;
                        window.close();
                    }
                }


                //STEROWANIE
                if(menu_selected_flag == 1)
                {
                    if (event.key.code == sf::Keyboard::W)
                    {
                        p1.moveW(0,-20.0f);
                    }
                    if (event.key.code == sf::Keyboard::A)
                    {
                        p1.moveA(-20.0f,0);
                    }
                    if (event.key.code == sf::Keyboard::S)
                    {
                        p1.moveS(0,20.0f);
                    }
                    if (event.key.code == sf::Keyboard::D)
                    {
                        p1.moveD(20.0f,0);
                    }
                }
            }
        }
        window.clear();
        if(menu_selected_flag==1){
            window.draw(background1);
            window.draw(p1.getPlayer());
        }
        if(menu_selected_flag==0) {
            window.clear();
            menu.draw(window);
        }
        window.display();
    }
    return 0;
}
