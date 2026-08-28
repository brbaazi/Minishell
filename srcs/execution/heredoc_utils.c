/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:59:55 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 10:29:25 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredocs(t_cmd *cmd_list, t_shell *shell)
{
	t_redirect	*redir;

	while (cmd_list)
	{
		redir = cmd_list->redirs;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				redir->heredoc_fd = read_heredoc_input(redir, shell);
				if (redir->heredoc_fd < 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

int	read_heredoc_input(t_redirect *redir, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		heredoc_child_process(redir, shell, pipefd);
	return (heredoc_parent_process(pid, shell, pipefd));
}

char	*remove_soh(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 1)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	expnd(t_shell *shell, char *line, int write_fd)
{
	char	*expanded;

	expanded = expand_heredoc_line(line, shell);
	ft_putendl_fd(expanded, write_fd);
}
