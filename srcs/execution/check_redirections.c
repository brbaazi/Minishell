/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:23:21 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/16 11:32:06 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append_redirect(t_redirect *redir)
{
	int	fd;

	if (redir->file[0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (-1);
	}
	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(" Permission denied", STDERR_FILENO);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_input_redirect(t_redirect *redir)
{
	int	fd;

	if (redir->file[0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (-1);
	}
	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		print_error("minishell: ", redir->file,
			": No such file or directory\n");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirect(t_redirect *redir, int flags)
{
	int	fd;

	if (redir->file[0] == '\0')
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (-1);
	}
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	process_single_redirect(t_redirect *redir)
{
	if (redir->type == TOKEN_REDIR_IN)
	{
		if (handle_input_redirect(redir) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_REDIR_OUT)
	{
		if (handle_output_redirect(redir, O_WRONLY | O_CREAT | O_TRUNC) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_APPEND)
	{
		if (handle_output_redirect(redir, O_WRONLY | O_CREAT | O_APPEND) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
	return (0);
}

int	check_redirections(t_cmd *cmd)
{
	t_redirect	*redir;

	if (!cmd || !cmd->redirs)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (process_single_redirect(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
