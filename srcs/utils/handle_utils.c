/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:34:10 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/18 11:19:24 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (!ft_strcmp(cmd->args[0], "cd")
		|| !ft_strcmp(cmd->args[0], "echo")
		|| !ft_strcmp(cmd->args[0], "pwd")
		|| !ft_strcmp(cmd->args[0], "export")
		|| !ft_strcmp(cmd->args[0], "unset")
		|| !ft_strcmp(cmd->args[0], "env")
		|| !ft_strcmp(cmd->args[0], "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd, int flag)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (cd_builtin(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(shell, cmd));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(shell->env_list));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (mini_exit(shell, cmd, flag));
	return (1);
}

void	exec_child(t_shell *shell, t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_redirections(cmd) == -1)
		cleanup_and_exit(EXIT_FAILURE);
	if (is_builtin(cmd))
		cleanup_and_exit(exec_builtin(shell, cmd, 0));
	cleanup_and_exit(exec_external(shell, cmd));
}

void	write_error_msg(char *cmd, char *suffix)
{
	int		len;
	char	*msg;

	len = ft_strlen("minishell: ") + ft_strlen(cmd) + ft_strlen(suffix);
	msg = gc_malloc(len + 1, 1);
	ft_strlcpy(msg, "minishell: ", len + 1);
	ft_strlcat(msg, cmd, len + 1);
	ft_strlcat(msg, suffix, len + 1);
	write(2, msg, len);
}
