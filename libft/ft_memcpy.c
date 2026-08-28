/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:07:43 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/15 23:17:27 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*desti;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	source = (unsigned char *)src;
	desti = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		desti[i] = source[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	char src[] = "hello world";
	char dest[10] = "ali";
	size_t n = 12;
	ft_memcpy(dest + 3, src, n);
	printf("%s\n", dest);
}*/