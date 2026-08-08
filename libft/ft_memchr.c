/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:07:57 by anematol          #+#    #+#             */
/*   Updated: 2025/05/28 14:27:17 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;
	unsigned char	uns_c;

	i = 0;
	ptr_s = (unsigned char *)s;
	uns_c = (unsigned char)c;
	while (i < n)
	{
		if (*ptr_s == uns_c)
			return (ptr_s);
		ptr_s++;
		i++;
	}
	return (NULL);
}
