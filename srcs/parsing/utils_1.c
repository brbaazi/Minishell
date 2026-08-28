/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:36:49 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/16 20:39:40 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_separator(t_token *tok, t_cmd **list, t_cmd **curr)
{
	if (tok->type == TOKEN_PIPE)
		(*curr)->pipe_out = 1;
	cmd_add_back(list, *curr);
	*curr = new_command();
	return (1);
}

int	process_single_token(t_token **tokens, t_cmd **cmd_list,
		t_cmd **current_cmd, int *expect_cmd)
{
	if ((*tokens)->type == TOKEN_WORD
		&& is_variable_assignment((*tokens)->value)
		&& !*cmd_list && !(*current_cmd)->args)
	{
		add_arg(*current_cmd, ft_strdup("export"));
		add_arg(*current_cmd, ft_strdup((*tokens)->value));
		cmd_add_back(cmd_list, *current_cmd);
		*current_cmd = new_command();
		*tokens = (*tokens)->next;
		return (1);
	}
	if (!process_token_loop(tokens, cmd_list, current_cmd, expect_cmd))
		return (0);
	*tokens = (*tokens)->next;
	return (1);
}

int	is_separator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE);
}
