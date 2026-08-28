/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:02:28 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 11:25:36 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(size_t size, int mode)
{
	static t_list	*temp_head = NULL;
	t_list			*node;
	void			*ptr;

	if (mode == 0)
	{
		ft_lstclear(&temp_head, free);
		temp_head = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	if (ptr == NULL)
	{
		gc_malloc(0, 0);
		return (NULL);
	}
	node = ft_lstnew(ptr);
	if (node == NULL)
	{
		free(ptr);
		gc_malloc(0, 0);
		return (NULL);
	}
	ft_lstadd_back(&temp_head, node);
	return (ptr);
}
