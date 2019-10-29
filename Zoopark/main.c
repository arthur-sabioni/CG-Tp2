#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "glm.h"

#define PADRAO 100
//experimentar valores
#define AumentoAngulo_RodaGigante 0,01
#define AumentoAngulo_Carrossel 0,05
#define AnguloEntreCarrinhos M_PI/4

#define LARGURA_DO_MUNDO 1920
#define ALTURA_DO_MUNDO 1080


struct coordenadas {
    double x, y, z, altura, largura;
};

struct coordenadas p;
struct coordenadas foco;
struct coordenadas camera;
struct coordenadas up;

double phi;
double teta;
double rotate;

float buffer[5];
float enviar[5];

float Angulo_RodaGigante = 0;
float Angulo_Carrossel = 0;

//valores retirados de exemplo do coutinho
//revisar e modifica-los
// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

typedef struct vetor_r3{
    GLfloat x;
    GLfloat y;
    GLfloat z;

} vetor_r3;

typedef struct Objeto{
	vetor_r3 posicao;
	vetor_r3 dimensoes;
	GLuint listaVisualizacao;
	float multiplicadorDeProporcao;
} Objeto;

Objeto RodaGigante_base,RodaGigante_roda,RodaGigante_carrinho;
Objeto Carrossel_estrutura,Carrossel_giragira;
Objeto BarcoViking_base,BarcoViking_barco;

void redimensiona(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA_DO_MUNDO, 0, ALTURA_DO_MUNDO, -1, 1);

    float razaoAspectoJanela = ((float)width)/height;
    float razaoAspectoMundo = ((float) LARGURA_DO_MUNDO)/ ALTURA_DO_MUNDO;
    if (razaoAspectoJanela < razaoAspectoMundo) {
        float hViewport = width / razaoAspectoMundo;
        float yViewport = (height - hViewport)/2;
        glViewport(0, yViewport, width, hViewport);
    }
    else if (razaoAspectoJanela > razaoAspectoMundo) {
        float wViewport = ((float)height) * razaoAspectoMundo;
        float xViewport = (width - wViewport)/2;
        glViewport(xViewport, 0, wViewport, height);
    } else {
        glViewport(0, 0, width, height);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void listamentoOBJ(Objeto* brinquedo, GLMmodel* modelo){
    glmUnitize(modelo);
    glmFacetNormals(modelo);
    glmVertexNormals(modelo,90.0,1);
    brinquedo->listaVisualizacao = glmList(modelo, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    float dimensoes_proporcionais[3];
    glmDimensions(modelo,dimensoes_proporcionais);
    brinquedo->dimensoes.x = dimensoes_proporcionais[0];
    brinquedo->dimensoes.y = dimensoes_proporcionais[1];
    brinquedo->dimensoes.z = dimensoes_proporcionais[2];
    free(modelo);

}

void ListaDeOBJ(){
    //precisa definir as coordenadas de posição para conseguir fazer a atribuição dos valores
    //carrega a lista da roda gigante
    listamentoOBJ(&RodaGigante_base,glmReadOBJ("Roda_Gigante/base2.obj"));
    listamentoOBJ(&RodaGigante_roda,glmReadOBJ("Roda_Gigante/roda.obj"));
    listamentoOBJ(&RodaGigante_carrinho,glmReadOBJ("Roda_Gigante/carrinho2.obj"));
}

void PosicionarOBJ(){

    RodaGigante_base.posicao.x=0;
    RodaGigante_base.posicao.y=0;
    RodaGigante_base.posicao.z=0;

}

void desenhaRodaGigante(){

    glPushMatrix();
    glTranslatef(RodaGigante_base.posicao.x,RodaGigante_base.posicao.y,RodaGigante_base.posicao.z);
    glCallList(RodaGigante_base.listaVisualizacao);
    glPopMatrix();


}

void desenhaCarrossel(){

}

void desenhaBarcoViking(){

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);

    camera.x = 10*sin(phi)*cos(teta);
    camera.z = 10*sin(phi)*sin(teta);
    camera.y = 10*cos(phi);

    gluLookAt( camera.x, camera.y, camera.z, 0, 0, 0, up.x, up.y, up.z);

    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
        glutSolidSphere(5,10,10);
    glPopMatrix();
//    desenhaRodaGigante();
//    desenhaCarrossel();
//    desenhaBarcoViking();

    glutSwapBuffers();
}

void atualizaCena(int periodo) {



    desenha();

    glutTimerFunc(periodo, atualizaCena, periodo);
}

void AcrescentarAngulos(){
    //arruma o angulo da roda gigante
    Angulo_RodaGigante += AumentoAngulo_RodaGigante;
    if(Angulo_RodaGigante > 2*M_PI){
        Angulo_RodaGigante -= 2*M_PI;
    }

    //arruma o angulo do carrossel
    Angulo_Carrossel += AumentoAngulo_Carrossel;
    if(Angulo_Carrossel > 2*M_PI){
        Angulo_Carrossel -= 2*M_PI;
    }
}

void setup() {
    glClearColor(1, 1, 1, 1); // cinza
    glCullFace(GL_BACK);
    // habilita o depth buffer para que a coordenada Z seja usada
    glEnable(GL_DEPTH_TEST);

    // habilita anti-aliasing para desenhar as linhas de forma suave
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_LINE_SMOOTH );

    // habilita blending para que transparências (e.g., linhas suaves) funcionem
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // modelo de iluminação
    // prcisa criar as luzes ainda!! --> isso foi tirado do ex do coutinho
    /*glEnable(GL_LIGHT0);
    vetor direcaoLuz[] = { -1.0, 2.0, 2.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, direcaoLuz);
    glEnable(GL_LIGHT1);
    vetor direcaoLuz2[] = { 2.0, 4.0, -2.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, direcaoLuz2);*/

    glShadeModel(GL_FLAT);

    ListaDeOBJ();
    PosicionarOBJ();

    AcrescentarAngulos();
}

