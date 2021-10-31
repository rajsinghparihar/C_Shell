#include "runcommand.h"

int cd(char* arr[])
{
    int flag = chdir(arr[1]);
    if(flag == -1)
    {
      printf("%s : No such file or directory\n", arr[1]);
    }
}
