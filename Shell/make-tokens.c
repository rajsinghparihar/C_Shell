#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "runcommand.h"

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

void signal_handler(int signal_number) {
    // Write your code here.
		char signame[10];
		if(signal_number == 2){
			printf("\nInterrupted : SIGINT\nbash>");
      fflush(0);
      return;
		}
}

char **tokenize(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for(i =0; i < strlen(line); i++){

        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0){
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0;
            }
        }
        else {
            token[tokenIndex++] = readChar;
        }
    }

    free(token);
    tokens[tokenNo] = NULL ;
    return tokens;
}


int main(void)
{
    signal(SIGINT, signal_handler);
    char  line[MAX_INPUT_SIZE];
    char  **tokens;
    char  **command_tokens;
    int i;

    while (1) {

        printf("raj@turtle>");
        bzero(line, MAX_INPUT_SIZE);
        gets(line);
        if(strcmp(line, "") == 0)
        {
          continue;
        }
        line[strlen(line)] = '\n'; //terminate with new line
        command_tokens = strtok(line,";;");
        while(command_tokens != NULL)
        {
          tokens = tokenize(command_tokens);
          int redir_flag = 0;
					int pipe_flag = 0;

          for(i=0;tokens[i]!=NULL;i++){
              if(strcmp(tokens[i],">") == 0)
              {
                redir_flag = 1;
              }
          }

					for(i=0;tokens[i]!=NULL;i++){
              if(strcmp(tokens[i],"|") == 0)
              {
                pipe_flag = 1;
              }
          }

          //do whatever you want with the commands, here we just print them
					if(pipe_flag == 1 && redir_flag == 0)
          {
            Pipe(tokens);
          }
					else if(redir_flag == 1)
          {
            redirection(tokens, pipe_flag);
          }
          else if(strcmp(tokens[0], "exit") == 0){
            exit(0);
          }
          else if(strcmp(tokens[0],"cd") == 0)
          {
            cd(tokens);
          }
          else
          {
            run_command(tokens);
          }
          // Freeing the allocated memory
          for(i=0;tokens[i]!=NULL;i++){
              free(tokens[i]);
          }
          free(tokens);
          command_tokens = strtok(NULL, ";;");
        }
    }
    // Freeing the allocated memory
    for(i=0;command_tokens[i]!=NULL;i++){
        free(command_tokens[i]);
    }
    free(command_tokens);
    return 0;
}
