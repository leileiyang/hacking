#include <stdio.h>
#include <string.h>

int generate_nml_cfg(char *filename, char *ip) {
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    return -1; 
  }
  fprintf(fp, "# Note: emcsvr is the master for all NML channels,"
      " and therefore is the\n");

  fprintf(fp, "# first to start.\n\n");
  fprintf(fp, "# Buffers\n");
  fprintf(fp, "# Name        Type   Host         size    neut?  (old)   buffer#  MP ---\n");
  fprintf(fp, "# Top-level buffers to EMC\n");
  fprintf(fp, "B emcCommand  SHMEM  %s   8192    0       0      1        16 1001 TCP=5005 xdr\n", ip);
  fprintf(fp, "B emcStatus   SHMEM  %s   20480   0       0      2        16 1002 TCP=5005 xdr\n", ip);
  fprintf(fp, "B emcError    SHMEM  %s   8192    0       0      3        16 1003 TCP=5005 xdr queue\n", ip);
  fprintf(fp, "# Processes\n");
  fprintf(fp, "# Name  Buffer       Type      Host        Ops  server?  timeout   master?  tcnum\n");
  fprintf(fp, "P xemc  emcCommand   REMOTE    %s  W      0      10.0      0        10\n", ip);
  fprintf(fp, "P xemc  emcStatus    REMOTE    %s  R      0      10.0      0        10\n", ip);
  fprintf(fp, "P xemc  emcError     REMOTE    %s  R      0      10.0      0        10\n", ip);
  fclose(fp);
  return 0;
}

int main() {
  generate_nml_cfg("omotion.nml", "localhost");
  return 0;
}
