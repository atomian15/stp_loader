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

int checkAmpGain(FILE *fp)
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

static double extractDataNum(char *str)
{
  int i,len = strlen(str);
  char *error,ch,tmp[STR_SIZE] = {'\0'};

  for(i=0;i<len;i++){
    if(*(str + i) == ':'){
      strcpy(tmp,str+i+1);
      memset(str, '\0',len);
      len -= i + 1;
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

static char* extractDataStr(char *str)
{
  int i,len = strlen(str);
  char *error,ch,tmp[STR_SIZE] = {'\0'};

  for(i=0;i<len;i++){
    if(*(str + i) == ':'){
      strcpy(tmp,str+i+1);
      memset(str, '\0',len);
      len -= i + 1;
    }
  }
  for(i=0;i<len;i++){
    ch = *(tmp + i);
    sprintf(str,"%s%c",str,ch);
  }
  //printf("1st:%s\n",str );
  return str;
}

extern void readHeaderTopo(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"r")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }
  char tmp[STR_SIZE] = {'\0'};
  char *check[] = {"X Amplitude",
                   "Y Amplitude",
                   "Number of rows",
                   "Number of columns",
                   "Z Calibration",
                   "Z HV Amp Gain (H)",
                   "Z HV Amp Gain (L)",
                   "Image header size",
                   "Image Data Type"};

  int cntCR = 0;
  int header_size = searchHeaderEnd(fp);
  int HL = checkAmpGain(fp);
  double num;
  
  rewind(fp);
  test->Volt_range = 1.0e1;

  while(cntCR < header_size){
    fgets(tmp,STR_SIZE,fp);
    cntCR++;
    if(strstr(tmp,check[0]) != NULL){
        test->X_range = extractDataNum(tmp);
    }else if(strstr(tmp,check[1]) != NULL){
        test->Y_range = extractDataNum(tmp);
    }else if(strstr(tmp,check[2]) != NULL){
        test->X_point = extractDataNum(tmp);
    }else if(strstr(tmp,check[3]) != NULL){
        test->Y_point = extractDataNum(tmp);
    }else if(strstr(tmp,check[4]) != NULL){
        test->Z_const = extractDataNum(tmp);
    }else if(strstr(tmp,check[5]) != NULL){
        if(HL == 1){
            test->PZ_GAIN = extractDataNum(tmp);
        }
    }else if(strstr(tmp,check[6]) != NULL){
        if(HL == 0){
            test->PZ_GAIN = extractDataNum(tmp);
        }
    }else if(strstr(tmp,check[7]) != NULL){
        test->h_size = extractDataNum(tmp);
    }else{}
    memset(tmp, '\0',sizeof(tmp));
  }
  fclose(fp);
}

extern void readHeaderZX(stp_t *test)
{
  FILE *fp;
  if((fp = fopen(test->name,"r")) == NULL){
    printf("FILE ERROR\n");
    exit(1);
  }
  char tmp[STR_SIZE] = {'\0'};
  char *check[] = {"X Amplitude",
                   "Y Amplitude",
                   "Number of rows",
                   "Number of columns",
                   "Z Calibration",
                   "Image header size"};

  int cntCR = 0;
  int header_size = searchHeaderEnd(fp);
  double num;
  
  rewind(fp);
  while(cntCR < header_size){
    fgets(tmp,STR_SIZE,fp);
    cntCR++;
    if(strstr(tmp,check[0]) != NULL){
        test->Z_range = extractDataNum(tmp);
    }else if(strstr(tmp,check[1]) != NULL){
        test->X_range = extractDataNum(tmp);
    }else if(strstr(tmp,check[2]) != NULL){
        test->X_point = extractDataNum(tmp);
    }else if(strstr(tmp,check[3]) != NULL){
        test->Z_point = extractDataNum(tmp);
    }else if(strstr(tmp,check[4]) != NULL){
        test->Z_const = extractDataNum(tmp);
    }else if(strstr(tmp,check[5]) != NULL){
        test->h_size = extractDataNum(tmp);
    }else{}
    memset(tmp, '\0',sizeof(tmp));
  }

  fclose(fp);
}
