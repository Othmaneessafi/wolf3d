/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oes-safi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 21:18:55 by oes-safi          #+#    #+#             */
/*   Updated: 2019/04/01 21:46:39 by oes-safi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				res;
	int				sign;
	unsigned char	*s;

	i = 0;
	res = 0;
	sign = 1;
	s = (unsigned char *)str;
	while (s[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\n')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] == '0')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}
