/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:48:05 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/09 12:33:41 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
	{
		return ;
	}
	new->next = *lst;
	*lst = new;
}
/*int main()
{
    int value1 = 42;
    t_list *head = ft_lstnew(&value1);
    int value2 = 99;
    t_list *new_node = ft_lstnew(&value2);
    ft_lstadd_front(&head, new_node);
    printf("%d\n", *(int *)(head->content));
    printf("%d\n", *(int *)(head->next->content));
    free(new_node);
    free(head);
}*/
