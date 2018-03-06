#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {

  int i;
  char * found;
  char * axis;
  FILE *f;
  double values[6];
  char line[256];
  
  color c;
  c.red = MAX_COLOR;
  c.blue = MAX_COLOR;
  c.green = 0;
  
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);
    
    if ( !strcmp(line, "line") ) {//add line case
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      printf(":%s:\n",line);

      found = strtok(line," ");

      for (i = 0; i < 6; i++) {
	//printf("%s\t", found);
	values[i] = atof(found);

	found = strtok(NULL," ");
      }
      //printf("\n");
      
      add_edge(edges, values[0], values[1], values[2], values[3], values[4], values[5]);
      //print_martix(edges);
    }
    
    else if ( !strcmp(line, "ident") ) {//identity case
      ident(transform);
      //print_matrix(transform);
    }
    
    else if ( !strcmp(line, "scale") ) {//scale case
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      printf(":%s:\n",line);

      found = strtok(line," ");

      for (i = 0; i < 3; i++) {
	//printf("%s\t", found);
	values[i] = atof(found);
	
	found = strtok(NULL," ");
      }
      //printf("\n");

      matrix_mult( make_scale(values[0], values[1], values[2]), transform );
      //print_matrix(transform);
    }
    
    else if ( !strcmp(line, "move") ) {//move case
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      printf(":%s:\n",line);
      
      found = strtok(line," ");

      for (i = 0; i < 3; i++) {
	//printf("%s\t", found);
	values[i] = atof(found);
	
	found = strtok(NULL," ");
      }
      //printf("\n");

      matrix_mult( make_translate(values[0], values[1], values[2]), transform );
      //print_matrix(transform);
    }
    
    else if ( !strcmp(line, "rotate") ) {//rotate case
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      printf(":%s:\n",line);

      axis = strtok(line," ");
      //printf("%s\t", axis);

      found = strtok(NULL," ");
      //printf("%s\t\n", found);
      
      values[0] = (atof(found) * M_PI / 180);

      if ( !strcmp( axis, "x" ) ) {
	//printf("rot x triggered\n");
	matrix_mult( make_rotX(values[0]), transform );
      }
      
      else if ( !strcmp( axis, "y" ) ) {
	//printf("rot y triggered\n");
	matrix_mult( make_rotY(values[0]), transform );
      }
      
      else if ( !strcmp( axis, "z" ) ) {
	//printf("rot z triggered\n");
	matrix_mult( make_rotZ(values[0]), transform );
      }
      //print_matrix(transform);
    }

    else if ( !strcmp(line, "apply") ) {//apply case
      matrix_mult(transform, edges);
      //print_matrix(edges);
    }
    
    else if ( !strcmp(line, "display") ) {//display case
      clear_screen(s);
      draw_lines(edges, s, c);
      display(s);
    }
    
    else if ( !strcmp(line, "save") ) {//save case
      fgets(line, 255, f);
      //line[strlen(line)-1]='\0';
      printf(":%s:\n",line);

      clear_screen(s);
      draw_lines(edges, s, c);

      save_ppm(s, line);
    }    
    
  }
}
  
