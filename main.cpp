#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(476.0, 476.0), "Sesja egzaminacyjna");
    sf::Event event;
    window.setFramerateLimit(60);
    Interfejs* interfejs = new Interfejs(sf::Vector2f(476.0, 476.0));
    Menu menu(window.getSize().x, window.getSize().y);
    Healthbar hp;
    int time = 0;

    int trudnosc;
    int tryb_gry = 0;
    bool gra_w_toku = false;

    //STWORZ NAPIS GAMEOVER
    gameOver* end = new gameOver;
    bool czy_zrestartowano = false;

    //ZEGARKI DO KONTROLI MECHANIK
    sf::Clock zegar_kolizja, zegar_koniec, zegar_pocisk, zegar;

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
    trudnosc = dane.trudnosc;
    Player p1(50.0, 200.0);

    //STWORZ N PRZECIWNIKOW
    int liczba_przeciwnikow = 10;
    Enemy przeciwnik(liczba_przeciwnikow);

    //STWORZ POCISK
    Pocisk pocisk(p1);
    int cooldown = 2;
    bool flaga_pocisk= false;

    while (window.isOpen())
    {

        if(tryb_gry==1)
        {
            //Czas grania
            if(zegar.getElapsedTime().asSeconds()>1.0f)
            {
                time+=1;
                dane.czas = time;
                zegar.restart();
            }

            //STEROWANIE GRACZEM
            p1 = poruszaj_graczem(p1, window, 1.5f);

            //OBSLUGA KOLIZJI PRZECIWNIK - PLAYER
            if(przeciwnik.kolizja_gracz(p1, liczba_przeciwnikow) && zegar_kolizja.getElapsedTime().asSeconds() > 1.0f)
            {
                dane.zycie -= 1;
                zegar_kolizja.restart();
            }

            //OBSLUGA KOLIZJI POCISK - PRZECIWNIK
            if(przeciwnik.kolizja_pocisk(pocisk, liczba_przeciwnikow) == true){
                dane.scores += 1;
                pocisk.respawn_pocisk();
            }

            //OBSLUGA COOLDOWNU POCISKU W INTERFEJSIE
            cooldown = CD(zegar_pocisk);

            //OBSLUGA POCISKU
            if(flaga_pocisk == true && pocisk.warunek_pocisk() == true){
                pocisk.move_pocisk(8);
                zegar_pocisk.restart();
            }
            else if(pocisk.warunek_pocisk() == false && flaga_pocisk == true)
            {
                flaga_pocisk = false;
                pocisk.respawn_pocisk();
            }

            //OBSLUGA POZIOMU TRUDNOSCI
            if(gra_w_toku = true)
            {
                switch(trudnosc)
                {
                    case 1:
                        przeciwnik.move(-3);
                        break;
                    case 2:
                        przeciwnik.move(-4);
                        break;
                    case 3:
                        przeciwnik.move(-6);
                        break;
                }
            }

        }


        ////=========================================================================================================\\\\


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                //STRZELAJ POCISKIEM - USTAW FLAGE
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && zegar_pocisk.getElapsedTime().asSeconds() > 2.0f)
                {
                    pocisk.set_pocisk(p1);
                    flaga_pocisk = true;
                }

                //PRZESUWAJ SIĘ PO REKORDACH MENU
                menu = poruszaj_menu(menu, event);

                //POWROT DO MENU
                if (event.key.code == sf::Keyboard::Escape && tryb_gry == 1){
                    tryb_gry = 0;
                }

                if(event.key.code == sf::Keyboard::F1 && tryb_gry == 1) {
                    tryb_gry = 2;
                }



                //MENU GŁOWNE -WYBOR
                if (event.key.code == sf::Keyboard::Enter && tryb_gry == 0)
                {
                    switch (menu.getRekord())
                    {
                        case 0:
                            gra_w_toku = true;
                            tryb_gry = 1;
                            break;
                        case 1:
                            dane = wczytajDane(plik, dane);
                            trudnosc = wczytaj_trudnosc(dane);
                            tryb_gry = 1;
                            break;
                        case 2:
                            std::cout << "Pomoc..." << std::endl;
                            tryb_gry = 2;
                            break;
                        case 3:
                            tryb_gry = 3;
                            break;
                        case 4:
                            tryb_gry = 4;
                            break;
                        case 5:
                            window.close();
                            break;
                    }
                }
            }
        }
        window.clear();
        //WYBOR POZIOMU TRUDNOSCI
        if(tryb_gry == 4)
        {
            menu.poziomtrudnosci(window.getSize().x, window.getSize().y);
            window.clear();
            window.draw(tlo_menu);
            menu.draw(window);

            if (event.key.code == sf::Keyboard::Enter && menu.getRekord() == 1)
            {
                //latwy
                trudnosc = 1;
                dane = poziom(6, 1);
                tryb_gry = 0;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getRekord() == 2)
            {
                //sredni
                trudnosc = 2;
                dane = poziom(3, 2);
                tryb_gry = 0;
            }

            if (event.key.code == sf::Keyboard::Enter && menu.getRekord() == 3)
            {
                //trudny
                trudnosc = 3;
                dane = poziom(1, 3);
                tryb_gry = 0;
            }
        }



        //ZAPISZ DO PLIKU
        if(tryb_gry == 3)
        {
            std::cout << "Zapisz..."<< std::endl;
            plik = fopen("dane.dat", "w+b");
            zapiszDane(plik, dane);
            tryb_gry = 0;
        }



        //POKAZ STEROWANIE
        if(tryb_gry == 2)
        {
            menu.sterowanie(window.getSize().x, window.getSize().y);
            window.clear();
            window.draw(tlo_menu);
            menu.draw(window);
            if ((event.key.code == sf::Keyboard::Enter && menu.getRekord() == 5 && gra_w_toku == true)
                || (event.key.code == sf::Keyboard::Escape && gra_w_toku == true))
            {
                tryb_gry = 1;
            }

            if ((event.key.code == sf::Keyboard::Enter && menu.getRekord() == 5 && gra_w_toku == false)
                || (event.key.code == sf::Keyboard::Escape && gra_w_toku == false))
            {
                tryb_gry = 0;
            }
        }



        //START GRY
        if(tryb_gry==1)
        {
            window.draw(background1);
            interfejs->draw(window);
            interfejs->update("                   Czas sesji: "+std::to_string(time)+"s\n Punkty: " + std::to_string(dane.scores) + "   Cooldown: " + std::to_string(cooldown) + "s");
            window.draw(hp.getHealthbar());
            hp.update_hp(dane);
            window.draw(p1.getPlayer());
            przeciwnik.drawEnemy(window);
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
        if(tryb_gry==0)
        {
            window.clear();
            window.draw(tlo_menu);
            menu.menuglowne(window.getSize().x, window.getSize().y);
            menu.draw(window);
        }
        window.display();
    }
    return 0;
}