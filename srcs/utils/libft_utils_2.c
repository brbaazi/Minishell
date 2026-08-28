/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:42:09 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 09:21:24 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	finish;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	finish = 0;
	if (start < slen)
		finish = slen - start;
	if (finish > len)
		finish = len;
	new = (char *)gc_malloc(sizeof(char) * (finish + 1), 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s + start, finish + 1);
	return (new);
}

static void	copy_string(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = gc_malloc(len1 + len2 + 1, 1);
	if (!ptr)
		return (NULL);
	copy_string(ptr, s1);
	copy_string(ptr + len1, s2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

int	wait_and_update_exit_status(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (shell->exit_status == 130)
			write(1, "\n", 1);
		else if (shell->exit_status == 131)
			write(1, "Quit (core dumped)\n", 19);
	}
	return (shell->exit_status);
}

char	*check_full_path(char *full_path)
{
	if (access(full_path, F_OK) == 0)
		return (full_path);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}
