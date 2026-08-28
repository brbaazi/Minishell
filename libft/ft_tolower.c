/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:40:52 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/12 12:43:29 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int chr)
{
	if (chr >= 'A' && chr <= 'Z')
	{
		chr += 32;
		return (chr);
	}
	else
		return (chr);
}
/*int main()
{
	int chr = 'A';
	printf("%c", ft_tolower(chr));
}*/