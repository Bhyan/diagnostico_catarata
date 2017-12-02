#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Imagem.h"
#include "Filtros.h"

/*
 * Em matemática a convolução é uma operação matemática em duas funções (no nosso caso, a
 * imagem e o kernel) para produzir uma terceira função, que normalmente é vista como uma 
 * versão modificada de uma das funções originais.
*/ 
RGB **convolucao(RGB **img, int *linhas, int *colunas, int k_linhas, int k_colunas, int kernel[][k_colunas], 
                int divisor){
    RGB aux, **imagem;
    int i, j, x, y, k_i, k_j; //Contadores.

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){ //Percorre a imagem.
        for(j = 0; j < *colunas; j ++){
            aux.red = 0;
            aux.green = 0;
            aux.blue = 0;
            for(x = 0, k_i = - k_linhas / 2; x < k_linhas; x ++, k_i ++){ //Percorre a matriz kernel.
                for(y = 0, k_j = - k_colunas / 2; y < k_colunas; y ++, k_j ++){
                    /* 
                     * Testa se esta dentro da imagem, evitando entrar em
                     * memoria não alocada. 
                    */
                    if((i + k_i >= 0 && i + k_i < *linhas) && (j + k_j >= 0 && j + k_j < *colunas)){
                        aux.red += (img[i + k_i][j + k_j].red * kernel[x][y]) / divisor;
                        aux.green += (img[i + k_i][j + k_j].green * kernel[x][y]) / divisor;
                        aux.blue += (img[i + k_i][j + k_j].blue * kernel[x][y]) / divisor;
                    }
                }
            }
            imagem[i][j] = aux;
        }
    }

    return imagem;
}

/*
 * Uma função gaussiana é aquela que apresenta seu gráfico em forma de sino,
 * transportando isso para um gráfico 3D teremos algum similar a um vulcão,
 * onde seu maior valor (ou pico) se encontra no valor mas alto. Sendo assim o
 * nosso kernel tem que obedecer essa propriedade, como essa e a matriz dada no
 * projeto, preferimos utiliza-la, porem qualquer matriz que obedeça essa
 * propriedade poderia ser utilizada.
*/ 
RGB **filtro_gaussiano(RGB **img, int *linhas, int *colunas){
    RGB **imagem;
    int kernel[5][5] = {{ 2,  4,  5,  4, 2 },
                        { 4,  9, 12,  9, 4 },
                        { 5, 12, 15, 12, 5 },
                        { 4,  9, 12,  9, 4 },
                        { 2,  4,  5,  4, 2 }};

    /*
     * O valor 159 passado para a função convolação, o divisor, é a soma de todos
     * os valores da matriz kernel. Os valores equivalentes a k_linhas é
     * k_colunas são os tamanhos da matriz, neste caso nosso kernel e uma
     * matriz 5 x 5.
    */
    imagem = convolucao(img, linhas, colunas, 5, 5, kernel, 159);

    return imagem;
}

/*
 * O filtro de Sobel e uma convolução, onde e utilizado duas matrizes, uma para
 * detectar o gradiente vertical da imagem original e outra vertical (gradiente
 * e o nome dado a um vetor que denota a menor distancia para o pico daquela
 * função). Apos mapeado os gradientes verticais e horizontais os valores são
 * combinados para gerar o valor máximo do gradiente (raiz quadrada da soma dos
 * quadrados do gradiente vertical e horizontal). Também e extraído o teta do
 * gradiente (tangente do gradiente vertical e horizontal).
*/ 
RGB **filtro_sobel(RGB **img, int *linhas, int *colunas){
    RGB **img_v, **img_h, **imagem;
    int i, j, angulo[*linhas][*colunas];
    float teta;
    int sobel_vertical[3][3] = {{ 1, 0, -1},
                                { 2, 0, -2},
                                { 1, 0, -1}};

    int sobel_horizontal[3][3] = {{ 1,  2, 1 },
                                  { 0,  0, 0 },
                                  {-1, -2, -1}};

    /* No filtro de Sobel, diferente do filtro gaussiano não existe a divisão
     * pela soma dos valores da matriz passada para realizar a convolução, para
     * reaproveitar o código e passado o valor 1 como divisor, por ser um
     * elemento neutro na divisão é não afetar o resultado da convolução.
     * Novamente em k_linhas e k_colunas e passado o tamanho da matriz, duas
     * matriz 3 x 3.
    */
    img_v = convolucao(img, linhas, colunas, 3, 3, sobel_vertical, 1);
    img_h = convolucao(img, linhas, colunas, 3, 3, sobel_horizontal, 1);

    imagem = alocar_imagem(linhas, colunas);

    // Combinação das duas matrizes de gradiente, gerando o valor máximo do gradiente.
    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            imagem[i][j].red = sqrt((img_v[i][j].red * img_v[i][j].red) +
                                    (img_h[i][j].red * img_h[i][j].red));
            imagem[i][j].green = sqrt((img_v[i][j].green * img_v[i][j].green) +
                                    (img_h[i][j].green * img_h[i][j].green));
            imagem[i][j].blue = sqrt((img_v[i][j].blue * img_v[i][j].blue) +
                                    (img_h[i][j].blue * img_h[i][j].blue));

            // Extração do ângulo teta dos gradientes.
            teta = atan2(img_v[i][j].red, img_h[i][j].red);

            /* Como recebe um valor float, aqui é feito o arredondamento dos
             * valores para ângulos inteiros e conhecidos (0º, 45º, 90º e
             * 135º).
            */
            if((teta >= 0.0 && teta < 22.5) || (teta >= 157.5 && teta < 180.0)){
                angulo[i][j] = 0;
            }
            else if(teta >= 22.5 && teta < 67.5){
                angulo[i][j] = 45;
            }
            else if(teta >= 67.5 && teta < 112.5){
                angulo[i][j] = 90;
            }
            else{
                angulo[i][j] = 135;
            }
        }
    }

    imagem = realce_aresta(imagem, linhas, colunas, angulo);

    return imagem;
}

