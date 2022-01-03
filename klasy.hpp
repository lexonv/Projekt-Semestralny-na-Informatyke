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
    void _get(float*, float*);
    void _set(float*, float*);
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

void Player::_get(float *x_get, float *y_get){
    *x_get = this -> position.x;
    *y_get = this -> position.y;
}

void Player::_set(float *xt, float *yt){

    this -> position.x = *xt;
    this -> position.y = *yt;

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
    menu[0].setString("Nowa Gra");
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

//ZAPIS DO PLIKU
typedef struct{
    int zycie;
    int scores;
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
void wczytajDane(FILE *file, Gracz p){
    file = fopen("dane.dat", "rb");
    fseek(file, 0, SEEK_SET);
    fread(&p, sizeof(p), 1, file);
    std::cout<<"===== Dane: ====="<<std::endl;
    std::cout<<"Życie -> "<<p.zycie<<std::endl;
    std::cout<<"=================="<<std::endl;
    std::cout<<"Scores -> "<<p.scores<<std::endl;
    fclose(file);
}
Gracz generuj(){
    Gracz dane;
    dane.zycie = 4;
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
    Gracz dane;
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

void Interfejs::update(std::string _goraLewy) {
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


