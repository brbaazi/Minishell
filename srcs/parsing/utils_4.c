/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:29:58 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/16 11:23:48 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_redirect(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_args;

	if (!cmd || !arg)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = (char **)gc_malloc(sizeof(char *) * (i + 2), 1);
	if (!new_args)
		gc_malloc(sizeof(char *) * (i + 2), 0);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
}

int	add_redirect(t_cmd *cmd, int type, char *file)
{
	t_redirect	*new_redir;
	t_redirect	*last;

	if (!cmd || !file)
		return (0);
	new_redir = (t_redirect *)gc_malloc(sizeof(t_redirect), 1);
	if (!new_redir)
		gc_malloc(sizeof(t_redirect), 0);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
		return (0);
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	return (1);
}

void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
