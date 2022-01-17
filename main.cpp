#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasy.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(476.0, 476.0), "Projekt Semestralny Gry");
    window.setFramerateLimit(60);
    Interfejs* interfejs = new Interfejs(true);
    Menu menu(window.getSize().x, window.getSize().y);
    Healthbar hp(20.0f, 0.0f);

    int trudnosc;
    int tryb_gry = 0;
    bool gra_w_toku = false;
    bool czy_otwarto_sterowanie = false;
    bool czy_zrestartowano = false;

    //ZEGARKI DO KONTROLI MECHANIK
    sf::Clock zegar_kolizja, zegar_koniec, zegar_cooldown, zegar;

    //STWORZ TLO GRY
    Background tlo_gra(window.getSize().x, window.getSize().y, true);
    Background tlo_menu(window.getSize().x, window.getSize().y, false);

    //STWORZ DANE
    Gracz dane;
    dane = generuj();
    FILE* plik;
    trudnosc = dane.trudnosc;
    Player p1;

    //STWORZ N PRZECIWNIKOW
    int liczba_przeciwnikow = 20;
    Enemy przeciwnik(liczba_przeciwnikow);

    //STWORZ POCISK
    auto *pocisk = new Pocisk();
    int cooldown_pocisku = 2;
    bool flaga_pocisk= false;

    while (window.isOpen())
    {

        sf::Event event;
        if(tryb_gry==1)
        {
            //CZAS DANEJ SESJI
            if(zegar.getElapsedTime().asSeconds()>=1.0f)
            {
                dane.czas += 1;
                zegar.restart();
            }
            //OBSLUGA COOLDOWNU POCISKU W INTERFEJSIE
            cooldown_pocisku = CD(zegar_cooldown);

            //STEROWANIE GRACZEM
            p1 = poruszaj_graczem(p1, window, 2.0f);

            //OBSLUGA KOLIZJI PRZECIWNIK - PLAYER
            if(przeciwnik.kolizja_gracz(p1, liczba_przeciwnikow) && zegar_kolizja.getElapsedTime().asSeconds() > 1.0f){
                dane.zycie -= 1;
                zegar_kolizja.restart();
            }

            //OBSLUGA POCISKU oraz KOLIZJI PRZECIWNIK - POCISK
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && zegar_cooldown.getElapsedTime().asSeconds() > 2.0f){
                pocisk->set_pocisk(p1);
                flaga_pocisk = true;
                zegar_cooldown.restart();
            }
            obsluga_pocisku(zegar_cooldown, pocisk, flaga_pocisk);
            if(przeciwnik.kolizja_pocisk(*pocisk, liczba_przeciwnikow)){
                dane.scores += 1;
                pocisk->respawn_pocisk();
            }

            //OBSLUGA POZIOMU TRUDNOSCI
            obsluga_trudnosci(&przeciwnik, trudnosc);
        }


        ////=========================================================================================================\\\\


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                //POWROT DO MENU Z OKNA GRY
                if (event.key.code == sf::Keyboard::Escape && tryb_gry == 1){
                    tryb_gry = 0;
                }
                //OTWORZ STEROWANIE
                if(event.key.code == sf::Keyboard::F1 && tryb_gry == 1) {
                    tryb_gry = 2;
                }

                //PRZESUWAJ SIĘ PO REKORDACH MENU
                menu = poruszaj_menu(menu, event);

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
                            trudnosc = dane.trudnosc;
                            tryb_gry = 1;
                            break;
                        case 2:
                            tryb_gry = 2;
                            break;
                        case 3:
                            tryb_gry = 3;
                            break;
                        case 4:
                            tryb_gry = 4;
                            break;
                        case 5:
                            tryb_gry = 5;
                            break;
                    }
                }
            }
        }

        window.clear();

        //WYJSCIE Z GRY
        if(tryb_gry == 5)
        {
            menu.potwierdzenie_wyjscia(window.getSize().x, window.getSize().y);
            window.clear();
            tlo_menu.draw(window);
            menu.draw(window);
            if(event.key.code == sf::Keyboard::Enter)
            {
                switch (menu.getRekord())
                {
                    case 1:
                        window.close();
                        break;
                    case 2:
                        menu.reset_indeks(5);
                        tryb_gry = 0;
                        break;
                }
            }
        }

        //WYBOR POZIOMU TRUDNOSCI
        if(tryb_gry == 4)
        {
            menu.poziomtrudnosci(window.getSize().x, window.getSize().y);
            window.clear();
            tlo_menu.draw(window);
            menu.draw(window);

            if(event.key.code == sf::Keyboard::Enter)
            {
                switch (menu.getRekord())
                {
                    case 1:
                        trudnosc = 1;
                        dane = poziom(6, 1);
                        przeciwnik.restart();
                        p1.restart(50,200);
                        menu.reset_indeks(4);
                        tryb_gry = 0;
                        break;
                    case 2:
                        trudnosc = 2;
                        dane = poziom(3, 2);
                        przeciwnik.restart();
                        p1.restart(50,200);
                        menu.reset_indeks(4);
                        tryb_gry = 0;
                        break;
                    case 3:
                        trudnosc = 3;
                        dane = poziom(1, 3);
                        przeciwnik.restart();
                        p1.restart(50,200);
                        menu.reset_indeks(4);
                        tryb_gry = 0;
                        break;
                }
            }
        }

        //ZAPISZ DO PLIKU
        if(tryb_gry == 3)
        {
            plik = fopen("dane.dat", "w+b");
            zapiszDane(plik, dane);
            tryb_gry = 0;
        }

        //START GRY
        if(tryb_gry==1 || (czy_otwarto_sterowanie && gra_w_toku))
        {
            tlo_gra.draw(window);
            interfejs->rysuj_interfejs(window);
            interfejs->update("\nPunkty: " + std::to_string(dane.scores),"Czas sesji: "+std::to_string(dane.czas)+"s\n" + "Cooldown: " + std::to_string(cooldown_pocisku) + "s");
            window.draw(hp.getHealthbar());
            hp.update_hp(dane);
            window.draw(p1.getPlayer());
            przeciwnik.drawEnemy(window);
            if(flaga_pocisk)
                window.draw(pocisk->getPocisk());

            if(dane.zycie <= 0)
            {
                gameOver* end = new gameOver;
                if(!czy_zrestartowano)
                {
                    zegar_koniec.restart();
                    czy_zrestartowano = true;
                }
                window.draw(*end);
                if(zegar_koniec.getElapsedTime().asSeconds() > 2.0f)
                {
                    tryb_gry = 0;
                    delete end;
                    gra_w_toku = false;
                    dane = generuj();
                    przeciwnik.restart();
                    p1.restart(50,200);
                    dane = set_trudnosc(trudnosc, dane);
                    czy_zrestartowano = false;
                }
            }
        }

        //POKAZ STEROWANIE
        if(tryb_gry == 2)
        {
            Interfejs* opcje = new Interfejs(false);
            opcje->rysuj_opcje(window);
            czy_otwarto_sterowanie = true;

            if (event.key.code == sf::Keyboard::Escape && gra_w_toku)
            {
                delete opcje;
                czy_otwarto_sterowanie = false;
                tryb_gry = 1;
            }
            else if (event.key.code == sf::Keyboard::Escape && !gra_w_toku)
            {
                delete opcje;
                czy_otwarto_sterowanie = false;
                tryb_gry = 0;
            }
        }

        //POKAZ MENU GLOWNE
        if(tryb_gry==0)
        {
            window.clear();
            tlo_menu.draw(window);
            menu.menuglowne(window.getSize().x, window.getSize().y);
            menu.draw(window);
        }
        window.display();
    }
    return 0;
}