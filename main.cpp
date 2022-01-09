#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.hpp"

int main() {
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(476.0, 476.0), "Sesja egzaminacyjna");
    window.setFramerateLimit(60);

    Interfejs* interfejs = new Interfejs(sf::Vector2f(476.0, 476.0));
    Menu menu(window.getSize().x, window.getSize().y);


    Healthbar hp;

    int menu_selected_flag = 0;
    bool gra_w_toku = false;
    //STWORZ NAPIS GAMEOVER
    gameOver* end = new gameOver;
    bool czy_zrestartowano = false;

    sf::Clock zegar_kolizja, zegar_koniec, zegar_pocisk;

    //STWORZ TLO GRA
    sf::Texture background_texture;
    sf::IntRect background(0,0,476.0,476.0);
    background_texture.loadFromFile("textures/background1.png");
    sf::Sprite background1(background_texture, background);

    //STWORZ TLO MENU
    sf::Texture tlo_menu_texture;
    tlo_menu_texture.loadFromFile("textures/pg.jpeg");
    sf::Sprite tlo_menu(tlo_menu_texture, background);

    //STWORZ DANE
    Gracz dane;
    dane = generuj();
    FILE* plik;

    Player p1(50.0, 200.0);

    //STWORZ 8 PRZECIWNIKOW
    Enemy* przeciwnik1 = new Enemy();
    Enemy* przeciwnik2 = new Enemy();
    Enemy* przeciwnik3 = new Enemy();
    Enemy* przeciwnik4 = new Enemy();
    Enemy* przeciwnik5 = new Enemy();
    Enemy* przeciwnik6 = new Enemy();
    Enemy* przeciwnik7 = new Enemy();
    Enemy* przeciwnik8 = new Enemy();

    //STWORZ POCISK
    Pocisk pocisk(p1);
    bool pocisk_flaga = false;

    while (window.isOpen())
    {
        //OBSLUGA KOLIZJI PRZECIWNIK - PLAYER
        if(menu_selected_flag==1)
        {
            przeciwnik1 -> move(-2.60);
            przeciwnik2 -> move(-3.5);
            przeciwnik3 -> move(-2.75);
            przeciwnik4 -> move(-2.45);
            przeciwnik5 -> move(-2.8);
            przeciwnik6 -> move(-3.25);
            przeciwnik7 -> move(-3.5);
            przeciwnik8 -> move(-3.3);

            if((kolizja(p1, przeciwnik1) == true)||
               (kolizja(p1, przeciwnik2) == true)||
               (kolizja(p1, przeciwnik3) == true)||
               (kolizja(p1, przeciwnik4) == true)||
               (kolizja(p1, przeciwnik5) == true)||
               (kolizja(p1, przeciwnik6) == true)||
               (kolizja(p1, przeciwnik7) == true)||
               (kolizja(p1, przeciwnik8) == true))
            {
                if(zegar_kolizja.getElapsedTime().asSeconds() > 1.0f && dane.zycie > 0)
                {
                    dane.zycie = dane.zycie - 1;
                    zegar_kolizja.restart();
                }
            }

            //OBSLUGA POCISKU
            if (pocisk_flaga == true) {
                pocisk.move_pocisk(8, p1);
                zegar_pocisk.restart();
            }

            if (pocisk.warunek_pocisk() == true)
            {
                pocisk.respawn_pocisk();
                pocisk_flaga = false;
            }



            //OBSLUGA KOLIZJI POCISK - PRZECIWNIK
            if(kolizja(pocisk, przeciwnik1) == true){
                przeciwnik1->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik2) == true){
                przeciwnik2->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik3) == true){
                przeciwnik3->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik4) == true){
                przeciwnik4->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik5) == true){
                przeciwnik5->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik6) == true){
                przeciwnik6->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik7) == true){
                przeciwnik7->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }
            if(kolizja(pocisk, przeciwnik8) == true){
                przeciwnik8->respawn();
                pocisk.respawn_pocisk();
                dane.scores += 10;
            }

        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {

                //STRZELAJ POCISKIEM
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pocisk.warunek_pocisk() == true && zegar_pocisk.getElapsedTime().asSeconds() > 2.0f){
                    pocisk.set_pocisk(p1);
                    pocisk_flaga = true;
                }

                //DEBUG INTERFEJS
