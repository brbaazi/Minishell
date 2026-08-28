/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:07:17 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/09 10:07:17 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_operator(char **input, t_token **tokens)
{
	char	*op;

	if ((**input == '>' && *(*input + 1) == '>')
		|| (**input == '<' && *(*input + 1) == '<'))
	{
		op = ft_strndup(*input, 2);
		*input += 2;
		add_token(tokens, op, get_operator_type(op));
	}
	else
	{
		op = ft_strndup(*input, 1);
		(*input)++;
		add_token(tokens, op, get_operator_type(op));
	}
}

t_token	*handle_operator(char **input, t_token *tokens)
{
	char	*op;

	if (!input || !*input || !**input)
		return (NULL);
	if ((**input == '>' && *(*input + 1) == '>' && *(*input + 2) == '>')
		|| (**input == '<' && *(*input + 1) == '<' && *(*input + 2) == '<'))
	{
		op = ft_strndup(*input, 3);
		*input += 3;
		add_token(&tokens, op, TOKEN_ERROR);
	}
	else
		process_operator(input, &tokens);
	return (tokens);
}

t_token	*handle_word(char **input, t_token *tokens)
{
	char	*word;

	word = extract_word(input);
	if (!word)
	{
		free_tokens(tokens);
		return (NULL);
	}
	add_token(&tokens, word, TOKEN_WORD);
	return (tokens);
}

int	handle_pipe(t_token **tokens, t_cmd **cmd_list, t_cmd **current)
{
	if (!*cmd_list && !(*current)->args && !(*current)->redirs)
	{
		print_syntax_error("|");
		return (0);
	}
	cmd_add_back(cmd_list, *current);
	*current = new_command();
	if (!*current)
	{
		free_cmds(*cmd_list);
		return (0);
	}
	*tokens = (*tokens)->next;
	return (1);
}

int	handle_redirect(t_token **tokens, t_cmd **cmd_list, t_cmd *current)
{
	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
	{
		if ((*tokens)->next)
			print_syntax_error((*tokens)->next->value);
		else
			print_syntax_error("newline");
		return (0);
	}
	if (!add_redirect(current, (*tokens)->type, (*tokens)->next->value))
	{
		free_cmds(*cmd_list);
		free_cmd(current);
		return (0);
	}
	*tokens = (*tokens)->next->next;
	return (1);
}
