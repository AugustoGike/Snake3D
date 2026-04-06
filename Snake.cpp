#include "Snake.h"

/*Construtor Padrão. Utilizado para inicializar a cobra*/
Snake::Snake(){
    this->posX = 0.0f;
    this->posY = 0.0f;
    this->posZ = 0.0f;
    this->angleX = 0.0f;
    this->angleY = 0.0f;
}

/*Metodo que retorna o vector responsavel pelo corpo da cobra

    Saida:
        body -> Vector que guarda as coordenadas do corpo da cobra

*/
std::vector<Point3D>& Snake::getBody(){
    return body;
}

/*Metodo que retorna o valor de x da cobra

    Saida:
        posX -> Valor de x da cobra
*/
float Snake::getPosX(){ 
    return posX; 
}

/*Metodo que retorna o valor de y da cobra

    Saida:
        posY -> Valor de y da cobra
*/
float Snake::getPosY(){ 
    return posY; 
}

/*Metodo que retorna o valor de z da cobra

    Saida:
        posZ -> Valor de z da cobra
*/
float Snake::getPosZ(){ 
    return posZ; 
}

/*Metodo que retorna o valor do angulo em x da cobra

    Saida:
        angleX -> Valor do angulo em x da cobra
*/
float Snake::getAngleX(){ 
    return angleX; 
}

/*Metodo que retorna o valor do angulo em y da cobra

    Saida:
        angleY -> Valor do angulo em y da cobra
*/
float Snake::getAngleY(){ 
    return angleY; 
}

/*Metodo que altera o angulo em x da cobra

    Entrada:
        angle -> Valor do angulo em x que sera adicionado ao da cobra
*/
void Snake::rotateX(float angle) { 
    angleX += angle; 
}

/*Metodo que altera o angulo em y da cobra

    Entrada:
        angle -> Valor do angulo em y que sera adicionado ao da cobra
*/
void Snake::rotateY(float angle) { 
    angleY += angle; 
}

/*Metodo que movimenta a cobra com os valores internos*/
void Snake::move() {
    /*Primeiramente, movimentamos o corpo da cobra*/
    if (!body.empty()) { //Entao, testamos se existe o corpo da cobra
        
        //Caso exista, cada parte do corpo copia as coordenadas da parte antes dela
        //Para acelerar o processo, testamos se não tem so 1 parte a mais
        if(body.size() > 1) {
            //Caso tenha, ele faz o processo do final para o começo (evitando perder informacao)
            for (size_t i = body.size() - 1; i > 0; --i) {
                body[i] = body[i - 1];
            }
        }

        //Dai assim, o primeiro bloco do corpo copia as coordenadas antigas da cabeça
        body[0] = {posX, posY, posZ};
    }

    //Dai, começamos o calculo para movimentar a cabeça
    /*Primeiro, convertemos os angulos para radianos, pois as funcoes do math.h calcula em radiano*/
    float radX = angleX * M_PI / 180.0f;
    float radY = angleY * M_PI / 180.0f;

    /*Agora vamos calcular o vetor que a cobra ta apontando para cada coordenada usando apenas o angulo em x e em y*/
    float dirX = cos(radX) * sin(radY); //Esse depende da rotacao lateral e da inclinacao
    float dirY = -sin(radX); //Esse depende apenas da inclinacao, pois a rotacao lateral nao altera o quanto a cobra sobe ou desce
    float dirZ = cos(radX) * cos(radY); //Esse depende dos 2, mas agora e cos(y) por que olhamos para o lado z do plano XZ

    /*Depois de calcular o vetor, calculamos a posicao da cobra*/
    this->posX += dirX * 2.0f; //O valor é 2 por que é o tamanho de cada parte do corpo 
    this->posY += dirY * 2.0f;
    this->posZ += dirZ * 2.0f;
}

