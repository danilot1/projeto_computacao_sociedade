#include <conio.h>
#include <stdio.h>
#include <string.h>
 
// Driver Code
int main()
{
    // Substitute the file_path string
    // with full path of CSV file
    FILE* fp = fopen("C:\\Users\\anabi\\OneDrive\\Documentos\\data.csv", "a+");
 
    
     char contrato[50],doacao[50],CPF[50];

 
    if (!fp) {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
    }
 
    // Asking user input for the
    // new record to be added
    printf("\nDe entrada no numero de contrato\n");
    scanf("%s", contrato);
    printf("\nEntre valor de doacao\n");
    scanf("%s", doacao);
    printf("\nDe entrada no CPF\n");
    scanf("%s", CPF);
 
    // Saving data in file

    if(CPF==NULL){
        //erro nao identificado
        fprintf(fp, "000000%s; 000000000%s; 00000000000000000\n", contrato,
            doacao, CPF);
    }
    else{
        fprintf(fp, "00000%s; 000000000%s; 020000%s\n", contrato,
            doacao, CPF);
    }
 
    printf("\nNew Account added to record");
 
    fclose(fp);
    return 0;
}
