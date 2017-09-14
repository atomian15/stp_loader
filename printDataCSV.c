#include<stdio.h>
#include<stdlib.h>
#include"structs.h"

extern void printCSVZX(stp_t *test)
{
  int i,j;

  FILE *fp;
  if((fp = fopen(test->csvname,"w")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  for(i=0;i<test->X_point;i++){
    for(j=0;j<test->Z_point;j++){
      fprintf(fp, "%e, ", *(test->data + test->Z_point * test->X_point - 1 - i*test->Z_point - j) );
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

extern void printCSVTopo(stp_t *test)
{
  int i,j;

  FILE *fp;
  if((fp = fopen(test->csvname,"w")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  for(i=0;i<test->Y_point;i++){
    for(j=0;j<test->X_point;j++){
      fprintf(fp, "%e, ", *(test->data + i*test->X_point + test->X_point - 1 - j) );
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}
