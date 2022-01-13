#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//GRACZ
class Player{
private:
    sf::Sprite gracz;
    sf::Texture tekstura;
    sf::Vector2f position;
    sf::Vector2f vel = { 1.1f, 1.1f};
    sf::IntRect ksztalt;
public:
    Player();
    Player(float x, float y);
    void moveW(float x, float y);
    void moveA(float x, float y);
    void moveS(float x, float y, sf::RenderWindow&);
    void moveD(float x, float y, sf::RenderWindow&);
    sf::Sprite& getPlayer(){ return gracz; }
    sf::Vector2f getPos() { return gracz.getPosition(); }
};

Player::Player(){
    position.x = 100;
    position.y = 100;
    tekstura.loadFromFile("textures/profesor.png");
    ksztalt = sf::IntRect({0, 0, 64, 64});
    gracz = sf::Sprite (tekstura, ksztalt);
    gracz.setPosition(position);
}

Player::Player(float xt, float yt){
    position.x = xt;
    position.y = yt;
    tekstura.loadFromFile("textures/profesor.png");
    ksztalt = sf::IntRect({0, 0, 64, 64});
    gracz = sf::Sprite (tekstura, ksztalt);
    gracz.setPosition(position);
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

    if(getPos().y <= 55){
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

void Player::moveS(float xt, float yt, sf::RenderWindow &window){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;

    ksztalt.top = 128;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);

    if(getPos().y >= window.getSize().y - 60.0f){
        pos.y=0;
    }
    gracz.move(pos);
}

void Player::moveD(float xt, float yt, sf::RenderWindow &window){
    sf::Vector2f pos;
    pos.x = xt * vel.x;
    pos.y = yt * vel.y;
    ksztalt.top = 192;
    if(ksztalt.left == 512)
        ksztalt.left = 0;
    else
        ksztalt.left += 64;
    gracz.setTextureRect(ksztalt);

    if(getPos().x >=window.getSize().x -50.0f){
        pos.x=0;
    }
    gracz.move(pos);
}



//MENU
class Menu
{

private:
    sf::Font font;
    sf::Text menu[6];//maksymalna liczba poziomow
    int wybrany_rekord = 0;
    int maksymalny_poziom = 6;

public:
    Menu(float width, float height);
    void Up();
    void Down();
    int getRekord() { return wybrany_rekord; }
    void draw(sf::RenderWindow &window);
    void menuglowne(float width, float height);
    void poziomtrudnosci(float width, float height);
    void potwierdzenie(float width, float height);
};

Menu::Menu(float width, float height){
    if (!font.loadFromFile("fonts/vikingfont.ttf"))
    {
        std::cout<<"ER00R"<<std::endl;
        return;
    }
    this->menuglowne(width, height);
}

void Menu::poziomtrudnosci(float width, float height) {
    maksymalny_poziom = 4;
    if(wybrany_rekord == 0){
        menu[wybrany_rekord]=menu[1];
    }
    if(wybrany_rekord>3){
        wybrany_rekord = 0;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Poziom:");
    menu[0].setPosition(sf::Vector2f(width / 4, height / (maksymalny_poziom + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Latwy");
    menu[1].setPosition(sf::Vector2f(width / 4, height / (maksymalny_poziom + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Normalny");
    menu[2].setPosition(sf::Vector2f(width / 4, height / (maksymalny_poziom + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Trudny");
    menu[3].setPosition(sf::Vector2f(width / 4, height / (maksymalny_poziom + 1) * 4));
}

void Menu::menuglowne(float width, float height) {
    maksymalny_poziom = 6;
    menu[0].setFont(font);
    menu[0].setString("Graj");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 1));
    menu[0].setFillColor(sf::Color::White);

    menu[1].setFont(font);
    menu[1].setString("Wczytaj");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 2));
    menu[1].setFillColor(sf::Color::White);

    menu[2].setFont(font);
    menu[2].setString("Sterowanie");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 3));
    menu[2].setFillColor(sf::Color::White);

    menu[3].setFont(font);
    menu[3].setString("Zapisz");
    menu[3].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 4));
    menu[3].setFillColor(sf::Color::White);

    menu[4].setFont(font);
    menu[4].setString("Trudnosc");
    menu[4].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 5));
    menu[4].setFillColor(sf::Color::White);

    menu[5].setFont(font);
    menu[5].setString("Wyjscie");
    menu[5].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 6));
    menu[5].setFillColor(sf::Color::Red);

}

