 
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "glm.h"
#include "structs.h"
#include "cabecalho.h"

// Constantes globais
#define FPS 17.0
#define CARRINHOS 9.0
#define QTDECHAO 3.0
#define VELOCIDADE_RODA 0.5
#define TAMANHO 10

// Variaveis globais

Objeto3D	rodaGG_base,rodaGG_aro,rodaGG_carro, arvore1,arvore2,arvore_morta, terreno, pedra_3,cerca, fonte, pipoca, pipoca1, 
		banco, terreno_rua,terreno_rcurva,poste,OBJ;

spriteObject    wallpaper_menu, wallpaper_creditos, jogar, controles, creditos, sair_menu, sair_creditos, mouse;
vetorR3         camera, cursor;
int             keyboard[256], tela = 1, light = 0, xMouse = 0, yMouse = 0, modoCamera = 3, isLightingOn = 0, start=0;
float           matAmbAndDif[4], matShine[], altura = 720, largura = 1280, pi = 90, theta = 0, auxRotacao = 0;
Mix_Chunk       *som1, *som2, *som3, *som4;

// Parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_position[] = { 20.0f, 50.0f, 50.0f, 0.0f };

// Parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void main(int argc, char** argv)
{
    // Inicializacao
    glutInit(&argc, argv);

    // Definindo versao do GLUT
    glutInitContextVersion(1,1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuracoeses iniciais da janela GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(largura, altura);
    glutInitWindowPosition (0, 0);

    // Inicializando a Janela
    glutCreateWindow("Lego Park");

    glutEnterGameMode();

    // Seta valores iniciais
    setupJogo();
 
    // Callbacks
    glutDisplayFunc(desenhaMinhaCena);
    glutReshapeFunc(redimensiona);
    glutTimerFunc(FPS,refresh,FPS);
    glutKeyboardFunc(teclaPressionada);
    glutKeyboardUpFunc(teclaSegurada);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);

	glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Loop
    glutMainLoop();
}

#include "draws_aux.h"
#include "cod_aux.h"
#include "refresh.h"
#include "draws.h"
#include "setup.h"
#include "keyboard.h"
#include "mouse.h"
#include "musicas.h"
