#include "../header/main.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

#define PAGELEN 24
#define LINELEN 512

int getch(void) // 입력 버퍼 X, 문자 표시 X 입력 함수
{
#ifdef _WIN32
    return _getch();
#else
    struct termios old;
    struct termios new;

    int ch;

    tcgetattr(0, &old);

    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    new.c_cc[VMIN] = 1;
    new.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &new);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &old);

    return ch;
#endif
}

int more_line()
{
    int c;
    while ((c = getch()) != EOF)
    {
        if (c == 'q' || c == 'Q')
            return 0;
        if (c == ' ')
            return PAGELEN;
        if (c == '\n')
            return 1;
        // if (c == 'b')
        //     return -1; // 한 페이지 앞으로 이동
    }
    return 0;
}

void more(char *filename)
{
    FILE *fp;
    char line[LINELEN];
    int linenum = 0;
    int reply;
    FILE *fp_tty;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        exit(1);
    }

    fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL)
    {
        fclose(fp);
        fprintf(stderr, "Error: Cannot open terminal\n");
        exit(1);
    }

    while (fgets(line, LINELEN, fp))
    {
        if (linenum == PAGELEN)
        {
            reply = more_line();
            if (reply == 0)
                break;
            // else if (reply < 0) // b를 눌렀을 때
            // {
            //     fseek(fp, -(PAGELEN - 1) * LINELEN, SEEK_CUR); // 한 페이지 앞으로 이동
            //     linenum = 0;
            // }
            else
                linenum -= reply;
        }
        if (fputs(line, stdout) == EOF)
        {
            fclose(fp);
            fclose(fp_tty);
            fprintf(stderr, "Error: Failed to write to stdout\n");
            exit(1);
        }
        linenum++;
    }

    fclose(fp);
    fclose(fp_tty);
}
