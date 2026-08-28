/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:07:05 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/09 10:07:05 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = gc_malloc(ft_strlen(str) + 1, 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
		}
		else
		{
			result[j] = str[i];
			j++;
			i++;
		}
	}
	result[j] = '\0';
	return (result);
}

static int	handle_word_or_redir(t_token **tok, t_cmd *cmd)
{
	t_token_type	type;
	char			*filename;

	type = (*tok)->type;
	if (type == TOKEN_WORD)
	{
		add_arg(cmd, (*tok)->value);
	}
	else
	{
		if (!(*tok)->next || (*tok)->next->type != TOKEN_WORD)
		{
			if ((*tok)->next)
				print_syntax_error((*tok)->next->value);
			else
				print_syntax_error("newline");
			return (0);
		}
		filename = strip_quotes((*tok)->next->value);
		add_redirect(cmd, type, filename);
		*tok = (*tok)->next;
	}
	return (1);
}

int	process_token_loop(t_token **tokens, t_cmd **cmd_list,
		t_cmd **current_cmd, int *expect_cmd)
{
	if (((*tokens)->type == TOKEN_ERROR
			|| (*tokens)->next == NULL)
		&& (*tokens)->type != TOKEN_WORD)
	{
		print_syntax_error((*tokens)->value);
		return (0);
	}
	if (is_separator(*tokens))
	{
		if (*expect_cmd)
		{
			print_syntax_error((*tokens)->value);
			return (0);
		}
		process_separator(*tokens, cmd_list, current_cmd);
		*expect_cmd = 1;
	}
	else if (!handle_word_or_redir(tokens, *current_cmd))
	{
		return (0);
	}
	else
		*expect_cmd = 0;
	return (1);
}

int	is_variable_assignment(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=');
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	int		expect_cmd;

	(void)shell;
	cmd_list = NULL;
	if (!tokens)
		return (NULL);
	current_cmd = new_command();
	expect_cmd = 1;
	while (tokens)
	{
		if (process_single_token(&tokens, &cmd_list, &current_cmd,
				&expect_cmd) == 0)
			return (NULL);
	}
	cmd_add_back(&cmd_list, current_cmd);
	return (cmd_list);
}
