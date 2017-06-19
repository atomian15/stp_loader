#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs.h"

void readHeader3Dgrid(stp_t*);
void readBinary3Dgrid(stp_t*);
void printCSV3Dgrid(stp_t*,char*);
void gp_plot2D3Dgrid(stp_t*,char*);

void readHeaderTopoWSxM(stp_t*);
void readBinaryTopoWSxM(stp_t*);
void printCSVTopo(stp_t*,char*);
void gp_plot2DTopo(stp_t*,char*);

void readHeaderTopoAlpha(stp_t*);
void readBinaryTopoAlpha(stp_t*);

int main(void)
{
  stp_t test = {0};
/*
  char *fname = "sample.stp";
  char *outfname = "data.csv";


  test.name = fname;

  readHeader3Dgrid(&test);
  readBinary3Dgrid(&test);
  printCSV3Dgrid(&test,outfname);

  gp_plot2D3Dgrid(&test,outfname);

  memset(&test,0,sizeof(stp_t));

  char *fname_topo = "sample_topo.stp";
  char *outfname_topo = "data_topo.csv";

  test.name = fname_topo;

  readHeaderTopoWSxM(&test);
  readBinaryTopoAlpha(&test);
  printCSVTopo(&test,outfname_topo);

  gp_plot2DTopo(&test,outfname_topo);
  
  memset(&test,0,sizeof(stp_t));
*/
  char *fname_topo_alpha = "topo_alpha.stp";
  char *outfname_topo_alpha = "data_topo_alpha.csv";

  test.name = fname_topo_alpha;

  readHeaderTopoAlpha(&test);
//  readBinaryTopoAlpha(&test);
//  printCSVTopo(&test,outfname_topo_alpha);

//  gp_plot2DTopo(&test,outfname_topo_alpha);

  free(test.data);
  return 0;
}
