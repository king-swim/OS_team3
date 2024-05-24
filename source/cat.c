#include "../header/main.h"

void cat(DirectoryTree *currentDirectoryTree, char *var)
{
    // var로 전달된 파일명 또는 옵션을 파싱하여 파일을 처리
    char *fileName = var; // 기본적으로 파일명은 var로부터 추출
    char *option = NULL;

    // 옵션이 있는 경우 var에서 옵션 추출과 파일명 재추출
    if (var[0] == '-' || var[0] == '>')
    {
        option = strtok(var, " ");
        fileName = strtok(NULL, " ");
    }

    // 현재 위치에 존재하는 파일이면 노드 반환하고 아니면 NULL
    DirectoryNode *fileNode = IsExistDir(currentDirectoryTree, var, '-');

    // 파일이 존재하고 권한이 있는 경우
    if (fileNode && HasPermission(fileNode, 'r'))
    {
        char filePath[MAX_DIR];
        sprintf(filePath, "%s/%s", currentDirectoryTree->current->name, var); // 파일 경로 생성

        if (option)
        {
            if (strcmp(option, "-n") == 0)
            {
                // 각 줄에 줄 번호 출력
                int lineNumber = 1;
                FILE *file = fopen(fileName, "r");
                if (file)
                {
                    char buffer[1024];
                    while (fgets(buffer, sizeof(buffer), file))
                    {
                        printf("%d %s", lineNumber++, buffer);
                    }
                    fclose(file);
                }
                else
                {
                    printf("Permission denied or File not found: %s\n", fileName);
                }
            }
            else if (strcmp(option, "-E") == 0)
            {
                // 각 줄 끝에 줄 바꿈 문자 표시
                FILE *file = fopen(fileName, "r");
                if (file)
                {
                    char buffer[1024];
                    while (fgets(buffer, sizeof(buffer), file))
                    {
                        printf("%s$\n", buffer);
                    }
                    fclose(file);
                }
                else
                {
                    printf("Permission denied or File not found: %s\n", fileName);
                }
            }
            else if (strcmp(option, "-b") == 0)
            {
                // 비어 있지 않은 줄에만 줄 번호 출력
                int lineNumber = 1;
                FILE *file = fopen(fileName, "r");
                if (file)
                {
                    char buffer[1024];
                    while (fgets(buffer, sizeof(buffer), file))
                    {
                        if (strlen(buffer) > 1)
                        { // 비어 있지 않은 줄만 처리
                            printf("%d %s", lineNumber++, buffer);
                        }
                        else
                        {
                            printf("%s", buffer);
                        }
                    }
                    fclose(file);
                }
                else
                {
                    printf("Permission denied or File not found: %s\n", fileName);
                }
            }
            else if (strcmp(option, "-h") == 0 || strcmp(option, "--help") == 0)
            {
                printf("Usage: cat [OPTION]... [FILE]...\n");
                printf("Concatenate FILE(s) to standard output.\n\n");
                printf("  -n, --number            number all output lines\n");
                printf("  -b, --number-nonblank   number nonempty output lines, overrides -n\n");
                printf("  -E, --show-ends         display $ at end of each line\n");
                printf("  -h, --help              display this help and exit\n");
                return;
            }
            else if (strcmp(option, ">") == 0)
            {
                // 파일을 추가 쓰기 모드로 열고 없으면 생성
                // directoryTree에 파일 추가 touch 이용하면 좋을 것 같음
                FILE *file = fopen(fileName, "a");
                if (file)
                {
                    char buffer[1024];
                    printf("File '%s' already exists. Do you want to overwrite it? (Y/N): ", fileName);
                    char response;
                    response = getch();
                    if (response == 'Y' || response == 'y')
                    {
                        // 입력 받은 내용을 파일에 적음
                        printf("Enter text (Press Ctrl+D to save and exit):\n");
                        while (fgets(buffer, sizeof(buffer), stdin))
                        {
                            fputs(buffer, file);
                        }
                        printf("File '%s' overwritten successfully.\n", fileName);
                    }
                    else
                    {
                        printf("Operation canceled. File '%s' not overwritten.\n", fileName);
                    }
                    fclose(file);
                }
                else
                {
                    printf("Failed to open file '%s'.\n", fileName);
                }
                return;
            }
            else
            {
                printf("Invalid option: %s\n", option);
            }
        }
        // 옵션이 없을 때 기본 출력
        else
        {
            // 파일 내용 출력
            FILE *file = fopen(fileName, "r");
            if (file)
            {
                char buffer[1024];
                while (fgets(buffer, sizeof(buffer), file))
                {
                    printf("%s", buffer);
                }
                fclose(file);
            }
            else
            {
                printf("Permission denied or File not found: %s\n", fileName);
            }
        }
    }
    else // 파일이 존재하지 않거나 읽기 권한이 존재하지 않는 경우
    {
        printf("Permission denied or File not found: %s\n", var);
        printf("Usage: cat [OPTION] [FILE...]\n");
    }
}