// Inicializa comandos essenciais
void setup()
{
    // Cor do fundo
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Habilita a utilização de texturas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Limpa a tela
    glClear(GL_COLOR_BUFFER_BIT);

    // Desativando a opção de repetir uma tecla quando ela é continua apertada
    glutSetKeyRepeat(0);

    // Maquinas de estado
    tela = 0;
    cursor.x = 0;
    cursor.y = 0;
    cursor.z = 0;
	
    wallpaper_menu.textura = loadTexture("../Imagens/wallpaper_menu.png");
    jogar.textura = loadTexture("../Imagens/jogar_branco.png");
    controles.textura = loadTexture("../Imagens/controles_branco.png");
    creditos.textura = loadTexture("../Imagens/creditos_branco.png");
    sair_menu.textura = loadTexture("../Imagens/sair_branco.png");
    sair_creditos.textura = loadTexture("../Imagens/sair_branco.png");
    wallpaper_creditos.textura = loadTexture("../Imagens/wallpaper_creditos.png");

    float matAmbAndDif[4] = {1.0, 1.0, 1.0, 1.0};    // vetor cor ambiente e difusa: branca
    float matShine[] = {5};                          // expoente especular (shininess)
    int light = 0;
}

void attPosicao()
{
    // Objetos gerais
    wallpaper_menu.dimensoes.x = largura;
    wallpaper_menu.dimensoes.y = altura;
    wallpaper_menu.posicao.x = largura/2;
    wallpaper_menu.posicao.y = altura/2;

    jogar.dimensoes.x = largura/6;
    jogar.dimensoes.y = altura/12;
    jogar.posicao.x = largura/5;
    jogar.posicao.y = altura/2 - altura/50;
    jogar.posicao.z = 0;

    controles.dimensoes.x = largura/4 - largura/50;
    controles.dimensoes.y = altura/12;
    controles.posicao.x = largura/6;
    controles.posicao.y = altura/4;

    creditos.dimensoes.x = largura/4 - largura/50;
    creditos.dimensoes.y = altura/12;
    creditos.posicao.x = largura/2 + largura/3;
    creditos.posicao.y = altura/2 - altura/50;

    sair_menu.dimensoes.x = largura/8;
    sair_menu.dimensoes.y = altura/12;
    sair_menu.posicao.x = largura/2 + largura/3 - largura/20;
    sair_menu.posicao.y = altura/4;

    sair_creditos.dimensoes.x = largura/8;
    sair_creditos.dimensoes.y = altura/12;
    sair_creditos.posicao.x = largura/2 + largura/3;
    sair_creditos.posicao.y = altura/4;

    wallpaper_creditos.dimensoes.x = largura;
    wallpaper_creditos.dimensoes.y = altura;
    wallpaper_creditos.posicao.x = largura/2;
    wallpaper_creditos.posicao.y = altura/2;
}

void setupJogo(){
    // Carregando objetos
    // Nessa ordem
    // TAMANHO é a variavel global de parametrização de tamanho para as coisas
    /* Para dar ctrl C

    carregaOBJ(&, glmReadOBJ("../pontos_obj/.obj"));
    setPosicao(&,0,0,0);
    setDimensoesProp(&,TAMANHO);
    */

    //só teste algum obj q precisa desenhando-o no centro(acima do chão) com dimensão TAMANHO
    //carregaOBJ(&OBJ, glmReadOBJ("../pontos_obj/lanchonete.obj"));

    carregaOBJ(&poste, glmReadOBJ("../pontos_obj/poste.obj"));
    setPosicao(&poste,0,0,0);
    setDimensoesProp(&poste,TAMANHO*1.6/2);

    carregaOBJ(&arvore1, glmReadOBJ("../pontos_obj/arvore_1.obj"));
    setPosicao(&arvore1,0,0,0);
    setDimensoesProp(&arvore1,TAMANHO);

    carregaOBJ(&arvore2, glmReadOBJ("../pontos_obj/arvore_2.obj"));
    setPosicao(&arvore2,0,0,0);
    setDimensoesProp(&arvore2,TAMANHO);

    carregaOBJ(&arvore_morta, glmReadOBJ("../pontos_obj/arvore_morta.obj"));
    setPosicao(&arvore_morta,0,0,0);
    setDimensoesProp(&arvore_morta,TAMANHO);

    carregaOBJ(&terreno, glmReadOBJ("../pontos_obj/terreno.obj"));
    setDimensoesDesprop(&terreno,TAMANHO*3,TAMANHO,TAMANHO*3);
    setPosicao(&terreno, 0,0,0);

    carregaOBJ(&fonte, glmReadOBJ("../pontos_obj/fonte.obj"));
    setDimensoesProp(&fonte, TAMANHO+TAMANHO/3);
    setPosicao(&fonte,0,0,0);

    carregaOBJ(&pipoca, glmReadOBJ("../pontos_obj/pipoca.obj"));
    setDimensoesProp(&pipoca, TAMANHO/2.3);
    setPosicao(&pipoca, -30, 0,-10);

    carregaOBJ(&pipoca1, glmReadOBJ("../pontos_obj/pipoca.obj"));
    setDimensoesProp(&pipoca1, TAMANHO/2.3);
    setPosicao(&pipoca1, -30, 0,10);
  
    carregaOBJ(&banco, glmReadOBJ("../pontos_obj/banco.obj"));
    setPosicao(&banco, 0,0,0);
    setDimensoesProp(&banco, TAMANHO/2.8);

    carregaOBJ(&terreno_rua, glmReadOBJ("../pontos_obj/terreno_rua_quadrado.obj"));
    setPosicao(&terreno_rua, 0,0,0);
    setDimensoesProp(&terreno_rua,TAMANHO/2);

    carregaOBJ(&terreno_rcurva, glmReadOBJ("../pontos_obj/terreno_rua_curva.obj"));
    setPosicao(&terreno_rcurva, 0,0,0);
    setDimensoesProp(&terreno_rcurva,TAMANHO*1.26);

    carregaOBJ(&cerca, glmReadOBJ("../pontos_obj/cerca.obj"));
    setPosicao(&cerca,0,0,0);
    setDimensoesProp(&cerca, TAMANHO);


    carregaOBJ(&rodaGG_base, glmReadOBJ("../pontos_obj/base_roda_gigante.obj"));
    setPosicao(&rodaGG_base,0,0,0);
    setDimensoesProp(&rodaGG_base,TAMANHO);
    carregaOBJ(&rodaGG_aro, glmReadOBJ("../pontos_obj/aro_roda_gigante.obj"));
    setPosicao(&rodaGG_aro,0,0,0);
    setDimensoesProp(&rodaGG_aro,TAMANHO);
    carregaOBJ(&rodaGG_carro, glmReadOBJ("../pontos_obj/carrinho_vermelho.obj"));
    setPosicao(&rodaGG_carro,0,0,0);
    setDimensoesProp(&rodaGG_carro,TAMANHO/5);

    carregaOBJ(&pedra_3, glmReadOBJ("../pontos_obj/pedra_3.obj"));
    setPosicao(&pedra_3, 0,0,0);
    setDimensoesDesprop(&pedra_3, 100,1,1);

}
