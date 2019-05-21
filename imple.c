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
    printf("---+------------------------------+--------------------+--------------------+-----------+--------------------------+----------\n");


    for(i = 0; i < 6; i++){
        //ID
        //Printa o número de espaços analisando o número de digitos de id
        if(inv[i].id < 10){
            printf("%i  |", inv[i].id);
        } else {
            printf("%i |", inv[i].id);  
        }

        //Autor
        int j;
        //Cria uma int leng que recebe o tamanho do título do livro
        int leng = strlen(inv[i].titulo);
        //Printa o nome do livro
        printf("%s", inv[i].titulo);
        //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (30 - leng)
        for(j = 0; j < (30 - leng) ; j++){
            printf(" ");
        }
        //Printa a barra separadora de colunas
        printf("|");

        //Autor
        //Cria uma int leng que recebe o tamanho do nome do autor
        leng = strlen(inv[i].autor); 
        //Printa o nome do autor
        printf("%s", inv[i].autor);
        //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (20 - leng)
        for(j = 0; j < (20 - leng) ; j++){
            printf(" ");
        }
        //Printa a barra separadora de colunas
        printf("|");

        //Gênero 
        //Cria uma int leng que recebe o tamanho do gênero
        leng = strlen(inv[i].genero); 
        //Printa o gênero
        printf("%s", inv[i].genero);
        //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (20 - leng)
        for(j = 0; j < (20 - leng) ; j++){
            printf(" ");
        }
        //Printa a barra separadora de colunas
        printf("|");

        //Ano de publicação
        //Printa o ano de publicação
        printf("%i", inv[i].publicacao);
        //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso 7        
        for(j = 0; j < 7 ; j++){
            printf(" ");
        }
        //Printa a barra separadora de colunas
        printf("|");

        //Editora
        //Cria uma int leng que recebe o tamanho da editora
        leng = strlen(inv[i].editora); 
        //Printa a editora
        printf("%s", inv[i].editora);
        //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (26 - leng)
        for(j = 0; j < (26-leng) ; j++){
            printf(" ");
        }
        //Printa a barra separadora de colunas
        printf("|");

        //Nº de exemplares
        //Printa o número de exemplares
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




}

