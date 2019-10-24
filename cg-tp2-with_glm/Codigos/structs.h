// Struct de x e y
typedef struct vetorR3
{
    GLfloat x;
    GLfloat y;
    GLfloat z;

} vetorR3;

// Objetos não animados
typedef struct spriteObject
{
    vetorR3 posicao;
    vetorR3 dimensoes;
    GLuint textura;

} spriteObject;

typedef struct Objeto3D
{
	vetorR3 posicao;
	vetorR3 dimensoes;
	vetorR3 aumento;
	GLuint listaVisualizacao;
} Objeto3D;
