#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

int countlines(char *filename);

void main(int argc, char *argv[])
{
  printf("LINES: %d\n",countlines("./OS09_01(linux).txt"));         
}


int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL) 
    return 0;

  while(!feof(fp))
    {
  ch = fgetc(fp);
  if(ch == '\n')
    {
      lines++;
    }
  }
  fclose(fp);
  return lines;
}