/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:22:28 by anematol          #+#    #+#             */
/*   Updated: 2025/05/29 18:52:57 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptrsrc;
	unsigned char	*ptrdest;

	if (dest == NULL && src == NULL)
		return (dest);
	i = -1;
	ptrsrc = (unsigned char *)src;
	ptrdest = (unsigned char *)dest;
	if (ptrsrc >= ptrdest)
	{
		while (++i < n)
		{
			ptrdest[i] = ptrsrc[i];
		}
	}
	else
	{
		while (++i < n)
		{
			ptrdest[n - i - 1] = ptrsrc[n - i - 1];
		}
	}
	return (ptrdest);
}
