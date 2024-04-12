#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
/*Os comentáraios estão de acordo com o que foi pedido, copiei grande parte
do enunciado do exercício*/

typedef struct No{
    struct No* direita;
    struct No* esquerda;
    int valor;
}No;

typedef struct Arvore{
    No* raiz;
}Arvore;

/*Assim como nas outras TADs, para criar uma arvore só precisamos instanciar ela e
criar uma referência para o elemento(s) que serviram de referência para as operações.
Neste caso, apenas a raiz é o suficiente.*/
Arvore* arvore_cria(){
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

/*Para criar um nó e deixar o restante do código mais limpo e organizado*/
No* criar_no(int x){
    No* no = malloc(sizeof(No));
    no->direita = NULL;
    no->esquerda = NULL;
    no->valor = x;
    return no;
}
void arvore_inserir(Arvore* arvore, int x){
    //Neste ponto a árvore não existe.
    if (arvore == NULL)
        return;

    No* no = arvore->raiz;
    if (no == NULL){
        /*Caso a árvore ainda esteja vazia, o algoritmo 
         deve criar um novo nó com o valor a ser inserido 
        e colocá-lo como raiz da árvore*/
        arvore->raiz = criar_no(x);
    }else{
        //se a árvore não estiver vazia, vamos procurar onde inserir de forma recursiva
        //a recursividade vai deixar o código mais simples
        inserir(no, x);
    }
}

void inserir(No* no, int x){
    /*
    o algoritmo deve verificar se o valor a ser inserido é menor ou maior que o valor 
    do nó atual. Se for maior, o algoritmo deve verificar se o nó da direita é nulo.
     Se for nulo, o algoritmo deve criar um novo nó com o valor a ser inserido e colocá-lo
    como "filho" direito do nó atual. */
    if(no->valor < x){
        if(no->direita == NULL){
            no->direita = criar_no(x);
        }else{
            /*Se não for nulo, o algoritmo deve chamar recursivamente o mesmo algoritmo, 
            passando como parâmetro o valor a ser inserido e o nó da direita como o novo 
            da subárvore.*/
            inserir(no->direita, x);
        }
    }else{
        /*A ideia é a mesma, porém para valores menores devemos ir para esquerda*/
        if(no->esquerda == NULL){
            no->esquerda = criar_no(x);
        }else{
            inserir(no->esquerda, x);
        }
    }
}

int arvore_busca(Arvore* arvore, int x){
    /*Verificando se a árvore existe*/
    if(arvore == NULL)
        return 0;
    /*Se a árvore existe, vamos validar se está vazia*/
    if(arvore->raiz == NULL)
        return 0;
    
    /*Nossa busca será baseaada em nó, por este motivo foi criada uma função
    interna para fazer a busca (recursiva novamente para facilitar as coisas)*/
    return buscar_no(arvore->raiz, x);

}

/*A ideia aqui é bem parecida com a inserção, tentem entender..*/
int buscar_no(No* no, int x){
    if(no->valor == x){
        
        return 1;
    }else 
    if(no->valor < x){
        if(no->direita == NULL)
            return 0;
        else
            return buscar_no(no->direita, x);
    }else{
        if(no->esquerda == NULL)
            return 0;
        else
            return buscar_no(no->esquerda, x);
    }
}

// função para imprimir a arvore só verifica se tem arvore e raiz e chama outra função auxiliar que de fato vai manipular os nós
//igual acontece na função de busca
void arvore_imprimir(Arvore *arvore) {
    if (arvore != NULL && arvore->raiz != NULL) {
        // Chama uma função auxiliar para imprimir os nós
        imprimir_em_ordem(arvore->raiz);
    }
}

// Função auxiliar para imprimir os nós em ordem so imprime a esqueda  e volta a direita
void imprimir_em_ordem(No *no) {
    if (no != NULL) {
        imprimir_em_ordem(no->esquerda);
        printf("%d ", no->valor);
        imprimir_em_ordem(no->direita);
    }
}

// Função auxiliar para encontrar o nó mais a esquerda da arvore para usar no caso de ter valor a direita e a esquerda da  arvore
// da pra fazer o contrario e procura o no mais a direita
No *encontrar_minimo(No *raiz) {
    No *atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

void arvore_apagar(Arvore *arvore, int x) {
    if (arvore == NULL || arvore->raiz == NULL) {
        return;
    }

    No *atual = arvore->raiz;
    No *pai = NULL;
    while (atual != NULL && atual->valor != x) {
        pai = atual;
        if (x < atual->valor) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    if (atual == NULL) {
        // Valor não encontrado na árvore
        return;
    }

    if (atual->esquerda == NULL && atual->direita == NULL) {
        // Caso 1: o nó a ser removido é uma folha
        // nesse caso e so percorrer  até o nó ver se os dois ponteiros apontam pro null se for e so ele não tem nada embaixo
        // so apagar, retorna null pro ponteiro anterio e prontim
        if (pai == NULL) {
            // O nó é a raiz
            free(atual);
            arvore->raiz = NULL;
        } else if (pai->esquerda == atual) {
            pai->esquerda = NULL;
            free(atual);
        } else {
            pai->direita = NULL;
            free(atual);
        }
    } else if (atual->esquerda == NULL || atual->direita == NULL) {
        // Caso 2: o nó a ser removido tem apenas um filho
        // nesse caso o que fazemos é  percorre a raiz e verificar se um dos ponteiros aponta pro nulo que ai so vai ter um no ligado a ele
        //o que fazemos é o ponteiro do nó "pai" que é o anterio do que vamos apagar apontar pro filho 
        No *filho = (atual->esquerda != NULL) ? atual->esquerda : atual->direita;
        if (pai == NULL) {
            // O nó é a raiz
            arvore->raiz = filho;
            free(atual);
        } else if (pai->esquerda == atual) {
            pai->esquerda = filho;
            free(atual);
        } else {
            pai->direita = filho;
            free(atual);
        }
    } else {
        // Caso 3: o nó a ser removido tem dois filhos 
        //Nesse caso o que fazemos é percorre a arvore pela direita procurando o valor mais a esquerda ( o ultimo nó a esquerda ) 
        // e trocamos o valor pra posição do no que seria removido desse jeito a organização da arvore se mantém
        // poderia ter sido feito o contrario também percorrer pela esquerda e pegar o valor mais a direita
        No *sucessor = encontrar_minimo(atual->direita);
        int temp = sucessor->valor;
        arvore_apagar(arvore, temp); // Remove o sucessor recursivamente
        atual->valor = temp;
    }
} 