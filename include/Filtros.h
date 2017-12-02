#ifndef _FILTROS_H
#define _FILTROS_H

RGB **filtro_gaussiano(RGB **img, int *linhas, int *colunas);

RGB **filtro_sobel(RGB **img, int *linhas, int *colunas);

RGB **convolucao(RGB **img, int *linhas, int *colunas, int k_linhas, int k_colunas, int kernel[][k_colunas], int divisor);

RGB **realce_aresta(RGB **img, int *linhas, int *colunas, int angulo[][*colunas]);

RGB **binarizacao(RGB **img, int *linhas, int *colunas);

#endif
