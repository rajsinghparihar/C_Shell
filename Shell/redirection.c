#include "runcommand.h"
#include <fcntl.h>
int redirection(char* arr[], int pipe_flag)
{
  int pos_redir;
  for(int i=0;arr[i]!=NULL;i++){
      if(strcmp(arr[i],">") == 0)
      {
        pos_redir = i;
        arr[i] = NULL;
      }
  }
  if(pipe_flag == 0)
  {
      if (fork() == 0)
      {
        int file = open(arr[pos_redir+1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(file == -1){
          printf("Error\n");
        }
        dup2(file, 1);
        close(file);
        execvp(arr[0], arr);
      }
      else
          wait(NULL);
  }
  else
  {
    char* left_commands[64];
    for(int i=0;i < pos_redir;i++){
        left_commands[i] = arr[i];
    }
      if (fork() == 0)
      {
        int file = open(arr[pos_redir+1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(file == -1){
          printf("Error\n");
        }
        dup2(file, 1);
        close(file);
        Pipe(left_commands);
        exit(0);
      }
      else
          wait(NULL);
  }
  return 0;
}
