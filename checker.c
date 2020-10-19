#include "wolf3d.h"


int flines(int fd)
{
    char *line;
    int c;

    c = 0;
    while (get_next_line(fd, &line) == 1)
        c++;
        close(fd);
    return(c);
}

int fcoln(char *line)
{
    int c;
    char **tmp;
    c = 0;
    tmp = ft_split_whitespaces(line);
    while (tmp[c])
        c++;
    if (c != 20)
        c = 0;
    return(c);
}

int **ft_check(int ac, char **av)
{
    if (ac == 2)
    {
        int fd = open(av[1], O_RDONLY);
        int l = flines(fd);
        if (l != 13)
            return(0);
        else
        {
            char *line;
            int c = 0;
            fd = open(av[1], O_RDONLY);
            int i = 0, j = 0;
            int **map = NULL;
            map = malloc(l * sizeof(int *));
            while (get_next_line(fd, &line) == 1)
            {
                c = fcoln(line);
                if (c == 0)
                    return(0);
                else
                {
                    map[i] = malloc(sizeof(int) * c);
                    char **tmp = ft_split_whitespaces(line);
                    j = 0;
                    while (j < c)
                    {
                        map[i][j] = ft_atoi(tmp[j]);
                        j++;
                    }
                
                }
                i++;
            }
            return (map);
        }
    }
    return (0);
}