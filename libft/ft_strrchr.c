/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:24:17 by anematol          #+#    #+#             */
/*   Updated: 2025/05/29 17:31:06 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last_char;
	unsigned char	*ptr_s;
	unsigned char	uns_c;

	ptr_s = (unsigned char *)s;
	uns_c = (unsigned char)c;
	last_char = NULL;
	while (*ptr_s != '\0')
	{
		if (*ptr_s == (char)uns_c)
			last_char = (char *)ptr_s;
		ptr_s++;
	}
	if (uns_c == 0)
		return ((char *)ptr_s);
	return (last_char);
}
