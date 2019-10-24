// Função de carregar texturas
GLuint loadTexture(const char* arquivo)
{
    GLuint idTextura = SOIL_load_OGL_texture(arquivo, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (idTextura == 0)
    {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

// Reshape
void redimensiona(int w, int h)
{
    largura = w;
    altura = h;

    switch(tela)
    {
        case 0:
        case 2:
        case 3:

            glDisable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, w, 0, h, 0, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glViewport(0, 0, w, h);
            break;

        case 1:
	
	    glEnable(GL_DEPTH_TEST);
            glViewport (0, 0, w, h);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, (float)w/(float)h, 0.2, 400.0);     //colocar fovy entre 45.0 e 60.0
            glMatrixMode(GL_MODELVIEW);
            begin3d();
	    glLoadIdentity();
            break;
    }

    glutPostRedisplay();

}

// Atualiza a cena
void refresh(int delay)
{
    // Atualiza as posições
    attPosicao();
    
    // Redesenha
    glutPostRedisplay();

    // Registra a callback novamente
    glutTimerFunc(delay, refresh, delay);
}

void begin3d()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
