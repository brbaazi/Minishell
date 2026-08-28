/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:33 by abjellal          #+#    #+#             */
/*   Updated: 2025/07/17 21:54:33 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*new;
// 	size_t	slen;
// 	size_t	finish;

// 	if (!s)
// 		return (NULL);
// 	slen = ft_strlen(s);
// 	finish = 0;
// 	if (start < slen)
// 		finish = slen - start;
// 	if (finish > len)
// 		finish = len;
// 	new = (char *)gc_malloc(sizeof(char) * (finish + 1));
// 	if (!new)
// 		return (NULL);
// 	ft_strlcpy(new, s + start, finish + 1);
// 	return (new);
// }

/*int main()
{
	char str[] = "hi how are you";
	unsigned int start = 3;
	size_t len = 7;
	printf("%s\n", ft_substr(str, start, len));
}*/