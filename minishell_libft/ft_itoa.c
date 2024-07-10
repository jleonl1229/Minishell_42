/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:03:16 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 18:23:10 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_digits(long nl)
{
	long	number;
	int		digits;

	number = nl;
	digits = 0;
	if (number == 0)
		digits = 1;
	if (number < 0)
	{
		digits++;
		number = -number;
	}
	while (number > 0)
	{
		number = number / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	long	nl;
	char	*result;

	nl = n;
	if (nl == 0)
		return (ft_strdup("0"));
	digits = count_digits(nl);
	result = ft_calloc(digits + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	if (nl < 0)
	{
		nl = nl * -1;
		result[0] = '-';
	}
	while (nl > 0)
	{
		result[--digits] = nl % 10 + '0';
		nl = nl / 10;
	}
	return (result);
}
/*int main(void)
{
    int n = -10;
    char *result = ft_itoa(n);
    printf("%s\n", result);
    return (0);
}*/
