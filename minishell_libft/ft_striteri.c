/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:37:53 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:27 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/*void convert_to_a(unsigned int index, char *character)
{
    // Changing each character to 'A'
    *character = 'z';
}

int main() {
    // Starting string
    char str[] = "Hello, World!";
	printf("Original string: %s\n", str);

    // Applying ft_striteri to convert each character to 'A'
    ft_striteri(str, convert_to_a);

    // Printing the modified string
    printf("Modified string: %s\n", str);

    return 0;
}*/
