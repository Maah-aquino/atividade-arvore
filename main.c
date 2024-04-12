#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(){
    Arvore *arvore = arvore_cria();
    arvore_inserir(arvore, 10);
    arvore_inserir(arvore, 0);
    arvore_inserir(arvore, 20);
    arvore_inserir(arvore, 5);
    arvore_inserir(arvore, 25);

     printf("Elementos da arvore em ordem crescente:\n");
    arvore_imprimir(arvore);
    printf("\n");

    printf("%d\n", arvore_busca(arvore, 0));
    printf("%d\n", arvore_busca(arvore, 10));
    printf("%d\n", arvore_busca(arvore, 15));
    printf("%d\n", arvore_busca(arvore, 25));

     // Remover um nó (p or exemplo, 20)
    arvore_apagar(arvore,20);

    // Imprimir novamente para verificar a remoção
    printf("Elementos da arvore após remoção de 20:\n");
    arvore_imprimir(arvore);
    printf("\n");

   //void arvore_imprimir(No->raiz);

   return 0;
}