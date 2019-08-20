#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//função que substitui o uso de fflush(stdin), que pode não funcionar dependendo do compilador
void clean_stdin(void){
  int c;
  do {
      c = getchar();
  } while (c != '\n' && c != EOF);

}
//abre o arquivo
FILE* open(int a){
  //cria um ponteiro de arquivo
  FILE *fp;
  if(a == 1){
    //se o parametro a for 1 > abre o arquivo com append (se o arquivo existir abre com o stream no final dele, caso contrário cria o arquivo).
    fp = fopen("db.txt","a+");
  } else {
    //caso parametro a seja não-zero abre o arquivo com w+ (se o arquivo existir limpa ele, caso contrário cria um novo)
    fp = fopen("db.txt","w+");
  }
  //checagem se o ponteiro é válido
  if(fp == NULL){
    printf("Não foi possível abrir a base de dados.\n");
  } else {
    //se válido retorna o valor do ponteiro
    return fp;
  }
}

//escreve os dados do struct para o arquivo
void write(struct livros *inv, FILE *fp){
  //conta o numero de elementos no struct do heap (memória virtual) e define o i
  int contagem = contar(inv)+1, i;
  //itera sobre os elementos do struct gravando cada entrada em uma linha e cada propriedade separada por um pipe (|)
  for(i = 0; i < contagem; i++){
    fprintf(fp, "%i|", inv[i].id);
    fprintf(fp, "%s|", inv[i].titulo);
    fprintf(fp, "%s|", inv[i].autor);
    fprintf(fp, "%s|", inv[i].genero);
    fprintf(fp, "%i|", inv[i].publicacao);
    fprintf(fp, "%s|", inv[i].editora);
    fprintf(fp, "%i\n", inv[i].exemplares);
  }
}

//salva o numero do contador em um arquivo em separado
void saveCount(int *cont){
  FILE *fp;
  fp = fopen("contador.txt","w+");
  fprintf(fp,"%i", *cont);
  fclose(fp);
}

//quebra uma linha do arquivo pelo |
void tokenize(char* entry, char response[7][80]){
    int i = 0;
    char *token;
    //função strtok le todos o caracteres até o pipe
    token = strtok(entry, "|");
    //le as outras propriedades entre os pipes até o retorno ser nulo
    while(token != NULL ) {
      //copia a propriedade lida para o array response
      strcpy(response[i], token);
      //quando a strtok é chamada com NULL ela continua a ler do stream de sua ultima chamada, asism lendo todas as propriedades entre os pipes
      token = strtok(NULL, "|");
      //aumenta o iterador
      i++;
    }
}

//loga os dados do arquivo para o struct
void load(struct livros *inv, FILE *fp, int *cont){
  //iteradores
  int i = -1, j;
  //array de strings auxiliares
  char a[30][200];
  //volta ao inicio do arquivo
  rewind(fp);

  //se o final do arquivo NÃO foi atingido
  while(feof(fp) == 0){
    //usa o fscanf para ler do arquivo, com a diletiva %[^\n] ele para a leitura quando achar um \n
    fscanf(fp,"%[^\n]", a[i]);
    //checa novamente se é o fim do arquivo. Isso é feito pois se o stream estiver no final do arquivo, move-lo para frente ira voltar ao inicio do arquivo
    if(feof(fp) == 0){
      //move o stream 2 bytes da posição atual. (2 bytes é o tamanho de um char único)
      fseek( fp, 2, SEEK_CUR);
    }
    //iterador
    i++;
  }

  //itera sobre a contagem de linhas/entradas do arquivo
  for(j = 0; j < i; j++){
    //array de strings auxiliar
    char response[7][80];
    //chama a função tokenize para cada uma das linhas, que irá retornar as propriedades individuais da entrada
    tokenize(a[j], response);
    //conversões de char para int usando a função strtol(string, ponteiro, base). 
    //pos é o id da entrada
    int pos = strtol(response[0], NULL, 10);
    //pub é o ano de publicação da entrada
    int pub = strtol(response[4], NULL, 10);
    //exp é o numero de exemplares da entrada
    int exp = strtol(response[6], NULL, 10);

    // escreve o id, ano de publicação e número de exemplares da entrada no struct
    inv[j].id = pos;
    inv[j].publicacao = pub;
    inv[j].exemplares = exp;

    //copia titulo, autor, editora e genero para o heap
    strcpy(inv[j].titulo, response[1]);
    strcpy(inv[j].autor, response[2]);
    strcpy(inv[j].genero, response[3]);
    strcpy(inv[j].editora, response[5]);
  }


  //===== essa parte do código garante que os ID's sejam únicos =======
  //abre o arquivo do contador para leitura
  FILE *ident;
  ident = fopen("contador.txt", "r");
  //se ele não existir:
  if(ident == NULL){
    //o contador retornado será o numero de entradas do struct +1
    *cont = inv[contar(inv)].id+1;
  } else {
    //caso contrário:
    //cria string auxiliar num
    char num[2];
    //le até o fim da linha
    fscanf(ident,"%[^\n]", num);
    //converte a string lida para int
    int leitura = strtol(num, NULL, 10);
    //o valor do contador agora será o valor lido do arquivo.
    *cont = leitura;
    //fecha o arquivo
    fclose(ident);
  }

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
  saveCount(cont);
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

  FILE *file;
  file = open(1);

  load(inv,file, &cont);
  fclose(file);


  while(ops != 0){
    printf("------------------------\n0: Sair\n1: Listar\n2: Inserir\n3: Remover\n4: Consulta\n5: Buscar por Autor\n6: Mudar Nº de exemplares\n7: Limpar base de dados\n\n:::Escolha uma opção: ");
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
        FILE *file;
        file = open(0);
        write(inv, file);
        fclose(file);
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
        FILE *file;
        file = open(0);
        write(inv, file);
        fclose(file);
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
          write(inv,file);
        } else{
          printf(":::::.Registro não encontrado.:::::\n");
        }
        FILE *file;
        file = open(0);
        write(inv, file);
        fclose(file);
        break;
      }
      case 7: {
        FILE *fp;
        fp = fopen("db.txt","w+");
        fclose(fp);
        fp = fopen("contador.txt","w+");
        fclose(fp);
        memset(inv, 0, sizeof inv);
        cont = 0;
        break;
      }
      
      default:{
        printf("Opção não listada\n");
        break;
      }
    }
  }
}
