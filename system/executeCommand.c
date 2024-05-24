#include "../header/main.h"

void executeCommand(DirectoryTree *currentDirectoryTree, char *command)
{
    char *var;
    char *var1;
    char *var2;
    int value;

    if (!strcmp(command, "") || command[0] == ' ')
        return;

    var = strtok(command, " ");

    if (!strcmp(var, "mkdir"))
    {
        var = strtok(NULL, " ");
        // mkdir 코드 구현
    }
    else if (!strcmp(var, "touch"))
    {
        var = strtok(NULL, " ");
        // touch 코드 구현
    }
    else if (!strcmp(var, "mv"))
    {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        // mv 코드 구현
    }
    else if (!strcmp(var, "cp"))
    {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        // cp 코드 구현
    }
    else if (!strcmp(var, "cd"))
    {
        var = strtok(NULL, " ");
        cd(currentDirectoryTree, var);
        // cd 코드 구현
    }
    else if (!strcmp(var, "pwd"))
    {
        var = strtok(NULL, " ");
        pwd(currentDirectoryTree, dirStack, var);
    }
    else if (!strcmp(var, "ls"))
    {
        var = strtok(NULL, " ");
        // ls 코드 구현
    }
    else if (!strcmp(var, "cat"))
    {
        var = strtok(NULL, " ");
        cat(currentDirectoryTree, var);
    }
    else if (!strcmp(var, "chmod"))
    {
        var = strtok(NULL, " ");
        // chmod 코드 구현
    }
    else if (!strcmp(var, "grep"))
    {
        var = strtok(NULL, " ");
        // grep 코드 구현
    }
    else if (!strcmp(command, "exit"))
    {
        printf("logout\n");
        exit(0);
    }
    else
        printf("Command '%s' not found\n", command);
    return;
}
