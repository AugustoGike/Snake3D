#include "world.h" //Inclui a biblioteca do mundo (com seus include e tudo mais)
#include <time.h> //Utilizada para gerar a semente dos numeros aleatorios

// Instâncias globais
Snake snake; //A cobra
Fruit fruit; //A fruta
bool gameOver = false; //Flag que determina se o jogo acabou ou nao
int fruitsCollected = 0; //Variavel que armazena quantas frutas o jogador coletou

/*Funcao que verifica se a cobra colidiu com a fruta*/
void checkCollision(){
    // Verifica se a cabeça da cobra bateu na fruta
    if (fabs(snake.getPosX() - fruit.getX()) < 2.0f &&
        fabs(snake.getPosY() - fruit.getY()) < 2.0f &&
        fabs(snake.getPosZ() - fruit.getZ()) < 2.0f) {
        
        /*Caso a cobra bata na fruta*/
        snake.grow(); // A cobra cresce
        bool ff = fruit.randomizePosition(snake); // A fruta nasce em um local valido
        fruitsCollected++; // Conta mais uma fruta
        
        /*Caso a fruta nao consiga nascer em nenhum lugar*/
        if(!ff){
            gameOver = true; //Acaba o jogo
        }
    }
}

/*Funcao que testa se a cobra bateu na skybox

    Saida:
        true -> Se a cobra bateu na skybox
        false -> Se a cobra nao bateu na skybox
*/
bool checkSkyboxCollision() {
    // Verifica se a cobra ultrapassou os limites do mapa (Skybox)
    if (snake.getPosX() >= size || snake.getPosX() <= -size ||
        snake.getPosY() >= size || snake.getPosY() <= -size ||
        snake.getPosZ() >= size || snake.getPosZ() <= -size) {
        return true; //Caso passou, retorna true
    }
    return false; //Caso contrario, retorna false
}

//Init do OpenGL
void init(void){

    glClearColor(0.0, 0.0, 0.0, 0.0); //Limpa as cores
    glEnable(GL_DEPTH_TEST); //Ativa Z buffer para evitar oclusao
    srand(time(NULL)); //Gera uma semente aleatoria para a posicao da fruta
    
    isIntroAnimating = true; //Reseta a flag pra comecar a animacao

    glEnable(GL_LIGHTING); //Ativa iluminacao
    glEnable(GL_LIGHT0); //Liga a Luz0, utilizada como a luz da fruta
    glEnable(GL_COLOR_MATERIAL); //Habilida as cores da iluminacao

    fruit.randomizePosition(snake); //Gera a posicao inicial da fruta

    loadTexture("background.jpg"); //Binda a textura da skybox

    glutTimerFunc(16, introTimer, 0); //Inicia a animacao
}

/*Funcao que gera o frame que vai para a tela*/
void display(){
    /*Limpa as matrizes tanto de cor quanto de profundidade*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (gameOver) {
        //Caso esteja com o gameOver, desenha a tela de gameOver
        drawGameOverText(fruitsCollected*100);
    }else{
        //Caso contrario, desenha o jogo normalmente

        /*Primeiro, ele ve se a camera e a animacao ou e a camera normal*/
        if (isIntroAnimating){
            //Caso esteja na animacao, o codigo usa a camera da animacao
            setCameraAnimation(snake);
        }else{
            //Caso contrario, o codigo usa a camera normal
            setCameraAngled(snake);
        }

        /*Depois ele comeca a desenhar os objetos*/
        drawSkybox(); //Comeca pela skybox
        snake.draw(); //Agora desenha a cobra
        fruit.draw(); //Depois a fruta
        drawArrowToFruit(snake,fruit); //Depois a seta entre a cobra e a fruta
    }

    glutSwapBuffers();
}

//Funcao que faz o reshape quando o usuario arruma a janela
void reshape(int w, int h) {
    float ratio = w * 1.0f / h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, ratio, 0.1f, 500.0f);
    
    glMatrixMode(GL_MODELVIEW);
}

/*Funcao que gerencia as teclas especiais (no caso sao as setinhas)*/
void specialKeys(int key, int x, int y){
    /*Primeiro, testa se ou a animacao ta ativada ou o jogo acabou*/
    if (isIntroAnimating || gameOver) return;

    switch(key){
        case GLUT_KEY_UP:    snake.rotateX(5.0f); break; //Seta pra cima = Rotaciona para cima
        case GLUT_KEY_DOWN:  snake.rotateX(-5.0f); break; //Seta pra baixo = Rotaciona para baixo
        case GLUT_KEY_LEFT:  snake.rotateY(5.0f); break; //Seta para esquerda = Rotaciona para a esquerda
        case GLUT_KEY_RIGHT: snake.rotateY(-5.0f); break; //Seta para direita = Rotaciona para a direita
    }

    glutPostRedisplay();
}

/*Funcao que gerencia as teclas normais (No caso, o ESC e o Z)*/
void keyboard(unsigned char key, int x, int y){
    /*Caso aperte o ESC, a janela fecha*/
    if (key == 27) exit(0); // ESC

    /*Caso o jogo acabe ou esteja na animacao, o jogo fica parado*/
    if (isIntroAnimating || gameOver) return;   

    if(key == 'z'){
        //Primeiramente, move a cobra
        snake.move();

        //Depois, verifica se a cobra bateu nela mesmo ou na skybox
        if (snake.checkSelfCollision() || checkSkyboxCollision()) {
            //Caso sim, o jogo acaba
            gameOver = true;
        }else{

            //Caso contrario, testa se a cobra bateu na fruta
            checkCollision(); 
        }

    }
    
    glutPostRedisplay();
}

//Main
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake 3D");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
