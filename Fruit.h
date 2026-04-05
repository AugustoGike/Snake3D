#ifndef FRUIT_H
#define FRUIT_H

#include "Snake.h" //Para alguns calculos de colisao, a fruta precisa saber onde a cobra ta
#include <stdlib.h> //Biblioteca para a funcao rand(), gerador de numeros aleatorios

class Fruit {
    private:
        float x, y, z; //Atributos que indicam a posicao da fruta
        
    public:
        Fruit(); //Construtor Padrao
        float getX(); //Metodo get para a posicao x da fruta
        float getY(); //Metodo get para a posicao y da fruta
        float getZ(); //Metodo get para a posicao z da fruta
        void setPosition(float newX, float newY, float newZ); // Metodo set para alterar as 3 posicoes da fruta
        
        bool randomizePosition(Snake& snake); //Metodo para gerar a posicao aleatoria da fruta
        void draw(); //Metodo para desenhar a fruta
};

#endif
