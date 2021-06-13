/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:08:02 by kzennoun          #+#    #+#             */
/*   Updated: 2021/06/09 16:09:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (casted_s1[i] != casted_s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (casted_s1[i] - casted_s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	long int		nb;
	long int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	if (nb * sign > 2147483647)
		return (-1);
	if (nb * sign < -2147483648)
		return (0);
	return (nb * sign);
}

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