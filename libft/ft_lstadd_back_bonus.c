/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:52:28 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/13 10:39:17 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

/*
t_list *ft_lstnew(void *content)
{
    t_list *node;
    
    node = (t_list *)malloc(sizeof(t_list));
    if (node == NULL)
    {
        return (NULL);
    }
    node->content = content;
    node->next = NULL;
    return (node);
}

int main()
{
    char *str = "hello";
    char *str2 = "hi";
    t_list *head = NULL;
    t_list *new = ft_lstnew(str);
    t_list *new2 = ft_lstnew(str2);
    ft_lstadd_back(&head, new);
    ft_lstadd_back(&head, new2);
    printf("%s\n",(char *)(head->content));
    printf("%s\n", (char *)(head->next->content));
         
}*/