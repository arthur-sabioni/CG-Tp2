// Registrando a posicao atual do mouse
void mouseMove(int x, int y)
{
	// Vetor 2D de movimento
	double xChange, yChange;

	// Posicao atual do mouse
    	mouse.posicao.x = x;
   	mouse.posicao.y = altura - y;

   	// Salvando as alteracoes realizadas na camera do jogador
	// xMouse e yMouse são valores do ultimo frame do mouse
	xChange = x - xMouse;
	yChange = y - yMouse;

   	// Regulando os angulos em coordenadas esfericas 2D -> 3D
   	pi = pi - yChange/150;
   	theta = theta + xChange/150;

   	// Limitando o valor do angulo
   	if(pi >= 180)
   	{
   		pi = 180;
   	}

   	// Atualizando o ultimo valor de frame do mouse
   	xMouse = x;
   	yMouse = y;

   	// Evitar lags
   	glutPostRedisplay();

    // Realizando o efeito hover no menu
    if(tela == 0)
	{

		if(mouse.posicao.x < jogar.posicao.x + jogar.dimensoes.x/2 && mouse.posicao.x > jogar.posicao.x - jogar.dimensoes.x/2 &&
		   mouse.posicao.y < jogar.posicao.y + jogar.dimensoes.y/2 && mouse.posicao.y > jogar.posicao.y - jogar.dimensoes.y/2)
		{
			jogar.textura = loadTexture("../Imagens/jogar_cinza.png");
		}
		else
			jogar.textura = loadTexture("../Imagens/jogar_branco.png");
			
		if(mouse.posicao.x < controles.posicao.x + controles.dimensoes.x/2 && mouse.posicao.x > controles.posicao.x - controles.dimensoes.x/2 &&
		   mouse.posicao.y < controles.posicao.y + controles.dimensoes.y/2 && mouse.posicao.y > controles.posicao.y - controles.dimensoes.y/2)
		{
			controles.textura = loadTexture("../Imagens/controles_cinza.png");
		}
		else
			controles.textura = loadTexture("../Imagens/controles_branco.png");

		if(mouse.posicao.x < creditos.posicao.x + creditos.dimensoes.x/2 && mouse.posicao.x > creditos.posicao.x - creditos.dimensoes.x/2 &&
		   mouse.posicao.y < creditos.posicao.y + creditos.dimensoes.y/2 && mouse.posicao.y > creditos.posicao.y - creditos.dimensoes.y/2)
		{
			creditos.textura = loadTexture("../Imagens/creditos_cinza.png");
		}
		else
			creditos.textura = loadTexture("../Imagens/creditos_branco.png");
		
		if(mouse.posicao.x < sair_menu.posicao.x + sair_menu.dimensoes.x/2 && mouse.posicao.x > sair_menu.posicao.x - sair_menu.dimensoes.x/2 &&
		   mouse.posicao.y < sair_menu.posicao.y + sair_menu.dimensoes.y/2 && mouse.posicao.y > sair_menu.posicao.y - sair_menu.dimensoes.y/2)
		{
			sair_menu.textura = loadTexture("../Imagens/sair_cinza.png");
		}
		else
			sair_menu.textura = loadTexture("../Imagens/sair_branco.png");
	}

	// Efeito hover nos creditos
	if(tela == 3)
	{		
		if(mouse.posicao.x < sair_creditos.posicao.x + sair_creditos.dimensoes.x/2 && mouse.posicao.x > sair_creditos.posicao.x - sair_creditos.dimensoes.x/2 &&
		   mouse.posicao.y < sair_creditos.posicao.y + sair_creditos.dimensoes.y/2 && mouse.posicao.y > sair_creditos.posicao.y - sair_creditos.dimensoes.y/2)
		{
			sair_creditos.textura = loadTexture("../Imagens/sair_cinza.png");
		}
		else
			sair_creditos.textura = loadTexture("../Imagens/sair_branco.png");
		
	}	
}

// Clique do mouse
void mouseClick(int botao, int estado, int x, int y)
{
	switch(botao)
    {
		case GLUT_LEFT_BUTTON :

			// Menu
			if(tela == 0)
			{
				// Clicando "Jogar"
				if(mouse.posicao.x < jogar.posicao.x + jogar.dimensoes.x/2 && mouse.posicao.x > jogar.posicao.x - jogar.dimensoes.x/2 &&
				   mouse.posicao.y < jogar.posicao.y + jogar.dimensoes.y/2 && mouse.posicao.y > jogar.posicao.y - jogar.dimensoes.y/2)
				{
					tela = 1;
					if(start==0){
						setupJogo();
						start++;
					}glutSetCursor(GLUT_CURSOR_NONE);
					glutReshapeWindow(largura,altura);
				}

				// Clicando "Controles"
				if(mouse.posicao.x < controles.posicao.x + controles.dimensoes.x/2 && mouse.posicao.x > controles.posicao.x - controles.dimensoes.x/2 &&
				   mouse.posicao.y < controles.posicao.y + controles.dimensoes.y/2 && mouse.posicao.y > controles.posicao.y - controles.dimensoes.y/2)
			    {
			    	tela = 2;
			    }

			    // Clicando "Creditos"
				if(mouse.posicao.x < creditos.posicao.x + creditos.dimensoes.x/2 && mouse.posicao.x > creditos.posicao.x - creditos.dimensoes.x/2 &&
				   mouse.posicao.y < creditos.posicao.y + creditos.dimensoes.y/2 && mouse.posicao.y > creditos.posicao.y - creditos.dimensoes.y/2)
				{
					tela = 3;
				}

				// Clicando "Sair"
				if(mouse.posicao.x < sair_menu.posicao.x + sair_menu.dimensoes.x/2 && mouse.posicao.x > sair_menu.posicao.x - sair_menu.dimensoes.x/2 &&
				   mouse.posicao.y < sair_menu.posicao.y + sair_menu.dimensoes.y/2 && mouse.posicao.y > sair_menu.posicao.y - sair_menu.dimensoes.y/2)
				{
					exit(0);
				}
			}

			// Creditos
			if(tela == 3)
			{
				// Clicando "Sair"
				if(mouse.posicao.x < sair_creditos.posicao.x + sair_creditos.dimensoes.x/2 && mouse.posicao.x > sair_creditos.posicao.x - sair_creditos.dimensoes.x/2 &&
				   mouse.posicao.y < sair_creditos.posicao.y + sair_creditos.dimensoes.y/2 && mouse.posicao.y > sair_creditos.posicao.y - sair_creditos.dimensoes.y/2)
				{
					tela = 0;
				}
			}			
	}
}
