#ifndef _IMAGEM_H
#define _IMAGEM_H

typedef struct rgb{
    int red;
    int green;
    int blue;
} RGB;

RGB **imagem_ppm(char *nome_imagem);

void escala_cinza(RGB **img, int linhas, int colunas, int cor, char *comentario, char *cabecalho);

#endif