/* 
 * O realce de aresta checa os valores do gradiente do pixel e do seu entorno,
 * se ele for o maior, o mesmo e mantido com seu valor original, caso exista um
 * valor maior na sua vizinhança, o pixel atual e zerado. E assim e feito para o
 * próximo pixel ate o fim da imagem.
*/
RGB **realce_aresta(RGB **img, int *linhas, int *colunas, int angulo[][*colunas]){
    RGB **imagem;
    int i, j;

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            switch(angulo[i][j]){
                case 0:
                    // Verifica se esta dentro da memoria alocada para a imagem.
                    if(i + 1 < *linhas && i - 1 >= 0 && j - 1 >= 0 && j + 1 < *colunas){
                        // Checa se o valor e o maior entre seu entorno.
                        if(img[i][j].red < img[i][j - 1].red || img[i][j].red < img[i][j + 1].red){
                            imagem[i][j].red = 0;
                            imagem[i][j].green = 0;
                            imagem[i][j].blue = 0;
                        }
                    }
                    break;
                case 45:
                    // Verifica se esta dentro da memoria alocada para a imagem.
                    if(i + 1 < *linhas && i - 1 >= 0 && j - 1 >= 0 && j + 1 < *colunas){
                        // Checa se o valor e o maior entre seu entorno.
                        if(img[i][j].red < img[i + 1][j - 1].red || img[i][j].red < img[i - 1][j + 1].red){
                            imagem[i][j].red = 0;
                            imagem[i][j].green = 0;
                            imagem[i][j].blue = 0;
                        }
                    }
                    break;
                case 90:
                    // Verifica se esta dentro da memoria alocada para a imagem.
                    if(i + 1 < *linhas && i - 1 >= 0 && j - 1 >= 0 && j + 1 < *colunas){
                        // Checa se o valor e o maior entre seu entorno.
                        if(img[i][j].red < img[i - 1][j].red || img[i][j].red < img[i + 1][j].red){
                            imagem[i][j].red = 0;
                            imagem[i][j].green = 0;
                            imagem[i][j].blue = 0;
                        }
                    }
                    break;
                case 135:
                    // Verifica se esta dentro da memoria alocada para a imagem.
                    if(i + 1 < *linhas && i - 1 >= 0 && j - 1 >= 0 && j + 1 < *colunas){
                        // Checa se o valor e o maior entre seu entorno.
                        if(img[i][j].red < img[i - 1][j - 1].red || img[i][j].red < img[i + 1][j + 1].red){
                            imagem[i][j].red = 0;
                            imagem[i][j].green = 0;
                            imagem[i][j].blue = 0;
                        }
                    }
                    break;
            }

            /*
             * Apos a checagem dos gradientes, alguns valores não foram
             * zerados, pois tinha o maior gradiente naquela região, sem assim
             * uma aresta. Para poder destacar melhor a divisão de cada
             * textura na imagem e necessário padronizar os valores restantes,
             * assim valores maiores ou iguais 75 mudara para 255 (branco),
             * maior que 35 e menor que 74 recebe o valor 0 (preto) e o
             * restante que não se encontra nesse intervalo recebe o valor 100
             * (valor intermediário, próximo a cinza). Esses valores de
             * intervalo são escolhidos testando visualmente, por isso algumas
             * imagens não apresenta divisão clara entre suas arestas. Esse
             * valor foi o melhor encontrado utilizando as imagens base como
             * referencia, é mesmo assim algumas imagens não tiveram um realce
             * satisfatório.
            */ 
            if(img[i][j].red >= 75){
                imagem[i][j].red = 255;
                imagem[i][j].green = 255;
                imagem[i][j].blue = 255;
            }
            else if(img[i][j].red < 35){
                imagem[i][j].red = 0;
                imagem[i][j].green = 0;
                imagem[i][j].blue = 0;
            }
            else{
                imagem[i][j].red = 100;
                imagem[i][j].green = 100;
                imagem[i][j].blue = 100;
            }
        }
    }

    return imagem;
}

/*
 * A binarização segue o mesmo principio da padronização de cor da função de
 * realce de aresta, porem aqui na saída só existira dois valores, 0 (preto)
 * ou 255 (branco). Novamente os valores de intervalo são encontrados testando
 * visualmente cada imagem.
*/ 
RGB **binarizacao(RGB **img, int *linhas, int *colunas){
    RGB **imagem;
    int i, j;

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            if(img[i][j].red >= 100){ //Valores de pixel maior ou igual a 100 recebem 255 (branco).
                imagem[i][j].red = 255;
                imagem[i][j].green = 255;
                imagem[i][j].blue = 255;
            }
            else{ //Menores que 100 recebem o valor 0 (preto).
                imagem[i][j].red = 0;
                imagem[i][j].green = 0;
                imagem[i][j].blue = 0;
            }
        }
    }

    return imagem;
}
