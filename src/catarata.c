#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Imagem.h"


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
        /*Função da biblioteca unistd. Usada para casar os paramentos -i, -f,
         * -o e o adicional -h para help, assim que casado ele pega o argumento
         *  utilizando a função snprintf(variável que recebe o argumento, tamanho,
         *  formato do argumento para leitura, e entrada padrão.
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

    if(strcmp(formato, "ppm") == 0){// Alterado para passar e chamar a função.
        img = imagem_ppm(nome, &linhas, &colunas);
        escala_cinza(img, &linhas, &colunas);
    }

    return 0;
}
