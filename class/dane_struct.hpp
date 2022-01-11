#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

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
    dane.zycie = 6;
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