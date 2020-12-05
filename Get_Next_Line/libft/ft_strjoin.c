/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:25:47 by oes-safi          #+#    #+#             */
/*   Updated: 2019/04/08 23:41:57 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fun(char *fresh, char *str1, char *str2, int i)
{
	int		j;

	j = 0;
	while (str1[j])
	{
		fresh[j] = str1[j];
		j++;
	}
	while (str2[i])
	{
		fresh[j + i] = str2[i];
		i++;
	}
	fresh[j + i] = '\0';
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	char	*str1;
	char	*str2;
	int		i;
	int		k;

	if (s1 && s2)
	{
		str1 = (char *)s1;
		str2 = (char *)s2;
		i = 0;
		k = ft_strlen(s1) + ft_strlen(s2);
		fresh = (char *)malloc((k + 1) * sizeof(char));
		if (fresh == NULL)
			return (NULL);
		fun(fresh, str1, str2, i);
		return (fresh);
	}
	return (NULL);
}
