#include <GL/glut.h> // Biblioteca para as funções do OPENGL
#include "Fruit.h" //Inclui a biblioteca da fruta e todas que ela chama (tipo a cobra)

/*Inclui uma biblioteca usada para carregar imagens como textura*/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
 
/*Variaveis Globais*/
GLuint texture; //Guarda a textura
float size = 100.0f; //Tamanho da skybox

/*Variaveis usadas para a animacao da introducao*/
bool isIntroAnimating = true; //Flag para saber se ta na animacao
float tIntro = 0.0f; //Valor do tempo da animacao. Para saber em que ponto da curva de Bezier a camera esta
float P0[3] = {0.0f, size, 0.0f}; //P1 da curva de Bezier
float P1[3] = {size, -size, -size}; //P2 da curva de Bezier
float P2[3] = {-size, 0, -size}; //P3 da curva de Bezier
float P3[3] = {0.0f, 10.0f, -20.0f}; //P4 da curva de Bezier

/*Funcao que calcula as coordenadas de um ponto na curva de Bezier.

    Entrada:
        t -> valor da posicao na curva
        result -> vetor onde fica armazenado as coordenadas 3D do ponto calculado
*/
void bezierPoint(float t, float* result) {
    //Calcula o valor dos pontos na curva de Bezier usando a formula de curvas cúbicas (com 4 pontos de controle):
    // B(i) = u³.P1[i] + 3.u².t.P2[i] + 3.u.t².P3[i] + t³.P4[i]
    //Em que u = 1 - t e i indica a cooordenada (0=x,1=y,2=z)

    float u = 1.0f - t;
    float t2 = t * t;
    float u2 = u * u;
    float u3 = u2 * u;
    float t3 = t2 * t;

    for (int i = 0; i < 3; i++) {
        result[i] = u3 * P0[i] +
                    3 * u2 * t * P1[i] +
                    3 * u * t2 * P2[i] +
                    t3 * P3[i];
    }
}

/*Funcao que gerencia o tempo da animacao

    Entrada:
        value -> valor passado pelo timer (nao utilizado, mas necessario para a chamada da funcao glutTimerFunc)
*/
void introTimer(int value) {
    //Primeiro testa se a animacao ainda continua
    if (isIntroAnimating) {
        tIntro += 0.002f; //Caso sim, atualiza o valor de tempo da animacao
        
        //Caso chegue no final da animacao
        if (tIntro >= 1.0f) {
            tIntro = 1.0f; //Garante que o valor pare em 1
            isIntroAnimating = false; //Pausa a animacao
        }
        
        glutPostRedisplay(); //Pede para desenhar o proximo frame
        
        //Caso ainda esteja na animacao
        if (isIntroAnimating) {
            //Chama essa funcao novamente com um intervalo de 16ms (Deixando a animacao em 60fps)
            glutTimerFunc(16, introTimer, 0); 
        }
    }
}

//Funcao utilizada em sala para baixar a imagem e colocar como textura
void loadTexture(const char * filename) {
    int width , height , nrChannels ;
    unsigned char * data = stbi_load(filename, &width, &height, &nrChannels, 0);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (nrChannels == 3) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    }else if (nrChannels == 4) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    
    stbi_image_free(data);
}

/*Desenha a skybox*/
void drawSkybox() {
    //Desliga a iluminacao para evitar efeitos de iluminacao na textura
    glDisable(GL_LIGHTING);

    //Habilita efeitos de textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture); //Coloca a textura na skybox
    glColor3f(1.0f, 1.0f, 1.0f); //Deixa a cor dela como branco

    /*Comeca a desenhar a skybox*/
    glBegin(GL_QUADS);
    //Desenha a face da frente e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);
    
    //Desenha a face de tras e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);
    
    //Desenha a face da esquerda e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
    
    //Desenha a face da direita e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);
    
    //Desenha a face de cima e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
    
    //Desenha a face de baixo e fazendo ela ficar com a textura certinha
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size, -size,  size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size,  size);
    glEnd();

    //Depois de desenhar a skybox, desativa os efeitos de textura
    glDisable(GL_TEXTURE_2D);
    //E reativa a iluminacao para o resto que for desenhado, ter os efeitos de iluminacao
    glEnable(GL_LIGHTING);
}

