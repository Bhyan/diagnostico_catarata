#include <stdio.h>
#include "Imagem.h"
#include "Filtros.h"


RGB **convolucao(RGB **img, int *linhas, int *colunas, int k_lin, int k_col, int kernel[][k_col]){
    int i, j, k_i, k_j, soma, div;

    for(i = 0; i < *linhas; i ++){// Percorre imagem.
        for(j = 0; j < *colunas; j ++){
            soma = 0;
            div = 0;

            for(k_i = -2; k_i < 2; k_i ++){// Percorre o kernel.
                for(k_j = -2; k_j < 2; k_j ++){
                    if((i + k_i >= 0 && i + k_i < *linhas) && (j + k_j >= 0 && j + k_j < *colunas)){
                        soma += img[i + k_i][j + k_j].red * kernel[k_i + 2][k_j + 2];
                        div += kernel[k_i + 2][k_j + 2];
                    }
                }
            }

            if(div != 0){ //Para não ocorrer divisão por zero.
                img[i][j].red = soma / div;
                img[i][j].green = soma / div;
                img[i][j].blue = soma / div;
            }
        }
    }

    return img;
}

RGB **filtro_gaussiano(RGB **img, int *linhas, int *colunas){
    RGB **imagem;
    int kernel[5][5] = {{ 2,  4,  5,  4, 2 },
                        { 4,  9, 12,  9, 4 },
                        { 5, 12, 15, 12, 5 },
                        { 4,  9, 12,  9, 4 },
                        { 2,  4,  5,  4, 2 }};

    imagem = convolucao(img, linhas, colunas, 5, 5, kernel);

    return imagem;
}
