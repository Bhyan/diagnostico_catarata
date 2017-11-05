#include <stdlib.h>
#include "CUnit/Basic.h"
#include "Imagem.h"


void teste_input();

int main(){
    CU_initialize_registry();

    CU_pSuite teste = CU_add_suite("Suite de teste", NULL, NULL);

    CU_add_test(teste, "teste_input", teste_input);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

void teste_input(){
    //Teste de passagem de paramentros para o o main do programa.
    system("../bin/main -i imagem.ppm -f ppm -o diagnostico.txt");
}
