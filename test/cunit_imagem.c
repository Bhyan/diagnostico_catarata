#include <stdlib.h>
#include "CUnit/Basic.h"
#include "Imagem.h"


void criar_imagem();
void teste_imagem_ppm();
void teste_escala_cinza();

int main(){
    criar_imagem();// Cria imagem.

    CU_initialize_registry();

    CU_pSuite teste = CU_add_suite("Suite de teste", NULL, NULL);

    CU_add_test(teste, "Teste alocação de imagem ppm.", teste_imagem_ppm);
    CU_add_test(teste, "Teste escala de cinza.", teste_escala_cinza);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    system("rm images/imagem_teste.ppm");// Remove imagem criada.
    return CU_get_error();
}

void teste_imagem_ppm(){
    RGB **imagem;
    FILE *imagem_fake;
    int i, j, red, green, blue, linhas, colunas;
    char temp[100];

    imagem = imagem_ppm("./images/imagem_teste.ppm", &linhas, &colunas);

    imagem_fake = fopen("./images/imagem_teste.ppm", "r");

    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);

    for(i = 0; i < linhas; i ++){
        for(j = 0; j < colunas; j ++){
            fscanf(imagem_fake,"%d %d %d", &red, &green, &blue);
            CU_ASSERT_EQUAL(red, imagem[i][j].red);
            CU_ASSERT_EQUAL(green, imagem[i][j].green);
            CU_ASSERT_EQUAL(blue, imagem[i][j].blue);
        }
    }

    fclose(imagem_fake);

}

void teste_escala_cinza(){
    RGB **imagem;
    FILE *imagem_fake;
    int i, j, red, green, blue, linhas, colunas, cinza;
    char temp[100];

    imagem = imagem_ppm("./images/imagem_teste.ppm", &linhas, &colunas);

    escala_cinza(imagem, &linhas, &colunas);

    imagem_fake = fopen("./images/imagem_teste.ppm", "r");

    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);

    for(i = 0; i < linhas; i ++){
        for(j = 0; j < colunas; j ++){
            fscanf(imagem_fake,"%d %d %d", &red, &green, &blue);

            cinza = red * 0.3 + green * 0.59 + blue * 0.11;

            CU_ASSERT_EQUAL(cinza, imagem[i][j].red);
            CU_ASSERT_EQUAL(cinza, imagem[i][j].green);
            CU_ASSERT_EQUAL(cinza, imagem[i][j].blue);
        }
    }

    fclose(imagem_fake);

}

void criar_imagem(){
    FILE *img;

    img = fopen("./images/imagem_teste.ppm", "w");

    fprintf(img, "P3\n");
    fprintf(img, "# example from the man page\n");
    fprintf(img, "4 4\n");
    fprintf(img, "15\n");
    fprintf(img, " 0  0  0    0  0  0    0  0  0   15  0 15\n");
    fprintf(img, " 0  0  0    0 15  7    0  0  0    0  0  0\n");
    fprintf(img, " 0  0  0    0  0  0    0 15  7    0  0  0\n");
    fprintf(img, "15  0 15    0  0  0    0  0  0    0  0  0");

    fclose(img);

}