void Menu::potwierdzenie(float width, float height){
    maksymalny_poziom = 3;
    if(wybrany_rekord == 0){
        menu[wybrany_rekord]=menu[wybrany_rekord+1];
    }
    if(wybrany_rekord>2){
        wybrany_rekord = 0;
    }
    menu[0].setFont(font);
    menu[0].setString("Czy na pewno?");
    menu[0].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 1));
    menu[0].setFillColor(sf::Color::White);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Tak");
    menu[1].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Nie");
    menu[2].setPosition(sf::Vector2f(width / 6, height / (maksymalny_poziom + 1) * 3));

}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < maksymalny_poziom; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::Up()
{
    if (wybrany_rekord >= 0 && wybrany_rekord < maksymalny_poziom)
    {
        menu[wybrany_rekord].setStyle(sf::Text::Regular);
        wybrany_rekord--;
        if (wybrany_rekord < 0)
            wybrany_rekord = maksymalny_poziom - 1;
        menu[wybrany_rekord].setStyle(sf::Text::Bold);
    }
}

void Menu::Down()
{
    if (wybrany_rekord >= 0 && wybrany_rekord < maksymalny_poziom)
    {
        menu[wybrany_rekord].setStyle(sf::Text::Regular);
        wybrany_rekord++;
        if (wybrany_rekord >= maksymalny_poziom)
            wybrany_rekord = 0;
        menu[wybrany_rekord].setStyle(sf::Text::Bold);
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



//ZAPIS DO PLIKU i STRUKTURA DANYCH
typedef struct{
    int zycie;
    int scores;
    int trudnosc;
    int czas;
}Gracz;

void zapiszDane(FILE *file, Gracz p)
{
    file = fopen("dane.dat", "w+b");
    if(file == NULL)
    {
        perror("ER00R");
    }
    else
    {
        std::cout<<"Plik zaladowany"<<"\n"<<std::endl;
    }
    fwrite(&p, sizeof(p), 2, file);
    fclose(file);
}

Gracz wczytajDane(FILE *file, Gracz dane){
    file = fopen("dane.dat", "rb");
    fseek(file, 0, SEEK_SET);
    fread(&dane, sizeof(dane), 1, file);
    std::cout<<"===== Dane: ====="<<std::endl;
    std::cout<<"Życie -> "<<dane.zycie<<std::endl;
    std::cout<<"=================="<<std::endl;
    std::cout<<"Scores -> "<<dane.scores<<std::endl;
    std::cout<<"=================="<<std::endl;
    std::cout<<"Trudność -> "<<dane.trudnosc<<std::endl;
    std::cout<<"=================="<<std::endl;
    std::cout<<"Czas sesji -> "<<dane.czas<<std::endl;
    fclose(file);
    return dane;
}

Gracz generuj(){
    Gracz dane;
    dane.zycie = 6;
    dane.scores = 0;
    dane.trudnosc = 1;
    dane.czas = 0;
    return dane;
}

Gracz poziom(int hp, int trudnosc){
    Gracz dane;
    dane.zycie = hp;
    dane.scores = 0;
    dane.trudnosc = trudnosc;
    return dane;
}

//HEALTHBAR W INTERFEJSIE
class Healthbar{
private:
    sf::Sprite healthbar;
    sf::Texture tekstura;
    sf::IntRect ksztalt;
    sf::Vector2f pozycja;

public:
    Healthbar();
    sf::Sprite& getHealthbar(){return healthbar;}
    void update_hp(Gracz);
};

Healthbar::Healthbar() {
    tekstura.loadFromFile("textures/healthbar.png");
    ksztalt = sf::IntRect({0,0,630,179});
    healthbar.setTexture(tekstura);
    healthbar = sf::Sprite(tekstura, ksztalt);
    pozycja.x = 20.0f;
    pozycja.y = 0.0f;
    healthbar.setScale(0.18f, 0.18f);
    healthbar.setPosition(pozycja);
}

void Healthbar::update_hp(Gracz dane) {
    if(dane.zycie >= 6)
        ksztalt.top = 895;
    if(dane.zycie == 5)
        ksztalt.top = 710;
    if(dane.zycie == 4)
        ksztalt.top = 525;
    if(dane.zycie == 3)
        ksztalt.top = 340;
    if(dane.zycie == 2)
        ksztalt.top = 155;
    if(dane.zycie == 1)
        ksztalt.top = -30;
    healthbar.setTextureRect(ksztalt);
}



//INTERFEJS GRY (PUNTY ZYCIE ITD.)
class Interfejs{
private:
    sf::Text* srodek;
    sf::RectangleShape tlo_sterowania;
    sf::Vector2f size = {396.0f, 396.0f};
    sf::Text* UpperLeft;
    sf::Text* UpperRight;
    sf::Font* czcionka;

    void inicjuj_interfejs();
    void inicjuj_sterowanie();
public:
    Interfejs(bool);
    void rysuj_opcje(sf::RenderWindow& _okno);
    void draw(sf::RenderWindow& _okno);
    void update(std::string, std::string);
};

void Interfejs::inicjuj_sterowanie() {
    czcionka = new sf::Font;
    if (!czcionka->loadFromFile("fonts/vikingfont.ttf"))
        return;

    tlo_sterowania.setPosition(40, 40);
    tlo_sterowania.setSize(size);
    tlo_sterowania.setFillColor(sf::Color::Blue);
    tlo_sterowania.setOutlineColor(sf::Color::Black);
    tlo_sterowania.setOutlineThickness(4.0f);

    srodek = new sf::Text;
    srodek->setFont(*czcionka);
    srodek->setCharacterSize(25);
    srodek->setPosition(100, 80);
    srodek->setFillColor(sf::Color::White);
    srodek->setStyle(sf::Text::Bold);
    srodek->setString("W - gora\n\nA - lewo\n\nS - dol\n\nD - prawo\n\nSpacja - strzal\n\nWyjscie - ESC");
}

void Interfejs::inicjuj_interfejs() {
    czcionka = new sf::Font;
    if (!czcionka->loadFromFile("fonts/vikingfont.ttf"))
        return;

    UpperLeft = new sf::Text;
    UpperLeft->setFont(*czcionka);
    UpperLeft->setCharacterSize(18);
    UpperLeft->setPosition(20, 10);
    UpperLeft->setFillColor(sf::Color::Black);
    UpperLeft->setStyle(sf::Text::Bold);
    UpperLeft->setString("DEBUG UPPERLEFT");

    UpperRight = new sf::Text;
    UpperRight->setFont(*czcionka);
    UpperRight->setCharacterSize(18);
    UpperRight->setPosition(250, 5);
    UpperRight->setFillColor(sf::Color::Black);
    UpperRight->setStyle(sf::Text::Bold);
    UpperRight->setString("DEBUG UPPERRIGHT");
}

void Interfejs::update(const std::string text_upperleft, const std::string text_upperright) {
    UpperLeft->setString(text_upperleft);
    UpperRight->setString(text_upperright);
}

Interfejs::Interfejs(bool flaga)
{
    if(flaga)
        this->inicjuj_interfejs();
    if(!flaga)
        this->inicjuj_sterowanie();
}

void Interfejs::draw(sf::RenderWindow& okno)
{
    okno.draw(*UpperLeft);
    okno.draw(*UpperRight);
}

void Interfejs::rysuj_opcje(sf::RenderWindow& okno)
{
    okno.draw(tlo_sterowania);
    okno.draw(*srodek);
};



//GAME OVER
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



//LOGIKA DZIALANIA POCISKU
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



//PRZECIWNICY
class Enemy{
private:
    sf::Sprite *enemy;
    sf::IntRect ksztalt_enemy;
    sf::Texture texture_enemy;
    sf::Vector2f vel = { 0.8f, 0.0f};
    std::random_device rd;
    int N;
public:
    Enemy(int);
    void move(float);
    void drawEnemy(sf::RenderWindow &window);
    bool kolizja_gracz(Player gracz, int Nt);
    bool kolizja_pocisk(Pocisk pocisk, int Nt);
};

Enemy::Enemy(int Nt)
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(200,500);
    std::uniform_int_distribution<> distY(50,450);

    texture_enemy.loadFromFile("textures/szkieletor.png");
    ksztalt_enemy = sf::IntRect({0, 0, 60, 60});
    N = Nt;
    enemy = new sf::Sprite[N];
    for(int i = 0; i < Nt; i++)
    {
        enemy[i].setTextureRect(ksztalt_enemy);
        enemy[i].setTexture(texture_enemy);
        enemy[i].setPosition(sf::Vector2f(distX(gen),distY(gen)));
    }
}

void Enemy::move(float dx)
{
    sf::Vector2f pos;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(480,600);
    std::uniform_int_distribution<> distY(50,420);
    pos.x = dx * vel.x;
    ksztalt_enemy.top = 60;
    if(ksztalt_enemy.left == 512)
        ksztalt_enemy.left = 0;
    else
        ksztalt_enemy.left += 64;

    for(int i = 0; i < N; i++){
        enemy[i].setTextureRect(ksztalt_enemy);
        if(enemy[i].getPosition().x<=-30){
            enemy[i].setPosition(distX(gen), distY(gen));
        }
        enemy[i].move(pos);
    }
}

void Enemy::drawEnemy(sf::RenderWindow &window)
{
    for(int i = 0;i<N;i++){
        window.draw(enemy[i]);
    }
}



//KOLIZJA POCISKU Z PRZECIWNIKIEM
bool Enemy::kolizja_pocisk(Pocisk pocisk, int Nt){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(480,500);
    std::uniform_int_distribution<> distY(50,420);
    N = Nt;
    for(int i = 0; i<N; i++)
    {
        if(sqrt((pocisk.getPos_pocisk().x - enemy[i].getPosition().x)*(pocisk.getPos_pocisk().x - enemy[i].getPosition().x)+
                (pocisk.getPos_pocisk().y - enemy[i].getPosition().y)*(pocisk.getPos_pocisk().y - enemy[i].getPosition().y))<20)
        {
            std::cout<<"Kolizja pocisku z przeciwnik["<<i<<"]"<<std::endl;
            enemy[i].setPosition(distX(gen), distY(gen));
            return true;
        }
    }
    return false;
}

//KOLIZJA GRACZA Z PRZECIWNIKIEM
bool Enemy::kolizja_gracz(Player gracz, int Nt){
    for (int i = 0; i < Nt; i++)
    {
        if (sqrt((gracz.getPos().x - enemy[i].getPosition().x) * (gracz.getPos().x - enemy[i].getPosition().x) +
                 (gracz.getPos().y - enemy[i].getPosition().y) * (gracz.getPos().y - enemy[i].getPosition().y)) < 20)
        {
            std::cout << "Kolizja z przeciwnik[" << i << "]" << std::endl;
            return true;
        }
    }
    return false;
}





//GRAFICZNA OBSLUGA COOLDOWNU POCISKU
int CD(sf::Clock zegar_pocisk)
{
    if(zegar_pocisk.getElapsedTime().asSeconds() < 1)
    {
        return 2;
    }
    else if(zegar_pocisk.getElapsedTime().asSeconds() >= 1 && zegar_pocisk.getElapsedTime().asSeconds()< 2){
        return 1;
    }
    else {
        return 0;
    }
}

//PORUSZAJ GRACZEM
Player poruszaj_graczem(Player gracz, sf::RenderWindow &window, float dir)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        gracz.moveW(0,-dir);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        gracz.moveS(0,dir, window);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        gracz.moveA(-dir,0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        gracz.moveD(dir,0, window);
    }
    return gracz;
}

//PRZEMIESZCZAJ REKORDAMI MENU
Menu poruszaj_menu(Menu menu, sf::Event event)
{
    if (event.key.code == sf::Keyboard::Up)
    {
        myDelay(100);
        menu.Up();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        myDelay(100);
        menu.Down();
    }
    return menu;
}

//WCZYTAJ ZAPISANA TRUDNOSC
float wczytaj_trudnosc(Gracz dane)
{
    if(dane.trudnosc == 1)
    {
        return 1;
    }
    else if(dane.trudnosc == 2)
    {
        return 2;
    }
    else if(dane.trudnosc == 3)
    {
        return 3;
    }
    else
    {
     return 1;
    }
}