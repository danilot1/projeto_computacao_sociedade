#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 2024
#define FILE_SIZE 1024

int main(){
    FILE *file ,*temp;
    char filename[FILE_SIZE]="data.csv";
    char temp_filename[FILE_SIZE];
    char buffer[MAX_LINE];

    int delete_line=0;

    

    strcpy(temp_filename,"temp____");
    strcat(temp_filename,filename);

    printf("Delete Line: ");
    scanf("%d",&delete_line);

    file = fopen(filename,"r");
    temp =fopen(temp_filename,"w");

     if( file == NULL || temp == NULL){
        printf("Error opening file(s)");
        return 1;
     }

     bool keep_reading = true;
     int current_line=1;

     do{
        fgets(buffer,MAX_LINE,file);
         if(feof(file)) keep_reading = false;

         else if(current_line != delete_line ){
            fputs(buffer,temp);  
         }
         current_line++;
         

     }while( keep_reading);

    fclose(file);
    fclose(temp);

    remove(filename);
    rename(temp_filename,filename);


    return 0;
}
