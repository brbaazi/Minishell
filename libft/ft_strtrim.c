/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:23:33 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/15 00:24:39 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_trim_start(const char *s1, const char *set)
{
	int	beg;

	beg = 0;
	while (s1[beg] && ft_strchr(set, s1[beg]))
		beg++;
	return (beg);
}

static int	ft_get_trim_end(const char *s1, const char *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beg;
	int		end;
	int		len;
	int		i;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	beg = ft_get_trim_start(s1, set);
	end = ft_get_trim_end(s1, set);
	len = 0;
	if (end >= beg)
		len = end - beg + 1;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[beg + i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

/*int main()
{
	char s1[] = "hello";
	char set[] = "heo";
	printf("%s", ft_strtrim(s1, set));
}*/