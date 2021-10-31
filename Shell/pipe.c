#include "runcommand.h"
#include <fcntl.h>
#include <string.h>

int Pipe(char* arr[])
{
  char* left_commands[64];
  char* right_commands[64];
  int fd[2];
  if(pipe(fd) == -1)
  {
    return 1;
  }
  int pos_pipe;
  for(int i=0;arr[i]!=NULL;i++){
      if(strcmp(arr[i],"|") == 0)
      {
        pos_pipe = i;
      }
    }
  for (int i = 0; i <= pos_pipe-1; i++) {
    left_commands[i] = arr[i];
  }
  left_commands[pos_pipe] = NULL;
  int cnt = 0;
  for (int i = pos_pipe+1; arr[i] != NULL ; i++) {
    right_commands[i-(pos_pipe+1)] = arr[i];
    cnt++;
  }
  right_commands[cnt] = NULL;
  int pid1 = fork();
  if(pid1 < 0){
    return 2;
  }
  if(pid1 == 0){
    close(1);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execvp(left_commands[0], left_commands);
  }

  int pid2 = fork();
  if(pid2 < 0){
    return 3;
  }
  if(pid2 == 0){
    close(0);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
    execvp(right_commands[0], right_commands);
  }
  close(fd[0]);
  close(fd[1]);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
  return 0;
}
