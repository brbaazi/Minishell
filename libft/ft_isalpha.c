/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:03:53 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/12 12:08:19 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int alph)
{
	if ((alph >= 65 && alph <= 90) || (alph >= 97 && alph <= 122))
		return (1);
	return (0);
}
/*int main()
{
	int alph = '1';
	printf("%d", ft_isalpha(alph));
}*/