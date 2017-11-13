#include <stdio.h>
#include <stdlib.h>
#include "Imagem.h"


RGB **imagem_ppm(char *nome){
    FILE *imagem;
    RGB **img;
    int linhas, colunas, cor, i, j;
    char comentario[100], cabecalho[5];

    imagem = fopen(nome, "r"); //Abrindo imagem.
    
    if(imagem == NULL){ //Teste se abriu o arquivo.
        printf("Erro na abertura da imagem.\n");
        exit(1);
    }
    
    else{
        fgets(cabecalho, 5, imagem); //Ler o cabeçalho. Padrão P3.
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
            printf("Erro ao alocar memória para a coluna[%d] da imagem.\n", i);
            exit(1);
        }
    }

    for(i = 0; i < linhas; i ++){ //Leitura da imagem e salvamento dos valores na estrutura RGB.
        for(j = 0; j < colunas; j ++){
            fscanf(imagem, "%d %d %d", &img[i][j].red, &img[i][j].green, &img[i][j].blue);
        }
    }

    fclose(imagem);

    return img;

}

void escala_cinza(RGB **img, int linhas, int colunas, int cor, char *comentario, char *cabecalho){
    FILE *imagem_cinza;
    int cinza, i, j;

    imagem_cinza = fopen("./images/cinza.tmp", "w");
    /* Novo arquivo, onde recebera a copia da imagem de entrada
     * porem em tons de cinza. Daqui para a frente trabalhar com
     * essa imagem.
    */

    fprintf(imagem_cinza, "%s", cabecalho); // Escreve o cabeçalho da imagem de entrada.
    fprintf(imagem_cinza, "%s", comentario); // Escreve qualquer comentário que existia na imagem original.
    fprintf(imagem_cinza, "%d %d\n", colunas, linhas); // Escreve as colunas e as linhas.
    fprintf(imagem_cinza, "%d\n", cor); //Escreve o padrão de cor.

    for(i = 0; i < linhas; i ++){
        for(j = 0; j < colunas; j ++){
            cinza = img[i][j].red * 0.3 + img[i][j].green * 0.59 + img[i][j].blue * 0.11;
            /* Transforma cada pixel de colorido para escala de cinza. É
             * utilizado o fator de luminância para isso. O algorítimo consiste
             * em criar uma nova cor com 30% de vermelho, 59% de verde e 11% de
             * azul, gerando assim um novo pixel de cor cinza ao olho humano.
            */
            fprintf(imagem_cinza, "%d %d %d\n", cinza, cinza, cinza);
        }
    }

    fclose(imagem_cinza);
}
