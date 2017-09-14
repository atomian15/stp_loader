#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs.h"

#define STR_SIZE 128

void xyzSelector(stp_t*);      // Topo or ZX
void datatypeSelector(stp_t*); // short (Alpha) or double (WSxM)

void readHeaderTopo(stp_t*);
void readHeaderZX(stp_t*);

void readBinaryTopo(stp_t*);
void readBinaryZX(stp_t*);

void printCSVTopo(stp_t*);
void printCSVZX(stp_t*);

void gp_plotTopo(stp_t*);
void gp_plotZX(stp_t*);

int main(int argc,char *argv[])
{
  stp_t test = {0};
  
  char outname[] = "outname.csv";
  test.csvname = outname;
  
  test.name = argv[1];
  
  xyzSelector(&test);
  datatypeSelector(&test);
  
  if(test.xyz_mode == 1){
    readHeaderTopo(&test);
    printf("%d\n",test.h_size);
    printf("%e\n",test.X_range);
    printf("%d\n",test.X_point);
    printf("%e\n",test.Y_range);
    printf("%d\n",test.Y_point);
    printf("%e\n",test.Z_const);
    printf("%e\n",test.PZ_GAIN);
    printf("%d\n",test.data_type);  
    readBinaryTopo(&test);
    printCSVTopo(&test);
    gp_plotTopo(&test);
  }else{
    readHeaderZX(&test);
    printf("%d\n",test.h_size);
    printf("%e\n",test.X_range);
    printf("%d\n",test.X_point);
    printf("%e\n",test.Z_range);
    printf("%d\n",test.Z_point);
    printf("%e\n",test.Z_const);
    printf("%e\n",test.PZ_GAIN);
    printf("%d\n",test.data_type);  
    readBinaryZX(&test);
    printCSVZX(&test);
    gp_plotZX(&test);
  }
  
  //readHeaderTopoAlpha(&test);
  //readBinaryTopoAlpha(&test);
  //printCSVTopo(&test,outfname_topo_alpha);

  //gp_plot2DTopo(&test,outfname_topo_alpha);

  free(test.data);
  return 0;
}
