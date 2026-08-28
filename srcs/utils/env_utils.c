/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:00:25 by brbaazi          #+#    #+#             */
/*   Updated: 2025/07/30 16:00:25 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_envp_entry(char **envp, int i, t_env *node)
{
	char	*temp;

	if (node->value)
	{
		temp = ft_strjoin(node->key, "=");
		envp[i] = ft_strjoin(temp, node->value);
	}
	else
		envp[i] = ft_strdup(node->key);
	if (!envp[i])
		return (0);
	return (1);
}

t_env	*get_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = gc_malloc(sizeof(t_env), 1);
	if (!node)
		gc_malloc(0, 0);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	process_env_entry(char *entry, t_env **head, t_env **current)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		key_len;
	t_env	*node;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign)
	{
		key_len = equal_sign - entry;
		key = ft_strndup(entry, key_len);
		value = equal_sign + 1;
		node = new_env_node(key, value);
		if (!*head)
			*head = node;
		else
			(*current)->next = node;
		*current = node;
	}
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		process_env_entry(envp[i], &head, &current);
		i++;
	}
	return (head);
}
