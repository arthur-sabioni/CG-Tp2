CC=gcc
OPCOES_COMPILADOR= -lglut -lGL -lSOIL -lGLEW -lGLU -lSDL -lSDL_mixer -lm -std=gnu11
TODOS_ARQUIVOS_PONTOH =  
TODOS_ARQUIVOS_OBJ = main.o glm.o glmimg.o glm_util.o


%.o: ../Codigos/%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	./main

clean:
	rm *.o main
