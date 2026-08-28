/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:34:10 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/15 14:01:26 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*allocate_status_array(int cmd_count)
{
	int	*status;
	int	i;

	status = gc_malloc(sizeof(int) * cmd_count, 1);
	if (!status)
		return (NULL);
	i = 0;
	while (i < cmd_count)
	{
		status[i] = 0;
		i++;
	}
	return (status);
}

static int	wait_for_children(pid_t *pids, int cmd_count, t_shell *shell)
{
	int	exit_value;
	int	appeared;
	int	*status;

	exit_value = 0;
	appeared = 0;
	status = allocate_status_array(cmd_count);
	if (!status)
		return (1);
	wait_all_children(pids, cmd_count, status, &appeared);
	if (WIFSIGNALED(status[cmd_count - 1]))
	{
		exit_value = WTERMSIG(status[cmd_count - 1]);
		shell->exit_status = exit_value + 128;
	}
	else if (WIFEXITED(status[cmd_count - 1]))
	{
		exit_value = WEXITSTATUS(status[cmd_count - 1]);
		shell->exit_status = exit_value;
	}
	if (appeared == 2)
		write(1, "\n", 1);
	else if (appeared == 3 && shell->exit_status != 0)
		write(1, "Quit (core dumped)\n", 19);
	return (shell->exit_status);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	pid_t	*pids;
	int		cmd_count;
	int		in_fd;

	cmd_count = count_commands(cmd);
	pids = gc_malloc(sizeof(pid_t) * cmd_count, 1);
	if (!pids)
		return (1);
	in_fd = STDIN_FILENO;
	signal(SIGINT, SIG_IGN);
	fork_and_execute(shell, cmd, pids, &in_fd);
	wait_for_children(pids, cmd_count, shell);
	signal_flag(0);
	handle_signals();
	return (shell->exit_status);
}
