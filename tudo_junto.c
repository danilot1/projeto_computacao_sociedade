#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 2024
#define FILE_SIZE 1024

 int add(){
     FILE *arq = fopen("data.csv", "a+");
 
     char contrato[50],doacao[50],CPF[50];
 
    if (!arq) {
        printf("Erro ao abrir arquivo\n");
    }
 
    printf("\nDe entrada no numero de contrato\n");
    scanf("%s", contrato);
    printf("\nEntre valor de doacao\n");
    scanf("%s", doacao);
    printf("\nDe entrada no CPF\n");
    scanf("%s", CPF);
 
    // Saving data in file

    if(strcmp(CPF,"0")==0){
        fprintf(arq, "00000%s; 000000000%s; 0000000000000000%s\n", contrato,
            doacao, CPF);
    }
    else{
        fprintf(arq, "00000%s; 000000000%s; 020000%s\n", contrato,
            doacao, CPF);
    }
 
    printf("\nNova pessoa esta adicionada na planilha\n");
 
    fclose(arq);

    return 0;
 }

 int buscar(const char *valorBusca) {
    FILE *arq = fopen("data.csv", "r");


    if (arq == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char linha[MAX_LINE];
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
                //return 0;
            }
            token = strtok(NULL, ";");
        }
    }

    printf("Informacao nao encontrada.\n");
    fclose(arq);
    return -1;
}

int remover(const char *valorBusca){
   FILE *arq ,*temp;

    char filename[FILE_SIZE]="data.csv";
    char temp_filename[FILE_SIZE];
    char buffer[MAX_LINE];
    
   int i=buscar(valorBusca);
   if(i!=-1){
      int delete_line=i;
   
    strcpy(temp_filename,"temp____");
    strcat(temp_filename,filename);


    arq = fopen(filename,"r");
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

    remove(filename);
    rename(temp_filename,filename);
    printf("Numero de contrato selecionado foi deletado\n");
   }
}

int main(){
        
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
        }
      if(choice==2){
        char valor[50];
        char valorBusca[50];

        printf("Digite numero de contrato que voce deseja buscar:\n");
        scanf("%s",valor);

        strcpy(valorBusca,"00000");
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
