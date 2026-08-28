/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:10:29 by abjellal          #+#    #+#             */
/*   Updated: 2024/11/17 12:15:33 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;

	if (!f || !lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&node, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}

/*void del_content(void *content)
{
    free(content);
}

void *transform_content(void *content)
{
    int *new_value = malloc(sizeof(int));
    if (!new_value)
        return NULL;
    *new_value = *(int *)content * 2;
    return new_value;
}

void print_list(t_list *lst)
{
    while (lst) {
        printf("%d -> ", *(int *)(lst->content));
        lst = lst->next;
    }
    printf("NULL\n");
}

int main()
{
    int *val;
    t_list *lst = NULL;
    t_list *mapped_lst;
    int i = 0;
    while (i <= 5)
	{
        val = malloc(sizeof(int));
        *val = i;
        ft_lstadd_back(&lst, ft_lstnew(val));
        i++;
    }

    printf("original list:\n");
    print_list(lst);
    mapped_lst = ft_lstmap(lst, transform_content, del_content);

    printf("mapped list:\n");
    print_list(mapped_lst);

    ft_lstclear(&lst, del_content);
    ft_lstclear(&mapped_lst, del_content);
}*/