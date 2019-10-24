/*
LEMBRETE:
eixo x: altera cima/baixo, sendo positivo levando mais para baixo
eixo z: altera direita/esquerda, sendo positivo levando mais para esquerda
*/

void aux_cerca(int qtdeQDD, float centrox, float centroz, int direcao){
	//faz crescer na vertical e para "baixo", centro deve coincidir com a cera mais acima do sistema
	if(direcao==1)
		for(int random=0; random<qtdeQDD; random++){
			glPushMatrix();
				glTranslatef(cerca.dimensoes.x*random,0,0);
				desenhaPosicao(cerca,centrox,centroz,0);
			glPopMatrix();
		}
	//direcao==0 ou qlq outro nmr
	//faz crescer na horizontal para "esquerda", o centro deve ser o centro da cerca mais á "direita"
	else
		for(int random=0; random<qtdeQDD; random++){
			glPushMatrix();
				glTranslatef(0,0,cerca.dimensoes.x*random);
				desenhaPosicao(cerca,centrox,centroz,90);
			glPopMatrix();
		}		
}

//direcao == 1: eixo z, senão eixo x
//tem q passar o centrox e centroy
void aux_rua(int qtdeQDD, float centrox, float centroz, int direcao){
	if(direcao==1){
		for(int random = 0; random<qtdeQDD ; random++){
			glPushMatrix();
				glTranslatef(terreno_rua.dimensoes.z*random,0,0);
				desenhaPosicao(terreno_rua,centrox,centroz,0);				
			glPopMatrix();
		}
	}else{
		for(int random = 0; random<qtdeQDD ; random++){
			glPushMatrix();
				glTranslatef(0,0,terreno_rua.dimensoes.x*random);
				desenhaPosicao(terreno_rua,centrox,centroz,0);
			glPopMatrix();
		}
	}
}
