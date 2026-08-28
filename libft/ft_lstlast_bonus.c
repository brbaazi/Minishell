/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:30:06 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/14 19:18:40 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*int main()
{
    t_list *head;
    char *a = "jellal";
    head = ft_lstnew(a);
    char *c = "abde";
    t_list *new1 = ft_lstnew(c);
    t_list *last;
    last = ft_lstlast(head);
    printf("%s\n", (char *)(head->content));
    printf("%s\n", (char *)(last->content));
    free(head);
    free(new1);
}*/
