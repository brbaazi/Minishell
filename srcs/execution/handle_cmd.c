/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:45:26 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 11:40:43 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (is_builtin(cmd) && !cmd->next && !cmd->redirs)
		return (exec_builtin(shell, cmd, 1));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_child(shell, cmd);
	if (pid > 0)
		return (wait_and_update_exit_status(pid, shell));
	signal_flag(0);
	handle_signals();
	perror("minishell");
	shell->exit_status = errno;
	return (shell->exit_status);
}
