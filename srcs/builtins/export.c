/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:39:22 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 11:56:48 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_invalid_option(t_shell *shell, char *arg)
{
	char	option_char[2];

	option_char[0] = arg[1];
	option_char[1] = '\0';
	ft_putstr_fd("minishell: export: -", 2);
	ft_putstr_fd(option_char, 2);
	ft_putstr_fd(": invalid option\n", 2);
	shell->exit_status = 2;
	return (2);
}

static int	handle_invalid(t_shell *shell, char *arg)
{
	handle_invalid_key(arg, shell);
	shell->exit_status = 1;
	return (1);
}

static void	update_or_add(t_shell *shell, t_env *existing, char *key,
		char *value)
{
	if (existing)
	{
		if (value)
		{
			existing->value = ft_strdup(value);
			if (!existing->value)
				return ;
		}
	}
	else
		add_env(&shell->env_list, key, value);
}

static int	handle_argument(t_shell *shell, char *arg, int is_first_arg)
{
	char	*key;
	char	*value;
	t_env	*existing;

	if (is_first_arg && arg[0] == '-' && arg[1] != '\0')
		return (handle_invalid_option(shell, arg));
	split_key_value(arg, &key, &value);
	if (!is_valid_identifier(key))
		return (handle_invalid(shell, arg));
	existing = get_env_node(shell->env_list, key);
	update_or_add(shell, existing, key, value);
	return (0);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	result;

	i = 1;
	if (!cmd->args[1])
		return (print_and_return(shell->env_list));
	shell->exit_status = 0;
	while (cmd->args[i])
	{
		result = handle_argument(shell, cmd->args[i], (i == 1));
		if (result == 2)
			return (shell->exit_status);
		i++;
	}
	return (shell->exit_status);
}
