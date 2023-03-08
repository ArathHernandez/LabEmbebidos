#include<stdio.h>
int main(int argc, char *argv[]) {
  int i = 0;
  for (i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  
  if(strcmp(argv[1], "-a") == 0){
    int area = atoi(argv[3])*atoi(argv[5]);
    printf("area = %d units", area);
  }
  if(strcmp(argv[1], "-p") == 0){
    int prmtr = 2*(atoi(argv[3])*atoi(argv[5]));
    printf("perimeter = %d units", prmtr);
  }
  return 0;
}
