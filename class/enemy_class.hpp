#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>


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
    std::uniform_int_distribution<> distX(250,500);
    std::uniform_int_distribution<> distY(50,450);

    texture_enemy.loadFromFile("textures/szkieletor.png");
    ksztalt_enemy = sf::IntRect({0, 0, 60, 60});
    N = Nt;
    enemy = new sf::Sprite[N];
    for(int i = 0; i < Nt; i++){
        enemy[i].setTextureRect(ksztalt_enemy);
        enemy[i].setTexture(texture_enemy);
        enemy[i].setPosition(sf::Vector2f(distX(gen),distY(gen)));
    }
}

void Enemy::move(float dx)
{
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

bool Enemy::kolizja_pocisk(Pocisk pocisk, int Nt) {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(480,500);
    std::uniform_int_distribution<> distY(50,420);
    N = Nt;
    for(int i = 0; i<N; i++)
    {
        if(sqrt((pocisk.getPos_pocisk().x - enemy[i].getPosition().x)*(pocisk.getPos_pocisk().x - enemy[i].getPosition().x)+
                (pocisk.getPos_pocisk().y - enemy[i].getPosition().y)*(pocisk.getPos_pocisk().y - enemy[i].getPosition().y))<30)
        {
            std::cout<<"Kolizja pocisku z przeciwnik["<<i<<"]"<<std::endl;
            enemy[i].setPosition(distX(gen), distY(gen));
            return true;
        }
    }
    return false;
}



//KOLIZJA GRACZA Z PRZECIWNIKIEM
bool Enemy::kolizja_gracz(Player gracz, int Nt) {
    for (int i = 0; i < Nt; i++)
    {
        if (sqrt((gracz.getPos().x - enemy[i].getPosition().x) * (gracz.getPos().x - enemy[i].getPosition().x) +
                 (gracz.getPos().y - enemy[i].getPosition().y) * (gracz.getPos().y - enemy[i].getPosition().y)) < 30)
        {
            std::cout << "Kolizja z przeciwnik[" << i << "]" << std::endl;
            return true;
        }
    }
    return false;
}