/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:50:51 by anematol          #+#    #+#             */
/*   Updated: 2025/05/29 19:37:01 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp_next;

	temp = *lst;
	while (temp != NULL)
	{
		temp_next = temp->next;
		ft_lstdelone(temp, del);
		temp = temp_next;
	}
	*lst = NULL;
}
