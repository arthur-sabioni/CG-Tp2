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
#define AumentoAngulo_RodaGigante 1
#define AumentoAngulo_Carrossel 0,05
#define AnguloEntreCarrinhos M_PI/4

#define LARGURA_DO_MUNDO 1920
#define ALTURA_DO_MUNDO 1080


typedef struct coordenadas {
    double x, y, z;
}coordenadas;

coordenadas camera;
coordenadas base_gigante;
coordenadas chao;

float Angulo_RodaGigante = 0;
float Angulo_Carrossel = 0;

int camera_posicao=1;

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

GLMmodel *RodaGigante_base,*RodaGigante_roda,*RodaGigante_carrinho,
*Carrossel_estrutura,*Carrossel_giragira,
*BarcoViking_base,*BarcoViking_barco,*chaoObj;

void desenhaChao(GLMmodel* objeto, char* string, coordenadas coordenada){
    if(objeto == NULL){
            objeto = glmReadOBJ(string);    //manda pro objeto sua localização
            if(!objeto)
                exit(0);
            glmScale(objeto, 200.0); //o último parâmetro muda o que?
            glmUnitize(objeto);
            glmFacetNormals(objeto);
            glmVertexNormals(objeto, 90.0, 1);  //o que esses parârametros mudam?
        }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(30,30,30);
    glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    glPopMatrix();
}

void desenhaObjeto(GLMmodel* objeto, char* string, coordenadas coordenada){
    if(objeto == NULL){
            objeto = glmReadOBJ(string);    //manda pro objeto sua localização
            if(!objeto)
                exit(0);
            glmScale(objeto, 200.0); //o último parâmetro muda o que?
            glmUnitize(objeto);
            glmFacetNormals(objeto);
            glmVertexNormals(objeto, 90.0, 1);  //o que esses parârametros mudam?
        }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(1,1,1);
    glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    glPopMatrix();
}

void desenhaRodaGigante(GLMmodel* objeto1,GLMmodel* objeto2,GLMmodel* objeto3, char* string1,char* string2,char* string3, coordenadas coordenada){
    if(objeto1 == NULL){
            objeto1 = glmReadOBJ(string1);    //manda pro objeto sua localização
            if(!objeto1)
                exit(0);
            glmScale(objeto1, 200.0); //o último parâmetro muda o que?
            glmUnitize(objeto1);
            glmFacetNormals(objeto1);
            glmVertexNormals(objeto1, 90.0, 1);  //o que esses parârametros mudam?
        }
    if(objeto2 == NULL){
            objeto2 = glmReadOBJ(string2);    //manda pro objeto sua localização
            if(!objeto2)
                exit(0);
            glmScale(objeto2, 200.0); //o último parâmetro muda o que?
            glmUnitize(objeto2);
            glmFacetNormals(objeto2);
            glmVertexNormals(objeto2, 90.0, 1);  //o que esses parârametros mudam?
        }
    if(objeto3 == NULL){
            objeto3 = glmReadOBJ(string3);    //manda pro objeto sua localização
            if(!objeto3)
                exit(0);
            glmScale(objeto3, 200.0); //o último parâmetro muda o que?
            glmUnitize(objeto3);
            glmFacetNormals(objeto3);
            glmVertexNormals(objeto3, 90.0, 1);  //o que esses parârametros mudam?
        }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(1,1,1);
    glmDraw(objeto1, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
        glTranslatef(coordenada.x, coordenada.y-0.1,coordenada.z);
        glRotatef(Angulo_RodaGigante,1,0,0);
        glmDraw(objeto2, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    glPopMatrix();
}


void redimensiona(int width, int height) {

    glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, ((float)width)/height, 0.5, 200);
    glMatrixMode(GL_MODELVIEW);
}

void PosicionarOBJ(){

}

void desenhaCarrossel(){

}

void desenhaBarcoViking(){

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.8, 0.8, 0.8, 1);
    glLoadIdentity();
    if(camera_posicao==1)
        gluLookAt( camera.x, camera.y, camera.z, camera.x-4, 0, camera.z, 0, 1, 0); //geral

    glColor3f(0.0,0.0,0.0);
    //desenhaObjeto(RodaGigante_base,"Roda_Gigante/base2.obj",base_gigante);
    desenhaChao(chaoObj,"objetos/grama.obj",chao);
    //desenhaObjeto(RodaGigante_carrinho,"Roda_Gigante/carrinho2.obj",base_gigante);
    desenhaRodaGigante(RodaGigante_base,RodaGigante_roda,RodaGigante_carrinho,"Roda_Gigante/base2.obj","Roda_Gigante/roda.obj","Roda_Gigante/carrinho2.obj",base_gigante);
//    desenhaCarrossel();
//    desenhaBarcoViking();

    glutSwapBuffers();
}

void inicializa_posicoes(){

    base_gigante.x=0;
    base_gigante.y=0.9;
    base_gigante.z=0;

    chao.x=-10;
    chao.y=0;
    chao.z=0;

    camera.x=4;
    camera.y=4;
    camera.z=0;

}

void AcrescentarAngulos(){
    //arruma o angulo da roda gigante
    Angulo_RodaGigante += AumentoAngulo_RodaGigante;

    //arruma o angulo do carrossel
    Angulo_Carrossel += AumentoAngulo_Carrossel;
    if(Angulo_Carrossel > 2*M_PI){
        Angulo_Carrossel -= 2*M_PI;
    }
}
void atualizaCena(int periodo) {

    AcrescentarAngulos();
    glutPostRedisplay();
    glutTimerFunc(periodo, atualizaCena, periodo);

}

void setup() {
    glClearColor(1, 1, 1, 1); // preto
//    glCullFace(GL_BACK);
    // habilita o depth buffer para que a coordenada Z seja usada
    glEnable(GL_DEPTH_TEST);

    // habilita anti-aliasing para desenhar as linhas de forma suave
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_LINE_SMOOTH );

    // habilita blending para que transparências (e.g., linhas suaves) funcionem
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    inicializa_posicoes();

}

void Apertada(unsigned char key, int x, int y){
    switch(key){
        case 27: //ESC
            exit(0);
            break;
        case 'w':
        case 'W':
            camera.x--;
            break;
        case 'a':
        case 'A':
            camera.z++;
            break;
        case 's':
        case 'S':
            camera.x++;
            break;
        case 'd':
        case 'D':
            camera.z--;
            break;
    }
}

void Solta(unsigned char key, int x, int y){

}

void movimentoMouse(int x, int y) {

}

void click(int botao, int estado, int x, int y){

}

void main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitContextVersion(1,1);
    //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("Zoopark");

    glutEnterGameMode();

    setup();

    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(Apertada);
    glutKeyboardUpFunc(Solta);
    glutPassiveMotionFunc(movimentoMouse);
    glutMouseFunc(click);

    glutTimerFunc(0,atualizaCena,33);

    glewInit();

    glutMainLoop();
    }
