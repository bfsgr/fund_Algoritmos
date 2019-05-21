#include <stdio.h>
#include <string.h>

struct livros{
    int id, publicacao, exemplares;
    char titulo[100];
    char autor[50];
    char genero[30];
    char editora[50];
};

void listar(struct livros inv[30]){
    int i;
    printf("ID |Título                        |Autor               |Gênero              |Publicação |Editora                   |Exemplares\n");
    printf("---|------------------------------|--------------------|--------------------|-----------|--------------------------|----------\n");
    for(i = 0; i < 6; i++){
        //ID
        printf("%i  |", inv[i].id);
        
        //Nome
        int j;
        int leng = strlen(inv[i].titulo); 
        printf("%s", inv[i].titulo);
        for(j = 0; j < (30 - leng) ; j++){
            printf(" ");
        }
        printf("|");

        //autor
        leng = strlen(inv[i].autor); 
        printf("%s", inv[i].autor);
        for(j = 0; j < (20 - leng) ; j++){
            printf(" ");
        }
        printf("|");

        //genero 
        leng = strlen(inv[i].genero); 
        printf("%s", inv[i].genero);
        for(j = 0; j < (20 - leng) ; j++){
            printf(" ");
        }
        printf("|");


        printf("%i", inv[i].publicacao);
        for(j = 0; j < 7 ; j++){
            printf(" ");
        }
        printf("|");

        leng = strlen(inv[i].editora); 
        printf("%s", inv[i].editora);
        for(j = 0; j < (26-leng) ; j++){
            printf(" ");
        }
        printf("|");

        //até
        printf("%i\n", inv[i].exemplares);





    }
}
void remover(){

}
void inserir(){

}
void buscar(){

}
void buscaautor(){

}
void buscagenero(){

}


int main(){
    int i;

    struct livros inv[30] = {
        {.id = 0, .titulo = "1984", .autor = "George Orwell", .publicacao = 1949, .genero = "Distopia", .editora = "Companhia Das Letras", .exemplares = 10},
        {.id = 1, .titulo = "Com amor, Simon", .autor = "Becky Albertalli", .publicacao = 2015, .genero = "LGBT", .editora = "Intrinseca", .exemplares = 10},
        {.id = 2, .titulo = "Admiravel novo mundo", .autor = "Aldous Huxley", .publicacao = 1941, .genero = "Distopia", .editora = "Biblioteca Azul", .exemplares = 10},
        {.id = 3, .titulo = "A hora da estrela", .autor = "Clarice Lispector", .publicacao = 1977, .genero = "Romance", .editora = "Rocco", .exemplares = 10},
        {.id = 4, .titulo = "Divergente", .autor = "Veronica Roth", .publicacao = 2011, .genero = "Aventura", .editora = "Rocco", .exemplares = 10},
        {.id = 5, .titulo = "Codigo da vinci", .autor = "Dan Brown", .publicacao = 2003, .genero = "Romance", .editora = "Arqueiro", .exemplares = 10},

        
        
    };
    listar(inv);

    // // inv[4].titulo;



}

