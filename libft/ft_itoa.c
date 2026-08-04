/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:57:21 by anematol          #+#    #+#             */
/*   Updated: 2025/05/30 09:28:12 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_digits_including_sign(int n)
{
	size_t	digits;

	digits = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	else if (n < 0)
	{
		n *= -1;
		digits++;
	}
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static char	*ft_init_str(size_t strlen)
{
	char	*str;

	str = (char *)malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[strlen] = '\0';
	return (str);
}

static char	*ft_return_intmin(void)
{
	char	*str;

	str = ft_init_str(11);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	digit_len;
	char	*num_str;
	int		i;
	int		sign;

	if (n == -2147483648)
		return (ft_return_intmin());
	digit_len = ft_get_digits_including_sign(n);
	num_str = ft_init_str(digit_len);
	if (!num_str)
		return (NULL);
	i = digit_len - 1;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		num_str[0] = '-';
	}
	n *= sign;
	while (i >= (0 + (sign == -1)))
	{
		num_str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (num_str);
}
/*
int main()
{
	int num = 12;

	char *num_str = ft_itoa(num);
	printf("%s\n", num_str);
}
*/
