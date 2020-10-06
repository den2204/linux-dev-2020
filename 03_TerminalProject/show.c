#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#define DX 3


char **parse_file(char *filename, int *ret_sz)
{

    struct stat info;
    stat(filename, &info);
    int sz = info.st_size;
    char *buf = malloc(sizeof(char) * (sz));
    int fd = open(filename, O_RDONLY);
    read(fd, buf, sz);
    close(fd);
    int cnt = 1;
    for (int i = 0; i < sz; i++)
    {
        cnt += (int)(buf[i] == '\n');
    }

    char **res = malloc(sizeof(char *) * cnt);


    int l = 0;
    int r = 0;
    int i = 0;
    while(r < sz)
    {
        while (r < sz && buf[r] != '\n')
        {
            r++;
        }
        if (l == r)
        {
            res[i] = malloc(sizeof(char));
            res[i][0] = ' ';
        }
        else
        {
            res[i] = malloc((r - l + 1) * sizeof(char));
            strncpy(res[i], buf + l, r - l);
            res[i][r - l] = '\0';
        }
        i++;
        l = r = r + 1;
    }

    while (i != cnt)
    {
        res[i] = malloc(sizeof(char));
        res[i][0] = ' ';
        i++;
    }

    *ret_sz = cnt;
    free(buf);
    return res;
}

int main(int argc, char **argv)
{
    char *filename = argv[1];

    if (filename == NULL)
    {
        printf("filename is NULL\n");
        return 5;
    }
    int sz = 0;
    char **content = parse_file(filename, &sz);
    initscr();
    noecho();
    cbreak();
    refresh();
    int up = 0;
    wchar_t c = 0;

    int H = LINES - 2 * DX;
    int W = COLS - 2 * DX;
    int real_lines = H - 2;
    int real_cols = W - 2 - 4;

    WINDOW *win = newwin(H, W, DX, DX);
    WINDOW *name_win = newwin(1, COLS, 0, 0);

    keypad(win, TRUE);
    scrollok(win, TRUE);
    do
    {
        werase(name_win);
        mvwprintw(name_win, 0, 0, "Filename: %s", filename);
        if ((c == ' ' || c == KEY_DOWN) && up + real_lines < sz)
        {
            up++;
        }
        if (c == KEY_UP && up > 0)
        {
            up--;
        }
        wrefresh(name_win);
        werase(win);
        for (int j = 0; j < real_lines && up + j < sz; j++)
        {
            int clen = strlen(content[up + j]);
            if (clen > real_cols)
            {
                char *tmp = malloc(sizeof(char) * (real_cols + 1));
                strncpy(tmp, content[up + j], real_cols);
                mvwprintw(win, j + 1, 1, "%3d %s", up + j + 1, tmp);
                free(tmp);
            }
            else
            {
                mvwprintw(win, j + 1, 1, "%3d %s", up + j + 1, content[up + j]);
            }
        }
        box(win, 0, 0);
        wrefresh(win);
    }
    while ((c = wgetch(win)) != 27); 
    for (int i = 0; i < sz; i++)
    {
        free(content[i]);
    }
    free(content);
    endwin();

    return 0;
}
