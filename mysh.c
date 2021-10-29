// Contributors: Sebastian Almeida, Alex, Estefania Sanchez
// COP 4600 Homework 2
// 10/27/2021

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
char* readInput();
char** tokenize();
char*** addToHistory();

// Function To Read Users Input As A Raw String
char *readInput(void)
{
  int bufsize = 1024;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  // Check If Malloc Succeded
  if (!buffer)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  // Loop Through User Input
  while (1) {
    // Read a character
    c = getchar();
    // If we hit EOF, replace it with a null character and return.
    if (c == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = c;
    }
    position++;
    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize)
    {
      bufsize += 1024;
      buffer = realloc(buffer, bufsize);
      // Check If Realloc Succeeded
      if (!buffer)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

// Function To Split Raw Input Into Tokens On Spaces
char **tokenize(char *line)
{
  int bufsize = 128;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  // Check If Malloc Succeeded
  if (!tokens)
  {
    exit(EXIT_FAILURE);
  }
  token = strtok(line, " ");
  while (token != NULL)
  {
    tokens[position] = token;
    position++;
    if (position >= bufsize)
    {
      bufsize += 128;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      // Check If Realloc Succeeded
      if (!tokens)
      {
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, " ");
  }
  tokens[position] = NULL;
  return tokens;
}

// moves directory || Estefania Sanchez
void moveToDir(char *directory)
{
  /* The code here in the comments will change directories but only once
     I promise I tried my best.
  // check for directory
  if (parsedInput[1] == NULL)
  {
    printf("**Error: no directory stated.\n**Correct input format: # movetodir <directory>\n");
  }
  else if (currentDir == NULL)
  {
    printf("**Error: unable to open directory.\n");
  }
  else
  {
    //if ((temp = opendir(parsedInput[1])) != NULL)
    if ((filepath = realpath(parsedInput[1], NULL)) != NULL)
    {
      // close current directories
      //closedir(temp);
      closedir(currentDir);
      // update filepath and current directory
      //filepath = realpath(parsedInput[1], NULL);
      currentDir = opendir(filepath);
      printf("Moved to directory: %s\n", parsedInput[1]);
    }
    else
    {
      printf("**Error: directory not found.\n");
    }
  }
  */
  char currdir[PATH_MAX];
  if (directory == NULL)
  {
    printf("**Error: no directory stated.\n**Correct input format: # movetodir <directory>\n");
  }
  else
  {
    strcpy(currdir,realpath(directory, NULL));
    if (chdir(directory) != 0)
    {
      printf("**Error: directory not found.\n");
      return;
    }
    printf("Moved to directory: %s\n", directory);
  }
}

// gets current directory || Estefania Sanchez
void whereAmI()
{
  char *filepath;
  char currdir[PATH_MAX];
  filepath = getcwd(currdir, sizeof(currdir));
  printf("Current Directory: %s\n", filepath);
}


int main()
{
  // Initialize Variables
  char *rawInput;
  char **parsedInput;
  char ***history;


  int *argc;
  int byebye = 0;



  // Loop For Printing Prompt And Then Reading User Input
  while(byebye == 0)
  {
    // Print Prompt
    printf("# ");
    // Read In User Input
    rawInput = readInput();
    // Parse User Input
    parsedInput = tokenize(rawInput);
    // Ensure That A Command Was Passed
    if (parsedInput[0] == NULL)
    {
      free(rawInput);
      free(parsedInput);
      continue;
    }
    // If-Else Command Statemnt
    // ByeBye Command
    if (strcmp(parsedInput[0], "byebye") == 0)
    {
      byebye = 1;
      break;
    }
    // History Command
    else if (strcmp(parsedInput[0], "history") == 0)
    {
    }
    // Replay Command
    else if (strcmp(parsedInput[0], "replay") == 0)
    {
    }
    // Start Command
    else if (strcmp(parsedInput[0], "start") == 0)
    {
    }
    // Background Command
    else if (strcmp(parsedInput[0], "background") == 0)
    {
    }
    // Dalek Command
    else if (strcmp(parsedInput[0], "dalek") == 0)
    {
    }
    // Movetodir Command: Estefania Sanchez
    else if (strcmp(parsedInput[0], "movetodir") == 0)
    {
        moveToDir(parsedInput[1]);
    }
    // Whereami Command: Estefania Sanchez
    else if (strcmp(parsedInput[0], "whereami") == 0)
    {
        whereAmI();
    }
    // Unrecognized Command
    else
    {
      printf("Unrecognized Command\n");
    }
    // Free Input Arrays
    free(rawInput);
    free(parsedInput);
  }
  return 0;
}
