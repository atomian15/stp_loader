#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include"structs.h"

void BitComp2(unsigned int *doubleBit)
{
  int i,cnt = 0;    // if cnt = 0, the value means as -128
  int BIT_LEN = 16; //short 
  
  for(i=0;i<BIT_LEN-1;i++){
    if(*(doubleBit + BIT_LEN - 1 - i) == 1){
      cnt = BIT_LEN - 1 - i;
      break;
    }
  }
  if(cnt == 0){
    cnt = BIT_LEN;
  }
  
  for(i=1;i<cnt;i++){
    if(*(doubleBit + i) == 0){
      *(doubleBit + i) = 1;
    }else{
      *(doubleBit + i) = 0;
    }
  }
}

void AutoOffset(stp_t *test)
{
  int i;
  double min = DBL_MAX;
  
  for(i=0;i<test->X_point * test->Y_point;i++){
    if(*(test->data + i) < min){
      min = *(test->data + i);
    }
  }
  for(i=0;i<test->X_point * test->Y_point;i++){
    *(test->data + i) -= min;
  }
}

void toOffset(stp_t *test)
{
  int i;
  double min = DBL_MAX;
  
  for(i=0;i<test->X_point * test->Y_point;i++){
    if(*(test->data + i) < min){
      min = *(test->data + i);
    }
  }
  printf("%e\n\n",min);
}
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

static double Bit_to_double(unsigned int *doubleBit)
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

static double Bit_to_short(stp_t *test, unsigned int *doubleBit)
{
  int i;
  double sum = 0e0;
  
  for(i=1;i<16;i++){
    sum += pow(2e0,(double)(15-i)) * (double)(*(doubleBit + i));
  }
  if(test->xyz_mode == 0){
    test->PZ_GAIN = 1.0e0;
    test->Z_const = 1.0e0;
  }
  sum *= 1.0e1 * test->PZ_GAIN * test->Z_const;
  sum /= pow(2e0,15e0);
   
  if(*doubleBit == 1){
    sum *= -1.0e0;
  }
  
  //sum += 0.721;
  return sum;
}

void readBinaryZXWSxM(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->h_size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[64] = {0};
  int i,j,k,l;

  test->data = (double *)malloc(test->X_point * test->Z_point * sizeof(double));

  for(i=0;i<test->X_point;i++){
    for(j=0;j<test->Z_point;j++){
      for(k=0;k<sizeof(double);k++){
        fread(&ch,1,1,fp);
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[63-8*k-l] = byteBit[l];
        }
      }
      *(test->data + i*test->Z_point + j) = Bit_to_double(doubleBit);
      if(fabs(*(test->data + i*test->Z_point + j)) < DBL_MIN){
        *(test->data + i*test->Z_point + j) = 0.0e0;
      }
    }
  }
  fclose(fp);
}

void readBinaryZXAlpha(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->h_size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[16] = {0};
  int i,j,k,l;
  
  test->data = (double *)malloc(test->X_point * test->Z_point * sizeof(double));

  for(i=0;i<test->X_point;i++){
    for(j=0;j<test->Z_point;j++){
      for(k=0;k<sizeof(short);k++){
        fread(&ch,1,1,fp);
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[15-8*k-l] = byteBit[l];
        }
      }
      if(*doubleBit == 1){
        BitComp2(doubleBit);
      }
      *(test->data + i*test->Z_point + j) = Bit_to_short(test,doubleBit);
      /*if(fabs(*(test->data + i*test->Z_point + j)) < DBL_MIN){
        *(test->data + i*test->Z_point + j) = 0.0e0;
      }*/
    }
  }
  fclose(fp);
}


void readBinaryTopoWSxM(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->h_size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[64] = {0};
  int i,j,k,l;
  double tmp;

  test->data = (double *)malloc(test->Y_point * test->X_point * sizeof(double));

  for(i=0;i<test->Y_point;i++){
    for(j=0;j<test->X_point;j++){
      for(k=0;k<sizeof(double);k++){
        fread(&ch,1,1,fp);
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[63-8*k-l] = byteBit[l];
        }
      }
      *(test->data + i*test->X_point + j) = Bit_to_double(doubleBit);
      if(fabs(*(test->data + i*test->X_point + j)) < DBL_MIN){
        *(test->data + i*test->X_point + j) = 0.0e0;
      }
    }
  }
  fclose(fp);
}


void readBinaryTopoAlpha(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"rb")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  fseek(fp,test->h_size,SEEK_SET);

  unsigned int ch,byteBit[8] = {0};
  unsigned int doubleBit[16] = {0};
  int i,j,k,l;
  double tmp;

  test->data = (double *)malloc(test->Y_point * test->X_point * sizeof(double));

  for(i=0;i<test->Y_point;i++){
    for(j=0;j<test->X_point;j++){
      for(k=0;k<sizeof(short);k++){
        fread(&ch,1,1,fp);
        DecimaltoBinary(ch,byteBit);
        for(l=0;l<8;l++){
          doubleBit[15-8*k-l] = byteBit[l];
        }
      }
      if(*doubleBit == 1){
        BitComp2(doubleBit);
      }
      *(test->data + i*test->X_point + j) = Bit_to_short(test,doubleBit);
      /*if(fabs(*(test->data + i*test->X_point + j)) < DBL_MIN){
        *(test->data + i*test->X_point + j) = 0.0e0;
      }*/
    }
  }
  fclose(fp);
}


extern void readBinaryTopo(stp_t *test)
{
  if(test->data_type == 0){
    readBinaryTopoAlpha(test);
  }else if(test->data_type == 1){
    readBinaryTopoWSxM(test);
  }
  AutoOffset(test);
}

extern void readBinaryZX(stp_t *test)
{
  if(test->data_type == 0){
    readBinaryZXAlpha(test);
  }else if(test->data_type == 1){
    readBinaryZXWSxM(test);
  }else{
    printf("data_type ERROR\n");
  }
}