#include <stdlib.h>
#include "CUnit/Basic.h"
#include "Imagem.h"


void teste_imagem_ppm();

int main(){
    CU_initialize_registry();

    CU_pSuite teste = CU_add_suite("Suite de teste", NULL, NULL);

    CU_add_test(teste, "Teste alocação de imagem ppm.", teste_imagem_ppm);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

void teste_imagem_ppm(){
    RGB **imagem;
    FILE *imagem_fake;
    int i, j, red, green, blue;
    char temp[100];

    imagem = imagem_ppm("./images/imagem_teste.ppm");

    imagem_fake = fopen("./images/imagem_teste.ppm", "r");

    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);
    fgets(temp, 100, imagem_fake);

    for(i = 0; i < 4; i ++){
        for(j = 0; j < 4; j ++){
            fscanf(imagem_fake,"%d %d %d", &red, &green, &blue);
            CU_ASSERT_EQUAL(red, imagem[i][j].red);
            CU_ASSERT_EQUAL(green, imagem[i][j].green);
            CU_ASSERT_EQUAL(blue, imagem[i][j].blue);
        }
    }

    fclose(imagem_fake);

}
