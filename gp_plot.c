#include<stdio.h>
#include"structs.h"

extern void gp_plotZX(stp_t *test)
{
  FILE *gp = popen("gnuplot -persist","w");

  fprintf(gp, "set datafile separator \",\"\n");
  fprintf(gp, "set pm3d map\n");
  fprintf(gp, "set xrange [0:%d]\n", test->Z_point-1);
  fprintf(gp, "set yrange [0:%d]\n", test->X_point-1);
  fprintf(gp, "set size ratio %f\n", (double)(test->X_point) / (double)(test->Z_point) );
  fprintf(gp, "splot \"%s\" matrix\n",test->csvname);
  fprintf(gp, "reset\n");

  pclose(gp);
}

extern void gp_plotTopo(stp_t *test)
{
  FILE *gp = popen("gnuplot -persist","w");

  fprintf(gp, "set datafile separator \",\"\n");
  fprintf(gp, "set pm3d map\n");
  fprintf(gp, "set xrange [0:%d]\n", test->X_point-1);
  fprintf(gp, "set yrange [0:%d]\n", test->Y_point-1);
  fprintf(gp, "set size ratio %f\n", (double)(test->X_point) / (double)(test->Y_point) );
  fprintf(gp, "splot \"%s\" matrix\n",test->csvname);
  fprintf(gp, "reset\n");
  
  pclose(gp);
}
