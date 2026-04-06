## Sobre o projeto

Este projeto consiste em uma versão tridimensional do clássico jogo da cobrinha (*Snake*). Mantendo as regras tradicionais dos jogos presentes em celulares antigos, o diferencial está na movimentação em 3D.

Além dos movimentos básicos (frente, esquerda e direita), a cobrinha pode se deslocar nos eixos vertical (cima e baixo) e também realizar movimentos diagonais, permitindo combinações mais complexas e desafiadoras.

---

## Imagem do programa

<img width="610" height="636" alt="image" src="https://github.com/user-attachments/assets/6ba901d4-495d-4156-8624-abfb284b778f" />

<img width="612" height="633" alt="image" src="https://github.com/user-attachments/assets/8778eed9-09b7-47b2-a964-85a5c41f39e0" />


## Requisitos

Para compilar e executar o projeto, você precisa de:

* Terminal com o sistema operacional Linux
* Compilador **G++**
* Biblioteca **OpenGL (FreeGLUT)**

### Instalação das dependências

```bash
sudo apt update
sudo apt install freeglut3-dev
```

---

## Como compilar e executar

Compile o projeto com:

```bash
g++ main.cpp Snake.cpp Fruit.cpp -o main -lGL -lGLU -lglut -lm
```

Execute:

```bash
./main
```

---

## Controles

| Tecla                  | Ação                            |
| ---------------------- | ------------------------------- |
| ↑ (Seta para cima)     | Gira a cobrinha para cima       |
| ↓ (Seta para baixo)    | Gira a cobrinha para baixo      |
| → (Seta para direita)  | Gira a cobrinha para a direita  |
| ← (Seta para esquerda) | Gira a cobrinha para a esquerda |
| z                      | Move a cobrinha para frente     |

---

## Principais desafios

* **Sincronização da câmera com a movimentação da cobra**
  Especialmente no eixo Y (cima/baixo), houve dificuldades para manter o movimento da câmera alinhado com a rotação da cobrinha.

* **Crescimento da cobra**
  Implementar um crescimento fluido do corpo, acompanhando a cabeça de forma natural, exigiu bastante planejamento.

---

## Melhorias futuras

* Aplicar **texturas** na cobra e na fruta
* Implementar **movimento automático** da cobrinha
* Melhorar o sistema de **câmera**
* Tornar a movimentação mais **suave e fluida**

---

## Atividades práticas implementadas

* **Atividade Prática 2:**
  Modelagem da cobra com partes conectadas e uso de *WireCube* para bordas.

* **Atividade Prática 3:**
  Tratamento de **oclusão** entre skybox, cobra, seta e fruta.

* **Atividade Prática 4:**
  Implementação de **iluminação**, com a fruta atuando como fonte de luz e projeção de sombras.

* **Atividade Prática 5:**
  Aplicação de **textura na skybox**, simulando um ambiente espacial.

* **Atividade Prática 6:**
  **Animação inicial** com câmera percorrendo uma spline ao redor do cenário.

---

## Equipe

* **Daniel Diniz**
  Animação inicial, Câmeras, skybox, colisões com o ambiente e tela de *Game Over*

* **Guilherme Augusto**
  Movimentação, rotação da cobra e colisão com ela mesmo

* **Ulderico Queiroz**
  Geração da fruta, sendo ela a fonte de iluminação

---
