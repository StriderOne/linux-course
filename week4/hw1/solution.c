#include <stdio.h>

int main(int argc, char* argv[])
{
  char command[256];
  char line[130];     
  FILE *FileOpen;
  int counter = 0;
  sprintf(command, "%s %s", argv[1], argv[2]);

  FileOpen = popen(command, "r");      
  char c = fgetc(FileOpen);    
  while (!feof(FileOpen)) {
    if (c == '0')
      counter++;
    c = fgetc(FileOpen);  
  }
  printf("%d\n", counter);
  pclose(FileOpen);
}
