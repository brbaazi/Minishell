/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:49:41 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 16:01:04 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child_process(t_redirect *redir, t_shell *shell, int pipefd[2])
{
	signal_flag(1);
	handle_signals();
	close(pipefd[0]);
	heredoc_loop(redir, shell, pipefd[1]);
	close(pipefd[1]);
	cleanup_and_exit(0);
}

static int	handle_signaled_child(int status, t_shell *shell, int pipefd[2])
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		shell->exit_status = 130;
		return (-1);
	}
	return (0);
}

static int	handle_exited_child(int status, t_shell *shell, int pipefd[2])
{
	int	exit_code;

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 1)
		{
			close(pipefd[0]);
			shell->exit_status = 130;
			return (-1);
		}
		else if (exit_code == 130)
		{
			close(pipefd[0]);
			shell->exit_status = 130;
			return (-1);
		}
		else if (exit_code == 0)
		{
			shell->exit_status = 0;
			return (pipefd[0]);
		}
	}
	return (close(pipefd[0]), -1);
}

int	heredoc_parent_process(pid_t pid, t_shell *shell, int pipefd[2])
{
	int	status;
	int	result;

	(void)pid;
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	signal_flag(0);
	handle_signals();
	result = handle_signaled_child(status, shell, pipefd);
	if (result != 0)
		return (result);
	return (handle_exited_child(status, shell, pipefd));
}

void	heredoc_loop(t_redirect *redir, t_shell *shell, int write_fd)
{
	char	*line;
	char	*delim;

	delim = redir->file;
	delim = remove_soh(delim);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file\n");
			cleanup_and_exit(0);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (shell->expand_in_herdoc)
			expnd(shell, line, write_fd);
		else
			ft_putendl_fd(line, write_fd);
		free(line);
	}
}
