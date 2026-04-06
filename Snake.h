#ifndef SNAKE_H
#define SNAKE_H

#include <GL/glut.h> // Biblioteca para as funções do OPENGL
#include <math.h> // Biblioteca para funções matemáticas como cosseno() e seno()
#include <vector> //Biblioteca utilizada para armazenar o corpo da cobra

// Estrutura para guardar as coordenadas do corpo
struct Point3D {
    float x;
    float y;
    float z;
};

class Snake {
    private:
        /*Atributos da Cobra*/
        float posX, posY, posZ; //Coordenadas da cabeca
        float angleX, angleY; //Angulo da cabeca
        std::vector<Point3D> body; // Vetor que guarda as coordenadas do corpo da cobra
        
        void drawParallelepiped(bool isHead); //Metodo que desenha uma parte do corpo (ou a cabeça ou o corpo)
    
    public:
        Snake(); //Construtor Padrão

        std::vector<Point3D>& getBody(); //Metodo get para o corpo 
        float getPosX(); //Metodo get para a posicao x da cabeca
        float getPosY(); //Metodo get para a posicao y da cabeca
        float getPosZ(); //Metodo get para a posicao z da cabeca
        float getAngleX(); //Metodo get para o angulo em x da cabeca
        float getAngleY(); //Metodo get para o angulo em y da cabeca

        void rotateX(float angle); //Faz o calculo para alterar o angulo x da cabeça
        void rotateY(float angle); //Faz o calculo para alterar o angulo y da cabeça
        void move(); //Faz o calculo para mover a cabeça e o corpo
        void grow(); //Metodo para crescer a cobra
        
        void draw(); //Desenha a cobra completa (cabeça + corpo)
        bool checkSelfCollision(); //Metodo para testar se a cabeca colidiu com alguma parte do corpo

};

#endif