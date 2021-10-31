#ifndef __RUNCOMMAND_H
#define __RUNCOMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run_command(char* arr[]);
int cd(char* arr[]);
int redirection(char* arr[], int pipe_flag);
int Pipe(char* arr[]);

#endif
