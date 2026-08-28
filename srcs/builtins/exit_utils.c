/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:42:01 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/18 10:07:49 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;
	int	sign;
	int	trailing_check;

	if (!str || !str[0])
		return (0);
	i = skip_spaces_and_sign(str, &sign);
	if (!str[i])
		return (0);
	while (str[i])
	{
		trailing_check = check_trailing_spaces(str, i);
		if (trailing_check != -1)
			return (trailing_check);
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_positive_overflow(long long result, int digit)
{
	if (result > (LLONG_MAX - digit) / 10)
		return (0);
	return (1);
}

static int	check_negative_overflow(long long result, int digit)
{
	if (result > (LLONG_MAX - digit) / 10)
	{
		if (result == 922337203685477580LL && digit == 8)
			return (1);
		return (0);
	}
	return (1);
}

int	check_overflow(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	i = skip_spaces_and_sign(str, &sign);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		if (sign == 1 && !check_positive_overflow(result, str[i] - '0'))
			return (0);
		if (sign == -1 && !check_negative_overflow(result, str[i] - '0'))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	is_valid_long_long(const char *str)
{
	if (!is_numeric(str))
		return (0);
	return (check_overflow(str));
}
