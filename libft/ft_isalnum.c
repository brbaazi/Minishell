/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:05:22 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/12 12:08:50 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int num)
{
	if ((num >= 48 && num <= 57) || (num >= 65 && num <= 90))
		return (1);
	else if (num >= 97 && num <= 122)
		return (1);
	return (0);
}
/*int main()
{
	int num = '1';
	printf("%d", ft_isalnum(num));
}*/