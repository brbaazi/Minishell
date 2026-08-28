/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:45:53 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 11:48:25 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_putstr_fd("minishell: fork", STDERR_FILENO);
	return (pid);
}

void	setup_child_process(t_shell *shell, t_cmd *cmd,
	int pipe_fd[2], int in_fd)
{
	int	out_fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->pipe_out)
		out_fd = pipe_fd[1];
	else
		out_fd = STDOUT_FILENO;
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (cmd->pipe_out)
		close(pipe_fd[0]);
	if (check_redirections(cmd) == -1)
		cleanup_and_exit(EXIT_FAILURE);
	if (is_builtin(cmd))
		cleanup_and_exit(exec_builtin(shell, cmd, 0));
	cleanup_and_exit(exec_external(shell, cmd));
}

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		if (!cmd->pipe_out)
			break ;
		cmd = cmd->next;
	}
	return (count);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	return (0);
}
