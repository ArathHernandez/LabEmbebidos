#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  FILE *f = fopen("file.txt", "w");
  
  if(f == NULL){
    fprintf(sdterr, "Error opening file!\n");
      exit(1);
  }
  
  for(int i = 0; i <atoi(argv[2]); i++){
    char Nombre[100], ID[30];
    printf("Enter Name:\n");
    scanf("%s", Nombre);
    printf("Enter ID:\n");
    scanf("%s", ID);
    printf("Do you wish to add more [y/n]:\n");
    char rsp;
    scanf(" %c", &rsp);
    
    fprintf(f, "%s, \t%s\n, Nombre, ID);
    if(rsp == 'n'){
      break;
    }
   
            
  printf("Students information stored in Datalog.txt\n");
  //const char *text = "Write this to the file";
  //fprintf(f, "Some text: %s", text);
  fclose(f);
}
