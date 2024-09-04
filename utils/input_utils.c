/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:08:42 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 18:31:20 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	checks if user inputed special chars "<", ">" or "||"
	more than 2 times contiguosly
	
	example: "<>>" and "|<|" should throw a syntax error

	returns 1 if invalid sequence, 0 otherwise
*/
int	invalid_sequence(char *line, int i, int count)
{
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			count = 1;
			while (line[i + 1] == '<' || line[i + 1] == '>'
				|| line[i + 1] == '|')
			{
				count++;
				i++;
			}
			if (count > 3)
			{
				printf("bash invalid_sequence: syntax error\
				near unexpected token '%c'\n", line[i -1]);
				return (1);
			}
			else if (count == 3)
				return (three_valid(line));
		}
		i++;
	}
	return (0);
}

/*
** Checks if line, after trimming leading whitespace characters,
** starts with an invalid character.
** Currently, only the pipe '|' is considered an invalid initial character.
** space_chars -> space in the beginning, rest are 9,10,11,12,13 ASCII
** Returns 1 if pipe '|' is found as the initial character, 0 otherwise.
 */

int	bad_initial_char(char *line, t_sh_data **sh)
{
	int			result;
	const char	*space_chars;
	char		*trimmed;

	result = 0;
	space_chars = " \t\n\v\f\r";
	trimmed = ft_strtrim((const char *)line, space_chars);
	if (trimmed == NULL)
		pre_parse_cleanup(sh, NULL, NULL);
	if (trimmed[0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		result = 1;
	}
	free(trimmed);
	return (result);
}

/*
**	Pretty simmilar to the bad_initial_char, but in this case
**	having '<', '|', or '>' as last chars throws syntax error in bash
**	returns 1 if mentioned char is found, 0 otherwise
**	ft_strlen(trimmed) == 0 -> to prevent bugs from line == empty string
*/
int	bad_final_char(char *line, t_sh_data **sh, int result)
{
	const char	*space_chars;
	char		*trimmed;
	int			sz;
	char		c;

	space_chars = " \t\n\v\f\r";
	trimmed = ft_strtrim((const char *)line, space_chars);
	sz = ft_strlen(trimmed);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (result);
	}
	if (trimmed == NULL)
		pre_parse_cleanup(sh, NULL, NULL);
	if (trimmed[sz - 1] == '<' || trimmed[sz -1] == '>')
	{
		c = trimmed[sz -1];
		result = 1;
		printf("bash b_f_char: syntax error near unexpected token '%c'\n", c);
	}
	else if (trimmed[sz -1] == '|')
		result = 7;
	free(trimmed);
	return (result);
}

/*
variables will be 1 if their type of quote is opened, 0 otherwise.
in the loop, if the condition is triggered 1 becomes 0 and 0 becomes 1
34 ASCII representation of double quotes,
39 for single quotes
returns 1 if open quotes found, 0 otherwise
*/

int	is_open_quotes(char *line)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*line != '\0')
	{
		if (*line == 34 && single_q == 0)
			double_q = !double_q ;
		else if (*line == 39 && double_q == 0)
			single_q = !single_q;
		line++;
	}
	if (single_q || double_q)
	{
		printf("syntax error: unclosed quotes\n");
		return (1);
	}
	return (0);
}

/*
checks if string is only space. 
returns 0 if non-space char found
*/
int	is_space(char *line)
{
	int	is_space;

	if (line == NULL || *line == '\0')
		return (0);
	is_space = 1;
	while (*line)
	{
		if (!((9 <= *line && *line <= 13) || *line == 32))
		{
			is_space = 0;
			break ;
		}
		line++;
	}
	return (is_space);
}
