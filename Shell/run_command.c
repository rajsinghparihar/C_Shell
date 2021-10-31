#include "runcommand.h"

int run_command(char* arr[])
{
    if (fork() == 0)
    {
        int flag = execvp(arr[0], arr);
        if(flag == -1)
        {
          printf("%s : Invalid command\n", arr[0]);
          exit(0);
        }
    }
    else
        wait(NULL);
}
