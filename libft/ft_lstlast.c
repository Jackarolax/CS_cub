/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:22:05 by anematol          #+#    #+#             */
/*   Updated: 2025/05/29 19:13:19 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int main()
{
	int a = 6;
	int b = 5;
	int c = 4;

	t_list *a_node = ft_lstnew(&a);
	t_list *node = ft_lstnew(&b);
	t_list *new_node = ft_lstnew(&c);
	t_list **list = &a_node;

	ft_lstadd_front(list, node);
	ft_lstadd_front(list, new_node);
	t_list *last = ft_lstlast(*list);

	printf("%i\n", *(int*)last->content);

}
*/
