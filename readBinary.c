#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include"structs.h"

void DecimaltoBinary(unsigned int decimal,unsigned int *byteBit)
{
  int i;

  for(i=0;i<8;i++){
    *(byteBit + i) = decimal % 2;
    //decimal = decimal / 2;
    decimal = decimal >> 1;
  }
/*
  for(i=0;i<8;i++){
    printf("%d\t",*(byteBit + i) );
  }
  printf("\n");
*/
}

double Bit_to_double(unsigned int *doubleBit)
{
  int i;
  double Sign_part = 0.0e0;
  double Exp_part  = 0.0e0;

  for(i=1;i<12;i++){
   Sign_part += (double)(*(doubleBit + i))*pow(2.0e0,11-i);
  }

  Sign_part -= 1023e0;

  //printf("%.10lf\n",Sign_part);
  for(i=12;i<64;i++){
   Exp_part += (double)(*(doubleBit + i))*pow(2.0e0,11-i);
  }

  //printf("%.10lf\n",Exp_part);
  Exp_part += 1.0e0;

  Sign_part = pow(2.0e0,Sign_part) * Exp_part;

  if(*doubleBit == 1){
    Sign_part *= -1.0e0;
  }

  //printf("%.15e\n",Sign_part);
  //printf("%.10e\n",(double)n[2]);
  return Sign_part;
}

void readBinary3Dgrid(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[64] = {0};
  int i,j,k,l,cnt=0;
  double tmp;

  test->data = (double *)malloc(test->X_point * test->Z_point * sizeof(double));

  for(i=0;i<test->X_point;i++){
  //for(i=0;i<1;i++){
    for(j=0;j<test->Z_point;j++){
    //for(j=0;j<1;j++){
      for(k=0;k<sizeof(double);k++){
        fread(&ch,1,1,fp);
        //printf("%02X\n",ch );
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[63-8*cnt-l] = byteBit[l];
        }
        cnt++;
      }
      *(test->data + i*test->Z_point + j) = Bit_to_double(doubleBit);
      if(fabs(*(test->data + i*test->Z_point + j)) < DBL_MIN){
        *(test->data + i*test->Z_point + j) = 0.0e0;
      }
      cnt = 0;
      //printf("%e\n",*(test->data + i*test->Z_point + j));
    }
  }
/*
  printf("%d\n",0x0a);
  printf("%lu\n",sizeof(double));
  printf("%lu\n",sizeof(unsigned int));
*/
  fclose(fp);
}


void readBinaryTopoWSxM(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[64] = {0};
  int i,j,k,l,cnt=0;
  double tmp;

  test->data = (double *)malloc(test->Y_point * test->X_point * sizeof(double));

  for(i=0;i<test->Y_point;i++){
  //for(i=0;i<1;i++){
    for(j=0;j<test->X_point;j++){
    //for(j=0;j<1;j++){
      for(k=0;k<sizeof(double);k++){
        fread(&ch,1,1,fp);
        //printf("%02X\n",ch );
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[63-8*cnt-l] = byteBit[l];
        }
        cnt++;
      }
      *(test->data + i*test->X_point + j) = Bit_to_double(doubleBit);
      if(fabs(*(test->data + i*test->X_point + j)) < DBL_MIN){
        *(test->data + i*test->X_point + j) = 0.0e0;
      }
      cnt = 0;
      //printf("%e\n",*(test->data + i*test->X_point + j));
    }
  }
/*
  printf("%d\n",0x0a);
  printf("%lu\n",sizeof(double));
  printf("%lu\n",sizeof(unsigned int));
*/
  fclose(fp);
}


void readBinaryTopoAlpha(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[64] = {0};
  int i,j,k,l,cnt=0;
  double tmp;

  test->data = (double *)malloc(test->Y_point * test->X_point * sizeof(double));

  for(i=0;i<test->Y_point;i++){
  //for(i=0;i<1;i++){
    for(j=0;j<test->X_point;j++){
    //for(j=0;j<1;j++){
      for(k=0;k<sizeof(double);k++){
        fread(&ch,1,1,fp);
        //printf("%02X\n",ch );
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[63-8*cnt-l] = byteBit[l];
        }
        cnt++;
      }
      *(test->data + i*test->X_point + j) = Bit_to_double(doubleBit);
      if(fabs(*(test->data + i*test->X_point + j)) < DBL_MIN){
        *(test->data + i*test->X_point + j) = 0.0e0;
      }
      cnt = 0;
      //printf("%e\n",*(test->data + i*test->X_point + j));
    }
  }
/*
  printf("%d\n",0x0a);
  printf("%lu\n",sizeof(double));
  printf("%lu\n",sizeof(unsigned int));
*/
  fclose(fp);
}
