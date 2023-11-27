#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 2024
long int FILE_SIZE = 2024;

struct Dados {
    char *contrato;
    char *doacao;
    char *CPF;
};

void writeSortedDataToFile(const char* filename, struct Dados *p, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro: Falha ao abrir o arquivo para escrita\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s;%s;%s", p[i].contrato, p[i].doacao, p[i].CPF);
    }

    fclose(file);
}

char* allocateAndCopyString(const char* source) {
    if (source == NULL) {
        return NULL;
    }
    char* dest = malloc(strlen(source) + 1);
    if (dest) {
        strcpy(dest, source);
    }
    return dest;
}
void ord(struct Dados *p) {
  int n = 0;
  char linha[MAX_LINE];
  FILE *arq = fopen("data.csv", "r");
  if (arq == NULL) {
      printf("Erro ao abrir o arquivo\n");
  }
  
  while (fgets(linha, MAX_LINE, arq) != NULL && n < FILE_SIZE) {
      p[n].contrato = allocateAndCopyString(strtok(linha, ";"));
      p[n].doacao = allocateAndCopyString(strtok(NULL, ";"));
      p[n].CPF = allocateAndCopyString(strtok(NULL, ";"));
     n++;
  }
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(p[i].contrato, p[j].contrato) > 0) {
                struct Dados atual = p[i];
                p[i] = p[j];
                p[j] = atual;
            }
        }
    }
  writeSortedDataToFile("data.csv", p, n);

  for (int j = 0; j < n; j++) {
        free(p[j].contrato);
        free(p[j].doacao);
        free(p[j].CPF);
    }
    free(p);
}




 int add(){
     FILE *arq = fopen("data.csv", "a+");

      char *contrato = malloc(50 * sizeof(char));
      if (contrato == NULL) {
        printf("Falha na alocação de memória\n");
      }
      char *doacao = malloc(50 * sizeof(char));
      if (doacao == NULL) {
        printf("Falha na alocação de memória\n");
      }
      char *CPF = malloc(50 * sizeof(char));
      if (CPF == NULL) {
        printf("Falha na alocação de memória\n");
      }

    if (!arq) {
        printf("Erro ao abrir arquivo\n");
    }

    printf("\nDe entrada no numero de contrato\n");
    scanf("%s", contrato);
    printf("\nEntre valor de doacao\n");
    scanf("%s", doacao);
    printf("\nDe entrada no CPF\n");
    scanf("%s", CPF);


    if(strcmp(CPF,"0")==0){
        fprintf(arq, "00000%s; 000000000%s; 0000000000000000%s\n", contrato,
            doacao, CPF);
    }
    else{
        fprintf(arq, "00000%s; 000000000%s; 020000%s\n", contrato,
            doacao, CPF);
    }

    printf("\nNova pessoa esta adicionada na planilha\n");
    free(contrato);
    free(doacao);
    free(CPF);
    fclose(arq);

    return 0;
 }


 int buscar(const char *valorBusca) {
    FILE *arq = fopen("data.csv", "r");


    if (arq == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char *linha = malloc(MAX_LINE * sizeof(char));
    char *token;

    int colunaIndex = 0;  // Índice da coluna onde a busca será realizada

    // Realiza a busca na coluna especificada
    int cont =0;
    while (fgets(linha, MAX_LINE, arq) != NULL) {
        token = strtok(linha, ";");
        cont++;
        for (int i = 0; i <= colunaIndex; i++) {
            if (i == colunaIndex && strcmp(token, valorBusca) == 0) {
                printf("Numero de contrato %s encontrada na linha : %d\n", linha,cont-1);

                fclose(arq);
                 return cont;
            }
            token = strtok(NULL, ";");
        }
    }

    printf("Informacao nao encontrada.\n");
    free(linha);
    fclose(arq);
    return -1;
}

int remover(const char *valorBusca){
   FILE *arq ,*temp;

    char temp_filename[FILE_SIZE];
    char buffer[MAX_LINE];
    
   int i=buscar(valorBusca);
   if(i!=-1){
      int delete_line=i;
   
    strcpy(temp_filename,"temp____");
    strcat(temp_filename,"data.csv");


    arq = fopen("data.csv","r");
    temp =fopen(temp_filename,"w");

     if( arq == NULL || temp == NULL){
        printf("Erro em abrir arquivo(s)");
        return 1;
     }

     bool keep_reading = true;
     int current_line=1;

     do{
        fgets(buffer,MAX_LINE,arq);
         if(feof(arq)) keep_reading = false;

         else if(current_line != delete_line ){
            fputs(buffer,temp);  
         }
         current_line++;
         

     }while( keep_reading);

    fclose(arq);
    fclose(temp);

    remove("data.csv");
    rename(temp_filename,"data.csv");
    printf("Numero de contrato selecionado foi deletado\n");
   }
}

int main(){

    struct Dados *dados = malloc(FILE_SIZE * sizeof(struct Dados));
    if (dados == NULL) {
        printf("Falha na alocação de memória\n");
        return 1;
    }

    int n=0;
    int choice;
    while(n==0){
          printf("\n1. Adicionar pessoa\n");
          printf("2. Buscar Pessoa\n");
          printf("3. Remover Pessoa\n");
          printf("4. Sair\n");
          printf("Escolha uma opcao: ");
          scanf("%d", &choice);

      if(choice==1){
        add();
        ord(dados);
        }
      if(choice==2){
        char valor[50];
        char valorBusca[50]="00000";

        printf("Digite numero de contrato que voce deseja buscar:\n");
        scanf("%s",valor);

        strcat(valorBusca,valor);

         if (buscar(valorBusca) != -1) {

            printf("Busca bem-sucedida!\n");
        }   
        else {

            printf("Erro na busca.\n");
        }
      }
      if(choice==3){
      
        char valor[50];
        char valorBusca[50]="00000";
        printf("Digite numero de contrato que voce deseja deletar:\n");
        scanf("%s",valor);

        
        strcat(valorBusca,valor);

        remover(valorBusca);
      }
    
      if(choice==4){
        n++;
        }
    }


    return 0;
}
