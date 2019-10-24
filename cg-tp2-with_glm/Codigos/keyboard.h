// Callback de Teclado (Apertando)
void teclaPressionada(unsigned char key, int x, int y)
{
    switch(key)
    {
        // Teclas para andar com a camera
        case 'S':
        case 's':

            keyboard[83] = 1;    
            break;

        case 'W':
        case 'w':

            keyboard[87] = 1;         
            break;

        case 'A':
        case 'a':

            keyboard[65] = 1;                
            break;

        case 'D':
        case 'd':

            keyboard[68] = 1;  
            break;

	case 'Q':
	case 'q':

		keyboard[81] = 1;
		break;

	case 'E':
	case 'e':

		keyboard[69] = 1;
		break;

		case 'l':
    	case 'L':
        	if(isLightingOn==0){
				isLightingOn=1;
			}
			else{
				isLightingOn=0;
			}
        break;

        // As três cameras
        // Camera perspectiva
        case '1':

            if(tela == 1)
                modoCamera = 1;
            break;

        // Camera primeira pessoa
        case '2':

            if(tela == 1)
                modoCamera = 2;
            break;

        // Camera terceira pessoa
        case '3':

            if(tela == 1)
                modoCamera = 3;
            break;

        //ESC
        case 27 : 

		exit(0);
            // Menu
            /*if(tela == 0)
            {
                exit(0);
            }
            else if(tela == 3|| tela == 1)
            {
                tela = 0;
				glutSetCursor(GLUT_CURSOR_INHERIT);
		        	glutReshapeWindow(largura,altura);
            }

            else
                exit(0);*/

            break;
    }   
}

// Callback de Teclado (Soltando)
void teclaSegurada(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'S':
        case 's':

            keyboard[83] = 0;
            break;

        case 'W':
        case 'w':

            keyboard[87] = 0;
            break;

        case 'A':
        case 'a':

            keyboard[65] = 0;
            break;

        case 'D':
        case 'd':

            keyboard[68] = 0;
            break;

	case 'Q':
	case 'q':

		keyboard[81] = 0;
		break;

	case 'E':
	case 'e':

		keyboard[69] = 0;
		break;
    }
}

void movimentacao()
{
    // Tecla w/W        
    if(keyboard[87] == 1) 
    {
        cursor.x--;
    }

    // Tecla s/S
    if(keyboard[83] == 1)  
    {
        cursor.x++;
    }

    // Tecla a/A
    if(keyboard[65] == 1)  
    {
        cursor.z++;
    }

    // Tecla d/D
    if(keyboard[68] == 1)  
    {
        cursor.z--;
    }

	if(keyboard[69] == 1)
	{
		cursor.y++;
	}

	if(keyboard[81] == 1)
	{
		cursor.y--;
	}
}
