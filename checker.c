/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 05:52:32 by oes-safi          #+#    #+#             */
/*   Updated: 2020/12/04 06:06:05 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		flines(int fd)
{
	char	*line;
	int		c;

	c = 0;
	while (get_next_line(fd, &line) == 1)
		c++;
	close(fd);
	free(line);
	return (c);
}

int		fcoln(char *line)
{
	int		c;
	char	**tmp;

	c = 0;
	tmp = ft_split_whitespaces(line);
	while (tmp[c])
		c++;
	if (c != 20)
		c = 0;
	ft_free_tab(tmp);
	return (c);
}

int		check_line(char **av, int i)
{
	int		fd;
	char	*line;
	char	**tmp;

	fd = open(av[1], O_RDONLY);
	if ((get_next_line(fd, &line) == 1) && (tmp = ft_split_whitespaces(line)))
		while (tmp[++i])
			if (ft_atoi(tmp[i]) == 0)
				return (0);
	while (get_next_line(fd, &line) == 1)
		i++;
	tmp = ft_split_whitespaces(line);
	i = -1;
	while (tmp[++i])
		if (ft_atoi(tmp[i]) == 0)
		{
			free(line);
			ft_free_tab(tmp);
			return (0);
		}
	free(line);
	ft_free_tab(tmp);
	close(fd);
	return (1);
}

int		checker(t_wolf *wolf, char *line, int i, int c)
{
	int		j;
	char	**t;

	if (c == 0)
	{
		free(line);
		return (0);
	}
	else
	{
		if ((wolf->map[i] = malloc(sizeof(int) * c)) == NULL)
		{
			free(line);
			exit(0);
		}
		t = ft_split_whitespaces(line);
		if ((ft_atoi(t[0]) == 0 || ft_atoi(t[c - 1]) == 0 || ((i == 1 &&
		((ft_atoi(t[1]) != 0) || (ft_atoi(t[2]) != 0))) || ((i == 2 &&
		((ft_atoi(t[1]) != 0) || (ft_atoi(t[2]) != 0)))))) && (ft_free_tab(t)))
			return (0);
		j = -1;
		while (++j < c)
			wolf->map[i][j] = ft_atoi(t[j]);
	}
	return (1);
}

int		ft_check(char **av, t_wolf *wolf, int i)
{
	int		fd;
	int		l;
	char	*line;
	int		c;

	fd = open(av[1], O_RDONLY);
	l = flines(fd);
	if ((l != 13) || (check_line(av, -1)) == 0)
		return (0);
	else
	{
		fd = open(av[1], O_RDONLY);
		if ((wolf->map = malloc((l + 1) * sizeof(int *))) == NULL)
			exit(0);
		while (get_next_line(fd, &line) == 1)
		{
			c = fcoln(line);
			if (!(checker(wolf, line, i, c)))
				return (0);
			i++;
		}
		wolf->map[i] = NULL;
		return (1);
	}
	return (0);
}
