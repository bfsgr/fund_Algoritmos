#include <stdio.h>
#include <string.h>

struct livros{
    int id, publicacao, exemplares;
    char titulo[100];
    char autor[50];
    char genero[30];
    char editora[50];
};

//função que substitui o uso de fflush(stdin), que pode não funcionar dependendo do compilador
void clean_stdin(void){
  int c;
  do {
      c = getchar();
  } while (c != '\n' && c != EOF);

}

int contar(struct livros inv[]){
  int cont = -1;
  int i = 0;
  while(inv[i].autor[0] != '\0'){
    cont++;
    i++;
  }
  return cont;
}

void cabecalho(int aux){
  if(aux == 1){
    printf("ID |Título                        |Autor               |Gênero              |Publicação |Editora                   |Exemplares\n");
    printf("---+------------------------------+--------------------+--------------------+-----------+--------------------------+----------\n");
  }
}
//função interna que remove o '\n' de uma string. 
void clear(char str[]){
  char *p;
  p = strchr(str, '\n');
  *p = '\0';
};


void printar(struct livros inv[30], int pos){

  if(inv[pos].id < 10){
        printf("%i  |", inv[pos].id);
    } else {
        printf("%i |", inv[pos].id);
    }

    //Autor
    int j;
    //Cria uma int leng que recebe o tamanho do título do livro
    int leng = strlen(inv[pos].titulo);
    //Printa o nome do livro
    printf("%s", inv[pos].titulo);
    //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (30 - leng)
    for(j = 0; j < (30 - leng) ; j++){
        printf(" ");
    }
    //Printa a barra separadora de colunas
    printf("|");

    //Autor
    //Cria uma int leng que recebe o tamanho do nome do autor
    leng = strlen(inv[pos].autor);
    //Printa o nome do autor
    printf("%s", inv[pos].autor);
    //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (20 - leng)
    for(j = 0; j < (20 - leng) ; j++){
        printf(" ");
    }
    //Printa a barra separadora de colunas
    printf("|");

    //Gênero
    //Cria uma int leng que recebe o tamanho do gênero
    leng = strlen(inv[pos].genero);
    //Printa o gênero
    printf("%s", inv[pos].genero);
    //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (20 - leng)
    for(j = 0; j < (20 - leng) ; j++){
        printf(" ");
    }
    //Printa a barra separadora de colunas
    printf("|");

    //Ano de publicação
    //Printa o ano de publicação
    printf("%i", inv[pos].publicacao);
    //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso 7
    for(j = 0; j < 7 ; j++){
        printf(" ");
    }
    //Printa a barra separadora de colunas
    printf("|");

    //Editora
    //Cria uma int leng que recebe o tamanho da editora
    leng = strlen(inv[pos].editora);
    //Printa a editora
    printf("%s", inv[pos].editora);
    //Usa-se um for para printar o número de espaços até o fim da coluna, neste caso (26 - leng)
    for(j = 0; j < (26-leng) ; j++){
        printf(" ");
    }
    //Printa a barra separadora de colunas
    printf("|");

    //Nº de exemplares
    //Printa o número de exemplares
    printf("%i\n", inv[pos].exemplares);
}

void listar(struct livros inv[30]){
  int i;
  int tamanho = contar(inv)+1;
  if(tamanho != 0){
    cabecalho(1);
  } else {
    printf("::::.Sem registros.::::\n");
  }
  for(i = 0; i < tamanho; i++){
    printar(inv, i);
  }
}
int remover(struct livros *inv, int id){
  //Cria uma variavel que receve o tamanho do array
  int tamanho = contar(inv)+1;
  int i, j, ret = 1;
  //itera sobre os elementos do array
  for(i = 0; i < tamanho; i++){
    //se encontrar o elemento que o usuário digitou:
    if(id == inv[i].id){
      ret = 0;
      //começa a iterar a partir do elemento do usuário até o fim do array
      for(j = i; j < tamanho; j++){
        //copia o elemento seguinte para a posição do elemento a ser apagado e assim por diante
        inv[j].id = inv[j+1].id;
        inv[j].publicacao = inv[j+1].publicacao;
        inv[j].exemplares = inv[j+1].exemplares;
        strcpy(inv[j].autor, inv[j+1].autor);
        strcpy(inv[j].titulo, inv[j+1].titulo);
        strcpy(inv[j].editora, inv[j+1].editora);
        strcpy(inv[j].genero, inv[j+1].genero);
      }
      //retorna 0 depois de apagar o registro
      return ret;
    }
  }


}

