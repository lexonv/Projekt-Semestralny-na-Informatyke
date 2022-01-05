#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

//UZYTKOWNIK
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
    if(selectedItem == 0){
        menu[selectedItem]=menu[1];
    }
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
    max_poziom = 6;
    if (!font.loadFromFile("fonts/vikingfont.ttf"))
    {
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



//ZAPIS DO PLIKU i STRUKTURA DANYCH
typedef struct{
    int zycie;
    int scores = 0;
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
    return dane;
}

Gracz poziom(int hp){
    Gracz dane;
    dane.zycie = hp;
    dane.scores = 0;
    return dane;
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
    goraLewy->setFillColor(sf::Color::White);
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



//PRZECIWNICY
class Enemy{
private:
    sf::Sprite enemy;
    sf::IntRect ksztalt_enemy;
    sf::Texture texture_enemy;
    sf::Vector2f position_enemy;
    sf::Vector2f vel = { 0.1f, 0.1f};
    std::random_device rd;
public:
    Enemy();
    void move(int, int);
    sf::Sprite getEnemy(){ return enemy; }
    sf::Vector2f getPos() { return enemy.getPosition();}
};

Enemy::Enemy(){
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(300,430);
    std::uniform_int_distribution<> distY(50,380);
    position_enemy.x = distX(gen);
    position_enemy.y = distY(gen);
    texture_enemy.loadFromFile("textures/szkieletor.png");
    ksztalt_enemy = sf::IntRect({0, 0, 60, 60});
    enemy = sf::Sprite (texture_enemy, ksztalt_enemy);
    enemy.setPosition(position_enemy);
}

void Enemy::move(int dx, int dy){

    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distY(50,300);

    sf::Vector2f pos;
    pos.x = dx * vel.x;
    pos.y = dy * vel.y;
    ksztalt_enemy.top = 60;
    if(ksztalt_enemy.left == 512)
        ksztalt_enemy.left = 0;
    else
        ksztalt_enemy.left += 64;
    enemy.setTextureRect(ksztalt_enemy);

    if(getPos().x<=-30)
    {
        pos.x = 500;
//        pos.y = distY(gen);
    }
    enemy.move(pos);
}


bool kolizja(Player gracz, Enemy *przeciwnik)
{
    Gracz dane;
    if(sqrt((gracz.getPos().x - przeciwnik->getPos().x)*(gracz.getPos().x - przeciwnik->getPos().x)+
            (gracz.getPos().y - przeciwnik->getPos().y)*(gracz.getPos().y - przeciwnik->getPos().y))<25)
    {
        //Do sprawdzania bledow
        std::cout<<std::endl;
        std::cout<<"========================================"<<std::endl;
        std::cout<<"gracz.x = "<<gracz.getPos().x<<std::endl;
        std::cout<<"gracz.y = "<<gracz.getPos().y<<std::endl;
        std::cout<<"przeciwnik.x = "<<przeciwnik->getPos().x<<std::endl;
        std::cout<<"przeciwnik.y = "<<przeciwnik->getPos().y<<std::endl;
        std::cout<<"========================================"<<std::endl;
        return true;
    }
    return false;
}



