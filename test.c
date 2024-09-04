#include <stdio.h>


/*int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	negative;
	int		result;

	i = 0;
	negative = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = -negative;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * negative);
}

int main(void)
{
    int res = 256 - (345 % 256);
    printf("%i\n", res);
    return (0);
}*/
