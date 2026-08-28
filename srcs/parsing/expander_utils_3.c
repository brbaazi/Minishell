/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:32:08 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 11:29:59 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_args(t_cmd *cmd, t_shell *shell)
{
	char	*expanded_str;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		expanded_str = expand_and_join(cmd->args[i], shell);
		if (expanded_str)
			cmd->args[i] = expanded_str;
		else
			cmd->args[i] = ft_strdup("");
		i++;
	}
}

void	expand_redirs(t_cmd *cmd, t_shell *shell)
{
	t_redirect	*redir;
	char		*expanded_str;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != TOKEN_HEREDOC)
		{
			expanded_str = expand_and_join(redir->file, shell);
			if (expanded_str)
				redir->file = expanded_str;
			else
				redir->file = ft_strdup("");
		}
		redir = redir->next;
	}
}
