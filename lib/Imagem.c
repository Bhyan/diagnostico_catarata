#include <stdio.h>
#include <stdlib.h>
#include "Imagem.h"


typedef struct rgb{
    int red;
    int green;
    int blue;
} RGB;

void imagem_ppm(char *nome){
    FILE *imagem;
    RGB **img;
    int linhas, colunas, cor, i, j;
    char comentario[100], temp[5];

    imagem = fopen(nome, "r"); //Abrindo imagem.
    
    if(imagem == NULL){ //Teste se abriu o arquivo.
        printf("Erro na abertura da imagem.\n");
        exit(1);
    }
    
    else{
        fgets(temp, 5, imagem); //Ler o cabeçalho é descarta. Padrão P3.
        fgets(comentario, 100, imagem); //Ler o comentario.
        fscanf(imagem, "%d %d", &colunas, &linhas); //Ler os valores de linhas e colunas.
        fscanf(imagem, "%d", &cor); //Ler o padrão de cor. Padão e 255.
    }

    img = malloc(linhas * sizeof(RGB *)); //Alocando a memória para as linhas da matriz.

    if(img == NULL){ //Teste se ocorreu a alocação de memoria.
        printf("Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    for(i = 0; i < linhas; i ++){ //Alocando a memória para as colunas da matriz.
        img[i] = malloc(colunas * sizeof(RGB));
        if(img[i] == NULL){ //Teste se alocou a memoria para a linha. Testa linha por linha.
            printf("Erro ao alocar memória para a imagem.\n");
            exit(1);
        }
    }

    for(i = 0; i < linhas; i ++){ //Leitura da imagem e salvamento dos valores na estrutura RGB.
        for(j = 0; j < colunas; j ++){
            fscanf(imagem, "%d %d %d", &img[i][j].red, &img[i][j].green, &img[i][j].blue);
        }
    }

    fclose(imagem);

}