void Apertada(unsigned char key, int x, int y){
    switch(key){
        case 27: //ESC
            exit(0);
            break;
        case 'W':
        case 'w':
            if(foco.z<101.2)
            foco.z = foco.z + 0.2;
            rotate=0;
            break;
        case 'S':
        case 's':
            if(foco.z>-101.2)
            foco.z = foco.z - 0.2;
            rotate= 180;
            break;
        case 'A':
        case 'a':
            if(foco.x<149.6)
            foco.x = foco.x + 0.2;
            rotate= 90;
            break;
        case 'D':
        case 'd':
            if(foco.x>-149.4)
            foco.x = foco.x - 0.2;
            rotate= -90;
            break;
        case 'Q':
        case 'q':
            if(foco.y<39.0) foco.y = foco.y + 0.2;
            break;
        case 'E':
        case 'e':
            if(foco.y> -35.4) foco.y = foco.y - 0.2;
            break;
    }
}

void Solta(unsigned char key, int x, int y){

}

void movimentoMouse(int x, int y) {
  p.x=x;
  p.y=(ALTURA_DO_MUNDO)-y;

  printf("y : %i \n", y);
  printf("x: %f\n", p.x);
  printf("py: %f \n \n", p.y );

}

void click(int botao, int estado, int x, int y){

}

void inicializaCamera(){

  phi=0;
  teta=0;

  p.x = 0;
  p.y = 0;
  p.altura = 10;
  p.largura = 10;

  foco.x= 0;
  foco.y= 0;
  foco.z= 0;

  camera.x=0;
  camera.y=0;
  camera.z=0;

  up.x=0;
  up.y=1;
  up.z=0;

}

void main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitContextVersion(1,1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("Zoopark");

    setup();


    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(Apertada);
    glutKeyboardUpFunc(Solta);
    glutPassiveMotionFunc(movimentoMouse);
    glutMouseFunc(click);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    inicializaCamera();

    glutTimerFunc(0,atualizaCena,33);

    glutMainLoop();
    }
