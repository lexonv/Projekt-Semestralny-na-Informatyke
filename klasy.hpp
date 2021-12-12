#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


//Uzytkownik
class Player{
private:
    float x;
    float y;
    sf::Sprite gracz;
    sf::Texture tekstura;
    sf::Vector2f position;
    sf::Vector2f vel = { 1.5f, 1.5f};
    sf::IntRect ksztalt;
public:
    void moveW(float x, float y);
    void moveA(float x, float y);
    void moveS(float x, float y);
    void moveD(float x, float y);
    void _get(float*, float*);
    void _set(float*, float*);
    Player(float x, float y);
    sf::Sprite getPlayer(){ return gracz; }
    sf::Vector2f getPos() { return gracz.getPosition(); }
    void render();
};

Player::Player(float xt, float yt){
    position.x = xt;
    position.y = yt;
    
    tekstura.loadFromFile("textures/profesor.png");
    ksztalt = sf::IntRect({0, 0, 64, 64});
    gracz = sf::Sprite (tekstura, ksztalt);
    gracz.setPosition(position);
}

void Player::_get(float *x_get, float *y_get){
    *x_get = this -> x;
    *y_get = this -> y;
}

void Player::_set(float *xt, float *yt){

    this -> x = *xt;
    this -> y = *yt;

}
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
    if(getPos().x>=476){
        pos.x = 476;
    }
    gracz.move(pos);
}

//Koniec uzytkownika



//Menu

class Menu
{

private:
    sf::Font font;
    sf::Text menu[4];//maksymalna liczba poziomow
    int selectedItem = 0;
    int max_poziom = 4;

public:
    Menu(float width, float height);
    ~Menu() {};
    void przesunG();//przesun do gory
    void przesunD();//przesun w dol
    int getSelectedItem() { return selectedItem; }//zwroc poziom menu
    void draw(sf::RenderWindow &window);//rysuj menu w oknie
};

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("fonts/vikingfont.ttf"))
    {
        return;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 1));
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Pomoc");
    menu[1].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 2));
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Zapisz");
    menu[2].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 3));
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Wyjscie");
    menu[3].setPosition(sf::Vector2f(width / 4, height / (max_poziom + 1) * 4));
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
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0)
            selectedItem = max_poziom - 1;
        menu[selectedItem].setFillColor(sf::Color::Red);
        menu[selectedItem].setStyle(sf::Text::Bold);
    }


}

void Menu::przesunD()
{
    if (selectedItem >= 0 && selectedItem < max_poziom)
    {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= max_poziom)
            selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color::Red);
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

//Koniec Menu

class Enemy{
public:
    sf::Texture enemy_texture;
    sf::Sprite *enemy;
    int N;
    std::random_device rd;
private:
    Enemy(int);
    void updateEnemy();
    void moveEnemy();
};

//Przeciwnik
Enemy::Enemy(int Nt){
    std::mt19937 gen(rd());
        std::uniform_int_distribution<> distX(1,750);
        std::uniform_int_distribution<> distY(1,550);
        float x=0, y=0;
        enemy_texture.loadFromFile("toad.png");
        N = Nt;
        enemy = new sf::Sprite[N];
        for (int i = 0; i < N; i++)
        {
            x = distX(gen);
            y = distY(gen);

            enemy[i].setTexture(enemy_texture);
            enemy[i].setPosition(sf::Vector2f(x, y));
            enemy[i].setScale(sf::Vector2f(0.03f, 0.03f));
        }
}