//                if(event.key.code == sf::Keyboard::C){
//                    dane.zycie = dane.zycie + 1;
//                }
//                if(event.key.code == sf::Keyboard::V){
//                    dane.scores = dane.scores + 10;
//                }



                //STEROWANIE MENU
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



                //POWROT DO MENU
                if (event.key.code == sf::Keyboard::Escape && menu_selected_flag == 1){
                    menu_selected_flag = 0;
                }
                
                if(event.key.code == sf::Keyboard::F1 && menu_selected_flag == 1) {
                    menu_selected_flag = 2;
                }



                //MENU GŁOWNE -WYBOR
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        p1.moveW(0,-8.0f);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    {
                        p1.moveS(0,8.0f);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        p1.moveA(-8.0f,0);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    {
                        p1.moveD(8.0f,0);
                    }
                }

            }
        }
        window.clear();



        //ZAPISZ DO PLIKU
        if(menu_selected_flag == 4){
            std::cout << "Zapisz..."<< std::endl;
            plik = fopen("dane.dat", "w+b");
            zapiszDane(plik, dane);
            menu_selected_flag = 0;
        }



        //WYBOR POZIOMU
        if(menu_selected_flag == 3){
            menu.poziomtrudnosci(window.getSize().x, window.getSize().y);
            window.clear();
            window.draw(tlo_menu);
            menu.draw(window);
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1) {
                std::cout << "Wybrano Poziom Latwy"<< std::endl;
                dane = poziom(4);
                przeciwnik1->speed(0.4);
                przeciwnik2->speed(0.4);
                przeciwnik3->speed(0.4);
                przeciwnik4->speed(0.4);
                przeciwnik5->speed(0.4);
                przeciwnik6->speed(0.4);
                przeciwnik7->speed(0.4);
                przeciwnik8->speed(0.4);
                menu_selected_flag = 0;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2) {
                std::cout << "Wybrano Poziom Normalny"<< std::endl;
                dane = poziom(2);
                przeciwnik1->speed(0.8);
                przeciwnik2->speed(0.8);
                przeciwnik3->speed(0.8);
                przeciwnik4->speed(0.8);
                przeciwnik5->speed(0.8);
                przeciwnik6->speed(0.8);
                przeciwnik7->speed(0.8);
                przeciwnik8->speed(0.8);
                menu_selected_flag = 0;
            }
            if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3) {
                std::cout << "Wybrano Poziom Trudny"<< std::endl;
                dane = poziom(1);
                przeciwnik1->speed(1.2);
                przeciwnik2->speed(1.2);
                przeciwnik3->speed(1.2);
                przeciwnik4->speed(1.2);
                przeciwnik5->speed(1.2);
                przeciwnik6->speed(1.2);
                przeciwnik7->speed(1.2);
                przeciwnik8->speed(1.2);
                menu_selected_flag = 0;
            }
        }



        //POKAZ STEROWANIE
        if(menu_selected_flag == 2){
            menu.pomoc(window.getSize().x, window.getSize().y);
            window.clear();
            window.draw(tlo_menu);
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



        //START GRY
        if(menu_selected_flag==1){
            window.draw(background1);
            interfejs->draw(window);
            interfejs->update("\n Scores: " + std::to_string(dane.scores));
            window.draw(hp.getHealthbar());
            hp.update_hp(dane);
            window.draw(p1.getPlayer());
            window.draw(przeciwnik1->getEnemy());
            window.draw(przeciwnik2->getEnemy());
            window.draw(przeciwnik3->getEnemy());
            window.draw(przeciwnik4->getEnemy());
            window.draw(przeciwnik5->getEnemy());
            window.draw(przeciwnik6->getEnemy());
            window.draw(przeciwnik7->getEnemy());
            window.draw(przeciwnik8->getEnemy());
            window.draw(pocisk.getPocisk());

            //WARUNEK KONCA GRY #GAME_OVER
            if(dane.zycie <= 0)
            {
                if(czy_zrestartowano == false)
                {
                    zegar_koniec.restart();
                    czy_zrestartowano = true;
                }
                window.draw(*end);
                if(zegar_koniec.getElapsedTime().asSeconds() > 2.0f)
                    window.close();
            }

        }



        //POKAZ MENU GLOWNE
        if(menu_selected_flag==0){
            window.clear();
            window.draw(tlo_menu);
            menu.menuglowne(window.getSize().x, window.getSize().y);
            menu.draw(window);
        }
        window.display();
    }
    return 0;
}