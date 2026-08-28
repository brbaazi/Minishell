/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:46:24 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/16 21:00:44 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	set_env_value(t_env *env, char *key, char *value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_strdup(value);
			if (!current->value)
				return (1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

void	add_env(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = gc_malloc(sizeof(t_env), 1);
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (!new->key)
		return ;
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	if (value && !new->value)
		return ;
	new->next = NULL;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	**env_to_array(t_env *env_list)
{
	char	**envp;
	int		i;
	t_env	*tmp;
	int		size;

	tmp = env_list;
	size = 0;
	while (tmp && ++size)
		tmp = tmp->next;
	envp = gc_malloc(sizeof(char *) * (size + 1), 1);
	if (!envp)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (!fill_envp_entry(envp, i, tmp))
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