/*Metodo que faz a cobra crescer*/
void Snake::grow() {
    //Para crescer a cobra, basta adicionar uma parte no final do corpo. Com as coordenadas da ultima parte do corpo (Cabeca ou corpo mesmo)
    if (body.empty()) {
        body.push_back({posX, posY, posZ});
    } else {
        body.push_back(body.back());
    }
}

/*Metodo que testa se a cobra colidiu com ela mesmo

    Saida:
        true -> Se a cabeca colidiu com alguma parte do corpo
        false -> Se a cabeca nao colidiu com nenhuma parte do corpo
*/
bool Snake::checkSelfCollision(){

    //Se a cobra tiver menos de 8 partes, ela nao pode colidir com ela mesmo pois a movimentacao nao ta tao calibrada.
    //Cobras grandes, essa movimentacao da uma disfarcada
    if (body.size() < 8){
        return false; 
    } 
        
    /*Agora se ela for maior que 8*/
    for (size_t i = 8; i < body.size(); ++i) {
        //Ela anda por toda a parte do corpo testando se a cabeca esta em alguma parte do corpo
        if (fabs(posX - body[i].x) < 1.0f && 
            fabs(posY - body[i].y) < 1.0f && 
            fabs(posZ - body[i].z) < 1.0f) {
            return true; //Caso sim, ela retorna true
        }
    }

    return false; //Caso nao, retorna false
}

/*Metodo que desenha uma parte do corpo

    Entrada:
        isHead == 1 -> Esta desenhando a cabeca, entao uma face dela deve ser vermelha
        isHead == 0 -> Esta desenhando o corpo, entao todas as faces devem ser azuis
*/
void Snake::drawParallelepiped(bool isHead) {
    /*Comeca a desenhar a parte do corpo*/
    glBegin(GL_QUADS);

    //Define a cor azul (padrao para todas as faces, exceto a face que tem uma excecao)
    glColor3f(0.0f, 0.0f, 1.0f);

    //Desenha a face de tras
    glNormal3f(0.0f, 0.0f, -1.0f); //Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    //Desenha a face de cima
    glNormal3f(0.0f, 1.0f, 0.0f); //Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    //Desenha a face de baixo
    glNormal3f(0.0f, -1.0f, 0.0f); //Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    //Desenha a face da esquerda
    glNormal3f(-1.0f, 0.0f, 0.0f); //Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    // Desenha a face da direita
    glNormal3f(1.0f, 0.0f, 0.0f); //Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    /*Agora falta desenhar a face. Para ela tem um excecao. Se a parte desenhada, for a cabeca, essa parte sera vermelha*/
    if (isHead) {
        //Dai testamos estamos desenhando a cabeca, entao mudamos a cor para vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
    }

    //Dai sim desenhamos a face da frente, que tem a cor definida de acordo com o teste anterior
    glNormal3f(0.0f, 0.0f, 1.0f);//Normal, para a luz ser calculada correta
    //Indices dos vertices da face
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();

    //Agora desenhamos as linhas em volta do corpo para realsar. Ela e preta
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();
}

/*Metodo que desenha a cobra completa (incluindo a cabeça e todas as partes do corpo)*/
void Snake::draw() {

    /*Desenha a Cabeça da cobra*/
    glPushMatrix();
    //Realiza todas as transformacoes necessarias para desenhar a cabeca na posicao e angulo corretos
    glTranslatef(posX, posY, posZ);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    drawParallelepiped(true);  //Passando como true o parametro do drawParallelepiped, para desenhar a cabeca (que tem uma face vermelha)
    glPopMatrix();

    /*Dai, comecamos a desenhar o corpo*/
    for (auto& part : body) {

        glPushMatrix();
        //Que realiza as translacoes necessarias para desenhar a parte do corpo na posicao correta
        glTranslatef(part.x, part.y, part.z);
        drawParallelepiped(false); //E passa o parametro como false, para desenhar o corpo todo azul
        glPopMatrix();
    }
}