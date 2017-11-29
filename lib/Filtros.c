#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Imagem.h"
#include "Filtros.h"


RGB **convulacao(RGB **img, int *linhas, int *colunas, int k_linhas, int k_colunas, int kernel[][k_colunas], 
                int divisor){
    RGB aux, **imagem;
    int i, j, x, y, k_i, k_j; // Contadores.

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            aux.red = 0;
            aux.green = 0;
            aux.blue = 0;
            for(x = 0, k_i = - k_linhas / 2; x < k_linhas; x ++, k_i ++){
                for(y = 0, k_j = - k_colunas / 2; y < k_colunas; y ++, k_j ++){
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

RGB **filtro_gaussiano(RGB **img, int *linhas, int *colunas){
    RGB **imagem;
    int kernel[5][5] = {{ 2,  4,  5,  4, 2 },
                        { 4,  9, 12,  9, 4 },
                        { 5, 12, 15, 12, 5 },
                        { 4,  9, 12,  9, 4 },
                        { 2,  4,  5,  4, 2 }};

    imagem = convulacao(img, linhas, colunas, 5, 5, kernel, 159);

    return imagem;
}

RGB **filtro_sobel(RGB **img, int *linhas, int *colunas){
    RGB **img_v, **img_h, **imagem;
    int i, j, angulo[*linhas][*colunas];
    double teta, pi = 3.14159265;
    int sobel_vertical[3][3] = {{ 1, 0, -1},
                                { 2, 0, -2},
                                { 1, 0, -1}};

    int sobel_horizontal[3][3] = {{ 1,  2, 1 },
                                  { 0,  0, 0 },
                                  {-1, -2, -1}};

    img_v = convulacao(img, linhas, colunas, 3, 3, sobel_vertical, 1);
    img_h = convulacao(img, linhas, colunas, 3, 3, sobel_horizontal, 1);

    imagem = alocar_imagem(linhas, colunas);

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            imagem[i][j].red = sqrt((img_v[i][j].red * img_v[i][j].red) +
                                    (img_h[i][j].red * img_h[i][j].red));
            imagem[i][j].green = sqrt((img_v[i][j].green * img_v[i][j].green) +
                                    (img_h[i][j].green * img_h[i][j].green));
            imagem[i][j].blue = sqrt((img_v[i][j].blue * img_v[i][j].blue) +
                                    (img_h[i][j].blue * img_h[i][j].blue));

            teta = atan2(img_v[i][j].red, img_h[i][j].red) * 180.0 / pi;

            if((teta >= 0.0 && teta < 22.5) || (teta >= 157.5 && teta < 180.0)){
                angulo[i][j] = 0;
            }
            else if(teta >= 22.5 && teta < 67.5){
                angulo[i][j] = 1;
            }
            else if(teta >= 67.5 && teta < 112.5){
                angulo[i][j] = 2;
            }
            else{
                angulo[i][j] = 3;
            }
        }
    }

    imagem = realce_aresta(imagem, linhas, colunas, angulo);

    return imagem;
}

RGB **realce_aresta(RGB **img, int *linhas, int *colunas, int angulo[][*colunas]){
    int i, j;

    for(i = 0; i < *linhas; i ++){
        for(j = 0; j < *colunas; j ++){
            switch(angulo[i][j]){
                case 0:
                    if(j - 1 >= 0 && j + 1 < *colunas){
                        if(img[i][j].red < img[i][j - 1].red || img[i][j].red < img[i][j + 1].red){
                            img[i][j].red = 0;
                            img[i][j].green = 0;
                            img[i][j].blue = 0;
                        }
                    }
                    break;
                case 1:
                    if(i + 1 < *linhas && j - 1 >= 0 && i - 1 >= 0 && j + 1 < *colunas){
                        if(img[i][j].red < img[i + 1][j - 1].red || img[i][j].red < img[i - 1][j + 1].red){
                            img[i][j].red = 0;
                            img[i][j].green = 0;
                            img[i][j].blue = 0;
                        }
                    }
                    break;
                case 2:
                    if(i - 1 >= 0 && i + 1 < *linhas){
                        if(img[i][j].red < img[i - 1][j].red || img[i][j].red < img[i + 1][j].red){
                            img[i][j].red = 0;
                            img[i][j].green = 0;
                            img[i][j].blue = 0;
                        }
                    }
                    break;
                case 3:
                    if(i - 1 >= 0 && j - 1 >= 0 && i + 1 < *linhas && j + 1 < *colunas){
                        if(img[i][j].red < img[i - 1][j - 1].red || img[i][j].red < img[i + 1][j + 1].red){
                            img[i][j].red = 0;
                            img[i][j].green = 0;
                            img[i][j].blue = 0;
                        }
                    }
                    break;
            }

            if(img[i][j].red >= 75){
                img[i][j].red = 255;
                img[i][j].green = 255;
                img[i][j].blue = 255;
            }
            else if(img[i][j].red < 30){
                img[i][j].red = 0;
                img[i][j].green = 0;
                img[i][j].blue = 0;
            }
            else{
                img[i][j].red = 100;
                img[i][j].green = 100;
                img[i][j].blue = 100;
            }
        }
    }

    return img;
}
