/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:08:01 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/15 18:10:45 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*source;

	if (dest == NULL && src == NULL)
		return (NULL);
	dst = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (dst > source)
	{
		dst += n;
		source += n;
		while (n--)
			*(--dst) = *(--source);
	}
	else
	{
		while (n--)
			*dst++ = *source++;
	}
	return (dest);
}

/*int main()
{
	char src[] = "hello world";
	char dest[10] = "alii";
	size_t n = 4;
	ft_memmove(dest + 4, src, n);
	printf("%s\n", dest);
}*/
