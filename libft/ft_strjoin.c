/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:34:43 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/17 22:01:50 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	i;
// 	size_t	k;
// 	char	*ptr;

// 	if (s1 == NULL || s2 == NULL)
// 	{
// 		return (NULL);
// 	}
// 	i = 0;
// 	ptr = gc_malloc(ft_strlen(s1) + ft_strlen(s2) * sizeof(char) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (i < ft_strlen(s1))
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	k = 0;
// 	while (k < ft_strlen(s2))
// 	{
// 		ptr[i + k] = s2[k];
// 		k++;
// 	}
// 	ptr[i + k] = '\0';
// 	return (ptr);
// }
/*int main()
{
    char s1[] = "hi 9 ";
    char s2[] = "how are you";
    char *ptr = ft_strjoin(s1, s2);
    printf("%s\n", ptr);
}*/
