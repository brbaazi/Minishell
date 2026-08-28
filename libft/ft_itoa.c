/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:34:34 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/13 18:36:24 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_converter(char *str, int len, long num)
{
	while (num > 0)
	{
		str[len] = '0' + (num % 10);
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	long	num;
	char	*p;
	int		len;

	num = n;
	len = ft_numlen(num);
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (num == 0)
	{
		p[0] = '0';
		return (p);
	}
	if (num < 0)
	{
		p[0] = '-';
		num = -num;
	}
	ft_converter(p, len - 1, num);
	return (p);
}
/*
int main()
{
    int n = 0;
    char *str = ft_itoa(n);
    if (str)
	{
        printf("%s\n", str);
        free(str);
	}
}*/