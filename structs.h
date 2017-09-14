typedef struct{
  int h_size;
  int X_point;
  int Y_point;
  int Z_point;
  int xyz_mode;
  int data_type;    // double or short
  double X_range;
  double Y_range;
  double Z_range;
  double Z_const;
  double PZ_GAIN;
  double Volt_range;
  double dY;
  int dY_bit;
  double *data;
  char *name;
  char *csvname;
}stp_t;

