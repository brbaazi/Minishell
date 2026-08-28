/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:08:18 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/09 10:08:18 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quote(t_expand_state *state)
{
	if (state->p > state->segment_start)
		append_str_node(state->list,
			ft_substr(state->segment_start, 0,
				state->p - state->segment_start));
	if (*state->p == '\'')
		state->in_s_quotes = !state->in_s_quotes;
	else
		state->in_d_quotes = !state->in_d_quotes;
	state->segment_start = state->p + 1;
}

void	process_dollar(t_expand_state *state)
{
	if (state->p > state->segment_start)
		append_str_node(state->list,
			ft_substr(state->segment_start, 0,
				state->p - state->segment_start));
	append_str_node(state->list, get_var_value(&state->p, state->shell));
	state->segment_start = state->p;
}

void	init_expand_state(t_expand_state *st, char *arg, t_shell *sh)
{
	st->list = gc_malloc(sizeof(t_str_list *), 1);
	*st->list = NULL;
	st->p = arg;
	st->segment_start = arg;
	st->in_s_quotes = 0;
	st->in_d_quotes = 0;
	st->shell = sh;
}

static void	process_heredoc_expansion(char **p, char **segment_start,
		t_str_list **list_head, t_shell *shell)
{
	if (**p == '$' && is_expandable(*(*p + 1)))
	{
		if (*p > *segment_start)
			append_str_node(list_head,
				ft_substr(*segment_start, 0, *p - *segment_start));
		append_str_node(list_head, get_var_value(p, shell));
		*segment_start = *p;
	}
	else
		(*p)++;
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	t_str_list	*list_head;
	char		*p;
	char		*segment_start;
	char		*result;

	list_head = NULL;
	p = line;
	segment_start = line;
	while (*p)
	{
		process_heredoc_expansion(&p, &segment_start, &list_head, shell);
	}
	if (p > segment_start)
		append_str_node(&list_head,
			ft_substr(segment_start, 0, p - segment_start));
	result = join_str_list(list_head);
	return (result);
}
