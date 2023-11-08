#include <conio.h>
#include <stdio.h>
#include <string.h>
 
// Driver Code
int main()
{
    // Substitute the file_path string
    // with full path of CSV file
    FILE* fp = fopen("C:\\Users\\anabi\\OneDrive\\Documentos\\data.csv", "a+");
 
    
    int contrato,doacao;
    double CPF;
 
    if (!fp) {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
    }
 
    // Asking user input for the
    // new record to be added
    printf("\nEnter Account Holder Name\n");
    scanf("%d", &contrato);
    printf("\nEnter Account Number\n");
    scanf("%d", &doacao);
    printf("\nEnter Available Amount\n");
    scanf("%lf", &CPF);
 
    // Saving data in file
    fprintf(fp, "%d; %d; %1.lf\n", contrato,
            doacao, CPF);
 
    printf("\nNew Account added to record");
 
    fclose(fp);
    return 0;
}
