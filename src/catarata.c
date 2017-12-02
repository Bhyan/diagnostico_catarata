#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Imagem.h"
#include "Filtros.h"


int main(int argc, char **argv) {
    RGB **img;
    int paramentros, linhas, colunas;
    char nome[25], formato[4], saida[25];

    if(argc == 1){ //Caso o usuário rode o programa sem nenhum parâmetro sera retornado o help.
        printf("-i   <input-image>\n"
                "-f   <input-image-format>\n"
                "-o   <diagnose-file>\n"
                "-h   <help>\n");
    }

    else{
        /* 
         * Função da biblioteca unistd. Usada para casar os paramentos -i, -f,
         * -o e o adicional -h para help, assim que casado ele pega o argumento
         * utilizando a função snprintf(variável que recebe o argumento, tamanho,
         * formato do argumento para leitura, e entrada padrão.
        */
        while((paramentros = getopt(argc, argv, "i:f:o:h")) != -1){
            switch(paramentros){
                case 'i':
                    snprintf(nome, 25, "%s", optarg); 
                    break;
                case 'f':
                    snprintf(formato, 4, "%s", optarg); 
                    break;
                case 'o':
                    snprintf(saida, 25, "%s", optarg); 
                   break;
                case 'h':
                    printf("-i   <input-image>\n"
                            "-f   <input-image-format>\n"
                            "-o   <diagnose-file>\n"
                            "-h   <help>\n");
                    break;
            }
        }
    }

    if(strcmp(formato, "ppm\n") != 0){
        img = imagem_ppm(nome, &linhas, &colunas);
        img = escala_cinza(img, &linhas, &colunas);
        cria_imagem_ppm(img, "./images/cinza.ppm", &linhas, &colunas); // Cria imagem para teste visual.
        img = filtro_gaussiano(img, &linhas, &colunas);
        cria_imagem_ppm(img, "./images/gauss.ppm", &linhas, &colunas); // Cria imagem para teste visual.
        img = filtro_sobel(img, &linhas, &colunas);
        cria_imagem_ppm(img, "./images/sobel.ppm", &linhas, &colunas); // Cria imagem para teste visual.
        img = binarizacao(img, &linhas, &colunas);
        cria_imagem_ppm(img, "./images/binarizada.ppm", &linhas, &colunas); // Cria imagem para teste visual.
    }

    return 0;
}
