#include "../header/main.h"

void executeCommand(DirectoryTree *currentDirectoryTree, char *command) {
    char *var;
    char *var1;
    char *var2;
    int value;

    if (!strcmp(command, "") || command[0] == ' ') return;

    var = strtok(command, " ");
    
    if (!strcmp(var, "mkdir")) {
        var = strtok(NULL, " ");
        //mkdir 코드 구현 
    } else if (!strcmp(var, "touch")) {
        var = strtok(NULL, " ");
        //touch 코드 구현
    } else if (!strcmp(var, "mv")) {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        //mv 코드 구현
    } else if (!strcmp(var, "cp")) {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        //cp 코드 구현
    } else if (!strcmp(var, "cd")) {
        var = strtok(NULL, " ");
        cd(currentDirectoryTree, var);
        //cd 코드 구현
    } else if(!strcmp(var, "pwd")) {
        var = strtok(NULL, " ");
        pwd(currentDirectoryTree, dirStack, var);
    } else if (!strcmp(var, "ls")) {
        var = strtok(NULL, " ");
        ls(currentDirectoryTree, var);
    } else if (!strcmp(var, "cat")) {
        var = strtok(NULL, " ");
        catInterface(currentDirectoryTree, var);
    } else if(!strcmp(var, "chmod")) {
        var = strtok(NULL, " ");
        if (var == NULL) {
            printf("chmod: Invalid option\n");
            printf("Try \'chmod --help\' for more information.\n");
            return;
        }
        var1 = strtok(NULL, " ");
        //문자열 혹은 숫자로 권한을 받아서 Permission change_mod로 바꾸는 코드 추가 필요
        ch_mod(currentDirectoryTree, var, var1);
        //chmod 코드 구현
    } else if (!strcmp(var, "grep")) {
        var = strtok(NULL, " ");
        //grep 코드 구현
    } else if(!strcmp(command, "exit")) {
        printf("logout\n");
        exit(0);
    } else printf("Command '%s' not found\n", command);
    return;
}
