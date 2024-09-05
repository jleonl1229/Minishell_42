/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:43:54 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 15:50:29 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  auxiliary to three_valid
*/
char	three_invalid_print(char *line, char *last_invalid)
{
	const char	invalid_chars[] = "<>|";
	char		*temp;
	int			i;

	i = 0;
	while (invalid_chars[i] != '\0')
	{
		temp = ft_strrchr((const char *)line, invalid_chars[i]);
		if (temp != NULL)
		{
			if (last_invalid == NULL || temp > last_invalid)
				last_invalid = temp;
		}
		i++;
	}
	if (last_invalid != NULL)
		return (*last_invalid);
	else
		return ('\0');
}

/*
**  checks if command line includes any of the only 2 valid 3 symbol combination
**  auxiliary to invalid_sequence()
*/
int	three_valid(char *line)
{
	const char	*patterns[] = {"|<<", "|>>", NULL};
	int			i;
	char		c;

	i = 0;
	while (patterns[i] != NULL)
	{
		if (ft_strnstr(line, patterns[i], ft_strlen(line)) != NULL)
			return (0);
		i++;
	}
	c = three_invalid_print(line, NULL);
	if (c != '\0')
		printf("bash: syntax error near unexpected token '%c'\n", c);
	return (1);
}

/*
**	Approach with input validation: catch as many syntax errors as possible 
**	without going too crazy, being aware that some will slip through, 
**	but expecting further parts of the code to flag them as different 
**	types of errors.

**	Input can be invalid because quotes are not closed (ex. <" '>), 
**	certain chars are at the beginning ("|") or end of line(">"),
**	there is a non-valid sequence(||) or there are spaces between
*	invalid sequence ("< <")

Returns 0 if not valid, 1 if valid and 7 if user inputed command ends with a pipe
*/
int	input_validation(char *line, t_sh_data **sh)
{
	int	e_pipe;

	if (*line == '\0' || is_space(line) == 1
		||is_open_quotes(line) == 1 || valid_not_implemented(line) == 1
		|| bad_initial_char(line, sh) == 1
		|| invalid_sequence(line, 0, 0) == 1 || space_and_chars(line, 0) == 1
		|| sized2_invalid(line) == 1)
		return (0);
	e_pipe = bad_final_char(line, sh, 0);
	if (e_pipe == 1)
		return (0);
	else if (e_pipe == 7)
		return (7);
	return (1);
}
