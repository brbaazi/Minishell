/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:05:54 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/12 12:05:57 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int asc)
{
	if (asc >= 0 && asc <= 127)
		return (1);
	return (0);
}
/*int main()
{
	int asc = 127;
	printf("%d", ft_isascii(asc));
}*/