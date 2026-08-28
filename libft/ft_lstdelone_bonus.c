/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:11:38 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/09 19:19:43 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del != NULL)
		del(lst->content);
	free(lst);
}

/*int main()
{
    char *str = "hello";
    str = malloc(sizeof(t_list));
    t_list *head = ft_lstnew(str);
    ft_lstdelone(head, free);
    head = NULL;
    if (head == NULL)
    {
        printf("node has been deleted\n");
    }
}*/