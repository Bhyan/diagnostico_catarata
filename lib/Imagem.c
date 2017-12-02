#include <stdio.h>
#include <stdlib.h>
#include "Imagem.h"


RGB **imagem_ppm(char *nome, int *linhas, int *colunas){
    FILE *img;
    RGB **imagem;
    int cor, i, j;
    char temp[100];

    /* 
     * O formato de imagem ppm tem a seguinte estrutura, um cabeçalho, onde
     * esta contido o tipo do formato "magic number", nessa função e tratado o formato P3,
     * um comentário feito pelo criador da imagem, seguido por dois inteiros
     * onde se encontra o número de colunas e linhas, que no momento da
     * exibição dará o tamanho da imagem em pixel, o padrão de cor, no caso o
     * valor máximo que pode esta contido em dentro de um pixel nessa imagem,
     * novamente trabalhamos com o padrão, que é 255. Por ultimo temos uma
     * sequencia de números inteiros, onde cada trinca de valor será a
     * representação de um pixel, red, green e blue (rgb) respectivamente.
    */

    img = fopen(nome, "r"); //Abrindo imagem.
    
    if(img == NULL){ //Teste se abriu o arquivo.
        printf("Erro na abertura da imagem.\n");
        exit(1);
    }
    
    else{

        /* 
         * Como os valores de cabeçalho é cor são padrões, optamos não
         * armazena-los. O comentário não e algum essencial para a geração da
         * imagem, novamente preferi descartá-lo para não ter que retorna-lo em
         * todas as funções.
        */

        fgets(temp, 100, img); //Ler o cabeçalho. Descarta o valor.
        fgets(temp, 100, img); //Ler o comentário. Descarta o valor.
        fscanf(img, "%d %d", colunas, linhas); //Ler os valores de linhas e colunas.
        fscanf(img, "%d", &cor); //Ler o padrão de cor. Descarta o valor.
    }

    imagem = malloc(*linhas * sizeof(RGB *)); //Alocando a memória para as linhas da matriz.

    if(imagem == NULL){ //Teste se ocorreu a alocação das linhas na memoria.
        printf("Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    for(i = 0; i < *linhas; i ++){ //Alocando a memória para as colunas da matriz.
        imagem[i] = malloc(*colunas * sizeof(RGB));
        if(imagem[i] == NULL){ //Teste se alocou a memoria para a coluna. Testa coluna a coluna.
            printf("Erro ao alocar memória para a coluna[%d] da imagem.\n", i);
            exit(1);
        }
    }

    for(i = 0; i < *linhas; i ++){ //Leitura e armazenamento da imagem na estrutura RGB.
        for(j = 0; j < *colunas; j ++){
            fscanf(img, "%d %d %d", &imagem[i][j].red, &imagem[i][j].green, &imagem[i][j].blue);
        }
    }

    fclose(img);

    return imagem;
}

RGB **escala_cinza(RGB **img, int *linhas, int *colunas){
    int cinza, i, j;
    RGB **imagem;

    /* 
     * Transforma cada pixel de colorido para escala de cinza. É
     * utilizado o fator de luminância para isso. O algorítimo consiste
     * em criar uma nova cor com 30% de vermelho, 59% de verde e 11% de
     * azul, gerando assim um novo pixel de cor cinza ao olho humano.
    */

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            cinza = img[i][j].red * 0.3 + img[i][j].green * 0.59 + img[i][j].blue * 0.11;
            imagem[i][j].red = cinza;
            imagem[i][j].green = cinza;
            imagem[i][j].blue = cinza;
        }
    }

    return imagem;
}

//Função auxiliar, utilizada para checagem visual dos filtros.
void cria_imagem_ppm(RGB **img, char *nome, int *linhas, int *colunas){
    FILE *imagem;
    int i, j;

    imagem = fopen(nome , "w");

    if(imagem == NULL){
        printf("Erro na criação da imagem.\n"); //Testa se o arquivo foi criado.
        exit(1);
    }

    fprintf(imagem, "P3\n"); //Escreve o cabeçalho da imagem de entrada.
    fprintf(imagem, "# %s\n", nome); //Escreve um comentário, neste caso o endereço e o nome do arquivo de saída.
    fprintf(imagem, "%d %d\n", *colunas, *linhas); //Escreve os valores de colunas e as linhas.
    fprintf(imagem, "255\n"); //Escreve o padrão de cor.

    for(i = 0; i < *linhas; i ++){ //Escreve os pixeis.
        for(j = 0; j < *colunas; j ++){
            fprintf(imagem, "%d %d %d\n", img[i][j].red, img[i][j].green, img[i][j].blue);
        }
    }

    fclose(imagem);
}

/* 
 * Função auxiliar. Por opção de estrutura, foi preferido alocar uma nova área
 * de memoria em cada função que manipula a imagem, evitando assim erros futuros
 * por esta manipulando a mesma área de memoria desde o inicio da alocação.
*/
RGB **alocar_imagem(int *linhas, int *colunas){
    RGB **imagem;
    int i;

    imagem = malloc(*linhas * sizeof(RGB *)); //Alocando a memória para as linhas da matriz.

    if(imagem == NULL){ //Teste se ocorreu a alocação de memoria.
        printf("Erro ao alocar memória para a imagem.\n");
        exit(1);
    }

    for(i = 0; i < *linhas; i ++){ //Alocando a memória para as colunas da matriz.
        imagem[i] = malloc(*colunas * sizeof(RGB));
        if(imagem[i] == NULL){ //Teste se alocou a memoria para a coluna. Testa coluna por coluna.
            printf("Erro ao alocar memória para a coluna[%d] da imagem.\n", i);
            exit(1);
        }
    }

    return imagem;
}
