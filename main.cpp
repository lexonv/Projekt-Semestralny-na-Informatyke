#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.hpp"

int main() {
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(476.0, 476.0), "Szkieletor Atakuje");
    Interfejs* oknoGlowne = new Interfejs(sf::Vector2f(476.0, 476.0)); // zad 1

    sf::Texture background_texture;
    sf::IntRect background(0,0,476.0,476.0);
    background_texture.loadFromFile("textures/background.png"); //tło to placeholder
    sf::Sprite background1(background_texture, background);
    Gracz dane;
    dane = generuj();
    FILE* plik;
    Menu menu(window.getSize().x, window.getSize().y);
    int menu_selected_flag = 0;
    bool gra_w_toku = false;

    Player p1(50, 200);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //MENU
            if (event.type == sf::Event::KeyPressed)
            {
                //DEBUG INTERFEJS
                if(event.key.code == sf::Keyboard::C){
                    dane.zycie = dane.zycie - 1;
                    std::cout<<"dane.zycie = "<<dane.zycie<<std::endl;
                }
                if(event.key.code == sf::Keyboard::V){
                    dane.scores = dane.scores + 10;
                    std::cout<<"dane.scores = "<<dane.scores<<std::endl;
                }
                if(event.key.code == sf::Keyboard::P){
                    std::cout<<"!Aktualne dane!"<<std::endl;
                    std::cout<<"dane.zycie = "<<dane.zycie<<std::endl;
                    std::cout<<"dane.scores = "<<dane.scores<<std::endl;
                }

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


                if (event.key.code == sf::Keyboard::Escape && menu_selected_flag == 1){
                    menu_selected_flag = 0;
                }


                if(event.key.code == sf::Keyboard::F1 && menu_selected_flag == 1) {
                   menu_selected_flag = 2;
                }


                if (menu_selected_flag == 0)
                {
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
                    {
                        gra_w_toku = true;
                        menu_selected_flag = 1;
                    }

                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
                    {
                        std::cout << "Wczytaj zapis..."<< std::endl;
                        dane = wczytajDane(plik, dane);
                        menu_selected_flag = 1;
                    }
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
                    {
                        std::cout << "Pomoc..."<< std::endl;
                        menu_selected_flag = 2;

                    }
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3) {
                        menu_selected_flag = 4;
                    }
                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 4) {
                        std::cout << "Trudnosc..."<< std::endl;
                        menu_selected_flag = 3;
                    }

                    if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 5)
                    {
                        std::cout << "Koniec gry..." << std::endl;
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
        //zapisz do pliku
        if(menu_selected_flag == 4){
            std::cout << "Zapisz..."<< std::endl;
            plik = fopen("dane.dat", "w+b");
            zapiszDane(plik, dane);
            menu_selected_flag = 0;
        }

        //wybor poziomu
        if(menu_selected_flag == 3){
            menu.poziomtrudnosci(window.getSize().x, window.getSize().y);
            window.clear();
            menu.draw(window);
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1) {
                std::cout << "Wybrano Poziom Latwy"<< std::endl;
                dane = poziom(4);
                menu_selected_flag = 0;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2) {
                std::cout << "Wybrano Poziom Normalny"<< std::endl;
                dane = poziom(2);
                menu_selected_flag = 0;
            }
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3) {
                std::cout << "Wybrano Poziom Trudny"<< std::endl;
                dane = poziom(1);
                menu_selected_flag = 0;
            }
        }
        //pokaz sterowanie
        if(menu_selected_flag == 2){
            menu.pomoc(window.getSize().x, window.getSize().y);
            window.clear();
            menu.draw(window);
            if ((event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 5 && gra_w_toku == true)
            || (event.key.code == sf::Keyboard::Escape && gra_w_toku == true))
            {
                menu_selected_flag = 1;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 5 && gra_w_toku == false)
            {
                menu_selected_flag = 0;
            }
        }

        //rozpocznij gre
        if(menu_selected_flag==1){
            window.draw(background1);
            oknoGlowne->draw(window);
            oknoGlowne->update("Punkty zycia: " + std::to_string(dane.zycie) + "\n" + "Scores: " + std::to_string(dane.scores));
            window.draw(p1.getPlayer());
        }

        //pokaz menu glowne
        if(menu_selected_flag==0) {
            menu.menuglowne(window.getSize().x, window.getSize().y);
            window.clear();
            menu.draw(window);
        }
        window.display();
    }
    return 0;
}
