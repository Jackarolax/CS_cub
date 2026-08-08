/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:56:52 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 15:55:49 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main()
{
	int a = 5;
	int b = 4;

	t_list *node = ft_lstnew(&a);
	t_list *new_node = ft_lstnew(&b);
	t_list **list = &node;
	ft_lstadd_front(list, new_node);
	t_list *temp = *list;
	while (temp != NULL)
	{
		printf("%i\n", *(int*)temp->content);
		temp = temp->next;
	}

}
*/
