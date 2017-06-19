#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs.h"

#define STR_SIZE 256
#define HEADER_SIZE 189

int searchHeaderEnd(FILE *fp)
{
  int cnt = 0;
  char buf[STR_SIZE] = {'0'};
  char *endmark = "end";
  
  rewind(fp);
  while( fgets(buf,STR_SIZE,fp) != NULL){
    cnt++;
    if(strstr(buf,endmark) != NULL){
      return cnt;
    }
  }
  printf("No ENDMARK\n");
  return -1;
}

int checkAmpGainHeight(FILE *fp)
{
  char buf[STR_SIZE] = {'0'};
  char *amp_mark = "Z FB output channel selector";
  
  rewind(fp);
  while( fgets(buf,STR_SIZE,fp) != NULL){
    if(strstr(buf,amp_mark) != NULL){
      if(strstr(buf,"HV") != NULL){
        return 1;
      }else{
        return 0;
      }
    }
  }
  printf("AMP_CHECK_ERROR\n");
  return -1;
}

double extractDataNum(char *str)
{
  int i,len = strlen(str);
  char *error,ch,tmp[STR_SIZE] = {'\0'};

  for(i=0;i<len;i++){
    if(*(str + i) == ':'){
      strcpy(tmp,str+i+1);
      memset(str, '\0',len);
    }
  }
  for(i=0;i<len;i++){
    ch = *(tmp + i);
    if((ch > 47 && ch < 58) || (ch == 43) || (ch > 44 && ch < 47)){
      sprintf(str,"%s%c",str,ch);
    }
  }
  //printf("1st:%s\n",str );
  return strtod(str,&error);
}

extern void readHeader3Dgrid(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"r")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  char ch;
  char tmp[STR_SIZE] = {'\0'};

  int cntCR = 0;
  double num;
  
  while(cntCR < HEADER_SIZE){
    ch = fgetc(fp);
    if(ch == '\n'){
      cntCR++;
      switch(cntCR){
        case  3:
                test->size = extractDataNum(tmp);
                break;
        case 51:
                test->Z_range = extractDataNum(tmp);
                break;
        case 54:
                test->X_range = extractDataNum(tmp);
                break;
        case 72:
                test->Z_point = extractDataNum(tmp);
                break;
        case 73:
                test->X_point = extractDataNum(tmp);
                break;
        case 163:
                test->dY_bit = extractDataNum(tmp);
                break;
        case 164:
                test->dY = extractDataNum(tmp);
                break;
        default:
                break;
      }
      memset(tmp, '\0',sizeof(tmp));
    }else{
      sprintf(tmp,"%s%c",tmp,ch);
    }
  }

  fclose(fp);
}

extern void readHeaderTopoWSxM(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"r")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  char ch;
  char tmp[STR_SIZE] = {'\0'};

  int cntCR = 0;
  double num;

  while(cntCR < HEADER_SIZE){
    ch = fgetc(fp);
    if(ch == '\n'){
      cntCR++;
      switch(cntCR){
        case  3:
                test->size = extractDataNum(tmp);
                break;
        case 51:
                test->X_range = extractDataNum(tmp);
                break;
        case 54:
                test->Y_range = extractDataNum(tmp);
                break;
        case 90:
                test->X_point = extractDataNum(tmp);
                break;
        case 91:
                test->Y_point = extractDataNum(tmp);
                break;
        default:
                break;
      }
      memset(tmp, '\0',sizeof(tmp));
    }else{
      sprintf(tmp,"%s%c",tmp,ch);
    }
  }

  fclose(fp);
}

extern void readHeaderTopoAlpha(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"r")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }

  char tmp[STR_SIZE] = {'\0'};

  int cntCR = 0;
  double num;
  
  printf("%d\n",searchHeaderEnd(fp));
  printf("%d\n",checkAmpGainHeight(fp));
  rewind(fp);
  
  while(cntCR < HEADER_SIZE){
    ch = fgetc(fp);
    if(ch == '\n'){
      cntCR++;
      switch(cntCR){
        case  3:
                test->size = extractDataNum(tmp);
                break;
        case  7:
                test->X_range = extractDataNum(tmp);
                break;
        case  9:
                test->Y_range = extractDataNum(tmp);
                break;
        case 22:
                test->X_point = extractDataNum(tmp);
                break;
        case 23:
                test->Y_point = extractDataNum(tmp);
                break;
        default:
                break;
      }
      memset(tmp, '\0',sizeof(tmp));
    }else{
      sprintf(tmp,"%s%c",tmp,ch);
    }
  }

  fclose(fp);
}