void inserir(struct livros *inv, int *cont){

  int valida(char str[]){
    int size = strlen(str), i, cont = 0;
    for(i = 0; i < size; i++){
      if(str[i] == ' '){
        cont++;
      }
    }
    if(cont == size){
      printf("Entrada não pode ser vazia\n");
      return 1;
    } else {
      return 0;
    }

  };
  //recebe o tamanho do array
  int tamanho = contar(inv)+1, ano;
  //string auxiliar 
  char aux[100];
  //o novo id será o contador +1
  inv[tamanho].id = *cont;
  //limpa o stdin para remover bugs entre scanf e fgets
  clean_stdin();

  //Le o titulo
  do{
    printf("Título: ");
    fgets(aux, 100, stdin);
    clear(aux);
  } while(valida(aux) == 1);
  strcpy(inv[tamanho].titulo, aux);

  //Le o autor
  do{
    printf("Autor: ");
    fgets(aux, 100, stdin);
    clear(aux);
  }while(valida(aux) == 1);
  strcpy(inv[tamanho].autor, aux);
  
  //le a editora
  do{
    printf("Editora: ");
    fgets(aux, 100, stdin);
    clear(aux);
  }while(valida(aux) == 1);
  strcpy(inv[tamanho].editora, aux);

  //le o genero
  do{
    printf("Gênero: ");
    fgets(aux, 100, stdin);
    clear(aux);
  }while(valida(aux) == 1);
  strcpy(inv[tamanho].genero, aux);
  
  //le o ano de publicação
  printf("Ano de Publicação: ");
  scanf("%i", &inv[tamanho].publicacao);
  
  //le o número de exemplares
  printf("Nº Exemplares: ");
  scanf("%i", &inv[tamanho].exemplares);
  *cont = *cont + 1;
}

int consulta(struct livros *inv, int id){
  int i, tamanho = contar(inv)+1, ret = 1;

  for (i = 0; i < tamanho; i++){
    if(inv[i].id == id){
      ret = 0;
      printf("-----------------------\n");
      printf("ID: %i\n", inv[i].id);
      printf("Título: %s\n", inv[i].titulo);
      printf("Autor: %s\n", inv[i].autor);
      printf("Gênero: %s\n", inv[i].genero);
      printf("Editora: %s\n", inv[i].editora);
      printf("Publicação: %i\n", inv[i].publicacao);
      printf("Exemplares: %i\n", inv[i].exemplares);
      return ret;
    }
  }
  return ret;
  

}
int buscaAutor(struct livros *inv, char *chave){

  int i, tamanho = contar(inv)+1, aux = 0;

  for(i = 0; i < tamanho; i++){
    if( (strcmp(inv[i].autor, chave) ) == 0){
      aux++;
      cabecalho(aux);
      printar(inv, i);
    }
  }
  return aux;
}

int mudaEx(struct livros *inv, int chave){
  int i, tamanho = contar(inv)+1, ret = 1;

  for(i = 0; i < tamanho; i++){
    if(inv[i].id == chave){
      ret = 0;
      printf("Insira a quantidade de exemplares atualizadas de \"%s\": ", inv[i].titulo);
      scanf("%i", &inv[i].exemplares);
    }
  }
  return ret;
}


int main(){
  int i, ops = -1, aux, retorno, cont = 0;
  char autor[100];

  struct livros inv[30] = {};


  while(ops != 0){
    printf("------------------------\n0: Sair\n1: Listar\n2: Inserir\n3: Remover\n4: Consulta\n5: Buscar por Autor\n6: Mudar Nº de exemplares\n\n:::Escolha uma opção: ");
    scanf("%i", &ops);
    
    switch (ops){
      case 0:{
        break;
      }
      case 1:{
        listar(inv);
        break;
      }
      case 2:{
        inserir(inv, &cont);
        break;
      }
      case 3:{
        printf("Insira o ID que deseja remover: ");
        scanf("%i", &aux );
        
        retorno = remover(inv, aux);
        
        if(retorno == 0){
          printf(":::::.Registro removido com sucesso.:::::\n");
        } else{
          printf(":::::.Registro não encontrado.:::::\n");
        }

        break;
      }
      case 4:{
        printf("Insira um ID: ");
        scanf("%i", &aux);

        retorno = consulta(inv, aux);
        if(retorno == 1){
          printf(":::::.Registro não encontrado.:::::\n");
        }
        break;
      }
      case 5:{
        printf("Insira um autor: ");

        clean_stdin();
        fgets(autor, 100, stdin);
        clear(autor);

        retorno = buscaAutor(inv, autor);
        if(retorno == 0){
          printf(":::::.Registro não encontrado.:::::\n");
        }
        break;
      }
      case 6:{
        printf("Digite o ID que deseja modificar: ");
        scanf("%i", &aux);
        retorno = mudaEx(inv, aux);
        if(retorno == 0){
          printf(":::::.Registro alterado com sucesso.:::::\n");
        } else{
          printf(":::::.Registro não encontrado.:::::\n");
        }
        break;
      }
      
      default:{
        printf("Opção não listada\n");
        break;
      }
    }
  }
}
