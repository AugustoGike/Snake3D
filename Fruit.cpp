#include "Fruit.h"

float Sizef = 2.0f; //Tamanho da fruta

Fruit::Fruit(){
    //Construtor Padrao
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

/*Metodo que retorna o valor de x da fruta

    Saida:
        x -> Valor de x da fruta
*/
float Fruit::getX(){ 
    return this->x; 
}

/*Metodo que retorna o valor de y da fruta

    Saida:
        y -> Valor de y da fruta
*/
float Fruit::getY(){ 
    return this->y; 
}

/*Metodo que retorna o valor de z da fruta

    Saida:
        z -> Valor de z da fruta
*/
float Fruit::getZ(){ 
    return this->z; 
}

/*Metodo que seta a posicao da fruta

    Entrada:
        newX -> Novo valor de x da fruta
        newY -> Novo valor de y da fruta
        newZ -> Novo valor de z da fruta
*/
void Fruit::setPosition(float newX, float newY, float newZ) {
    this->x = newX;
    this->y = newY;
    this->z = newZ;
}

/*Metodo que gera e seta uma posicao aleatoria para a fruta

    Entrada:
        snake -> Referencia para a cobra (Nao modifica snake, apenas acessa ele)

    Saida:
        true -> Se a posicao foi gerada com sucesso
        false -> Se nao foi possivel gerar uma posicao valida
*/
bool Fruit::randomizePosition(Snake& snake){
    /*Variaveis usadas no escopo*/
    int tentativas = 0; //Indica qual a tentativa atual de gerar a posicao da fruta
    bool validPosition = true; //Flag usada para indicar se gerou uma posicao valida ou nao

    do {
        /*Primeiramente, reseta a flag*/
        validPosition = true;
        
        /*Agora, gera uma posicao aleatoria para a fruta num espaco 100x100x100(No caso, cada coordenada vai de -50 a 50)*/
        this->x = (rand() % 100 - 50);
        this->y = (rand() % 100 - 50);
        this->z = (rand() % 100 - 50);

        /*Dai, ele testa se a posicao e valida, primeiro testando se colidiu com a cabeca da cobra*/
        if (fabs((this->x) - snake.getPosX()) < 2.0f && 
            fabs((this->y) - snake.getPosY()) < 2.0f && 
            fabs((this->z) - snake.getPosZ()) < 2.0f) {
            validPosition = false; //Caso colida, isso nao pode ser uma posicao valida entao tem que recalcular outra
            tentativas++; //E adiciona em 1 a quantidade de tentativas
        }

        /*Entao, testa se o numero de tentativas ja foi ultrapassado*/
        if(tentativas > 1000000){
            return false; //Entao sai da funcao avisando que nao da pra gerar a funcao
        }else if(validPosition == false){
            //Agora testa se gerou uma posicao valida, se nao, ja vai para a proxima interacao
            continue;
        }

        /*Agora ve se ta colindo com alguma parte do corpo*/
        //Para isso, ele anda o corpo todo
        for (auto& part : snake.getBody()) {
            if (fabs((this->x) - part.x) < 2.0f && 
                fabs((this->y) - part.y) < 2.0f && 
                fabs((this->z) - part.z) < 2.0f) {
                validPosition = false; //Caso positivo, isso nao pode ser uma posicao valida entao tem que recalcular outra
                tentativas++; //E adiciona em 1 a quantidade de tentativas
                break; //E sai do for, ja que nao precisa testar o resto do corpo
            }
        }

        /*Entao faz o mesmo teste da cabeca*/
        if(tentativas > 1000000){
            return false; 
        }else if(validPosition == false){
            continue;
        }

        //Caso tenha passado tudo e chegado aqui, significa que a posicao e valida, entao ele pode sair do loop
    } while (validPosition == false); //Enquanto a posicao nao for valida, ele fica tentando gerar outra

    return true; //E avisa que gerou uma posicao valida
}

/*Metodo que desenha a fruta*/
void Fruit::draw() {
    glDisable(GL_LIGHTING); //Desliga a luz para desenhar a fruta (para ela ficar visivel)

    /*Coloca a fruta como fonte de luz*/
    GLfloat lightPos[] = { this->x, this->y, this->z, 1.0f };
    GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Que tera uma luz branca
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //E gera uma luz ambiente fraca para nao deixar o ambiente totalmente escuro

    //Agora, coloca os parametros da luz nas funcoes
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    //E desenha a fruta
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f); //Com a cor magenta para deixar bem visivel
    glTranslatef(this->x, this->y, this->z);
    glutSolidCube(Sizef); //Desenha ela com tamanho 2
    glPopMatrix();
    
    glEnable(GL_LIGHTING); // Volta a ligar para poder desenhar o resto do mapa
}
