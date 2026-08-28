/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:18:16 by brbaazi           #+#    #+#             */
/*   Updated: 2025/07/15 13:18:16 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dash_n(char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;
	int	first_arg;

	i = 1;
	flag = 0;
	first_arg = 1;
	if (!cmd || !cmd->args)
		return (1);
	while (cmd->args[i] && is_dash_n(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		if (!first_arg)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		first_arg = 0;
		i++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
