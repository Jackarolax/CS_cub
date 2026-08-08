/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:54 by anematol          #+#    #+#             */
/*   Updated: 2025/05/29 19:24:21 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
/*
int main()
{
	int a = 5;
	int b = 4;

	t_list *node = ft_lstnew(&a);
	t_list *new_node = ft_lstnew(&b);
	t_list **list = &node;
	ft_lstadd_back(list, new_node);
	t_list *temp = *list;
	while (temp != NULL)
	{
		printf("%i\n", *(int*)temp->content);
		temp = temp->next;
	}

}
*/
