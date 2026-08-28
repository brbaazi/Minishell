/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:18:33 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 22:28:22 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(int exit_code)
{
	gc_malloc(0, 0);
	clear_history();
	exit(exit_code);
}

static void	exit_with_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	cleanup_and_exit(2);
}

static void	too_many_args_error(t_shell *shell)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	shell->exit_status = 1;
}

int	mini_exit(t_shell *shell, t_cmd *cmd, int flag)
{
	char		**args;
	long long	code;

	args = cmd->args;
	if (flag)
		ft_putendl_fd("exit", STDOUT);
	if (!args[1])
		cleanup_and_exit(shell->exit_status);
	if (!is_valid_long_long(args[1]))
		exit_with_error(args[1]);
	if (args[2])
	{
		too_many_args_error(shell);
		return (1);
	}
	code = ft_atoi(args[1]);
	cleanup_and_exit((unsigned char)code);
	return (0);
}
