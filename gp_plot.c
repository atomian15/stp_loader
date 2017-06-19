#include<stdio.h>
#include"structs.h"

void gp_plot2D3Dgrid(stp_t *test,char *outfname)
{
  FILE *gp = popen("gnuplot -persist","w");

  fprintf(gp, "set datafile separator \",\"\n");
  fprintf(gp, "set pm3d map\n");
  fprintf(gp, "set xrange [0:%d]\n", test->Z_point-1);
  fprintf(gp, "set yrange [0:%d]\n", test->X_point-1);
  fprintf(gp, "set size ratio %f\n", (double)(test->X_point) / (double)(test->Z_point) );
  fprintf(gp, "splot \"%s\" matrix\n",outfname);
  fprintf(gp, "reset\n");

  pclose(gp);
}

void gp_plot2DTopo(stp_t *test,char *outfname)
{
  FILE *gp = popen("gnuplot -persist","w");

  fprintf(gp, "set datafile separator \",\"\n");
  fprintf(gp, "set pm3d map\n");
  fprintf(gp, "set xrange [0:%d]\n", test->X_point-1);
  fprintf(gp, "set yrange [0:%d]\n", test->Y_point-1);
  fprintf(gp, "set size ratio %f\n", (double)(test->X_point) / (double)(test->Y_point) );
  fprintf(gp, "splot \"%s\" matrix\n",outfname);
  fprintf(gp, "reset\n");
  
  pclose(gp);
}
