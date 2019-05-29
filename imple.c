#include <stdio.h>
#include <string.h>

struct livros{
    int id, publicacao, exemplares;
    char titulo[100];
    char autor[50];
    char genero[30];
    char editora[50];
};

int contar(struct livros inv[]){
  int cont = -1;
  int i = 0;
  while(inv[i].autor[0] != '\0'){
    cont++;
    i++;
  }
  return cont;
}

void listar(struct livros inv[30]){
    int i;
    printf("ID |Título                        |Autor               |Gênero              |Publicação |Editora                   |Exemplares\n");
    printf("---+------------------------------+--------------------+--------------------+-----------+--------------------------+----------\n");

    int tamanho = contar(inv)+1;
    for(i = 0; i < tamanho; i++){
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
void remover(struct livros *inv, int id){
  int tamanho = contar(inv)+1;
  int i,j;
  for(i = 0; i < tamanho; i++){
    if(id == inv[i].id){
      for(j = i; j < tamanho; j++){
        inv[j].id = inv[j+1].id;
        inv[j].publicacao = inv[j+1].publicacao;
        inv[j].exemplares = inv[j+1].exemplares;

        strcpy(inv[j].autor, inv[j+1].autor);
        strcpy(inv[j].titulo, inv[j+1].titulo);
        strcpy(inv[j].editora, inv[j+1].editora);
        strcpy(inv[j].genero, inv[j+1].genero);

      }
    }
  }


}


void inserir(struct livros *inv){

  int tamanho = contar(inv)+1;
  char aux[100];
  int a;
  inv[tamanho].id = inv[tamanho-1].id+1;

  printf("Título:");
  scanf("%s", aux);
  strcpy(inv[tamanho].titulo, aux);

  printf("Autor:");
  scanf("%s", aux);
  strcpy(inv[tamanho].autor, aux);

  printf("Editora: ");
  scanf("%s", aux);
  strcpy(inv[tamanho].editora, aux);

  printf("Gênero: ");
  scanf("%s", aux);
  strcpy(inv[tamanho].genero, aux);

  printf("Publicação: ");
  scanf("%i", &inv[tamanho].publicacao);

  printf("Exemplares: ");
  scanf("%i", &inv[tamanho].exemplares);
}

void consulta(struct livros *inv, int id){
  int i, tamanho = contar(inv)+1;

  for (i = 0; i < tamanho; i++){
    if(inv[i].id == id){
      printf("-----------------------\n");
      printf("ID: %i\n", inv[i].id);
      printf("Título: %s\n", inv[i].titulo);
      printf("Autor: %s\n", inv[i].autor);
      printf("Gênero: %s\n", inv[i].genero);
      printf("Editora: %s\n", inv[i].editora);
      printf("Publicação: %i\n", inv[i].publicacao);
      printf("Exemplares: %i\n", inv[i].exemplares);
    }
  }

}
void buscaAutor(struct livros *inv, char chave){
  int i, tamanho = contar(inv)+1;

  for(i = 0, i < tamanho, i++){
    if((strcmp(inv[i].autor, chave)) == 0){
      
    }
  }


}
void mudaEx(){

}


int main(){
    int i, ops = -1, aux;
    char a[100];

    struct livros inv[30] = {
        {.id = 0, .titulo = "1984", .autor = "George Orwell", .publicacao = 1949, .genero = "Distopia", .editora = "Companhia Das Letras", .exemplares = 10},
        {.id = 1, .titulo = "Com amor, Simon", .autor = "Becky Albertalli", .publicacao = 2015, .genero = "LGBT", .editora = "Intrinseca", .exemplares = 10},
        {.id = 2, .titulo = "Admiravel novo mundo", .autor = "Aldous Huxley", .publicacao = 1941, .genero = "Distopia", .editora = "Biblioteca Azul", .exemplares = 10},
        {.id = 3, .titulo = "A hora da estrela", .autor = "Clarice Lispector", .publicacao = 1977, .genero = "Romance", .editora = "Rocco", .exemplares = 10},
        {.id = 4, .titulo = "Divergente", .autor = "Veronica Roth", .publicacao = 2011, .genero = "Aventura", .editora = "Rocco", .exemplares = 10},
        {.id = 5, .titulo = "Codigo da vinci", .autor = "Dan Brown", .publicacao = 2003, .genero = "Romance", .editora = "Arqueiro", .exemplares = 10},

    };

    while(ops != 0){
      printf("------------------------\n0: Sair\n1: Listar\n2: Inserir\n3: Contar\n4: Remover\n5: Consulta\n6: Buscar por Autor\n\n:::Escolha uma opção: ");
      scanf("%i", &ops);

      if(ops != 0){
        if(ops == 1){
          listar(inv);
        } else if(ops == 2){
          inserir(inv);
        } else if(ops == 3){
          printf("%i",contar(inv));
        } else if(ops == 4){
          printf("Insira o ID que deseja remover: ");
          scanf("%i", &aux );
          remover(inv, aux);
        } else if(ops == 5){
          printf("Insira um ID: ");
          scanf("%i", &aux);
          consulta(inv, aux);
        } else if(ops == 6){
          printf("Insira um autor: ");
          scanf("%s", a);
          buscaAutor(inv, a);

        }
      }

    }




}
