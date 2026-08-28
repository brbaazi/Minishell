/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:07:46 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/09 10:07:46 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_expansion_loop(t_expand_state *st)
{
	while (*st->p)
	{
		if ((*st->p == '\'' && !st->in_d_quotes)
			|| (*st->p == '\"' && !st->in_s_quotes))
			process_quote(st);
		else if (*st->p == '$' && !st->in_s_quotes
			&& is_expandable(*(st->p + 1)))
		{
			process_dollar(st);
			continue ;
		}
		st->p++;
	}
}

static void	handle_segment_append(t_expand_state *st)
{
	if (st->p > st->segment_start)
		append_str_node(st->list,
			ft_substr(st->segment_start, 0, st->p - st->segment_start));
}

static char	*handle_quoted_empty(char *result, int was_quoted_var)
{
	if (was_quoted_var && (!result || result[0] == '\0'))
	{
		return (ft_strdup("\x01"));
	}
	return (result);
}

char	*expand_and_join(char *arg, t_shell *shell)
{
	t_expand_state	st;
	char			*result;
	int				was_quoted_var;

	was_quoted_var = (arg[0] == '"' && arg[1] == '$'
			&& ft_strchr(arg + 2, '"'));
	init_expand_state(&st, arg, shell);
	handle_expansion_loop(&st);
	handle_segment_append(&st);
	result = join_str_list(*st.list);
	result = handle_quoted_empty(result, was_quoted_var);
	return (result);
}

void	expander(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current_cmd;

	current_cmd = cmds;
	while (current_cmd)
	{
		expand_args(current_cmd, shell);
		expand_redirs(current_cmd, shell);
		current_cmd = current_cmd->next;
	}
}
