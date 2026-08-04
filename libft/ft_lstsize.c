/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:19:21 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 16:03:41 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lst_size;

	lst_size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		lst_size++;
	}
	return (lst_size);
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

	int size = ft_lstsize(*list);

	printf("%i\n", size);

}
*/
