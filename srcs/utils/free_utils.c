/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:39:26 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/30 17:00:54 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_redirect(t_redirect *redir)
{
	if (!redir)
		return ;
	free(redir->file);
	free(redir);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_redirections(t_redirect *redirs)
{
	t_redirect	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free_redirect(tmp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;

	while (cmds)
	{
		tmp_cmd = cmds;
		cmds = cmds->next;
		free_str_array(tmp_cmd->args);
		free_redirections(tmp_cmd->redirs);
		free(tmp_cmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free_redirections(cmd->redirs);
	free(cmd);
}
