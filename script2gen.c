#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * fp;
  int i;

  fp = fopen("./script2", "w");

  fprintf(fp, "line\n");
  fprintf(fp, "-125 -125 0 125 -125 0\n");

  fprintf(fp, "line\n");
  fprintf(fp, "125 -125 0 125 125 0\n");

  fprintf(fp, "line\n");
  fprintf(fp, "125 125 0 -125 125 0\n");

  fprintf(fp, "line\n");
  fprintf(fp, "-125 125 0 -125 -125 0\n");


  for (i = 0; i < 260; i += 3) {
    fprintf(fp, "ident\n");
    fprintf(fp, "rotate\n");
    fprintf(fp, "z %d\n", i);
    fprintf(fp, "move\n");
    fprintf(fp, "250 250 0\n");
    fprintf(fp, "apply\n");
    fprintf(fp, "display\n");
    fprintf(fp, "ident\n");
    fprintf(fp, "move\n");
    fprintf(fp, "-250 -250 0\n");
    fprintf(fp, "rotate\n");
    fprintf(fp, "z -%d\n", i);
    fprintf(fp, "apply\n");
  }

  fprintf(fp, "save\n");
  fprintf(fp, "pic.png\n");
}
  
    
    
