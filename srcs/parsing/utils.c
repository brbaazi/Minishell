/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:05:27 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/15 15:31:39 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	skip_white_spaces(char **str)
{
	while (**str && is_white_space(**str))
		(*str)++;
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

char	*extract_quoted_string(char **input, t_shell *shell)
{
	char	*start;
	char	quote_type;
	char	*result;

	(void)shell;
	quote_type = **input;
	(*input)++;
	start = *input;
	while (**input && **input != quote_type)
	{
		(*input)++;
	}
	if (**input != quote_type)
	{
		print_error("minishell: ", *input, "unclosed quote\n");
		return (NULL);
	}
	result = ft_strndup(start, *input - start);
	(*input)++;
	return (result);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
