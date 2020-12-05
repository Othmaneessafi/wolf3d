/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 14:19:56 by oes-safi          #+#    #+#             */
/*   Updated: 2019/03/04 00:08:22 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		num_word(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] != ' ' && str[i] != '\t' &&
				str[i] != '\n' && str[i] != '\0')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\t' ||
					str[i + 1] == '\n' || str[i + 1] == '\0')
			{
				nb++;
			}
			i++;
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (nb);
}

int		num_lettre(char *str, int i)
{
	int j;

	j = 0;
	while (str[i + j])
	{
		if (str[i + j + 1] == ' ' || str[i + j + 1] == '\t' ||
				str[i + j + 1] == '\n' || str[i + j + 1] == '\0')
		{
			j++;
			return (j);
		}
		j++;
	}
	return (j);
}

char	**ft_split_whitespaces(char *str)
{
	int		i;
	int		k;
	int		m;
	char	**ch;

	i = 0;
	k = 0;
	ch = malloc((num_word(str) + 1) * sizeof(char*));
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		{
			m = 0;
			ch[k] = malloc((num_lettre(str, i) + 1) * sizeof(char));
			while (m < num_lettre(str, i - m))
				ch[k][m++] = str[i++];
			ch[k++][m++] = '\0';
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	ch[k] = 0;
	return (ch);
}
