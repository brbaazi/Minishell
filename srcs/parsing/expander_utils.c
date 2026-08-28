/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:07:51 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/09 10:07:51 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

void	append_str_node(t_str_list **list, char *str)
{
	t_str_list	*new_node;
	t_str_list	*current;

	if (!str)
		return ;
	new_node = gc_malloc(sizeof(t_str_list), 1);
	if (!new_node)
		gc_malloc(sizeof(t_str_list), 0);
	new_node->str = str;
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

char	*join_str_list(t_str_list *list)
{
	t_str_list	*current;
	char		*result;
	size_t		total_len;

	total_len = 0;
	current = list;
	while (current)
	{
		total_len += ft_strlen(current->str);
		current = current->next;
	}
	result = gc_malloc(total_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	current = list;
	while (current)
	{
		ft_strlcat(result, current->str, total_len + 1);
		current = current->next;
	}
	return (result);
}

static char	*get_var_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (NULL);
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_var_value(char **str_ptr, t_shell *shell)
{
	char	*var_name;
	char	*value;
	char	*temp;

	(*str_ptr)++;
	var_name = get_var_name(*str_ptr);
	if (!var_name)
		return (ft_strdup("$"));
	*str_ptr += ft_strlen(var_name);
	if (ft_strcmp(var_name, "?") == 0)
	{
		temp = ft_itoa(shell->exit_status);
		value = ft_strdup(temp);
		free(temp);
		return (value);
	}
	value = get_env_value(shell->env_list, var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
