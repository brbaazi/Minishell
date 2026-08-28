/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:59:52 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/16 21:05:47 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *prefix, char *target, char *message)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (target)
		write(STDERR_FILENO, target, ft_strlen(target));
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
}

int	print_and_return(t_env *env_list)
{
	print_exported_env(env_list);
	return (0);
}
