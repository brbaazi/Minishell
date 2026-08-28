/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:45 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/15 00:24:22 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	unsigned int	len;
	char			*ptr;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		ptr[index] = (*f)(index, s[index]);
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

/*char capitalize(unsigned int i, char c)
{
    if (i % 2 == 0 && c >= 'a' && c <= 'z')
    {
        return (c - 32);
    }
    return (c);
}

int main()
{
    
    char str[] = "hello world";
    char *res = ft_strmapi(str, capitalize);
    printf("%s", res);
}*/
