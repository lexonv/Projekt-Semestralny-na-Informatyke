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
    void moveW(float x, float y);
    void moveA(float x, float y);
    void moveS(float x, float y);
    void moveD(float x, float y);
    Player(float x, float y);
    sf::Sprite& getPlayer(){ return gracz; }
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



//MENU
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



//ZAPIS DO PLIKU i STRUKTURA DANYCH
typedef struct{
    int zycie;
    int scores;
    int trudnosc;
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
    fclose(file);
    return dane;
}

Gracz generuj(){
    Gracz dane;
    dane.zycie = 4;
    dane.scores = 0;
    dane.trudnosc = 2;
    return dane;
}

Gracz poziom(int hp){
    Gracz dane;
    dane.zycie = hp;
    dane.scores = 0;
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
    pozycja.y = -5.0f;
    healthbar.setScale(0.18f, 0.18f);
    healthbar.setPosition(pozycja);
}

void Healthbar::update_hp(Gracz dane) {
    if(dane.zycie >= 4)
        ksztalt.top = 895;
    if(dane.zycie == 3)
        ksztalt.top = 525;
    if(dane.zycie == 2)
        ksztalt.top = 155;
    if(dane.zycie == 1)
        ksztalt.top = -30;
    healthbar.setTextureRect(ksztalt);
}



//INTERFEJS GRY (PUNTY ZYCIE ITD.)
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
    this->bounds.x = 460.0;
    this->bounds.y = 460.0;
    this->inicjuj();
}

void Interfejs::draw(sf::RenderWindow& okno) {
    okno.draw(*goraLewy);
}



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



//PRZECIWNICY
class Enemy{
private:
    sf::Sprite enemy;
    sf::IntRect ksztalt_enemy;
    sf::Texture texture_enemy;
    sf::Vector2f position_enemy;
    sf::Vector2f vel = { 0.8f, 0.8f};
    std::random_device rd;
public:
    Enemy();
    void move(float);
    sf::Sprite &getEnemy(){ return enemy; }
    sf::Vector2f getPos() { return enemy.getPosition();}
    void respawn();
    void speed(float);
};

Enemy::Enemy(){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(300,480);
    std::uniform_int_distribution<> distY(100,400);
    position_enemy.x = distX(gen);
    position_enemy.y = distY(gen);
    texture_enemy.loadFromFile("textures/szkieletor.png");
    ksztalt_enemy = sf::IntRect({0, 0, 60, 60});
    enemy = sf::Sprite (texture_enemy, ksztalt_enemy);
    enemy.setPosition(position_enemy);
}

void Enemy::move(float dx){

    sf::Vector2f pos;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(480,500);
    std::uniform_int_distribution<> distY(50,420);
    pos.x = dx * vel.x;

    ksztalt_enemy.top = 60;
    if(ksztalt_enemy.left == 512)
        ksztalt_enemy.left = 0;
    else
        ksztalt_enemy.left += 64;
    enemy.setTextureRect(ksztalt_enemy);
    if(getPos().x<=-30){
        enemy.setPosition(distX(gen), distY(gen));
    }
    enemy.move(pos);
}

void Enemy::respawn(){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(480,500);
    std::uniform_int_distribution<> distY(50,420);
    enemy.setPosition(distX(gen), distY(gen));
}

void Enemy::speed(float speed){
    vel.x = speed;
    vel.y = speed;
}



//LOGIKA DZIALANIA POCISKU
class Pocisk{
private:
    sf::Sprite pocisk;
    sf::Texture tekstura_pocisk;
    sf::Vector2f position_pocisk;
    sf::Vector2f vel = {1.0f, 1.0f};
    sf::IntRect ksztalt_pocisk;
public:
    Pocisk(Player);
    void move_pocisk(float, Player);
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

void Pocisk::move_pocisk(float dx, Player p){
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
    if(pocisk.getPosition().x >=480 || pocisk.getPosition().x <= 0){
        return true;
    }
    else
        return false;
}

void Pocisk::respawn_pocisk() {
    position_pocisk.x = -100.0f;
    position_pocisk.y = -50.0f;
    pocisk.setPosition(position_pocisk);
}



//KOLIZJA POCISKU Z PRZECIWNIKIEM
bool kolizja(Pocisk pocisk, Enemy *przeciwnik) //DO POPRAWY
{
    if(sqrt((pocisk.getPos_pocisk().x - przeciwnik->getPos().x)*(pocisk.getPos_pocisk().x - przeciwnik->getPos().x)+
            (pocisk.getPos_pocisk().y - przeciwnik->getPos().y)*(pocisk.getPos_pocisk().y - przeciwnik->getPos().y))<30)
    {
        return true;
    }
    return false;
}

//KOLIZJA GRACZA Z PRZECIWNIKIEM
bool kolizja(Player gracz, Enemy *przeciwnik)
{
    if(sqrt((gracz.getPos().x - przeciwnik->getPos().x)*(gracz.getPos().x - przeciwnik->getPos().x)+
            (gracz.getPos().y - przeciwnik->getPos().y)*(gracz.getPos().y - przeciwnik->getPos().y))<30)
    {
        return true;
    }
    return false;
}