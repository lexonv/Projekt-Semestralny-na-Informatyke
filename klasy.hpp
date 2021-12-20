#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//Uzytkownik
class Player{
private:
    sf::Sprite gracz;
    sf::Texture tekstura;
    sf::Vector2f position;
    sf::Vector2f vel = { 1.3f, 1.3f};
    sf::IntRect ksztalt;
public:
    void moveW(float x, float y);
    void moveA(float x, float y);
    void moveS(float x, float y);
    void moveD(float x, float y);
    void pocisk();
//    void _get(float*, float*);
//    void _set(float*, float*);
    Player(float x, float y);
    sf::Sprite getPlayer(){ return gracz; }
    sf::Vector2f getPos() { return gracz.getPosition(); }
};

Player::Player(float xt, float yt){
    position.x = xt;
    position.y = yt;
    
    tekstura.loadFromFile("textures/profesor.png");
    ksztalt = sf::IntRect({0, 0, 64, 64});
    gracz = sf::Sprite (tekstura, ksztalt);
    gracz.setPosition(position);
}
void Player::pocisk() {

}
//void Player::_get(float *x_get, float *y_get){
//    *x_get = this -> x;
//    *y_get = this -> y;
//}
//
//void Player::_set(float *xt, float *yt){
//
//    this -> x = *xt;
//    this -> y = *yt;
//
//}
void Player::moveW(float xt, float yt){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;
    ksztalt.top = 0;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);

    if(getPos().y <= 0){
        pos.y = 0;
    }
    gracz.move(pos);
}

void Player::moveA(float xt, float yt){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;
    ksztalt.top = 64;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);
    if(getPos().x <=0){
        pos.x = 0;
    }
    gracz.move(pos);
}

void Player::moveS(float xt, float yt){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;

    ksztalt.top = 128;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);
    if(getPos().y >=400){
        pos.y=0;
    }
    gracz.move(pos);
}

void Player::moveD(float xt, float yt){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;
    ksztalt.top = 192;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);

    if(getPos().x >=410){
        pos.x=0;
    }
    gracz.move(pos);
}

//Koniec uzytkownika



//Menu

class Menu
{

private:
    sf::Font font;
    sf::Text menu[6];//maksymalna liczba poziomow
    int selectedItem = 0;
    int max_poziom = 6;

public:
    Menu(float width, float height);
    ~Menu() {};
    void przesunG();//przesun do gory
    void przesunD();//przesun w dol
    int getSelectedItem() { return selectedItem; }//zwroc poziom menu
    void draw(sf::RenderWindow &window);
    void pomoc(float width, float height);
    void menuglowne(float width, float height);
    void poziomtrudnosci(float width, float height);
};
void Menu::poziomtrudnosci(float width, float height) {
    max_poziom = 4;
    if(selectedItem>3){
        selectedItem = 0;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Trudnosc:");
    menu[0].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Latwy");
    menu[1].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Normalny");
    menu[2].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Trudny");
    menu[3].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 4));
}

void Menu::menuglowne(float width, float height) {
    max_poziom = 6;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Pomoc");
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
    menu[5].setFillColor(sf::Color::White);
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
    menu[5].setFillColor(sf::Color::White);
    menu[5].setString("Wyjscie");
    menu[5].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 6));
}
Menu::Menu(float width, float height){
    max_poziom = 6;
    if (!font.loadFromFile("fonts/vikingfont.ttf"))
    {
        return;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Pomoc");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Zapisz");
    menu[3].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 4));
    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Opcje");
    menu[4].setPosition(sf::Vector2f(width / 6, height / (max_poziom + 1) * 5));
    menu[5].setFont(font);
    menu[5].setFillColor(sf::Color::White);
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
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }


}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < max_poziom)
    {
        menu[selectedItem].setFillColor(sf::Color::Red);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= max_poziom)
            selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }

}

void myDelay(int opoznienie)
{
    sf::Clock zegar;
    sf::Time czas;
    while (1)
    {
        czas = zegar.getElapsedTime();
        if (czas.asMilliseconds() > opoznienie)
        {
            zegar.restart();
            break;
        }

    }
}



//class Enemy{
//private:
//    sf::Texture enemy_texture;
//    sf::Sprite *enemy;
//    sf::IntRect ksztalt;
//    int N;
//    std::random_device rd;
//public:
//    Enemy(int);
//    void updateEnemy();
//    void moveEnemy();
//    sf::Sprite getEnemy(){ return *enemy; }
//};
//

//Enemy::Enemy(int Nt){
//    std::mt19937 gen(rd());
//        std::uniform_int_distribution<> distX(1,750);
//        std::uniform_int_distribution<> distY(1,550);
//        float x=0, y=0;
//        enemy_texture.loadFromFile("textures/profesor.png");
//        N = Nt;
//        enemy = new sf::Sprite[N];
//        for (int i = 0; i < N; i++)
//        {
//            x = distX(gen);
//            y = distY(gen);
//
//            enemy[i].setTexture(enemy_texture);
//            enemy[i].setPosition(sf::Vector2f(x, y));
//            enemy[i].setScale(sf::Vector2f(0.03f, 0.03f));
//        }
//}


//INTERFEJS GRY (PUNTY ZYCIE ITD.)
//class Interfejs{
//protected:
//    sf::Vector2f bounds;
//    sf::Vector2f innerBounds;
//    sf::Text* goraLewy;
//    sf::Font* czcionka;
//    void inicjuj();
//public:
//    Interfejs(sf::Vector2f _bounds);
//    Interfejs();
//    void draw(sf::RenderWindow& _okno);
//    void update(std::string _goraLewy);
//
//};
//
//void Interfejs::inicjuj() {
//    czcionka = new sf::Font;
//    if (!czcionka->loadFromFile("fonts/vikingfont.ttf"))
//        return;
//
//    goraLewy = new sf::Text;
//
//    goraLewy->setFont(*czcionka);
//    goraLewy->setCharacterSize(18);
//    goraLewy->setPosition(10, 5);
//    goraLewy->setFillColor(sf::Color::Cyan);
//    goraLewy->setString("Left top");
//}
//
//void Interfejs::update(std::string _goraLewy) {
//    goraLewy->setString(_goraLewy);
//}
//Interfejs::Interfejs(sf::Vector2f _bounds) :bounds(_bounds) {
//    this->inicjuj();
//}
//
//Interfejs::Interfejs() {
//    this->bounds.x = 800.0;
//    this->bounds.y = 600.0;
//    this->inicjuj();
//}
//
//void Interfejs::draw(sf::RenderWindow& okno) {
//    okno.draw(*goraLewy);
//}
//
//class interfejsTekst : public Interfejs {
//
//private:
//    sf::Text* glownyTekst;
//public:
//    interfejsTekst(sf::Vector2f _bounds, sf::RenderWindow* _okno);
//    void draw(sf::RenderWindow& okno);
//};
//
//interfejsTekst::interfejsTekst(sf::Vector2f _bounds, sf::RenderWindow* _okno) {
//    this->bounds = _bounds;
//    czcionka = new sf::Font;
//    if (!czcionka->loadFromFile("fonts/vikingfont.ttf"))
//        return;
//
//    glownyTekst = new sf::Text;
//
//    glownyTekst->setFont(*czcionka);
//    glownyTekst->setCharacterSize(28);
//    glownyTekst->setPosition(25, 60);
//    glownyTekst->setFillColor(sf::Color::Red);
//    glownyTekst->setString("Line1\nLine2\nLine3");
//}
//
//void interfejsTekst::draw(sf::RenderWindow& okno) {
//    Interfejs::draw(okno);
//    okno.draw(*glownyTekst);
//}
