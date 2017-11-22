#ifndef _FILTROS_H
#define _FILTROS_H

RGB **convolucao(RGB **img, int *linhas, int *colunas, int k_lin, int k_col, int kernel[][k_col]);

RGB **filtro_gaussiano(RGB **img, int *linhas, int *colunas);

#endif
