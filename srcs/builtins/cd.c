/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:16:22 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/17 11:55:15 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_value(shell->env_list, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			shell->exit_status = 1;
			return (NULL);
		}
		return (path);
	}
	return (cmd->args[1]);
}

int	ft_to_args(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	oldpwd_update(t_shell *shell, char *oldpwd)
{
	if (oldpwd)
	{
		if (get_env_value(shell->env_list, "OLDPWD"))
			set_env_value(shell->env_list, "OLDPWD", oldpwd);
		else
			add_env(&shell->env_list, "OLDPWD", oldpwd);
	}
}

void	pwd_update(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (get_env_value(shell->env_list, "PWD"))
			set_env_value(shell->env_list, "PWD", cwd);
		else
			add_env(&shell->env_list, "PWD", cwd);
	}
}

int	cd_builtin(t_shell *shell, t_cmd *cmd)
{
	char	cwd[1024];
	char	*path;
	char	*oldpwd;

	oldpwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		oldpwd = ft_strdup(cwd);
	if (ft_to_args(shell, cmd))
		return (1);
	path = get_path_cd(shell, cmd);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	oldpwd_update(shell, oldpwd);
	pwd_update(shell);
	shell->exit_status = 0;
	return (0);
}
