/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 06:50:07 by kzennoun          #+#    #+#             */
/*   Updated: 2021/05/21 15:34:23 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_get_digit_count(long int n)
{
	int		i;

	if (n < 0)
		n *= -1;
	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				dc;
	long int		ln;

	ln = n;
	dc = ft_get_digit_count(ln);
	if (ln < 0)
		dc++;
	str = malloc((dc + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	if (ln < 0)
	{
		str[0] = '-';
		ln *= -1;
	}
	str[dc] = '\0';
	while (((dc >= 0 && str[0] != '-') || (dc > 0 && str[0] == '-')) && ln != 0)
	{
		str[dc - 1] = (ln % 10) + '0';
		ln /= 10;
		dc--;
	}
	return (str);
}
