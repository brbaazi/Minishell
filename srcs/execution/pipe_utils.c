/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:46:34 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 11:49:20 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_execute(t_shell *shell, t_cmd *cmd, pid_t *pids, int *in_fd)
{
	int	pipe_fd[2];
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->pipe_out)
			create_pipe(pipe_fd);
		pids[i] = fork_process();
		if (pids[i] == 0)
			setup_child_process(shell, cmd, pipe_fd, *in_fd);
		parent_close_fds(cmd, pipe_fd, in_fd);
		if (!cmd->pipe_out)
			break ;
		cmd = cmd->next;
		i++;
	}
	return (0);
}

void	wait_all_children(pid_t *pids, int cmd_count, int *status,
		int *appeared)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status[i], 0);
		if (!(*appeared) && WIFSIGNALED(status[i]))
		{
			*appeared = WTERMSIG(status[i]);
		}
		i++;
	}
}

void	parent_close_fds(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (cmd->pipe_out)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}
