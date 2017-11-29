#include <stdio.h>
#include <stdlib.h>
#include "Imagem.h"


RGB **imagem_ppm(char *nome, int *linhas, int *colunas){
    FILE *imagem;
    RGB **img;
    int cor, i, j;
    char temp[100];

    imagem = fopen(nome, "r"); //Abrindo imagem.
    
    if(imagem == NULL){ //Teste se abriu o arquivo.
        fprintf(stderr, "Erro na abertura da imagem.\n");
        exit(1);
    }
    
    else{
        fgets(temp, 100, imagem); //Ler o cabeçalho. Padrão P3. Descarta valor.
        fgets(temp, 100, imagem); //Ler o comentário. Descarta valor.
        fscanf(imagem, "%d %d", colunas, linhas); //Ler os valores de linhas e colunas.
        fscanf(imagem, "%d", &cor); //Ler o padrão de cor. Padrão e 255.
    }

    img = malloc(*linhas * sizeof(RGB *)); //Alocando a memória para as linhas da matriz.

    if(img == NULL){ //Teste se ocorreu a alocação de memoria.
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    for(i = 0; i < *linhas; i ++){ //Alocando a memória para as colunas da matriz.
        img[i] = malloc(*colunas * sizeof(RGB));
        if(img[i] == NULL){ //Teste se alocou a memoria para a linha. Testa linha por linha.
            fprintf(stderr, "Erro ao alocar memória para a coluna[%d] da imagem.\n", i);
            exit(1);
        }
    }

    for(i = 0; i < *linhas; i ++){ //Leitura da imagem e salvamento dos valores na estrutura RGB.
        for(j = 0; j < *colunas; j ++){
            fscanf(imagem, "%d %d %d", &img[i][j].red, &img[i][j].green, &img[i][j].blue);
        }
    }

    fclose(imagem);

    return img;
}

RGB **escala_cinza(RGB **img, int *linhas, int *colunas){
    int cinza, i, j;

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            cinza = img[i][j].red * 0.3 + img[i][j].green * 0.59 + img[i][j].blue * 0.11;
            /* Transforma cada pixel de colorido para escala de cinza. É
             * utilizado o fator de luminância para isso. O algorítimo consiste
             * em criar uma nova cor com 30% de vermelho, 59% de verde e 11% de
             * azul, gerando assim um novo pixel de cor cinza ao olho humano.
            */
            img[i][j].red = cinza;
            img[i][j].green = cinza;
            img[i][j].blue = cinza;
        }
    }

    return img;
}

void cria_imagem_ppm(RGB **img, char *nome, int *linhas, int *colunas){
    FILE *imagem;
    int i, j;

    imagem = fopen(nome , "w");

    if(imagem == NULL){
        fprintf(stderr, "Erro na criação da imagem.\n");
        exit(1);
    }

    fprintf(imagem, "P3\n"); //Escreve o cabeçalho da imagem de entrada.
    fprintf(imagem, "# Teste\n"); //Escreve qualquer comentário que existia na imagem original.
    fprintf(imagem, "%d %d\n", *colunas, *linhas); //Escreve as colunas e as linhas.
    fprintf(imagem, "255\n"); //Escreve o padrão de cor.

    for(i = 0; i < *linhas; i ++){ //Escreve os pixeis.
        for(j = 0; j < *colunas; j ++){
            fprintf(imagem, "%d %d %d\n", img[i][j].red, img[i][j].green, img[i][j].blue);
        }
    }

    fclose(imagem);
}

RGB **alocar_imagem(int *linhas, int *colunas){
    RGB **img;
    int i;

    img = malloc(*linhas * sizeof(RGB *)); //Alocando a memória para as linhas da matriz.

    if(img == NULL){ //Teste se ocorreu a alocação de memoria.
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    for(i = 0; i < *linhas; i ++){ //Alocando a memória para as colunas da matriz.
        img[i] = malloc(*colunas * sizeof(RGB));
        if(img[i] == NULL){ //Teste se alocou a memoria para a linha. Testa linha por linha.
            fprintf(stderr, "Erro ao alocar memória para a coluna[%d] da imagem.\n", i);
            exit(1);
        }
    }

    return img;
}
