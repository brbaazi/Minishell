/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:19:57 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/10 11:42:44 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}

/*void ft_print(void *content)
{
    printf("%s\n", (char *)content);
}
int main()
{
    char *str = "hello";
    t_list *head;
    head = ft_lstnew(str);
    ft_lstiter(head, ft_print);
}*/