/*Desenha uma setinha da cabeça da cobra ate a fruta, facilitando para os jogadores

    Entradas:
        snake -> Referencia para a cobra
        fruit -> Referencia para a fruta
*/
void drawArrowToFruit(Snake& snake, Fruit& fruit){
    //Desenha uma linha da cobra ate a fruta
    glColor3f(1.0f, 0.0f, 0.0f); //Deixa ela vermelha para facilitar a visualizacao
    glBegin(GL_LINES);
        glVertex3f(snake.getPosX(), snake.getPosY(), snake.getPosZ()); //Comeca na posicao que a cabeça da cobra esta
        glVertex3f(fruit.getX(), fruit.getY(), fruit.getZ()); //Termina na posicao que a fruta esta
    glEnd();
}

/*Desenha uma tela de gameOver, com a frase e a pontuacao do jogador

    Entradas:
        points -> Pontuacao do jogador

*/
void drawGameOverText(int points) {
    /*Limpa tudo que esta desenhado */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    /*E seta qual a fonte sera usada*/
    void* font = GLUT_BITMAP_HELVETICA_18;
    glColor3f(1.0f, 0.0f, 0.0f); //Com a cor vermelha

    /*Agora escreve a primeira linha, no caso, a frase 'Game Over'*/
    const char* msg1 = "Game Over";

    int width1 = glutBitmapLength(font, (const unsigned char*)msg1); //Calcula a largura da frase para centralizar ela
    float x1 = 0.5f - (width1 / 2.0f) / glutGet(GLUT_WINDOW_WIDTH); //Posiciona o inicio da frase que e no meio da tela (um pouco pra cima para caber a frase debaixo)
    glRasterPos2f(x1, 0.55f); //Coloca a posicao no Raster
    
    for (const char* c = msg1; *c; c++) {
        //E escreve a frase letra por letra
        glutBitmapCharacter(font, *c);
    }

    /*Agora escreve a segunda linha, no caso, a pontuacao do jogador*/
    char buffer[64];
    sprintf(buffer, "Score = %d", points); //No caso, como a pontuacao e dinamica. Essa e a forma de converter para um ponteiro para char (utilizado no bitmap)
    
    int width2 = glutBitmapLength(font, (const unsigned char*)buffer); //Calcula a largura da frase para centralizar ela
    float x2 = 0.5f - (width2 / 2.0f) / glutGet(GLUT_WINDOW_WIDTH); //Calcula o x para centralizar a frase
    glRasterPos2f(x2, 0.5f); //Posiciona a frase um pouco mais a baixo da outra para ficar parecendo uma frase so
    
    for (const char* c = buffer; *c; c++) {
        //E comeca a escrever a frase letra por letra
        glutBitmapCharacter(font, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/*Funcao que seta a camera para a posicao que a animacao usara

    Entrada:
        snake -> Referencia para a cobra
*/
void setCameraAnimation(Snake& snake){
    float camPos[3]; //Variavel que guardara a posicao da camera na curva de Bezier
    bezierPoint(tIntro, camPos); //Calcula a posicao na curva e guarda em camPos
    
    glLoadIdentity();
    /*E ai coloca a camera na posicao calculada e olhando para a cobra*/
    gluLookAt(camPos[0], camPos[1], camPos[2], snake.getPosX(), snake.getPosY(), snake.getPosZ(), 0.0f, 1.0f, 0.0f);
}

/*Funcao que seta o angulo da camera na posicao que o jogo utiliza
    Entrada:
        snake -> Referencia para a cobra
*/
void setCameraAngled(Snake& snake){
    /*Variaveis utilizadas para controlar a posicao da camera*/
    float far = 20.0f; //Essa controla o quao longe a camera fica
    float height = 10.0f; // Essa controla o quao alto a camera fica

    /*Agora converte o angulo em radiano ao multiplicar por pi e dividir por 180, pois e o formato usado pelas funcoes do math*/
    float radY = snake.getAngleY() * M_PI / 180.0f;

    /*Agora calcula a posicao da camera com base na posicao da cobra e nos parametros*/
    float camX = snake.getPosX() - (sin(radY) * far); //Aqui calcula a posicao em x, usando a influencia do y
    float camY = snake.getPosY() + height; //Aqui a em Y e somando com a influencia do parametro altura
    float camZ = snake.getPosZ() - (cos(radY) * far); //Aqui calcula a posicao em z, usando a influencia do y

    /*Agora aplica essas mudancas na camera*/
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,       //Posicao da camera
              snake.getPosX(), snake.getPosY(), snake.getPosZ(), // Olhando para a cobra
              0.0f, 1.0f, 0.0f); // com Vup alinhado ao eixo Y
}
